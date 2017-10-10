#pragma once

#include <windows.h>
#include <winscard.h>
#include <stdio.h>
#include <assert.h>
#include "CONSTANTS.h"

#define PCSC_TRANS_BUFF_LEN	(262)
#define PCSC_RECV_BUFF_LEN	(262)

public class ConnectCard {
public:
	ConnectCard() {

	}

	SCARD_IO_REQUEST *CardProtocol2PCI(DWORD dwProtocol)
	{
		if (dwProtocol == SCARD_PROTOCOL_T0) {
			return (SCARD_IO_REQUEST *)SCARD_PCI_T0;
		}
		else if (dwProtocol == SCARD_PROTOCOL_T1) {
			return (SCARD_IO_REQUEST *)SCARD_PCI_T1;
		}
		else if (dwProtocol == SCARD_PROTOCOL_RAW) {
			return (SCARD_IO_REQUEST *)SCARD_PCI_RAW;
		}
		else if (dwProtocol == SCARD_PROTOCOL_UNDEFINED) {
			assert(false);
			return NULL;
		}

		return (SCARD_IO_REQUEST *)SCARD_PCI_T1;
	}

	CONSTANTS* constants;    //定数クラスをインスタンス化

	/*概要：機器との通信を行うためのリソースマネージャを確保するための関数
	引数：なし
	戻り値：unsigned long hContext確保したリソースマネージャ
	作成日：2017.10.10
	作成者：K.Asada*/
	unsigned long EstablishContext() {
		SCARDCONTEXT hContext = 0;        //確保したリソースマネージャのアドレス
		unsigned long lResult;                     //リソースマネージャを確保した際の結果を格納するための変数
		//リソースマネージャを確保し、その結果を取得する
		lResult = ::SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hContext);
		//もし確保に失敗していたら例外を投げる
		if (lResult != SCARD_S_SUCCESS) {
			//エラー内容により分岐
			if (lResult == SCARD_E_NO_SERVICE) {
				//リソースマネージャの確保に失敗した時のエラーを投げる
		//		throw gcnew System::Exception(NO_SERVICE_ERROR);
			}
			//それ以外の時はその他エラー
			else {
				//その他のエラーとして例外を投げる
	//			throw gcnew System::Exception(ESTABLISH_ERROR);
			}
		}
		//確保したリソースマネージャのアドレスを返す
		return hContext;
	}

	/*概要：確保したリソースマネージャの名前が目的のカードリーダの名前と一致しているかを調べるための関数
	引数：unsigned long Context：確保したリソースマネージャ
	戻り値；なし
	作成日：2017.10.10
	作成者：K.Asada*/
	void CheckReaderName(unsigned long Context) {
		char* ReaderName = NULL;                      //取得したリーダの名前を格納するための文字列
		unsigned long dwAutoAllocate = SCARD_AUTOALLOCATE;    //アロケータ
		unsigned long lResult;                                 //名前を正しく取得できたかの判定を格納するための文字列
		//確保したリソースマネージャのリーダの名前調べる
		lResult = ::SCardListReaders(Context, NULL, (WCHAR*)&ReaderName, &dwAutoAllocate);
		//失敗したら例外を投げる
		if (lResult != SCARD_S_SUCCESS) {
			//目的のリーダーと違っていたらその旨を例外として投げる
			if (lResult == SCARD_E_NO_READERS_AVAILABLE) {
				//リーダーが違う旨の例外を投げる
			//	throw gcnew System::Exception(NO_READERS_ERROR);
			}//それ以外のエラーは別のメッセージを投げる
			else {
				//何らかのエラーが発生して処理を中断した旨を例外として投げる
		//		throw gcnew System::Exception(ERROR);
			}
		}
		//目的のリーダーの名前と違っていたらその旨を例外として伝える
		if (ReaderName != constants->PASORI_NAME) {
			//リーダーが違う旨を例外として投げる
	//		throw gcnew System::Exception(NO_READERS_ERROR);
		}
		//カード、リーダーとの接続を終了する
		EndConnect(Context);
		return;
	}

	/*概要：カードへデータ送受信などのコマンドを送信するための関数
	引数：unsigned long：リーダーへのリソースマネージャ
		：unsigned long：カードへのハンドル
		：SENDCOMM SendComm：カードへ送信するコマンド
	作成日：2017.10.10
	作成者：K.Asada*/
	unsigned char** Transmit(unsigned long hContext, unsigned long hCard, CONSTANTS::SENDCOMM SendComm[],unsigned long ActiveProtocol) {
		unsigned char RecvBuf[PCSC_RECV_BUFF_LEN] = { '\0' };
		unsigned char* RetBuf[16] = { '\0' };
		unsigned long ResponseSize = 0;
		unsigned long lResult;
		//全てのコマンドを送信するまで繰り返す
		for (int i = 0; SendComm[i].sendLength > -1; i++) {
			//受信の最大サイズを取得する
			ResponseSize = sizeof(RecvBuf);
			//コマンドを送信して、結果とレスポンスへのポインタを取得する
			lResult = ::SCardTransmit(hCard, CardProtocol2PCI(ActiveProtocol), SendComm[i].sendCommand, SendComm[i].sendLength, NULL, RecvBuf, &ResponseSize);
			//コマンドの送信に失敗したらエラーを投げる（ここではコマンドが送れたかどうかのみ判定）
			if (lResult != SCARD_S_SUCCESS) {
				//例外を投げる
				throw gcnew System::Exception("Error");
				//リーダーとの通信、カードとの通信を終了する
				EndConnect(hContext, hCard);
			}
			//受け取ったすべてのレスポンスを格納する（後ろ2文字は送信正否の判定なので格納しないのため）
			for (int j = 0; j < ResponseSize - 2; j++) {
				//受け取ったレスポンスを返却用の文字列に格納する
				RetBuf[i][j] = RecvBuf[j];
			}
		}
		//作成した文字列を返却する
		return RetBuf;
	}

	/*概要:カードリーダの状態を取得し、カードが置かれたときにカードを読み込む関数
	引数:unsigned long hContext:確保したリソースマネージャのアドレス
	    :unsigned long *hCard:カードへのポインタ
	戻り値:unsigned long ActiveProtocol:開通したプロトコル
	作成日:2017.10.10
	作成者:K.Asada*/
	unsigned long CardConnect(unsigned long hContext, unsigned long *hCard) {
		unsigned long lResult = 0;        //接続結果を格納するための変数
		SCARD_READERSTATE readerstate;    //リーダの状態を格納するための構造体
		unsigned long ActiveProtocol = 0; //プロトコル
		//リーダーの状態が変化（カードがかざされたときに）その状態を読み取る関数
		lResult = ::SCardGetStatusChange(hContext, 0, &readerstate, 1);
		//もしコマンドの送信に失敗したら例外を投げる
		if (lResult != SCARD_S_SUCCESS) {
			//エラー内容により分岐
			if (lResult == SCARD_E_NO_READERS_AVAILABLE) {
				//カードリーダが接続されていない旨の例外を投げる
				//throw gcnew System::Exception("カードリーダーが接続されていません");
				//接続を終了する
				EndConnect(hContext, *hCard);
			}
		}
		//カードとの接続を開始する
		lResult = ::SCardConnect(hContext, (LPWSTR)constants->PASORI_NAME, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, (LPSCARDHANDLE)&hCard, &ActiveProtocol);
		//接続結果が失敗なら例外を投げる
		if (lResult != SCARD_S_SUCCESS) {
			//カードがないことのエラーなら
			if (lResult == SCARD_W_REMOVED_CARD) {
				//カードがない旨を伝えるエラーを投げる
				throw gcnew System::Exception("カードがありません");
			}//それ以外のエラーの時は別の例外を伝える
			else {
				throw gcnew System::Exception("ERROR");
			}
			//接続を終了する
			EndConnect(hContext, *hCard);
		}
		return ActiveProtocol;
	}

	/*概要:リーダーと接続し、カード受付待ち状態にする関数
	引数:なし
	戻り値:__int64:Context:確保したリソースマネージャのアドレス
	作成日:2017.10.10
	作成者:K.Asada*/
	unsigned long WaitingCard() {
		unsigned long Context = 0;    //確保したリソースマネージャのアドレスを格納する変数
		//リソースマネージャを確保する
		Context = EstablishContext();
		//リーダーの名前を照合し、目的のものと接続できているかを確認する
		CheckReaderName(Context);
		//確保しリソースマネージャを返却する
		return Context;
	}

	/*概要:カードおよびリーダーとの接続を終了する関数
	引数:unsigned long hContext:確保していたリソースマネージャ
	:unsigned long hCard:接続していたカード
	戻り値:なし
	作成日:2017.10.10
	作成者:K.Asada*/
	void EndConnect(unsigned long hContext, unsigned long hCard) {
		//カードとの接続を終了する
		::SCardDisconnect(hCard, SCARD_LEAVE_CARD);
		//リーダーを解放する
		::SCardFreeMemory(hContext, constants->PASORI_NAME);
		//リソースマネージャを解放する
		::SCardReleaseContext(hContext);
		return;
	}

	/*概要:リーダーとの接続を終了する関数
	引数:unsigned long hContext:確保していたリソースマネージャ
	戻り値:なし
	作成日：2017.10.10
	作成者：K.Asada*/
	void EndConnect(unsigned long hContext) {
		//リーダーを解放する
		::SCardFreeMemory(hContext, constants->PASORI_NAME);
		//リソースマネージャを解放する
		::SCardReleaseContext(hContext);
		return;
	}
};
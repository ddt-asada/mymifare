#pragma once

#include <windows.h>
#include <winscard.h>
#include <stdio.h>
#include <assert.h>
#include "CONSTANTS.h"

#pragma comment (lib, "winscard.lib")

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

	/*概要：機器との通信を行うためのリソースマネージャを確保するための関数
	引数：なし222222222222
	戻り値：SCARDCONTEXT hContext確保したリソースマネージャ
	作成日：2017.10.10
	作成者：K.Asada*/
	SCARDCONTEXT EstablishContext() {
		SCARDCONTEXT hContext = 0;        //確保したリソースマネージャのアドレス
		LONG lResult;                     //リソースマネージャを確保した際の結果を格納するための変数
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
	引数：SCARDCONTEXT Context：確保したリソースマネージャ
	戻り値；なし
	作成日：2017.10.10
	作成者：K.Asada*/
	void CheckReaderName(SCARDCONTEXT Context) {
//		std::cout >> constants->PASORI_NAME.c_str();
		LPTSTR ReaderName = NULL;                      //取得したリーダの名前を格納するための文字列
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //アロケータ
		LONG lResult;                                 //名前を正しく取得できたかの判定を格納するための文字列
		//確保したリソースマネージャのリーダの名前調べる
		lResult = ::SCardListReaders(Context, NULL, (LPTSTR)&ReaderName, &dwAutoAllocate);
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
//		if (ReaderName != constants->PASORI_NAME) {
			//リーダーが違う旨を例外として投げる
		//	throw gcnew System::Exception(NO_READERS_ERROR);
	//		EndConnect(Context);
//		}
		//カード、リーダーとの接続を終了する
		return;
	}

	/*概要：カードへデータ送受信などのコマンドを送信するための関数
	引数：SCARDCONTEXT：リーダーへのリソースマネージャ
		：SCARDHANDLE：カードへのハンドル
		：SENDCOMM SendComm：カードへ送信するコマンド
	作成日：2017.10.10
	作成者：K.Asada*/
		std::vector<std::vector<unsigned char>> Transmit(std::vector<CONSTANTGROUP::SENDCOMM> SendComm) {
		LONG lResult = 0;        //接続結果を格納するための変数
		SCARD_READERSTATE readerstate;    //リーダの状態を格納するための構造体
		SCARDHANDLE card = NULL;
		SCARDCONTEXT hContext = EstablishContext();
		DWORD ActiveProtocol = 0; //プロトコル
		LPTSTR ReaderName = NULL;                      //取得したリーダの名前を格納するための文字列
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //アロケータ
													  //	LONG lResult;                                 //名前を正しく取得できたかの判定を格納するための文字列
													  //確保したリソースマネージャのリーダの名前調べる
		lResult = ::SCardListReaders(hContext, NULL, (LPTSTR)&ReaderName, &dwAutoAllocate);
		/*		//リーダーの状態が変化（カードがかざされたときに）その状態を読み取る関数
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
		}*/
		//カードとの接続を開始する
		lResult = ::SCardConnect(hContext, ReaderName, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &card, &ActiveProtocol);
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
			//		EndConnect(hContext, *hCard);
		}
		unsigned char RecvBuf[PCSC_RECV_BUFF_LEN] = { '\0' };
		std::vector<std::vector<unsigned char>> RetBuf = { {'\0'} };
		unsigned long ResponseSize = 0;
		//unsigned long lResult;
		//全てのコマンドを送信するまで繰り返す
		for (int i = 0; SendComm[i].sendLength > -1; i++) {
			//受信の最大サイズを取得する
			ResponseSize = sizeof(RecvBuf);
			//コマンドを送信して、結果とレスポンスへのポインタを取得する
			lResult = ::SCardTransmit(card, CardProtocol2PCI(ActiveProtocol), SendComm[i].sendCommand, SendComm[i].sendLength, NULL, RecvBuf, &ResponseSize);
			//コマンドの送信に失敗したらエラーを投げる（ここではコマンドが送れたかどうかのみ判定）
			if (lResult != SCARD_S_SUCCESS) {
				//例外を投げる
				throw gcnew System::Exception("Error");
				//リーダーとの通信、カードとの通信を終了する
				EndConnect(hContext, card);
			}
			for (UINT uiRespIdx = 0; uiRespIdx < ResponseSize; uiRespIdx++) {
				_ftprintf_s(stdout, _T("%02X"), RecvBuf[uiRespIdx]);
				if ((uiRespIdx + 1) >= ResponseSize) {
					_ftprintf_s(stdout, _T("\n"));
				}
				else {
					_ftprintf_s(stdout, _T(" "));
				}
			}
			//受け取ったすべてのレスポンスを格納する（後ろ2文字は送信正否の判定なので格納しないのため）
/*			for (int j = 0; j < ResponseSize - 2; j++) {
				//受け取ったレスポンスを返却用の文字列に格納する
				RetBuf[i].push_back(RecvBuf[j]);
			}
			_ftprintf_s(stdout, _T("%02X"), RecvBuf[ResponseSize -2]);
			_ftprintf_s(stdout, _T("%02X"), RecvBuf[ResponseSize - 1]);*/
		}
		//作成した文字列を返却する
		return RetBuf;
	}

	/*概要:カードリーダの状態を取得し、カードが置かれたときにカードを読み込む関数
	引数:SCARDCONTEXT hContext:確保したリソースマネージャのアドレス
	    :SCARDHANDLE *hCard:カードへのポインタ
	戻り値:DWORD ActiveProtocol:開通したプロトコル
	作成日:2017.10.10
	作成者:K.Asada*/
	unsigned long CardConnect(SCARDCONTEXT hContext, SCARDHANDLE hCard) {
		LONG lResult = 0;        //接続結果を格納するための変数
		SCARD_READERSTATE readerstate;    //リーダの状態を格納するための構造体
		SCARDHANDLE card = NULL;
		DWORD ActiveProtocol = 0; //プロトコル
		LPTSTR ReaderName = NULL;                      //取得したリーダの名前を格納するための文字列
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //アロケータ
	//	LONG lResult;                                 //名前を正しく取得できたかの判定を格納するための文字列
													  //確保したリソースマネージャのリーダの名前調べる
		lResult = ::SCardListReaders(hContext, NULL, (LPTSTR)&ReaderName, &dwAutoAllocate);
/*		//リーダーの状態が変化（カードがかざされたときに）その状態を読み取る関数
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
		}*/
		//カードとの接続を開始する
		lResult = ::SCardConnect(hContext, ReaderName, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &ActiveProtocol);
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
	//		EndConnect(hContext, *hCard);
		}
		return ActiveProtocol;
	}

	/*概要:リーダーと接続し、カード受付待ち状態にする関数
	引数:なし
	戻り値:SCARDCONTEXT:Context:確保したリソースマネージャのアドレス
	作成日:2017.10.10
	作成者:K.Asada*/
	SCARDCONTEXT WaitingCard() {
		SCARDCONTEXT Context = 0;    //確保したリソースマネージャのアドレスを格納する変数
		//リソースマネージャを確保する
		Context = EstablishContext();
		//リーダーの名前を照合し、目的のものと接続できているかを確認する
		CheckReaderName(Context);
		//確保しリソースマネージャを返却する
		return Context;
	}

	/*概要:カードおよびリーダーとの接続を終了する関数
	引数:SCARDCONTEXT hContext:確保していたリソースマネージャ
	:SCARDHANDLE hCard:接続していたカード
	戻り値:なし
	作成日:2017.10.10
	作成者:K.Asada*/
	void EndConnect(SCARDCONTEXT hContext, SCARDHANDLE hCard) {
		//カードとの接続を終了する
		::SCardDisconnect(hCard, SCARD_LEAVE_CARD);
		//リーダーを解放する
		::SCardFreeMemory(hContext, CONSTANTGROUP::PASORI_NAME);
		//リソースマネージャを解放する
		::SCardReleaseContext(hContext);
		return;
	}

	/*概要:リーダーとの接続を終了する関数
	引数:SCARDCONTEXT hContext:確保していたリソースマネージャ
	戻り値:なし
	作成日：2017.10.10
	作成者：K.Asada*/
	void EndConnect(SCARDCONTEXT hContext) {
		//リーダーを解放する
		::SCardFreeMemory(hContext, CONSTANTGROUP::PASORI_NAME);
		//リソースマネージャを解放する
		::SCardReleaseContext(hContext);
		return;
	}
};
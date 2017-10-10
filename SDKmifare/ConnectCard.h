#pragma once

#include <windows.h>
#include <winscard.h>
#include <stdio.h>
#include <assert.h>

#define PCSC_TRANS_BUFF_LEN	(262)
#define PCSC_RECV_BUFF_LEN	(262)

typedef struct {
	int           sendLength;
	unsigned char bCommand[PCSC_TRANS_BUFF_LEN];
} SENDCOMM;

public class ConnectCard {
	ConnectCard() {

	}

	/*概要：機器との通信を行うためのリソースマネージャを確保するための関数
	引数：なし
	戻り値：unsigned long hContext確保したリソースマネージャ
	作成日：2017.10.10
	作成者：K.Asada*/
	unsigned long EstablishContext() {
		SCARDCONTEXT hContext = 0;        //確保したリソースマネージャのアドレス
		LONG lResult;                     //リソースマネージャを確保した際の結果を格納するための変数
		//リソースマネージャを確保し、その結果を取得する
		lResult = ::SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hContext);
		//もし確保に失敗していたら例外を投げる
		if (lResult != SCARD_S_SUCCESS) {
			//エラー内容により分岐
			if (lResult == SCARD_E_NO_SERVICE) {
				//リソースマネージャの確保に失敗した時のエラーを投げる
				throw gcnew System::Exception(NO_SERVICE_ERROR);
			}
			//それ以外の時はその他エラー
			else {
				//その他のエラーとして例外を投げる
				throw gcnew System::Exception(ESTABLISH_ERROR);
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
	void CheckReaderName(unsigned long Context) {
		LRSTR ReaderName = NULL;                      //取得したリーダの名前を格納するための文字列
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //アロケータ
		LONG lResult;                                 //名前を正しく取得できたかの判定を格納するための文字列
		//確保したリソースマネージャのリーダの名前調べる
		lResult = ::SCardListReaders(Context, NULL, (LRSTR)&ReaderName, &dwAutoAllocate);
		//失敗したら例外を投げる
		if (lResult != SCARD_S_SUCCESS) {
			//目的のリーダーと違っていたらその旨を例外として投げる
			if (lResult == SCARD_E_NO_READERS_AVAILABLE) {
				//リーダーが違う旨の例外を投げる
				throw gcnew System::Exception(NO_READERS_ERROR);
			}//それ以外のエラーは別のメッセージを投げる
			else {
				//何らかのエラーが発生して処理を中断した旨を例外として投げる
				throw gcnew System::Exception(ERROR);
			}
		}
		//目的のリーダーの名前と違っていたらその旨を例外として伝える
		if (_tcsnmp(pszExpectesReaderName, lpszReaderName, _tcslen(pszExceptedReaderName)) != 0) {
			//リーダーが違う旨を例外として投げる
			throw gcnew System::Exception(NO_READERS_ERROR);
		}
		//カード、リーダーとの接続を終了する
		EndConnect(Context, Card);
		return;
	}

	/*概要：カードへデータ送受信などのコマンドを送信するための関数
	引数：unsigned long：リーダーへのリソースマネージャ
		：unsigned long：カードへのハンドル
		：SENDCOMM SendComm：カードへ送信するコマンド
	作成日：2017.10.10
	作成者：K.Asada*/
	unsigned char Transmit(unsigned long hContext, unsigned long hCard, SENDCOMM SendComm) {
		BYTE RecvBuf[3 + BLOCK_COUNT][PCSC_RECV_BUFF_LEN] = { '\0' };
		DWORD ResponseSize = 0;
		//全てのコマンドを送信するまで繰り返す
		for (int i = 0; SendComm[i].sendLength > -1; i++) {
			//受信の最大サイズを取得する
			ResponseSize = sizeof(RecvBuf);
			//コマンドを送信して、結果とレスポンスへのポインタを取得する
			lResult = ::SCardTransmit(hCard, CatdProtocol2PCI(dwActiveProtocol), SendComm[i].bCommand, SendComm[i].sendLength, NULL, RecvBuf, &ResponseSize);
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
				RecvBuf[i][j] = RecvBuf[j];
			}
		}
		//作成した文字列を返却する
		return RecvBuf;
	}
};
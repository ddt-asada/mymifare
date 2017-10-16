#pragma once

#include <windows.h>
#include <winscard.h>
#include <stdio.h>
#include <assert.h>
#include <msclr/gcroot.h>
#include "CONSTANTS.h"

#pragma comment (lib, "winscard.lib")

#define PCSC_TRANS_BUFF_LEN	(262)
#define PCSC_RECV_BUFF_LEN	(262)

using namespace CONSTANTGROUP;

static LPTSTR PASORI_NAME = _T("Sony FeliCa Port/PaSoRi 3.0 0");

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

	msclr::gcroot<CONSTANTGROUP::ConstantString^> Constants = gcnew CONSTANTGROUP::ConstantString();

	/*概要：機器との通信を行うためのリソースマネージャを確保するための関数
	引数：なし
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
				throw gcnew System::Exception(Constants->NO_SERVICE_ERROR);
			}
			//それ以外の時はその他エラー
			else {
				//その他のエラーとして例外を投げる
				throw gcnew System::Exception(Constants->ERROR_MESSAGE);
			}
		}
		//確保したリソースマネージャのアドレスを返す
		return hContext;
	}

	/*概要：カードへデータ送受信などのコマンドを送信するための関数
	引数：SCARDCONTEXT：リーダーへのリソースマネージャ
		：SCARDHANDLE：カードへのハンドル
		：SENDCOMM SendComm：カードへ送信するコマンド
	作成日：2017.10.10
	作成者：K.Asada*/
		std::vector<std::vector<unsigned char>> Transmit(SCARDCONTEXT hContext, SCARDHANDLE hCard, DWORD ActiveProtocol, std::vector<CONSTANTGROUP::SENDCOMM> SendComm) {
		LONG lResult = 0;        //接続結果を格納するための変数
		SCARD_READERSTATE readerstate;    //リーダの状態を格納するための構造体
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //アロケータ
		unsigned char RecvBuf[PCSC_RECV_BUFF_LEN] = { '\0' };
		std::vector<std::vector<unsigned char>> RetBuf = { {'\0'} };
		unsigned long ResponseSize = 0;
		//unsigned long lResult;
		//全てのコマンドを送信するまで繰り返す
		for (int i = 0; SendComm[i].sendLength > -1; i++) {
			//受信の最大サイズを取得する
			ResponseSize = sizeof(RecvBuf);
			//コマンドを送信して、結果とレスポンスへのポインタを取得する
			lResult = ::SCardTransmit(hCard, CardProtocol2PCI(ActiveProtocol), SendComm[i].sendCommand, SendComm[i].sendLength, NULL, RecvBuf, &ResponseSize);
			//コマンドの送信に失敗したらエラーを投げる（ここではコマンドが送れたかどうかのみ判定）
			if (lResult != SCARD_S_SUCCESS) {
				//例外を投げる
				throw gcnew System::Exception(Constants->ERROR_MESSAGE);
				//リーダーとの通信、カードとの通信を終了する
				EndConnect(hContext, hCard);
			}
			for (UINT RespIdx = 0; RespIdx < ResponseSize; RespIdx++) {
				//受信データの末尾二つのデータは通信正否の判定なので読み飛ばす
				if (RespIdx < ResponseSize - 2) {
					//受信したデータを返却用の配列に格納する
					RetBuf[i].push_back(RecvBuf[RespIdx]);
				}
				//末尾二つのデータをコンソールに表示する
				else {
					//コマンドの送信結果がどうなったかを表示する
					_ftprintf_s(stdout, _T("%02X"), RecvBuf[RespIdx]);
				}
			}
		}
		//作成した文字列を返却する
		return RetBuf;
	}

	/*概要:カードリーダの状態を取得し、カードが置かれたときにカードを読み込む関数
	引数:SCARDCONTEXT hContext:確保したリソースマネージャのアドレス
	    :SCARDHANDLE hCard:カードへのポインタ
	戻り値:DWORD ActiveProtocol:開通したプロトコル
	作成日:2017.10.10
	作成者:K.Asada*/
	unsigned long CardConnect(SCARDCONTEXT hContext, SCARDHANDLE &hCard) {
		LONG lResult = 0;        //接続結果を格納するための変数
		SCARD_READERSTATE readerstate;    //リーダの状態を格納するための構造体
		DWORD ActiveProtocol = 0; //プロトコル
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //アロケータ
		//カードとの接続を開始する
		lResult = ::SCardConnect(hContext, PASORI_NAME, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &ActiveProtocol);
		//接続結果が失敗なら例外を投げる
		if (lResult != SCARD_S_SUCCESS) {
			//カードがないことのエラーなら
			if (lResult == SCARD_W_REMOVED_CARD) {
				//カードがない旨を伝えるエラーを投げる
				throw gcnew System::Exception(Constants->REMOVE_ERROR);
			}//それ以外のエラーの時は別の例外を伝える
			else {
				throw gcnew System::Exception(Constants->ERROR_MESSAGE);
			}
			//接続を終了する
			EndConnect(hContext, hCard);
		}
		//確保したプロトコルを返却する
		return ActiveProtocol;
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
		::SCardFreeMemory(hContext, PASORI_NAME);
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
		::SCardFreeMemory(hContext, PASORI_NAME);
		//リソースマネージャを解放する
		::SCardReleaseContext(hContext);
		return;
	}

	/*概要:リーダーとの通信の入り口となる関数
	引数:std::vector<SENDCOMM> sendcomm:リーダーへ送信するコマンド
	戻り値:std::vector<std::vector<unsigned char>> recvdata:カードから受信したデータ
	作成日:2017.10.16
	作成者:K.Asadaa*/
	std::vector<std::vector<unsigned char>> LinkCard(std::vector<SENDCOMM> sendcomm) {
		SCARDCONTEXT hContext = 0;        //確保したリソースマネージャのアドレス
		SCARDHANDLE hCard = 0;            //カードへのアドレス
		DWORD ActiveProtocol = 0;         //稼働中のプロトコル
		std::vector<std::vector<unsigned char>> recvdata;    //受信したデータを格納する配列
		//リソースマネージャの確保を行う
		hContext = EstablishContext();
		//カードとの接続、プロトコルの確保を行う
		ActiveProtocol = CardConnect(hContext, hCard);
		//カードへコマンドの送信を行う
		recvdata = Transmit(hContext, hCard, ActiveProtocol, sendcomm);
		//全ての接続を終了する
		EndConnect(hContext, hCard);
		//カードから取得したデータを返却する
		return recvdata;
	}
};
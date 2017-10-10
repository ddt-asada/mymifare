#pragma once

#define PCSC_TRANS_BUFF_LEN	(262)

/*概要:定数クラス
作成日:2017.10.10
作成者:K.Asada*/

public class CONSTANTS {
public:
	//デフォルトコンストラクタ
	CONSTANTS() {
	}

	//送信コマンド用構造体
	typedef struct send{
		int           sendLength;
		unsigned char sendCommand[PCSC_TRANS_BUFF_LEN];
	} SENDCOMM;
	
	//書き込みの始点となるブロック
	const int BEGIN_BLOCK = 8;
	//書き込みの終点となるブロック
	const int END_BLOCK = 26;
	//書き込むブロックの数
	const int BLOCK_COUNT = END_BLOCK - BEGIN_BLOCK;
	//キー認証コマンド、コマンド送信時の最初に行わなければならない(詳細はリファレンス参照)
	//Load Key Mifare Default Key(FFFFFFFFFFFF)
	SENDCOMM LOADKEY = { 11,{0xFF,0x82,0x00,0x00,0x06,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF} };
	//セクター認証コマンド、各セクターにアクセスする前に行わなければならない(詳細はリファレンス参照)
	// General Authenticate
	SENDCOMM AUTHENTICATE = { 10,{0xFF,0x86,0x00,0x00,0x05,0x01,0x00,BEGIN_BLOCK,0x60,0x00} };
	//データ受信コマンド、カードのデータを受信する際に使用(詳細はリファレンス参照)
	//ReadBinary
	SENDCOMM READCARD = { 5,{0xFF,0xB0,0x00,BEGIN_BLOCK,0x00} };
	//データ送信コマンド、カードにデータを送信する際に使用(詳細はリファレンス参照)
	//UpdateBinary
	SENDCOMM SENDCARD = { 21,{0xFF,0xD6,0x00,BEGIN_BLOCK,0x00} };
	//ユーザー名が格納されているブロック番号
	const int NAME_INDEX = 0;
	//ユーザーフリガナが格納されているブロック番号
	const int KANA_INDEX = 1;
	//ユーザーIDが格納されているブロック番号
	const int UID_INDEX = 2;
	//パスワードが格納されているブロック番号
	const int PASS_INDEX = 2;
	//属性が格納されているブロック番号
	const int ELEM_INDEX = 2;
	//権限が格納されているブロック番号
	const int ADM_INDEX = 2;
	//住所が格納されているブロック番号
	const int ADRESS_1_INDEX = 3;
	//住所が格納されているブロック番号
	const int ADRESS_2_INDEX = 4;
	//住所が格納されているブロック番号
	const int ADRESS_3_INDEX = 5;
	//住所が格納されているブロック番号
	const int ADRESS_4_INDEX = 6;
	//住所が格納されているブロック番号
	const int ADRESS_5_INDEX = 7;
	//年月が格納されているブロック番号
	const int YEAR_INDEX = 8;
	//入退館日が格納されているブロック番号
	const int TIMES_1_INDEX = 9;
	//入退館日が格納されているブロック番号
	const int TIMES_2_INDEX = 10;
	//入退館日が格納されているブロック番号
	const int TIMES_3_INDEX = 11;
	//入退館日が格納されているブロック番号
	const int TIMES_4_INDEX = 12;
	//入退館日が格納されているブロック番号
	const int TIMES_5_INDEX = 13;
	//入退館日が格納されているブロック番号
	const int TIMES_6_INDEX = 14;
	//カードリーダの名前
	const char* PASORI_NAME = "Sony FeliCa Port / PaSoRi 3.0";
	//リソースマネージャの確保に失敗した時に表示するエラーメッセージ
//	System::String^ NO_SERVICE_ERROR = "SCardシステムでエラーが発生";
};
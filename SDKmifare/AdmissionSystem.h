#pragma once

#include <iostream>
#include "ConnectCard.h"
#include "CONSTANTS.h"

public class AdmissionSystem {
public:
	AdmissionSystem() {

	}

	CONSTANTS* constants;    //定数クラスをインスタンス化

	/*概要:対象のユーザーのデータが存在しているかを確認するための関数
	引数:unsigned data:カードより取得した全データ
	戻り値:string uid:カードより取得したユーザーID
	作成日：2017.10.10
	作成者:K.Asada*/
	std::string CheckUser(unsigned char data) {
	/*	std::string uid = "";        //カードより取得したユーザーIDを格納するための文字列
		std::string name = "";       //カードより取得したユーザー名を格納するための文字列
		std::string pass = "";       //カードより取得したユーザーのパスワードを格納するための文字列
		//ユーザーIDが格納されたブロックを指定してユーザーIDを取得する
		uid = GetData(data, ID_INDEX);
		//ユーザーIDをファイル名としたファイルが開けないときはユーザーが存在していないとして例外を投げる
		if (!ifstream file(uid)) {
			//対象のユーザーが存在していない旨を例外として投げる
			throw gcnew System::Exception("対象のIDが存在していません");
		}//それ以外の時はパスワードの判定に移る
		else {
			//ユーザー名のブロックを指定してユーザー名を取得する
			name = GetData(data, NAME_INDEX);
			//パスワードのブロックを指定してパスワードを取得する
			pass = GetData(data, PASS_INDEX);
			//パスワードの判定に移る
			CheckPass(name, pass, file);
		}
		//判定が終わったらユーザーIDを返却する
		return uid;*/
	}

	/*概要:対象のユーザーのパスワードを確認し、正しいかを判定するための関数
	引数:string name:ユーザーの名前
	    :string pass:ユーザーが入力したパスワード
		:ifstream file:ユーザの情報が格納されたファイルへのストリーム
	戻り値:bool:照合結果の正否
	作成日:2017.10.10
	作成者:K.Asada*/
	bool CheckPass(std::string name, std::string pass, std::ifstream file) {
		std::string getname = "";        //ファイルより取得した名前を格納するための文字列
		std::string getpass = "";        //ファイルより取得したパスを格納するための文字列
		//ストリームより名前を取得する
		file >> getname;
		//ストリームよりパスを取得する
		file >> getpass;
		//名前が違ったら例外を投げる
		if (getname != name) {
			//名前が違う旨の例外を投げる
			throw gcnew System::Exception("ユーザー名が不正です。");
		}
		//パスが違ったら例外を投げる
		if (getpass != pass) {
			//パスが違う旨の例外を投げる
			throw gcnew System::Exception("パスワードが不正です。");
		}
		//ここまで来たら成功したとしてtrueを返却
		return true;
	}

	/*概要：カードより取得したunsigned charより文字列を取得するための関数
	引数:unsigned char data:カードより取得した変数
	    :int index:取得対象の文字列が存在するブロック
	戻り値:string datastring:取得した文字列
	作成日:2017.10.10
	作成者:K.Asada*/
	std::string GetData(unsigned char data, int index) {
/*		std::string datastring = "";    //取得した文字列を格納するための文字列
		//対象のブロックからすべての文字列を取得するまで繰り返す
		for (int i = 0; i < data[index].length, i++) {
			//1文字ずつ文字列を取得して格納していく
			datastring += data[index][i];
		}
		//取得した文字列を返却する
		return datasting;*/
	}
	
	/*概要:カードへ送信するデータの組み立て、コマンドの作成を行う関数
	引数:string setdata:送信するデータ
	戻り値:unsigned char:データを送信するためのコマンド
	作成日:2017.10.10
	作成者:K.Asada*/
	unsigned char ReadySetData(std::string) {
/*		//送信コマンドの初期化処理に当たる部分
		unsigned char[2 + BLOCK_COUNT] = { {11,{0xFF,0x82,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}},
										  {10,{0xFF,0x86,0x00,0x00,0x05,0x01,0x00,0x04,0x60,0x00}}};
		//全データを送信するための送信コマンドを組み立てていく
		for (int i = 0; i < BLOCK_COUNT; i++) {
			//4の倍数-1のセクターの終端ブロックでキーが格納されているため編集したくないので読み飛ばす
			if (i % 4 == 3) {
				//次のセクターへの認証を行うコマンドをセットする
				senddata[2 + i] = { 10,{0xFF,0x86,0x00,0x00,0x05,0x01,0x00,i + 1,0x60,0x00} };
			}//それ以外の時は通常通りデータを送信するためのコマンドを組み立てていく
			else {
				//文字列からデータを取り出し、コマンドを組み立てていく
				for (int j = 0;; j++) {
					//改行文字にたどり着くまで文字列を格納していく
					if (setdata != '\n') {
						//送信コマンドを組み立てていく
						senddata[2 + i].bCommand[j] = setdata;
					}//改行文字にたどり着いたらコマンドの組み立てを終了して次のブロックに移る
					else {
						//ループを抜ける
						break;
					}
				}
			}
		}
		//送信コマンドの終わりにコマンドの終了を意味するコマンドを格納する
		senddata[2 + BLOCK_COUNT] = { -1, NULL };
		//組み立てた送信コマンドを返却する
		return senddata;*/
	}

	/*概要:カードへデータを送信するための関数
	引数:unsigned long hContext:取得したリソースマネージャ
	    :unsigned long hCard:取得したカード
		:string uid:取得したカードのユーザーID
	戻り値:なし
	作成日:2017.10.10
	作成者:K.Asada*/
	void SetCardData(unsigned long hContext, unsigned long hCard, std::string uid) {
/*		std::string setdata = "";        //送信するデータを格納するための文字列
		ifstream file(uis);              //送信データが格納されたファイルをユーザーIDより開く
		unsigned char[BLOCK_COUNT] alldata = { '\0' };    //送信コマンドを格納するための文字列
		//送信コマンドを作成する関数を呼び出す
		alldata = ReadySetData(setdata);
		//カードへコマンドを送信する関数を呼び出す
		Transmit(hContext, hCard, alldata);
		//接続を終了する関数を呼び出す
		EndConnect(hContext, hCard);
		return;*/
	}

	/*概要:カードからデータを受信するための関数
	引数:unsigned long hContext:取得したリソースマネージャ
	    :unsigned long hCard:取得したカード
	戻り値:string uid:カードより取得したユーザーID
	作成日:2017.10.10
	作成者:K.Asada*/
	std::string GetCardData(unsigned char hContext, unsigned char hCard,std::string pass, unsigned long ActiveProtocol) {
		ConnectCard* con;
		unsigned char** getdata = { '\0' };    //取得したカードデータを格納するための変数
		//送信コマンドを格納するための変数、初期値としてキー認証及びセクタ認証を格納
		CONSTANTS::SENDCOMM SendComm[21] = {constants->LOADKEY, constants->AUTHENTICATE};
		//送信コマンドを組み立てるためのfor文
		for (int i = 0; i < constants->BLOCK_COUNT; i++) {
			//対象のブロックが4の倍数-1の時はセクタの終端ブロックであり、キー名等の管理用の情報が格納されているため読み飛ばす
			if (i % 4 == 3) {
				//次のセクタへの認証を行う（4ブロックごとにセクタが切り替わるため）
				SendComm[2 + i] = { constants->AUTHENTICATE.sendLength, constants->AUTHENTICATE.sendCommand[7] += (i + 1) };
			}//それ以外の時は通常通り対象のブロックからデータを取得する
			else {
				//データを受信するためのコマンドを格納する
				SendComm[2 + i] = { constants->READCARD.sendLength, constants->READCARD.sendCommand[3] = i+ constants->BLOCK_COUNT };
			}
		}
		//作成した送信コマンドの終わりに送信コマンドの終わりを示すコマンドを格納する
		SendComm[2 + constants->BLOCK_COUNT] = { -1,NULL };
		//データを受信するコマンドを送信してデータを取得する
		getdata = con->Transmit(hContext, hCard, SendComm, ActiveProtocol);
		//取得したデータのユーザ情報を照合し、ユーザIDを取得する
//		uid = CheckUser(getdata);
		//取得したユーザーIDを返却する
		return "aaa";
	}
};
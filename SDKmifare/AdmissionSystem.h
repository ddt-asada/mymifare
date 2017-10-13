#pragma once

#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <bitset>
#include <stdio.h>
#include "ConnectCard.h"
#include "CONSTANTS.h"

public class AdmissionSystem {
public:
	AdmissionSystem() {

	}
	/*概要:対象のユーザーのデータが存在しているかを確認するための関数
	引数:unsigned data:カードより取得した全データ
	戻り値:string uid:カードより取得したユーザーID
	作成日：2017.10.10
	作成者:K.Asada*/
	std::string CheckUser(std::vector<std::vector<unsigned char>> data, std::string pass) {
		std::string uid = "";        //カードより取得したユーザーIDを格納するための文字列
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
		return uid;
	}

	/*概要:対象のユーザーのパスワードを確認し、正しいかを判定するための関数
	引数:string name:ユーザーの名前
	    :string pass:ユーザーが入力したパスワード
		:ifstream file:ユーザの情報が格納されたファイルへのストリーム
	戻り値:bool:照合結果の正否
	作成日:2017.10.10
	作成者:K.Asada*/
	bool CheckPass(std::string name, std::string pass) {
		/*std::string getname = "";        //ファイルより取得した名前を格納するための文字列
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
		return true;*/
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
	CONSTANTGROUP::SENDCOMM ReadySetData(std::string uid, CONSTANTGROUP::SENDCOMM senddataa[]) {
		CONSTANTGROUP::SENDCOMM senddata[22];
		senddata[0] = CONSTANTGROUP::LOADKEY;
		senddata[1] = CONSTANTGROUP::AUTHENTICATE;
		CONSTANTGROUP::SENDCOMM copyauthenticate = CONSTANTGROUP::AUTHENTICATE;    //認証コマンドのコピー
		CONSTANTGROUP::SENDCOMM copysendcard = CONSTANTGROUP::SENDCARD;            //データ送信コマンドのコピー
		char setdata;             //ファイルより取得した文字列を格納する
		int blockindex;           //書き込み対象のブロック
		std::string bitstr;
		std::string setstr = "aaa";       //コマンドへセットする文字列
		std::ifstream ifs(uid);   //カードへ送信するデータが格納されたテキストを開く
		//全データを送信するための送信コマンドを組み立てていく
		for (int i = 0; i < CONSTANTGROUP::BLOCK_COUNT; i++) {
			//書き込み対象のブロック数を取得する
			blockindex = i + CONSTANTGROUP::BEGIN_BLOCK;
			//4の倍数-1はセクターの終端ブロックでキーが格納されているため編集したくないので読み飛ばすための分岐
			if (blockindex % 4 != 3) {
				//送信コマンドの送信先ブロックを書き換える
				copysendcard.sendCommand[3] = i + CONSTANTGROUP::BEGIN_BLOCK;
				//書き込みブロックの後半部分は年月日なので別処理するための分岐
				if (blockindex >= 20) {
					ifs >> bitstr;
					//送信コマンドを組み立てるためのループ
					for (int j = 0; j < 16; j++) {
						//ファイルにデータが存在していれば分岐
						if ((j + 1) * 8 <= bitstr.size() && !ifs.eof()) {
							//テキストから空白文字まで取得する
							setstr = bitstr.substr(j * 8, 8);
							//送信コマンドとして2進数の整数として取得し、charに8格納する
							copysendcard.sendCommand[5 + j] = std::stoi(setstr, nullptr, 2);
						}//データがないときは空文字として0を送信コマンドにセットする
						else {
							copysendcard.sendCommand[5 + j] = 0;
						}
					}
					//組み立てた送信コマンドを格納する
					senddata[2 + i] = copysendcard;
				}
				//16バイト分の送信コマンドを組み立てていく
				for (int j = 0; j < 16; j++) {
					ifs.get(setdata);//ファイルから1バイト分データを取り出す
					//改行文字にたどり着くまたはファイル終端で分岐
					if (!ifs.eof()) {
						if (setdata == '\n') {
							ifs.get(setdata);
						}
						//送信コマンドを書き換えていく
						copysendcard.sendCommand[5 + j] = setdata;
					}//格納する文字列がないときは送信コマンドに空を示す'0'を格納する
					else {
						copysendcard.sendCommand[5 + j] = 0;
					}
				}
				ifs.get(setdata);//ファイルから1バイト分データを取り出す
				//組み立てた送信コマンドを格納する
				senddata[2 + i] = copysendcard;
			}
			else {//読み飛ばすための処理
				//認証コマンドの認証先ブロックを書き換える
				copyauthenticate.sendCommand[7] = (i + 1 + CONSTANTGROUP::BEGIN_BLOCK);
				//次のセクターへの認証を行うコマンドをセットする
				senddata[2 + i] = copyauthenticate;
			}
		}
		//送信コマンドの終わりにコマンドの終了を意味するコマンドを格納する
		senddata[2 + CONSTANTGROUP::BLOCK_COUNT] = { -1, NULL };
		//組み立てた送信コマンドを返却する
		return *senddata;
	}

	/*概要:カードへデータを送信するための関数
	引数:SCARDCONTEXT hContext:取得したリソースマネージャ
	    :SCARDHANDLE hCard:取得したカード
		:string uid:取得したカードのユーザーID
	戻り値:なし
	作成日:2017.10.10
	作成者:K.Asada*/
	void SetCardData(SCARDCONTEXT hContext, SCARDHANDLE hCard, std::string uid) {
		ConnectCard* con = new ConnectCard();    //カード通信クラスをインスタンス化
		CONSTANTGROUP::SENDCOMM senddata[22];    //送信コマンドを格納するための構造体
		//送信コマンドを作成する関数を呼び出す
		ReadySetData(uid, senddata);
		//カードへコマンドを送信する関数を呼び出す
		con->Transmit(senddata);
		//接続を終了する関数を呼び出す
		con->EndConnect(hContext, hCard);
		return;
	}

	/*概要:カードからデータを受信するための関数
	引数:SCARDCONTEXT hContext:取得したリソースマネージャ
	    :SCARDHANDLE hCard:取得したカード
	戻り値:string uid:カードより取得したユーザーID
	作成日:2017.10.10
	作成者:K.Asada*/
	std::string GetCardData(std::string pass) {
		std::vector<CONSTANTGROUP::SENDCOMM>sendcomm;        //受信コマンドを格納するための配列
		std::vector<std::vector<unsigned char>> recvdata = { {'\0'} };    //受信データを格納するための配列
		std::string uid;
		ConnectCard* con = new ConnectCard();                //カードとの通信を行うクラスをインスタンス化
		//受信コマンドを組み立てる関数を呼び出す
		sendcomm = ReadyGetData();
		//受信コマンドをカードへ送信してデータを受け取る
		recvdata = con->Transmit(sendcomm);
		//ユーザー情報を確認する関数を呼び出す
		CheckUser(recvdata, pass);
		//入館時間を取得する関数を呼び出す
		SetAdmissionTimes(uid);
		//入館時間をカードに記録させる
		sendcomm = ReadySetTimes(uid);
		//カードへデータを送信する
		con->Transmit(sendcomm);
		return;
	}

	/*概要:データ受信コマンドを作成するための関数
	作成日:2017.10.12
	作成者:K.Asada*/
	std::vector<CONSTANTGROUP::SENDCOMM> ReadyGetData() {
		CONSTANTGROUP::SENDCOMM authenticate = CONSTANTGROUP::AUTHENTICATE;    //認証キーコマンドのコピーを作る
		CONSTANTGROUP::SENDCOMM readcard = CONSTANTGROUP::READCARD;             //受信コマンドのコピーを作る
		std::vector<CONSTANTGROUP::SENDCOMM> sendcomm;                         //組み立てたコマンドを格納するための配列
		int blockindex = 0;                                                    //認証先ブロックを格納する変数
		//受信コマンドの初期値としてキー認証コマンドをセットする
		sendcomm.push_back(CONSTANTGROUP::LOADKEY);
		//受信コマンドの初期値としてブロック認証コマンドをセットする
		sendcomm.push_back(CONSTANTGROUP::AUTHENTICATE);
		//受信コマンドを組み立てていく
		for (int i = CONSTANTGROUP::BEGIN_BLOCK; i < CONSTANTGROUP::BLOCK_COUNT; i++) {
			//読込先のブロックを取得する
			blockindex = i;
			//読込先がセクターの終端ブロックの場合は読み飛ばす
			if (blockindex % 4 != 3) {
				//読込先ブロックを設定する
				readcard.sendCommand[3] = blockindex;
				//コマンドを組み立てる
				sendcomm.push_back(readcard);
			}//読み飛ばすと同時に次のセクターに入るための準備をする
			else {
				//セクター認証コマンドの認証先を設定する
				authenticate.sendCommand[7] = blockindex + 1;
				//コマンドを組み立てる
				sendcomm.push_back(authenticate);
			}
		}
		//最後にコマンドの終わりを示すコマンドを格納する
		sendcomm.push_back({ -1, NULL });
		//組み立てたコマンドを返す
		return sendcomm;
	}

	/*概要:入退館日の取得及び年月の確認を行う関数
	引数:string uid:チェック対象のユーザのID
	戻り値:なし
	作成日：2017.10.11
	作成者:K.Asada*/
	void SetAdmissionTimes(std::string uid) {
		int times;            //取得した日時分を分に変換したものを格納する
		//年月をチェックする関数を呼び出し、年月が現在年月と異なっていたら書き換える
		CheckYears(uid);
		std::ofstream ofs(uid, std::ios::app);    //データを書き込む対象のファイルを開く
		//関数より現在日時分を取得する
		times = GetAdmissionTime();
		//取得した日時分をファイルへ書き出す
		ofs << std::bitset<16>(times);
		//書き出しを終えたら閉じる
		ofs.close();
		return;
	}

	/*概要:現在日時分を分に変換して取得する関数
	引数:なし
	戻り値:char times:分
	作成日：2017.10.11
	作成者:K.Asada*/
	int GetAdmissionTime() {
		time_t now = time(NULL);          //現在時刻を取得するため
		struct tm *pnow = localtime(&now);//現在時刻を取得するための構造体を宣言
		int times;                       //取得した現在時刻を格納するための変数
		//現在日時分を分に換算して格納する
		times = ((pnow->tm_mday * 24 + pnow->tm_hour) * 60 + pnow->tm_min);
		//取得した時間を返却する
		return times;
	}

	/*概要:ユーザ情報に含まれる年月が古くないかを確認する関数
	引数:string uid:チェック対象のユーザのID
	戻り値:なし
	作成日:2017.10.11
	作成者:K.Asada*/
	void CheckYears(std::string uid) {
		time_t now = time(NULL);          //現在時刻を取得するため
		struct tm *pnow = localtime(&now);//現在時刻を取得するための構造体を宣言
		int years;                       //取得した現在時刻を格納するための変数
		std::vector<std::string> admyear;                     //ファイルから取得した年月を格納するための変数
		std::string tmp;
		//現在年月を取得する
		years = ((pnow->tm_year + 1900) * 12 + pnow->tm_mon + 1);
		//ファイルから年月を取得するためのストリームを開く
		std::ifstream ifs(uid);
		//ファイルから一行ごとにデータをすべて取得する
		for (int i = 0; !ifs.eof(); i++) {
			//1行ずつ取得する
			std::getline(ifs, tmp);
			admyear.push_back(tmp);
		}
		//取得したデータの年月が現在の年月と異なっていれば上書きする
		if (admyear[5] != std::to_string(years)) {
			std::string bit(std::bitset<32>(years).to_string<char, std::char_traits<char>, std::allocator<char> >());
			//対象を上書きする
			admyear[5] = bit;
			//ファイルを更新するために開く
			std::ofstream ofs(uid);
			std::string tmp;
			//一行ずつ書き込んでいく
			for (int i = 0; i < admyear.size(); i++) {
				tmp = admyear[i];
				if (i + 1 == admyear.size()) {
					ofs << tmp;
				}
				else {
					//一行ずつ書き込む
					ofs << tmp + '\n';
				}
			}
		}
		return;
	}

	/*概要:年月日などのbitデータを送信するためのコマンドを作る関数
	作成日:2017.10.12
	作成者:K.Asada*/
	std::vector<CONSTANTGROUP::SENDCOMM> ReadySetTimes(std::string uid) {
		std::vector<CONSTANTGROUP::SENDCOMM> sendtime;
		CONSTANTGROUP::SENDCOMM authenticate = CONSTANTGROUP::AUTHENTICATE;
		CONSTANTGROUP::SENDCOMM sendcard = CONSTANTGROUP::SENDCARD;
		std::string gettime;
		std::string settime;
		int index = -8;
		sendtime.push_back(CONSTANTGROUP::LOADKEY);
		authenticate.sendCommand[7] = CONSTANTGROUP::BIT_BLOCK;
		sendtime.push_back(authenticate);
		std::ifstream ifs(uid);
		getline(ifs, gettime);
		getline(ifs, gettime);
		for (int i = CONSTANTGROUP::BEGIN_BLOCK; i < CONSTANTGROUP::BLOCK_COUNT; i++) {
			if (i % 4 != 3) {
				for (int j = 0; j < 16; j++) {
					settime = gettime.substr(index += 8, 8);
					if (settime != "        ") {
						sendcard.sendCommand[5 + j] = std::stoi(settime, nullptr, 2);
					}
					else {
						sendcard.sendCommand[5 + j] = 0;
					}
					sendcard.sendCommand[3] = i;
					sendtime.push_back(sendcard);
				}
			}
			else {
				authenticate.sendCommand[7] = i + 1;
				sendtime.push_back(authenticate);
			}
		}
		return sendtime;
	}
};
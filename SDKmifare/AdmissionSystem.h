#pragma once

#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <msclr/gcroot.h>
#include "ConnectCard.h"
#include "CONSTANTS.h"

using namespace CONSTANTGROUP;

public class AdmissionSystem {
public:
	AdmissionSystem() {

	}

	msclr::gcroot<ConstantString^> Constants = gcnew ConstantString();

	/*概要:対象のユーザーのデータが存在しているかを確認するための関数
	引数:unsigned data:カードより取得した全データ
	戻り値:string uid:カードより取得したユーザーID
	作成日：2017.10.10
	作成者:K.Asada*/
	std::string CheckUser(std::vector<std::vector<unsigned char>> data, std::string pass) {
		std::string uid = "";        //カードより取得したユーザーIDを格納するための文字列
		//ユーザーIDが格納されたブロックを指定してユーザーIDを取得する
		uid = GetData(data, UID_INDEX, 0, 8);
		//取得したユーザー名でファイルを開く
		std::ifstream ifs(uid);
		//ユーザーIDをファイル名としたファイルが開けないときはユーザーが存在していないとして例外を投げる
		if (!ifs) {
			//対象のユーザーが存在していない旨を例外として投げる
			throw gcnew System::Exception(Constants->ID_NOT_FOUND_ERROR);
		}//それ以外の時はパスワードの判定に移る
		else {
			//パスワードの判定に移る
			CheckPass(data, pass);
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
	bool CheckPass(std::vector<std::vector<unsigned char>> data, std::string pass) {
		std::string getpass = "";        //ファイルより取得したパスを格納するための文字列
		//受信したカードデータより情報を取得する関数を呼び出す
		getpass = GetData(data, PASS_INDEX, 8, 16);
		//パスが違ったら例外を投げる
		if (getpass != pass) {
			//パスワードが違う旨を表示する
			System::Windows::Forms::MessageBox::Show("パスワードが違います");
			//パスが違う旨の例外を投げる
			throw gcnew System::Exception(Constants->PASS_NOT_FOUND_ERROR);
		}
		//ここまで来たら成功したとしてtrueを返却
		return true;
	}

	/*概要：カードより取得したunsigned charより文字列を取得するための関数
	引数:unsigned char data:カードより取得した変数
	    :int index:取得対象の文字列が存在するブロック
		:int endbyte:データより取得する文字列のバイト数
		:int beginbyte:取得するときの始点(1ブロックに複数のデータが含まれている場合に指定)
	戻り値:string datastring:取得した文字列
	作成日:2017.10.10
	作成者:K.Asada*/
	std::string GetData(std::vector<std::vector<unsigned char>> data, int index, int beginbyte = 0, int endbyte = 16) {
		try {
			std::string datastring = "";    //取得した文字列を格納するための文字列
			for (int i = beginbyte; i < endbyte; i++) {
				//対象の文字列を取得する
				datastring += data[index][i];
			}
			//取得した文字列を返却する
			return datastring;
		}
		catch (System::IndexOutOfRangeException^ e) {
			System::Console::WriteLine(e);
		}
	}
	
	/*概要:カードへ送信するデータの組み立て、コマンドの作成を行う関数
	引数:string setdata:送信するデータ
	戻り値:unsigned char:データを送信するためのコマンド
	作成日:2017.10.10
	作成者:K.Asada*/
	std::vector<SENDCOMM> ReadySetData(std::string uid, int blockindex) {
		try {
			std::vector<SENDCOMM> sendcomm;        //組み立てたコマンドを格納するための構造体
			char setdata;                          //コマンドの中に組み込む送信文字列
			SENDCOMM certify = AUTHENTICATE;       //ブロック認証コマンドのコピー
			SENDCOMM sendcard = SENDCARD;          //データ送信コマンドのコピー
			//コマンドを初期化する
			sendcomm = InitCommand(blockindex);
			//カードへ送信するデータが格納されたファイルを開く
			std::ifstream ifs(uid);
			//コマンドを組み立てていく
			for (; blockindex < END_BLOCK; blockindex++) {
				//対象のブロックが4の倍数‐1の時は読み飛ばす
				if (blockindex % 4 != 3) {
					//16バイト分の送信コマンドを組み立てていく
					for (int i = 0; i < 16; i++) {
						//ファイルから1バイト分データを取得する
						ifs.get(setdata);
						//ファイルが末尾に到達していなければコマンドに送信データを格納していく
						if (!ifs.eof()) {
							//送信データとしてコマンドに格納する
							sendcard.sendCommand[5 + i] = setdata;
						}//末尾の時は空データを格納していく
						else {
							//空データを示す0を格納していく
							sendcard.sendCommand[5 + i] = 0;
						}
					}
					//データを送信する対象のブロックを設定する
					sendcard.sendCommand[3] = blockindex;
					//組み立てたコマンドを格納する
					sendcomm.push_back(sendcard);
				}//対象のブロックがセクターの末尾の時は読み飛ばす
				else {
					//読み飛ばすと同時に次のセクターへの認証を行う
					certify.sendCommand[7] = blockindex + 1;
					//送信コマンドに格納する
					sendcomm.push_back(certify);
				}
			}
			//コマンドの終わりを示すコマンドを格納する
			sendcomm.push_back({ -1, NULL });
			//組み立てたコマンドを返却する
			return sendcomm;
		}
		catch (System::IndexOutOfRangeException^ e) {
			System::Console::WriteLine(e);
		}
	}

	/*概要:カードへデータを送信するための関数
	引数:SCARDCONTEXT hContext:取得したリソースマネージャ
	    :SCARDHANDLE hCard:取得したカード
		:string uid:取得したカードのユーザーID
	戻り値:なし
	作成日:2017.10.10
	作成者:K.Asada*/
	void SetCardData(std::string uid) {
		try {
			ConnectCard* con = new ConnectCard();    //カード通信クラスをインスタンス化
			std::vector<SENDCOMM> senddata;    //送信コマンドを格納するための構造体
			//送信コマンドを作成する関数を呼び出す
			senddata = ReadySetData(uid, BEGIN_BLOCK);
			//送信コマンドの終わりにコマンドの終わりを示すコマンドを格納する
			senddata.push_back(ENDCOMMAND);
			//カードへコマンドを送信する関数を呼び出す
			con->LinkCard(senddata);
			return;
		}
		catch (System::IndexOutOfRangeException^ e) {
			System::Console::WriteLine(e);
		}
	}

	/*概要:カードからデータを受信するための関数
	引数:SCARDCONTEXT hContext:取得したリソースマネージャ
	    :SCARDHANDLE hCard:取得したカード
	戻り値:string uid:カードより取得したユーザーID
	作成日:2017.10.10
	作成者:K.Asada*/
	std::vector<std::vector<unsigned char>> GetCardData(std::string pass) {
		try {
			std::vector<SENDCOMM>sendcomm;        //受信コマンドを格納するための配列
			std::vector<SENDCOMM>copycomm;        //送信コマンドを格納するための配列
			std::vector<std::vector<unsigned char>> recvdata;    //受信データを格納するための配列
			std::string uid;                                     //ユーザーIDを格納するための配列
			ConnectCard* con = new ConnectCard();                //カードとの通信を行うクラスをインスタンス化
			//受信コマンドを組み立てる関数を呼び出す
			sendcomm = ReadyGetData(BEGIN_BLOCK);
			//受信コマンドをカードへ送信してデータを受け取る
			recvdata = con->LinkCard(sendcomm);
			//ユーザー情報を確認する関数を呼び出す
			uid = CheckUser(recvdata, pass);
			//入館時間を取得する関数を呼び出す
			SetEnterTimes(uid);
			//入館時間をカードに記録させるためのコマンドを作成する
			copycomm = ReadySetData(uid, BEGIN_BLOCK);
			//コマンドを連結する
			sendcomm.insert(sendcomm.begin(), copycomm.begin(), copycomm.end() - 1);
			//カードへデータを送信する
			recvdata = con->LinkCard(sendcomm);
			return recvdata;
		}
		catch (System::IndexOutOfRangeException^ e) {
			System::Console::WriteLine(e);
		}
	}

	/*概要:データ受信コマンドを作成するための関数
	作成日:2017.10.12
	作成者:K.Asada*/
	std::vector<SENDCOMM> ReadyGetData(int blockindex) {
		try {
			SENDCOMM authenticate = AUTHENTICATE;    //認証キーコマンドのコピーを作る
			SENDCOMM readcard = READCARD;             //受信コマンドのコピーを作る
			std::vector<SENDCOMM> sendcomm;                         //組み立てたコマンドを格納するための配列
			//コマンドの初期化処理を行う
			sendcomm = InitCommand(blockindex);
			//受信コマンドを組み立てていく
			for (; blockindex < END_BLOCK; blockindex++) {
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
		catch (System::IndexOutOfRangeException^ e) {
			System::Console::WriteLine(e);
		}
	}

	/*概要:入退館日の取得及び年月の確認を行う関数
	引数:string uid:チェック対象のユーザのID
	戻り値:なし
	作成日：2017.10.11
	作成者:K.Asada*/
	void SetAdmissionTimes(std::string uid) {
		ITOC times;            //取得した日時分を分に変換したものを格納する
		//年月をチェックする関数を呼び出し、年月が現在年月と異なっていたら書き換える
		CheckYears(uid);
		//関数より現在日時分を取得する
		times.num = GetAdmissionTime();
		//データを書き込む対象のファイルを開く
		std::ofstream ofs(uid, std::ios::app);
		//取得した日時分の上位8ビットをファイルに書き出す
		ofs << times.bytes[1];
		//取得した日時分の下位8ビットをファイルに書き出す
		ofs << times.bytes[0];
		//書き出しを終えたら閉じる
		ofs.close();
		return;
	}

	void SetEnterTimes(std::string uid) {
		ITOC times;
		char getdata[BLOCK_COUNT * 16];
		CheckYears(uid);
		times.num = GetAdmissionTime();
		std::ifstream ifs(uid);
		ifs.get(getdata, BLOCK_COUNT * 16);
		for (int i = TIMES_1_INDEX * 16; i < LEAVE_1_INDEX * 16; i++) {
			if (getdata[i] == ' ') {
				getdata[i] = times.bytes[1];
				getdata[i + 1] = times.bytes[0];
				std::ofstream ofs(uid);
				ofs << getdata;
				ofs.close();
				break;
			}
		}
		ifs.close();
		return;
	}

	void SetLeaveTimes(std::string uid) {
		ITOC times;
		char getdata[BLOCK_COUNT * 16];
		CheckYears(uid);
		times.num = GetAdmissionTime();
		std::ifstream ifs(uid);
		ifs.get(getdata, BLOCK_COUNT * 16);
		for (int i = LEAVE_1_INDEX * 16; i < (LEAVE_4_INDEX + 1) * 16; i++) {
			if (getdata[i] == ' ') {
				getdata[i] = times.bytes[1];
				getdata[i + 1] = times.bytes[0];
				std::ofstream ofs(uid);
				ofs << getdata;
				ofs.close();
				break;
			}
		}
		ifs.close();
		return;
	}

	/*概要:現在日時分を分に変換して取得する関数
	引数:なし
	戻り値:unsigned short int times:分
	作成日：2017.10.11
	作成者:K.Asada*/
	int GetAdmissionTime() {
		time_t now = time(NULL);          //現在時刻を取得するため
		struct tm *pnow = localtime(&now);//現在時刻を取得するための構造体を宣言
		unsigned short int times;                       //取得した現在時刻を格納するための変数
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
		ITOC years;                       //取得した現在時刻を格納するための変数
		char filedata[16 * BLOCK_COUNT] = { '\0' };  //ファイルから取得したデータを格納する変数
		int yearindex = 16 * YEAR_INDEX;             //カードデータの中の年月が格納されている場所
		//現在年月を取得する
		years.num = ((pnow->tm_year + 1900) * 12 + pnow->tm_mon + 1);
		//ファイルから年月を取得するためのストリームを開く
		std::ifstream ifs(uid);
		//ファイルからデータを取得する
		ifs.getline(filedata, 16*BLOCK_COUNT);
		//データから年月情報を取り出し、取得した年月と比較する
		if (years.bytes[1] != filedata[yearindex] || years.bytes[0] != filedata[yearindex + 1]) {
			//ファイルから取得した年月を上書きする
			filedata[yearindex++] = years.bytes[1];
			//年月を上書きする
			filedata[yearindex++] = years.bytes[0];
			//年月の後に格納されている日時分を削除する
			for (int i = yearindex; i < sizeof(filedata); i++) {
				//1バイトずつ'\0'に置き換えていく
				filedata[i] = ' ';
			}
			//書き込み用のファイルストリームを開く
			std::ofstream ofs(uid);
			//上書きしたデータをファイルに書き出す
			ofs << filedata;
			//書き込み用のファイルストリームを閉じる
			ofs.close();
		}
		//開いたファイルストリームを閉じる
		ifs.close();
		return;
	}

	/*概要:コマンドの初期化処理関数
	引数:int beginblock:コマンドを送信して初めにアクセスするブロック
	戻り値:std::vector<SENDCOMM> initcommand:作成したコマンド
	作成日:2017.10.13
	作成者:K.Asada*/
	std::vector<SENDCOMM> InitCommand(int beginblock) {
		std::vector<SENDCOMM> initcommand;    //作成したコマンドを格納するための配列
		SENDCOMM certify = AUTHENTICATE;                                    //ブロック認証コマンド
		//ブロック認証コマンドの認証先ブロックを書き換える
		certify.sendCommand[7] = beginblock;
		//コマンドを組み立てていく
		initcommand.push_back(LOADKEY);
		//認証コマンドを組み立てていく
		initcommand.push_back(certify);
		//組み立てたコマンドを返却する
		return initcommand;
	}
};
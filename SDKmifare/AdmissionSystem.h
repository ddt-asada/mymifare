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
		//ユーザーの属性を取得する
		uid = GetElem(data[ELEM_INDEX][4], ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4);
		//危険人物かどうかを判定する
		if (uid == ELEM_NAME2) {
			//危険人物あることを表示する
			System::Windows::Forms::MessageBox::Show(Constants->CAUNTION_MESSAGE);
			//危険人物であるエラーを投げる
			throw gcnew System::Exception(Constants->CAUNTION_MESSAGE);
		}
		//ユーザーIDが格納されたブロックを指定してユーザーIDを取得する
		uid = GetData(data, UID_INDEX);
		//取得したユーザー名でファイルを開く
		std::ifstream ifs(uid);
		//ユーザーIDをファイル名としたファイルが開けないときはユーザーが存在していないとして例外を投げる
		if (!ifs.is_open()) {
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
		getpass = GetData(data, PASS_INDEX);
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
				//NULLを読み飛ばすための処理
				if (data[index][i] != '\0') {
					//対象の文字列を取得する
					datastring += data[index][i];
				}
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
					if (!ifs.eof()) {
						//ファイルから1バイト分データを取得する
						ifs.get(setdata);
					}
					//16バイト分の送信コマンドを組み立てていく
					for (int i = 0; i < 16; i++) {
						//ファイルが末尾に到達していなければコマンドに送信データを格納していく
						if (setdata != '\n' && !ifs.eof()) {
							//送信データとしてコマンドに格納する
							sendcard.sendCommand[5 + i] = setdata;
							//ファイルから1バイト分データを取得する
							ifs.get(setdata);
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

	/*概要:カードへ送信するデータの組み立て、コマンドの作成を行う関数
	引数:string setdata:送信するデータ
	戻り値:unsigned char:データを送信するためのコマンド
	作成日:2017.10.10
	作成者:K.Asada*/
	std::vector<SENDCOMM> ReadySetData(std::vector<std::vector<unsigned char>> data, int blockindex) {
		try {
			std::vector<SENDCOMM> sendcomm;        //組み立てたコマンドを格納するための構造体
			int dataindex = 0;                     //データを取り出すためのインデックス
			SENDCOMM certify = AUTHENTICATE;       //ブロック認証コマンドのコピー
			SENDCOMM sendcard = SENDCARD;          //データ送信コマンドのコピー
            //コマンドを初期化する
			sendcomm = InitCommand(blockindex);
			//コマンドを組み立てていく
			for (; blockindex < END_BLOCK; blockindex++) {
				//対象のブロックが4の倍数‐1の時は読み飛ばす
				if (blockindex % 4 != 3) {
					//16バイト分の送信コマンドを組み立てていく
					for (int i = 0; i < 16; i++) {
						sendcard.sendCommand[5 + i] = data[dataindex][i];
					}
					//データを送信する対象のブロックを設定する
					sendcard.sendCommand[3] = blockindex;
					//組み立てたコマンドを格納する
					sendcomm.push_back(sendcard);
					//そのブロックのコマンドを組み立て終えたら次のブロックへ移動する
					dataindex++;
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
	void SetCardData(std::string pass) {
		try {
			ConnectCard* con = new ConnectCard();    //カード通信クラスをインスタンス化
			std::vector<SENDCOMM> senddata;    //送信コマンドを格納するための構造体
			std::vector<std::vector<unsigned char>> recvdata;    //受信データを格納するための配列
			std::string uid;
			//受信コマンドを組み立てる関数を呼び出す
			senddata = ReadyGetData(BEGIN_BLOCK);
			//受信コマンドをカードへ送信してデータを受け取る
			recvdata = con->LinkCard(senddata);
			//ユーザー情報を確認する関数を呼び出す
			uid = CheckUser(recvdata, pass);
			//対象のユーザーが入館中かを判定する
			if (!CheckLeave(recvdata)) {
				System::Windows::Forms::MessageBox::Show("このユーザーは入館していません。");
				throw gcnew System::Exception("このユーザは入館していません。");
			}
			//退館日を記録する
			recvdata = SetTimes(recvdata, LEAVE_1_INDEX, END_INDEX);
			//送信コマンドを作成する関数を呼び出す
			senddata = ReadySetData(recvdata, BEGIN_BLOCK);
			//送信コマンドの終わりにコマンドの終わりを示すコマンドを格納する
			senddata.push_back(ENDCOMMAND);
			//カードへコマンドを送信する関数を呼び出す
			con->LinkCard(senddata);
			return;
		}
		catch (System::Exception^ e) {
			System::Console::WriteLine(e);
			throw e;
		}
	}

	/*概要:カードへ新規でデータを送信するための関数
	引数:SCARDCONTEXT hContext:取得したリソースマネージャ
	:SCARDHANDLE hCard:取得したカード
	:string uid:取得したカードのユーザーID
	戻り値:なし
	作成日:2017.10.10
	作成者:K.Asada*/
	void SetNewCardData(std::string uid) {
		try {
			ConnectCard* con = new ConnectCard();    //カード通信クラスをインスタンス化
			std::vector<SENDCOMM> senddata;    //送信コマンドを格納するための構造体
			//データ送信用のコマンドを組み立てる
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
			//このユーザーが入館状態でないか判定する
			if (!CheckEnter(recvdata)) {
				System::Windows::Forms::MessageBox::Show("このユーザーは退館していません。");
				throw gcnew System::Exception("このユーザは退館していません。");
			}
			//入館時間を取得する関数を呼び出す
			recvdata = SetTimes(recvdata, TIMES_1_INDEX, LEAVE_1_INDEX);
			//入館時間をカードに記録させるためのコマンドを作成する
			copycomm = ReadySetData(recvdata, BEGIN_BLOCK);
			//コマンドを連結する
			sendcomm.insert(sendcomm.begin(), copycomm.begin(), copycomm.end() - 1);
			//カードへデータを送信する
			recvdata = con->LinkCard(sendcomm);
			return recvdata;
		}
		catch (System::Exception^ e) {
			System::Console::WriteLine(e);
			throw e;
		}
	}

	/*概要:データ受信コマンドを作成するための関数
	作成日:2017.10.12
	作成者:K.Asada*/
	std::vector<SENDCOMM> ReadyGetData(int blockindex) {
		try {
			SENDCOMM authenticate = AUTHENTICATE;     //認証キーコマンドのコピーを作る
			SENDCOMM readcard = READCARD;             //受信コマンドのコピーを作る
			std::vector<SENDCOMM> sendcomm;           //組み立てたコマンドを格納するための配列
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
	std::vector<std::vector<unsigned char>> SetTimes(std::vector<std::vector<unsigned char>> data, int index, int endindex) {
		ITOC times;            //取得した日時分を分に変換したものを格納する
		//年月をチェックする関数を呼び出し、年月が現在年月と異なっていたら書き換える
		data = CheckYears(data);
		//関数より現在日時分を取得する
		times.num = GetAdmissionTime();
		//対象のデータの走査を行う
		for (int i = 2; index < endindex; i++) {
			//データが存在しない場所があれば移行
			if (data[index][i] == '\0') {
				//上位8ビットを格納する
				data[index][i] = times.bytes[0];
				//下位8ビットを格納する
				data[index][i + 1] = times.bytes[1];
				//走査を終了する
				break;
			}
			//ブロック終端まで走査していたら次のブロックへ移行する
			if (i == 15) {
				//次のブロックへ移行する
				index++;
				//インデックスを最初に戻る
				i = -1;
			}
		}
		return data;
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
	std::vector<std::vector<unsigned char>> CheckYears(std::vector<std::vector<unsigned char>> data) {
		time_t now = time(NULL);          //現在時刻を取得するため
		struct tm *pnow = localtime(&now);//現在時刻を取得するための構造体を宣言
		ITOC years;                       //取得した現在時刻を格納するための変数
		//現在年月を取得する
		years.num = ((pnow->tm_year + 1900) * 12 + pnow->tm_mon + 1);
		//年月が格納されている場所をチェックして取得した年月日と異なれば書き換える
		if (data[YEAR_INDEX][0] != years.bytes[0] || data[YEAR_INDEX][1] != years.bytes[1]) {
			//下位8ビットを書き換える
			data[YEAR_INDEX][0] = years.bytes[0];
			//上位8ビットを書き換える
			data[YEAR_INDEX][1] = years.bytes[1];
		}
		return data;
	}

	/*概要:コマンドの初期化処理関数
	引数:int beginblock:コマンドを送信して初めにアクセスするブロック
	戻り値:std::vector<SENDCOMM> initcommand:作成したコマンド
	作成日:2017.10.13
	作成者:K.Asada*/
	std::vector<SENDCOMM> InitCommand(int beginblock) {
		std::vector<SENDCOMM> initcommand;    //作成したコマンドを格納するための配列
		SENDCOMM certify = AUTHENTICATE;      //ブロック認証コマンド
		//ブロック認証コマンドの認証先ブロックを書き換える
		certify.sendCommand[7] = beginblock;
		//コマンドを組み立てていく
		initcommand.push_back(LOADKEY);
		//認証コマンドを組み立てていく
		initcommand.push_back(certify);
		//組み立てたコマンドを返却する
		return initcommand;
	}

	/*概要:カードに格納された日時分情報を文字列に変換する関数
	引数:std::vector<std::vcotr<unsigned char>> data:カードデータ
	戻り値:std::vector<string> times:日時分を文字列に変換した配列
	作成日:2017.10.16
	作成者:K.Asada*/
 std::vector<std::string> ConvTimes(std::vector<std::vector<unsigned char>> data, int index,int endindex) {
	try {
		std::vector<std::string> times;        //日時分を文字列に変換したものを格納するための配列
		ITOC gettimes;                         //カードデータの中にあるchar型の数値をunsigned int型に変換するための共有体
		int day = 0;                           //取得した日を格納する変数
		int hour = 0;                          //取得した時間を格納する変数
		int min = 0;                           //取得した分を格納する変数
		int timeindex = index;
		//カードデータにある日時分情報を走査していく
		for (int i = 1; timeindex < endindex && data[timeindex][i * 2] != '\0'; i++) {
			//カードデータより日時分の下位8ビットを取得する
			gettimes.bytes[0] = data[timeindex][i * 2];
			//カードデータより日時分の上位8ビットを取得する
			gettimes.bytes[1] = data[timeindex][i * 2 + 1];
			//取得した日時分を日に変換する
			day = gettimes.num / 1440;
			//取得した日時分を時に変換する
			hour = gettimes.num / 60 - day * 24;
			//取得した日時分を分に変換する
			min = gettimes.num - 1440 * day - 60 * hour;
			//変換した日時分を連結して文字列を完成させる
			times.push_back(std::to_string(day) + "日" + std::to_string(hour) + "時" + std::to_string(min) + "分" + '\n');
			if (i == 7) {
				i = -1;
				timeindex++;
			}
		}
		//変換した文字列を返却する
		return times;
	}
	catch (System::IndexOutOfRangeException^ e) {
		System::Console::WriteLine(e);
	}
}

		 /*概要:ユーザーが入館状態かどうかをチェックするための関数
		 引数:std::vector<std::vector<unsigned char>> data:カードより取得したデータ
		 戻り値:bool judge:判定結果
		 作成日:2017.10.19
		 作成者:K.Asada*/
		 bool CheckEnter(std::vector<std::vector<unsigned char>> data) {
			 std::vector<std::string> entertimes;    //入館時間を格納する文字列
			 std::vector<std::string> leavetimes;    //退館時間を格納する文字列
			 bool judge = true;                      //判定結果を格納する
			 //入館時間を取得する
			 entertimes = ConvTimes(data, TIMES_1_INDEX, LEAVE_1_INDEX);
			 //退館時間を取得する
			 leavetimes = ConvTimes(data, LEAVE_1_INDEX, END_INDEX);
			 //入館状態かどうかの判定を行う
			 if (entertimes.size() > leavetimes.size()){
				 //入館状態である判定を返す
				 judge = false;
			 }
			 return judge;
		}

		 /*概要:ユーザーが入館状態かどうかをチェックするための関数
		 引数:std::vector<std::vector<unsigned char>> data:カードより取得したデータ
		 戻り値:bool judge:判定結果
		 作成日:2017.10.19
		 作成者:K.Asada*/
		 bool CheckLeave(std::vector<std::vector<unsigned char>> data) {
			 std::vector<std::string> entertimes;    //入館時間を格納する文字列
			 std::vector<std::string> leavetimes;    //退館時間を格納する文字列
			 bool judge = true;                      //判定結果を格納する
             //入館時間を取得する
			 entertimes = ConvTimes(data, TIMES_1_INDEX, LEAVE_1_INDEX);
			 //退館時間を取得する
			 leavetimes = ConvTimes(data, LEAVE_1_INDEX, END_INDEX);
			 //入館状態かどうかの判定を行う
			 if (entertimes.size() <= leavetimes.size()) {
				 //入館状態である判定を返す
				 judge = false;
			 }
			 return judge;
		 }

		 /*概要:ユーザーの属性を判定し、それに応じた判定を返す関数
		 作成日：2017.10.10
		 作成者：K.Asada*/
		 int CheckBit(char check) {
			 int countbit = 0;    //ビットがたっている場所
		     //対象を走査し何ビット目がたっているかを調べる
			 for (int i = 0; i < 8; i++) {
				 //ビットがたっていたらその場所を変数に格納する
				 if ((check >> i) & 1U) {
					 //ビットがたっている場所を保管する
					 countbit = i + 1;
					 //ループを抜ける
					 break;
				 }
			 }
			 //判定結果を返す
			 return countbit;
		 }

		 /*概要:何ビット目がたっているかに応じた文字列を返す関数
		 引数:string name1:1ビット目がたっているときに返す文字列
		 :string name2:2ビット目がたっているときに返す文字列
		 :string name3:3ビット目がたっているときに返す文字列
		 :string name4:4ビット目がたっているときに返す文字列
		 戻り値:string name:ビット数に応じた文字列
		 作成日:2017.10.17
		 作成者:K.Asada*/
		 std::string GetElem(unsigned char data, std::string name0, std::string name1, std::string name2, std::string name3) {
			 std::string name = "";    //返却用の文字列
			 int checkbit = 0;         //何ビット目がたっていたかを格納する変数
			 //何ビット目がたっているかを調べる
			 checkbit = this->CheckBit(data);
			 //何ビット目がたっていたかによって対応した文字列を返却する
			 switch (checkbit) {
				 //1の時は引数1の文字列を返す
			 case 0:name = name0;
				 break;
				 //2の時は引数2の文字列を返す
			 case 1:name = name1;
				 break;
				 //3の時は引数3の文字列を返す
			 case 2:name = name2;
				 break;
				 //4の時は引数4の文字列を返す
			 case 3:name = name3;
				 break;
			 }
			 //取得した文字列を返却する
			 return name;
		 }
};
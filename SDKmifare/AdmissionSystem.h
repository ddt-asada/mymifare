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

	/*概要:カードへ新規でデータを送信するための関数
	引数:SCARDCONTEXT hContext:取得したリソースマネージャ
	:SCARDHANDLE hCard:取得したカード
	:string uid:取得したカードのユーザーID
	戻り値:なし
	作成日:2017.10.10
	作成者:K.Asada
	更新内容:新仕様実装に伴い関数名、引数を変更
	更新日:2017.10.24
	更新者:K.Asada*/
	void SetCardData(std::string uid, SCARDCONTEXT hContext, SCARDHANDLE hCard, DWORD ActiveProtocol) {
		try {
			ConnectCard* con = new ConnectCard();    //カード通信クラスをインスタンス化
			std::vector<SENDCOMM> senddata;    //送信コマンドを格納するための構造体
			//データ送信用のコマンドを組み立てる
			senddata = ReadySetData(uid, BEGIN_BLOCK);
			//カードへコマンドを送信する関数を呼び出す
			con->Transmit(hContext, hCard, ActiveProtocol, senddata);
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
	作成者:K.Asada
	更新内容:新仕様実装に伴い引数を変更
	更新日:2017.10.24
	更新者:K.Asada*/
	std::vector<std::vector<unsigned char>> GetCardData(SCARDCONTEXT hContext, SCARDHANDLE hCard, DWORD ActiveProtocol) {
		try {
			std::vector<SENDCOMM>sendcomm;        //受信コマンドを格納するための配列
			std::vector<SENDCOMM>copycomm;        //送信コマンドを格納するための配列
			std::vector<std::vector<unsigned char>> recvdata;    //受信データを格納するための配列
			std::string uid;                                     //ユーザーIDを格納するための配列
			ConnectCard* con = new ConnectCard();                //カードとの通信を行うクラスをインスタンス化
																 //受信コマンドを組み立てる関数を呼び出す
			sendcomm = ReadyGetData(BEGIN_BLOCK);
			//受信コマンドをカードへ送信してデータを受け取る
			recvdata = con->Transmit(hContext, hCard, ActiveProtocol, sendcomm);
			return recvdata;
		}
		catch (System::Exception^ e) {
			System::Console::WriteLine(e);
			throw e;
		}
	}

	/*概要:カードデータの入退館日を更新するための関数
	引数:std::vector<std::vector<unsignde char>> data:カードのデータ
	    :SCARDCONTEXT hContext:確保したリソースマネージャのアドレス
		:SCARDHANDLE hCard:カードのアドレス
		:DWORD ActiveProtocol:プロトコル
		:int beginblock:更新対象を取得するための始点となるインデックス
		:int endblock:更新対象を取得するための終点となるインデックス
	戻り値:なし
	作成日:2017.10.24
	作成者:K.Asada*/
	void UpdateCardData(std::vector <std::vector<unsigned char>> data, SCARDCONTEXT hContext, SCARDHANDLE hCard, DWORD ActiveProtocol, int beginindex, int endindex) {
		ConnectCard* con = new ConnectCard();    //カード通信クラスをインスタンス化する
		std::vector<SENDCOMM> sendcomm;    //カードへの送信コマンド
		int *updateblock = 0;              //更新対象のブロック
		int *updateindex = 0;              //更新対象のインデックス
		//更新対象のブロック、インデックスを取得する
		GetLastBlock(data, beginindex, endindex);
		//更新コマンドを組み立てていく
		sendcomm = ReadyUpdateData(data, *updateblock, *updateindex);
		//カードへコマンドを送信する
		con->Transmit(hContext, hCard, ActiveProtocol, sendcomm);
		return;
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
			std::ifstream ifs(uid + ".txt");
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

	/*概要:対象となる日時分を更新するためのコマンドを組み立てる関数
	引数:std::vector<std::vector<unsigned char>> data:カードデータ
	    :int updateblock:更新対象のブロック
		:int updateindex:更新対象んインデックス
	戻り値:std::vector<SENDCOMM> sendcomm:カードデータ更新用のコマンド
	作成日:2017.10.24
	作成者:K.Asada*/
	std::vector<SENDCOMM> ReadyUpdateData(std::vector<std::vector<unsigned char>> data, int updateblock, int updateindex) {
		ITOC currenttime;    //カードに送信する現在日時を変換するための共有体
		std::vector<SENDCOMM> senddata;    //更新用のコマンド
		SENDCOMM copycomm = SENDCARD;      //データ送信コマンドのテンプレート
		//コマンドの初期値を取得する
		senddata = InitCommand(updateblock);
		//現在日時分を取得する
		currenttime.num = GetNowTime();
		//送信コマンドの対象のブロックを設定する
		copycomm.sendCommand[3] = updateblock;
		//1ブロック分の送信コマンドを組み立てていく
		for (int i = 0; i < 16; i++) {
			//更新対象となる場所にたどり着いたら
			if (i == updateindex) {
				//更新対象を現在日時分に書き換える
				copycomm.sendCommand[i++] = currenttime.bytes[0];
				//更新対象を現在日時分に書き換える
				copycomm.sendCommand[i] = currenttime.bytes[1];
			}//それ以外の時はそのままにする
			else {
				//更新対象の場所以外はカードデータを更新しない
				copycomm.sendCommand[i++] = data[updateblock][i];
				//更新しない
				copycomm.sendCommand[i] = data[updateblock][i];
			}
		}
		//組み立てた送信コマンドを返却用のコマンドに連結する
		senddata.push_back(copycomm);
		//コマンドの終わりを示すコマンドを連結する
		senddata.push_back(ENDCOMMAND);
		//組み立てたコマンドを返却する
		return senddata;
	}

	/*概要:現在日時分を分に変換して取得する関数
	引数:なし
	戻り値:unsigned short int times:分
	作成日：2017.10.11
	作成者:K.Asada*/
	int GetNowTime() {
		time_t now = time(NULL);          //現在時刻を取得するため
		struct tm *pnow = localtime(&now);//現在時刻を取得するための構造体を宣言
		unsigned short int times;                       //取得した現在時刻を格納するための変数
														//現在日時分を分に換算して格納する
		times = ((pnow->tm_mday * 24 + pnow->tm_hour) * 60 + pnow->tm_min);
		//取得した時間を返却する
		return times;
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

	/*概要:対象のユーザーのデータが存在しているかを確認するための関数
	引数:unsigned data:カードより取得した全データ
	戻り値:string uid:カードより取得したユーザーID
	作成日：2017.10.10
	作成者:K.Asada
	更新内容:パスワードチェックを削除
	更新日:2017.10.24
	更新者:K.Asada*/
	std::string CheckUser(std::vector<std::vector<unsigned char>> data) {
		std::string uid = "";        //カードより取得したユーザーIDを格納するための文字列
		//ユーザーIDが格納されたブロックを指定してユーザーIDを取得する
		uid = GetData(data, UID_INDEX);
		//取得したユーザー名でファイルを開く
		std::ifstream ifs((uid+".txt"));
		//ユーザーIDをファイル名としたファイルが開けないときはユーザーが存在していないとして例外を投げる
		if (!ifs.is_open()) {
			//対象のユーザーが存在していない旨を例外として投げる
			throw gcnew System::Exception(Constants->ID_NOT_FOUND_ERROR);
		}
		//判定が終わったらユーザーIDを返却する
		return uid;
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

	/*概要:対象の年が閏年かどうかを判定するための関数
	引数:int year:判定対象の年
	戻り値:bool judge:閏年であればtrueを、なければfalseを返す
	作成日:2017.10.24
	作成者:K.Asada*/
	bool CheckLeapYear(int year) {
		bool judge = true;    //判定結果を格納する場所
		//閏年の判定一回目
		if (year % 4 == 0) {
			//2回目の判定に移る
			if (year % 100 == 0) {
				//3回目の判定に移る
				if (year % 400 == 0) {
					//対象の年が4で割り切れ、100で割り切れ、400で割り切れる場合は閏年
					judge = true;
				}
				else {
					//対象の年が4で割り切れ、100で割り切れ、400で割り切れなかった場合は閏年でない
					judge = false;
				}
			}
			else {
				//対象の年が4で割り切れ、100で割り切れない場合は閏年
				judge = true;
			}
		}
		else {
			//対象の年が4で割り切れないときは閏年ではない
			judge = false;
		}
		//閏年かどうかの判定結果を返却する
		return judge;
	}

	/*概要:現在の年月日を閏年を考慮しながら日に変換して返却する関数
	引数:なし
	戻り値:int day:年月日を閏年を考慮しながら日に変換した変数
	作成日:2017.10.24
	作成者:K.Asada*/
	int ConvLeapYear() {
		time_t now = time(NULL);    //現在日を取得するための処理
		struct tm *pnow = localtime(&now);    //現在日を取得するための処理
		int year = 0;    //現在年を格納する変数
		int month = 0;   //現在月を格納する変数
		int day = 0;     //現在日を格納する変数
		//現在の年を取得する
		year = pnow->tm_year + 1900;
		//現在の月を取得する
		month = pnow->tm_mon + 1;
		//現在の日を取得する
		day = pnow->tm_mday;
		//年を日に変換する
		for (int i = 1; i < year; i++) {
			//閏年かどうかを判定する
			if (CheckLeapYear(i)) {
				//閏年の場合は1年は366日とする
				day += 366;
			}//閏年でない場合
			else {
				//閏年でない場合は1年は365日とする
				day += 365;
			}
		}
		//月を日に変換する
		for (int i = 0; i < month - 1; i++) {
			//それぞれの月に対応した日数の総和を求める
			day += yearmonth[i];
		}
		//求めた日を返却する
		return day;
	}

	/*概要:受け取った日を閏年を考慮しながら年、月、日に変換する関数
	引数:int days:変換対象の日
	戻り値:int days:求めた日
	作成日:2017.10.24
	作成者:K.Asada*/
int ConvLeapYear(int days) {
	int year = 0;    //求めた年を格納する変数
	int month = 0;   //求めた月を格納する変数
	int day = 0;     //求めた日を格納する変数
	//閏年を考慮しながら日を年に変換する
	for (int i = 0; days < 366; i++) {
		//閏年かどうかの判定を行う
		if (CheckLeapYear(i)) {
			//閏年であれば変換対象の日から366日を減算する
			days -= 366;
		}//閏年でなければ
		else {
			//閏年でなければ変換対象の日から365日を減算する
			days -= 365;
		}
	}
	//閏年を考慮しながら日を月に変換する
	for (int i = 0; days < yearmonth[i]; i++) {
		//総和の日からその月に対応した日数を減算していく
		days -= yearmonth[i];
	}
	//求めた日を返却する
	return days;
}

/*概要:前回の入館日または退館日を取得するための関数
引数:std::vector<std;;vector<unsigned char>> data:カードデータ
	:int beginindex:走査の始点となるインデックス
	:int endindex:走査の終点となるインデックス
戻り値:int gettime:前回の入館日または退館日
作成日:2017.10.24
作成者:K.Asada*/
int GetLastDay(std::vector<std::vector<unsigned char>> data, int beginindex, int endindex) {
	int yearday = 0;    //カード内の年月日情報を日に変換したもの
	int cardday = 0;    //カード内の日時分情報
	int gettime = 0;    //取得した日時分情報
	//カードより年月日情報を取得する
	yearday = GetCardYear(data);
	//年月日情報を日に変換する
	yearday = ConvLeapYear(yearday);
	//カードデータの走査を行う
	for (int i = 0; beginindex < endindex; i++) {
		//カードの日時分情報を取得する
		cardday = GetCardTime(data, beginindex, i);
		//前回の入館日または退館日であるかどうかの比較を行う
		if (yearday == cardday / 1440 && gettime <= cardday) {
			//前回の日時であれば取得する
			gettime = cardday;
		}
		//走査対象がブロック終端であれば
		if (i == 14) {
			//走査対象のインデックスを0に戻す
			i = 0;
			//次のブロックへ移動する
			beginindex++;
		}
	}
	//取得した前回の入館日または退館日を返却する
	return gettime;
}

/*概要:PC内のファイルデータとカードデータが一致するかを確認するための関数
引数:std::vector<std::vector<unsigned char>> data:カードデータ
	:std::string uid:ファイルを開くためのユーザーID
戻り値:bool judge:一致したかどうかの判定
作成日:2017.10.24
作成者:K.Asada*/
bool CollationFiledata(std::vector<std::vector<unsigned char>> data, std::string uid) {
	std::vector<std::vector<unsigned char>> filedata;    //ファイルより取得したデータを格納するための配列
	bool judge = true;    //ファイルデータが一致するかどうかの判定を格納する
	//ファイルデータを取得する
	filedata = GetFiledata(uid);
	//一致するかの判定を行う
	if (filedata == data) {
		//一致していればtrueを返す
		judge = true;
	}
	else {
		//一致していなければfalseを返す
		judge = false;
	}
	//判定結果を返却する
	return judge;
}

/*概要:ファイルデータを取得して配列に格納して返却する関数
引数:std::string uid:ファイルを開くためのユーザーID
戻り値:std::vector<std::vector<unsigned char>> filedata:ファイルデータを格納した配列
作成日:2017.10.24
作成者:K.Asada*/
std::vector<std::vector<unsigned char>> GetFiledata(std::string uid) {
	char getdata;    //ファイルから取得した1バイト分のデータを格納する変数
	std::vector<std::vector<unsigned char>> filedata = std::vector<std::vector<unsigned char>>(BLOCK_COUNT, std::vector<unsigned char>(0));
	int blockindex = 0;    //インデックス
	//ファイルストリームを開く
	std::ifstream ifs(uid + ".txt");
	//ファイルデータの走査を行う
	for (int i = 0; i < END_INDEX; i++) {
		if (!ifs.eof()) {
			//1バイト分取得する
			ifs.get(getdata);
		}
		//1ブロック分のデータを取得する
		for (int j = 0; j < 16; j++) {
			//ファイルデータを取得できているかの判定を行う
			if (getdata != '\n' && !ifs.eof()) {
				//取得したファイルデータを配列に格納する
				filedata[i].push_back(getdata);
				//次のデータを用意する
				ifs.get(getdata);
			}
			else {
				//ファイルデータがなければNULLを格納する
				filedata[i].push_back('\0');
			}
		}
	}
	//取得したファイルデータを返却する
	return filedata;
}

	/*概要:カードの入館日または退館日が格納されたブロックの中で次の更新対象となるブロックを取得するための関数
	引数:std::vector<std::vector<unsigned char>> data:カードデータ
	    :int beginindex:走査の始点となるブロック
		:int endindex:走査の終点となるブロック
	戻り値:int updateblock:次の更新対象となるブロック
	作成日:2017.10.24
	作成日:K.Asada*/
	int GetLastBlock(std::vector<std::vector<unsigned char>> data, int beginindex, int endindex) {
		int yearday = 0;        //カードに格納された年月日を格納する変数
		int cardday = 0;        //各ブロックごとの日付
		int gettime = 0;        //取得したカレントの日付
		int updateblock = 0;    //更新対象のブロック
		int updateindex = 0;    //更新対象のインデックス
		//カードから前回の年月日を取得する
		yearday = GetCardYear(data);
		//取得した年月日を日に変換する
		yearday = ConvLeapYear(yearday);
		//更新対象のブロックを探すために走査する
		for (int i = 0; beginindex < endindex; i+= 2) {
			//対象のデータから日時分を取得する
			cardday = GetCardTime(data, beginindex, i);
			//前回のカードへのアクセス時に更新した場所があれば取得する
			if (yearday == cardday / 1440 && gettime <= cardday) {
				//日時分を取得する
				gettime = cardday;
			}
			//ブロックの終端にたどり着いたら走査対象を次のブロックに切り替える
			if (i == 14) {
				//インデックスを0に戻す
				i = 0;
				//ブロックを進める
				beginindex++;
			}
			//更新対象となるブロックを記録する
			updateblock = beginindex;
		}
		//更新対象となるブロックを返却する
		return updateblock;
	}

	/*概要:退館状態を調べて対応した文字列を返却するための関数
	引数:std::vector<std::vector<unsigned char>> data:カードデータ
	戻り値:System::String check:退館状態に対応した文字列
	作成日:2017.10.24
	作成者:K.Asada*/
	System::String^ CheckLeaveState(std::vector<std::vector<unsigned char>> data) {
		int lastenter = 0;    //前回の入館日を格納する変数
		int lastleave = 0;    //前回の退館日を格納する変数
		System::String^ check = "";    //退館状態を示す文字列
		//前回の入館日を取得する
//		lastenter = GetLastDay(data, TIMES_1_INDEX, END_INDEX);
		//前回の退館日を取得する
//		lastleave = GetLastDay(data, LEAVE_1_INDEX, END_INDEX);
		//前回の入館日が前回の退館日より前であれば入館していないとする
		if (lastleave > lastenter) {
			//入館していない旨の文字列を格納する
			check = Constants->NOT_ENTER;
		}
		//取得した文字列を返却する
		return check;
	}

	/*概要:入館状態を調べて対応した文字列を返却する関数
	引数:std::vector<std::vector<unsigned char>> data:カードデータ
	戻り値:System::String^ check:状態に対応した文字列
	作成日:2017.10.24
	作成者:K.Asada*/
	System::String^ CheckEnterState(std::vector<std::vector<unsigned char>> data) {
		int lastenter = 0;             //前回の入館日
		int lastleave = 0;             //前回の退館日
		int current = 0;               //現在日時
		System::String^ check = "";    //判定結果の文字列
		//前回の入館日を取得する
//		lastenter = GetLastDay(data, TIMES_1_INDEX, END_INDEX);
		//前回の退館日を取得する
//		lastleave = GetLastDay(data, LEAVE_1_INDEX, END_INDEX);
		//現在の日時を取得する
		current = GetNowTime();
		//入館状態を判定する
		if (lastleave > lastenter && current - lastenter >= 1440) {
			//入館状態かつ前回の入館から1日以上経過していれば
			check = Constants->ENTER_DAY;
		}
		//取得した判定文字列を返却する
		return check;
	}

	/*概要:カード内の2バイトに分割された入館日または退館日をunsigned short int型に変換して返却する関数
	引数:std::vector<std::vector<unsigned char>> data:カードデータ
	    :int datablock:対象が格納されたブロック
		:int dataindex:対象が格納されているインデックス
	戻り値:ITOC time:指定された2バイトに分割された日付をunsigned short int型に連結した変数
	作成日:2017.10.24
	作成者:K.Asada*/
	unsigned short int GetCardTime(std::vector<std::vector<unsigned char>> data, int datablock, int dataindex) {
		ITOC time;    //2バイトに分割されたものを連結するための共有体
		//下位バイトを取得する
		time.bytes[0] = data[datablock][dataindex++];
		//上位バイトを取得する
		time.bytes[1] = data[datablock][dataindex];
		//連結したunsigned short int型を返却する
		return time.num;
	}

	/*概要:カード内の4バイトに分割された年月日をunsigned int型に変換して返却する関数
	引数:std::vector<std::vector<unsigned char>> data:カードデータ
	戻り値:UITOC year:unsigned int型に変換した年月日
	作成日:2017.10.24
	作成者:K.Asada*/
	unsigned int GetCardYear(std::vector<std::vector<unsigned char>> data) {
		UITOC years;    //4バイトに分割されたものを連結するための共有体
		//1バイトずつ連結する
		for (int i = 0; i < sizeof(unsigned int); i++) {
			//1バイトずつ連結していく
			years.bytes[i] = data[YEAR_INDEX][i];
		}
		//連結し終えたunsigned int型を返却する
		return years.num;
	}

	/*概要:カードに格納された日時分情報を文字列に変換する関数
	引数:std::vector<std::vcotr<unsigned char>> data:カードデータ
	戻り値:std::vector<string> times:日時分を文字列に変換した配列
	作成日:2017.10.16
	作成者:K.Asada*/
	std::vector<std::string> ConvTimes(std::vector<std::vector<unsigned char>> data, int index, int endindex) {
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
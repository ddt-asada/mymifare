#pragma once

#include "picojson.h"
#include <stdio.h>
#include <sstream>
#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <bitset>
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
	void UpdateCardData(std::vector <std::vector<unsigned char>> data, SCARDCONTEXT hContext, SCARDHANDLE hCard, DWORD ActiveProtocol, int beginindex) {
		ConnectCard* con = new ConnectCard();    //カード通信クラスをインスタンス化する
		std::vector<SENDCOMM> sendcomm;    //カードへの送信コマンド
		std::vector<SENDCOMM> tmp;
		ITOC now;            //現在の日時分を取得するための変数
		int updateblock = 0;              //更新対象のブロック
		int updateindex = 0;              //更新対象のインデックス
		//更新対象のブロック、インデックスを取得する
		GetUpdateBlock(beginindex, &updateblock, &updateindex);
		//現在日時分を取得する
		now.num = GetNowTime();
		//更新対象のデータを現在の日時分に書き換える
		ReadyData(data[updateblock], updateindex, now);
		//カード内の年月日の状態を確認する関数を呼び出す
		tmp = CheckYear(data);
		sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		//更新対象の日時分を書き換えるコマンドを組み立てる
		tmp = ReadyUpdateData(data[updateblock], updateblock);
		sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		//コマンドの終わりを示すコマンドを連結する
		sendcomm.push_back(ENDCOMMAND);
		//カードへコマンドを送信する
		con->Transmit(hContext, hCard, ActiveProtocol, sendcomm);
		return;
	}

	/*概要:カード内の年月日と現在の年月日を比較し、必要に応じて書き換える関数
	引数:std::vector<std::vector<unsigned char>> dataカードデータ
	戻り値:std::vector<SENDCOM>:送信データ
	作成日:2017.10.25
	作成者:K.Asada*/
	std::vector<SENDCOMM> CheckYear(std::vector<std::vector<unsigned char>>& data) {
		UITOC nowyears;    //現在の年月日を格納する
		std::vector<SENDCOMM> senddata;    //送信コマンド
		UITOC years;    //カード内の年月日を格納するための共有体
		//カード内の年月日を取得する
		years.num = GetCardYear(data);
		//現在の年月日を取得する
		nowyears.num = GetNowYear();
		//年月の判定を行う
		if (years.num / 100 != nowyears.num / 100) {
			//年月が違っていた場合は入館日、退館日、年月日を更新する
			senddata = UpdateAllDate(data, nowyears);
		}//年月日の判定を行う
		else if (years.num != nowyears.num) {
			//日が違っていた場合はカード内の年月日のみを書き換える
			senddata = UpdateYear(nowyears, data);
		}
		//作成した更新用のコマンドを返却する
		return senddata;
	}

	/*概要:カードへ送信するデータの組み立て、コマンドの作成を行う関数
	引数:string setdata:送信するデータ
	戻り値:unsigned char:データを送信するためのコマンド
	作成日:2017.10.10
	作成者:K.Asada*/
	std::vector<SENDCOMM> ReadySetData(std::vector<std::vector<unsigned char>> data, int blockindex) {
		try {
			std::vector<SENDCOMM> sendcomm;        //組み立てたコマンドを格納するための構造体
			SENDCOMM certify = AUTHENTICATE;       //ブロック認証コマンドのコピー
			SENDCOMM sendcard = SENDCARD;          //データ送信コマンドのコピー
												   //コマンドを初期化する
			sendcomm = InitCommand(blockindex);
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

	/**/
	unsigned int GetNowYear() {
		time_t now = time(NULL);    //現在日を取得するための処理
		struct tm *pnow = localtime(&now);    //現在日を取得するための処理
		int ret = 0;
		int year = 0;    //現在年を格納する変数
		int month = 0;   //現在月を格納する変数
		int day = 0;     //現在日を格納する変数
						 //現在の年を取得する
		year = pnow->tm_year + 1900;
		//現在の月を取得する
		month = pnow->tm_mon + 1;
		//現在の日を取得する
		day = pnow->tm_mday;
		ret = year * 10000 + month * 100 + day;
		return ret;
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
	std::vector<SENDCOMM> ReadyUpdateData(std::vector<unsigned char> data, int updateblock) {
		std::vector<SENDCOMM> senddata;    //更新用のコマンド
		SENDCOMM copycomm = SENDCARD;      //データ送信コマンドのテンプレート
		int block = writeblock[updateblock];
		//コマンドの初期値を取得する
		senddata = InitCommand(block);
		//送信コマンドの対象のブロックを設定する
		copycomm.sendCommand[3] = block;
		//1ブロック分の送信コマンドを組み立てていく
		for (int i = 0; i < 16; i++) {
			//送信コマンドを順に組み立てていく
			copycomm.sendCommand[5 + i] = data[i];
		}
		//組み立てた送信コマンドを返却用のコマンドに連結する
		senddata.push_back(copycomm);
		//組み立てたコマンドを返却する
		return senddata;
	}

	/*概要:カード内の年月日、入館日、退館日をすべて更新するためのコマンドを組み立てる関数
	引数:std::vector<std::vector<unsigned char>> data:カードデータ
	    :UITOC nowyears:現在年月日
	戻り値:std::vector<SENDCOMM> sendcomm:更新用のコマンド
	作成日:　2017.10.25
	作成者:K.Asada*/
	std::vector<SENDCOMM> UpdateAllDate(std::vector<std::vector<unsigned char>> data, UITOC nowyears) {
		int updateblock = 0;    //更新対象のブロック
		int updateindex = 0;    //更新対象のインデックス
		std::vector<SENDCOMM> sendcomm;    //更新用のコマンド
		std::vector<SENDCOMM> tmp;
		//更新対象のブロックを取得する
		GetUpdateBlock(TIMES_1_INDEX, &updateblock, &updateindex);
		//データを更新していく
		for (int i = TIMES_1_INDEX; i <= updateblock; i++) {
			//1ブロックずつデータを更新していく
			for (int j = 0; j < 16; j++) {
				//現在日時分を格納すべき場所にたどり着いたらやめる
				if (i == updateblock && j == updateindex * 2) {
					break;
				}//それ以外の時は
				else {
					//古いデータを削除していく
					data[i][j] = 0;
					data[i + 6][j] = 0;
				}
			}
			//1ブロック分の更新コマンドを組み立てる
			tmp = ReadyUpdateData(data[i], i);
			sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
			//1ブロック分の更新コマンドを組み立てる
			tmp = ReadyUpdateData(data[i], i);
			sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		}
		//年月日を更新するコマンドを格納する
		tmp = UpdateYear(nowyears, data);
		sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		//組み立てたコマンドを格納する
		return sendcomm;
	}

	/*概要:年月日のみを更新するコマンドを組み立てる関数
	作成日:2017.10.25
	作成者:K.Asada*/
	std::vector<SENDCOMM> UpdateYear(UITOC nowyear, std::vector<std::vector<unsigned char>> data) {
		ITOC lowbit;    //現在年月日の下位ビットを格納するための共有体
		ITOC upperbit;  //現在年月日の上位ビットを格納するための共有体
		std::vector<SENDCOMM> sendcomm;    //返却用のコマンド
		std::vector<SENDCOMM> tmp;
		//現在年月日を上位2バイトと下位2バイトに分割する
		for (int i = 0; i < 2; i++) {
			//下位2バイトを格納する
			lowbit.bytes[i] = nowyear.bytes[i];
			//上位2バイトを格納する
			upperbit.bytes[i] = nowyear.bytes[i + 2];
		}
		//更新データの準備を行う
		ReadyData(data[YEAR_1_INDEX], 0, lowbit);
		//更新データの準備を行う
		ReadyData(data[YEAR_2_INDEX], 0, upperbit);
		//更新用のコマンドを組み立てる
		tmp = ReadyUpdateData(data[YEAR_1_INDEX], YEAR_1_INDEX);
		sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		//更新用のコマンドを組み立てる
		tmp = ReadyUpdateData(data[YEAR_2_INDEX], YEAR_2_INDEX);
		sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		//組み立てたコマンドを返却する
		return sendcomm;
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
//	filedata = GetFiledata(uid);
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

	/*概要:カードの入館日または退館日が格納されたブロックの中で次の更新対象となるブロックを取得するための関数
	引数:std::vector<std::vector<unsigned char>> data:カードデータ
	    :int beginindex:走査の始点となるブロック
		:int endindex:走査の終点となるブロック
	戻り値:int updateblock:次の更新対象となるブロック
	作成日:2017.10.24
	作成日:K.Asada
	更新内容:ロジックを変更
	更新日:2017.10.25
	更新者:K.Asada*/
	void GetUpdateBlock(int block, int* updateblock, int* updateindex) {
		int nowday = 0;    //現在日時を格納する変数
		//現在日を取得する
		nowday = GetNowDay();
		//更新ブロックを計算する
		*updateblock = block + nowday / 8;
		//更新インデックスを計算する
		*updateindex = nowday % 8;
		return;
	}

	/*概要:現在の日を取得するための関数
	引数:なし
	戻り値:現在日
	作成日:2017.10.25
	作成者:K.Asada*/
	int GetNowDay() {
		time_t now = time(NULL);    //現在日を取得するための処理
		struct tm *pnow = localtime(&now);    //現在日を取得するための処理
		int day = 0;     //現在日を格納する変数
		//現在の日を取得する
		day = pnow->tm_mday;
		//取得した現在の日を返却する
		return day;
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
		for (int i = 0; i < 2; i++) {
			//1バイトずつ連結していく
			years.bytes[i] = data[YEAR_1_INDEX][i];
			years.bytes[i + 2] = data[YEAR_2_INDEX][i];
		}
		//連結し終えたunsigned int型を返却する
		return years.num;
	}

	/*概要:受け取ったunsigned short int型をカードに格納するために分割する関数
	引数:格納先のカードデータ
	戻り値:なし
	作成日:2017.10.25
	作成者:K.Asada*/
	void ReadyData(std::vector<unsigned char>& data, int updateblock, ITOC set) {
		//下位バイトを格納する
		data[updateblock * 2] = set.bytes[0];
		//上位バイトを格納する
		data[updateblock * 2 + 1] = set.bytes[1];
		return;
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

	/*概要:*/
	UITOC ConvJSONYear(std::string birthday) {
		UITOC conbirth;    //ストリングから取得した変数を格納する共有体
		//受け取った文字列から年を削除する
		birthday = AssignmentErase(birthday, "年");
		//文字列から月を削除する
		birthday = AssignmentErase(birthday, "月");
		//文字列から二値を削除する
		birthday = AssignmentErase(birthday, "日");
		//年月日を削除して数値だけになった文字列を変換する
		conbirth.num = std::stoi(birthday);
		//変換した変数を返却する
		return conbirth;
	}

	/*概要:*/
	char ConvJSONBit(std::string check, std::string name1, std::string name2, std::string name3, std::string name4) {
		char ret = 0;    //返却用の変数
		//どのビットがたっている状態にするかの判定を返す
		if (check == name1) {
			//1番目の時はどのビットもたっていない状態を返す
			ret = 0;
		}
		else if (check == name2) {
			//2番目の時は1ビット目がたっている状態を返す
			ret = 1;
		}
		else if (check == name3) {
			//3番目の時は2ビット目がたっている状態を返す
			ret = 1 << 1;
		}
		else if (check == name4) {
			//4番目の時は4ビット目がたっている状態を返す
			ret = 1 << 2;
		}
		//判定結果を返却する
		return ret;
	}

	/*概要:*/
	std::string AssignmentErase(std::string target, std::string assignment) {
		int index = 0;    //文字列削除の起点
		int strlen = 0;   //削除する長さ
		//削除の起点を取得する
		index = target.find(assignment);
		//削除の長さを取得する
		strlen = assignment.length();
		//指定した文字列を削除する
		target.erase(index, strlen);
		//削除し終えた文字列を返却する
		return target;
	}

	/*概要:ファイルデータから全情報を取得する関数
	作成日:2017.10.26
	作成者:K.Asada*/
	std::vector<std::vector<unsigned char>> GetFileData(std::string uid) {
		picojson::object obj;
		std::vector<std::vector<unsigned char>> retdata = std::vector<std::vector<unsigned char>>(BLOCK_COUNT, std::vector<unsigned char>(16, '\0'));    //返却用のファイルデータ
		std::vector<std::vector<unsigned char>> tmpdata;
		unsigned char tmp[16] = { '\0' };                            //各データを取得するための一時的な置き場
		std::vector<std::string> test;
		std::string str = "";
		UITOC con;                                          //文字列をint型に変換するときに1バイトごとに分割するための共有体
		obj = GetPicoObj(uid);
		//JSONからユーザーIDを取得する
		retdata[0] = ConvFileData(obj[UID_LABEL].get<std::string>());
		//JSONから名前（姓）を取得する
		retdata[1] = ConvFileData(obj[FIRST_NAME].get<std::string>());
		//JSONから名前（名）を取得する
		retdata[2] = ConvFileData(obj[LAST_NAME].get<std::string>());
		//JSONからパスワードを取得する
		retdata[3] = ConvFileData(obj[PASS_LABEL].get<std::string>());
		//JSONから電話番号を取得する
		retdata[4] = ConvFileData(obj[TELL_LABEL].get<std::string>());
		//JSONから生年月日を取得する
		con.num = StrYear(obj[BIRTH_LABEL].get<std::string>());
		retdata[5][0] = con.bytes[0];
		retdata[5][1] = con.bytes[1];
		retdata[5][2] = con.bytes[2];
		retdata[5][3] = con.bytes[3];
		//JSONから属性を取得する
		retdata[5][4] = ConvJSONBit(obj[ELEM_LABEL].get<std::string>(), ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4);
		//JSONから権限を取得する
		retdata[5][5] = ConvJSONBit(obj[ADM_LABEL].get<std::string>(), ADM_NAME1, ADM_NAME2, "", "");
		//JSONから役職を取得する
		retdata[5][6] = ConvJSONBit(obj[OCCUP_LABEL].get<std::string>(), POS_NAME1, POS_NAME2, POS_NAME3, POS_NAME4);
		//JSONから所属グループを取得する
		retdata[5][7] = ConvJSONBit(obj[GROUP_LABEL].get<std::string>(), "", OCCUP_NAME1, OCCUP_NAME2, OCCUP_NAME3) << 4;
		//JSONから所属を取得する
		retdata[5][7] = ConvJSONBit(obj[DEPART_LABEL].get<std::string>(), "", DEPART_NAME1, DEPART_NAME2, DEPART_NAME3);
		//JSONから住所を取得する
		str = obj[ADDRESS_LABEL].get<std::string>();
		//16バイトずつに分割して配列に格納する
		retdata[6] = ConvFileData(str, 0, 16);
		retdata[7] = ConvFileData(str, 16, 32);
		retdata[8] = ConvFileData(str, 32, 48);
		retdata[9] = ConvFileData(str, 48, 64);
		retdata[10] = ConvFileData(str, 64, 80);
		retdata[11] = ConvFileData(str, 80, 96);
		//入館日を取得する
		tmpdata = GetFileTime(obj[ENTER_LABEL].get<picojson::object>());
		retdata[12] = tmpdata[0];
		retdata[13] = tmpdata[1];
		retdata[14] = tmpdata[2];
		retdata[15] = tmpdata[3];
		//退館日を取得する
		tmpdata = GetFileTime(obj[LEAVE_LABEL].get<picojson::object>());
		retdata[18] = tmpdata[0];
		retdata[19] = tmpdata[1];
		retdata[20] = tmpdata[2];
		retdata[21] = tmpdata[3];
		//年月日を取得する
		con.num = StrYear(obj[YEAR_LABEL].get<std::string>());
		retdata[12][0] = con.bytes[0];
		retdata[12][1] = con.bytes[1];
		retdata[18][0] = con.bytes[0];
		retdata[18][1] = con.bytes[1];
		return retdata;
	}

	std::vector<unsigned char> ConvFileData(std::string filedata) {
		std::vector<unsigned char> data = std::vector<unsigned char>(16, '\0');
		for (int i = 0; i < filedata.size(); i++) {
			data[i] = filedata[i];
		}
		return data;
	}

	std::vector<unsigned char> ConvFileData(std::string filedata, int begin, int end) {
		std::vector<unsigned char> data = std::vector<unsigned char>(16, '\0');
		int index = 0;
		for (int i = begin; i < filedata.size() && i < end; i++) {
			data[index++] = filedata[i];
		}
		return data;
	}

	std::vector<std::vector<unsigned char>> GetFileTime(picojson::object obj) {
		std::vector<std::vector<unsigned char>> retdata = std::vector<std::vector<unsigned char>>(4, std::vector<unsigned char>(16, '\0'));    //返却用のファイルデータ
		int year = 0;    //年を取得するための変数
		int month = 0;    //月を取得するための変数
		int day = 0;     //日を取得するための変数
		ITOC tmp;
		picojson::array days;
		std::string key = "";    //JSONから日時分を取得するためのキー
		std::string test;
		time_t now = time(NULL);
		struct  tm *pnow = localtime(&now);
		//年を取得する
		year = pnow->tm_year + 1900;
		//月を取得する
		month = pnow->tm_mon;
		//日を取得する
		day = pnow->tm_mday + 1;
		//31日分の履歴を取得する
		for (int i = 0; i < 31; i++) {
			//JSONから日時分を取得するためのキーを組み立てる
			key = std::to_string(year) + "年" + std::to_string(month) + "月" + std::to_string(day) + "日";
			//キーに対応した日時分が取得できれば
			if (obj[key].is<picojson::array>()) {
				days = obj[key].get<picojson::array>();
				picojson::array::iterator itr = days.end();
				test = (--itr)->get<std::string>();
				tmp.num = StrTime(test);
				retdata[day / 8][(day % 8) * 2] = tmp.bytes[0];
				retdata[day / 8][(day % 8) * 2 + 1] = tmp.bytes[1];
			}
			if (day == 31) {
				day = 1;
				month += 1;
			}
			else {
				day++;
			}
		}
		return retdata;
	}

	/*概要:現在の日時分をファイルに格納するための文字列に変換する関数
	引数:なし
	戻り値:std::string timestr:現在の日時分を示す文字列
	作成日:2017.10.26
	作成者:K.Asada*/
	std::string TimeStr() {
		time_t now = time(NULL);    //現在時刻を取得するための構造体
		struct tm *pnow = localtime(&now);    //現在時刻を取得するための構造体
		int day = 0;    //現在日を格納するための変数
		int hour = 0;   //現在時を格納するための変数
		int minute = 0; //現在分を格納するための変数
		std::string timestr = "";    //現在日時分を示す文字列
		//現在の日を取得する
		day = pnow->tm_mday;
		//現在の時を取得する
		hour = pnow->tm_hour;
		//現在の分を取得する
		minute = pnow->tm_min;
		//文字列として組み立てる
		timestr = std::to_string(day) + "日" + std::to_string(hour) + "時" + std::to_string(minute) + "分";
		//作成した文字列を返却する
		return timestr;
	}

	/*概要:日時分をファイルに格納するための文字列に変換する関数
	引数:int nowtime:日時分を分に変換した変数
	戻り値:std::string timestr:日時分を示す文字列
	作成日:2017.10.26
	作成者:K.Asada*/
	std::string TimeStr(int nowtime) {
		int day = 0;    //現在日を格納するための変数
		int hour = 0;   //現在時を格納するための変数
		int minute = 0; //現在分を格納するための変数
		std::string timestr = "";    //現在日時分を示す文字列
		//引数から日を取得する
		day = nowtime / 1440;
		//引数から時を取得する
		hour = nowtime / 60 - day * 24;
		//引数から分を取得する
		minute = nowtime % 60;
		//文字列として組み立てる
		timestr = std::to_string(day) + "日" + std::to_string(hour) + "時" + std::to_string(minute) + "分";
		//作成した文字列を返却する
		return timestr;
	}

	/*概要:現在の年月日をファイルに格納するための文字列に変換するの関数
	引数:なし
	戻り値:std::string yearstr:現在の年月日を文字列に変換したもの
	作成日:2017.10.26
	作成者:K.Asada*/
	std::string YearStr() {
		time_t now = time(NULL);    //現在時刻を取得するための構造体
		struct tm *pnow = localtime(&now);    //現在時刻を取得するための構造体
		int year = 0;    //現在年を格納するための変数
		int month = 0;   //現在月を格納するための変数
		int day = 0; //現在日を格納するための変数
		std::string yearstr = "";    //現在日時分を示す文字列
									 //現在の年を取得する
		year = pnow->tm_year + 1900;
		//現在の月を取得する
		month = pnow->tm_mon + 1;
		//現在の日を取得する
		day = pnow->tm_mday;
		//文字列として組み立てる
		yearstr = std::to_string(year) + "年" + std::to_string(month) + "月" + std::to_string(day) + "日";
		//作成した文字列を返却する
		return yearstr;
	}

	/*概要:年月日をファイルに格納するための文字列に変換するの関数
	引数:int nowyear:年月日を示す変数
	戻り値:std::string yearstr:現在の年月日を文字列に変換したもの
	作成日:2017.10.26
	作成者:K.Asada*/
	std::string YearStr(int nowyear) {
		int year = 0;    //現在年を格納するための変数
		int month = 0;   //現在月を格納するための変数
		int day = 0; //現在日を格納するための変数
		std::string yearstr = "";    //現在日時分を示す文字列
									 //現在の年を取得する
		year = nowyear / 10000;
		//現在の月を取得する
		month = nowyear / 100 - year * 100;
		//現在の日を取得する
		day = nowyear % 100;
		//文字列として組み立てる
		yearstr = std::to_string(year) + "年" + std::to_string(month) + "月" + std::to_string(day) + "日";
		//作成した文字列を返却する
		return yearstr;
	}

	/*概要:日時分を示す文字列から日時分を示す変数に変換する関数
	引数:std:: string timestr:日時分を示す文字列
	戻り値:int time:日時分を示す変数
	作成日:2017.10.26
	作成者:K.Asada*/
	int StrTime(std::string timestr) {
		int time = 0;    //日時分を格納するためも文字列
		int begin = 0;
		int end = 0;   //文字列から日時分を抜き出す時のインデックス
		std::string day = "";//日を示す文字列
		std::string hour = "";    //時を示す文字列
		std::string minute = "";  //分を示す文字列
		//文字列の中の"日"の位置を探す
		end = timestr.find("日");
		//文字列の中から日を抜き出す
		day = timestr.substr(0, end);
		//次の始点を設定する
		begin = end + 1;
		//文字列の"時"の位置を探す
		end = timestr.find("時");
		//文字列の中から時を抜き出す
		hour = timestr.substr(begin, end - begin);
		//次の始点を設定する
		begin = end + 1;
		//文字列の"分"の位置を探す
		end = timestr.find("分");
		//文字列の中から分を抜き出す
		minute = timestr.substr(begin, end - begin);
		//文字列から変数に変換する
		time = std::stoi(day) * 1440 + std::stoi(hour) * 60 + std::stoi(minute);
		//変数を返却する
		return time;
	}

	/*概要:年月日を示す文字列から年月日を示す変数に変換する関数
	引数:std:: string yearstr:年月日を示す文字列
	戻り値:int years:年月日を示す変数
	作成日:2017.10.26
	作成者:K.Asada*/
	int StrYear(std::string yearstr) {
		int years = 0;    //年月日を格納するためも文字列
		int begin = 0;
		int end = 0;   //文字列から年月日を抜き出す時のインデックス
		std::string year = "";//年を示す文字列
		std::string month = "";    //月を示す文字列
		std::string day = "";  //日を示す文字列
								  //文字列の中の"年"の位置を探す
		end = yearstr.find("年");
		//文字列の中から日を抜き出す
		year = yearstr.substr(0, end);
		//次の始点を設定する
		begin = end + 1;
		//文字列の"月"の位置を探す
		end = yearstr.find("月");
		//文字列の中から時を抜き出す
		month = yearstr.substr(begin, end - begin);
		//次の始点を設定する
		begin = end + 1;
		//文字列の"日"の位置を探す
		end = yearstr.find("日");
		//文字列の中から分を抜き出す
		day = yearstr.substr(begin, end - begin);
		//文字列から変数に変換する
		years = std::stoi(year) * 10000 + std::stoi(month) * 100 + std::stoi(day);
		//変数を返却する
		return years;
	}

	/*概要:ファイルから取得した文字列をpicojsonで扱うためのobjectに変換する関数
	引数:std::string uid:ファイルの名前
	戻り値:picojson::object obj:picojsonのオブジェクト
	作成日:2017.10.26
	作成者:K.Asada*/
	picojson::object GetPicoObj(std::string uid) {
		picojson::object obj;    //返却用のpicojsonのオブジェクト
		picojson::value val;     //パースしたJSONを格納するためのvalue
		std::stringstream ss;    //ファイルからデータを取得するためのストリーム
		//ファイルを開く
		std::ifstream ifs(uid, std::ios_base::binary);
		//ストリームにデータを流し込む
		ss << ifs.rdbuf();
		//picojsonへ流し込んでパースする
		ss >> val;
		//JSONを扱えるようにオブジェクト型に変換する
		obj = val.get<picojson::object>();
		//ファイルストリームを閉じる
		ifs.close();
		//変換したオブジェクトを返却する
		return obj;
	}

	/*概要:作成したJSONオブジェクトをファイルに保存するための関数
	引数:picojson::object obj:作成したJSONオブジェクト
	戻り値:なし
	作成日:2017.10.26
	作成者:K.Asada*/
	void OutPutJSON(picojson::object obj, std::string uid) {
		std::string out;    //ファイルに格納するための文字列
		//書き込み用のストリームを開く
		std::ofstream ofs(uid);
		//JSONオブジェクトより文字列に変換する
		out = picojson::value(obj).serialize();
		//ファイルに文字列を書き出す
		ofs << out;
		//ファイルストリームを閉じる
		ofs.close();
		return;
	}

	/*概要:ファイル内の年月日を現在の年月日に更新するための関数
	引数:std::string uid:ファイルの名前
	戻り値:なし
	作成日:2017.10.26
	作成者:K.Asada*/
	void UpdateFileYear(std::string uid) {
		picojson::object obj;    //JSONを扱うためのオブジェクト
		//対象のファイルからJSONのオブジェクトを取得する
		obj = GetPicoObj(uid);
		//取得したJSONの年月日を書き換える
		obj[YEAR_LABEL] = (picojson::value)(YearStr());
		//書き換えたJSONをファイルへ書き出す
		OutPutJSON(obj, uid);
		return;
	}

	/*概要:ファイルに日付を追加する関数
	引数:std::string uid:ファイルの名前
	戻り値:なし
	作成日:2017.10.26
	作成者:K.Asada*/
	void UpdateFileDate(std::string uid) {
		picojson::object obj1;    //JSONを扱うためのオブジェクト
		picojson::object* obj2;    //JSONを扱うためのオブジェクト
		picojson::array timeary;  //JSONに配列を格納するための配列
		std::string key = "";     //JSONから書き換え対象を抜き出すためのキー
		std::string timestr = ""; //書き換えのための日時分をしめす文字列
		//ファイルからJSONのオブジェクトを取得する
		obj1 = GetPicoObj(uid);
		//書き換え対象を取得するためのキーを取得する
		key = YearStr();
		//書き換えるための日時分を取得する
		timestr = TimeStr();
		//オブジェクトから入館日を示すオブジェクトを取得する
		obj2 = &obj1[ENTER_LABEL].get<picojson::object>();
		//対象の箇所にすでに値があるかを判定する
		if ((*obj2)[key].is<picojson::array>()) {
			//既に配列があればその配列を取得する
			timeary = (*obj2)[key].get<picojson::array>();
		}
		//配列に現在の日時分を追加する
		timeary.push_back(picojson::value(timestr));
		//配列を入館日の子として連結する
		(*obj2)[key] = picojson::value(timeary);
		//JSONをファイルに書き出す
		OutPutJSON(obj1, uid);
	}
};
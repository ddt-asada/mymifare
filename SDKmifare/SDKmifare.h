#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "AdmissionSystem.h"
#include "ConnectCard.h"
#include "CONSTANTS.h"
#include "PassForm.h"
#include "InputNewUserForm.h"

namespace sdkmifare {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// SDKmifare の概要
	/// </summary>
	public ref class SDKmifare : public System::Windows::Forms::Form
	{
	public:
		SDKmifare(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~SDKmifare()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonAdmission;
	protected:
	private: System::Windows::Forms::Button^  buttonNewUser;
	private: System::Windows::Forms::Button^  buttonLeaving;
	private: System::Windows::Forms::Label^  labelCauntion;
	private: System::Windows::Forms::Label^  labelInfomasion;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonAdmission = (gcnew System::Windows::Forms::Button());
			this->buttonNewUser = (gcnew System::Windows::Forms::Button());
			this->buttonLeaving = (gcnew System::Windows::Forms::Button());
			this->labelCauntion = (gcnew System::Windows::Forms::Label());
			this->labelInfomasion = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonAdmission
			// 
			this->buttonAdmission->Location = System::Drawing::Point(123, 119);
			this->buttonAdmission->Name = L"buttonAdmission";
			this->buttonAdmission->Size = System::Drawing::Size(269, 229);
			this->buttonAdmission->TabIndex = 0;
			this->buttonAdmission->Text = L"入館";
			this->buttonAdmission->UseVisualStyleBackColor = true;
			this->buttonAdmission->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonAdmission);
			// 
			// buttonNewUser
			// 
			this->buttonNewUser->Location = System::Drawing::Point(777, 119);
			this->buttonNewUser->Name = L"buttonNewUser";
			this->buttonNewUser->Size = System::Drawing::Size(269, 229);
			this->buttonNewUser->TabIndex = 1;
			this->buttonNewUser->Text = L"作成";
			this->buttonNewUser->UseVisualStyleBackColor = true;
			this->buttonNewUser->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonNewUserClick);
			// 
			// buttonLeaving
			// 
			this->buttonLeaving->Location = System::Drawing::Point(455, 119);
			this->buttonLeaving->Name = L"buttonLeaving";
			this->buttonLeaving->Size = System::Drawing::Size(269, 229);
			this->buttonLeaving->TabIndex = 2;
			this->buttonLeaving->Text = L"退館";
			this->buttonLeaving->UseVisualStyleBackColor = true;
			this->buttonLeaving->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonLeavingClick);
			// 
			// labelCauntion
			// 
			this->labelCauntion->AutoSize = true;
			this->labelCauntion->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->labelCauntion->Location = System::Drawing::Point(503, 351);
			this->labelCauntion->Name = L"labelCauntion";
			this->labelCauntion->Size = System::Drawing::Size(0, 53);
			this->labelCauntion->TabIndex = 3;
			this->labelCauntion->Click += gcnew System::EventHandler(this, &SDKmifare::labelCauntion_Click);
			// 
			// labelInfomasion
			// 
			this->labelInfomasion->AutoSize = true;
			this->labelInfomasion->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->labelInfomasion->Location = System::Drawing::Point(212, 535);
			this->labelInfomasion->Name = L"labelInfomasion";
			this->labelInfomasion->Size = System::Drawing::Size(75, 33);
			this->labelInfomasion->TabIndex = 4;
			this->labelInfomasion->Text = L"aaaa";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Red;
			this->label1->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label1->Location = System::Drawing::Point(531, 56);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(117, 33);
			this->label1->TabIndex = 5;
			this->label1->Text = L"label1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label2->Location = System::Drawing::Point(0, 535);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(162, 363);
			this->label2->TabIndex = 5;
			this->label2->Text = L"名　　　前：\r\nふり 　がな：\r\n住　　　所：\r\n誕 生  日：\r\n電話番号：\r\n属　　　性：\r\n権　　　限：\r\n職　　　種：\r\n部　　　署：\r\n役　　　職：\r\n"
				L"入退館日：";
			// 
			// SDKmifare
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1175, 649);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->labelInfomasion);
			this->Controls->Add(this->labelCauntion);
			this->Controls->Add(this->buttonLeaving);
			this->Controls->Add(this->buttonNewUser);
			this->Controls->Add(this->buttonAdmission);
			this->Name = L"SDKmifare";
			this->Text = L"SDKmifare";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private:SCARDCONTEXT hContext = 0;		//読み込んだリソースマネージャへのポインタ
		std::vector<std::vector<unsigned char>>* carddata = new std::vector<std::vector<unsigned char>>();           //取得したカードデータ
		CONSTANTGROUP::ConstantString^ Constants = gcnew CONSTANTGROUP::ConstantString();


/*概要:作成ボタンを押したときのクリックイベント
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void ButtonNewUserClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		InputNewUserForm^ create = gcnew InputNewUserForm();    //新規ユーザー情報を入力するためのクラスをインスタンス化
		AdmissionSystem* adm = new AdmissionSystem();           //入館管理システム関連のクラスをインスタンス化
		//新規で作成する旨を伝える
		MessageBox::Show(Constants->NEW_MESSAGE);
		//作成画面でOKが押されたらそのまま作成する
		if (create->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			std::string id;
			this->MarshalString(create->UID, id);
			//カード待ち状態を示すダイアログを表示して、キャンセルが押されたら接続を終了する
			MessageBox::Show(Constants->SET_CARD_MESSAGE);
			//カードからデータを取得する関数を呼び出す
			adm->SetCardData(id);
			//作成完了のメッセージを表示する
			MessageBox::Show(Constants->FINISH_MESSAGE);
		}//OK以外の時は作成が中断されたとする
		else {
			MessageBox::Show(Constants->CANCEL_MESSAGE);
		}
		return;
	}
	catch (System::Exception^ e) {
		MessageBox::Show(Constants->ERROR_MESSAGE);
		Console::Write(e);
	}
}

/*概要:退館ボタンを押したときのクリックイベント
作成日：2017.10.10
作成者：K.Asada*/
private: System::Void ButtonLeavingClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		//入館していない場合は例外を投げる
		if (this->carddata->empty()) {
			//入館していない旨を表示する
			MessageBox::Show("入館していません。");
			//入館していない例外を投げる
			throw gcnew System::Exception("入館中のユーザーがいません。");
		}
		AdmissionSystem* adm = new AdmissionSystem();    //カードとの接続を行ったりするクラスをインスタンス化
		std::string uid = "";
		//カードデータよりユーザIDを取得する
		uid = adm->GetData(*this->carddata, UID_INDEX, 0, 8);
    	//退館日を記録する
		adm->SetAdmissionTimes(uid);
		//カード待ち状態を示すダイアログを表示して、キャンセルが押されたら接続を終了する
		MessageBox::Show(Constants->SET_CARD_MESSAGE);
		//カードからデータを取得する関数を呼び出す
		adm->SetCardData(uid);
		//ユーザー情報ラベルを初期化する
		this->labelInfomasion->Text = "";
		//属性ラベルを初期化する
		this->Controls->Remove(this->label1);
		//退館状態であることをメイン画面へ表示する
		this->labelCauntion->Text = Constants->LEAVE_MESSAGE;
		//保存しているユーザーのカードデータを削除する
		this->carddata->clear();
		//退館時のメッセージを表示する
		MessageBox::Show(Constants->LEAVE_MESSAGE);
		return;
	}
	catch (System::Exception^ e) {
		MessageBox::Show(Constants->ERROR_MESSAGE);
		System::Console::Write(e);
	}
}


/*概要:入館ボタンをクリックしたときのイベント
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void ButtonAdmission(System::Object^  sender, System::EventArgs^  e) {
	try {
		InputNewUserForm^ create = gcnew InputNewUserForm();
		AdmissionSystem* adm = new AdmissionSystem();    //カードとの接続を行ったりするクラスをインスタンス化
		PassForm^ pass = gcnew PassForm();               //パスワードを入力するフォームをインスタンス化
		std::string passtring = "";                      //パスワードを格納するための文字列
		//メッセージを表示する
		MessageBox::Show(Constants->SET_CARD_MESSAGE);
		//パスワード入力画面に移行する
		pass->ShowDialog();
		//受け取ったパスを変換するStringからstringへ
		this->MarshalString(create->SetByte(pass->textBox1->Text, 8), passtring);
		//カードデータを受信する関数を呼び出す
		*this->carddata = adm->GetCardData(passtring);
		//ユーザー情報をメイン画面へ反映する
		this->CreateDisp();
		//入館状態であることをメイン画面へ表示する
		this->labelCauntion->Text = Constants->ENTER_MESSAGE;
		//入館完了のメッセージを表示する
		MessageBox::Show(Constants->ENTER_MESSAGE);
		return;
	}
	catch (System::Exception^ e) {
		MessageBox::Show(Constants->ERROR_MESSAGE);
		Console::Write(e);
	}
}


/*概要:取得したデータをもとに画面に表示するラベルを作成する関数
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void CreateDisp() {
	try {
		std::string tmp = "";
		std::string showdata = "";            //カードより取得した文字列を格納する
		AdmissionSystem* adm = new AdmissionSystem();    //カードよりデータを取得するためのクラスをインスタンス化
		//カードデータより名前（漢字）を示す文字列を取得する
		showdata += adm->GetData(*this->carddata, NAME_INDEX) + '\n';
		//カードデータより名前（フリガナ）を示す文字列を取得する
		showdata += adm->GetData(*this->carddata, KANA_INDEX) + '\n';
		//カードデータより住所を示す文字列を取得する
		showdata += adm->GetData(*this->carddata, ADRESS_1_INDEX);
		//カードデータより住所を示す文字列を取得する
		showdata += adm->GetData(*this->carddata, ADRESS_2_INDEX);
		//カードデータより住所を示す文字列を取得する
		showdata += adm->GetData(*this->carddata, ADRESS_3_INDEX);
		//カードデータより住所を示す文字列を取得する
		showdata += adm->GetData(*this->carddata, ADRESS_4_INDEX);
		//カードデータより住所を示す文字列を取得する
		showdata += adm->GetData(*this->carddata, ADRESS_5_INDEX) + '\n';
		//カードデータより電話番号を示す文字列を取得する
		showdata += adm->GetData(*this->carddata, TELL_INDEX) + '\n';
		//カードデータより誕生日を示す文字列を取得する
		showdata += adm->GetData(*this->carddata, BIRTH_INDEX) + '\n';
		//カードデータより属性を示す文字列を取得する
		tmp = this->GetElem(ELEM_INDEX, 0, ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4);
		if (tmp == ELEM_NAME3) {
			this->label1->Text = gcnew String(tmp.c_str());
			this->Controls->Add(this->label1);
		}
		else if (tmp == ELEM_NAME4) {
			MessageBox::Show("危険人物です入館を拒否します。");
			throw gcnew System::Exception("危険人物です。");
		}
		showdata += tmp + '\n';
		//カードデータより権限を示す文字列を取得する
		showdata += this->GetElem(ADM_INDEX, 1, ADM_NAME1, ADM_NAME2, "", "") + '\n';
		//カードデータより職種を示す文字列を取得する
		showdata += this->GetElem(OCCUP_INDEX, 2, OCCUP_NAME1, OCCUP_NAME2, OCCUP_NAME3, OCCUP_NAME4) + '\n';
		//カードデータより部署を示す文字列を取得する
		showdata += this->GetElem(DEPART_INDEX, 3, DEPART_NAME1, DEPART_NAME2, DEPART_NAME3, DEPART_NAME4) + '\n';
		//カードデータより役職を示す文字列を取得する
		showdata += this->GetElem(POS_INDEX, 4, POS_NAME1, POS_NAME2, POS_NAME3, POS_NAME4) + '\n';
		//カードデータより年月を示す文字列を取得する
		showdata += this->ConvYears(*this->carddata) + '\n';
		//カードデータより日時分を示す文字列を取得する
		showdata += this->ConvTimes(*this->carddata) + '\n';
		//メイン画面へ文字列を反映する
		this->labelInfomasion->Text = gcnew String(showdata.c_str());
		return;
	}
	catch (System::IndexOutOfRangeException^ e) {
		System::Console::WriteLine(e);
	}
}

/*概要:カードに格納された日時分情報を文字列に変換する関数
引数:std::vector<std::vcotr<unsigned char>> data:カードデータ
戻り値:std::vector<string> times:日時分を文字列に変換した配列
作成日:2017.10.16
作成者:K.Asada*/
private: std::string ConvTimes(std::vector<std::vector<unsigned char>> data) {
	try {
		std::string times = "";        //日時分を文字列に変換したものを格納するための配列
		ITOC gettimes;                         //カードデータの中にあるchar型の数値をunsigned int型に変換するための共有体
		int day = 0;                           //取得した日を格納する変数
		int hour = 0;                          //取得した時間を格納する変数
		int min = 0;                           //取得した分を格納する変数
		int timeindex = TIMES_1_INDEX;
		//カードデータにある日時分情報を走査していく
		for (int i = 1; data[timeindex][i * 2] != 0; i++) {
			//カードデータより日時分の上位8ビットを取得する
			gettimes.bytes[1] = data[timeindex][i * 2];
			//カードデータより日時分の下位8ビットを取得する
			gettimes.bytes[0] = data[timeindex][i * 2 + 1];
			//取得した日時分を日に変換する
			day = gettimes.num / 1440;
			//取得した日時分を時に変換する
			hour = gettimes.num / 60 - day * 24;
			//取得した日時分を分に変換する
			min = gettimes.num - 1440 * day - 60 * hour;
			//変換した日時分を連結して文字列を完成させる
			times += std::to_string(day) + "日" + std::to_string(hour) + "時" + std::to_string(min) + "分" + '\n';
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

/*概要:カードに格納された年月情報を文字列に変換するための関数
引数:std::vector<std::vector<unsigned char>> data:カードより取得したデータ
戻り値:std::vector<std::string> years:文字列に変換した年月
作成日:2017.10.16
作成者:K.Asada*/
private: std::string ConvYears(std::vector<std::vector<unsigned char>> data) {
	try {
		std::string years;        //変換した文字列を格納する
		ITOC getyears;            //カードより取得した年月をunsigned int型に変換するための共有体
		int year = 0;             //取得した年
		int month = 0;            //取得した月
		//カードデータより年月の上位8ビットを取得する
		getyears.bytes[1] = data[YEAR_INDEX][0];
		//カードデータより年月の下位8ビットを取得する
		getyears.bytes[0] = data[YEAR_INDEX][1];
		//年月を年に変換する
		year = getyears.num / 12;
		//年月を月に変換する
		month = getyears.num % 12;
		//変換した年月を連結して文字列を完成させる
		years = (std::to_string(year) + "年" + std::to_string(month) + "月");
		//変換した文字列を返却する
		return years;
	}
	catch (System::IndexOutOfRangeException^ e) {
		System::Console::WriteLine(e);
	}
}

/*概要:ユーザーの属性を判定し、それに応じた判定を返す関数
作成日：2017.10.10
作成者：K.Asada*/
private: System::Int32 CheckBit(char check) {
	System::Int32 countbit = 0;    //ビットがたっている場所
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
		 引数:int index:カードデータの中の対象のデータが格納されている場所
		     :int byte:対象が格納されている何バイト目に格納されているか
			 :string name1:1ビット目がたっているときに返す文字列
			 :string name2:2ビット目がたっているときに返す文字列
			 :string name3:3ビット目がたっているときに返す文字列
			 :string name4:4ビット目がたっているときに返す文字列
		戻り値:string name:ビット数に応じた文字列
		作成日:2017.10.17
		作成者:K.Asada*/
		 std::string GetElem(int index, int byte, std::string name1, std::string name2, std::string name3, std::string name4) {
			 std::string name = "";    //返却用の文字列
			 std::vector<std::vector<unsigned char>> data = *this->carddata;
			 int checkbit = 0;         //何ビット目がたっていたかを格納する変数
			 //何ビット目がたっているかを調べる
			 checkbit = this->CheckBit(data[index][byte]);
			 //何ビット目がたっていたかによって対応した文字列を返却する
			 switch (checkbit) {
		     //1の時は引数1の文字列を返す
			 case 1:name = name1;
				 break;
			 //2の時は引数2の文字列を返す
			 case 2:name = name2;
				 break;
			 //3の時は引数3の文字列を返す
			 case 3:name = name3;
				 break;
			 //4の時は引数4の文字列を返す
			 case 4:name = name4;
				 break;
			 }
			 //取得した文字列を返却する
			 return name;
		 }

		 /*String^型をstring型へ変換する関数
		 引数：String^ sys_string：変換対象の文字列
		 ：string& std_string：変換後の文字列の格納先
		 戻り値：なし
		 作成日：2017.10.10
		 作成者：K.Asada
		 */
		 void MarshalString(String^ sys_string, std::string& std_string) {
			 using namespace Runtime::InteropServices;
			 const char* chars =
				 (const char*)(Marshal::StringToHGlobalAnsi(sys_string)).ToPointer();
			 std_string = chars;
			 Marshal::FreeHGlobal(IntPtr((void*)chars));
			 return;
		 }
private: System::Void labelCauntion_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}

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
			this->labelCauntion->Dock = System::Windows::Forms::DockStyle::Top;
			this->labelCauntion->Location = System::Drawing::Point(0, 0);
			this->labelCauntion->Name = L"labelCauntion";
			this->labelCauntion->Size = System::Drawing::Size(67, 24);
			this->labelCauntion->TabIndex = 3;
			this->labelCauntion->Text = L"label1";
			this->labelCauntion->Click += gcnew System::EventHandler(this, &SDKmifare::labelCauntion_Click);
			// 
			// labelInfomasion
			// 
			this->labelInfomasion->AutoSize = true;
			this->labelInfomasion->Location = System::Drawing::Point(0, 386);
			this->labelInfomasion->Name = L"labelInfomasion";
			this->labelInfomasion->Size = System::Drawing::Size(67, 24);
			this->labelInfomasion->TabIndex = 4;
			this->labelInfomasion->Text = L"label2";
			// 
			// SDKmifare
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(1175, 465);
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
		std::string* Uid = new std::string("asada");				//読み込んだカードのユーザーID
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
		//MessageBox::Show(e);
	}
}

/*概要:退館ボタンを押したときのクリックイベント
作成日：2017.10.10
作成者：K.Asada*/
private: System::Void ButtonLeavingClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		AdmissionSystem* adm = new AdmissionSystem();    //カードとの接続を行ったりするクラスをインスタンス化
	//退館日を記録する
		adm->SetAdmissionTimes(*this->Uid);
		//カード待ち状態を示すダイアログを表示して、キャンセルが押されたら接続を終了する
		MessageBox::Show(Constants->SET_CARD_MESSAGE);
		//カードからデータを取得する関数を呼び出す
		adm->SetCardData(*this->Uid);
		//退館時のメッセージを表示する
		MessageBox::Show(Constants->LEAVE_MESSAGE);
		return;
	}
	catch (System::Exception^ e) {
		System::Console::Write(e);
	}
}


/*概要:入館ボタンをクリックしたときのイベント
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void ButtonAdmission(System::Object^  sender, System::EventArgs^  e) {
	try {
		AdmissionSystem* adm = new AdmissionSystem();    //カードとの接続を行ったりするクラスをインスタンス化
		PassForm^ pass = gcnew PassForm();               //パスワードを入力するフォームをインスタンス化
		std::string passtring = "";                      //パスワードを格納するための文字列
		//メッセージを表示する
		MessageBox::Show(Constants->SET_CARD_MESSAGE);
		//パスワード入力画面に移行する
		pass->ShowDialog();
		//受け取ったパスを変換するStringからstringへ
		this->MarshalString(pass->textBox1->Text, passtring);
		//カードデータを受信する関数を呼び出す
		adm->GetCardData(passtring);
		this->CreateDisp();
		//入館完了のメッセージを表示する
		MessageBox::Show(Constants->ENTER_MESSAGE);
		return;
	}
	catch (System::Exception^ e) {
	//	MessageBox::Show(e);
	}
}


/*概要:取得したデータをもとに画面に表示するラベルを作成する関数
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void CreateDisp() {
	std::string showdata = "";            //カードより取得した文字列を格納する
	std::vector<std::string>times;        //カードより取得した日時分を示す文字列を格納する
	showdata = (this->carddata[0], this->carddata[0].size());
	//カードデータより名前(漢字)を示す文字列を取得し、メイン画面に設定する
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	//カードデータより名前(フリガナ)を取得し、メイン画面に設定する
	showdata = (this->carddata[1], this->carddata[1].size());
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	//カードデータより住所を取得し、メイン画面に設定する
	showdata = ((this->carddata[3], this->carddata[3].size()) + (this->carddata[4], this->carddata[4].size()) + (this->carddata[5], this->carddata[5].size()) + (this->carddata[6], this->carddata[6].size()) + (this->carddata[7], this->carddata[7].size()));
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	//カードデータより電話番号を取得し、メイン画面に設定する
	showdata = (this->carddata[8], this->carddata[8].size());
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	//カードデータより誕生日を取得し、メイン画面に設定する
	showdata = (this->carddata[9], this->carddata[9].size());
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	//カードデータより年月を取得し、メイン画面に設定する
	this->labelInfomasion->Text = gcnew String(this->ConvYears(*this->carddata).c_str());
	//カードデータより日時分を取得する
	times = this->ConvTimes(*this->carddata);
	//メイン画面へ日時分を設定する
	for (int i = 0; i < times.size(); i++) {
		//メイン画面へ設定する
		this->labelInfomasion->Text = gcnew String(times[i].c_str());
	}
	return;
}

/*概要:カードに格納された日時分情報を文字列に変換する関数
引数:std::vector<std::vcotr<unsigned char>> data:カードデータ
戻り値:std::vector<string> times:日時分を文字列に変換した配列
作成日:2017.10.16
作成者:K.Asada*/
private: std::vector<std::string> ConvTimes(std::vector<std::vector<unsigned char>> data) {
	std::vector<std::string> times;        //日時分を文字列に変換したものを格納するための配列
	ITOC gettimes;                         //カードデータの中にあるchar型の数値をunsigned int型に変換するための共有体
	int day = 0;                           //取得した日を格納する変数
	int hour = 0;                          //取得した時間を格納する変数
	int min = 0;                           //取得した分を格納する変数
	//カードデータにある日時分情報を走査していく
	for (int i = 0; data[TIMES_1_INDEX][i * 2] != 0; i++) {
		//カードデータより日時分の上位8ビットを取得する
		gettimes.bytes[1] = data[TIMES_1_INDEX][i * 2];
		//カードデータより日時分の下位8ビットを取得する
		gettimes.bytes[0] = data[TIMES_1_INDEX][i * 2 + 1];
		//取得した日時分を日に変換する
		day = gettimes.num / 1440;
		//取得した日時分を時に変換する
		hour = gettimes.num / 60 - day * 24;
		//取得した日時分を分に変換する
		min = gettimes.num - 1440 * day - 24 * hour;
		//変換した日時分を連結して文字列を完成させる
		times.push_back(std::to_string(day) + "日" + std::to_string(hour) + "時" + std::to_string(min) + "分");
	}
	//変換した文字列を返却する
	return times;
}

/*概要:カードに格納された年月情報を文字列に変換するための関数
引数:std::vector<std::vector<unsigned char>> data:カードより取得したデータ
戻り値:std::vector<std::string> years:文字列に変換した年月
作成日:2017.10.16
作成者:K.Asada*/
private: std::string ConvYears(std::vector<std::vector<unsigned char>> data) {
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

/*概要:ユーザーの属性を判定し、それに応じた判定を返す関数
作成日：2017.10.10
作成者：K.Asada*/
private: System::Boolean CheckElement(unsigned char* elem) {
	int check = elem[CONSTANTGROUP::ELEM_INDEX];    //対象のユーザーの属性を取得する
	//ビット演算により属性に当たる部分まで移動する
	check = check >> 19;
	//何ビット目がたっているかを調べ、それに応じた判定を返す
	if(check & 1U){
		//19ビット目（要注意人物属性）のビットがたっているときは要注意人物としてtrueを返す
		check = true;
	}//20ビット目を調べる
	else if (check >> 1 & 1U) {
		//20ビット目（危険人物属性）のビットがたっているときは危険人物として例外をなげ、入館を拒否する
		throw gcnew System::Exception("危険人物です。入館を拒否します。");
	}
	//判定結果を返す
	return true;
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

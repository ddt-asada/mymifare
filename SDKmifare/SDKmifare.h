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
		public:SCARDHANDLE hCard = 0;		//読み込んだカードへのポインタ
		DWORD ActivProtocol = 0;//プロトコル
		std::string* Uid = new std::string("asada");				//読み込んだカードのユーザーID


/*概要:作成ボタンを押したときのクリックイベント
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void ButtonNewUserClick(System::Object^  sender, System::EventArgs^  e) {
	InputNewUserForm^ create = gcnew InputNewUserForm();    //新規ユーザー情報を入力するためのクラスをインスタンス化
	AdmissionSystem* adm;
	ConnectCard* con;
	//新規で作成する旨を伝える
	MessageBox::Show("新規で作成します。\n情報を入力してください。");
	//作成画面でOKが押されたらそのまま作成する
	if (create->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		std::string id;
		this->MarshalString(create->UID, id);
		//カード待ち状態にする
	//	this->hContext = con->WaitingCard();
		//カード待ち状態を示すダイアログを表示して、キャンセルが押されたら接続を終了する
		MessageBox::Show("カードをかざしてください。");
		//カードがかざされたらデータの取得に移る
		//this->ActivProtocol = con->CardConnect(this->hContext, this->hCard)
		//カードからデータを取得する関数を呼び出す
		adm->SetCardData(this->hContext, this->hCard, id);
	}//OK以外の時は作成が中断されたとする
	else {
		MessageBox::Show("操作が中断されました。");
	}
	return;
}

/*概要:退館ボタンを押したときのクリックイベント
作成日：2017.10.10
作成者：K.Asada*/
private: System::Void ButtonLeavingClick(System::Object^  sender, System::EventArgs^  e) {
	AdmissionSystem* adm;    //カードとの接続を行ったりするクラスをインスタンス化
	//退館日を記録する
	adm->SetAdmissionTimes(*this->Uid);
	//カード待ち状態を示すダイアログを表示して、キャンセルが押されたら接続を終了する
	MessageBox::Show("カードをかざしてください。");
	//カードがかざされたらデータの取得に移る
	//カードからデータを取得する関数を呼び出す
	adm->SetCardData(this->hContext, this->hCard, *this->Uid);
	MessageBox::Show("退館しました。");
	return;
}


/*概要:入館ボタンをクリックしたときのイベント
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void ButtonAdmission(System::Object^  sender, System::EventArgs^  e) {
	AdmissionSystem* adm = new AdmissionSystem();    //カードとの接続を行ったりするクラスをインスタンス化
	PassForm^ pass = gcnew PassForm();               //パスワードを入力するフォームをインスタンス化
	std::string passtring = "";                      //パスワードを格納するための文字列
	//メッセージを表示する
	MessageBox::Show("カードをかざしてください");
	//パスワード入力画面に移行する
	pass->ShowDialog();
	//受け取ったパスを変換するStringからstringへ
	this->MarshalString(pass->textBox1->Text, passtring);
	//カードデータを受信する関数を呼び出す
	adm->GetCardData(passtring);
	this->CreateDisp();
	return;
}


/*概要:取得したデータをもとに画面に表示するラベルを作成する関数
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void CreateDisp() {
//	std::string showdata = "";    //表示するための文字列を格納するための文字
	std::string test = *this->Uid;
	//ユーザIDより各種情報が格納されたテキストを開く
	std::ifstream ifs;
	//ストリームより文字列を取得する
	ifs.open(test.c_str());
	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char>last;
	std::string showdata(it, last);
	//文字列より表示するためのラベルを作成する
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	return;
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

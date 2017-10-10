#pragma once

#include "AdmissionSystem.h"
#include "InputNewUserForm.h"
#include <iostream>

namespace SDKmifare {

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
			// 
			// labelInfomasion
			// 
			this->labelInfomasion->AutoSize = true;
			this->labelInfomasion->Location = System::Drawing::Point(119, 446);
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
			this->ClientSize = System::Drawing::Size(1103, 739);
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
private:unsigned long hContext = 0;		//読み込んだリソースマネージャへのポインタ
		unsigned long hCard = NULL;		//読み込んだカードへのポインタ
		String^ Uid = "";				//読み込んだカードのユーザーID


/*概要:作成ボタンを押したときのクリックイベント
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void ButtonNewUserClick(System::Object^  sender, System::EventArgs^  e) {
	InputNewUserForm^ create = gcnew InputNewUserForm();    //新規ユーザー情報を入力するためのクラスをインスタンス化
	//新規で作成する旨を伝える
	MessageBox::Show("新規で作成します。\n情報を入力してください。");
	//新規情報ダイアログを開く
	create->ShowDialog();
	//カード待ち状態にする
	this->hContext = adm->WaittingCard();
	//カード待ち状態を示すダイアログを表示して、キャンセルが押されたら接続を終了する
	if (MessageBox::Show("カードをかざしてください。") == System::Windows::Forms::DialogResult::Cancel) {
		//操作が中断された旨を表示する
		MessageBox::Show("操作が中断されました。");
		//接続を終了する関数を呼び出す
		adm->EndConnect(this->hContext, this->hCard);
	}//カードがかざされたらデータの取得に移る
	else if (this->hCard = ::SCardConnect()) {
		//カードからデータを取得する関数を呼び出す
		adm->SetCardData(this->hContext, this->hCard, this->Uid);
	}
	return;
}

/*概要:退館ボタンを押したときのクリックイベント
作成日：2017.10.10
作成者：K.Asada*/
private: System::Void ButtonLeavingClick(System::Object^  sender, System::EventArgs^  e) {
	AdmissionSystem adm^ = gcnew AdmissionSystem();    //カードとの接続を行ったりするクラスをインスタンス化
	//カード待ち状態にしたうえで、リソースマネージャへのアドレスをメンバへ格納する
	this->hContext = adm->WaittingCard();
	//カード待ち状態を示すダイアログを表示して、キャンセルが押されたら接続を終了する
	if (MessageBox::Show("カードをかざしてください。") == System::Windows::Forms::DialogResult::Cancel) {
		//操作が中断された旨を表示する
		MessageBox::Show("操作が中断されました。");
		//接続を終了する関数を呼び出す
		adm->EndConnect(this->hContext, this->hCard);
	}//カードがかざされたらデータの取得に移る
	else if (this->hCard = ::SCardConnect()) {
		//カードからデータを取得する関数を呼び出す
		adm->SetCardData(this->hContext, this->hCard, this->Uid);
	}
	return;
}


/*概要:入館ボタンをクリックしたときのイベント
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void ButtonAdmission(System::Object^  sender, System::EventArgs^  e) {
	AdmissionSystem adm^ = gcnew AdmissionSystem();    //カードとの接続を行ったりするクラスをインスタンス化
	//カード待ち状態にしたうえで、リソースマネージャへのアドレスをメンバへ格納する
	this->hContext = adm->WaittingCard();
	//カード待ち状態を示すダイアログを表示して、キャンセルが押されたら接続を終了する
	if (MessageBox::Show("カードをかざしてください。") == System::Windows::Forms::DialogResult::Cancel) {
		//操作が中断された旨を表示する
		MessageBox::Show("操作が中断されました。");
		//接続を終了する関数を呼び出す
		adm->EndConnect(this->hContext, this->hCard);
	}//カードがかざされたらデータの取得に移る
	else if (this->hCard = ::SCardConnect()) {
		//カードからデータを取得する関数を呼び出す
		this->Uid = adm->GetCardData(this->hContext, this->hCard);
		//取得したデータから画面に表示する文字列を作成する
		this->CreateDisp();
	}
	return;
}


/*概要:取得したデータをもとに画面に表示するラベルを作成する関数
作成日:2017.10.10
作成者:K.Asada*/
private: System::Void CreateDisp() {
	std::string showdata = "";    //表示するための文字列を格納するための文字列
	//ユーザIDより各種情報が格納されたテキストを開く
	ifstream file(this->Uid.c_str());
	//ストリームより文字列を取得する
	file >> showdata;
	//文字列より表示するためのラベルを作成する
	this->labelInfomasion->Text = showdata;
	//ユーザの属性を判定する
	if (this->CheckElement(this->Carddata)) {
		//判定結果がtrueなら要注意人物である旨を表示する
		this->labelCauntion->Text = "要注意人物です。";
	}
	return;
}


/*概要:ユーザーの属性を判定し、それに応じた判定を返す関数
作成日：2017.10.10
作成者：K.Asada*/
private: System::Void CheckElement(unsigned char[] elem) {
	int check = elem[ELEMENT_INDEX];    //対象のユーザーの属性を取得する
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
	return check;
}
};
}

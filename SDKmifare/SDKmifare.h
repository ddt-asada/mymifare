#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "TimeCardForm.h"
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
	private: System::Windows::Forms::Button^  buttonEntering;
	private: System::Windows::Forms::Button^  buttonOutPut;
	protected:

	protected:

	private: System::Windows::Forms::Button^  buttonLeaving;
	private: System::Windows::Forms::Button^  buttonTimeList;




	private: System::Windows::Forms::Label^  labelInformation;
	private: System::Windows::Forms::Label^  labelCauntion;
	private: System::Windows::Forms::Label^  labelState;



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
			this->buttonEntering = (gcnew System::Windows::Forms::Button());
			this->buttonOutPut = (gcnew System::Windows::Forms::Button());
			this->buttonLeaving = (gcnew System::Windows::Forms::Button());
			this->buttonTimeList = (gcnew System::Windows::Forms::Button());
			this->labelInformation = (gcnew System::Windows::Forms::Label());
			this->labelCauntion = (gcnew System::Windows::Forms::Label());
			this->labelState = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonEntering
			// 
			this->buttonEntering->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonEntering->Location = System::Drawing::Point(12, 408);
			this->buttonEntering->Name = L"buttonEntering";
			this->buttonEntering->Size = System::Drawing::Size(269, 229);
			this->buttonEntering->TabIndex = 0;
			this->buttonEntering->Text = L"入館";
			this->buttonEntering->UseVisualStyleBackColor = true;
			this->buttonEntering->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonEnteringClick);
			// 
			// buttonOutPut
			// 
			this->buttonOutPut->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonOutPut->Location = System::Drawing::Point(562, 408);
			this->buttonOutPut->Name = L"buttonOutPut";
			this->buttonOutPut->Size = System::Drawing::Size(269, 229);
			this->buttonOutPut->TabIndex = 1;
			this->buttonOutPut->Text = L"書き出し";
			this->buttonOutPut->UseVisualStyleBackColor = true;
			this->buttonOutPut->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonWrittingClick);
			// 
			// buttonLeaving
			// 
			this->buttonLeaving->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonLeaving->Location = System::Drawing::Point(287, 408);
			this->buttonLeaving->Name = L"buttonLeaving";
			this->buttonLeaving->Size = System::Drawing::Size(269, 229);
			this->buttonLeaving->TabIndex = 2;
			this->buttonLeaving->Text = L"退館";
			this->buttonLeaving->UseVisualStyleBackColor = true;
			this->buttonLeaving->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonLeavingClick);
			// 
			// buttonTimeList
			// 
			this->buttonTimeList->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonTimeList->Location = System::Drawing::Point(837, 408);
			this->buttonTimeList->Name = L"buttonTimeList";
			this->buttonTimeList->Size = System::Drawing::Size(269, 229);
			this->buttonTimeList->TabIndex = 5;
			this->buttonTimeList->Text = L"日付一覧";
			this->buttonTimeList->UseVisualStyleBackColor = true;
			this->buttonTimeList->Click += gcnew System::EventHandler(this, &SDKmifare::buttonTimeListClick);
			// 
			// labelInformation
			// 
			this->labelInformation->AutoSize = true;
			this->labelInformation->Location = System::Drawing::Point(89, 53);
			this->labelInformation->Name = L"labelInformation";
			this->labelInformation->Size = System::Drawing::Size(138, 24);
			this->labelInformation->TabIndex = 6;
			this->labelInformation->Text = L"ユーザー情報";
			// 
			// labelCauntion
			// 
			this->labelCauntion->AutoSize = true;
			this->labelCauntion->Location = System::Drawing::Point(86, 140);
			this->labelCauntion->Name = L"labelCauntion";
			this->labelCauntion->Size = System::Drawing::Size(149, 24);
			this->labelCauntion->TabIndex = 7;
			this->labelCauntion->Text = L"警告メッセージ";
			// 
			// labelState
			// 
			this->labelState->AutoSize = true;
			this->labelState->Location = System::Drawing::Point(89, 213);
			this->labelState->Name = L"labelState";
			this->labelState->Size = System::Drawing::Size(106, 24);
			this->labelState->TabIndex = 8;
			this->labelState->Text = L"入館状態";
			// 
			// SDKmifare
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1182, 649);
			this->Controls->Add(this->labelState);
			this->Controls->Add(this->labelCauntion);
			this->Controls->Add(this->labelInformation);
			this->Controls->Add(this->buttonTimeList);
			this->Controls->Add(this->buttonLeaving);
			this->Controls->Add(this->buttonOutPut);
			this->Controls->Add(this->buttonEntering);
			this->Name = L"SDKmifare";
			this->Text = L"SDKmifare";
			this->Load += gcnew System::EventHandler(this, &SDKmifare::SDKmifareFormLoad);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		public:SCARDCONTEXT hContext = 0;        //リソースマネージャのアドレス
			   SCARDHANDLE hCard = 0;            //カードのアドレス
			   DWORD ActiveProtocol = 0;         //カードとの通信時に使うプロトコル
private:std::vector<std::vector<unsigned char>>* carddata = new std::vector<std::vector<unsigned char>>();           //取得したカードデータ
		std::string* uid = new std::string();    //ユーザーID
		CONSTANTGROUP::ConstantString^ Constants = gcnew CONSTANTGROUP::ConstantString();


/*概要:作成ボタンを押したときのクリックイベント
作成日:2017.10.10
作成者:K.Asada*/
		/*
private: System::Void ButtonNewUserClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		InputNewUserForm^ create = gcnew InputNewUserForm();    //新規ユーザー情報を入力するためのクラスをインスタンス化
		AdmissionSystem* adm = new AdmissionSystem();           //入館管理システム関連のクラスをインスタンス化
		//新規で作成する旨を伝える
		MessageBox::Show(Constants->NEW_MESSAGE);
		//作成画面でOKが押されたらそのまま作成する
		if (create->ShowDialog() != System::Windows::Forms::DialogResult::Cancel) {
			std::string id;
			this->MarshalString(create->UID, id);
			//カード待ち状態を示すダイアログを表示して、キャンセルが押されたら接続を終了する
			MessageBox::Show(Constants->SET_CARD_MESSAGE);
			//カードからデータを取得する関数を呼び出す
			adm->SetNewCardData(id);
			//作成完了のメッセージを表示する
			MessageBox::Show(Constants->FINISH_MESSAGE);
		}//OK以外の時は作成が中断されたとする
		else {
			MessageBox::Show(Constants->CANCEL_MESSAGE);
			throw gcnew System::Exception(Constants->CANCEL_MESSAGE);
		}
		//保存しているユーザーのカードデータを削除する
		this->carddata->clear();
		//ユーザー情報ラベルを初期化する
		this->labelInfomasion->Text = "";
		//属性ラベルを初期化する
		this->label1->Visible = false;
		//退館状態であることをメイン画面へ表示する
		this->labelCauntion->Text = "カードを作成しました。";
		return;
	}
	catch (System::Exception^ e) {
		MessageBox::Show(Constants->ERROR_MESSAGE);
		Console::Write(e);
	}
}*/

/*概要:退館ボタンを押したときのクリックイベント
作成日：2017.10.10
作成者：K.Asada
更新内容:新仕様実装に伴いイベントの内容を大幅に変更
更新日:2017.10.24
更新者:K.Asada*/
private: System::Void ButtonLeavingClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		AdmissionSystem* adm = new AdmissionSystem();   //関数群クラスをインスタンス化
		System::String^ check = "";    //退館状態を格納するための文字列
		//退館状態を調べる関数を呼び出す
		check = adm->CheckLeaveState(*this->carddata);
		//退館状態を調べて何らかの文字列が帰ってきた場合はメッセージを表示
		if (check != "") {
			//現在の退館状態がどうなっているかのメッセージを表示する
			MessageBox::Show(check);
			//退館するかどうかの確認メッセージを表示する
			if (MessageBox::Show(Constants->LEAVE_CHECK,"", System::Windows::Forms::MessageBoxButtons::OKCancel, System::Windows::Forms::MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::OK) {
				//キャンセルの時はエラーを投げて処理を中断する
				throw gcnew System::Exception(Constants->LEAVE_CANCEL);
			}
		}
		//退館時刻をカードに記録する関数を呼び出す
		adm->UpdateCardData(*this->carddata, this->hContext, this->hCard, this->ActiveProtocol, LEAVE_1_INDEX, END_INDEX);
		//退館完了のメッセージを表示する
		MessageBox::Show(Constants->LEAVE_MESSAGE);
		return;
	}
	catch (System::Exception^ e) {
		MessageBox::Show(Constants->ERROR_MESSAGE);
		System::Console::Write(e);
	}
}

		 /*概要:カードユーザーの属性を判定し、危険度ランクを判定する関数
		 引数:std::vector<std::vector<unsigned char>> data:カードより取得したデータ
		 戻り値:System::String^:ユーザーの危険度を示す文字列
		 作成日:2017.10.24
		 作成者:K.Asada*/
		 System::String^ CheckCauntion(std::vector<std::vector<unsigned char>> data) {
			 AdmissionSystem* adm = new AdmissionSystem();    //関数群クラスをインスタンス化
			 std::string check = ""; //判定結果の文字列
			 //属性を取得する関数を呼び出す
			 check = adm->GetElem(data[ELEM_INDEX][4], ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4);
			 //危険度を判定する
			 if (check == ELEM_NAME2) {
				 //危険人物を示す文字列であればメッセージを表示
				 MessageBox::Show("危険人物です。");
			 }
			 else if (check == ELEM_NAME3) {
				 //要注意人物を示す文字列であればメッセージを表示
				 MessageBox::Show("要注意人物です。");
			 }
			 //文字列を返却する
			 return gcnew String(check.c_str());
		 }

		 /*概要:カードユーザーの入退館状態を判定し、現在の状態を示す文字列を返却する関数
		 引数:std::vector<std::vector<unsigned char>>:カードより取得したデータ
		 戻り値:System::String^:入退館状態を示す文字列
		 作成日:2017.10.24
		 作成者:K.Asada*/

/*概要:取得したデータをもとに画面に表示するラベルを作成する関数
作成日:2017.10.10
作成者:K.Asada
更新内容:新仕様実装に伴い関数名、戻り値、引数を変更
引数:std::vector<std::vector<unsigned char>> data:ユーザー情報が格納されたカードデータ
戻り値:Sytem::String^ userdata:カードより取得したユーザー情報
更新日:2017.10.24
更新者:K.Asada*/
private: System::String^ GetUserInfo(std::vector<std::vector<unsigned char>> data) {
	try {
		std::string userinfo = "";            //カードより取得した文字列を格納する
		AdmissionSystem* adm = new AdmissionSystem();    //カードよりデータを取得するためのクラスをインスタンス化
		//カードデータより名前（漢字）を示す文字列を取得する
		userinfo += FIRST_NAME + adm->GetData(*this->carddata, NAME_INDEX) + '\n';
		//カードデータより名前（フリガナ）を示す文字列を取得する
		userinfo += LAST_NAME + adm->GetData(*this->carddata, KANA_INDEX) + '\n';
		//カードデータより住所を示す文字列を取得する
		userinfo += ADDRESS_LABEL + adm->GetData(*this->carddata, ADRESS_1_INDEX);
		//カードデータより住所を示す文字列を取得する
		userinfo += adm->GetData(*this->carddata, ADRESS_2_INDEX);
		//カードデータより住所を示す文字列を取得する
		userinfo += adm->GetData(*this->carddata, ADRESS_3_INDEX);
		//カードデータより住所を示す文字列を取得する
		userinfo += adm->GetData(*this->carddata, ADRESS_4_INDEX);
		//カードデータより住所を示す文字列を取得する
		userinfo += adm->GetData(*this->carddata, ADRESS_5_INDEX) + '\n';
		//カードデータより電話番号を示す文字列を取得する
		userinfo += TELL_LABEL + adm->GetData(*this->carddata, TELL_INDEX) + '\n';
		//カードデータより誕生日を示す文字列を取得する
		userinfo += BIRTH_LABEL + this->ConvBirth(data[BIRTH_INDEX]) + '\n';
		//属性を取得する
		userinfo += + ELEM_LABEL + adm->GetElem(data[ELEM_INDEX][4], ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4) + '\n';
		//カードデータより権限を示す文字列を取得する
		userinfo += ADM_LABEL + adm->GetElem(data[ADM_INDEX][5], ADM_NAME1, ADM_NAME2, "", "") + '\n';
		//カードデータより役職を示す文字列を取得する
		userinfo += OCCUP_LABEL + adm->GetElem(data[POS_INDEX][6], POS_NAME1, POS_NAME2, POS_NAME3, POS_NAME4) + '\n';
		userinfo += GROUP_LABEL + adm->GetElem(data[DEPART_INDEX][7] >> 4, "", OCCUP_NAME1, OCCUP_NAME2, OCCUP_NAME3) + '\n';
		userinfo += DEPART_LABEL + adm->GetElem(data[DEPART_INDEX][7], "", DEPART_NAME1, DEPART_NAME2, DEPART_NAME3) + '\n';
		return gcnew String(userinfo.c_str());
	}
	catch (System::Exception^ e) {
		System::Console::WriteLine(e);
		throw e;
	}
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

		 /*概要:カードデータより誕生日を取得するための関数
		 引数:vector<char> data:カードデータ
		 戻り値:std::string birth:誕生日を取得して文字列に変換したデータ
		 作成日:2017.10.19
		 作成者:K.Asada*/
		 std::string ConvBirth(std::vector<unsigned char> data) {
			 UITOC condata;    //char型をint型に変換する際に使用するバイト配列
			 int year = 0;                               //誕生年
			 int month = 0;                              //誕生月
			 int day = 0;                                //誕生日
			 std::string birth;                          //誕生年月日を示す文字列
			 //カードデータより誕生日を取得する
			 for (int i = 0; i < 4; i++) {
				 //1バイトずつ取得していく
				 condata.bytes[i] = data[i];
			 }
			 //誕生年を取得する
			 year = condata.num / 10000;
			 //誕生月を取得する
			 month = condata.num / 100 - year * 100;
			 //誕生日を取得する
			 day = condata.num - year * 10000 - month * 100;
			 //誕生年月日の文字列として組み立てる
			 birth = std::to_string(year) + "年" + std::to_string(month) + "月" + std::to_string(day) + "日";
			 //取得した文字列を返却する
			 return birth;
		 }


		 /*概要:入退館画面ロード時のイベント
		 作成日:2017.10.24
		 作成者:K.Asada*/
private: System::Void SDKmifareFormLoad(System::Object^  sender, System::EventArgs^  e) {
	try {
		AdmissionSystem* adm = new AdmissionSystem();    //関数群クラスをインスタンス化
		//かざされたカードからカードデータを取得する
		*this->carddata = adm->GetCardData(this->hContext, this->hCard, this->ActiveProtocol);
		//カードのユーザーがシステムに登録されているかをチェックする
		*this->uid = adm->CheckUser(*this->carddata);
		//カード内のデータとシステムに登録されているデータが一致するかをチェックする
		if (!adm->CollationFiledata(*this->carddata, *this->uid)) {
			//一致していなければエラーを投げる
			throw gcnew System::Exception("カードデータが不正です。");
		}
		//ユーザー情報をカードデータより取得する
		this->labelInformation->Text = this->GetUserInfo(*this->carddata);
		//ユーザーの危険度をチェックして対応した文字列を取得する
		this->labelCauntion->Text = this->CheckCauntion(*this->carddata);
		//ユーザーの入館状態を判定する
		this->labelState->Text = adm->CheckEnterState(*this->carddata);
		return;
	}
	catch (System::Exception^ e) {
		//コンソールにエラー内容を表示する
		Console::WriteLine(e);
	}
}

		 /*概要:入館ボタンクリック時のイベント
		 作成日:2017.10.24
		 作成者:K.Asada*/
private: System::Void ButtonEnteringClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		AdmissionSystem* adm = new AdmissionSystem();    //関数群クラスをインスタンス化
		System::String^ checkenter = "";    //入館状態を判定する文字列
		//入館状態を判定する
		checkenter = adm->CheckEnterState(*this->carddata);
		//空文字でないときはかくにんを行う
		if (checkenter != "") {
			//入館状態を表示する
			MessageBox::Show(checkenter);
			//入館処理を行うかを確認する
			if (MessageBox::Show(Constants->ENTER_CHECK, "", MessageBoxButtons::OKCancel, MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::OK) {
				//キャンセルの時はエラーを投げる
				throw gcnew System::Exception(Constants->ENTER_CANCEL);
			}
		}
		//入館したうえで、入館時間を更新する関数を呼び出す
		adm->UpdateCardData(*this->carddata, this->hContext, this->hCard, this->ActiveProtocol, TIMES_1_INDEX, END_INDEX);
		//入館官僚のメッセージを表示する
		MessageBox::Show(Constants->ENTER_MESSAGE);
		return;
	}
	catch (System::Exception^ e) {
		//エラー内容をコンソールに表示する
		Console::WriteLine(e);
	}
}

/*概要:書き込みボタンクリック時のイベント
作成日:2017.10.24
作成者:K.Asada*/
private: System::Void ButtonWrittingClick(System::Object^  sender, System::EventArgs^  e) {
	AdmissionSystem* adm = new AdmissionSystem();    //関数群クラスをインスタンス化
	std::string uid = "";    //ユーザーIDを格納するための文字列
	//カードへ全データを送信するための関数を呼び出す
	adm->SetCardData(uid, this->hContext, this->hCard, this->ActiveProtocol);
	return;
}

		 /*概要:日付一覧ボタンのクリックイベント
		 作成日:2017.10.24
		 作成者:K.Asada*/
private: System::Void buttonTimeListClick(System::Object^  sender, System::EventArgs^  e) {
	TimeCardForm^ time = gcnew TimeCardForm();    //日付一覧表示画面をインスタンス化する
	//日付一覧画面にカードより取得したユーザー情報を渡す
	*time->carddata = *this->carddata;
	//日付一覧画面を表示する
	time->ShowDialog();
	return;
}
};
}

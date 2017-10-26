#pragma once

#include "ConnectCard.h"
#include "SDKmifare.h"
#include "InputNewUserForm.h"
#include "AdmissionSystem.h"

namespace sdkmifare {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// AcceptanceForm の概要
	/// </summary>
	public ref class AcceptanceForm : public System::Windows::Forms::Form
	{
	public:
		AcceptanceForm(void)
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
		~AcceptanceForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(764, 418);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(236, 117);
			this->button1->TabIndex = 0;
			this->button1->Text = L"テスト用";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &AcceptanceForm::button1_Click);
			// 
			// AcceptanceForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1128, 580);
			this->Controls->Add(this->button1);
			this->Name = L"AcceptanceForm";
			this->Text = L"AcceptanceForm";
			this->Load += gcnew System::EventHandler(this, &AcceptanceForm::AcceptanceForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
		/*概要:フォームロード時のイベント
		作成日:2017.10.24
		作成者:K.Asada*/
	private: System::Void AcceptanceForm_Load(System::Object^  sender, System::EventArgs^  e) {
		this->InitPolling();
	}

			 /*概要:ポーリングを開始する関数
			 引数:なし
			 戻り値:なし
			 作成日:2017.10.24
			 作成者:K.Asada*/
			 System::Void InitPolling() {
				 SDKmifare^ sdk = gcnew SDKmifare();      //入退館画面をインスタンス化
				 ConnectCard* con = new ConnectCard();    //カード通信クラスをインスタンス化
				 SCARDCONTEXT hContext = 0;               //取得したリソースマネージャのアドレス
				 SCARDHANDLE hCard = 0;                   //取得したカードのアドレス
				 DWORD ActiveProtocol = 0;                //通信に使うプロトコル
				 //アプリが終了するまで無限ループさせる
				 for (;;) {
					 //ポーリングを開始する
					 con->BeginPolling(hContext, hCard, ActiveProtocol);
					 //入退館画面に取得したリソースマネージャを渡す
					 sdk->hContext = hContext;
					 //入退館画面に取得したアドレスを渡す
					 sdk->hCard = hCard;
					 //入退館画面にプロトコルを渡す
					 sdk->ActiveProtocol = ActiveProtocol;
					 //入退館画面を表示する
					 sdk->ShowDialog();
					 //画面を閉じたらいったん通信を終了する
					 con->EndConnect(hContext, hCard);
				 }
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		InputNewUserForm^ user = gcnew InputNewUserForm();
		AdmissionSystem* adm = new AdmissionSystem();
		user->ShowDialog();
		//adm->UpdateFileDate("asada.txt");
	}
	};
}

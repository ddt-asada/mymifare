#pragma once

#include "ConnectCard.h"
#include "SDKmifare.h"

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
			this->SuspendLayout();
			// 
			// AcceptanceForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1128, 580);
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
	};
}

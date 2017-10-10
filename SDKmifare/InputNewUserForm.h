#pragma once

namespace sdkmifare {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// InputNewUserForm の概要
	/// </summary>
	public ref class InputNewUserForm : public System::Windows::Forms::Form
	{
	public:
		InputNewUserForm(void)
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
		~InputNewUserForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBoxNameaKana;
	protected:
	private: System::Windows::Forms::TextBox^  textBoxAdm;
	private: System::Windows::Forms::TextBox^  textBoxElement;
	private: System::Windows::Forms::TextBox^  textBoxPASS;
	private: System::Windows::Forms::TextBox^  textBoxUID;
	private: System::Windows::Forms::TextBox^  textBoxAdress;
	private: System::Windows::Forms::TextBox^  textBoxName;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Button^  buttonCancel;

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
			this->textBoxNameaKana = (gcnew System::Windows::Forms::TextBox());
			this->textBoxAdm = (gcnew System::Windows::Forms::TextBox());
			this->textBoxElement = (gcnew System::Windows::Forms::TextBox());
			this->textBoxPASS = (gcnew System::Windows::Forms::TextBox());
			this->textBoxUID = (gcnew System::Windows::Forms::TextBox());
			this->textBoxAdress = (gcnew System::Windows::Forms::TextBox());
			this->textBoxName = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBoxNameaKana
			// 
			this->textBoxNameaKana->Location = System::Drawing::Point(353, 56);
			this->textBoxNameaKana->Name = L"textBoxNameaKana";
			this->textBoxNameaKana->Size = System::Drawing::Size(409, 31);
			this->textBoxNameaKana->TabIndex = 0;
			// 
			// textBoxAdm
			// 
			this->textBoxAdm->Location = System::Drawing::Point(353, 288);
			this->textBoxAdm->Name = L"textBoxAdm";
			this->textBoxAdm->Size = System::Drawing::Size(409, 31);
			this->textBoxAdm->TabIndex = 12;
			// 
			// textBoxElement
			// 
			this->textBoxElement->Location = System::Drawing::Point(353, 240);
			this->textBoxElement->Name = L"textBoxElement";
			this->textBoxElement->Size = System::Drawing::Size(409, 31);
			this->textBoxElement->TabIndex = 13;
			// 
			// textBoxPASS
			// 
			this->textBoxPASS->Location = System::Drawing::Point(353, 195);
			this->textBoxPASS->Name = L"textBoxPASS";
			this->textBoxPASS->Size = System::Drawing::Size(409, 31);
			this->textBoxPASS->TabIndex = 14;
			// 
			// textBoxUID
			// 
			this->textBoxUID->Location = System::Drawing::Point(353, 147);
			this->textBoxUID->Name = L"textBoxUID";
			this->textBoxUID->Size = System::Drawing::Size(409, 31);
			this->textBoxUID->TabIndex = 15;
			// 
			// textBoxAdress
			// 
			this->textBoxAdress->Location = System::Drawing::Point(353, 98);
			this->textBoxAdress->Name = L"textBoxAdress";
			this->textBoxAdress->Size = System::Drawing::Size(409, 31);
			this->textBoxAdress->TabIndex = 16;
			// 
			// textBoxName
			// 
			this->textBoxName->Location = System::Drawing::Point(353, 12);
			this->textBoxName->Name = L"textBoxName";
			this->textBoxName->Size = System::Drawing::Size(409, 31);
			this->textBoxName->TabIndex = 17;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(271, 33);
			this->label1->TabIndex = 18;
			this->label1->Text = L"ユーザー名(漢字)";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label9->Location = System::Drawing::Point(12, 284);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(79, 33);
			this->label9->TabIndex = 26;
			this->label9->Text = L"権限";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label10->Location = System::Drawing::Point(12, 236);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(79, 33);
			this->label10->TabIndex = 27;
			this->label10->Text = L"属性";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label11->Location = System::Drawing::Point(12, 191);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(175, 33);
			this->label11->TabIndex = 28;
			this->label11->Text = L"パスワード";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label12->Location = System::Drawing::Point(12, 143);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(175, 33);
			this->label12->TabIndex = 29;
			this->label12->Text = L"ユーザーID";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label13->Location = System::Drawing::Point(12, 94);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(271, 33);
			this->label13->TabIndex = 30;
			this->label13->Text = L"住所（半角カナ）";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label14->Location = System::Drawing::Point(12, 52);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(335, 33);
			this->label14->TabIndex = 31;
			this->label14->Text = L"ユーザー名(ふりがな)";
			// 
			// buttonOK
			// 
			this->buttonOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->buttonOK->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonOK->Location = System::Drawing::Point(18, 349);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(369, 89);
			this->buttonOK->TabIndex = 32;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonCancel->Location = System::Drawing::Point(393, 349);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(369, 89);
			this->buttonCancel->TabIndex = 33;
			this->buttonCancel->Text = L"キャンセル";
			this->buttonCancel->UseVisualStyleBackColor = true;
			// 
			// InputNewUserForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(769, 450);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBoxName);
			this->Controls->Add(this->textBoxAdress);
			this->Controls->Add(this->textBoxUID);
			this->Controls->Add(this->textBoxPASS);
			this->Controls->Add(this->textBoxElement);
			this->Controls->Add(this->textBoxAdm);
			this->Controls->Add(this->textBoxNameaKana);
			this->Name = L"InputNewUserForm";
			this->Text = L"InputNewUserForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &InputNewUserForm::InputNewUserForm_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	/*概要:新規作成画面を閉じるときのイベント
	作成日:2017.10.10
	作成者:K.Asada*/
	private: System::Void InputNewUserForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
/*		std::string filename = "";    //ファイル名を格納するための文字列
		std::string setdata = "";     //テキストに格納するための文字列
		//ユーザーIDをファイル名として取得する
		filename = this->textBoxUID->Text;
		//名前を取得する、終わりで改行したいので改行文字列もセットにする
		setdata = this->textBoxName->Text + '\n';
		//名前のふりがなを取得する
		setdata = this->textBoxNameaKana->Text + '\n';
		//パスワードを取得する
		setdata = this->textBoxPASS->Text + '\n';
		//属性を取得する
		setdata = this->textBoxElement->Text + '\n';
		//権限を取得する
		setdata = this->textBoxAdm->Text + '\n';
		//住所を取得する
		setdata = this->textBoxAdress->Text + '\n';
		//ユーザーIDで新規にファイルを作成する
		ifstream newuser(filename);
		//作成したテキストファイルの中にユーザー情報を格納する
		newuser << setdata;*/
		return;
	}
};
}

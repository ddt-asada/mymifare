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
	private: System::Windows::Forms::TextBox^  textBoxNameKana;
	protected:

	protected:


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
	private: System::Windows::Forms::ComboBox^  comboBoxElement;
	private: System::Windows::Forms::ComboBox^  comboBoxAdmin;
	private: System::Windows::Forms::ComboBox^  comboBoxOccupations;
	private: System::Windows::Forms::ComboBox^  comboBoxPosition;
	private: System::Windows::Forms::ComboBox^  comboBoxDepart;
	private: System::Windows::Forms::ComboBox^  comboBox6;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;

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
			this->textBoxNameKana = (gcnew System::Windows::Forms::TextBox());
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
			this->comboBoxElement = (gcnew System::Windows::Forms::ComboBox());
			this->comboBoxAdmin = (gcnew System::Windows::Forms::ComboBox());
			this->comboBoxOccupations = (gcnew System::Windows::Forms::ComboBox());
			this->comboBoxPosition = (gcnew System::Windows::Forms::ComboBox());
			this->comboBoxDepart = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox6 = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBoxNameKana
			// 
			this->textBoxNameKana->Location = System::Drawing::Point(484, 54);
			this->textBoxNameKana->Name = L"textBoxNameKana";
			this->textBoxNameKana->Size = System::Drawing::Size(409, 31);
			this->textBoxNameKana->TabIndex = 2;
			// 
			// textBoxPASS
			// 
			this->textBoxPASS->Location = System::Drawing::Point(484, 193);
			this->textBoxPASS->Name = L"textBoxPASS";
			this->textBoxPASS->Size = System::Drawing::Size(409, 31);
			this->textBoxPASS->TabIndex = 5;
			// 
			// textBoxUID
			// 
			this->textBoxUID->Location = System::Drawing::Point(484, 145);
			this->textBoxUID->Name = L"textBoxUID";
			this->textBoxUID->Size = System::Drawing::Size(409, 31);
			this->textBoxUID->TabIndex = 4;
			// 
			// textBoxAdress
			// 
			this->textBoxAdress->Location = System::Drawing::Point(484, 96);
			this->textBoxAdress->Name = L"textBoxAdress";
			this->textBoxAdress->Size = System::Drawing::Size(409, 31);
			this->textBoxAdress->TabIndex = 3;
			// 
			// textBoxName
			// 
			this->textBoxName->Location = System::Drawing::Point(484, 10);
			this->textBoxName->Name = L"textBoxName";
			this->textBoxName->Size = System::Drawing::Size(409, 31);
			this->textBoxName->TabIndex = 1;
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
			this->buttonOK->Location = System::Drawing::Point(12, 596);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(460, 89);
			this->buttonOK->TabIndex = 12;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &InputNewUserForm::buttonOK_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonCancel->Location = System::Drawing::Point(485, 596);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(408, 89);
			this->buttonCancel->TabIndex = 13;
			this->buttonCancel->Text = L"キャンセル";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &InputNewUserForm::buttonCancel_Click);
			// 
			// comboBoxElement
			// 
			this->comboBoxElement->FormattingEnabled = true;
			this->comboBoxElement->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"属性1", L"属性2" });
			this->comboBoxElement->Location = System::Drawing::Point(484, 238);
			this->comboBoxElement->Name = L"comboBoxElement";
			this->comboBoxElement->Size = System::Drawing::Size(409, 32);
			this->comboBoxElement->TabIndex = 6;
			// 
			// comboBoxAdmin
			// 
			this->comboBoxAdmin->FormattingEnabled = true;
			this->comboBoxAdmin->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"権限1", L"権限2" });
			this->comboBoxAdmin->Location = System::Drawing::Point(484, 286);
			this->comboBoxAdmin->Name = L"comboBoxAdmin";
			this->comboBoxAdmin->Size = System::Drawing::Size(409, 32);
			this->comboBoxAdmin->TabIndex = 7;
			// 
			// comboBoxOccupations
			// 
			this->comboBoxOccupations->FormattingEnabled = true;
			this->comboBoxOccupations->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"職種1", L"職種2" });
			this->comboBoxOccupations->Location = System::Drawing::Point(484, 334);
			this->comboBoxOccupations->Name = L"comboBoxOccupations";
			this->comboBoxOccupations->Size = System::Drawing::Size(409, 32);
			this->comboBoxOccupations->TabIndex = 8;
			// 
			// comboBoxPosition
			// 
			this->comboBoxPosition->FormattingEnabled = true;
			this->comboBoxPosition->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"役職1", L"役職2" });
			this->comboBoxPosition->Location = System::Drawing::Point(484, 430);
			this->comboBoxPosition->Name = L"comboBoxPosition";
			this->comboBoxPosition->Size = System::Drawing::Size(409, 32);
			this->comboBoxPosition->TabIndex = 10;
			// 
			// comboBoxDepart
			// 
			this->comboBoxDepart->FormattingEnabled = true;
			this->comboBoxDepart->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"部署1", L"部署2" });
			this->comboBoxDepart->Location = System::Drawing::Point(484, 382);
			this->comboBoxDepart->Name = L"comboBoxDepart";
			this->comboBoxDepart->Size = System::Drawing::Size(409, 32);
			this->comboBoxDepart->TabIndex = 9;
			// 
			// comboBox6
			// 
			this->comboBox6->FormattingEnabled = true;
			this->comboBox6->Location = System::Drawing::Point(485, 478);
			this->comboBox6->Name = L"comboBox6";
			this->comboBox6->Size = System::Drawing::Size(409, 32);
			this->comboBox6->TabIndex = 11;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label2->Location = System::Drawing::Point(12, 428);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(79, 33);
			this->label2->TabIndex = 40;
			this->label2->Text = L"役職";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label3->Location = System::Drawing::Point(12, 380);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(79, 33);
			this->label3->TabIndex = 41;
			this->label3->Text = L"部署";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label4->Location = System::Drawing::Point(12, 332);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(79, 33);
			this->label4->TabIndex = 42;
			this->label4->Text = L"職種";
			// 
			// InputNewUserForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(905, 697);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->comboBox6);
			this->Controls->Add(this->comboBoxDepart);
			this->Controls->Add(this->comboBoxPosition);
			this->Controls->Add(this->comboBoxOccupations);
			this->Controls->Add(this->comboBoxAdmin);
			this->Controls->Add(this->comboBoxElement);
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
			this->Controls->Add(this->textBoxNameKana);
			this->Name = L"InputNewUserForm";
			this->Text = L"InputNewUserForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &InputNewUserForm::InputNewUserForm_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		public:String^ UID = "";
	/*概要:新規作成画面を閉じるときのイベント
	作成日:2017.10.10
	作成者:K.Asada*/
	private: System::Void InputNewUserForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
//		std::string filename = "";    //ファイル名を格納するための文字列
	//	std::string setdata = "";     //テキストに格納するための文字
	}
private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
	System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(this->textBoxUID->Text);
	writer->Write(this->SetByte(this->textBoxName->Text, 16));
	writer->Write(this->SetByte(this->textBoxNameKana->Text, 16));
	writer->Write(this->SetByte(this->textBoxUID->Text, 8));
	writer->Write(this->SetByte(this->textBoxPASS->Text, 8));
	writer->WriteLine(this->SetByte(this->textBoxAdress->Text, 80));
	writer->Write(this->SetByte(Convert::ToString(this->comboBoxElement->SelectedIndex, 2), 4 * 8));
	writer->Write(this->SetByte(Convert::ToString(this->comboBoxAdmin->SelectedIndex, 2), 4 * 8));
	writer->Write(this->SetByte(Convert::ToString(this->comboBoxOccupations->SelectedIndex, 2), 4 * 8));
	writer->Write(this->SetByte(Convert::ToString(this->comboBoxDepart->SelectedIndex, 2), 3 * 8));
	writer->Write(this->SetByte(Convert::ToString(this->comboBoxPosition->SelectedIndex, 2), 1 * 8));
	writer->Close();
	this->Close();
}

private:System::String^ SetByte(String^ data, Int32 setbyte) {
	System::Text::Encoding^ e = System::Text::Encoding::GetEncoding("shift_jis");
	Int32 bytecount = e->GetByteCount(data);
	for (; bytecount < setbyte; bytecount++) {
		data += " ";
	}
	return data;
}
private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}
};
}

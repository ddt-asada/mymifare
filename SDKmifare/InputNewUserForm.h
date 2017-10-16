#pragma once

#include "CONSTANTS.h"

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
	private: System::Windows::Forms::Label^  labelBirthDay;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBoxTELL1;
	private: System::Windows::Forms::TextBox^  textBoxTELL2;
	private: System::Windows::Forms::TextBox^  textBoxTELL3;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBoxBirthDay;
	private: System::Windows::Forms::TextBox^  textBoxBirthMonth;
	private: System::Windows::Forms::TextBox^  textBoxBirthYear;
	private: System::Windows::Forms::Label^  label16;

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
			this->labelBirthDay = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBoxTELL1 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxTELL2 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxTELL3 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBoxBirthDay = (gcnew System::Windows::Forms::TextBox());
			this->textBoxBirthMonth = (gcnew System::Windows::Forms::TextBox());
			this->textBoxBirthYear = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBoxNameKana
			// 
			this->textBoxNameKana->Location = System::Drawing::Point(485, 56);
			this->textBoxNameKana->Name = L"textBoxNameKana";
			this->textBoxNameKana->Size = System::Drawing::Size(409, 31);
			this->textBoxNameKana->TabIndex = 2;
			// 
			// textBoxPASS
			// 
			this->textBoxPASS->Location = System::Drawing::Point(479, 287);
			this->textBoxPASS->Name = L"textBoxPASS";
			this->textBoxPASS->Size = System::Drawing::Size(409, 31);
			this->textBoxPASS->TabIndex = 5;
			// 
			// textBoxUID
			// 
			this->textBoxUID->Location = System::Drawing::Point(479, 239);
			this->textBoxUID->Name = L"textBoxUID";
			this->textBoxUID->Size = System::Drawing::Size(409, 31);
			this->textBoxUID->TabIndex = 4;
			// 
			// textBoxAdress
			// 
			this->textBoxAdress->Location = System::Drawing::Point(485, 98);
			this->textBoxAdress->Name = L"textBoxAdress";
			this->textBoxAdress->Size = System::Drawing::Size(409, 31);
			this->textBoxAdress->TabIndex = 3;
			// 
			// textBoxName
			// 
			this->textBoxName->Location = System::Drawing::Point(485, 12);
			this->textBoxName->Name = L"textBoxName";
			this->textBoxName->Size = System::Drawing::Size(409, 31);
			this->textBoxName->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label1->Location = System::Drawing::Point(13, 11);
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
			this->label9->Location = System::Drawing::Point(7, 375);
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
			this->label10->Location = System::Drawing::Point(7, 327);
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
			this->label11->Location = System::Drawing::Point(7, 285);
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
			this->label12->Location = System::Drawing::Point(7, 237);
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
			this->label13->Location = System::Drawing::Point(13, 96);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(79, 33);
			this->label13->TabIndex = 30;
			this->label13->Text = L"住所";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label14->Location = System::Drawing::Point(13, 54);
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
			this->buttonOK->Location = System::Drawing::Point(13, 610);
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
			this->buttonCancel->Location = System::Drawing::Point(479, 610);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(416, 89);
			this->buttonCancel->TabIndex = 13;
			this->buttonCancel->Text = L"キャンセル";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &InputNewUserForm::buttonCancel_Click);
			// 
			// comboBoxElement
			// 
			this->comboBoxElement->FormattingEnabled = true;
			this->comboBoxElement->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"属性1", L"属性2" });
			this->comboBoxElement->Location = System::Drawing::Point(479, 329);
			this->comboBoxElement->Name = L"comboBoxElement";
			this->comboBoxElement->Size = System::Drawing::Size(409, 32);
			this->comboBoxElement->TabIndex = 6;
			// 
			// comboBoxAdmin
			// 
			this->comboBoxAdmin->FormattingEnabled = true;
			this->comboBoxAdmin->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"権限1", L"権限2" });
			this->comboBoxAdmin->Location = System::Drawing::Point(479, 377);
			this->comboBoxAdmin->Name = L"comboBoxAdmin";
			this->comboBoxAdmin->Size = System::Drawing::Size(409, 32);
			this->comboBoxAdmin->TabIndex = 7;
			// 
			// comboBoxOccupations
			// 
			this->comboBoxOccupations->FormattingEnabled = true;
			this->comboBoxOccupations->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"職種1", L"職種2" });
			this->comboBoxOccupations->Location = System::Drawing::Point(479, 425);
			this->comboBoxOccupations->Name = L"comboBoxOccupations";
			this->comboBoxOccupations->Size = System::Drawing::Size(409, 32);
			this->comboBoxOccupations->TabIndex = 8;
			// 
			// comboBoxPosition
			// 
			this->comboBoxPosition->FormattingEnabled = true;
			this->comboBoxPosition->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"役職1", L"役職2" });
			this->comboBoxPosition->Location = System::Drawing::Point(479, 521);
			this->comboBoxPosition->Name = L"comboBoxPosition";
			this->comboBoxPosition->Size = System::Drawing::Size(409, 32);
			this->comboBoxPosition->TabIndex = 10;
			// 
			// comboBoxDepart
			// 
			this->comboBoxDepart->FormattingEnabled = true;
			this->comboBoxDepart->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"部署1", L"部署2" });
			this->comboBoxDepart->Location = System::Drawing::Point(479, 473);
			this->comboBoxDepart->Name = L"comboBoxDepart";
			this->comboBoxDepart->Size = System::Drawing::Size(409, 32);
			this->comboBoxDepart->TabIndex = 9;
			// 
			// comboBox6
			// 
			this->comboBox6->FormattingEnabled = true;
			this->comboBox6->Location = System::Drawing::Point(480, 569);
			this->comboBox6->Name = L"comboBox6";
			this->comboBox6->Size = System::Drawing::Size(409, 32);
			this->comboBox6->TabIndex = 11;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label2->Location = System::Drawing::Point(7, 519);
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
			this->label3->Location = System::Drawing::Point(7, 471);
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
			this->label4->Location = System::Drawing::Point(7, 423);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(79, 33);
			this->label4->TabIndex = 42;
			this->label4->Text = L"職種";
			// 
			// labelBirthDay
			// 
			this->labelBirthDay->AutoSize = true;
			this->labelBirthDay->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->labelBirthDay->Location = System::Drawing::Point(13, 144);
			this->labelBirthDay->Name = L"labelBirthDay";
			this->labelBirthDay->Size = System::Drawing::Size(143, 33);
			this->labelBirthDay->TabIndex = 43;
			this->labelBirthDay->Text = L"生年月日";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label6->Location = System::Drawing::Point(13, 190);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(79, 33);
			this->label6->TabIndex = 44;
			this->label6->Text = L"TELL";
			// 
			// textBoxTELL1
			// 
			this->textBoxTELL1->Location = System::Drawing::Point(479, 194);
			this->textBoxTELL1->Name = L"textBoxTELL1";
			this->textBoxTELL1->Size = System::Drawing::Size(84, 31);
			this->textBoxTELL1->TabIndex = 45;
			// 
			// textBoxTELL2
			// 
			this->textBoxTELL2->Location = System::Drawing::Point(606, 194);
			this->textBoxTELL2->Name = L"textBoxTELL2";
			this->textBoxTELL2->Size = System::Drawing::Size(120, 31);
			this->textBoxTELL2->TabIndex = 46;
			// 
			// textBoxTELL3
			// 
			this->textBoxTELL3->Location = System::Drawing::Point(769, 194);
			this->textBoxTELL3->Name = L"textBoxTELL3";
			this->textBoxTELL3->Size = System::Drawing::Size(118, 31);
			this->textBoxTELL3->TabIndex = 47;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label5->Location = System::Drawing::Point(732, 194);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(31, 33);
			this->label5->TabIndex = 48;
			this->label5->Text = L"-";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label7->Location = System::Drawing::Point(569, 194);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(31, 33);
			this->label7->TabIndex = 49;
			this->label7->Text = L"-";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label8->Location = System::Drawing::Point(606, 148);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(47, 33);
			this->label8->TabIndex = 54;
			this->label8->Text = L"年";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label15->Location = System::Drawing::Point(732, 148);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(47, 33);
			this->label15->TabIndex = 53;
			this->label15->Text = L"月";
			// 
			// textBoxBirthDay
			// 
			this->textBoxBirthDay->Location = System::Drawing::Point(785, 152);
			this->textBoxBirthDay->Name = L"textBoxBirthDay";
			this->textBoxBirthDay->Size = System::Drawing::Size(62, 31);
			this->textBoxBirthDay->TabIndex = 52;
			// 
			// textBoxBirthMonth
			// 
			this->textBoxBirthMonth->Location = System::Drawing::Point(659, 150);
			this->textBoxBirthMonth->Name = L"textBoxBirthMonth";
			this->textBoxBirthMonth->Size = System::Drawing::Size(67, 31);
			this->textBoxBirthMonth->TabIndex = 51;
			// 
			// textBoxBirthYear
			// 
			this->textBoxBirthYear->Location = System::Drawing::Point(485, 148);
			this->textBoxBirthYear->Name = L"textBoxBirthYear";
			this->textBoxBirthYear->Size = System::Drawing::Size(115, 31);
			this->textBoxBirthYear->TabIndex = 50;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label16->Location = System::Drawing::Point(853, 150);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(47, 33);
			this->label16->TabIndex = 55;
			this->label16->Text = L"日";
			// 
			// InputNewUserForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(904, 710);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->textBoxBirthDay);
			this->Controls->Add(this->textBoxBirthMonth);
			this->Controls->Add(this->textBoxBirthYear);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBoxTELL3);
			this->Controls->Add(this->textBoxTELL2);
			this->Controls->Add(this->textBoxTELL1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->labelBirthDay);
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
		private:CONSTANTGROUP::ConstantString^ Constants = gcnew CONSTANTGROUP::ConstantString();
	/*概要:新規作成画面を閉じるときのイベント
	作成日:2017.10.10
	作成者:K.Asada*/
	private: System::Void InputNewUserForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
//		std::string filename = "";    //ファイル名を格納するための文字列
	//	std::string setdata = "";     //テキストに格納するための文字
	}
private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
	this->UID = this->textBoxUID->Text;
	System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter(this->textBoxUID->Text);
	writer->Write(this->SetByte(this->textBoxName->Text, 16));
	writer->Write(this->SetByte(this->textBoxNameKana->Text, 16));
	writer->Write(this->SetByte(this->textBoxUID->Text, 8));
	writer->Write(this->SetByte(this->textBoxPASS->Text, 8));
	writer->Write(this->SetByte(this->textBoxBirthYear->Text + "年" + this->textBoxBirthMonth->Text + "月" + this->textBoxBirthDay->Text + "日", 16));
	writer->Write(this->SetByte(this->textBoxTELL1->Text + this->textBoxTELL2->Text + this->textBoxTELL3->Text, 16));
	writer->Write(this->SetByte(this->textBoxAdress->Text, 80));
	writer->Write(this->SetByte(Convert::ToString(this->comboBoxElement->SelectedIndex), 1));
	writer->Write(this->SetByte(Convert::ToString(this->comboBoxAdmin->SelectedIndex), 1));
	writer->Write(this->SetByte(Convert::ToString(this->comboBoxOccupations->SelectedIndex), 1));
	writer->Write(this->SetByte(Convert::ToString(this->comboBoxDepart->SelectedIndex), 1));
	writer->Write(this->SetByte(Convert::ToString(this->comboBoxPosition->SelectedIndex), 12));
	writer->Close();
	this->Close();
}

private:System::String^ SetByte(String^ data, Int32 setbyte) {
	System::Text::Encoding^ e = System::Text::Encoding::GetEncoding("shift_jis");
	Int32 bytecount = e->GetByteCount(data);
	if (bytecount <= setbyte) {
		for (; bytecount < setbyte; bytecount++) {
			data += " ";
		}
	}
	else {
		throw gcnew System::Exception(Constants->OVER_ERROR_MESSAGE);
	}
	return data;
}
private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}
};
}

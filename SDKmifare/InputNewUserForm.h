#pragma once

#include "CONSTANTS.h"
#include <iostream>

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



	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown3;

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
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
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
			this->textBoxPASS->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->textBoxPASS->Location = System::Drawing::Point(479, 287);
			this->textBoxPASS->Name = L"textBoxPASS";
			this->textBoxPASS->Size = System::Drawing::Size(409, 31);
			this->textBoxPASS->TabIndex = 11;
			// 
			// textBoxUID
			// 
			this->textBoxUID->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->textBoxUID->Location = System::Drawing::Point(479, 239);
			this->textBoxUID->Name = L"textBoxUID";
			this->textBoxUID->Size = System::Drawing::Size(409, 31);
			this->textBoxUID->TabIndex = 10;
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
			this->label1->Text = L"名前（姓）";
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
			this->label14->Text = L"名前（名）";
			// 
			// buttonOK
			// 
			this->buttonOK->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonOK->Location = System::Drawing::Point(13, 610);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(460, 89);
			this->buttonOK->TabIndex = 17;
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
			this->buttonCancel->TabIndex = 18;
			this->buttonCancel->Text = L"キャンセル";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &InputNewUserForm::buttonCancel_Click);
			// 
			// comboBoxElement
			// 
			this->comboBoxElement->FormattingEnabled = true;
			this->comboBoxElement->Items->AddRange(gcnew cli::array< System::Object^  >(4) { Constants->CLI_ELEM_NAME1, Constants->CLI_ELEM_NAME2, Constants->CLI_ELEM_NAME3, Constants->CLI_ELEM_NAME4 });
			this->comboBoxElement->Location = System::Drawing::Point(479, 329);
			this->comboBoxElement->Name = L"comboBoxElement";
			this->comboBoxElement->Size = System::Drawing::Size(409, 32);
			this->comboBoxElement->Sorted = false;
			this->comboBoxElement->TabIndex = 12;
			// 
			// comboBoxAdmin
			// 
			this->comboBoxAdmin->FormattingEnabled = true;
			this->comboBoxAdmin->Items->AddRange(gcnew cli::array< System::Object^  >(2) { Constants->CLI_ADM_NAME1, Constants->CLI_ADM_NAME2 });
			this->comboBoxAdmin->Location = System::Drawing::Point(479, 377);
			this->comboBoxAdmin->Name = L"comboBoxAdmin";
			this->comboBoxAdmin->Size = System::Drawing::Size(409, 32);
			this->comboBoxAdmin->TabIndex = 13;
			// 
			// comboBoxOccupations
			// 
			this->comboBoxOccupations->FormattingEnabled = true;
			this->comboBoxOccupations->Items->AddRange(gcnew cli::array< System::Object^  >(4) {Constants->CLI_OCCUP_NAME1, Constants->CLI_OCCUP_NAME2, Constants->CLI_OCCUP_NAME3, Constants->
			CLI_OCCUP_NAME4});
			this->comboBoxOccupations->Location = System::Drawing::Point(479, 425);
			this->comboBoxOccupations->Name = L"comboBoxOccupations";
			this->comboBoxOccupations->Size = System::Drawing::Size(409, 32);
			this->comboBoxOccupations->TabIndex = 14;
			// 
			// comboBoxPosition
			// 
			this->comboBoxPosition->FormattingEnabled = true;
			this->comboBoxPosition->Items->AddRange(gcnew cli::array< System::Object^  >(4) { Constants->CLI_POS_NAME1, Constants->CLI_POS_NAME2, Constants->CLI_POS_NAME3, Constants->
			CLI_POS_NAME4});
			this->comboBoxPosition->Location = System::Drawing::Point(479, 521);
			this->comboBoxPosition->Name = L"comboBoxPosition";
			this->comboBoxPosition->Size = System::Drawing::Size(409, 32);
			this->comboBoxPosition->TabIndex = 16;
			// 
			// comboBoxDepart
			// 
			this->comboBoxDepart->FormattingEnabled = true;
			this->comboBoxDepart->Items->AddRange(gcnew cli::array< System::Object^  >(4) {Constants->CLI_DEPART_NAME1, Constants->CLI_DEPART_NAME2, Constants->CLI_DEPART_NAME3, Constants->
			CLI_DEPART_NAME4});
			this->comboBoxDepart->Location = System::Drawing::Point(479, 473);
			this->comboBoxDepart->Name = L"comboBoxDepart";
			this->comboBoxDepart->Size = System::Drawing::Size(409, 32);
			this->comboBoxDepart->TabIndex = 15;
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
			this->textBoxTELL1->TabIndex = 7;
			this->textBoxTELL1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &InputNewUserForm::textBoxTELL1_KeyPress);
			// 
			// textBoxTELL2
			// 
			this->textBoxTELL2->Location = System::Drawing::Point(606, 194);
			this->textBoxTELL2->Name = L"textBoxTELL2";
			this->textBoxTELL2->Size = System::Drawing::Size(120, 31);
			this->textBoxTELL2->TabIndex = 8;
			this->textBoxTELL2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &InputNewUserForm::textBoxTELL1_KeyPress);
			// 
			// textBoxTELL3
			// 
			this->textBoxTELL3->Location = System::Drawing::Point(769, 194);
			this->textBoxTELL3->Name = L"textBoxTELL3";
			this->textBoxTELL3->Size = System::Drawing::Size(118, 31);
			this->textBoxTELL3->TabIndex = 9;
			this->textBoxTELL3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &InputNewUserForm::textBoxTELL1_KeyPress);
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
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"ＭＳ ゴシック", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label16->Location = System::Drawing::Point(875, 150);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(47, 33);
			this->label16->TabIndex = 55;
			this->label16->Text = L"日";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(479, 149);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2017, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1900, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 31);
			this->numericUpDown1->TabIndex = 4;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2000, 0, 0, 0 });
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(785, 150);
			this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 31, 0, 0, 0 });
			this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(84, 31);
			this->numericUpDown2->TabIndex = 6;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->Location = System::Drawing::Point(654, 149);
			this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 12, 0, 0, 0 });
			this->numericUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(72, 31);
			this->numericUpDown3->TabIndex = 5;
			this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// InputNewUserForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(924, 724);
			this->Controls->Add(this->numericUpDown3);
			this->Controls->Add(this->numericUpDown2);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label15);
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
			this->comboBoxAdmin->SelectedIndex = 0;
			this->comboBoxDepart->SelectedIndex = 0;
			this->comboBoxElement->SelectedIndex = 0;
			this->comboBoxOccupations->SelectedIndex = 0;
			this->comboBoxPosition->SelectedIndex = 0;
			this->Name = L"InputNewUserForm";
			this->Text = L"InputNewUserForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		public:String^ UID = "";    //取得したユーザーID
		private:CONSTANTGROUP::ConstantString^ Constants = gcnew CONSTANTGROUP::ConstantString();    //定数クラスをインスタンス化

/*概要:OKボタンクリック時のイベント
*/
private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		System::String^ tmp = "";
		CONSTANTGROUP::UITOC itoc;    //int型のビットを変換するための共用体
		//ユーザーIDをメンバへ保管する
		this->UID = this->textBoxUID->Text;
		//ユーザIDが空の場合はファイルが生成できないのでその時点で処理を終了する
		if (this->UID == "") {
			MessageBox::Show(Constants->IDEMPTY_ERROR_MESSAGE);
			throw gcnew System::Exception(Constants->IDEMPTY_ERROR_MESSAGE);
		}
		//ユーザーIDを8バイト分書き出す
		tmp += "{\"" + Constants->CLI_UID_LABEL + "\":\"" + this->CheckByte(this->textBoxUID->Text, 16) + "\",";
		//名前(漢字)を16バイト分書き出す
		tmp += "\"" +Constants->CLI_FIRST_NAME + "\":\"" + this->CheckByte(this->textBoxName->Text, 16) + "\",";
		//名前(ふりがな)を16バイト分書き出す
		tmp += "\"" + Constants->CLI_LAST_NAME + "\":\"" + this->CheckByte(this->textBoxNameKana->Text, 16) + "\",";
		//パスワードを8バイト分書き出す
		tmp += "\"" + Constants->CLI_PASS_LABEL + "\":\"" + this->CheckByte(this->textBoxPASS->Text, 16) + "\",";
		//電話番号を16バイト分書き出す
		tmp += "\"" + Constants->CLI_TELL_LABEL + "\":\"" + this->CheckByte(this->textBoxTELL1->Text + this->textBoxTELL2->Text + this->textBoxTELL3->Text, 16) + "\",";
		//生年月日をint型に変換して保持する
		tmp += "\"" + Constants->CLI_IRTH_LABEL + "\":\"" + Convert::ToString(this->numericUpDown1->Value) + "年" + Convert::ToString(this->numericUpDown3->Value) + "月" + Convert::ToString(this->numericUpDown2->Value) + "日" + "\",";
		//属性をビットとして書き出す
		tmp += "\"" + Constants->CLI_ELEM_LABEL + "\":\"" + this->comboBoxElement->SelectedItem->ToString() + "\",";
		//権限をビットとして書き出す
		tmp += "\"" + Constants->CLI_ADM_LABEL + "\":\"" + this->comboBoxAdmin->SelectedItem->ToString() + "\",";
		//役職をビットとして書き出す
		tmp += "\"" + Constants->CLI_OCCUP_LABEL + "\":\"" + this->comboBoxPosition->SelectedItem->ToString() + "\",";
		//部署をビットとして書き出す
		tmp += "\"" + Constants->CLI_DEPART_LABEL + "\":\"" + this->comboBoxDepart->SelectedItem->ToString() + "\",";
		tmp += "\"" + Constants->CLI_GROUP_LABEL + "\":\"" + this->comboBoxOccupations->SelectedItem->ToString() + "\",";
		//住所が96バイトに収まっているかチェックする
		this->CheckByte(this->textBoxAdress->Text, 96);
		tmp += "\"" + Constants->CLI_ADDRESS_LABEL + "\":\"" + this->textBoxAdress->Text +"\",";
		tmp += "\"" + Constants->CLI_YEAR_LABEL + "\":\"\"," + "\"" + Constants->CLI_ENTER_LABEL + "\":\"\"," + "\"" + Constants->CLI_LEAVE_LABEL + "\":\"\"}";
		//ファイル入力クラスをインスタンス化
		System::IO::StreamWriter^ writer = gcnew System::IO::StreamWriter((this->textBoxUID->Text + ".txt"), false, System::Text::Encoding::GetEncoding("shift_jis"));
		//書き出す
		writer->Write(tmp);
		//入力を終了する
		writer->Close();
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		//ダイアログを閉じる
		this->Close();
		//return;
	}
	catch (System::Exception^ e) {
		//エラーが発生した旨を表示する
		MessageBox::Show(Constants->ERROR_MESSAGE);
		//コンソールにエラー内容を表示する
		Console::WriteLine(e);
	}
}


/*概要:指定したバイト数分の文字列を抜き出す関数
引数:String^ data:対象の文字列
    :INt32 beginbyte:抜き出しの始点のバイト数
	:int32 endbyte:抜き出しの終点のバイト数
戻り値:String^ bytestring:加工し終えた文字列
作成日:2017.10.20
作成者:K.Asada*/
public:System::String^ SetByte(String^ data, Int32 beginbyte, Int32 endbyte) {
	System::Text::Encoding^ e = System::Text::Encoding::GetEncoding("shift_jis");    //バイト数をカウントするためのクラスをインスタンス化
	array<Byte>^ bytes = e->GetBytes(data);     //文字列をバイト配列に変換する
	int index = 0;
	char getbyte[16] = { '\0' };                   //抜き出した文字列を格納するchar配列
	System::String^ bytestring = "";            //返却用の文字列
		//文字列を走査して加工する
		for (int i = beginbyte; i < endbyte && i < bytes->Length; i++) {
			//指定のバイト数分抜き出していく
			getbyte[index++] = bytes[i];
		}
	//加工し終えた文字列を返却する
	return bytestring = gcnew String(getbyte,0,16);
}


/*概要:指定したバイト数を超えていないかを確認するための関数
引数:String^ data:対象の文字列
    :Int32 checkbyte:指定のバイト数
戻り値:String^ data:確認を終えた文字列
作成日:2017.10.20
作成者:K.Asada*/
public:System::String^ CheckByte(String^ data, Int32 checkbyte) {
	System::Text::Encoding^ e = System::Text::Encoding::GetEncoding("shift_jis");    //バイト数をカウントするためのクラスをインスタンス化
	Int32 bytecount = e->GetByteCount(data);    //受け取った文字列をを"shift_jis"としてバイト数をカウントする
	//文字列のバイト数が指定のバイト数を超えていないかのチェック
	if (bytecount > checkbyte) {
		//画面にエラーをひょうじする
		MessageBox::Show(Constants->OVER_ERROR_MESSAGE);
		//文字数を超えている旨の例外を投げる
		throw gcnew System::Exception(Constants->OVER_ERROR_MESSAGE);
	}
	else if (data == "") {
		//画面にエラーを表示する
		MessageBox::Show(Constants->EMPTY_ERROR_MESSAGE);
		//情報未入力の例外を投げる
		throw gcnew System::Exception(Constants->EMPTY_ERROR_MESSAGE);
	}
	//判定を終えた文字列を返却する
	return data;
}

/*概要:キャンセルボタンクリック時のイベント
*/
private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	//何も行わずにダイアログを閉じる
	this->Close();
}

/*概要:テキストボックスにて数字以外を入力できないようにする関数
*/
private: System::Void textBoxTELL1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if ((e->KeyChar < 0x30) || (e->KeyChar > 0x39)) {
		if (e->KeyChar != '\b') {
			e->Handled = true;
		}
	}
}
};
}

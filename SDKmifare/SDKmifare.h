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
	/// SDKmifare �̊T�v
	/// </summary>
	public ref class SDKmifare : public System::Windows::Forms::Form
	{
	public:
		SDKmifare(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
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
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;



	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonAdmission = (gcnew System::Windows::Forms::Button());
			this->buttonNewUser = (gcnew System::Windows::Forms::Button());
			this->buttonLeaving = (gcnew System::Windows::Forms::Button());
			this->labelCauntion = (gcnew System::Windows::Forms::Label());
			this->labelInfomasion = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// buttonAdmission
			// 
			this->buttonAdmission->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonAdmission->Location = System::Drawing::Point(12, 119);
			this->buttonAdmission->Name = L"buttonAdmission";
			this->buttonAdmission->Size = System::Drawing::Size(269, 229);
			this->buttonAdmission->TabIndex = 0;
			this->buttonAdmission->Text = L"����";
			this->buttonAdmission->UseVisualStyleBackColor = true;
			this->buttonAdmission->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonAdmission);
			// 
			// buttonNewUser
			// 
			this->buttonNewUser->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonNewUser->Location = System::Drawing::Point(591, 119);
			this->buttonNewUser->Name = L"buttonNewUser";
			this->buttonNewUser->Size = System::Drawing::Size(269, 229);
			this->buttonNewUser->TabIndex = 1;
			this->buttonNewUser->Text = L"�쐬";
			this->buttonNewUser->UseVisualStyleBackColor = true;
			this->buttonNewUser->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonNewUserClick);
			// 
			// buttonLeaving
			// 
			this->buttonLeaving->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonLeaving->Location = System::Drawing::Point(301, 119);
			this->buttonLeaving->Name = L"buttonLeaving";
			this->buttonLeaving->Size = System::Drawing::Size(269, 229);
			this->buttonLeaving->TabIndex = 2;
			this->buttonLeaving->Text = L"�ފ�";
			this->buttonLeaving->UseVisualStyleBackColor = true;
			this->buttonLeaving->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonLeavingClick);
			// 
			// labelCauntion
			// 
			this->labelCauntion->AutoSize = true;
			this->labelCauntion->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->labelCauntion->Location = System::Drawing::Point(503, 351);
			this->labelCauntion->Name = L"labelCauntion";
			this->labelCauntion->Size = System::Drawing::Size(0, 53);
			this->labelCauntion->TabIndex = 3;
			// 
			// labelInfomasion
			// 
			this->labelInfomasion->AutoSize = true;
			this->labelInfomasion->BackColor = System::Drawing::Color::White;
			this->labelInfomasion->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->labelInfomasion->Location = System::Drawing::Point(12, 504);
			this->labelInfomasion->Name = L"labelInfomasion";
			this->labelInfomasion->Size = System::Drawing::Size(0, 33);
			this->labelInfomasion->TabIndex = 4;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Red;
			this->label1->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label1->Location = System::Drawing::Point(12, 433);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(134, 33);
			this->label1->TabIndex = 5;
			this->label1->Text = L"dawdada";
			this->label1->Visible = false;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->button1->Location = System::Drawing::Point(886, 119);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(269, 229);
			this->button1->TabIndex = 5;
			this->button1->Text = L"�^�C���J�[�h";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SDKmifare::button1_Click);
			// 
			// SDKmifare
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1182, 649);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
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
private:SCARDCONTEXT hContext = 0;		//�ǂݍ��񂾃��\�[�X�}�l�[�W���ւ̃|�C���^
		std::vector<std::vector<unsigned char>>* carddata = new std::vector<std::vector<unsigned char>>();           //�擾�����J�[�h�f�[�^
		CONSTANTGROUP::ConstantString^ Constants = gcnew CONSTANTGROUP::ConstantString();


/*�T�v:�쐬�{�^�����������Ƃ��̃N���b�N�C�x���g
�쐬��:2017.10.10
�쐬��:K.Asada*/
private: System::Void ButtonNewUserClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		InputNewUserForm^ create = gcnew InputNewUserForm();    //�V�K���[�U�[������͂��邽�߂̃N���X���C���X�^���X��
		AdmissionSystem* adm = new AdmissionSystem();           //���يǗ��V�X�e���֘A�̃N���X���C���X�^���X��
		//�V�K�ō쐬����|��`����
		MessageBox::Show(Constants->NEW_MESSAGE);
		//�쐬��ʂ�OK�������ꂽ�炻�̂܂܍쐬����
		if (create->ShowDialog() != System::Windows::Forms::DialogResult::Cancel) {
			std::string id;
			this->MarshalString(create->UID, id);
			//�J�[�h�҂���Ԃ������_�C�A���O��\�����āA�L�����Z���������ꂽ��ڑ����I������
			MessageBox::Show(Constants->SET_CARD_MESSAGE);
			//�J�[�h����f�[�^���擾����֐����Ăяo��
			adm->SetNewCardData(id);
			//�쐬�����̃��b�Z�[�W��\������
			MessageBox::Show(Constants->FINISH_MESSAGE);
		}//OK�ȊO�̎��͍쐬�����f���ꂽ�Ƃ���
		else {
			MessageBox::Show(Constants->CANCEL_MESSAGE);
			throw gcnew System::Exception(Constants->CANCEL_MESSAGE);
		}
		//�ۑ����Ă��郆�[�U�[�̃J�[�h�f�[�^���폜����
		this->carddata->clear();
		//���[�U�[��񃉃x��������������
		this->labelInfomasion->Text = "";
		//�������x��������������
		this->label1->Visible = false;
		//�ފُ�Ԃł��邱�Ƃ����C����ʂ֕\������
		this->labelCauntion->Text = "�J�[�h���쐬���܂����B";
		return;
	}
	catch (System::Exception^ e) {
		MessageBox::Show(Constants->ERROR_MESSAGE);
		Console::Write(e);
	}
}

/*�T�v:�ފك{�^�����������Ƃ��̃N���b�N�C�x���g
�쐬���F2017.10.10
�쐬�ҁFK.Asada*/
private: System::Void ButtonLeavingClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		InputNewUserForm^ create = gcnew InputNewUserForm();
		AdmissionSystem* adm = new AdmissionSystem();    //�J�[�h�Ƃ̐ڑ����s�����肷��N���X���C���X�^���X��
		PassForm^ pass = gcnew PassForm();               //�p�X���[�h����͂���t�H�[�����C���X�^���X��
		std::string passtring = "";                      //�p�X���[�h���i�[���邽�߂̕�����
		//�p�X���[�h���͉�ʂɈڍs����
		pass->ShowDialog();
		//�󂯎�����p�X��ϊ�����String����string��
		this->MarshalString(pass->textBox1->Text, passtring);
		//���b�Z�[�W��\������
		MessageBox::Show(Constants->SET_CARD_MESSAGE);
		//�J�[�h����f�[�^���擾����֐����Ăяo��
		adm->SetCardData(passtring);
		//���[�U�[��񃉃x��������������
		this->labelInfomasion->Text = "";
		//�������x��������������
		this->label1->Visible = false;
		//�ފُ�Ԃł��邱�Ƃ����C����ʂ֕\������
		this->labelCauntion->Text = Constants->LEAVE_MESSAGE;
		//�ۑ����Ă��郆�[�U�[�̃J�[�h�f�[�^���폜����
		this->carddata->clear();
		return;
	}
	catch (System::Exception^ e) {
		MessageBox::Show(Constants->ERROR_MESSAGE);
		System::Console::Write(e);
	}
}


/*�T�v:���ك{�^�����N���b�N�����Ƃ��̃C�x���g
�쐬��:2017.10.10
�쐬��:K.Asada*/
private: System::Void ButtonAdmission(System::Object^  sender, System::EventArgs^  e) {
	try {
		InputNewUserForm^ create = gcnew InputNewUserForm();
		AdmissionSystem* adm = new AdmissionSystem();    //�J�[�h�Ƃ̐ڑ����s�����肷��N���X���C���X�^���X��
		PassForm^ pass = gcnew PassForm();               //�p�X���[�h����͂���t�H�[�����C���X�^���X��
		std::string passtring = "";                      //�p�X���[�h���i�[���邽�߂̕�����
		//�p�X���[�h���͉�ʂɈڍs����
		pass->ShowDialog();
		//�󂯎�����p�X��ϊ�����String����string��
		this->MarshalString(pass->textBox1->Text, passtring);
		//���b�Z�[�W��\������
		MessageBox::Show(Constants->SET_CARD_MESSAGE);
		//�J�[�h�f�[�^����M����֐����Ăяo��
		*this->carddata = adm->GetCardData(passtring);
		//���[�U�[�������C����ʂ֔��f����
		this->CreateDisp();
		//���ُ�Ԃł��邱�Ƃ����C����ʂ֕\������
		this->labelCauntion->Text = Constants->ENTER_MESSAGE;
		return;
	}
	catch (System::Exception^ e) {
		MessageBox::Show(Constants->ERROR_MESSAGE);
		Console::Write(e);
	}
}


/*�T�v:�擾�����f�[�^�����Ƃɉ�ʂɕ\�����郉�x�����쐬����֐�
�쐬��:2017.10.10
�쐬��:K.Asada*/
private: System::Void CreateDisp() {
	try {
		std::vector<std::vector<unsigned char>> data = *this->carddata;
		std::string tmp = "";
		std::string showdata = "";            //�J�[�h���擾������������i�[����
		AdmissionSystem* adm = new AdmissionSystem();    //�J�[�h���f�[�^���擾���邽�߂̃N���X���C���X�^���X��
		//�J�[�h�f�[�^��薼�O�i�����j��������������擾����
		showdata += FIRST_NAME + adm->GetData(*this->carddata, NAME_INDEX) + '\n';
		//�J�[�h�f�[�^��薼�O�i�t���K�i�j��������������擾����
		showdata += LAST_NAME + adm->GetData(*this->carddata, KANA_INDEX) + '\n';
		//�J�[�h�f�[�^���Z����������������擾����
		showdata += ADDRESS_LABEL + adm->GetData(*this->carddata, ADRESS_1_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		showdata += adm->GetData(*this->carddata, ADRESS_2_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		showdata += adm->GetData(*this->carddata, ADRESS_3_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		showdata += adm->GetData(*this->carddata, ADRESS_4_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		showdata += adm->GetData(*this->carddata, ADRESS_5_INDEX) + '\n';
		//�J�[�h�f�[�^���d�b�ԍ���������������擾����
		showdata += TELL_LABEL + adm->GetData(*this->carddata, TELL_INDEX) + '\n';
		//�J�[�h�f�[�^���a������������������擾����
		showdata += BIRTH_LABEL + this->ConvBirth(data[BIRTH_INDEX]) + '\n';
		//�J�[�h�f�[�^��葮����������������擾����
		showdata += ELEM_LABEL + adm->GetElem(data[ELEM_INDEX][4], ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4) + '\n';
		//�J�[�h�f�[�^�@�@�@��茠����������������擾����
		showdata += ADM_LABEL + adm->GetElem(data[ADM_INDEX][5], ADM_NAME1, ADM_NAME2, "", "") + '\n';
		//�J�[�h�f�[�^����E��������������擾����
		showdata += OCCUP_LABEL + adm->GetElem(data[POS_INDEX][6], POS_NAME1, POS_NAME2, POS_NAME3, POS_NAME4) + '\n';
		showdata += GROUP_LABEL + adm->GetElem(data[DEPART_INDEX][7] >> 4, "", OCCUP_NAME1, OCCUP_NAME2, OCCUP_NAME3) + '\n';
		showdata += DEPART_LABEL + adm->GetElem(data[DEPART_INDEX][7], "", DEPART_NAME1, DEPART_NAME2, DEPART_NAME3) + '\n';
		//���C����ʂ֕�����𔽉f����
		this->labelInfomasion->Text = gcnew String(showdata.c_str());
		return;
	}
	catch (System::Exception^ e) {
		System::Console::WriteLine(e);
		//�ۑ����Ă��郆�[�U�[�̃J�[�h�f�[�^���폜����
		this->carddata->clear();
		throw e;
	}
}

		 /*String^�^��string�^�֕ϊ�����֐�
		 �����FString^ sys_string�F�ϊ��Ώۂ̕�����
		 �Fstring& std_string�F�ϊ���̕�����̊i�[��
		 �߂�l�F�Ȃ�
		 �쐬���F2017.10.10
		 �쐬�ҁFK.Asada
		 */
		 void MarshalString(String^ sys_string, std::string& std_string) {
			 using namespace Runtime::InteropServices;
			 const char* chars =
				 (const char*)(Marshal::StringToHGlobalAnsi(sys_string)).ToPointer();
			 std_string = chars;
			 Marshal::FreeHGlobal(IntPtr((void*)chars));
			 return;
		 }

		 /*�T�v:�J�[�h�f�[�^���a�������擾���邽�߂̊֐�
		 ����:vector<char> data:�J�[�h�f�[�^
		 �߂�l:std::string birth:�a�������擾���ĕ�����ɕϊ������f�[�^
		 �쐬��:2017.10.19
		 �쐬��:K.Asada*/
		 std::string ConvBirth(std::vector<unsigned char> data) {
			 TOC condata;    //char�^��int�^�ɕϊ�����ۂɎg�p����o�C�g�z��
			 int year = 0;                               //�a���N
			 int month = 0;                              //�a����
			 int day = 0;                                //�a����
			 std::string birth;                          //�a���N����������������
			 //�J�[�h�f�[�^���a�������擾����
			 for (int i = 0; i < 4; i++) {
				 //1�o�C�g���擾���Ă���
				 condata.bytes[i] = data[i];
			 }
			 //�a���N���擾����
			 year = condata.num / 10000;
			 //�a�������擾����
			 month = condata.num / 100 - year * 100;
			 //�a�������擾����
			 day = condata.num - year * 10000 - month * 100;
			 //�a���N�����̕�����Ƃ��đg�ݗ��Ă�
			 birth = std::to_string(year) + "�N" + std::to_string(month) + "��" + std::to_string(day) + "��";
			 //�擾�����������ԋp����
			 return birth;
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	try {
		//���ق��Ă��Ȃ��ꍇ�͗�O�𓊂���
		if (this->carddata->empty()) {
			//���ق��Ă��Ȃ��|��\������
			MessageBox::Show(Constants->NOT_ENTER_MESSAGE);
			//���ق��Ă��Ȃ���O�𓊂���
			throw gcnew System::Exception(Constants->NOT_ENTER_MESSAGE);
		}
		//�^�C���J�[�h�\���p�̃N���X���C���X�^���X��
		TimeCardForm^ card = gcnew TimeCardForm();
		//�J�[�h�f�[�^��n��
		*card->carddata = *this->carddata;
		//�_�C�A���O���J��
		card->ShowDialog();
	}
	catch (System::Exception^ e) {
		MessageBox::Show(Constants->ERROR_MESSAGE);
		Console::Write(e);
	}
}
};
}

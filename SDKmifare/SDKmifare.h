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
	private: System::Windows::Forms::Label^  label2;

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
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonAdmission
			// 
			this->buttonAdmission->Location = System::Drawing::Point(123, 119);
			this->buttonAdmission->Name = L"buttonAdmission";
			this->buttonAdmission->Size = System::Drawing::Size(269, 229);
			this->buttonAdmission->TabIndex = 0;
			this->buttonAdmission->Text = L"����";
			this->buttonAdmission->UseVisualStyleBackColor = true;
			this->buttonAdmission->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonAdmission);
			// 
			// buttonNewUser
			// 
			this->buttonNewUser->Location = System::Drawing::Point(777, 119);
			this->buttonNewUser->Name = L"buttonNewUser";
			this->buttonNewUser->Size = System::Drawing::Size(269, 229);
			this->buttonNewUser->TabIndex = 1;
			this->buttonNewUser->Text = L"�쐬";
			this->buttonNewUser->UseVisualStyleBackColor = true;
			this->buttonNewUser->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonNewUserClick);
			// 
			// buttonLeaving
			// 
			this->buttonLeaving->Location = System::Drawing::Point(455, 119);
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
			this->labelCauntion->Click += gcnew System::EventHandler(this, &SDKmifare::labelCauntion_Click);
			// 
			// labelInfomasion
			// 
			this->labelInfomasion->AutoSize = true;
			this->labelInfomasion->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->labelInfomasion->Location = System::Drawing::Point(212, 535);
			this->labelInfomasion->Name = L"labelInfomasion";
			this->labelInfomasion->Size = System::Drawing::Size(75, 33);
			this->labelInfomasion->TabIndex = 4;
			this->labelInfomasion->Text = L"aaaa";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Red;
			this->label1->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label1->Location = System::Drawing::Point(531, 56);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(117, 33);
			this->label1->TabIndex = 5;
			this->label1->Text = L"label1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->label2->Location = System::Drawing::Point(0, 535);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(162, 363);
			this->label2->TabIndex = 5;
			this->label2->Text = L"���@�@�@�O�F\r\n�ӂ� �@���ȁF\r\n�Z�@�@�@���F\r\n�a ��  ���F\r\n�d�b�ԍ��F\r\n���@�@�@���F\r\n���@�@�@���F\r\n�E�@�@�@��F\r\n���@�@�@���F\r\n���@�@�@�E�F\r\n"
				L"���ފٓ��F";
			// 
			// SDKmifare
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1175, 649);
			this->Controls->Add(this->label2);
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
		if (create->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			std::string id;
			this->MarshalString(create->UID, id);
			//�J�[�h�҂���Ԃ������_�C�A���O��\�����āA�L�����Z���������ꂽ��ڑ����I������
			MessageBox::Show(Constants->SET_CARD_MESSAGE);
			//�J�[�h����f�[�^���擾����֐����Ăяo��
			adm->SetCardData(id);
			//�쐬�����̃��b�Z�[�W��\������
			MessageBox::Show(Constants->FINISH_MESSAGE);
		}//OK�ȊO�̎��͍쐬�����f���ꂽ�Ƃ���
		else {
			MessageBox::Show(Constants->CANCEL_MESSAGE);
		}
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
		//���ق��Ă��Ȃ��ꍇ�͗�O�𓊂���
		if (this->carddata->empty()) {
			//���ق��Ă��Ȃ��|��\������
			MessageBox::Show("���ق��Ă��܂���B");
			//���ق��Ă��Ȃ���O�𓊂���
			throw gcnew System::Exception("���ْ��̃��[�U�[�����܂���B");
		}
		AdmissionSystem* adm = new AdmissionSystem();    //�J�[�h�Ƃ̐ڑ����s�����肷��N���X���C���X�^���X��
		std::string uid = "";
		//�J�[�h�f�[�^��胆�[�UID���擾����
		uid = adm->GetData(*this->carddata, UID_INDEX, 0, 8);
    	//�ފٓ����L�^����
		adm->SetAdmissionTimes(uid);
		//�J�[�h�҂���Ԃ������_�C�A���O��\�����āA�L�����Z���������ꂽ��ڑ����I������
		MessageBox::Show(Constants->SET_CARD_MESSAGE);
		//�J�[�h����f�[�^���擾����֐����Ăяo��
		adm->SetCardData(uid);
		//���[�U�[��񃉃x��������������
		this->labelInfomasion->Text = "";
		//�������x��������������
		this->Controls->Remove(this->label1);
		//�ފُ�Ԃł��邱�Ƃ����C����ʂ֕\������
		this->labelCauntion->Text = Constants->LEAVE_MESSAGE;
		//�ۑ����Ă��郆�[�U�[�̃J�[�h�f�[�^���폜����
		this->carddata->clear();
		//�ފَ��̃��b�Z�[�W��\������
		MessageBox::Show(Constants->LEAVE_MESSAGE);
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
		//���b�Z�[�W��\������
		MessageBox::Show(Constants->SET_CARD_MESSAGE);
		//�p�X���[�h���͉�ʂɈڍs����
		pass->ShowDialog();
		//�󂯎�����p�X��ϊ�����String����string��
		this->MarshalString(create->SetByte(pass->textBox1->Text, 8), passtring);
		//�J�[�h�f�[�^����M����֐����Ăяo��
		*this->carddata = adm->GetCardData(passtring);
		//���[�U�[�������C����ʂ֔��f����
		this->CreateDisp();
		//���ُ�Ԃł��邱�Ƃ����C����ʂ֕\������
		this->labelCauntion->Text = Constants->ENTER_MESSAGE;
		//���ي����̃��b�Z�[�W��\������
		MessageBox::Show(Constants->ENTER_MESSAGE);
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
		std::string tmp = "";
		std::string showdata = "";            //�J�[�h���擾������������i�[����
		AdmissionSystem* adm = new AdmissionSystem();    //�J�[�h���f�[�^���擾���邽�߂̃N���X���C���X�^���X��
		//�J�[�h�f�[�^��薼�O�i�����j��������������擾����
		showdata += adm->GetData(*this->carddata, NAME_INDEX) + '\n';
		//�J�[�h�f�[�^��薼�O�i�t���K�i�j��������������擾����
		showdata += adm->GetData(*this->carddata, KANA_INDEX) + '\n';
		//�J�[�h�f�[�^���Z����������������擾����
		showdata += adm->GetData(*this->carddata, ADRESS_1_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		showdata += adm->GetData(*this->carddata, ADRESS_2_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		showdata += adm->GetData(*this->carddata, ADRESS_3_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		showdata += adm->GetData(*this->carddata, ADRESS_4_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		showdata += adm->GetData(*this->carddata, ADRESS_5_INDEX) + '\n';
		//�J�[�h�f�[�^���d�b�ԍ���������������擾����
		showdata += adm->GetData(*this->carddata, TELL_INDEX) + '\n';
		//�J�[�h�f�[�^���a������������������擾����
		showdata += adm->GetData(*this->carddata, BIRTH_INDEX) + '\n';
		//�J�[�h�f�[�^��葮����������������擾����
		tmp = this->GetElem(ELEM_INDEX, 0, ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4);
		if (tmp == ELEM_NAME3) {
			this->label1->Text = gcnew String(tmp.c_str());
			this->Controls->Add(this->label1);
		}
		else if (tmp == ELEM_NAME4) {
			MessageBox::Show("�댯�l���ł����ق����ۂ��܂��B");
			throw gcnew System::Exception("�댯�l���ł��B");
		}
		showdata += tmp + '\n';
		//�J�[�h�f�[�^��茠����������������擾����
		showdata += this->GetElem(ADM_INDEX, 1, ADM_NAME1, ADM_NAME2, "", "") + '\n';
		//�J�[�h�f�[�^���E���������������擾����
		showdata += this->GetElem(OCCUP_INDEX, 2, OCCUP_NAME1, OCCUP_NAME2, OCCUP_NAME3, OCCUP_NAME4) + '\n';
		//�J�[�h�f�[�^��蕔����������������擾����
		showdata += this->GetElem(DEPART_INDEX, 3, DEPART_NAME1, DEPART_NAME2, DEPART_NAME3, DEPART_NAME4) + '\n';
		//�J�[�h�f�[�^����E��������������擾����
		showdata += this->GetElem(POS_INDEX, 4, POS_NAME1, POS_NAME2, POS_NAME3, POS_NAME4) + '\n';
		//�J�[�h�f�[�^���N����������������擾����
		showdata += this->ConvYears(*this->carddata) + '\n';
		//�J�[�h�f�[�^����������������������擾����
		showdata += this->ConvTimes(*this->carddata) + '\n';
		//���C����ʂ֕�����𔽉f����
		this->labelInfomasion->Text = gcnew String(showdata.c_str());
		return;
	}
	catch (System::IndexOutOfRangeException^ e) {
		System::Console::WriteLine(e);
	}
}

/*�T�v:�J�[�h�Ɋi�[���ꂽ���������𕶎���ɕϊ�����֐�
����:std::vector<std::vcotr<unsigned char>> data:�J�[�h�f�[�^
�߂�l:std::vector<string> times:�������𕶎���ɕϊ������z��
�쐬��:2017.10.16
�쐬��:K.Asada*/
private: std::string ConvTimes(std::vector<std::vector<unsigned char>> data) {
	try {
		std::string times = "";        //�������𕶎���ɕϊ��������̂��i�[���邽�߂̔z��
		ITOC gettimes;                         //�J�[�h�f�[�^�̒��ɂ���char�^�̐��l��unsigned int�^�ɕϊ����邽�߂̋��L��
		int day = 0;                           //�擾���������i�[����ϐ�
		int hour = 0;                          //�擾�������Ԃ��i�[����ϐ�
		int min = 0;                           //�擾���������i�[����ϐ�
		int timeindex = TIMES_1_INDEX;
		//�J�[�h�f�[�^�ɂ�����������𑖍����Ă���
		for (int i = 1; data[timeindex][i * 2] != 0; i++) {
			//�J�[�h�f�[�^���������̏��8�r�b�g���擾����
			gettimes.bytes[1] = data[timeindex][i * 2];
			//�J�[�h�f�[�^���������̉���8�r�b�g���擾����
			gettimes.bytes[0] = data[timeindex][i * 2 + 1];
			//�擾��������������ɕϊ�����
			day = gettimes.num / 1440;
			//�擾���������������ɕϊ�����
			hour = gettimes.num / 60 - day * 24;
			//�擾�����������𕪂ɕϊ�����
			min = gettimes.num - 1440 * day - 60 * hour;
			//�ϊ�������������A�����ĕ����������������
			times += std::to_string(day) + "��" + std::to_string(hour) + "��" + std::to_string(min) + "��" + '\n';
			if (i == 7) {
				i = -1;
				timeindex++;
			}
		}
		//�ϊ������������ԋp����
		return times;
	}
	catch (System::IndexOutOfRangeException^ e) {
		System::Console::WriteLine(e);
	}
}

/*�T�v:�J�[�h�Ɋi�[���ꂽ�N�����𕶎���ɕϊ����邽�߂̊֐�
����:std::vector<std::vector<unsigned char>> data:�J�[�h���擾�����f�[�^
�߂�l:std::vector<std::string> years:������ɕϊ������N��
�쐬��:2017.10.16
�쐬��:K.Asada*/
private: std::string ConvYears(std::vector<std::vector<unsigned char>> data) {
	try {
		std::string years;        //�ϊ�������������i�[����
		ITOC getyears;            //�J�[�h���擾�����N����unsigned int�^�ɕϊ����邽�߂̋��L��
		int year = 0;             //�擾�����N
		int month = 0;            //�擾������
		//�J�[�h�f�[�^���N���̏��8�r�b�g���擾����
		getyears.bytes[1] = data[YEAR_INDEX][0];
		//�J�[�h�f�[�^���N���̉���8�r�b�g���擾����
		getyears.bytes[0] = data[YEAR_INDEX][1];
		//�N����N�ɕϊ�����
		year = getyears.num / 12;
		//�N�������ɕϊ�����
		month = getyears.num % 12;
		//�ϊ������N����A�����ĕ����������������
		years = (std::to_string(year) + "�N" + std::to_string(month) + "��");
		//�ϊ������������ԋp����
		return years;
	}
	catch (System::IndexOutOfRangeException^ e) {
		System::Console::WriteLine(e);
	}
}

/*�T�v:���[�U�[�̑����𔻒肵�A����ɉ����������Ԃ��֐�
�쐬���F2017.10.10
�쐬�ҁFK.Asada*/
private: System::Int32 CheckBit(char check) {
	System::Int32 countbit = 0;    //�r�b�g�������Ă���ꏊ
	//�Ώۂ𑖍������r�b�g�ڂ������Ă��邩�𒲂ׂ�
	for (int i = 0; i < 8; i++) {
		//�r�b�g�������Ă����炻�̏ꏊ��ϐ��Ɋi�[����
		if ((check >> i) & 1U) {
			//�r�b�g�������Ă���ꏊ��ۊǂ���
			countbit = i + 1;
			//���[�v�𔲂���
			break;
		}
	}
	//���茋�ʂ�Ԃ�
	return countbit;
}

		 /*�T�v:���r�b�g�ڂ������Ă��邩�ɉ������������Ԃ��֐�
		 ����:int index:�J�[�h�f�[�^�̒��̑Ώۂ̃f�[�^���i�[����Ă���ꏊ
		     :int byte:�Ώۂ��i�[����Ă��鉽�o�C�g�ڂɊi�[����Ă��邩
			 :string name1:1�r�b�g�ڂ������Ă���Ƃ��ɕԂ�������
			 :string name2:2�r�b�g�ڂ������Ă���Ƃ��ɕԂ�������
			 :string name3:3�r�b�g�ڂ������Ă���Ƃ��ɕԂ�������
			 :string name4:4�r�b�g�ڂ������Ă���Ƃ��ɕԂ�������
		�߂�l:string name:�r�b�g���ɉ�����������
		�쐬��:2017.10.17
		�쐬��:K.Asada*/
		 std::string GetElem(int index, int byte, std::string name1, std::string name2, std::string name3, std::string name4) {
			 std::string name = "";    //�ԋp�p�̕�����
			 std::vector<std::vector<unsigned char>> data = *this->carddata;
			 int checkbit = 0;         //���r�b�g�ڂ������Ă��������i�[����ϐ�
			 //���r�b�g�ڂ������Ă��邩�𒲂ׂ�
			 checkbit = this->CheckBit(data[index][byte]);
			 //���r�b�g�ڂ������Ă������ɂ���đΉ������������ԋp����
			 switch (checkbit) {
		     //1�̎��͈���1�̕������Ԃ�
			 case 1:name = name1;
				 break;
			 //2�̎��͈���2�̕������Ԃ�
			 case 2:name = name2;
				 break;
			 //3�̎��͈���3�̕������Ԃ�
			 case 3:name = name3;
				 break;
			 //4�̎��͈���4�̕������Ԃ�
			 case 4:name = name4;
				 break;
			 }
			 //�擾�����������ԋp����
			 return name;
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
private: System::Void labelCauntion_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}

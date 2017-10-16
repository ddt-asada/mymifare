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
			this->labelCauntion->Dock = System::Windows::Forms::DockStyle::Top;
			this->labelCauntion->Location = System::Drawing::Point(0, 0);
			this->labelCauntion->Name = L"labelCauntion";
			this->labelCauntion->Size = System::Drawing::Size(67, 24);
			this->labelCauntion->TabIndex = 3;
			this->labelCauntion->Text = L"label1";
			this->labelCauntion->Click += gcnew System::EventHandler(this, &SDKmifare::labelCauntion_Click);
			// 
			// labelInfomasion
			// 
			this->labelInfomasion->AutoSize = true;
			this->labelInfomasion->Location = System::Drawing::Point(0, 386);
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
			this->ClientSize = System::Drawing::Size(1175, 465);
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
		std::string* Uid = new std::string("asada");				//�ǂݍ��񂾃J�[�h�̃��[�U�[ID
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
		//MessageBox::Show(e);
	}
}

/*�T�v:�ފك{�^�����������Ƃ��̃N���b�N�C�x���g
�쐬���F2017.10.10
�쐬�ҁFK.Asada*/
private: System::Void ButtonLeavingClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		AdmissionSystem* adm = new AdmissionSystem();    //�J�[�h�Ƃ̐ڑ����s�����肷��N���X���C���X�^���X��
	//�ފٓ����L�^����
		adm->SetAdmissionTimes(*this->Uid);
		//�J�[�h�҂���Ԃ������_�C�A���O��\�����āA�L�����Z���������ꂽ��ڑ����I������
		MessageBox::Show(Constants->SET_CARD_MESSAGE);
		//�J�[�h����f�[�^���擾����֐����Ăяo��
		adm->SetCardData(*this->Uid);
		//�ފَ��̃��b�Z�[�W��\������
		MessageBox::Show(Constants->LEAVE_MESSAGE);
		return;
	}
	catch (System::Exception^ e) {
		System::Console::Write(e);
	}
}


/*�T�v:���ك{�^�����N���b�N�����Ƃ��̃C�x���g
�쐬��:2017.10.10
�쐬��:K.Asada*/
private: System::Void ButtonAdmission(System::Object^  sender, System::EventArgs^  e) {
	try {
		AdmissionSystem* adm = new AdmissionSystem();    //�J�[�h�Ƃ̐ڑ����s�����肷��N���X���C���X�^���X��
		PassForm^ pass = gcnew PassForm();               //�p�X���[�h����͂���t�H�[�����C���X�^���X��
		std::string passtring = "";                      //�p�X���[�h���i�[���邽�߂̕�����
		//���b�Z�[�W��\������
		MessageBox::Show(Constants->SET_CARD_MESSAGE);
		//�p�X���[�h���͉�ʂɈڍs����
		pass->ShowDialog();
		//�󂯎�����p�X��ϊ�����String����string��
		this->MarshalString(pass->textBox1->Text, passtring);
		//�J�[�h�f�[�^����M����֐����Ăяo��
		adm->GetCardData(passtring);
		this->CreateDisp();
		//���ي����̃��b�Z�[�W��\������
		MessageBox::Show(Constants->ENTER_MESSAGE);
		return;
	}
	catch (System::Exception^ e) {
	//	MessageBox::Show(e);
	}
}


/*�T�v:�擾�����f�[�^�����Ƃɉ�ʂɕ\�����郉�x�����쐬����֐�
�쐬��:2017.10.10
�쐬��:K.Asada*/
private: System::Void CreateDisp() {
	std::string showdata = "";            //�J�[�h���擾������������i�[����
	std::vector<std::string>times;        //�J�[�h���擾������������������������i�[����
	showdata = (this->carddata[0], this->carddata[0].size());
	//�J�[�h�f�[�^��薼�O(����)��������������擾���A���C����ʂɐݒ肷��
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	//�J�[�h�f�[�^��薼�O(�t���K�i)���擾���A���C����ʂɐݒ肷��
	showdata = (this->carddata[1], this->carddata[1].size());
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	//�J�[�h�f�[�^���Z�����擾���A���C����ʂɐݒ肷��
	showdata = ((this->carddata[3], this->carddata[3].size()) + (this->carddata[4], this->carddata[4].size()) + (this->carddata[5], this->carddata[5].size()) + (this->carddata[6], this->carddata[6].size()) + (this->carddata[7], this->carddata[7].size()));
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	//�J�[�h�f�[�^���d�b�ԍ����擾���A���C����ʂɐݒ肷��
	showdata = (this->carddata[8], this->carddata[8].size());
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	//�J�[�h�f�[�^���a�������擾���A���C����ʂɐݒ肷��
	showdata = (this->carddata[9], this->carddata[9].size());
	this->labelInfomasion->Text = gcnew String(showdata.c_str());
	//�J�[�h�f�[�^���N�����擾���A���C����ʂɐݒ肷��
	this->labelInfomasion->Text = gcnew String(this->ConvYears(*this->carddata).c_str());
	//�J�[�h�f�[�^�����������擾����
	times = this->ConvTimes(*this->carddata);
	//���C����ʂ֓�������ݒ肷��
	for (int i = 0; i < times.size(); i++) {
		//���C����ʂ֐ݒ肷��
		this->labelInfomasion->Text = gcnew String(times[i].c_str());
	}
	return;
}

/*�T�v:�J�[�h�Ɋi�[���ꂽ���������𕶎���ɕϊ�����֐�
����:std::vector<std::vcotr<unsigned char>> data:�J�[�h�f�[�^
�߂�l:std::vector<string> times:�������𕶎���ɕϊ������z��
�쐬��:2017.10.16
�쐬��:K.Asada*/
private: std::vector<std::string> ConvTimes(std::vector<std::vector<unsigned char>> data) {
	std::vector<std::string> times;        //�������𕶎���ɕϊ��������̂��i�[���邽�߂̔z��
	ITOC gettimes;                         //�J�[�h�f�[�^�̒��ɂ���char�^�̐��l��unsigned int�^�ɕϊ����邽�߂̋��L��
	int day = 0;                           //�擾���������i�[����ϐ�
	int hour = 0;                          //�擾�������Ԃ��i�[����ϐ�
	int min = 0;                           //�擾���������i�[����ϐ�
	//�J�[�h�f�[�^�ɂ�����������𑖍����Ă���
	for (int i = 0; data[TIMES_1_INDEX][i * 2] != 0; i++) {
		//�J�[�h�f�[�^���������̏��8�r�b�g���擾����
		gettimes.bytes[1] = data[TIMES_1_INDEX][i * 2];
		//�J�[�h�f�[�^���������̉���8�r�b�g���擾����
		gettimes.bytes[0] = data[TIMES_1_INDEX][i * 2 + 1];
		//�擾��������������ɕϊ�����
		day = gettimes.num / 1440;
		//�擾���������������ɕϊ�����
		hour = gettimes.num / 60 - day * 24;
		//�擾�����������𕪂ɕϊ�����
		min = gettimes.num - 1440 * day - 24 * hour;
		//�ϊ�������������A�����ĕ����������������
		times.push_back(std::to_string(day) + "��" + std::to_string(hour) + "��" + std::to_string(min) + "��");
	}
	//�ϊ������������ԋp����
	return times;
}

/*�T�v:�J�[�h�Ɋi�[���ꂽ�N�����𕶎���ɕϊ����邽�߂̊֐�
����:std::vector<std::vector<unsigned char>> data:�J�[�h���擾�����f�[�^
�߂�l:std::vector<std::string> years:������ɕϊ������N��
�쐬��:2017.10.16
�쐬��:K.Asada*/
private: std::string ConvYears(std::vector<std::vector<unsigned char>> data) {
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

/*�T�v:���[�U�[�̑����𔻒肵�A����ɉ����������Ԃ��֐�
�쐬���F2017.10.10
�쐬�ҁFK.Asada*/
private: System::Boolean CheckElement(unsigned char* elem) {
	int check = elem[CONSTANTGROUP::ELEM_INDEX];    //�Ώۂ̃��[�U�[�̑������擾����
	//�r�b�g���Z�ɂ�葮���ɓ����镔���܂ňړ�����
	check = check >> 19;
	//���r�b�g�ڂ������Ă��邩�𒲂ׁA����ɉ����������Ԃ�
	if(check & 1U){
		//19�r�b�g�ځi�v���Ӑl�������j�̃r�b�g�������Ă���Ƃ��͗v���Ӑl���Ƃ���true��Ԃ�
		check = true;
	}//20�r�b�g�ڂ𒲂ׂ�
	else if (check >> 1 & 1U) {
		//20�r�b�g�ځi�댯�l�������j�̃r�b�g�������Ă���Ƃ��͊댯�l���Ƃ��ė�O���Ȃ��A���ق����ۂ���
		throw gcnew System::Exception("�댯�l���ł��B���ق����ۂ��܂��B");
	}
	//���茋�ʂ�Ԃ�
	return true;
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

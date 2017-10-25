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
			this->buttonEntering->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonEntering->Location = System::Drawing::Point(12, 408);
			this->buttonEntering->Name = L"buttonEntering";
			this->buttonEntering->Size = System::Drawing::Size(269, 229);
			this->buttonEntering->TabIndex = 0;
			this->buttonEntering->Text = L"����";
			this->buttonEntering->UseVisualStyleBackColor = true;
			this->buttonEntering->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonEnteringClick);
			// 
			// buttonOutPut
			// 
			this->buttonOutPut->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonOutPut->Location = System::Drawing::Point(562, 408);
			this->buttonOutPut->Name = L"buttonOutPut";
			this->buttonOutPut->Size = System::Drawing::Size(269, 229);
			this->buttonOutPut->TabIndex = 1;
			this->buttonOutPut->Text = L"�����o��";
			this->buttonOutPut->UseVisualStyleBackColor = true;
			this->buttonOutPut->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonWrittingClick);
			// 
			// buttonLeaving
			// 
			this->buttonLeaving->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonLeaving->Location = System::Drawing::Point(287, 408);
			this->buttonLeaving->Name = L"buttonLeaving";
			this->buttonLeaving->Size = System::Drawing::Size(269, 229);
			this->buttonLeaving->TabIndex = 2;
			this->buttonLeaving->Text = L"�ފ�";
			this->buttonLeaving->UseVisualStyleBackColor = true;
			this->buttonLeaving->Click += gcnew System::EventHandler(this, &SDKmifare::ButtonLeavingClick);
			// 
			// buttonTimeList
			// 
			this->buttonTimeList->Font = (gcnew System::Drawing::Font(L"�l�r �S�V�b�N", 19.875F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->buttonTimeList->Location = System::Drawing::Point(837, 408);
			this->buttonTimeList->Name = L"buttonTimeList";
			this->buttonTimeList->Size = System::Drawing::Size(269, 229);
			this->buttonTimeList->TabIndex = 5;
			this->buttonTimeList->Text = L"���t�ꗗ";
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
			this->labelInformation->Text = L"���[�U�[���";
			// 
			// labelCauntion
			// 
			this->labelCauntion->AutoSize = true;
			this->labelCauntion->Location = System::Drawing::Point(86, 140);
			this->labelCauntion->Name = L"labelCauntion";
			this->labelCauntion->Size = System::Drawing::Size(149, 24);
			this->labelCauntion->TabIndex = 7;
			this->labelCauntion->Text = L"�x�����b�Z�[�W";
			// 
			// labelState
			// 
			this->labelState->AutoSize = true;
			this->labelState->Location = System::Drawing::Point(89, 213);
			this->labelState->Name = L"labelState";
			this->labelState->Size = System::Drawing::Size(106, 24);
			this->labelState->TabIndex = 8;
			this->labelState->Text = L"���ُ��";
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
		public:SCARDCONTEXT hContext = 0;        //���\�[�X�}�l�[�W���̃A�h���X
			   SCARDHANDLE hCard = 0;            //�J�[�h�̃A�h���X
			   DWORD ActiveProtocol = 0;         //�J�[�h�Ƃ̒ʐM���Ɏg���v���g�R��
private:std::vector<std::vector<unsigned char>>* carddata = new std::vector<std::vector<unsigned char>>();           //�擾�����J�[�h�f�[�^
		std::string* uid = new std::string();    //���[�U�[ID
		CONSTANTGROUP::ConstantString^ Constants = gcnew CONSTANTGROUP::ConstantString();


/*�T�v:�쐬�{�^�����������Ƃ��̃N���b�N�C�x���g
�쐬��:2017.10.10
�쐬��:K.Asada*/
		/*
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
}*/

/*�T�v:�ފك{�^�����������Ƃ��̃N���b�N�C�x���g
�쐬���F2017.10.10
�쐬�ҁFK.Asada
�X�V���e:�V�d�l�����ɔ����C�x���g�̓��e��啝�ɕύX
�X�V��:2017.10.24
�X�V��:K.Asada*/
private: System::Void ButtonLeavingClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		AdmissionSystem* adm = new AdmissionSystem();   //�֐��Q�N���X���C���X�^���X��
		System::String^ check = "";    //�ފُ�Ԃ��i�[���邽�߂̕�����
		//�ފُ�Ԃ𒲂ׂ�֐����Ăяo��
		check = adm->CheckLeaveState(*this->carddata);
		//�ފُ�Ԃ𒲂ׂĉ��炩�̕����񂪋A���Ă����ꍇ�̓��b�Z�[�W��\��
		if (check != "") {
			//���݂̑ފُ�Ԃ��ǂ��Ȃ��Ă��邩�̃��b�Z�[�W��\������
			MessageBox::Show(check);
			//�ފق��邩�ǂ����̊m�F���b�Z�[�W��\������
			if (MessageBox::Show(Constants->LEAVE_CHECK,"", System::Windows::Forms::MessageBoxButtons::OKCancel, System::Windows::Forms::MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::OK) {
				//�L�����Z���̎��̓G���[�𓊂��ď����𒆒f����
				throw gcnew System::Exception(Constants->LEAVE_CANCEL);
			}
		}
		//�ފَ������J�[�h�ɋL�^����֐����Ăяo��
		adm->UpdateCardData(*this->carddata, this->hContext, this->hCard, this->ActiveProtocol, LEAVE_1_INDEX, END_INDEX);
		//�ފي����̃��b�Z�[�W��\������
		MessageBox::Show(Constants->LEAVE_MESSAGE);
		return;
	}
	catch (System::Exception^ e) {
		MessageBox::Show(Constants->ERROR_MESSAGE);
		System::Console::Write(e);
	}
}

		 /*�T�v:�J�[�h���[�U�[�̑����𔻒肵�A�댯�x�����N�𔻒肷��֐�
		 ����:std::vector<std::vector<unsigned char>> data:�J�[�h���擾�����f�[�^
		 �߂�l:System::String^:���[�U�[�̊댯�x������������
		 �쐬��:2017.10.24
		 �쐬��:K.Asada*/
		 System::String^ CheckCauntion(std::vector<std::vector<unsigned char>> data) {
			 AdmissionSystem* adm = new AdmissionSystem();    //�֐��Q�N���X���C���X�^���X��
			 std::string check = ""; //���茋�ʂ̕�����
			 //�������擾����֐����Ăяo��
			 check = adm->GetElem(data[ELEM_INDEX][4], ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4);
			 //�댯�x�𔻒肷��
			 if (check == ELEM_NAME2) {
				 //�댯�l��������������ł���΃��b�Z�[�W��\��
				 MessageBox::Show("�댯�l���ł��B");
			 }
			 else if (check == ELEM_NAME3) {
				 //�v���Ӑl��������������ł���΃��b�Z�[�W��\��
				 MessageBox::Show("�v���Ӑl���ł��B");
			 }
			 //�������ԋp����
			 return gcnew String(check.c_str());
		 }

		 /*�T�v:�J�[�h���[�U�[�̓��ފُ�Ԃ𔻒肵�A���݂̏�Ԃ������������ԋp����֐�
		 ����:std::vector<std::vector<unsigned char>>:�J�[�h���擾�����f�[�^
		 �߂�l:System::String^:���ފُ�Ԃ�����������
		 �쐬��:2017.10.24
		 �쐬��:K.Asada*/

/*�T�v:�擾�����f�[�^�����Ƃɉ�ʂɕ\�����郉�x�����쐬����֐�
�쐬��:2017.10.10
�쐬��:K.Asada
�X�V���e:�V�d�l�����ɔ����֐����A�߂�l�A������ύX
����:std::vector<std::vector<unsigned char>> data:���[�U�[��񂪊i�[���ꂽ�J�[�h�f�[�^
�߂�l:Sytem::String^ userdata:�J�[�h���擾�������[�U�[���
�X�V��:2017.10.24
�X�V��:K.Asada*/
private: System::String^ GetUserInfo(std::vector<std::vector<unsigned char>> data) {
	try {
		std::string userinfo = "";            //�J�[�h���擾������������i�[����
		AdmissionSystem* adm = new AdmissionSystem();    //�J�[�h���f�[�^���擾���邽�߂̃N���X���C���X�^���X��
		//�J�[�h�f�[�^��薼�O�i�����j��������������擾����
		userinfo += FIRST_NAME + adm->GetData(*this->carddata, NAME_INDEX) + '\n';
		//�J�[�h�f�[�^��薼�O�i�t���K�i�j��������������擾����
		userinfo += LAST_NAME + adm->GetData(*this->carddata, KANA_INDEX) + '\n';
		//�J�[�h�f�[�^���Z����������������擾����
		userinfo += ADDRESS_LABEL + adm->GetData(*this->carddata, ADRESS_1_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		userinfo += adm->GetData(*this->carddata, ADRESS_2_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		userinfo += adm->GetData(*this->carddata, ADRESS_3_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		userinfo += adm->GetData(*this->carddata, ADRESS_4_INDEX);
		//�J�[�h�f�[�^���Z����������������擾����
		userinfo += adm->GetData(*this->carddata, ADRESS_5_INDEX) + '\n';
		//�J�[�h�f�[�^���d�b�ԍ���������������擾����
		userinfo += TELL_LABEL + adm->GetData(*this->carddata, TELL_INDEX) + '\n';
		//�J�[�h�f�[�^���a������������������擾����
		userinfo += BIRTH_LABEL + this->ConvBirth(data[BIRTH_INDEX]) + '\n';
		//�������擾����
		userinfo += + ELEM_LABEL + adm->GetElem(data[ELEM_INDEX][4], ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4) + '\n';
		//�J�[�h�f�[�^��茠����������������擾����
		userinfo += ADM_LABEL + adm->GetElem(data[ADM_INDEX][5], ADM_NAME1, ADM_NAME2, "", "") + '\n';
		//�J�[�h�f�[�^����E��������������擾����
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
			 UITOC condata;    //char�^��int�^�ɕϊ�����ۂɎg�p����o�C�g�z��
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


		 /*�T�v:���ފى�ʃ��[�h���̃C�x���g
		 �쐬��:2017.10.24
		 �쐬��:K.Asada*/
private: System::Void SDKmifareFormLoad(System::Object^  sender, System::EventArgs^  e) {
	try {
		AdmissionSystem* adm = new AdmissionSystem();    //�֐��Q�N���X���C���X�^���X��
		//�������ꂽ�J�[�h����J�[�h�f�[�^���擾����
		*this->carddata = adm->GetCardData(this->hContext, this->hCard, this->ActiveProtocol);
		//�J�[�h�̃��[�U�[���V�X�e���ɓo�^����Ă��邩���`�F�b�N����
		*this->uid = adm->CheckUser(*this->carddata);
		//�J�[�h���̃f�[�^�ƃV�X�e���ɓo�^����Ă���f�[�^����v���邩���`�F�b�N����
		if (!adm->CollationFiledata(*this->carddata, *this->uid)) {
			//��v���Ă��Ȃ���΃G���[�𓊂���
			throw gcnew System::Exception("�J�[�h�f�[�^���s���ł��B");
		}
		//���[�U�[�����J�[�h�f�[�^���擾����
		this->labelInformation->Text = this->GetUserInfo(*this->carddata);
		//���[�U�[�̊댯�x���`�F�b�N���đΉ�������������擾����
		this->labelCauntion->Text = this->CheckCauntion(*this->carddata);
		//���[�U�[�̓��ُ�Ԃ𔻒肷��
		this->labelState->Text = adm->CheckEnterState(*this->carddata);
		return;
	}
	catch (System::Exception^ e) {
		//�R���\�[���ɃG���[���e��\������
		Console::WriteLine(e);
	}
}

		 /*�T�v:���ك{�^���N���b�N���̃C�x���g
		 �쐬��:2017.10.24
		 �쐬��:K.Asada*/
private: System::Void ButtonEnteringClick(System::Object^  sender, System::EventArgs^  e) {
	try {
		AdmissionSystem* adm = new AdmissionSystem();    //�֐��Q�N���X���C���X�^���X��
		System::String^ checkenter = "";    //���ُ�Ԃ𔻒肷�镶����
		//���ُ�Ԃ𔻒肷��
		checkenter = adm->CheckEnterState(*this->carddata);
		//�󕶎��łȂ��Ƃ��͂����ɂ���s��
		if (checkenter != "") {
			//���ُ�Ԃ�\������
			MessageBox::Show(checkenter);
			//���ُ������s�������m�F����
			if (MessageBox::Show(Constants->ENTER_CHECK, "", MessageBoxButtons::OKCancel, MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::OK) {
				//�L�����Z���̎��̓G���[�𓊂���
				throw gcnew System::Exception(Constants->ENTER_CANCEL);
			}
		}
		//���ق��������ŁA���َ��Ԃ��X�V����֐����Ăяo��
		adm->UpdateCardData(*this->carddata, this->hContext, this->hCard, this->ActiveProtocol, TIMES_1_INDEX, END_INDEX);
		//���ي����̃��b�Z�[�W��\������
		MessageBox::Show(Constants->ENTER_MESSAGE);
		return;
	}
	catch (System::Exception^ e) {
		//�G���[���e���R���\�[���ɕ\������
		Console::WriteLine(e);
	}
}

/*�T�v:�������݃{�^���N���b�N���̃C�x���g
�쐬��:2017.10.24
�쐬��:K.Asada*/
private: System::Void ButtonWrittingClick(System::Object^  sender, System::EventArgs^  e) {
	AdmissionSystem* adm = new AdmissionSystem();    //�֐��Q�N���X���C���X�^���X��
	std::string uid = "";    //���[�U�[ID���i�[���邽�߂̕�����
	//�J�[�h�֑S�f�[�^�𑗐M���邽�߂̊֐����Ăяo��
	adm->SetCardData(uid, this->hContext, this->hCard, this->ActiveProtocol);
	return;
}

		 /*�T�v:���t�ꗗ�{�^���̃N���b�N�C�x���g
		 �쐬��:2017.10.24
		 �쐬��:K.Asada*/
private: System::Void buttonTimeListClick(System::Object^  sender, System::EventArgs^  e) {
	TimeCardForm^ time = gcnew TimeCardForm();    //���t�ꗗ�\����ʂ��C���X�^���X������
	//���t�ꗗ��ʂɃJ�[�h���擾�������[�U�[����n��
	*time->carddata = *this->carddata;
	//���t�ꗗ��ʂ�\������
	time->ShowDialog();
	return;
}
};
}

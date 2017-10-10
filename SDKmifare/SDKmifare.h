#pragma once

#include "AdmissionSystem.h"
#include "InputNewUserForm.h"
#include <iostream>

namespace SDKmifare {

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
			// 
			// labelInfomasion
			// 
			this->labelInfomasion->AutoSize = true;
			this->labelInfomasion->Location = System::Drawing::Point(119, 446);
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
			this->ClientSize = System::Drawing::Size(1103, 739);
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
private:unsigned long hContext = 0;		//�ǂݍ��񂾃��\�[�X�}�l�[�W���ւ̃|�C���^
		unsigned long hCard = NULL;		//�ǂݍ��񂾃J�[�h�ւ̃|�C���^
		String^ Uid = "";				//�ǂݍ��񂾃J�[�h�̃��[�U�[ID


/*�T�v:�쐬�{�^�����������Ƃ��̃N���b�N�C�x���g
�쐬��:2017.10.10
�쐬��:K.Asada*/
private: System::Void ButtonNewUserClick(System::Object^  sender, System::EventArgs^  e) {
	InputNewUserForm^ create = gcnew InputNewUserForm();    //�V�K���[�U�[������͂��邽�߂̃N���X���C���X�^���X��
	//�V�K�ō쐬����|��`����
	MessageBox::Show("�V�K�ō쐬���܂��B\n������͂��Ă��������B");
	//�V�K���_�C�A���O���J��
	create->ShowDialog();
	//�J�[�h�҂���Ԃɂ���
	this->hContext = adm->WaittingCard();
	//�J�[�h�҂���Ԃ������_�C�A���O��\�����āA�L�����Z���������ꂽ��ڑ����I������
	if (MessageBox::Show("�J�[�h���������Ă��������B") == System::Windows::Forms::DialogResult::Cancel) {
		//���삪���f���ꂽ�|��\������
		MessageBox::Show("���삪���f����܂����B");
		//�ڑ����I������֐����Ăяo��
		adm->EndConnect(this->hContext, this->hCard);
	}//�J�[�h���������ꂽ��f�[�^�̎擾�Ɉڂ�
	else if (this->hCard = ::SCardConnect()) {
		//�J�[�h����f�[�^���擾����֐����Ăяo��
		adm->SetCardData(this->hContext, this->hCard, this->Uid);
	}
	return;
}

/*�T�v:�ފك{�^�����������Ƃ��̃N���b�N�C�x���g
�쐬���F2017.10.10
�쐬�ҁFK.Asada*/
private: System::Void ButtonLeavingClick(System::Object^  sender, System::EventArgs^  e) {
	AdmissionSystem adm^ = gcnew AdmissionSystem();    //�J�[�h�Ƃ̐ڑ����s�����肷��N���X���C���X�^���X��
	//�J�[�h�҂���Ԃɂ��������ŁA���\�[�X�}�l�[�W���ւ̃A�h���X�������o�֊i�[����
	this->hContext = adm->WaittingCard();
	//�J�[�h�҂���Ԃ������_�C�A���O��\�����āA�L�����Z���������ꂽ��ڑ����I������
	if (MessageBox::Show("�J�[�h���������Ă��������B") == System::Windows::Forms::DialogResult::Cancel) {
		//���삪���f���ꂽ�|��\������
		MessageBox::Show("���삪���f����܂����B");
		//�ڑ����I������֐����Ăяo��
		adm->EndConnect(this->hContext, this->hCard);
	}//�J�[�h���������ꂽ��f�[�^�̎擾�Ɉڂ�
	else if (this->hCard = ::SCardConnect()) {
		//�J�[�h����f�[�^���擾����֐����Ăяo��
		adm->SetCardData(this->hContext, this->hCard, this->Uid);
	}
	return;
}


/*�T�v:���ك{�^�����N���b�N�����Ƃ��̃C�x���g
�쐬��:2017.10.10
�쐬��:K.Asada*/
private: System::Void ButtonAdmission(System::Object^  sender, System::EventArgs^  e) {
	AdmissionSystem adm^ = gcnew AdmissionSystem();    //�J�[�h�Ƃ̐ڑ����s�����肷��N���X���C���X�^���X��
	//�J�[�h�҂���Ԃɂ��������ŁA���\�[�X�}�l�[�W���ւ̃A�h���X�������o�֊i�[����
	this->hContext = adm->WaittingCard();
	//�J�[�h�҂���Ԃ������_�C�A���O��\�����āA�L�����Z���������ꂽ��ڑ����I������
	if (MessageBox::Show("�J�[�h���������Ă��������B") == System::Windows::Forms::DialogResult::Cancel) {
		//���삪���f���ꂽ�|��\������
		MessageBox::Show("���삪���f����܂����B");
		//�ڑ����I������֐����Ăяo��
		adm->EndConnect(this->hContext, this->hCard);
	}//�J�[�h���������ꂽ��f�[�^�̎擾�Ɉڂ�
	else if (this->hCard = ::SCardConnect()) {
		//�J�[�h����f�[�^���擾����֐����Ăяo��
		this->Uid = adm->GetCardData(this->hContext, this->hCard);
		//�擾�����f�[�^�����ʂɕ\�����镶������쐬����
		this->CreateDisp();
	}
	return;
}


/*�T�v:�擾�����f�[�^�����Ƃɉ�ʂɕ\�����郉�x�����쐬����֐�
�쐬��:2017.10.10
�쐬��:K.Asada*/
private: System::Void CreateDisp() {
	std::string showdata = "";    //�\�����邽�߂̕�������i�[���邽�߂̕�����
	//���[�UID���e���񂪊i�[���ꂽ�e�L�X�g���J��
	ifstream file(this->Uid.c_str());
	//�X�g���[����蕶������擾����
	file >> showdata;
	//��������\�����邽�߂̃��x�����쐬����
	this->labelInfomasion->Text = showdata;
	//���[�U�̑����𔻒肷��
	if (this->CheckElement(this->Carddata)) {
		//���茋�ʂ�true�Ȃ�v���Ӑl���ł���|��\������
		this->labelCauntion->Text = "�v���Ӑl���ł��B";
	}
	return;
}


/*�T�v:���[�U�[�̑����𔻒肵�A����ɉ����������Ԃ��֐�
�쐬���F2017.10.10
�쐬�ҁFK.Asada*/
private: System::Void CheckElement(unsigned char[] elem) {
	int check = elem[ELEMENT_INDEX];    //�Ώۂ̃��[�U�[�̑������擾����
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
	return check;
}
};
}

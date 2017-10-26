#pragma once

#include "ConnectCard.h"
#include "SDKmifare.h"
#include "InputNewUserForm.h"
#include "AdmissionSystem.h"

namespace sdkmifare {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// AcceptanceForm �̊T�v
	/// </summary>
	public ref class AcceptanceForm : public System::Windows::Forms::Form
	{
	public:
		AcceptanceForm(void)
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
		~AcceptanceForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(764, 418);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(236, 117);
			this->button1->TabIndex = 0;
			this->button1->Text = L"�e�X�g�p";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &AcceptanceForm::button1_Click);
			// 
			// AcceptanceForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1128, 580);
			this->Controls->Add(this->button1);
			this->Name = L"AcceptanceForm";
			this->Text = L"AcceptanceForm";
			this->Load += gcnew System::EventHandler(this, &AcceptanceForm::AcceptanceForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
		/*�T�v:�t�H�[�����[�h���̃C�x���g
		�쐬��:2017.10.24
		�쐬��:K.Asada*/
	private: System::Void AcceptanceForm_Load(System::Object^  sender, System::EventArgs^  e) {
		this->InitPolling();
	}

			 /*�T�v:�|�[�����O���J�n����֐�
			 ����:�Ȃ�
			 �߂�l:�Ȃ�
			 �쐬��:2017.10.24
			 �쐬��:K.Asada*/
			 System::Void InitPolling() {
				 SDKmifare^ sdk = gcnew SDKmifare();      //���ފى�ʂ��C���X�^���X��
				 ConnectCard* con = new ConnectCard();    //�J�[�h�ʐM�N���X���C���X�^���X��
				 SCARDCONTEXT hContext = 0;               //�擾�������\�[�X�}�l�[�W���̃A�h���X
				 SCARDHANDLE hCard = 0;                   //�擾�����J�[�h�̃A�h���X
				 DWORD ActiveProtocol = 0;                //�ʐM�Ɏg���v���g�R��
				 //�A�v�����I������܂Ŗ������[�v������
				 for (;;) {
					 //�|�[�����O���J�n����
					 con->BeginPolling(hContext, hCard, ActiveProtocol);
					 //���ފى�ʂɎ擾�������\�[�X�}�l�[�W����n��
					 sdk->hContext = hContext;
					 //���ފى�ʂɎ擾�����A�h���X��n��
					 sdk->hCard = hCard;
					 //���ފى�ʂɃv���g�R����n��
					 sdk->ActiveProtocol = ActiveProtocol;
					 //���ފى�ʂ�\������
					 sdk->ShowDialog();
					 //��ʂ�����炢������ʐM���I������
					 con->EndConnect(hContext, hCard);
				 }
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		InputNewUserForm^ user = gcnew InputNewUserForm();
		AdmissionSystem* adm = new AdmissionSystem();
		user->ShowDialog();
		//adm->UpdateFileDate("asada.txt");
	}
	};
}

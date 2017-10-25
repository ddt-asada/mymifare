#pragma once

#include "ConnectCard.h"
#include "SDKmifare.h"

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
			this->SuspendLayout();
			// 
			// AcceptanceForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1128, 580);
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
	};
}

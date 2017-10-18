#pragma once

#include <vector>
#include <string>
#include "CONSTANTS.h"

namespace sdkmifare {

	using namespace CONSTANTGROUP;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// TimeCardForm �̊T�v
	/// </summary>
	public ref class TimeCardForm : public System::Windows::Forms::Form
	{
	public:
		TimeCardForm(void)
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
		~TimeCardForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::PictureBox^  pictureBox2;


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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(401, 51);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::White;
			this->pictureBox2->Location = System::Drawing::Point(0, 200);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(401, 51);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// TimeCardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(339, 270);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"TimeCardForm";
			this->Text = L"TimeCardForm";
			this->Load += gcnew System::EventHandler(this, &TimeCardForm::TimeCardForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public:
		std::vector<std::vector<unsigned char>>* carddata = new std::vector<std::vector<unsigned char>>();    //�J�[�h���擾�����f�[�^
		ConstantString^ Constants = gcnew ConstantString();    //�萔�N���X���C���X�^���X��

	private:
		/*�T�v:�^�C���J�[�h�̕\���쐬����֐�
		����:std::vector<std::vecor<unsigned char>> data:�J�[�h����M�����f�[�^
		�߂�l:System::Drawing::Bitmap^ img:�쐬�����\�摜
		�쐬��:2017.10.18
		�쐬��:K.Asada*/
		System::Drawing::Bitmap^ CreateTimes(std::vector<std::vector<unsigned char>> data) {
			std::vector<std::string> entertimes;    //���ٓ����i�[���镶����
			std::vector<std::string> leavetimes;    //�ފٓ����i�[���镶����
			int index = 0;    //���[�v�񐔂�ݒ肷�邽�߂̕ϐ�
			//�J�[�h�f�[�^�����ٓ����擾����
			entertimes = this->ConvEnterTimes(data);
			//�J�[�h�f�[�^���ފٓ����擾����
			leavetimes = this->ConvLeaveTimes(data);
			//���ٓ��̗v�f�����擾����
			index = entertimes.size();
			System::Drawing::Bitmap^ img = gcnew Bitmap(200 * 2 + 1, 50 * index + 1);    //�摜�p�̋�̃r�b�g�}�b�v���쐬
			System::Drawing::Graphics^ gr = System::Drawing::Graphics::FromImage(img);   //�`��p�̃O���t�B�b�N�N���X���C���X�^���X��
			System::Drawing::Font^ font = gcnew System::Drawing::Font(System::Drawing::FontFamily::GenericSansSerif, 12, System::Drawing::FontStyle::Regular);    //������`��p�̃t�H���g���C���X�^���X��
			//���ٓ��̑������s��
			for (int i = 0; i < entertimes.size(); i++) {
				//�\�摜�̊i�q��`�悷��
				gr->DrawRectangle(Pens::Black, 0, 50 * i, 200, 50);
				//�\�摜�̊i�q��`�悷��
				gr->DrawRectangle(Pens::Black, 200, 50 * i, 200, 50);
				//���ٓ���`�悷��
				gr->DrawString(gcnew String(entertimes[i].c_str()), font, Brushes::Black, 0, 50*i);
				
			}
			//�ފٓ��̑������s��
			for (int i = 0; i < leavetimes.size(); i++) {
				//�ފٓ���`�悷��
				gr->DrawString(gcnew String(leavetimes[i].c_str()), font, Brushes::Black, 200, 50 * i);
			}
			//�쐬�����摜��ԋp����
			return img;
		}

		/*�T�v:�^�C���J�[�h�̃^�C�g���������쐬����֐�
		����:std::vector<std::vecor<unsigned char>> data:�J�[�h����M�����f�[�^
		�߂�l:System::Drawing::Bitmap^ img:�쐬�����\�摜
		�쐬��:2017.10.18
		�쐬��:K.Asada*/
		System::Drawing::Bitmap^ InitPict(std::vector<std::vector<unsigned char>> data) {
			std::string years;    //�N�����i�[���邽�߂̕�����
			//�J�[�h�f�[�^���N�����擾����
			years = this->ConvYears(data);
			//��̃r�b�g�}�b�v�𐶐�����
			System::Drawing::Bitmap^ img = gcnew Bitmap(200 * 2 + 1, 100 +1);
			//�`��p�̃O���t�B�b�N�N���X�C���X�^���X��
			System::Drawing::Graphics^ gr = System::Drawing::Graphics::FromImage(img);
			//������`��p�̃t�H���g���C���X�^���X��
			System::Drawing::Font^ font = gcnew System::Drawing::Font(System::Drawing::FontFamily::GenericSansSerif, 12, System::Drawing::FontStyle::Regular);
			//�\�摜�̊i�q��`�悷��
			gr->DrawRectangle(Pens::Black, 0, 0, 200, 50);
			//�\�摜�̊i�q��`�悷��
			gr->DrawRectangle(Pens::Black, 200, 0, 200, 50);
			//�\�摜�̊i�q��`�悷��
			gr->DrawRectangle(Pens::Black, 0, 50, 200, 50);
			//�\�摜�̊i�q��`�悷��
			gr->DrawRectangle(Pens::Black, 200, 50, 200, 50);
			//�N����`�悷��
			gr->DrawString("�N��", font, Brushes::Black, 0, 0);
			//�N����`�悷��
			gr->DrawString(gcnew String(years.c_str()), font, Brushes::Black, 200, 0);
			//���ٓ���`�悷��
			gr->DrawString("���ٓ�", font, Brushes::Black, 0, 50);
			//�ފٓ���`�悷��
			gr->DrawString("�ފٓ�", font, Brushes::Black, 200, 50);
			//�쐬�����摜��Ԃ�
			return img;
		}

		/*�T�v:�J�[�h�Ɋi�[���ꂽ���������𕶎���ɕϊ�����֐�
		����:std::vector<std::vcotr<unsigned char>> data:�J�[�h�f�[�^
		�߂�l:std::vector<string> times:�������𕶎���ɕϊ������z��
		�쐬��:2017.10.16
		�쐬��:K.Asada*/
private: std::vector<std::string> ConvEnterTimes(std::vector<std::vector<unsigned char>> data) {
	try {
		std::vector<std::string> times;        //�������𕶎���ɕϊ��������̂��i�[���邽�߂̔z��
		ITOC gettimes;                         //�J�[�h�f�[�^�̒��ɂ���char�^�̐��l��unsigned int�^�ɕϊ����邽�߂̋��L��
		int day = 0;                           //�擾���������i�[����ϐ�
		int hour = 0;                          //�擾�������Ԃ��i�[����ϐ�
		int min = 0;                           //�擾���������i�[����ϐ�
		int timeindex = TIMES_1_INDEX;
		//�J�[�h�f�[�^�ɂ�����������𑖍����Ă���
		for (int i = 1; data[timeindex][i * 2] != ' '; i++) {
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
			times.push_back(std::to_string(day) + "��" + std::to_string(hour) + "��" + std::to_string(min) + "��" + '\n');
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

		 /*�T�v:�J�[�h�Ɋi�[���ꂽ�ފَ��Ԃ��擾���邽�߂̊֐�
		 ����:std::vector<std::vcotr<unsigned char>> data:�J�[�h�f�[�^
		 �߂�l:std::vector<string> times:�������𕶎���ɕϊ������z��
		 �쐬��:2017.10.17
		 �쐬��:K.Asada*/
		 private: std::vector<std::string> ConvLeaveTimes(std::vector<std::vector<unsigned char>> data) {
			 try {
				std::vector<std::string> times;        //�������𕶎���ɕϊ��������̂��i�[���邽�߂̔z��
				 ITOC gettimes;                         //�J�[�h�f�[�^�̒��ɂ���char�^�̐��l��unsigned int�^�ɕϊ����邽�߂̋��L��
				 int day = 0;                           //�擾���������i�[����ϐ�
				 int hour = 0;                          //�擾�������Ԃ��i�[����ϐ�
				 int min = 0;                           //�擾���������i�[����ϐ�
				 int timeindex = LEAVE_1_INDEX;
				 //�J�[�h�f�[�^�ɂ�����������𑖍����Ă���
				 for (int i = 0; data[timeindex][i * 2] != ' '; i++) {
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
					 times.push_back(std::to_string(day) + "��" + std::to_string(hour) + "��" + std::to_string(min) + "��" + '\n');
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
	private: System::Void TimeCardForm_Load(System::Object^  sender, System::EventArgs^  e) {
		//�^�C�g�������̕\�摜���쐬����
		this->pictureBox1->Image = this->InitPict(*this->carddata);
		//�\�摜�̒��g���쐬����
		this->pictureBox2->Image = this->CreateTimes(*this->carddata);
	}
};
}

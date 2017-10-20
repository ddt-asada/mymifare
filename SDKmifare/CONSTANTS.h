#pragma once

#define PCSC_TRANS_BUFF_LEN	(262)

#include <tchar.h>

/*�T�v:�萔�N���X
�쐬��:2017.10.10
�쐬��:K.Asada*/
namespace CONSTANTGROUP {
	//���M�R�}���h�p�\����
	typedef struct send {
		int           sendLength;
		unsigned char sendCommand[PCSC_TRANS_BUFF_LEN];
	} SENDCOMM;

	union ITOC {
		unsigned short int num;
		char bytes[sizeof(unsigned short int)];
	};

	union TOC {
		unsigned int num;
		char bytes[sizeof(unsigned int)];
	};

	//�������݂̎n�_�ƂȂ�u���b�N
	static const int BEGIN_BLOCK = 8;
	//�������݂̏I�_�ƂȂ�u���b�N
	static const int END_BLOCK = 37;
	//�������ރu���b�N�̐�
	static const int BLOCK_COUNT = END_BLOCK - BEGIN_BLOCK;
	//���[�U�[�����i�[����Ă���u���b�N�ԍ�
	static const int NAME_INDEX = 1;
	//���[�U�[�t���K�i���i�[����Ă���u���b�N�ԍ�
	static const int KANA_INDEX = 2;
	//���[�U�[ID���i�[����Ă���u���b�N�ԍ�
	static const int UID_INDEX = 0;
	//�p�X���[�h���i�[����Ă���u���b�N�ԍ�
	static const int PASS_INDEX = 3;
	//�������i�[����Ă���u���b�N�ԍ�
	static const int ELEM_INDEX = 5;
	//�������i�[����Ă���u���b�N�ԍ�
	static const int ADM_INDEX = 5;
	//�E�킪�i�[����Ă���u���b�N�ԍ�
	static const int OCCUP_INDEX = 5;
	//�������i�[����Ă���u���b�N�ԍ�
	static const int DEPART_INDEX = 5;
	//��E���i�[����Ă���u���b�N�ԍ�
	static const int POS_INDEX = 5;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	static const int ADRESS_1_INDEX = 6;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	static const int ADRESS_2_INDEX = 7;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	static const int ADRESS_3_INDEX = 8;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	static const int ADRESS_4_INDEX = 9;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	static const int ADRESS_5_INDEX = 10;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	static const int ADRESS_6_INDEX = 11;
	//�d�b�ԍ����i�[����Ă���u���b�N�ԍ�
	static const int TELL_INDEX = 4;
	//�a�������i�[����Ă���u���b�N�ԍ�
	static const int BIRTH_INDEX = 5;
	//�N�����i�[����Ă���u���b�N�ԍ�
	static const int YEAR_INDEX = 12;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	static 	const int TIMES_1_INDEX = 12;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	static const int TIMES_2_INDEX = 13;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	static const int TIMES_3_INDEX = 14;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	static const int TIMES_4_INDEX = 15;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	static 	const int LEAVE_1_INDEX = 18;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	static const int LEAVE_2_INDEX = 19;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	static const int LEAVE_3_INDEX = 20;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	static const int LEAVE_4_INDEX = 21;
	//�I�[�̃u���b�N�ԍ�
	static const int END_INDEX = 22;
	//������1�r�b�g�ڂ̖��O
	static const char* ELEM_NAME1 = "���";
	//������2�r�b�g�ڂ̖��O
	static const char* ELEM_NAME2 = "�댯�l��";
	//������3�r�b�g�ڂ̖��O
	static const char* ELEM_NAME3 = "�v���Ӑl��";
	//������4�r�b�g�ڂ̖��O
	static const char* ELEM_NAME4 = "";
	//������1�r�b�g�ڂ̖��O
	static const char* ADM_NAME1 = "���";
	//������2�r�b�g�ڂ̖��O
	static const char* ADM_NAME2 = "�Ǘ���";
	//�E���1�r�b�g�ڂ̖��O
	static const char* OCCUP_NAME1 = "���O���[�v";
	//�E���2�r�b�g�ڂ̖��O
	static const char* OCCUP_NAME2 = "���O���[�v";
	//�E���3�r�b�g�ڂ̖��O
	static const char* OCCUP_NAME3 = "��O�O���[�v";
	//�E���4�r�b�g�ڂ̖��O
	static const char* OCCUP_NAME4 = "";
	//������1�r�b�g�ڂ̖��O
	static const char* DEPART_NAME1 = "�c�ƕ�";
	//������2�r�b�g�ڂ̖��O
	static const char* DEPART_NAME2 = "������";
	//������3�r�b�g�ڂ̖��O
	static const char* DEPART_NAME3 = "�J����";
	//������4�r�b�g�ڂ̖��O
	static const char* DEPART_NAME4 = "";
	//��E��1�r�b�g�ڂ̖��O
	static const char* POS_NAME1 = "���Ј�";
	//��E��2�r�b�g�ڂ̖��O
	static const char* POS_NAME2 = "�p�[�g";
	//��E��3�r�b�g�ڂ̖��O
	static const char* POS_NAME3 = "����";
	//��E��4�r�b�g�ڂ̖��O
	static const char* POS_NAME4 = "";
	//���O�i���j�̃��x���̖��O
	static const char* FIRST_NAME = "���O�i���j�F";
	//���O�i���j�̃��x���̖��O
	static const char* LAST_NAME = "���O�i���j�F";
	//�Z���̃��x���̖��O
	static const char* ADDRESS_LABEL = "�Z�@�@�@���F";
	//�d�b�ԍ��̃��x���̖��O
	static const char* TELL_LABEL = "�d�b�ԍ��F";
	//�a�����̃��x���̖��O
	static const char* BIRTH_LABEL = "�a ��  ���F";
	//�����̃��x���̖��O
	static const char* ELEM_LABEL = "���@�@�@���F";
	//�����̃��x���̖��O
	static const char* ADM_LABEL = "���@�@�@���F";
	//��E�̃��x���̖��O
	static const char* OCCUP_LABEL = "���@�@�@�E�F";
	//�O���[�v�̃��x���̖��O
	static const char* GROUP_LABEL = "�O �� �[ �v�F";
	//�����̃��x���̖��O
	static const char* DEPART_LABEL = "���@�@�@���F";
	static const SENDCOMM LOADKEY = { 11,{ 0xFF,0x82,0x00,0x00,0x06,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF } };
	//�Z�N�^�[�F�؃R�}���h�A�e�Z�N�^�[�ɃA�N�Z�X����O�ɍs��Ȃ���΂Ȃ�Ȃ�(�ڍׂ̓��t�@�����X�Q��)
	// General Authenticate
	static const SENDCOMM AUTHENTICATE = { 10,{ 0xFF,0x86,0x00,0x00,0x05,0x01,0x00,BEGIN_BLOCK,0x60,0x00 } };
	//�f�[�^��M�R�}���h�A�J�[�h�̃f�[�^����M����ۂɎg�p(�ڍׂ̓��t�@�����X�Q��)
	//ReadBinary
	static const SENDCOMM READCARD = { 5,{ 0xFF,0xB0,0x00,BEGIN_BLOCK,0x00 } };
	//�f�[�^���M�R�}���h�A�J�[�h�Ƀf�[�^�𑗐M����ۂɎg�p(�ڍׂ̓��t�@�����X�Q��)
	//UpdateBinary
	static const SENDCOMM SENDCARD = { 21,{ 0xFF,0xD6,0x00,BEGIN_BLOCK,0x10 } };
	//���M�R�}���h�̏I�������߂��R�}���h
	static const SENDCOMM ENDCOMMAND = { -1, NULL };

	public ref class ConstantString {
	public:
		ConstantString() {

		}

		//�V�K�쐬���ɕ\������郁�b�Z�[�W
		static System::String^ NEW_MESSAGE = "�V�K�ō쐬���܂��B\n������͂��Ă��������B";
		//�J�[�h���������w���̃��b�Z�[�W
		static System::String^ SET_CARD_MESSAGE = "�J�[�h���������Ă�������";
		//�쐬�������̃��b�Z�[�W
		static System::String^ FINISH_MESSAGE = "�J�[�h���쐬����܂���";
		//����L�����Z�����̃��b�Z�[�W
		static System::String^ CANCEL_MESSAGE = "���삪���f����܂����B";
		//�ފَ��̃��b�Z�[�W
		static System::String^ LEAVE_MESSAGE = "�ފق��܂����B";
		//���َ��̃��b�Z�[�W
		static System::String^ ENTER_MESSAGE = "���ق��܂����B";
		//���ɓ��ٍς݂̏ꍇ�ɕ\�����郁�b�Z�[�W
		static System::String^ ALREADY_ENTER_MESSAGE = "���ɓ��ٍς݂ł��B";
		//���ق��Ă��Ȃ��Ƃ��ɕ\�����郁�b�Z�[�W
		static System::String^ NOT_ENTER_MESSAGE = "���ْ��̃��[�U�[�����܂���B";
		//��O�������̃��b�Z�[�W
		static System::String^ ERROR_MESSAGE = "�G���[���������܂����B";
		//�X�}�[�g�J�[�h�T�[�r�X�������Ă��Ȃ����̃��b�Z�[�W
		static System::String^ NO_SERVICE_ERROR = "�X�}�[�g�J�[�h�T�[�r�X���ғ����Ă��܂���B";
		//�J�[�h���ݒu����Ă��Ȃ��Ƃ��̃��b�Z�[�W
		static System::String^ REMOVE_ERROR = "�J�[�h�����m�ł��܂���B";
		//���[�U�[ID���o�^����Ă��Ȃ��Ƃ��̃��b�Z�[�W
		static System::String^ ID_NOT_FOUND_ERROR = "�Ώۂ�ID��������܂���B";
		//�p�X���[�h���Ԉ���Ă���Ƃ��̂Ƃ��̃��b�Z�[�W
		static System::String^ PASS_NOT_FOUND_ERROR = "�p�X���[�h���Ⴂ�܂��B";
		//���͂��ꂽ������������̕������𒴂��Ă���Ƃ��̃��b�Z�[�W
		static System::String^ OVER_ERROR_MESSAGE = "�����������𒴂��Ă��܂��B\n���͂��Ȃ����Ă��������B";
		//���[�U�[ID�����͂���Ă��Ȃ��Ƃ��ɕ\�����郁�b�Z�[�W
		static System::String^ EMPTY_ERROR_MESSAGE = "���͂���Ă��Ȃ��ꏊ������܂��B\n���͂��Ȃ����Ă��������B";
		//���[�U�[ID�������͂̎��ɕ\�����郁�b�Z�[�W
		static System::String^ IDEMPTY_ERROR_MESSAGE = "���[�U�[ID�������͂ł��B\n�m�F���Ă��������B";
		//�댯�l���ł���Ƃ��̃��b�Z�[�W
		static System::String^ CAUNTION_MESSAGE = "�댯�l���ł��B���ق����ۂ��܂��B";
		//������1�r�b�g�ڂ̖��O
		static System::String^ CLI_ELEM_NAME1 = gcnew System::String(ELEM_NAME1);
		//������2�r�b�g�ڂ̖��O
		static System::String^ CLI_ELEM_NAME2 = gcnew System::String(ELEM_NAME2);
		//������3�r�b�g�ڂ̖��O
		static System::String^ CLI_ELEM_NAME3 = gcnew System::String(ELEM_NAME3);
		//������4�r�b�g�ڂ̖��O
		static System::String^ CLI_ELEM_NAME4 = gcnew System::String(ELEM_NAME4);
		//������1�r�b�g�ڂ̖��O
		static System::String^ CLI_ADM_NAME1 = gcnew System::String(ADM_NAME1);
		//������2�r�b�g�ڂ̖��O
		static System::String^ CLI_ADM_NAME2 = gcnew System::String(ADM_NAME2);
		//�E���1�r�b�g�ڂ̖��O
		static System::String^ CLI_OCCUP_NAME1 = gcnew System::String(OCCUP_NAME1);
		//�E���2�r�b�g�ڂ̖��O
		static System::String^ CLI_OCCUP_NAME2 = gcnew System::String(OCCUP_NAME2);
		//�E���3�r�b�g�ڂ̖��O
		static System::String^ CLI_OCCUP_NAME3 = gcnew System::String(OCCUP_NAME3);
		//�E���4�r�b�g�ڂ̖��O
		static System::String^ CLI_OCCUP_NAME4 = gcnew System::String(OCCUP_NAME4);
		//������1�r�b�g�ڂ̖��O
		static System::String^ CLI_DEPART_NAME1 = gcnew System::String(DEPART_NAME1);
		//������2�r�b�g�ڂ̖��O
		static System::String^ CLI_DEPART_NAME2 = gcnew System::String(DEPART_NAME2);
		//������3�r�b�g�ڂ̖��O
		static System::String^ CLI_DEPART_NAME3 = gcnew System::String(DEPART_NAME3);
		//������4�r�b�g�ڂ̖��O
		static System::String^ CLI_DEPART_NAME4 = gcnew System::String(DEPART_NAME4);
		//��E��1�r�b�g�ڂ̖��O
		static System::String^ CLI_POS_NAME1 = gcnew System::String(POS_NAME1);
		//��E��2�r�b�g�ڂ̖��O
		static System::String^ CLI_POS_NAME2 = gcnew System::String(POS_NAME2);
		//��E��3�r�b�g�ڂ̖��O
		static System::String^ CLI_POS_NAME3 = gcnew System::String(POS_NAME3);
		//��E��4�r�b�g�ڂ̖��O
		static System::String^ CLI_POS_NAME4 = gcnew System::String(POS_NAME4);
	};
}
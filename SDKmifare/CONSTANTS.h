#pragma once

#define PCSC_TRANS_BUFF_LEN	(262)

#include <tchar.h>

/*�T�v:�萔�N���X
�쐬��:2017.10.10
�쐬��:K.Asada*/
namespace CONSTANTGROUP {
		//���M�R�}���h�p�\����
		typedef struct send{
			int           sendLength;
			unsigned char sendCommand[PCSC_TRANS_BUFF_LEN];
		} SENDCOMM;

		//�������݂̎n�_�ƂȂ�u���b�N
		static const int BEGIN_BLOCK = 8;

		static const int BIT_BLOCK = 19;
		//�������݂̏I�_�ƂȂ�u���b�N
		static const int END_BLOCK = 26;
		//�������ރu���b�N�̐�
		static const int BLOCK_COUNT = END_BLOCK - BEGIN_BLOCK;
		//�L�[�F�؃R�}���h�A�R�}���h���M���̍ŏ��ɍs��Ȃ���΂Ȃ�Ȃ�(�ڍׂ̓��t�@�����X�Q��)
		//Load Key Mifare Default Key(FFFFFFFFFFFF)
	//	static const SENDCOMM LOADKEY;
		//�Z�N�^�[�F�؃R�}���h�A�e�Z�N�^�[�ɃA�N�Z�X����O�ɍs��Ȃ���΂Ȃ�Ȃ�(�ڍׂ̓��t�@�����X�Q��)
		// General Authenticate
	//	static const SENDCOMM AUTHENTICATE;
		//�f�[�^��M�R�}���h�A�J�[�h�̃f�[�^����M����ۂɎg�p(�ڍׂ̓��t�@�����X�Q��)
		//ReadBinary
	//	static const SENDCOMM READCARD;
		//�f�[�^���M�R�}���h�A�J�[�h�Ƀf�[�^�𑗐M����ۂɎg�p(�ڍׂ̓��t�@�����X�Q��)
	//	//UpdateBinary
	//	static const SENDCOMM SENDCARD;
		//���[�U�[�����i�[����Ă���u���b�N�ԍ�
		static const int NAME_INDEX = 0;
		//���[�U�[�t���K�i���i�[����Ă���u���b�N�ԍ�
		static const int KANA_INDEX = 1;
		//���[�U�[ID���i�[����Ă���u���b�N�ԍ�
		static const int UID_INDEX = 2;
		//�p�X���[�h���i�[����Ă���u���b�N�ԍ�
		static const int PASS_INDEX = 2;
		//�������i�[����Ă���u���b�N�ԍ�
		static const int ELEM_INDEX = 2;
		//�������i�[����Ă���u���b�N�ԍ�
		static const int ADM_INDEX = 2;
		//�Z�����i�[����Ă���u���b�N�ԍ�
		static const int ADRESS_1_INDEX = 3;
		//�Z�����i�[����Ă���u���b�N�ԍ�
		static const int ADRESS_2_INDEX = 4;
		//�Z�����i�[����Ă���u���b�N�ԍ�
		static const int ADRESS_3_INDEX = 5;
		//�Z�����i�[����Ă���u���b�N�ԍ�
		static const int ADRESS_4_INDEX = 6;
		//�Z�����i�[����Ă���u���b�N�ԍ�
		static const int ADRESS_5_INDEX = 7;
		//�N�����i�[����Ă���u���b�N�ԍ�
		static const int YEAR_INDEX = 8;
		//���ފٓ����i�[����Ă���u���b�N�ԍ�
		static 	const int TIMES_1_INDEX = 9;
		//���ފٓ����i�[����Ă���u���b�N�ԍ�
		static const int TIMES_2_INDEX = 10;
		//���ފٓ����i�[����Ă���u���b�N�ԍ�
		static 	const int TIMES_3_INDEX = 11;
		//���ފٓ����i�[����Ă���u���b�N�ԍ�
		static const int TIMES_4_INDEX = 12;
		//���ފٓ����i�[����Ă���u���b�N�ԍ�
		static 	const int TIMES_5_INDEX = 13;
		//���ފٓ����i�[����Ă���u���b�N�ԍ�
		static const int TIMES_6_INDEX = 14;
		//�J�[�h���[�_�̖��O
		//static const LPTSTR PASORI_NAME;

static const LPTSTR PASORI_NAME = _T("Sony FeliCa Port/PaSoRi 3.0 0");
	static const SENDCOMM LOADKEY = { 11,{ 0xFF,0x82,0x00,0x00,0x06,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF } };
	//�Z�N�^�[�F�؃R�}���h�A�e�Z�N�^�[�ɃA�N�Z�X����O�ɍs��Ȃ���΂Ȃ�Ȃ�(�ڍׂ̓��t�@�����X�Q��)
	// General Authenticate
	static const SENDCOMM AUTHENTICATE = { 10,{ 0xFF,0x86,0x00,0x00,0x05,0x01,0x00,BEGIN_BLOCK,0x60,0x00 } };
	//�f�[�^��M�R�}���h�A�J�[�h�̃f�[�^����M����ۂɎg�p(�ڍׂ̓��t�@�����X�Q��)
	//ReadBinary
	static const SENDCOMM READCARD = { 5,{ 0xFF,0xB0,0x00,(unsigned char)BEGIN_BLOCK,0x00 } };
	//�f�[�^���M�R�}���h�A�J�[�h�Ƀf�[�^�𑗐M����ۂɎg�p(�ڍׂ̓��t�@�����X�Q��)
	//UpdateBinary
	static const SENDCOMM SENDCARD = { 21,{ 0xFF,0xD6,0x00,(unsigned char)BEGIN_BLOCK,0x10 } };
}
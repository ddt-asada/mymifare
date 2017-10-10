#pragma once

#define PCSC_TRANS_BUFF_LEN	(262)

/*�T�v:�萔�N���X
�쐬��:2017.10.10
�쐬��:K.Asada*/

public class CONSTANTS {
public:
	//�f�t�H���g�R���X�g���N�^
	CONSTANTS() {
	}

	//���M�R�}���h�p�\����
	typedef struct send{
		int           sendLength;
		unsigned char sendCommand[PCSC_TRANS_BUFF_LEN];
	} SENDCOMM;
	
	//�������݂̎n�_�ƂȂ�u���b�N
	const int BEGIN_BLOCK = 8;
	//�������݂̏I�_�ƂȂ�u���b�N
	const int END_BLOCK = 26;
	//�������ރu���b�N�̐�
	const int BLOCK_COUNT = END_BLOCK - BEGIN_BLOCK;
	//�L�[�F�؃R�}���h�A�R�}���h���M���̍ŏ��ɍs��Ȃ���΂Ȃ�Ȃ�(�ڍׂ̓��t�@�����X�Q��)
	//Load Key Mifare Default Key(FFFFFFFFFFFF)
	SENDCOMM LOADKEY = { 11,{0xFF,0x82,0x00,0x00,0x06,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF} };
	//�Z�N�^�[�F�؃R�}���h�A�e�Z�N�^�[�ɃA�N�Z�X����O�ɍs��Ȃ���΂Ȃ�Ȃ�(�ڍׂ̓��t�@�����X�Q��)
	// General Authenticate
	SENDCOMM AUTHENTICATE = { 10,{0xFF,0x86,0x00,0x00,0x05,0x01,0x00,BEGIN_BLOCK,0x60,0x00} };
	//�f�[�^��M�R�}���h�A�J�[�h�̃f�[�^����M����ۂɎg�p(�ڍׂ̓��t�@�����X�Q��)
	//ReadBinary
	SENDCOMM READCARD = { 5,{0xFF,0xB0,0x00,BEGIN_BLOCK,0x00} };
	//�f�[�^���M�R�}���h�A�J�[�h�Ƀf�[�^�𑗐M����ۂɎg�p(�ڍׂ̓��t�@�����X�Q��)
	//UpdateBinary
	SENDCOMM SENDCARD = { 21,{0xFF,0xD6,0x00,BEGIN_BLOCK,0x00} };
	//���[�U�[�����i�[����Ă���u���b�N�ԍ�
	const int NAME_INDEX = 0;
	//���[�U�[�t���K�i���i�[����Ă���u���b�N�ԍ�
	const int KANA_INDEX = 1;
	//���[�U�[ID���i�[����Ă���u���b�N�ԍ�
	const int UID_INDEX = 2;
	//�p�X���[�h���i�[����Ă���u���b�N�ԍ�
	const int PASS_INDEX = 2;
	//�������i�[����Ă���u���b�N�ԍ�
	const int ELEM_INDEX = 2;
	//�������i�[����Ă���u���b�N�ԍ�
	const int ADM_INDEX = 2;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	const int ADRESS_1_INDEX = 3;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	const int ADRESS_2_INDEX = 4;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	const int ADRESS_3_INDEX = 5;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	const int ADRESS_4_INDEX = 6;
	//�Z�����i�[����Ă���u���b�N�ԍ�
	const int ADRESS_5_INDEX = 7;
	//�N�����i�[����Ă���u���b�N�ԍ�
	const int YEAR_INDEX = 8;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	const int TIMES_1_INDEX = 9;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	const int TIMES_2_INDEX = 10;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	const int TIMES_3_INDEX = 11;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	const int TIMES_4_INDEX = 12;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	const int TIMES_5_INDEX = 13;
	//���ފٓ����i�[����Ă���u���b�N�ԍ�
	const int TIMES_6_INDEX = 14;
	//�J�[�h���[�_�̖��O
	const char* PASORI_NAME = "Sony FeliCa Port / PaSoRi 3.0";
	//���\�[�X�}�l�[�W���̊m�ۂɎ��s�������ɕ\������G���[���b�Z�[�W
//	System::String^ NO_SERVICE_ERROR = "SCard�V�X�e���ŃG���[������";
};
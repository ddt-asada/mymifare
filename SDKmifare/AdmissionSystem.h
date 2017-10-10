#pragma once

#include <iostream>
#include "ConnectCard.h"
#include "CONSTANTS.h"

public class AdmissionSystem {
public:
	AdmissionSystem() {

	}

	CONSTANTS* constants;    //�萔�N���X���C���X�^���X��

	/*�T�v:�Ώۂ̃��[�U�[�̃f�[�^�����݂��Ă��邩���m�F���邽�߂̊֐�
	����:unsigned data:�J�[�h���擾�����S�f�[�^
	�߂�l:string uid:�J�[�h���擾�������[�U�[ID
	�쐬���F2017.10.10
	�쐬��:K.Asada*/
	std::string CheckUser(unsigned char data) {
	/*	std::string uid = "";        //�J�[�h���擾�������[�U�[ID���i�[���邽�߂̕�����
		std::string name = "";       //�J�[�h���擾�������[�U�[�����i�[���邽�߂̕�����
		std::string pass = "";       //�J�[�h���擾�������[�U�[�̃p�X���[�h���i�[���邽�߂̕�����
		//���[�U�[ID���i�[���ꂽ�u���b�N���w�肵�ă��[�U�[ID���擾����
		uid = GetData(data, ID_INDEX);
		//���[�U�[ID���t�@�C�����Ƃ����t�@�C�����J���Ȃ��Ƃ��̓��[�U�[�����݂��Ă��Ȃ��Ƃ��ė�O�𓊂���
		if (!ifstream file(uid)) {
			//�Ώۂ̃��[�U�[�����݂��Ă��Ȃ��|���O�Ƃ��ē�����
			throw gcnew System::Exception("�Ώۂ�ID�����݂��Ă��܂���");
		}//����ȊO�̎��̓p�X���[�h�̔���Ɉڂ�
		else {
			//���[�U�[���̃u���b�N���w�肵�ă��[�U�[�����擾����
			name = GetData(data, NAME_INDEX);
			//�p�X���[�h�̃u���b�N���w�肵�ăp�X���[�h���擾����
			pass = GetData(data, PASS_INDEX);
			//�p�X���[�h�̔���Ɉڂ�
			CheckPass(name, pass, file);
		}
		//���肪�I������烆�[�U�[ID��ԋp����
		return uid;*/
	}

	/*�T�v:�Ώۂ̃��[�U�[�̃p�X���[�h���m�F���A���������𔻒肷�邽�߂̊֐�
	����:string name:���[�U�[�̖��O
	    :string pass:���[�U�[�����͂����p�X���[�h
		:ifstream file:���[�U�̏�񂪊i�[���ꂽ�t�@�C���ւ̃X�g���[��
	�߂�l:bool:�ƍ����ʂ̐���
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	bool CheckPass(std::string name, std::string pass, std::ifstream file) {
		std::string getname = "";        //�t�@�C�����擾�������O���i�[���邽�߂̕�����
		std::string getpass = "";        //�t�@�C�����擾�����p�X���i�[���邽�߂̕�����
		//�X�g���[����薼�O���擾����
		file >> getname;
		//�X�g���[�����p�X���擾����
		file >> getpass;
		//���O����������O�𓊂���
		if (getname != name) {
			//���O���Ⴄ�|�̗�O�𓊂���
			throw gcnew System::Exception("���[�U�[�����s���ł��B");
		}
		//�p�X����������O�𓊂���
		if (getpass != pass) {
			//�p�X���Ⴄ�|�̗�O�𓊂���
			throw gcnew System::Exception("�p�X���[�h���s���ł��B");
		}
		//�����܂ŗ����琬�������Ƃ���true��ԋp
		return true;
	}

	/*�T�v�F�J�[�h���擾����unsigned char��蕶������擾���邽�߂̊֐�
	����:unsigned char data:�J�[�h���擾�����ϐ�
	    :int index:�擾�Ώۂ̕����񂪑��݂���u���b�N
	�߂�l:string datastring:�擾����������
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	std::string GetData(unsigned char data, int index) {
/*		std::string datastring = "";    //�擾������������i�[���邽�߂̕�����
		//�Ώۂ̃u���b�N���炷�ׂĂ̕�������擾����܂ŌJ��Ԃ�
		for (int i = 0; i < data[index].length, i++) {
			//1��������������擾���Ċi�[���Ă���
			datastring += data[index][i];
		}
		//�擾�����������ԋp����
		return datasting;*/
	}
	
	/*�T�v:�J�[�h�֑��M����f�[�^�̑g�ݗ��āA�R�}���h�̍쐬���s���֐�
	����:string setdata:���M����f�[�^
	�߂�l:unsigned char:�f�[�^�𑗐M���邽�߂̃R�}���h
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	unsigned char ReadySetData(std::string) {
/*		//���M�R�}���h�̏����������ɓ����镔��
		unsigned char[2 + BLOCK_COUNT] = { {11,{0xFF,0x82,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}},
										  {10,{0xFF,0x86,0x00,0x00,0x05,0x01,0x00,0x04,0x60,0x00}}};
		//�S�f�[�^�𑗐M���邽�߂̑��M�R�}���h��g�ݗ��ĂĂ���
		for (int i = 0; i < BLOCK_COUNT; i++) {
			//4�̔{��-1�̃Z�N�^�[�̏I�[�u���b�N�ŃL�[���i�[����Ă��邽�ߕҏW�������Ȃ��̂œǂݔ�΂�
			if (i % 4 == 3) {
				//���̃Z�N�^�[�ւ̔F�؂��s���R�}���h���Z�b�g����
				senddata[2 + i] = { 10,{0xFF,0x86,0x00,0x00,0x05,0x01,0x00,i + 1,0x60,0x00} };
			}//����ȊO�̎��͒ʏ�ʂ�f�[�^�𑗐M���邽�߂̃R�}���h��g�ݗ��ĂĂ���
			else {
				//�����񂩂�f�[�^�����o���A�R�}���h��g�ݗ��ĂĂ���
				for (int j = 0;; j++) {
					//���s�����ɂ��ǂ蒅���܂ŕ�������i�[���Ă���
					if (setdata != '\n') {
						//���M�R�}���h��g�ݗ��ĂĂ���
						senddata[2 + i].bCommand[j] = setdata;
					}//���s�����ɂ��ǂ蒅������R�}���h�̑g�ݗ��Ă��I�����Ď��̃u���b�N�Ɉڂ�
					else {
						//���[�v�𔲂���
						break;
					}
				}
			}
		}
		//���M�R�}���h�̏I���ɃR�}���h�̏I�����Ӗ�����R�}���h���i�[����
		senddata[2 + BLOCK_COUNT] = { -1, NULL };
		//�g�ݗ��Ă����M�R�}���h��ԋp����
		return senddata;*/
	}

	/*�T�v:�J�[�h�փf�[�^�𑗐M���邽�߂̊֐�
	����:unsigned long hContext:�擾�������\�[�X�}�l�[�W��
	    :unsigned long hCard:�擾�����J�[�h
		:string uid:�擾�����J�[�h�̃��[�U�[ID
	�߂�l:�Ȃ�
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	void SetCardData(unsigned long hContext, unsigned long hCard, std::string uid) {
/*		std::string setdata = "";        //���M����f�[�^���i�[���邽�߂̕�����
		ifstream file(uis);              //���M�f�[�^���i�[���ꂽ�t�@�C�������[�U�[ID���J��
		unsigned char[BLOCK_COUNT] alldata = { '\0' };    //���M�R�}���h���i�[���邽�߂̕�����
		//���M�R�}���h���쐬����֐����Ăяo��
		alldata = ReadySetData(setdata);
		//�J�[�h�փR�}���h�𑗐M����֐����Ăяo��
		Transmit(hContext, hCard, alldata);
		//�ڑ����I������֐����Ăяo��
		EndConnect(hContext, hCard);
		return;*/
	}

	/*�T�v:�J�[�h����f�[�^����M���邽�߂̊֐�
	����:unsigned long hContext:�擾�������\�[�X�}�l�[�W��
	    :unsigned long hCard:�擾�����J�[�h
	�߂�l:string uid:�J�[�h���擾�������[�U�[ID
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	std::string GetCardData(unsigned char hContext, unsigned char hCard,std::string pass, unsigned long ActiveProtocol) {
		ConnectCard* con;
		unsigned char** getdata = { '\0' };    //�擾�����J�[�h�f�[�^���i�[���邽�߂̕ϐ�
		//���M�R�}���h���i�[���邽�߂̕ϐ��A�����l�Ƃ��ăL�[�F�؋y�уZ�N�^�F�؂��i�[
		CONSTANTS::SENDCOMM SendComm[21] = {constants->LOADKEY, constants->AUTHENTICATE};
		//���M�R�}���h��g�ݗ��Ă邽�߂�for��
		for (int i = 0; i < constants->BLOCK_COUNT; i++) {
			//�Ώۂ̃u���b�N��4�̔{��-1�̎��̓Z�N�^�̏I�[�u���b�N�ł���A�L�[�����̊Ǘ��p�̏�񂪊i�[����Ă��邽�ߓǂݔ�΂�
			if (i % 4 == 3) {
				//���̃Z�N�^�ւ̔F�؂��s���i4�u���b�N���ƂɃZ�N�^���؂�ւ�邽�߁j
				SendComm[2 + i] = { constants->AUTHENTICATE.sendLength, constants->AUTHENTICATE.sendCommand[7] += (i + 1) };
			}//����ȊO�̎��͒ʏ�ʂ�Ώۂ̃u���b�N����f�[�^���擾����
			else {
				//�f�[�^����M���邽�߂̃R�}���h���i�[����
				SendComm[2 + i] = { constants->READCARD.sendLength, constants->READCARD.sendCommand[3] = i+ constants->BLOCK_COUNT };
			}
		}
		//�쐬�������M�R�}���h�̏I���ɑ��M�R�}���h�̏I���������R�}���h���i�[����
		SendComm[2 + constants->BLOCK_COUNT] = { -1,NULL };
		//�f�[�^����M����R�}���h�𑗐M���ăf�[�^���擾����
		getdata = con->Transmit(hContext, hCard, SendComm, ActiveProtocol);
		//�擾�����f�[�^�̃��[�U�����ƍ����A���[�UID���擾����
//		uid = CheckUser(getdata);
		//�擾�������[�U�[ID��ԋp����
		return "aaa";
	}
};
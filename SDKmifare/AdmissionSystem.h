#pragma once

#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <msclr/gcroot.h>
#include "ConnectCard.h"
#include "CONSTANTS.h"

using namespace CONSTANTGROUP;

public class AdmissionSystem {
public:
	AdmissionSystem() {

	}

	msclr::gcroot<ConstantString^> Constants = gcnew ConstantString();

	/*�T�v:�Ώۂ̃��[�U�[�̃f�[�^�����݂��Ă��邩���m�F���邽�߂̊֐�
	����:unsigned data:�J�[�h���擾�����S�f�[�^
	�߂�l:string uid:�J�[�h���擾�������[�U�[ID
	�쐬���F2017.10.10
	�쐬��:K.Asada*/
	std::string CheckUser(std::vector<std::vector<unsigned char>> data, std::string pass) {
		std::string uid = "";        //�J�[�h���擾�������[�U�[ID���i�[���邽�߂̕�����
		//���[�U�[ID���i�[���ꂽ�u���b�N���w�肵�ă��[�U�[ID���擾����
		uid = GetData(data, UID_INDEX);
		//�擾�������[�U�[���Ńt�@�C�����J��
		std::ifstream ifs(uid);
		//���[�U�[ID���t�@�C�����Ƃ����t�@�C�����J���Ȃ��Ƃ��̓��[�U�[�����݂��Ă��Ȃ��Ƃ��ė�O�𓊂���
		if (!ifs) {
			//�Ώۂ̃��[�U�[�����݂��Ă��Ȃ��|���O�Ƃ��ē�����
			throw gcnew System::Exception(Constants->ID_NOT_FOUND_ERROR);
		}//����ȊO�̎��̓p�X���[�h�̔���Ɉڂ�
		else {
			//�p�X���[�h�̔���Ɉڂ�
			CheckPass(data, pass);
		}
		//���肪�I������烆�[�U�[ID��ԋp����
		return uid;
	}

	/*�T�v:�Ώۂ̃��[�U�[�̃p�X���[�h���m�F���A���������𔻒肷�邽�߂̊֐�
	����:string name:���[�U�[�̖��O
	    :string pass:���[�U�[�����͂����p�X���[�h
		:ifstream file:���[�U�̏�񂪊i�[���ꂽ�t�@�C���ւ̃X�g���[��
	�߂�l:bool:�ƍ����ʂ̐���
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	bool CheckPass(std::vector<std::vector<unsigned char>> data, std::string pass) {
		std::string getpass = "";        //�t�@�C�����擾�����p�X���i�[���邽�߂̕�����
		//��M�����J�[�h�f�[�^�������擾����֐����Ăяo��
		getpass = GetData(data, PASS_INDEX);
		//�p�X����������O�𓊂���
		if (getpass != pass) {
			//�p�X���Ⴄ�|�̗�O�𓊂���
			throw gcnew System::Exception(Constants->PASS_NOT_FOUND_ERROR);
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
	std::string GetData(std::vector<std::vector<unsigned char>> data, int index) {
		std::string datastring = "";    //�擾������������i�[���邽�߂̕�����
		//�Ώۂ̕�������擾����
		datastring = (data[index], data[index].size());
		//�擾�����������ԋp����
		return datastring;
	}
	
	/*�T�v:�J�[�h�֑��M����f�[�^�̑g�ݗ��āA�R�}���h�̍쐬���s���֐�
	����:string setdata:���M����f�[�^
	�߂�l:unsigned char:�f�[�^�𑗐M���邽�߂̃R�}���h
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> ReadySetData(std::string uid, int blockindex) {
		std::vector<SENDCOMM> sendcomm;        //�g�ݗ��Ă��R�}���h���i�[���邽�߂̍\����
		char setdata;                          //�R�}���h�̒��ɑg�ݍ��ޑ��M������
		SENDCOMM certify = AUTHENTICATE;       //�u���b�N�F�؃R�}���h�̃R�s�[
		SENDCOMM sendcard = SENDCARD;          //�f�[�^���M�R�}���h�̃R�s�[
		//�R�}���h������������
		sendcomm = InitCommand(blockindex);
		//�J�[�h�֑��M����f�[�^���i�[���ꂽ�t�@�C�����J��
		std::ifstream ifs(uid);
		//�R�}���h��g�ݗ��ĂĂ���
		for (; blockindex < END_BLOCK; blockindex++) {
			//�Ώۂ̃u���b�N��4�̔{���]1�̎��͓ǂݔ�΂�
			if (blockindex % 4 != 3) {
				//16�o�C�g���̑��M�R�}���h��g�ݗ��ĂĂ���
				for (int i = 0; i < 16; i++) {
					//�t�@�C������1�o�C�g���f�[�^���擾����
					ifs.get(setdata);
					//�t�@�C���������ɓ��B���Ă��Ȃ���΃R�}���h�ɑ��M�f�[�^���i�[���Ă���
					if (!ifs.eof()) {
						//���M�f�[�^�Ƃ��ăR�}���h�Ɋi�[����
						sendcard.sendCommand[5 + i] = setdata;
					}//�����̎��͋�f�[�^���i�[���Ă���
					else {
						//��f�[�^������0���i�[���Ă���
						sendcard.sendCommand[5 + i] = 0;
					}
				}
				//�f�[�^�𑗐M����Ώۂ̃u���b�N��ݒ肷��
				sendcard.sendCommand[3] = blockindex;
				//�g�ݗ��Ă��R�}���h���i�[����
				sendcomm.push_back(sendcard);
			}//�Ώۂ̃u���b�N���Z�N�^�[�̖����̎��͓ǂݔ�΂�
			else {
				//�ǂݔ�΂��Ɠ����Ɏ��̃Z�N�^�[�ւ̔F�؂��s��
				certify.sendCommand[7] = blockindex + 1;
				//���M�R�}���h�Ɋi�[����
				sendcomm.push_back(certify);
			}
		}
		//�R�}���h�̏I���������R�}���h���i�[����
		sendcomm.push_back({ -1, NULL });
		//�g�ݗ��Ă��R�}���h��ԋp����
		return sendcomm;
	}

	/*�T�v:�J�[�h�փf�[�^�𑗐M���邽�߂̊֐�
	����:SCARDCONTEXT hContext:�擾�������\�[�X�}�l�[�W��
	    :SCARDHANDLE hCard:�擾�����J�[�h
		:string uid:�擾�����J�[�h�̃��[�U�[ID
	�߂�l:�Ȃ�
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	void SetCardData(std::string uid) {
		ConnectCard* con = new ConnectCard();    //�J�[�h�ʐM�N���X���C���X�^���X��
		std::vector<SENDCOMM> senddata;    //���M�R�}���h���i�[���邽�߂̍\����
		//���M�R�}���h���쐬����֐����Ăяo��
		senddata = ReadySetData(uid, BEGIN_BLOCK);
		//���M�R�}���h�̏I���ɃR�}���h�̏I���������R�}���h���i�[����
		senddata.push_back(ENDCOMMAND);
		//�J�[�h�փR�}���h�𑗐M����֐����Ăяo��
		con->LinkCard(senddata);
		return;
	}

	/*�T�v:�J�[�h����f�[�^����M���邽�߂̊֐�
	����:SCARDCONTEXT hContext:�擾�������\�[�X�}�l�[�W��
	    :SCARDHANDLE hCard:�擾�����J�[�h
	�߂�l:string uid:�J�[�h���擾�������[�U�[ID
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	std::string GetCardData(std::string pass) {
		std::vector<SENDCOMM>sendcomm;        //��M�R�}���h���i�[���邽�߂̔z��
		std::vector<SENDCOMM>copycomm;
		std::vector<std::vector<unsigned char>> recvdata;    //��M�f�[�^���i�[���邽�߂̔z��
		std::string uid;
		ConnectCard* con = new ConnectCard();                //�J�[�h�Ƃ̒ʐM���s���N���X���C���X�^���X��
		//��M�R�}���h��g�ݗ��Ă�֐����Ăяo��
		sendcomm = ReadyGetData(BEGIN_BLOCK);
		//��M�R�}���h���J�[�h�֑��M���ăf�[�^���󂯎��
		recvdata = con->LinkCard(sendcomm);
		//���[�U�[�����m�F����֐����Ăяo��
		uid = CheckUser(recvdata, pass);
		//���َ��Ԃ��擾����֐����Ăяo��
		SetAdmissionTimes(uid);
		//���َ��Ԃ��J�[�h�ɋL�^������
		sendcomm.insert(sendcomm.begin(), copycomm.begin(), copycomm.end());
		//�J�[�h�փf�[�^�𑗐M����
		recvdata = con->LinkCard(sendcomm);
		return uid;
	}

	/*�T�v:�f�[�^��M�R�}���h���쐬���邽�߂̊֐�
	�쐬��:2017.10.12
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> ReadyGetData(int blockindex) {
		SENDCOMM authenticate = AUTHENTICATE;    //�F�؃L�[�R�}���h�̃R�s�[�����
		SENDCOMM readcard = READCARD;             //��M�R�}���h�̃R�s�[�����
		std::vector<SENDCOMM> sendcomm;                         //�g�ݗ��Ă��R�}���h���i�[���邽�߂̔z��
		//�R�}���h�̏������������s��
		sendcomm = InitCommand(blockindex);
		//��M�R�}���h��g�ݗ��ĂĂ���
		for (; blockindex < END_BLOCK; blockindex++) {
			//�Ǎ��悪�Z�N�^�[�̏I�[�u���b�N�̏ꍇ�͓ǂݔ�΂�
			if (blockindex % 4 != 3) {
				//�Ǎ���u���b�N��ݒ肷��
				readcard.sendCommand[3] = blockindex;
				//�R�}���h��g�ݗ��Ă�
				sendcomm.push_back(readcard);
			}//�ǂݔ�΂��Ɠ����Ɏ��̃Z�N�^�[�ɓ��邽�߂̏���������
			else {
				//�Z�N�^�[�F�؃R�}���h�̔F�ؐ��ݒ肷��
				authenticate.sendCommand[7] = blockindex + 1;
				//�R�}���h��g�ݗ��Ă�
				sendcomm.push_back(authenticate);
			}
		}
		//�Ō�ɃR�}���h�̏I���������R�}���h���i�[����
		sendcomm.push_back({ -1, NULL });
		//�g�ݗ��Ă��R�}���h��Ԃ�
		return sendcomm;
	}

	/*�T�v:���ފٓ��̎擾�y�єN���̊m�F���s���֐�
	����:string uid:�`�F�b�N�Ώۂ̃��[�U��ID
	�߂�l:�Ȃ�
	�쐬���F2017.10.11
	�쐬��:K.Asada*/
	void SetAdmissionTimes(std::string uid) {
		ITOC times;            //�擾�����������𕪂ɕϊ��������̂��i�[����
		//�N�����`�F�b�N����֐����Ăяo���A�N�������ݔN���ƈقȂ��Ă����珑��������
		CheckYears(uid);
		//�֐���茻�ݓ��������擾����
		times.num = GetAdmissionTime();
		//�f�[�^���������ޑΏۂ̃t�@�C�����J��
		std::ofstream ofs(uid, std::ios::app);
		//�擾�����������̏��8�r�b�g���t�@�C���ɏ����o��
		ofs << times.bytes[1];
		//�擾�����������̉���8�r�b�g���t�@�C���ɏ����o��
		ofs << times.bytes[0];
		//�����o�����I���������
		ofs.close();
		return;
	}

	/*�T�v:���ݓ������𕪂ɕϊ����Ď擾����֐�
	����:�Ȃ�
	�߂�l:unsigned short int times:��
	�쐬���F2017.10.11
	�쐬��:K.Asada*/
	int GetAdmissionTime() {
		time_t now = time(NULL);          //���ݎ������擾���邽��
		struct tm *pnow = localtime(&now);//���ݎ������擾���邽�߂̍\���̂�錾
		unsigned short int times;                       //�擾�������ݎ������i�[���邽�߂̕ϐ�
		//���ݓ������𕪂Ɋ��Z���Ċi�[����
		times = ((pnow->tm_mday * 24 + pnow->tm_hour) * 60 + pnow->tm_min);
		//�擾�������Ԃ�ԋp����
		return times;
	}

	/*�T�v:���[�U���Ɋ܂܂��N�����Â��Ȃ������m�F����֐�
	����:string uid:�`�F�b�N�Ώۂ̃��[�U��ID
	�߂�l:�Ȃ�
	�쐬��:2017.10.11
	�쐬��:K.Asada*/
	void CheckYears(std::string uid) {
		time_t now = time(NULL);          //���ݎ������擾���邽��
		struct tm *pnow = localtime(&now);//���ݎ������擾���邽�߂̍\���̂�錾
		ITOC years;                       //�擾�������ݎ������i�[���邽�߂̕ϐ�
		char filedata[16*BLOCK_COUNT];  //�t�@�C������擾�����f�[�^���i�[����ϐ�
		//���ݔN�����擾����
		years.num = ((pnow->tm_year + 1900) * 12 + pnow->tm_mon + 1);
		//�t�@�C������N�����擾���邽�߂̃X�g���[�����J��
		std::fstream fs(uid);
		//�t�@�C������f�[�^���擾����
		fs.getline(filedata, 16*BLOCK_COUNT);
		//�f�[�^����N���������o���A�擾�����N���Ɣ�r����
		if (years.bytes[1] != filedata[16 * YEAR_INDEX] && years.bytes[0] != filedata[16 * YEAR_INDEX + 1]) {
			//�t�@�C������擾�����N�����㏑������
			filedata[16 * YEAR_INDEX] = years.bytes[1];
			//�N�����㏑������
			filedata[16 * YEAR_INDEX + 1] = years.bytes[0];
			//�㏑�������f�[�^���t�@�C���ɏ����o��
			fs << filedata;
		}
		//�J�����t�@�C���X�g���[�������
		fs.close();
		return;
	}

	/*�T�v:�N�����Ȃǂ�bit�f�[�^�𑗐M���邽�߂̃R�}���h�����֐�
	�쐬��:2017.10.12
	�쐬��:K.Asada*/
	/*
	std::vector<SENDCOMM> ReadySetTimes(std::string uid) {
		std::vector<CONSTANTGROUP::SENDCOMM> sendtime;
		CONSTANTGROUP::SENDCOMM authenticate = CONSTANTGROUP::AUTHENTICATE;
		CONSTANTGROUP::SENDCOMM sendcard = CONSTANTGROUP::SENDCARD;
		std::string gettime;
		std::string settime;
		int index = -8;
		sendtime.push_back(CONSTANTGROUP::LOADKEY);
		authenticate.sendCommand[7] = CONSTANTGROUP::BIT_BLOCK;
		sendtime.push_back(authenticate);
		std::ifstream ifs(uid);
		getline(ifs, gettime);
		getline(ifs, gettime);
		for (int i = CONSTANTGROUP::BEGIN_BLOCK; i < CONSTANTGROUP::BLOCK_COUNT; i++) {
			if (i % 4 != 3) {
				for (int j = 0; j < 16; j++) {
					settime = gettime.substr(index += 8, 8);
					if (settime != "        ") {
						sendcard.sendCommand[5 + j] = std::stoi(settime, nullptr, 2);
					}
					else {
						sendcard.sendCommand[5 + j] = 0;
					}
					sendcard.sendCommand[3] = i;
					sendtime.push_back(sendcard);
				}
			}
			else {
				authenticate.sendCommand[7] = i + 1;
				sendtime.push_back(authenticate);
			}
		}
		return sendtime;
	}*/

	/*�T�v:�R�}���h�̏����������֐�
	����:int beginblock:�R�}���h�𑗐M���ď��߂ɃA�N�Z�X����u���b�N
	�߂�l:std::vector<SENDCOMM> initcommand:�쐬�����R�}���h
	�쐬��:2017.10.13
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> InitCommand(int beginblock) {
		std::vector<SENDCOMM> initcommand;    //�쐬�����R�}���h���i�[���邽�߂̔z��
		SENDCOMM certify = AUTHENTICATE;                                    //�u���b�N�F�؃R�}���h
		//�u���b�N�F�؃R�}���h�̔F�ؐ�u���b�N������������
		certify.sendCommand[7] = beginblock;
		//�R�}���h��g�ݗ��ĂĂ���
		initcommand.push_back(LOADKEY);
		//�F�؃R�}���h��g�ݗ��ĂĂ���
		initcommand.push_back(certify);
		//�g�ݗ��Ă��R�}���h��ԋp����
		return initcommand;
	}
};
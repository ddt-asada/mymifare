#pragma once

#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <bitset>
#include <stdio.h>
#include "ConnectCard.h"
#include "CONSTANTS.h"

public class AdmissionSystem {
public:
	AdmissionSystem() {

	}
	/*�T�v:�Ώۂ̃��[�U�[�̃f�[�^�����݂��Ă��邩���m�F���邽�߂̊֐�
	����:unsigned data:�J�[�h���擾�����S�f�[�^
	�߂�l:string uid:�J�[�h���擾�������[�U�[ID
	�쐬���F2017.10.10
	�쐬��:K.Asada*/
	std::string CheckUser(std::vector<std::vector<unsigned char>> data, std::string pass) {
		std::string uid = "";        //�J�[�h���擾�������[�U�[ID���i�[���邽�߂̕�����
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
		return uid;
	}

	/*�T�v:�Ώۂ̃��[�U�[�̃p�X���[�h���m�F���A���������𔻒肷�邽�߂̊֐�
	����:string name:���[�U�[�̖��O
	    :string pass:���[�U�[�����͂����p�X���[�h
		:ifstream file:���[�U�̏�񂪊i�[���ꂽ�t�@�C���ւ̃X�g���[��
	�߂�l:bool:�ƍ����ʂ̐���
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	bool CheckPass(std::string name, std::string pass) {
		/*std::string getname = "";        //�t�@�C�����擾�������O���i�[���邽�߂̕�����
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
		return true;*/
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
	CONSTANTGROUP::SENDCOMM ReadySetData(std::string uid, CONSTANTGROUP::SENDCOMM senddataa[]) {
		CONSTANTGROUP::SENDCOMM senddata[22];
		senddata[0] = CONSTANTGROUP::LOADKEY;
		senddata[1] = CONSTANTGROUP::AUTHENTICATE;
		CONSTANTGROUP::SENDCOMM copyauthenticate = CONSTANTGROUP::AUTHENTICATE;    //�F�؃R�}���h�̃R�s�[
		CONSTANTGROUP::SENDCOMM copysendcard = CONSTANTGROUP::SENDCARD;            //�f�[�^���M�R�}���h�̃R�s�[
		char setdata;             //�t�@�C�����擾������������i�[����
		int blockindex;           //�������ݑΏۂ̃u���b�N
		std::string bitstr;
		std::string setstr = "aaa";       //�R�}���h�փZ�b�g���镶����
		std::ifstream ifs(uid);   //�J�[�h�֑��M����f�[�^���i�[���ꂽ�e�L�X�g���J��
		//�S�f�[�^�𑗐M���邽�߂̑��M�R�}���h��g�ݗ��ĂĂ���
		for (int i = 0; i < CONSTANTGROUP::BLOCK_COUNT; i++) {
			//�������ݑΏۂ̃u���b�N�����擾����
			blockindex = i + CONSTANTGROUP::BEGIN_BLOCK;
			//4�̔{��-1�̓Z�N�^�[�̏I�[�u���b�N�ŃL�[���i�[����Ă��邽�ߕҏW�������Ȃ��̂œǂݔ�΂����߂̕���
			if (blockindex % 4 != 3) {
				//���M�R�}���h�̑��M��u���b�N������������
				copysendcard.sendCommand[3] = i + CONSTANTGROUP::BEGIN_BLOCK;
				//�������݃u���b�N�̌㔼�����͔N�����Ȃ̂ŕʏ������邽�߂̕���
				if (blockindex >= 20) {
					ifs >> bitstr;
					//���M�R�}���h��g�ݗ��Ă邽�߂̃��[�v
					for (int j = 0; j < 16; j++) {
						//�t�@�C���Ƀf�[�^�����݂��Ă���Ε���
						if ((j + 1) * 8 <= bitstr.size() && !ifs.eof()) {
							//�e�L�X�g����󔒕����܂Ŏ擾����
							setstr = bitstr.substr(j * 8, 8);
							//���M�R�}���h�Ƃ���2�i���̐����Ƃ��Ď擾���Achar��8�i�[����
							copysendcard.sendCommand[5 + j] = std::stoi(setstr, nullptr, 2);
						}//�f�[�^���Ȃ��Ƃ��͋󕶎��Ƃ���0�𑗐M�R�}���h�ɃZ�b�g����
						else {
							copysendcard.sendCommand[5 + j] = 0;
						}
					}
					//�g�ݗ��Ă����M�R�}���h���i�[����
					senddata[2 + i] = copysendcard;
				}
				//16�o�C�g���̑��M�R�}���h��g�ݗ��ĂĂ���
				for (int j = 0; j < 16; j++) {
					ifs.get(setdata);//�t�@�C������1�o�C�g���f�[�^�����o��
					//���s�����ɂ��ǂ蒅���܂��̓t�@�C���I�[�ŕ���
					if (!ifs.eof()) {
						if (setdata == '\n') {
							ifs.get(setdata);
						}
						//���M�R�}���h�����������Ă���
						copysendcard.sendCommand[5 + j] = setdata;
					}//�i�[���镶���񂪂Ȃ��Ƃ��͑��M�R�}���h�ɋ������'0'���i�[����
					else {
						copysendcard.sendCommand[5 + j] = 0;
					}
				}
				ifs.get(setdata);//�t�@�C������1�o�C�g���f�[�^�����o��
				//�g�ݗ��Ă����M�R�}���h���i�[����
				senddata[2 + i] = copysendcard;
			}
			else {//�ǂݔ�΂����߂̏���
				//�F�؃R�}���h�̔F�ؐ�u���b�N������������
				copyauthenticate.sendCommand[7] = (i + 1 + CONSTANTGROUP::BEGIN_BLOCK);
				//���̃Z�N�^�[�ւ̔F�؂��s���R�}���h���Z�b�g����
				senddata[2 + i] = copyauthenticate;
			}
		}
		//���M�R�}���h�̏I���ɃR�}���h�̏I�����Ӗ�����R�}���h���i�[����
		senddata[2 + CONSTANTGROUP::BLOCK_COUNT] = { -1, NULL };
		//�g�ݗ��Ă����M�R�}���h��ԋp����
		return *senddata;
	}

	/*�T�v:�J�[�h�փf�[�^�𑗐M���邽�߂̊֐�
	����:SCARDCONTEXT hContext:�擾�������\�[�X�}�l�[�W��
	    :SCARDHANDLE hCard:�擾�����J�[�h
		:string uid:�擾�����J�[�h�̃��[�U�[ID
	�߂�l:�Ȃ�
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	void SetCardData(SCARDCONTEXT hContext, SCARDHANDLE hCard, std::string uid) {
		ConnectCard* con = new ConnectCard();    //�J�[�h�ʐM�N���X���C���X�^���X��
		CONSTANTGROUP::SENDCOMM senddata[22];    //���M�R�}���h���i�[���邽�߂̍\����
		//���M�R�}���h���쐬����֐����Ăяo��
		ReadySetData(uid, senddata);
		//�J�[�h�փR�}���h�𑗐M����֐����Ăяo��
		con->Transmit(senddata);
		//�ڑ����I������֐����Ăяo��
		con->EndConnect(hContext, hCard);
		return;
	}

	/*�T�v:�J�[�h����f�[�^����M���邽�߂̊֐�
	����:SCARDCONTEXT hContext:�擾�������\�[�X�}�l�[�W��
	    :SCARDHANDLE hCard:�擾�����J�[�h
	�߂�l:string uid:�J�[�h���擾�������[�U�[ID
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	std::string GetCardData(std::string pass) {
		std::vector<CONSTANTGROUP::SENDCOMM>sendcomm;        //��M�R�}���h���i�[���邽�߂̔z��
		std::vector<std::vector<unsigned char>> recvdata = { {'\0'} };    //��M�f�[�^���i�[���邽�߂̔z��
		std::string uid;
		ConnectCard* con = new ConnectCard();                //�J�[�h�Ƃ̒ʐM���s���N���X���C���X�^���X��
		//��M�R�}���h��g�ݗ��Ă�֐����Ăяo��
		sendcomm = ReadyGetData();
		//��M�R�}���h���J�[�h�֑��M���ăf�[�^���󂯎��
		recvdata = con->Transmit(sendcomm);
		//���[�U�[�����m�F����֐����Ăяo��
		CheckUser(recvdata, pass);
		//���َ��Ԃ��擾����֐����Ăяo��
		SetAdmissionTimes(uid);
		//���َ��Ԃ��J�[�h�ɋL�^������
		sendcomm = ReadySetTimes(uid);
		//�J�[�h�փf�[�^�𑗐M����
		con->Transmit(sendcomm);
		return;
	}

	/*�T�v:�f�[�^��M�R�}���h���쐬���邽�߂̊֐�
	�쐬��:2017.10.12
	�쐬��:K.Asada*/
	std::vector<CONSTANTGROUP::SENDCOMM> ReadyGetData() {
		CONSTANTGROUP::SENDCOMM authenticate = CONSTANTGROUP::AUTHENTICATE;    //�F�؃L�[�R�}���h�̃R�s�[�����
		CONSTANTGROUP::SENDCOMM readcard = CONSTANTGROUP::READCARD;             //��M�R�}���h�̃R�s�[�����
		std::vector<CONSTANTGROUP::SENDCOMM> sendcomm;                         //�g�ݗ��Ă��R�}���h���i�[���邽�߂̔z��
		int blockindex = 0;                                                    //�F�ؐ�u���b�N���i�[����ϐ�
		//��M�R�}���h�̏����l�Ƃ��ăL�[�F�؃R�}���h���Z�b�g����
		sendcomm.push_back(CONSTANTGROUP::LOADKEY);
		//��M�R�}���h�̏����l�Ƃ��ău���b�N�F�؃R�}���h���Z�b�g����
		sendcomm.push_back(CONSTANTGROUP::AUTHENTICATE);
		//��M�R�}���h��g�ݗ��ĂĂ���
		for (int i = CONSTANTGROUP::BEGIN_BLOCK; i < CONSTANTGROUP::BLOCK_COUNT; i++) {
			//�Ǎ���̃u���b�N���擾����
			blockindex = i;
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
		int times;            //�擾�����������𕪂ɕϊ��������̂��i�[����
		//�N�����`�F�b�N����֐����Ăяo���A�N�������ݔN���ƈقȂ��Ă����珑��������
		CheckYears(uid);
		std::ofstream ofs(uid, std::ios::app);    //�f�[�^���������ޑΏۂ̃t�@�C�����J��
		//�֐���茻�ݓ��������擾����
		times = GetAdmissionTime();
		//�擾�������������t�@�C���֏����o��
		ofs << std::bitset<16>(times);
		//�����o�����I���������
		ofs.close();
		return;
	}

	/*�T�v:���ݓ������𕪂ɕϊ����Ď擾����֐�
	����:�Ȃ�
	�߂�l:char times:��
	�쐬���F2017.10.11
	�쐬��:K.Asada*/
	int GetAdmissionTime() {
		time_t now = time(NULL);          //���ݎ������擾���邽��
		struct tm *pnow = localtime(&now);//���ݎ������擾���邽�߂̍\���̂�錾
		int times;                       //�擾�������ݎ������i�[���邽�߂̕ϐ�
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
		int years;                       //�擾�������ݎ������i�[���邽�߂̕ϐ�
		std::vector<std::string> admyear;                     //�t�@�C������擾�����N�����i�[���邽�߂̕ϐ�
		std::string tmp;
		//���ݔN�����擾����
		years = ((pnow->tm_year + 1900) * 12 + pnow->tm_mon + 1);
		//�t�@�C������N�����擾���邽�߂̃X�g���[�����J��
		std::ifstream ifs(uid);
		//�t�@�C�������s���ƂɃf�[�^�����ׂĎ擾����
		for (int i = 0; !ifs.eof(); i++) {
			//1�s���擾����
			std::getline(ifs, tmp);
			admyear.push_back(tmp);
		}
		//�擾�����f�[�^�̔N�������݂̔N���ƈقȂ��Ă���Ώ㏑������
		if (admyear[5] != std::to_string(years)) {
			std::string bit(std::bitset<32>(years).to_string<char, std::char_traits<char>, std::allocator<char> >());
			//�Ώۂ��㏑������
			admyear[5] = bit;
			//�t�@�C�����X�V���邽�߂ɊJ��
			std::ofstream ofs(uid);
			std::string tmp;
			//��s����������ł���
			for (int i = 0; i < admyear.size(); i++) {
				tmp = admyear[i];
				if (i + 1 == admyear.size()) {
					ofs << tmp;
				}
				else {
					//��s����������
					ofs << tmp + '\n';
				}
			}
		}
		return;
	}

	/*�T�v:�N�����Ȃǂ�bit�f�[�^�𑗐M���邽�߂̃R�}���h�����֐�
	�쐬��:2017.10.12
	�쐬��:K.Asada*/
	std::vector<CONSTANTGROUP::SENDCOMM> ReadySetTimes(std::string uid) {
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
	}
};
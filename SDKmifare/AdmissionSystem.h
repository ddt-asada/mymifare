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

	/*�T�v:�J�[�h�֐V�K�Ńf�[�^�𑗐M���邽�߂̊֐�
	����:SCARDCONTEXT hContext:�擾�������\�[�X�}�l�[�W��
	:SCARDHANDLE hCard:�擾�����J�[�h
	:string uid:�擾�����J�[�h�̃��[�U�[ID
	�߂�l:�Ȃ�
	�쐬��:2017.10.10
	�쐬��:K.Asada
	�X�V���e:�V�d�l�����ɔ����֐����A������ύX
	�X�V��:2017.10.24
	�X�V��:K.Asada*/
	void SetCardData(std::string uid, SCARDCONTEXT hContext, SCARDHANDLE hCard, DWORD ActiveProtocol) {
		try {
			ConnectCard* con = new ConnectCard();    //�J�[�h�ʐM�N���X���C���X�^���X��
			std::vector<SENDCOMM> senddata;    //���M�R�}���h���i�[���邽�߂̍\����
			//�f�[�^���M�p�̃R�}���h��g�ݗ��Ă�
			senddata = ReadySetData(uid, BEGIN_BLOCK);
			//�J�[�h�փR�}���h�𑗐M����֐����Ăяo��
			con->Transmit(hContext, hCard, ActiveProtocol, senddata);
			return;
		}
		catch (System::IndexOutOfRangeException^ e) {
			System::Console::WriteLine(e);
		}
	}

	/*�T�v:�J�[�h����f�[�^����M���邽�߂̊֐�
	����:SCARDCONTEXT hContext:�擾�������\�[�X�}�l�[�W��
	:SCARDHANDLE hCard:�擾�����J�[�h
	�߂�l:string uid:�J�[�h���擾�������[�U�[ID
	�쐬��:2017.10.10
	�쐬��:K.Asada
	�X�V���e:�V�d�l�����ɔ���������ύX
	�X�V��:2017.10.24
	�X�V��:K.Asada*/
	std::vector<std::vector<unsigned char>> GetCardData(SCARDCONTEXT hContext, SCARDHANDLE hCard, DWORD ActiveProtocol) {
		try {
			std::vector<SENDCOMM>sendcomm;        //��M�R�}���h���i�[���邽�߂̔z��
			std::vector<SENDCOMM>copycomm;        //���M�R�}���h���i�[���邽�߂̔z��
			std::vector<std::vector<unsigned char>> recvdata;    //��M�f�[�^���i�[���邽�߂̔z��
			std::string uid;                                     //���[�U�[ID���i�[���邽�߂̔z��
			ConnectCard* con = new ConnectCard();                //�J�[�h�Ƃ̒ʐM���s���N���X���C���X�^���X��
																 //��M�R�}���h��g�ݗ��Ă�֐����Ăяo��
			sendcomm = ReadyGetData(BEGIN_BLOCK);
			//��M�R�}���h���J�[�h�֑��M���ăf�[�^���󂯎��
			recvdata = con->Transmit(hContext, hCard, ActiveProtocol, sendcomm);
			return recvdata;
		}
		catch (System::Exception^ e) {
			System::Console::WriteLine(e);
			throw e;
		}
	}

	/*�T�v:�J�[�h�f�[�^�̓��ފٓ����X�V���邽�߂̊֐�
	����:std::vector<std::vector<unsignde char>> data:�J�[�h�̃f�[�^
	    :SCARDCONTEXT hContext:�m�ۂ������\�[�X�}�l�[�W���̃A�h���X
		:SCARDHANDLE hCard:�J�[�h�̃A�h���X
		:DWORD ActiveProtocol:�v���g�R��
		:int beginblock:�X�V�Ώۂ��擾���邽�߂̎n�_�ƂȂ�C���f�b�N�X
		:int endblock:�X�V�Ώۂ��擾���邽�߂̏I�_�ƂȂ�C���f�b�N�X
	�߂�l:�Ȃ�
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	void UpdateCardData(std::vector <std::vector<unsigned char>> data, SCARDCONTEXT hContext, SCARDHANDLE hCard, DWORD ActiveProtocol, int beginindex, int endindex) {
		ConnectCard* con = new ConnectCard();    //�J�[�h�ʐM�N���X���C���X�^���X������
		std::vector<SENDCOMM> sendcomm;    //�J�[�h�ւ̑��M�R�}���h
		int *updateblock = 0;              //�X�V�Ώۂ̃u���b�N
		int *updateindex = 0;              //�X�V�Ώۂ̃C���f�b�N�X
		//�X�V�Ώۂ̃u���b�N�A�C���f�b�N�X���擾����
		GetLastBlock(data, beginindex, endindex);
		//�X�V�R�}���h��g�ݗ��ĂĂ���
		sendcomm = ReadyUpdateData(data, *updateblock, *updateindex);
		//�J�[�h�փR�}���h�𑗐M����
		con->Transmit(hContext, hCard, ActiveProtocol, sendcomm);
		return;
	}

	/*�T�v:�J�[�h�֑��M����f�[�^�̑g�ݗ��āA�R�}���h�̍쐬���s���֐�
	����:string setdata:���M����f�[�^
	�߂�l:unsigned char:�f�[�^�𑗐M���邽�߂̃R�}���h
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> ReadySetData(std::string uid, int blockindex) {
		try {
			std::vector<SENDCOMM> sendcomm;        //�g�ݗ��Ă��R�}���h���i�[���邽�߂̍\����
			char setdata;                          //�R�}���h�̒��ɑg�ݍ��ޑ��M������
			SENDCOMM certify = AUTHENTICATE;       //�u���b�N�F�؃R�}���h�̃R�s�[
			SENDCOMM sendcard = SENDCARD;          //�f�[�^���M�R�}���h�̃R�s�[
												   //�R�}���h������������
			sendcomm = InitCommand(blockindex);
			//�J�[�h�֑��M����f�[�^���i�[���ꂽ�t�@�C�����J��
			std::ifstream ifs(uid + ".txt");
			//�R�}���h��g�ݗ��ĂĂ���
			for (; blockindex < END_BLOCK; blockindex++) {
				//�Ώۂ̃u���b�N��4�̔{���]1�̎��͓ǂݔ�΂�
				if (blockindex % 4 != 3) {
					if (!ifs.eof()) {
						//�t�@�C������1�o�C�g���f�[�^���擾����
						ifs.get(setdata);
					}
					//16�o�C�g���̑��M�R�}���h��g�ݗ��ĂĂ���
					for (int i = 0; i < 16; i++) {
						//�t�@�C���������ɓ��B���Ă��Ȃ���΃R�}���h�ɑ��M�f�[�^���i�[���Ă���
						if (setdata != '\n' && !ifs.eof()) {
							//���M�f�[�^�Ƃ��ăR�}���h�Ɋi�[����
							sendcard.sendCommand[5 + i] = setdata;
							//�t�@�C������1�o�C�g���f�[�^���擾����
							ifs.get(setdata);
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
		catch (System::IndexOutOfRangeException^ e) {
			System::Console::WriteLine(e);
		}
	}

	/*�T�v:�f�[�^��M�R�}���h���쐬���邽�߂̊֐�
	�쐬��:2017.10.12
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> ReadyGetData(int blockindex) {
		try {
			SENDCOMM authenticate = AUTHENTICATE;     //�F�؃L�[�R�}���h�̃R�s�[�����
			SENDCOMM readcard = READCARD;             //��M�R�}���h�̃R�s�[�����
			std::vector<SENDCOMM> sendcomm;           //�g�ݗ��Ă��R�}���h���i�[���邽�߂̔z��
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
		catch (System::IndexOutOfRangeException^ e) {
			System::Console::WriteLine(e);
		}
	}

	/*�T�v:�ΏۂƂȂ���������X�V���邽�߂̃R�}���h��g�ݗ��Ă�֐�
	����:std::vector<std::vector<unsigned char>> data:�J�[�h�f�[�^
	    :int updateblock:�X�V�Ώۂ̃u���b�N
		:int updateindex:�X�V�Ώۂ�C���f�b�N�X
	�߂�l:std::vector<SENDCOMM> sendcomm:�J�[�h�f�[�^�X�V�p�̃R�}���h
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> ReadyUpdateData(std::vector<std::vector<unsigned char>> data, int updateblock, int updateindex) {
		ITOC currenttime;    //�J�[�h�ɑ��M���錻�ݓ�����ϊ����邽�߂̋��L��
		std::vector<SENDCOMM> senddata;    //�X�V�p�̃R�}���h
		SENDCOMM copycomm = SENDCARD;      //�f�[�^���M�R�}���h�̃e���v���[�g
		//�R�}���h�̏����l���擾����
		senddata = InitCommand(updateblock);
		//���ݓ��������擾����
		currenttime.num = GetNowTime();
		//���M�R�}���h�̑Ώۂ̃u���b�N��ݒ肷��
		copycomm.sendCommand[3] = updateblock;
		//1�u���b�N���̑��M�R�}���h��g�ݗ��ĂĂ���
		for (int i = 0; i < 16; i++) {
			//�X�V�ΏۂƂȂ�ꏊ�ɂ��ǂ蒅������
			if (i == updateindex) {
				//�X�V�Ώۂ����ݓ������ɏ���������
				copycomm.sendCommand[i++] = currenttime.bytes[0];
				//�X�V�Ώۂ����ݓ������ɏ���������
				copycomm.sendCommand[i] = currenttime.bytes[1];
			}//����ȊO�̎��͂��̂܂܂ɂ���
			else {
				//�X�V�Ώۂ̏ꏊ�ȊO�̓J�[�h�f�[�^���X�V���Ȃ�
				copycomm.sendCommand[i++] = data[updateblock][i];
				//�X�V���Ȃ�
				copycomm.sendCommand[i] = data[updateblock][i];
			}
		}
		//�g�ݗ��Ă����M�R�}���h��ԋp�p�̃R�}���h�ɘA������
		senddata.push_back(copycomm);
		//�R�}���h�̏I���������R�}���h��A������
		senddata.push_back(ENDCOMMAND);
		//�g�ݗ��Ă��R�}���h��ԋp����
		return senddata;
	}

	/*�T�v:���ݓ������𕪂ɕϊ����Ď擾����֐�
	����:�Ȃ�
	�߂�l:unsigned short int times:��
	�쐬���F2017.10.11
	�쐬��:K.Asada*/
	int GetNowTime() {
		time_t now = time(NULL);          //���ݎ������擾���邽��
		struct tm *pnow = localtime(&now);//���ݎ������擾���邽�߂̍\���̂�錾
		unsigned short int times;                       //�擾�������ݎ������i�[���邽�߂̕ϐ�
														//���ݓ������𕪂Ɋ��Z���Ċi�[����
		times = ((pnow->tm_mday * 24 + pnow->tm_hour) * 60 + pnow->tm_min);
		//�擾�������Ԃ�ԋp����
		return times;
	}

	/*�T�v�F�J�[�h���擾����unsigned char��蕶������擾���邽�߂̊֐�
	����:unsigned char data:�J�[�h���擾�����ϐ�
	:int index:�擾�Ώۂ̕����񂪑��݂���u���b�N
	:int endbyte:�f�[�^���擾���镶����̃o�C�g��
	:int beginbyte:�擾����Ƃ��̎n�_(1�u���b�N�ɕ����̃f�[�^���܂܂�Ă���ꍇ�Ɏw��)
	�߂�l:string datastring:�擾����������
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	std::string GetData(std::vector<std::vector<unsigned char>> data, int index, int beginbyte = 0, int endbyte = 16) {
		try {
			std::string datastring = "";    //�擾������������i�[���邽�߂̕�����
			for (int i = beginbyte; i < endbyte; i++) {
				//NULL��ǂݔ�΂����߂̏���
				if (data[index][i] != '\0') {
					//�Ώۂ̕�������擾����
					datastring += data[index][i];
				}
			}
			//�擾�����������ԋp����
			return datastring;
		}
		catch (System::IndexOutOfRangeException^ e) {
			System::Console::WriteLine(e);
		}
	}

	/*�T�v:�Ώۂ̃��[�U�[�̃f�[�^�����݂��Ă��邩���m�F���邽�߂̊֐�
	����:unsigned data:�J�[�h���擾�����S�f�[�^
	�߂�l:string uid:�J�[�h���擾�������[�U�[ID
	�쐬���F2017.10.10
	�쐬��:K.Asada
	�X�V���e:�p�X���[�h�`�F�b�N���폜
	�X�V��:2017.10.24
	�X�V��:K.Asada*/
	std::string CheckUser(std::vector<std::vector<unsigned char>> data) {
		std::string uid = "";        //�J�[�h���擾�������[�U�[ID���i�[���邽�߂̕�����
		//���[�U�[ID���i�[���ꂽ�u���b�N���w�肵�ă��[�U�[ID���擾����
		uid = GetData(data, UID_INDEX);
		//�擾�������[�U�[���Ńt�@�C�����J��
		std::ifstream ifs((uid+".txt"));
		//���[�U�[ID���t�@�C�����Ƃ����t�@�C�����J���Ȃ��Ƃ��̓��[�U�[�����݂��Ă��Ȃ��Ƃ��ė�O�𓊂���
		if (!ifs.is_open()) {
			//�Ώۂ̃��[�U�[�����݂��Ă��Ȃ��|���O�Ƃ��ē�����
			throw gcnew System::Exception(Constants->ID_NOT_FOUND_ERROR);
		}
		//���肪�I������烆�[�U�[ID��ԋp����
		return uid;
	}

	/*�T�v:���[�U�[�̑����𔻒肵�A����ɉ����������Ԃ��֐�
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	int CheckBit(char check) {
		int countbit = 0;    //�r�b�g�������Ă���ꏊ
							 //�Ώۂ𑖍������r�b�g�ڂ������Ă��邩�𒲂ׂ�
		for (int i = 0; i < 8; i++) {
			//�r�b�g�������Ă����炻�̏ꏊ��ϐ��Ɋi�[����
			if ((check >> i) & 1U) {
				//�r�b�g�������Ă���ꏊ��ۊǂ���
				countbit = i + 1;
				//���[�v�𔲂���
				break;
			}
		}
		//���茋�ʂ�Ԃ�
		return countbit;
	}

	/*�T�v:�R�}���h�̏����������֐�
	����:int beginblock:�R�}���h�𑗐M���ď��߂ɃA�N�Z�X����u���b�N
	�߂�l:std::vector<SENDCOMM> initcommand:�쐬�����R�}���h
	�쐬��:2017.10.13
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> InitCommand(int beginblock) {
		std::vector<SENDCOMM> initcommand;    //�쐬�����R�}���h���i�[���邽�߂̔z��
		SENDCOMM certify = AUTHENTICATE;      //�u���b�N�F�؃R�}���h
											  //�u���b�N�F�؃R�}���h�̔F�ؐ�u���b�N������������
		certify.sendCommand[7] = beginblock;
		//�R�}���h��g�ݗ��ĂĂ���
		initcommand.push_back(LOADKEY);
		//�F�؃R�}���h��g�ݗ��ĂĂ���
		initcommand.push_back(certify);
		//�g�ݗ��Ă��R�}���h��ԋp����
		return initcommand;
	}

	/*�T�v:�Ώۂ̔N���[�N���ǂ����𔻒肷�邽�߂̊֐�
	����:int year:����Ώۂ̔N
	�߂�l:bool judge:�[�N�ł����true���A�Ȃ����false��Ԃ�
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	bool CheckLeapYear(int year) {
		bool judge = true;    //���茋�ʂ��i�[����ꏊ
		//�[�N�̔������
		if (year % 4 == 0) {
			//2��ڂ̔���Ɉڂ�
			if (year % 100 == 0) {
				//3��ڂ̔���Ɉڂ�
				if (year % 400 == 0) {
					//�Ώۂ̔N��4�Ŋ���؂�A100�Ŋ���؂�A400�Ŋ���؂��ꍇ�͉[�N
					judge = true;
				}
				else {
					//�Ώۂ̔N��4�Ŋ���؂�A100�Ŋ���؂�A400�Ŋ���؂�Ȃ������ꍇ�͉[�N�łȂ�
					judge = false;
				}
			}
			else {
				//�Ώۂ̔N��4�Ŋ���؂�A100�Ŋ���؂�Ȃ��ꍇ�͉[�N
				judge = true;
			}
		}
		else {
			//�Ώۂ̔N��4�Ŋ���؂�Ȃ��Ƃ��͉[�N�ł͂Ȃ�
			judge = false;
		}
		//�[�N���ǂ����̔��茋�ʂ�ԋp����
		return judge;
	}

	/*�T�v:���݂̔N�������[�N���l�����Ȃ�����ɕϊ����ĕԋp����֐�
	����:�Ȃ�
	�߂�l:int day:�N�������[�N���l�����Ȃ�����ɕϊ������ϐ�
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	int ConvLeapYear() {
		time_t now = time(NULL);    //���ݓ����擾���邽�߂̏���
		struct tm *pnow = localtime(&now);    //���ݓ����擾���邽�߂̏���
		int year = 0;    //���ݔN���i�[����ϐ�
		int month = 0;   //���݌����i�[����ϐ�
		int day = 0;     //���ݓ����i�[����ϐ�
		//���݂̔N���擾����
		year = pnow->tm_year + 1900;
		//���݂̌����擾����
		month = pnow->tm_mon + 1;
		//���݂̓����擾����
		day = pnow->tm_mday;
		//�N����ɕϊ�����
		for (int i = 1; i < year; i++) {
			//�[�N���ǂ����𔻒肷��
			if (CheckLeapYear(i)) {
				//�[�N�̏ꍇ��1�N��366���Ƃ���
				day += 366;
			}//�[�N�łȂ��ꍇ
			else {
				//�[�N�łȂ��ꍇ��1�N��365���Ƃ���
				day += 365;
			}
		}
		//������ɕϊ�����
		for (int i = 0; i < month - 1; i++) {
			//���ꂼ��̌��ɑΉ����������̑��a�����߂�
			day += yearmonth[i];
		}
		//���߂�����ԋp����
		return day;
	}

	/*�T�v:�󂯎���������[�N���l�����Ȃ���N�A���A���ɕϊ�����֐�
	����:int days:�ϊ��Ώۂ̓�
	�߂�l:int days:���߂���
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
int ConvLeapYear(int days) {
	int year = 0;    //���߂��N���i�[����ϐ�
	int month = 0;   //���߂������i�[����ϐ�
	int day = 0;     //���߂������i�[����ϐ�
	//�[�N���l�����Ȃ������N�ɕϊ�����
	for (int i = 0; days < 366; i++) {
		//�[�N���ǂ����̔�����s��
		if (CheckLeapYear(i)) {
			//�[�N�ł���Εϊ��Ώۂ̓�����366�������Z����
			days -= 366;
		}//�[�N�łȂ����
		else {
			//�[�N�łȂ���Εϊ��Ώۂ̓�����365�������Z����
			days -= 365;
		}
	}
	//�[�N���l�����Ȃ���������ɕϊ�����
	for (int i = 0; days < yearmonth[i]; i++) {
		//���a�̓����炻�̌��ɑΉ��������������Z���Ă���
		days -= yearmonth[i];
	}
	//���߂�����ԋp����
	return days;
}

/*�T�v:�O��̓��ٓ��܂��͑ފٓ����擾���邽�߂̊֐�
����:std::vector<std;;vector<unsigned char>> data:�J�[�h�f�[�^
	:int beginindex:�����̎n�_�ƂȂ�C���f�b�N�X
	:int endindex:�����̏I�_�ƂȂ�C���f�b�N�X
�߂�l:int gettime:�O��̓��ٓ��܂��͑ފٓ�
�쐬��:2017.10.24
�쐬��:K.Asada*/
int GetLastDay(std::vector<std::vector<unsigned char>> data, int beginindex, int endindex) {
	int yearday = 0;    //�J�[�h���̔N����������ɕϊ���������
	int cardday = 0;    //�J�[�h���̓��������
	int gettime = 0;    //�擾�������������
	//�J�[�h���N���������擾����
	yearday = GetCardYear(data);
	//�N����������ɕϊ�����
	yearday = ConvLeapYear(yearday);
	//�J�[�h�f�[�^�̑������s��
	for (int i = 0; beginindex < endindex; i++) {
		//�J�[�h�̓����������擾����
		cardday = GetCardTime(data, beginindex, i);
		//�O��̓��ٓ��܂��͑ފٓ��ł��邩�ǂ����̔�r���s��
		if (yearday == cardday / 1440 && gettime <= cardday) {
			//�O��̓����ł���Ύ擾����
			gettime = cardday;
		}
		//�����Ώۂ��u���b�N�I�[�ł����
		if (i == 14) {
			//�����Ώۂ̃C���f�b�N�X��0�ɖ߂�
			i = 0;
			//���̃u���b�N�ֈړ�����
			beginindex++;
		}
	}
	//�擾�����O��̓��ٓ��܂��͑ފٓ���ԋp����
	return gettime;
}

/*�T�v:PC���̃t�@�C���f�[�^�ƃJ�[�h�f�[�^����v���邩���m�F���邽�߂̊֐�
����:std::vector<std::vector<unsigned char>> data:�J�[�h�f�[�^
	:std::string uid:�t�@�C�����J�����߂̃��[�U�[ID
�߂�l:bool judge:��v�������ǂ����̔���
�쐬��:2017.10.24
�쐬��:K.Asada*/
bool CollationFiledata(std::vector<std::vector<unsigned char>> data, std::string uid) {
	std::vector<std::vector<unsigned char>> filedata;    //�t�@�C�����擾�����f�[�^���i�[���邽�߂̔z��
	bool judge = true;    //�t�@�C���f�[�^����v���邩�ǂ����̔�����i�[����
	//�t�@�C���f�[�^���擾����
	filedata = GetFiledata(uid);
	//��v���邩�̔�����s��
	if (filedata == data) {
		//��v���Ă����true��Ԃ�
		judge = true;
	}
	else {
		//��v���Ă��Ȃ����false��Ԃ�
		judge = false;
	}
	//���茋�ʂ�ԋp����
	return judge;
}

/*�T�v:�t�@�C���f�[�^���擾���Ĕz��Ɋi�[���ĕԋp����֐�
����:std::string uid:�t�@�C�����J�����߂̃��[�U�[ID
�߂�l:std::vector<std::vector<unsigned char>> filedata:�t�@�C���f�[�^���i�[�����z��
�쐬��:2017.10.24
�쐬��:K.Asada*/
std::vector<std::vector<unsigned char>> GetFiledata(std::string uid) {
	char getdata;    //�t�@�C������擾����1�o�C�g���̃f�[�^���i�[����ϐ�
	std::vector<std::vector<unsigned char>> filedata = std::vector<std::vector<unsigned char>>(BLOCK_COUNT, std::vector<unsigned char>(0));
	int blockindex = 0;    //�C���f�b�N�X
	//�t�@�C���X�g���[�����J��
	std::ifstream ifs(uid + ".txt");
	//�t�@�C���f�[�^�̑������s��
	for (int i = 0; i < END_INDEX; i++) {
		if (!ifs.eof()) {
			//1�o�C�g���擾����
			ifs.get(getdata);
		}
		//1�u���b�N���̃f�[�^���擾����
		for (int j = 0; j < 16; j++) {
			//�t�@�C���f�[�^���擾�ł��Ă��邩�̔�����s��
			if (getdata != '\n' && !ifs.eof()) {
				//�擾�����t�@�C���f�[�^��z��Ɋi�[����
				filedata[i].push_back(getdata);
				//���̃f�[�^��p�ӂ���
				ifs.get(getdata);
			}
			else {
				//�t�@�C���f�[�^���Ȃ����NULL���i�[����
				filedata[i].push_back('\0');
			}
		}
	}
	//�擾�����t�@�C���f�[�^��ԋp����
	return filedata;
}

	/*�T�v:�J�[�h�̓��ٓ��܂��͑ފٓ����i�[���ꂽ�u���b�N�̒��Ŏ��̍X�V�ΏۂƂȂ�u���b�N���擾���邽�߂̊֐�
	����:std::vector<std::vector<unsigned char>> data:�J�[�h�f�[�^
	    :int beginindex:�����̎n�_�ƂȂ�u���b�N
		:int endindex:�����̏I�_�ƂȂ�u���b�N
	�߂�l:int updateblock:���̍X�V�ΏۂƂȂ�u���b�N
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	int GetLastBlock(std::vector<std::vector<unsigned char>> data, int beginindex, int endindex) {
		int yearday = 0;        //�J�[�h�Ɋi�[���ꂽ�N�������i�[����ϐ�
		int cardday = 0;        //�e�u���b�N���Ƃ̓��t
		int gettime = 0;        //�擾�����J�����g�̓��t
		int updateblock = 0;    //�X�V�Ώۂ̃u���b�N
		int updateindex = 0;    //�X�V�Ώۂ̃C���f�b�N�X
		//�J�[�h����O��̔N�������擾����
		yearday = GetCardYear(data);
		//�擾�����N��������ɕϊ�����
		yearday = ConvLeapYear(yearday);
		//�X�V�Ώۂ̃u���b�N��T�����߂ɑ�������
		for (int i = 0; beginindex < endindex; i+= 2) {
			//�Ώۂ̃f�[�^������������擾����
			cardday = GetCardTime(data, beginindex, i);
			//�O��̃J�[�h�ւ̃A�N�Z�X���ɍX�V�����ꏊ������Ύ擾����
			if (yearday == cardday / 1440 && gettime <= cardday) {
				//���������擾����
				gettime = cardday;
			}
			//�u���b�N�̏I�[�ɂ��ǂ蒅�����瑖���Ώۂ����̃u���b�N�ɐ؂�ւ���
			if (i == 14) {
				//�C���f�b�N�X��0�ɖ߂�
				i = 0;
				//�u���b�N��i�߂�
				beginindex++;
			}
			//�X�V�ΏۂƂȂ�u���b�N���L�^����
			updateblock = beginindex;
		}
		//�X�V�ΏۂƂȂ�u���b�N��ԋp����
		return updateblock;
	}

	/*�T�v:�ފُ�Ԃ𒲂ׂđΉ������������ԋp���邽�߂̊֐�
	����:std::vector<std::vector<unsigned char>> data:�J�[�h�f�[�^
	�߂�l:System::String check:�ފُ�ԂɑΉ�����������
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	System::String^ CheckLeaveState(std::vector<std::vector<unsigned char>> data) {
		int lastenter = 0;    //�O��̓��ٓ����i�[����ϐ�
		int lastleave = 0;    //�O��̑ފٓ����i�[����ϐ�
		System::String^ check = "";    //�ފُ�Ԃ�����������
		//�O��̓��ٓ����擾����
//		lastenter = GetLastDay(data, TIMES_1_INDEX, END_INDEX);
		//�O��̑ފٓ����擾����
//		lastleave = GetLastDay(data, LEAVE_1_INDEX, END_INDEX);
		//�O��̓��ٓ����O��̑ފٓ����O�ł���Γ��ق��Ă��Ȃ��Ƃ���
		if (lastleave > lastenter) {
			//���ق��Ă��Ȃ��|�̕�������i�[����
			check = Constants->NOT_ENTER;
		}
		//�擾�����������ԋp����
		return check;
	}

	/*�T�v:���ُ�Ԃ𒲂ׂđΉ������������ԋp����֐�
	����:std::vector<std::vector<unsigned char>> data:�J�[�h�f�[�^
	�߂�l:System::String^ check:��ԂɑΉ�����������
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	System::String^ CheckEnterState(std::vector<std::vector<unsigned char>> data) {
		int lastenter = 0;             //�O��̓��ٓ�
		int lastleave = 0;             //�O��̑ފٓ�
		int current = 0;               //���ݓ���
		System::String^ check = "";    //���茋�ʂ̕�����
		//�O��̓��ٓ����擾����
//		lastenter = GetLastDay(data, TIMES_1_INDEX, END_INDEX);
		//�O��̑ފٓ����擾����
//		lastleave = GetLastDay(data, LEAVE_1_INDEX, END_INDEX);
		//���݂̓������擾����
		current = GetNowTime();
		//���ُ�Ԃ𔻒肷��
		if (lastleave > lastenter && current - lastenter >= 1440) {
			//���ُ�Ԃ��O��̓��ق���1���ȏ�o�߂��Ă����
			check = Constants->ENTER_DAY;
		}
		//�擾�������蕶�����ԋp����
		return check;
	}

	/*�T�v:�J�[�h����2�o�C�g�ɕ������ꂽ���ٓ��܂��͑ފٓ���unsigned short int�^�ɕϊ����ĕԋp����֐�
	����:std::vector<std::vector<unsigned char>> data:�J�[�h�f�[�^
	    :int datablock:�Ώۂ��i�[���ꂽ�u���b�N
		:int dataindex:�Ώۂ��i�[����Ă���C���f�b�N�X
	�߂�l:ITOC time:�w�肳�ꂽ2�o�C�g�ɕ������ꂽ���t��unsigned short int�^�ɘA�������ϐ�
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	unsigned short int GetCardTime(std::vector<std::vector<unsigned char>> data, int datablock, int dataindex) {
		ITOC time;    //2�o�C�g�ɕ������ꂽ���̂�A�����邽�߂̋��L��
		//���ʃo�C�g���擾����
		time.bytes[0] = data[datablock][dataindex++];
		//��ʃo�C�g���擾����
		time.bytes[1] = data[datablock][dataindex];
		//�A������unsigned short int�^��ԋp����
		return time.num;
	}

	/*�T�v:�J�[�h����4�o�C�g�ɕ������ꂽ�N������unsigned int�^�ɕϊ����ĕԋp����֐�
	����:std::vector<std::vector<unsigned char>> data:�J�[�h�f�[�^
	�߂�l:UITOC year:unsigned int�^�ɕϊ������N����
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	unsigned int GetCardYear(std::vector<std::vector<unsigned char>> data) {
		UITOC years;    //4�o�C�g�ɕ������ꂽ���̂�A�����邽�߂̋��L��
		//1�o�C�g���A������
		for (int i = 0; i < sizeof(unsigned int); i++) {
			//1�o�C�g���A�����Ă���
			years.bytes[i] = data[YEAR_INDEX][i];
		}
		//�A�����I����unsigned int�^��ԋp����
		return years.num;
	}

	/*�T�v:�J�[�h�Ɋi�[���ꂽ���������𕶎���ɕϊ�����֐�
	����:std::vector<std::vcotr<unsigned char>> data:�J�[�h�f�[�^
	�߂�l:std::vector<string> times:�������𕶎���ɕϊ������z��
	�쐬��:2017.10.16
	�쐬��:K.Asada*/
	std::vector<std::string> ConvTimes(std::vector<std::vector<unsigned char>> data, int index, int endindex) {
		try {
			std::vector<std::string> times;        //�������𕶎���ɕϊ��������̂��i�[���邽�߂̔z��
			ITOC gettimes;                         //�J�[�h�f�[�^�̒��ɂ���char�^�̐��l��unsigned int�^�ɕϊ����邽�߂̋��L��
			int day = 0;                           //�擾���������i�[����ϐ�
			int hour = 0;                          //�擾�������Ԃ��i�[����ϐ�
			int min = 0;                           //�擾���������i�[����ϐ�
			int timeindex = index;
			//�J�[�h�f�[�^�ɂ�����������𑖍����Ă���
			for (int i = 1; timeindex < endindex && data[timeindex][i * 2] != '\0'; i++) {
				//�J�[�h�f�[�^���������̉���8�r�b�g���擾����
				gettimes.bytes[0] = data[timeindex][i * 2];
				//�J�[�h�f�[�^���������̏��8�r�b�g���擾����
				gettimes.bytes[1] = data[timeindex][i * 2 + 1];
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


	/*�T�v:���r�b�g�ڂ������Ă��邩�ɉ������������Ԃ��֐�
	����:string name1:1�r�b�g�ڂ������Ă���Ƃ��ɕԂ�������
	:string name2:2�r�b�g�ڂ������Ă���Ƃ��ɕԂ�������
	:string name3:3�r�b�g�ڂ������Ă���Ƃ��ɕԂ�������
	:string name4:4�r�b�g�ڂ������Ă���Ƃ��ɕԂ�������
	�߂�l:string name:�r�b�g���ɉ�����������
	�쐬��:2017.10.17
	�쐬��:K.Asada*/
	std::string GetElem(unsigned char data, std::string name0, std::string name1, std::string name2, std::string name3) {
		std::string name = "";    //�ԋp�p�̕�����
		int checkbit = 0;         //���r�b�g�ڂ������Ă��������i�[����ϐ�
		//���r�b�g�ڂ������Ă��邩�𒲂ׂ�
		checkbit = this->CheckBit(data);
		//���r�b�g�ڂ������Ă������ɂ���đΉ������������ԋp����
		switch (checkbit) {
			//1�̎��͈���1�̕������Ԃ�
		case 0:name = name0;
			break;
			//2�̎��͈���2�̕������Ԃ�
		case 1:name = name1;
			break;
			//3�̎��͈���3�̕������Ԃ�
		case 2:name = name2;
			break;
			//4�̎��͈���4�̕������Ԃ�
		case 3:name = name3;
			break;
		}
		//�擾�����������ԋp����
		return name;
	}
};
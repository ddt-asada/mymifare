#pragma once

#include "picojson.h"
#include <stdio.h>
#include <sstream>
#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <bitset>
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
	void UpdateCardData(std::vector <std::vector<unsigned char>> data, SCARDCONTEXT hContext, SCARDHANDLE hCard, DWORD ActiveProtocol, int beginindex) {
		ConnectCard* con = new ConnectCard();    //�J�[�h�ʐM�N���X���C���X�^���X������
		std::vector<SENDCOMM> sendcomm;    //�J�[�h�ւ̑��M�R�}���h
		std::vector<SENDCOMM> tmp;
		ITOC now;            //���݂̓��������擾���邽�߂̕ϐ�
		int updateblock = 0;              //�X�V�Ώۂ̃u���b�N
		int updateindex = 0;              //�X�V�Ώۂ̃C���f�b�N�X
		//�X�V�Ώۂ̃u���b�N�A�C���f�b�N�X���擾����
		GetUpdateBlock(beginindex, &updateblock, &updateindex);
		//���ݓ��������擾����
		now.num = GetNowTime();
		//�X�V�Ώۂ̃f�[�^�����݂̓������ɏ���������
		ReadyData(data[updateblock], updateindex, now);
		//�J�[�h���̔N�����̏�Ԃ��m�F����֐����Ăяo��
		tmp = CheckYear(data);
		sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		//�X�V�Ώۂ̓�����������������R�}���h��g�ݗ��Ă�
		tmp = ReadyUpdateData(data[updateblock], updateblock);
		sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		//�R�}���h�̏I���������R�}���h��A������
		sendcomm.push_back(ENDCOMMAND);
		//�J�[�h�փR�}���h�𑗐M����
		con->Transmit(hContext, hCard, ActiveProtocol, sendcomm);
		return;
	}

	/*�T�v:�J�[�h���̔N�����ƌ��݂̔N�������r���A�K�v�ɉ����ď���������֐�
	����:std::vector<std::vector<unsigned char>> data�J�[�h�f�[�^
	�߂�l:std::vector<SENDCOM>:���M�f�[�^
	�쐬��:2017.10.25
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> CheckYear(std::vector<std::vector<unsigned char>>& data) {
		UITOC nowyears;    //���݂̔N�������i�[����
		std::vector<SENDCOMM> senddata;    //���M�R�}���h
		UITOC years;    //�J�[�h���̔N�������i�[���邽�߂̋��L��
		//�J�[�h���̔N�������擾����
		years.num = GetCardYear(data);
		//���݂̔N�������擾����
		nowyears.num = GetNowYear();
		//�N���̔�����s��
		if (years.num / 100 != nowyears.num / 100) {
			//�N��������Ă����ꍇ�͓��ٓ��A�ފٓ��A�N�������X�V����
			senddata = UpdateAllDate(data, nowyears);
		}//�N�����̔�����s��
		else if (years.num != nowyears.num) {
			//��������Ă����ꍇ�̓J�[�h���̔N�����݂̂�����������
			senddata = UpdateYear(nowyears, data);
		}
		//�쐬�����X�V�p�̃R�}���h��ԋp����
		return senddata;
	}

	/*�T�v:�J�[�h�֑��M����f�[�^�̑g�ݗ��āA�R�}���h�̍쐬���s���֐�
	����:string setdata:���M����f�[�^
	�߂�l:unsigned char:�f�[�^�𑗐M���邽�߂̃R�}���h
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> ReadySetData(std::vector<std::vector<unsigned char>> data, int blockindex) {
		try {
			std::vector<SENDCOMM> sendcomm;        //�g�ݗ��Ă��R�}���h���i�[���邽�߂̍\����
			SENDCOMM certify = AUTHENTICATE;       //�u���b�N�F�؃R�}���h�̃R�s�[
			SENDCOMM sendcard = SENDCARD;          //�f�[�^���M�R�}���h�̃R�s�[
												   //�R�}���h������������
			sendcomm = InitCommand(blockindex);
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

	/**/
	unsigned int GetNowYear() {
		time_t now = time(NULL);    //���ݓ����擾���邽�߂̏���
		struct tm *pnow = localtime(&now);    //���ݓ����擾���邽�߂̏���
		int ret = 0;
		int year = 0;    //���ݔN���i�[����ϐ�
		int month = 0;   //���݌����i�[����ϐ�
		int day = 0;     //���ݓ����i�[����ϐ�
						 //���݂̔N���擾����
		year = pnow->tm_year + 1900;
		//���݂̌����擾����
		month = pnow->tm_mon + 1;
		//���݂̓����擾����
		day = pnow->tm_mday;
		ret = year * 10000 + month * 100 + day;
		return ret;
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
	std::vector<SENDCOMM> ReadyUpdateData(std::vector<unsigned char> data, int updateblock) {
		std::vector<SENDCOMM> senddata;    //�X�V�p�̃R�}���h
		SENDCOMM copycomm = SENDCARD;      //�f�[�^���M�R�}���h�̃e���v���[�g
		int block = writeblock[updateblock];
		//�R�}���h�̏����l���擾����
		senddata = InitCommand(block);
		//���M�R�}���h�̑Ώۂ̃u���b�N��ݒ肷��
		copycomm.sendCommand[3] = block;
		//1�u���b�N���̑��M�R�}���h��g�ݗ��ĂĂ���
		for (int i = 0; i < 16; i++) {
			//���M�R�}���h�����ɑg�ݗ��ĂĂ���
			copycomm.sendCommand[5 + i] = data[i];
		}
		//�g�ݗ��Ă����M�R�}���h��ԋp�p�̃R�}���h�ɘA������
		senddata.push_back(copycomm);
		//�g�ݗ��Ă��R�}���h��ԋp����
		return senddata;
	}

	/*�T�v:�J�[�h���̔N�����A���ٓ��A�ފٓ������ׂčX�V���邽�߂̃R�}���h��g�ݗ��Ă�֐�
	����:std::vector<std::vector<unsigned char>> data:�J�[�h�f�[�^
	    :UITOC nowyears:���ݔN����
	�߂�l:std::vector<SENDCOMM> sendcomm:�X�V�p�̃R�}���h
	�쐬��:�@2017.10.25
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> UpdateAllDate(std::vector<std::vector<unsigned char>> data, UITOC nowyears) {
		int updateblock = 0;    //�X�V�Ώۂ̃u���b�N
		int updateindex = 0;    //�X�V�Ώۂ̃C���f�b�N�X
		std::vector<SENDCOMM> sendcomm;    //�X�V�p�̃R�}���h
		std::vector<SENDCOMM> tmp;
		//�X�V�Ώۂ̃u���b�N���擾����
		GetUpdateBlock(TIMES_1_INDEX, &updateblock, &updateindex);
		//�f�[�^���X�V���Ă���
		for (int i = TIMES_1_INDEX; i <= updateblock; i++) {
			//1�u���b�N���f�[�^���X�V���Ă���
			for (int j = 0; j < 16; j++) {
				//���ݓ��������i�[���ׂ��ꏊ�ɂ��ǂ蒅�������߂�
				if (i == updateblock && j == updateindex * 2) {
					break;
				}//����ȊO�̎���
				else {
					//�Â��f�[�^���폜���Ă���
					data[i][j] = 0;
					data[i + 6][j] = 0;
				}
			}
			//1�u���b�N���̍X�V�R�}���h��g�ݗ��Ă�
			tmp = ReadyUpdateData(data[i], i);
			sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
			//1�u���b�N���̍X�V�R�}���h��g�ݗ��Ă�
			tmp = ReadyUpdateData(data[i], i);
			sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		}
		//�N�������X�V����R�}���h���i�[����
		tmp = UpdateYear(nowyears, data);
		sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		//�g�ݗ��Ă��R�}���h���i�[����
		return sendcomm;
	}

	/*�T�v:�N�����݂̂��X�V����R�}���h��g�ݗ��Ă�֐�
	�쐬��:2017.10.25
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> UpdateYear(UITOC nowyear, std::vector<std::vector<unsigned char>> data) {
		ITOC lowbit;    //���ݔN�����̉��ʃr�b�g���i�[���邽�߂̋��L��
		ITOC upperbit;  //���ݔN�����̏�ʃr�b�g���i�[���邽�߂̋��L��
		std::vector<SENDCOMM> sendcomm;    //�ԋp�p�̃R�}���h
		std::vector<SENDCOMM> tmp;
		//���ݔN���������2�o�C�g�Ɖ���2�o�C�g�ɕ�������
		for (int i = 0; i < 2; i++) {
			//����2�o�C�g���i�[����
			lowbit.bytes[i] = nowyear.bytes[i];
			//���2�o�C�g���i�[����
			upperbit.bytes[i] = nowyear.bytes[i + 2];
		}
		//�X�V�f�[�^�̏������s��
		ReadyData(data[YEAR_1_INDEX], 0, lowbit);
		//�X�V�f�[�^�̏������s��
		ReadyData(data[YEAR_2_INDEX], 0, upperbit);
		//�X�V�p�̃R�}���h��g�ݗ��Ă�
		tmp = ReadyUpdateData(data[YEAR_1_INDEX], YEAR_1_INDEX);
		sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		//�X�V�p�̃R�}���h��g�ݗ��Ă�
		tmp = ReadyUpdateData(data[YEAR_2_INDEX], YEAR_2_INDEX);
		sendcomm.insert(sendcomm.end(), tmp.begin(), tmp.end());
		//�g�ݗ��Ă��R�}���h��ԋp����
		return sendcomm;
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
//	filedata = GetFiledata(uid);
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

	/*�T�v:�J�[�h�̓��ٓ��܂��͑ފٓ����i�[���ꂽ�u���b�N�̒��Ŏ��̍X�V�ΏۂƂȂ�u���b�N���擾���邽�߂̊֐�
	����:std::vector<std::vector<unsigned char>> data:�J�[�h�f�[�^
	    :int beginindex:�����̎n�_�ƂȂ�u���b�N
		:int endindex:�����̏I�_�ƂȂ�u���b�N
	�߂�l:int updateblock:���̍X�V�ΏۂƂȂ�u���b�N
	�쐬��:2017.10.24
	�쐬��:K.Asada
	�X�V���e:���W�b�N��ύX
	�X�V��:2017.10.25
	�X�V��:K.Asada*/
	void GetUpdateBlock(int block, int* updateblock, int* updateindex) {
		int nowday = 0;    //���ݓ������i�[����ϐ�
		//���ݓ����擾����
		nowday = GetNowDay();
		//�X�V�u���b�N���v�Z����
		*updateblock = block + nowday / 8;
		//�X�V�C���f�b�N�X���v�Z����
		*updateindex = nowday % 8;
		return;
	}

	/*�T�v:���݂̓����擾���邽�߂̊֐�
	����:�Ȃ�
	�߂�l:���ݓ�
	�쐬��:2017.10.25
	�쐬��:K.Asada*/
	int GetNowDay() {
		time_t now = time(NULL);    //���ݓ����擾���邽�߂̏���
		struct tm *pnow = localtime(&now);    //���ݓ����擾���邽�߂̏���
		int day = 0;     //���ݓ����i�[����ϐ�
		//���݂̓����擾����
		day = pnow->tm_mday;
		//�擾�������݂̓���ԋp����
		return day;
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
		for (int i = 0; i < 2; i++) {
			//1�o�C�g���A�����Ă���
			years.bytes[i] = data[YEAR_1_INDEX][i];
			years.bytes[i + 2] = data[YEAR_2_INDEX][i];
		}
		//�A�����I����unsigned int�^��ԋp����
		return years.num;
	}

	/*�T�v:�󂯎����unsigned short int�^���J�[�h�Ɋi�[���邽�߂ɕ�������֐�
	����:�i�[��̃J�[�h�f�[�^
	�߂�l:�Ȃ�
	�쐬��:2017.10.25
	�쐬��:K.Asada*/
	void ReadyData(std::vector<unsigned char>& data, int updateblock, ITOC set) {
		//���ʃo�C�g���i�[����
		data[updateblock * 2] = set.bytes[0];
		//��ʃo�C�g���i�[����
		data[updateblock * 2 + 1] = set.bytes[1];
		return;
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

	/*�T�v:*/
	UITOC ConvJSONYear(std::string birthday) {
		UITOC conbirth;    //�X�g�����O����擾�����ϐ����i�[���鋤�L��
		//�󂯎���������񂩂�N���폜����
		birthday = AssignmentErase(birthday, "�N");
		//�����񂩂猎���폜����
		birthday = AssignmentErase(birthday, "��");
		//�����񂩂��l���폜����
		birthday = AssignmentErase(birthday, "��");
		//�N�������폜���Đ��l�����ɂȂ����������ϊ�����
		conbirth.num = std::stoi(birthday);
		//�ϊ������ϐ���ԋp����
		return conbirth;
	}

	/*�T�v:*/
	char ConvJSONBit(std::string check, std::string name1, std::string name2, std::string name3, std::string name4) {
		char ret = 0;    //�ԋp�p�̕ϐ�
		//�ǂ̃r�b�g�������Ă����Ԃɂ��邩�̔����Ԃ�
		if (check == name1) {
			//1�Ԗڂ̎��͂ǂ̃r�b�g�������Ă��Ȃ���Ԃ�Ԃ�
			ret = 0;
		}
		else if (check == name2) {
			//2�Ԗڂ̎���1�r�b�g�ڂ������Ă����Ԃ�Ԃ�
			ret = 1;
		}
		else if (check == name3) {
			//3�Ԗڂ̎���2�r�b�g�ڂ������Ă����Ԃ�Ԃ�
			ret = 1 << 1;
		}
		else if (check == name4) {
			//4�Ԗڂ̎���4�r�b�g�ڂ������Ă����Ԃ�Ԃ�
			ret = 1 << 2;
		}
		//���茋�ʂ�ԋp����
		return ret;
	}

	/*�T�v:*/
	std::string AssignmentErase(std::string target, std::string assignment) {
		int index = 0;    //������폜�̋N�_
		int strlen = 0;   //�폜���钷��
		//�폜�̋N�_���擾����
		index = target.find(assignment);
		//�폜�̒������擾����
		strlen = assignment.length();
		//�w�肵����������폜����
		target.erase(index, strlen);
		//�폜���I�����������ԋp����
		return target;
	}

	/*�T�v:�t�@�C���f�[�^����S�����擾����֐�
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	std::vector<std::vector<unsigned char>> GetFileData(std::string uid) {
		picojson::object obj;
		std::vector<std::vector<unsigned char>> retdata = std::vector<std::vector<unsigned char>>(BLOCK_COUNT, std::vector<unsigned char>(16, '\0'));    //�ԋp�p�̃t�@�C���f�[�^
		std::vector<std::vector<unsigned char>> tmpdata;
		unsigned char tmp[16] = { '\0' };                            //�e�f�[�^���擾���邽�߂̈ꎞ�I�Ȓu����
		std::vector<std::string> test;
		std::string str = "";
		UITOC con;                                          //�������int�^�ɕϊ�����Ƃ���1�o�C�g���Ƃɕ������邽�߂̋��L��
		obj = GetPicoObj(uid);
		//JSON���烆�[�U�[ID���擾����
		retdata[0] = ConvFileData(obj[UID_LABEL].get<std::string>());
		//JSON���疼�O�i���j���擾����
		retdata[1] = ConvFileData(obj[FIRST_NAME].get<std::string>());
		//JSON���疼�O�i���j���擾����
		retdata[2] = ConvFileData(obj[LAST_NAME].get<std::string>());
		//JSON����p�X���[�h���擾����
		retdata[3] = ConvFileData(obj[PASS_LABEL].get<std::string>());
		//JSON����d�b�ԍ����擾����
		retdata[4] = ConvFileData(obj[TELL_LABEL].get<std::string>());
		//JSON���琶�N�������擾����
		con.num = StrYear(obj[BIRTH_LABEL].get<std::string>());
		retdata[5][0] = con.bytes[0];
		retdata[5][1] = con.bytes[1];
		retdata[5][2] = con.bytes[2];
		retdata[5][3] = con.bytes[3];
		//JSON���瑮�����擾����
		retdata[5][4] = ConvJSONBit(obj[ELEM_LABEL].get<std::string>(), ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4);
		//JSON���猠�����擾����
		retdata[5][5] = ConvJSONBit(obj[ADM_LABEL].get<std::string>(), ADM_NAME1, ADM_NAME2, "", "");
		//JSON�����E���擾����
		retdata[5][6] = ConvJSONBit(obj[OCCUP_LABEL].get<std::string>(), POS_NAME1, POS_NAME2, POS_NAME3, POS_NAME4);
		//JSON���珊���O���[�v���擾����
		retdata[5][7] = ConvJSONBit(obj[GROUP_LABEL].get<std::string>(), "", OCCUP_NAME1, OCCUP_NAME2, OCCUP_NAME3) << 4;
		//JSON���珊�����擾����
		retdata[5][7] = ConvJSONBit(obj[DEPART_LABEL].get<std::string>(), "", DEPART_NAME1, DEPART_NAME2, DEPART_NAME3);
		//JSON����Z�����擾����
		str = obj[ADDRESS_LABEL].get<std::string>();
		//16�o�C�g���ɕ������Ĕz��Ɋi�[����
		retdata[6] = ConvFileData(str, 0, 16);
		retdata[7] = ConvFileData(str, 16, 32);
		retdata[8] = ConvFileData(str, 32, 48);
		retdata[9] = ConvFileData(str, 48, 64);
		retdata[10] = ConvFileData(str, 64, 80);
		retdata[11] = ConvFileData(str, 80, 96);
		//���ٓ����擾����
		tmpdata = GetFileTime(obj[ENTER_LABEL].get<picojson::object>());
		retdata[12] = tmpdata[0];
		retdata[13] = tmpdata[1];
		retdata[14] = tmpdata[2];
		retdata[15] = tmpdata[3];
		//�ފٓ����擾����
		tmpdata = GetFileTime(obj[LEAVE_LABEL].get<picojson::object>());
		retdata[18] = tmpdata[0];
		retdata[19] = tmpdata[1];
		retdata[20] = tmpdata[2];
		retdata[21] = tmpdata[3];
		//�N�������擾����
		con.num = StrYear(obj[YEAR_LABEL].get<std::string>());
		retdata[12][0] = con.bytes[0];
		retdata[12][1] = con.bytes[1];
		retdata[18][0] = con.bytes[0];
		retdata[18][1] = con.bytes[1];
		return retdata;
	}

	std::vector<unsigned char> ConvFileData(std::string filedata) {
		std::vector<unsigned char> data = std::vector<unsigned char>(16, '\0');
		for (int i = 0; i < filedata.size(); i++) {
			data[i] = filedata[i];
		}
		return data;
	}

	std::vector<unsigned char> ConvFileData(std::string filedata, int begin, int end) {
		std::vector<unsigned char> data = std::vector<unsigned char>(16, '\0');
		int index = 0;
		for (int i = begin; i < filedata.size() && i < end; i++) {
			data[index++] = filedata[i];
		}
		return data;
	}

	std::vector<std::vector<unsigned char>> GetFileTime(picojson::object obj) {
		std::vector<std::vector<unsigned char>> retdata = std::vector<std::vector<unsigned char>>(4, std::vector<unsigned char>(16, '\0'));    //�ԋp�p�̃t�@�C���f�[�^
		int year = 0;    //�N���擾���邽�߂̕ϐ�
		int month = 0;    //�����擾���邽�߂̕ϐ�
		int day = 0;     //�����擾���邽�߂̕ϐ�
		ITOC tmp;
		picojson::array days;
		std::string key = "";    //JSON������������擾���邽�߂̃L�[
		std::string test;
		time_t now = time(NULL);
		struct  tm *pnow = localtime(&now);
		//�N���擾����
		year = pnow->tm_year + 1900;
		//�����擾����
		month = pnow->tm_mon;
		//�����擾����
		day = pnow->tm_mday + 1;
		//31�����̗������擾����
		for (int i = 0; i < 31; i++) {
			//JSON������������擾���邽�߂̃L�[��g�ݗ��Ă�
			key = std::to_string(year) + "�N" + std::to_string(month) + "��" + std::to_string(day) + "��";
			//�L�[�ɑΉ��������������擾�ł����
			if (obj[key].is<picojson::array>()) {
				days = obj[key].get<picojson::array>();
				picojson::array::iterator itr = days.end();
				test = (--itr)->get<std::string>();
				tmp.num = StrTime(test);
				retdata[day / 8][(day % 8) * 2] = tmp.bytes[0];
				retdata[day / 8][(day % 8) * 2 + 1] = tmp.bytes[1];
			}
			if (day == 31) {
				day = 1;
				month += 1;
			}
			else {
				day++;
			}
		}
		return retdata;
	}

	/*�T�v:���݂̓��������t�@�C���Ɋi�[���邽�߂̕�����ɕϊ�����֐�
	����:�Ȃ�
	�߂�l:std::string timestr:���݂̓�����������������
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	std::string TimeStr() {
		time_t now = time(NULL);    //���ݎ������擾���邽�߂̍\����
		struct tm *pnow = localtime(&now);    //���ݎ������擾���邽�߂̍\����
		int day = 0;    //���ݓ����i�[���邽�߂̕ϐ�
		int hour = 0;   //���ݎ����i�[���邽�߂̕ϐ�
		int minute = 0; //���ݕ����i�[���邽�߂̕ϐ�
		std::string timestr = "";    //���ݓ�����������������
		//���݂̓����擾����
		day = pnow->tm_mday;
		//���݂̎����擾����
		hour = pnow->tm_hour;
		//���݂̕����擾����
		minute = pnow->tm_min;
		//������Ƃ��đg�ݗ��Ă�
		timestr = std::to_string(day) + "��" + std::to_string(hour) + "��" + std::to_string(minute) + "��";
		//�쐬�����������ԋp����
		return timestr;
	}

	/*�T�v:���������t�@�C���Ɋi�[���邽�߂̕�����ɕϊ�����֐�
	����:int nowtime:�������𕪂ɕϊ������ϐ�
	�߂�l:std::string timestr:������������������
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	std::string TimeStr(int nowtime) {
		int day = 0;    //���ݓ����i�[���邽�߂̕ϐ�
		int hour = 0;   //���ݎ����i�[���邽�߂̕ϐ�
		int minute = 0; //���ݕ����i�[���邽�߂̕ϐ�
		std::string timestr = "";    //���ݓ�����������������
		//������������擾����
		day = nowtime / 1440;
		//�������玞���擾����
		hour = nowtime / 60 - day * 24;
		//�������番���擾����
		minute = nowtime % 60;
		//������Ƃ��đg�ݗ��Ă�
		timestr = std::to_string(day) + "��" + std::to_string(hour) + "��" + std::to_string(minute) + "��";
		//�쐬�����������ԋp����
		return timestr;
	}

	/*�T�v:���݂̔N�������t�@�C���Ɋi�[���邽�߂̕�����ɕϊ�����̊֐�
	����:�Ȃ�
	�߂�l:std::string yearstr:���݂̔N�����𕶎���ɕϊ���������
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	std::string YearStr() {
		time_t now = time(NULL);    //���ݎ������擾���邽�߂̍\����
		struct tm *pnow = localtime(&now);    //���ݎ������擾���邽�߂̍\����
		int year = 0;    //���ݔN���i�[���邽�߂̕ϐ�
		int month = 0;   //���݌����i�[���邽�߂̕ϐ�
		int day = 0; //���ݓ����i�[���邽�߂̕ϐ�
		std::string yearstr = "";    //���ݓ�����������������
									 //���݂̔N���擾����
		year = pnow->tm_year + 1900;
		//���݂̌����擾����
		month = pnow->tm_mon + 1;
		//���݂̓����擾����
		day = pnow->tm_mday;
		//������Ƃ��đg�ݗ��Ă�
		yearstr = std::to_string(year) + "�N" + std::to_string(month) + "��" + std::to_string(day) + "��";
		//�쐬�����������ԋp����
		return yearstr;
	}

	/*�T�v:�N�������t�@�C���Ɋi�[���邽�߂̕�����ɕϊ�����̊֐�
	����:int nowyear:�N�����������ϐ�
	�߂�l:std::string yearstr:���݂̔N�����𕶎���ɕϊ���������
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	std::string YearStr(int nowyear) {
		int year = 0;    //���ݔN���i�[���邽�߂̕ϐ�
		int month = 0;   //���݌����i�[���邽�߂̕ϐ�
		int day = 0; //���ݓ����i�[���邽�߂̕ϐ�
		std::string yearstr = "";    //���ݓ�����������������
									 //���݂̔N���擾����
		year = nowyear / 10000;
		//���݂̌����擾����
		month = nowyear / 100 - year * 100;
		//���݂̓����擾����
		day = nowyear % 100;
		//������Ƃ��đg�ݗ��Ă�
		yearstr = std::to_string(year) + "�N" + std::to_string(month) + "��" + std::to_string(day) + "��";
		//�쐬�����������ԋp����
		return yearstr;
	}

	/*�T�v:�����������������񂩂�������������ϐ��ɕϊ�����֐�
	����:std:: string timestr:������������������
	�߂�l:int time:�������������ϐ�
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	int StrTime(std::string timestr) {
		int time = 0;    //���������i�[���邽�߂�������
		int begin = 0;
		int end = 0;   //�����񂩂�������𔲂��o�����̃C���f�b�N�X
		std::string day = "";//��������������
		std::string hour = "";    //��������������
		std::string minute = "";  //��������������
		//������̒���"��"�̈ʒu��T��
		end = timestr.find("��");
		//������̒�������𔲂��o��
		day = timestr.substr(0, end);
		//���̎n�_��ݒ肷��
		begin = end + 1;
		//�������"��"�̈ʒu��T��
		end = timestr.find("��");
		//������̒����玞�𔲂��o��
		hour = timestr.substr(begin, end - begin);
		//���̎n�_��ݒ肷��
		begin = end + 1;
		//�������"��"�̈ʒu��T��
		end = timestr.find("��");
		//������̒����番�𔲂��o��
		minute = timestr.substr(begin, end - begin);
		//�����񂩂�ϐ��ɕϊ�����
		time = std::stoi(day) * 1440 + std::stoi(hour) * 60 + std::stoi(minute);
		//�ϐ���ԋp����
		return time;
	}

	/*�T�v:�N���������������񂩂�N�����������ϐ��ɕϊ�����֐�
	����:std:: string yearstr:�N����������������
	�߂�l:int years:�N�����������ϐ�
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	int StrYear(std::string yearstr) {
		int years = 0;    //�N�������i�[���邽�߂�������
		int begin = 0;
		int end = 0;   //�����񂩂�N�����𔲂��o�����̃C���f�b�N�X
		std::string year = "";//�N������������
		std::string month = "";    //��������������
		std::string day = "";  //��������������
								  //������̒���"�N"�̈ʒu��T��
		end = yearstr.find("�N");
		//������̒�������𔲂��o��
		year = yearstr.substr(0, end);
		//���̎n�_��ݒ肷��
		begin = end + 1;
		//�������"��"�̈ʒu��T��
		end = yearstr.find("��");
		//������̒����玞�𔲂��o��
		month = yearstr.substr(begin, end - begin);
		//���̎n�_��ݒ肷��
		begin = end + 1;
		//�������"��"�̈ʒu��T��
		end = yearstr.find("��");
		//������̒����番�𔲂��o��
		day = yearstr.substr(begin, end - begin);
		//�����񂩂�ϐ��ɕϊ�����
		years = std::stoi(year) * 10000 + std::stoi(month) * 100 + std::stoi(day);
		//�ϐ���ԋp����
		return years;
	}

	/*�T�v:�t�@�C������擾�����������picojson�ň������߂�object�ɕϊ�����֐�
	����:std::string uid:�t�@�C���̖��O
	�߂�l:picojson::object obj:picojson�̃I�u�W�F�N�g
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	picojson::object GetPicoObj(std::string uid) {
		picojson::object obj;    //�ԋp�p��picojson�̃I�u�W�F�N�g
		picojson::value val;     //�p�[�X����JSON���i�[���邽�߂�value
		std::stringstream ss;    //�t�@�C������f�[�^���擾���邽�߂̃X�g���[��
		//�t�@�C�����J��
		std::ifstream ifs(uid, std::ios_base::binary);
		//�X�g���[���Ƀf�[�^�𗬂�����
		ss << ifs.rdbuf();
		//picojson�֗�������Ńp�[�X����
		ss >> val;
		//JSON��������悤�ɃI�u�W�F�N�g�^�ɕϊ�����
		obj = val.get<picojson::object>();
		//�t�@�C���X�g���[�������
		ifs.close();
		//�ϊ������I�u�W�F�N�g��ԋp����
		return obj;
	}

	/*�T�v:�쐬����JSON�I�u�W�F�N�g���t�@�C���ɕۑ����邽�߂̊֐�
	����:picojson::object obj:�쐬����JSON�I�u�W�F�N�g
	�߂�l:�Ȃ�
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	void OutPutJSON(picojson::object obj, std::string uid) {
		std::string out;    //�t�@�C���Ɋi�[���邽�߂̕�����
		//�������ݗp�̃X�g���[�����J��
		std::ofstream ofs(uid);
		//JSON�I�u�W�F�N�g��蕶����ɕϊ�����
		out = picojson::value(obj).serialize();
		//�t�@�C���ɕ�����������o��
		ofs << out;
		//�t�@�C���X�g���[�������
		ofs.close();
		return;
	}

	/*�T�v:�t�@�C�����̔N���������݂̔N�����ɍX�V���邽�߂̊֐�
	����:std::string uid:�t�@�C���̖��O
	�߂�l:�Ȃ�
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	void UpdateFileYear(std::string uid) {
		picojson::object obj;    //JSON���������߂̃I�u�W�F�N�g
		//�Ώۂ̃t�@�C������JSON�̃I�u�W�F�N�g���擾����
		obj = GetPicoObj(uid);
		//�擾����JSON�̔N����������������
		obj[YEAR_LABEL] = (picojson::value)(YearStr());
		//����������JSON���t�@�C���֏����o��
		OutPutJSON(obj, uid);
		return;
	}

	/*�T�v:�t�@�C���ɓ��t��ǉ�����֐�
	����:std::string uid:�t�@�C���̖��O
	�߂�l:�Ȃ�
	�쐬��:2017.10.26
	�쐬��:K.Asada*/
	void UpdateFileDate(std::string uid) {
		picojson::object obj1;    //JSON���������߂̃I�u�W�F�N�g
		picojson::object* obj2;    //JSON���������߂̃I�u�W�F�N�g
		picojson::array timeary;  //JSON�ɔz����i�[���邽�߂̔z��
		std::string key = "";     //JSON���珑�������Ώۂ𔲂��o�����߂̃L�[
		std::string timestr = ""; //���������̂��߂̓����������߂�������
		//�t�@�C������JSON�̃I�u�W�F�N�g���擾����
		obj1 = GetPicoObj(uid);
		//���������Ώۂ��擾���邽�߂̃L�[���擾����
		key = YearStr();
		//���������邽�߂̓��������擾����
		timestr = TimeStr();
		//�I�u�W�F�N�g������ٓ��������I�u�W�F�N�g���擾����
		obj2 = &obj1[ENTER_LABEL].get<picojson::object>();
		//�Ώۂ̉ӏ��ɂ��łɒl�����邩�𔻒肷��
		if ((*obj2)[key].is<picojson::array>()) {
			//���ɔz�񂪂���΂��̔z����擾����
			timeary = (*obj2)[key].get<picojson::array>();
		}
		//�z��Ɍ��݂̓�������ǉ�����
		timeary.push_back(picojson::value(timestr));
		//�z�����ٓ��̎q�Ƃ��ĘA������
		(*obj2)[key] = picojson::value(timeary);
		//JSON���t�@�C���ɏ����o��
		OutPutJSON(obj1, uid);
	}
};
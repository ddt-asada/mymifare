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
		//���[�U�[�̑������擾����
		uid = GetElem(data[ELEM_INDEX][4], ELEM_NAME1, ELEM_NAME2, ELEM_NAME3, ELEM_NAME4);
		//�댯�l�����ǂ����𔻒肷��
		if (uid == ELEM_NAME2) {
			//�댯�l�����邱�Ƃ�\������
			System::Windows::Forms::MessageBox::Show(Constants->CAUNTION_MESSAGE);
			//�댯�l���ł���G���[�𓊂���
			throw gcnew System::Exception(Constants->CAUNTION_MESSAGE);
		}
		//���[�U�[ID���i�[���ꂽ�u���b�N���w�肵�ă��[�U�[ID���擾����
		uid = GetData(data, UID_INDEX);
		//�擾�������[�U�[���Ńt�@�C�����J��
		std::ifstream ifs(uid);
		//���[�U�[ID���t�@�C�����Ƃ����t�@�C�����J���Ȃ��Ƃ��̓��[�U�[�����݂��Ă��Ȃ��Ƃ��ė�O�𓊂���
		if (!ifs.is_open()) {
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
			//�p�X���[�h���Ⴄ�|��\������
			System::Windows::Forms::MessageBox::Show("�p�X���[�h���Ⴂ�܂�");
			//�p�X���Ⴄ�|�̗�O�𓊂���
			throw gcnew System::Exception(Constants->PASS_NOT_FOUND_ERROR);
		}
		//�����܂ŗ����琬�������Ƃ���true��ԋp
		return true;
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
			std::ifstream ifs(uid);
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

	/*�T�v:�J�[�h�֑��M����f�[�^�̑g�ݗ��āA�R�}���h�̍쐬���s���֐�
	����:string setdata:���M����f�[�^
	�߂�l:unsigned char:�f�[�^�𑗐M���邽�߂̃R�}���h
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	std::vector<SENDCOMM> ReadySetData(std::vector<std::vector<unsigned char>> data, int blockindex) {
		try {
			std::vector<SENDCOMM> sendcomm;        //�g�ݗ��Ă��R�}���h���i�[���邽�߂̍\����
			int dataindex = 0;                     //�f�[�^�����o�����߂̃C���f�b�N�X
			SENDCOMM certify = AUTHENTICATE;       //�u���b�N�F�؃R�}���h�̃R�s�[
			SENDCOMM sendcard = SENDCARD;          //�f�[�^���M�R�}���h�̃R�s�[
            //�R�}���h������������
			sendcomm = InitCommand(blockindex);
			//�R�}���h��g�ݗ��ĂĂ���
			for (; blockindex < END_BLOCK; blockindex++) {
				//�Ώۂ̃u���b�N��4�̔{���]1�̎��͓ǂݔ�΂�
				if (blockindex % 4 != 3) {
					//16�o�C�g���̑��M�R�}���h��g�ݗ��ĂĂ���
					for (int i = 0; i < 16; i++) {
						sendcard.sendCommand[5 + i] = data[dataindex][i];
					}
					//�f�[�^�𑗐M����Ώۂ̃u���b�N��ݒ肷��
					sendcard.sendCommand[3] = blockindex;
					//�g�ݗ��Ă��R�}���h���i�[����
					sendcomm.push_back(sendcard);
					//���̃u���b�N�̃R�}���h��g�ݗ��ďI�����玟�̃u���b�N�ֈړ�����
					dataindex++;
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

	/*�T�v:�J�[�h�փf�[�^�𑗐M���邽�߂̊֐�
	����:SCARDCONTEXT hContext:�擾�������\�[�X�}�l�[�W��
	    :SCARDHANDLE hCard:�擾�����J�[�h
		:string uid:�擾�����J�[�h�̃��[�U�[ID
	�߂�l:�Ȃ�
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	void SetCardData(std::string pass) {
		try {
			ConnectCard* con = new ConnectCard();    //�J�[�h�ʐM�N���X���C���X�^���X��
			std::vector<SENDCOMM> senddata;    //���M�R�}���h���i�[���邽�߂̍\����
			std::vector<std::vector<unsigned char>> recvdata;    //��M�f�[�^���i�[���邽�߂̔z��
			std::string uid;
			//��M�R�}���h��g�ݗ��Ă�֐����Ăяo��
			senddata = ReadyGetData(BEGIN_BLOCK);
			//��M�R�}���h���J�[�h�֑��M���ăf�[�^���󂯎��
			recvdata = con->LinkCard(senddata);
			//���[�U�[�����m�F����֐����Ăяo��
			uid = CheckUser(recvdata, pass);
			//�Ώۂ̃��[�U�[�����ْ����𔻒肷��
			if (!CheckLeave(recvdata)) {
				System::Windows::Forms::MessageBox::Show("���̃��[�U�[�͓��ق��Ă��܂���B");
				throw gcnew System::Exception("���̃��[�U�͓��ق��Ă��܂���B");
			}
			//�ފٓ����L�^����
			recvdata = SetTimes(recvdata, LEAVE_1_INDEX, END_INDEX);
			//���M�R�}���h���쐬����֐����Ăяo��
			senddata = ReadySetData(recvdata, BEGIN_BLOCK);
			//���M�R�}���h�̏I���ɃR�}���h�̏I���������R�}���h���i�[����
			senddata.push_back(ENDCOMMAND);
			//�J�[�h�փR�}���h�𑗐M����֐����Ăяo��
			con->LinkCard(senddata);
			return;
		}
		catch (System::Exception^ e) {
			System::Console::WriteLine(e);
			throw e;
		}
	}

	/*�T�v:�J�[�h�֐V�K�Ńf�[�^�𑗐M���邽�߂̊֐�
	����:SCARDCONTEXT hContext:�擾�������\�[�X�}�l�[�W��
	:SCARDHANDLE hCard:�擾�����J�[�h
	:string uid:�擾�����J�[�h�̃��[�U�[ID
	�߂�l:�Ȃ�
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	void SetNewCardData(std::string uid) {
		try {
			ConnectCard* con = new ConnectCard();    //�J�[�h�ʐM�N���X���C���X�^���X��
			std::vector<SENDCOMM> senddata;    //���M�R�}���h���i�[���邽�߂̍\����
			//�f�[�^���M�p�̃R�}���h��g�ݗ��Ă�
			senddata = ReadySetData(uid, BEGIN_BLOCK);
			//���M�R�}���h�̏I���ɃR�}���h�̏I���������R�}���h���i�[����
			senddata.push_back(ENDCOMMAND);
			//�J�[�h�փR�}���h�𑗐M����֐����Ăяo��
			con->LinkCard(senddata);
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
	�쐬��:K.Asada*/
	std::vector<std::vector<unsigned char>> GetCardData(std::string pass) {
		try {
			std::vector<SENDCOMM>sendcomm;        //��M�R�}���h���i�[���邽�߂̔z��
			std::vector<SENDCOMM>copycomm;        //���M�R�}���h���i�[���邽�߂̔z��
			std::vector<std::vector<unsigned char>> recvdata;    //��M�f�[�^���i�[���邽�߂̔z��
			std::string uid;                                     //���[�U�[ID���i�[���邽�߂̔z��
			ConnectCard* con = new ConnectCard();                //�J�[�h�Ƃ̒ʐM���s���N���X���C���X�^���X��
			//��M�R�}���h��g�ݗ��Ă�֐����Ăяo��
			sendcomm = ReadyGetData(BEGIN_BLOCK);
			//��M�R�}���h���J�[�h�֑��M���ăf�[�^���󂯎��
			recvdata = con->LinkCard(sendcomm);
			//���[�U�[�����m�F����֐����Ăяo��
			uid = CheckUser(recvdata, pass);
			//���̃��[�U�[�����ُ�ԂłȂ������肷��
			if (!CheckEnter(recvdata)) {
				System::Windows::Forms::MessageBox::Show("���̃��[�U�[�͑ފق��Ă��܂���B");
				throw gcnew System::Exception("���̃��[�U�͑ފق��Ă��܂���B");
			}
			//���َ��Ԃ��擾����֐����Ăяo��
			recvdata = SetTimes(recvdata, TIMES_1_INDEX, LEAVE_1_INDEX);
			//���َ��Ԃ��J�[�h�ɋL�^�����邽�߂̃R�}���h���쐬����
			copycomm = ReadySetData(recvdata, BEGIN_BLOCK);
			//�R�}���h��A������
			sendcomm.insert(sendcomm.begin(), copycomm.begin(), copycomm.end() - 1);
			//�J�[�h�փf�[�^�𑗐M����
			recvdata = con->LinkCard(sendcomm);
			return recvdata;
		}
		catch (System::Exception^ e) {
			System::Console::WriteLine(e);
			throw e;
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

	/*�T�v:���ފٓ��̎擾�y�єN���̊m�F���s���֐�
	����:string uid:�`�F�b�N�Ώۂ̃��[�U��ID
	�߂�l:�Ȃ�
	�쐬���F2017.10.11
	�쐬��:K.Asada*/
	std::vector<std::vector<unsigned char>> SetTimes(std::vector<std::vector<unsigned char>> data, int index, int endindex) {
		ITOC times;            //�擾�����������𕪂ɕϊ��������̂��i�[����
		//�N�����`�F�b�N����֐����Ăяo���A�N�������ݔN���ƈقȂ��Ă����珑��������
		data = CheckYears(data);
		//�֐���茻�ݓ��������擾����
		times.num = GetAdmissionTime();
		//�Ώۂ̃f�[�^�̑������s��
		for (int i = 2; index < endindex; i++) {
			//�f�[�^�����݂��Ȃ��ꏊ������Έڍs
			if (data[index][i] == '\0') {
				//���8�r�b�g���i�[����
				data[index][i] = times.bytes[0];
				//����8�r�b�g���i�[����
				data[index][i + 1] = times.bytes[1];
				//�������I������
				break;
			}
			//�u���b�N�I�[�܂ő������Ă����玟�̃u���b�N�ֈڍs����
			if (i == 15) {
				//���̃u���b�N�ֈڍs����
				index++;
				//�C���f�b�N�X���ŏ��ɖ߂�
				i = -1;
			}
		}
		return data;
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
	std::vector<std::vector<unsigned char>> CheckYears(std::vector<std::vector<unsigned char>> data) {
		time_t now = time(NULL);          //���ݎ������擾���邽��
		struct tm *pnow = localtime(&now);//���ݎ������擾���邽�߂̍\���̂�錾
		ITOC years;                       //�擾�������ݎ������i�[���邽�߂̕ϐ�
		//���ݔN�����擾����
		years.num = ((pnow->tm_year + 1900) * 12 + pnow->tm_mon + 1);
		//�N�����i�[����Ă���ꏊ���`�F�b�N���Ď擾�����N�����ƈقȂ�Ώ���������
		if (data[YEAR_INDEX][0] != years.bytes[0] || data[YEAR_INDEX][1] != years.bytes[1]) {
			//����8�r�b�g������������
			data[YEAR_INDEX][0] = years.bytes[0];
			//���8�r�b�g������������
			data[YEAR_INDEX][1] = years.bytes[1];
		}
		return data;
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

	/*�T�v:�J�[�h�Ɋi�[���ꂽ���������𕶎���ɕϊ�����֐�
	����:std::vector<std::vcotr<unsigned char>> data:�J�[�h�f�[�^
	�߂�l:std::vector<string> times:�������𕶎���ɕϊ������z��
	�쐬��:2017.10.16
	�쐬��:K.Asada*/
 std::vector<std::string> ConvTimes(std::vector<std::vector<unsigned char>> data, int index,int endindex) {
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

		 /*�T�v:���[�U�[�����ُ�Ԃ��ǂ������`�F�b�N���邽�߂̊֐�
		 ����:std::vector<std::vector<unsigned char>> data:�J�[�h���擾�����f�[�^
		 �߂�l:bool judge:���茋��
		 �쐬��:2017.10.19
		 �쐬��:K.Asada*/
		 bool CheckEnter(std::vector<std::vector<unsigned char>> data) {
			 std::vector<std::string> entertimes;    //���َ��Ԃ��i�[���镶����
			 std::vector<std::string> leavetimes;    //�ފَ��Ԃ��i�[���镶����
			 bool judge = true;                      //���茋�ʂ��i�[����
			 //���َ��Ԃ��擾����
			 entertimes = ConvTimes(data, TIMES_1_INDEX, LEAVE_1_INDEX);
			 //�ފَ��Ԃ��擾����
			 leavetimes = ConvTimes(data, LEAVE_1_INDEX, END_INDEX);
			 //���ُ�Ԃ��ǂ����̔�����s��
			 if (entertimes.size() > leavetimes.size()){
				 //���ُ�Ԃł��锻���Ԃ�
				 judge = false;
			 }
			 return judge;
		}

		 /*�T�v:���[�U�[�����ُ�Ԃ��ǂ������`�F�b�N���邽�߂̊֐�
		 ����:std::vector<std::vector<unsigned char>> data:�J�[�h���擾�����f�[�^
		 �߂�l:bool judge:���茋��
		 �쐬��:2017.10.19
		 �쐬��:K.Asada*/
		 bool CheckLeave(std::vector<std::vector<unsigned char>> data) {
			 std::vector<std::string> entertimes;    //���َ��Ԃ��i�[���镶����
			 std::vector<std::string> leavetimes;    //�ފَ��Ԃ��i�[���镶����
			 bool judge = true;                      //���茋�ʂ��i�[����
             //���َ��Ԃ��擾����
			 entertimes = ConvTimes(data, TIMES_1_INDEX, LEAVE_1_INDEX);
			 //�ފَ��Ԃ��擾����
			 leavetimes = ConvTimes(data, LEAVE_1_INDEX, END_INDEX);
			 //���ُ�Ԃ��ǂ����̔�����s��
			 if (entertimes.size() <= leavetimes.size()) {
				 //���ُ�Ԃł��锻���Ԃ�
				 judge = false;
			 }
			 return judge;
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
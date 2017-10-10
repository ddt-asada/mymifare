#pragma once

#include <windows.h>
#include <winscard.h>
#include <stdio.h>
#include <assert.h>
#include "CONSTANTS.h"

#define PCSC_TRANS_BUFF_LEN	(262)
#define PCSC_RECV_BUFF_LEN	(262)

public class ConnectCard {
public:
	ConnectCard() {

	}

	SCARD_IO_REQUEST *CardProtocol2PCI(DWORD dwProtocol)
	{
		if (dwProtocol == SCARD_PROTOCOL_T0) {
			return (SCARD_IO_REQUEST *)SCARD_PCI_T0;
		}
		else if (dwProtocol == SCARD_PROTOCOL_T1) {
			return (SCARD_IO_REQUEST *)SCARD_PCI_T1;
		}
		else if (dwProtocol == SCARD_PROTOCOL_RAW) {
			return (SCARD_IO_REQUEST *)SCARD_PCI_RAW;
		}
		else if (dwProtocol == SCARD_PROTOCOL_UNDEFINED) {
			assert(false);
			return NULL;
		}

		return (SCARD_IO_REQUEST *)SCARD_PCI_T1;
	}

	CONSTANTS* constants;    //�萔�N���X���C���X�^���X��

	/*�T�v�F�@��Ƃ̒ʐM���s�����߂̃��\�[�X�}�l�[�W�����m�ۂ��邽�߂̊֐�
	�����F�Ȃ�
	�߂�l�Funsigned long hContext�m�ۂ������\�[�X�}�l�[�W��
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	unsigned long EstablishContext() {
		SCARDCONTEXT hContext = 0;        //�m�ۂ������\�[�X�}�l�[�W���̃A�h���X
		unsigned long lResult;                     //���\�[�X�}�l�[�W�����m�ۂ����ۂ̌��ʂ��i�[���邽�߂̕ϐ�
		//���\�[�X�}�l�[�W�����m�ۂ��A���̌��ʂ��擾����
		lResult = ::SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hContext);
		//�����m�ۂɎ��s���Ă������O�𓊂���
		if (lResult != SCARD_S_SUCCESS) {
			//�G���[���e�ɂ�蕪��
			if (lResult == SCARD_E_NO_SERVICE) {
				//���\�[�X�}�l�[�W���̊m�ۂɎ��s�������̃G���[�𓊂���
		//		throw gcnew System::Exception(NO_SERVICE_ERROR);
			}
			//����ȊO�̎��͂��̑��G���[
			else {
				//���̑��̃G���[�Ƃ��ė�O�𓊂���
	//			throw gcnew System::Exception(ESTABLISH_ERROR);
			}
		}
		//�m�ۂ������\�[�X�}�l�[�W���̃A�h���X��Ԃ�
		return hContext;
	}

	/*�T�v�F�m�ۂ������\�[�X�}�l�[�W���̖��O���ړI�̃J�[�h���[�_�̖��O�ƈ�v���Ă��邩�𒲂ׂ邽�߂̊֐�
	�����Funsigned long Context�F�m�ۂ������\�[�X�}�l�[�W��
	�߂�l�G�Ȃ�
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	void CheckReaderName(unsigned long Context) {
		char* ReaderName = NULL;                      //�擾�������[�_�̖��O���i�[���邽�߂̕�����
		unsigned long dwAutoAllocate = SCARD_AUTOALLOCATE;    //�A���P�[�^
		unsigned long lResult;                                 //���O�𐳂����擾�ł������̔�����i�[���邽�߂̕�����
		//�m�ۂ������\�[�X�}�l�[�W���̃��[�_�̖��O���ׂ�
		lResult = ::SCardListReaders(Context, NULL, (WCHAR*)&ReaderName, &dwAutoAllocate);
		//���s�������O�𓊂���
		if (lResult != SCARD_S_SUCCESS) {
			//�ړI�̃��[�_�[�ƈ���Ă����炻�̎|���O�Ƃ��ē�����
			if (lResult == SCARD_E_NO_READERS_AVAILABLE) {
				//���[�_�[���Ⴄ�|�̗�O�𓊂���
			//	throw gcnew System::Exception(NO_READERS_ERROR);
			}//����ȊO�̃G���[�͕ʂ̃��b�Z�[�W�𓊂���
			else {
				//���炩�̃G���[���������ď����𒆒f�����|���O�Ƃ��ē�����
		//		throw gcnew System::Exception(ERROR);
			}
		}
		//�ړI�̃��[�_�[�̖��O�ƈ���Ă����炻�̎|���O�Ƃ��ē`����
		if (ReaderName != constants->PASORI_NAME) {
			//���[�_�[���Ⴄ�|���O�Ƃ��ē�����
	//		throw gcnew System::Exception(NO_READERS_ERROR);
		}
		//�J�[�h�A���[�_�[�Ƃ̐ڑ����I������
		EndConnect(Context);
		return;
	}

	/*�T�v�F�J�[�h�փf�[�^����M�Ȃǂ̃R�}���h�𑗐M���邽�߂̊֐�
	�����Funsigned long�F���[�_�[�ւ̃��\�[�X�}�l�[�W��
		�Funsigned long�F�J�[�h�ւ̃n���h��
		�FSENDCOMM SendComm�F�J�[�h�֑��M����R�}���h
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	unsigned char** Transmit(unsigned long hContext, unsigned long hCard, CONSTANTS::SENDCOMM SendComm[],unsigned long ActiveProtocol) {
		unsigned char RecvBuf[PCSC_RECV_BUFF_LEN] = { '\0' };
		unsigned char* RetBuf[16] = { '\0' };
		unsigned long ResponseSize = 0;
		unsigned long lResult;
		//�S�ẴR�}���h�𑗐M����܂ŌJ��Ԃ�
		for (int i = 0; SendComm[i].sendLength > -1; i++) {
			//��M�̍ő�T�C�Y���擾����
			ResponseSize = sizeof(RecvBuf);
			//�R�}���h�𑗐M���āA���ʂƃ��X�|���X�ւ̃|�C���^���擾����
			lResult = ::SCardTransmit(hCard, CardProtocol2PCI(ActiveProtocol), SendComm[i].sendCommand, SendComm[i].sendLength, NULL, RecvBuf, &ResponseSize);
			//�R�}���h�̑��M�Ɏ��s������G���[�𓊂���i�����ł̓R�}���h�����ꂽ���ǂ����̂ݔ���j
			if (lResult != SCARD_S_SUCCESS) {
				//��O�𓊂���
				throw gcnew System::Exception("Error");
				//���[�_�[�Ƃ̒ʐM�A�J�[�h�Ƃ̒ʐM���I������
				EndConnect(hContext, hCard);
			}
			//�󂯎�������ׂẴ��X�|���X���i�[����i���2�����͑��M���ۂ̔���Ȃ̂Ŋi�[���Ȃ��̂��߁j
			for (int j = 0; j < ResponseSize - 2; j++) {
				//�󂯎�������X�|���X��ԋp�p�̕�����Ɋi�[����
				RetBuf[i][j] = RecvBuf[j];
			}
		}
		//�쐬�����������ԋp����
		return RetBuf;
	}

	/*�T�v:�J�[�h���[�_�̏�Ԃ��擾���A�J�[�h���u���ꂽ�Ƃ��ɃJ�[�h��ǂݍ��ފ֐�
	����:unsigned long hContext:�m�ۂ������\�[�X�}�l�[�W���̃A�h���X
	    :unsigned long *hCard:�J�[�h�ւ̃|�C���^
	�߂�l:unsigned long ActiveProtocol:�J�ʂ����v���g�R��
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	unsigned long CardConnect(unsigned long hContext, unsigned long *hCard) {
		unsigned long lResult = 0;        //�ڑ����ʂ��i�[���邽�߂̕ϐ�
		SCARD_READERSTATE readerstate;    //���[�_�̏�Ԃ��i�[���邽�߂̍\����
		unsigned long ActiveProtocol = 0; //�v���g�R��
		//���[�_�[�̏�Ԃ��ω��i�J�[�h���������ꂽ�Ƃ��Ɂj���̏�Ԃ�ǂݎ��֐�
		lResult = ::SCardGetStatusChange(hContext, 0, &readerstate, 1);
		//�����R�}���h�̑��M�Ɏ��s�������O�𓊂���
		if (lResult != SCARD_S_SUCCESS) {
			//�G���[���e�ɂ�蕪��
			if (lResult == SCARD_E_NO_READERS_AVAILABLE) {
				//�J�[�h���[�_���ڑ�����Ă��Ȃ��|�̗�O�𓊂���
				//throw gcnew System::Exception("�J�[�h���[�_�[���ڑ�����Ă��܂���");
				//�ڑ����I������
				EndConnect(hContext, *hCard);
			}
		}
		//�J�[�h�Ƃ̐ڑ����J�n����
		lResult = ::SCardConnect(hContext, (LPWSTR)constants->PASORI_NAME, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, (LPSCARDHANDLE)&hCard, &ActiveProtocol);
		//�ڑ����ʂ����s�Ȃ��O�𓊂���
		if (lResult != SCARD_S_SUCCESS) {
			//�J�[�h���Ȃ����Ƃ̃G���[�Ȃ�
			if (lResult == SCARD_W_REMOVED_CARD) {
				//�J�[�h���Ȃ��|��`����G���[�𓊂���
				throw gcnew System::Exception("�J�[�h������܂���");
			}//����ȊO�̃G���[�̎��͕ʂ̗�O��`����
			else {
				throw gcnew System::Exception("ERROR");
			}
			//�ڑ����I������
			EndConnect(hContext, *hCard);
		}
		return ActiveProtocol;
	}

	/*�T�v:���[�_�[�Ɛڑ����A�J�[�h��t�҂���Ԃɂ���֐�
	����:�Ȃ�
	�߂�l:__int64:Context:�m�ۂ������\�[�X�}�l�[�W���̃A�h���X
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	unsigned long WaitingCard() {
		unsigned long Context = 0;    //�m�ۂ������\�[�X�}�l�[�W���̃A�h���X���i�[����ϐ�
		//���\�[�X�}�l�[�W�����m�ۂ���
		Context = EstablishContext();
		//���[�_�[�̖��O���ƍ����A�ړI�̂��̂Ɛڑ��ł��Ă��邩���m�F����
		CheckReaderName(Context);
		//�m�ۂ����\�[�X�}�l�[�W����ԋp����
		return Context;
	}

	/*�T�v:�J�[�h����у��[�_�[�Ƃ̐ڑ����I������֐�
	����:unsigned long hContext:�m�ۂ��Ă������\�[�X�}�l�[�W��
	:unsigned long hCard:�ڑ����Ă����J�[�h
	�߂�l:�Ȃ�
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	void EndConnect(unsigned long hContext, unsigned long hCard) {
		//�J�[�h�Ƃ̐ڑ����I������
		::SCardDisconnect(hCard, SCARD_LEAVE_CARD);
		//���[�_�[���������
		::SCardFreeMemory(hContext, constants->PASORI_NAME);
		//���\�[�X�}�l�[�W�����������
		::SCardReleaseContext(hContext);
		return;
	}

	/*�T�v:���[�_�[�Ƃ̐ڑ����I������֐�
	����:unsigned long hContext:�m�ۂ��Ă������\�[�X�}�l�[�W��
	�߂�l:�Ȃ�
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	void EndConnect(unsigned long hContext) {
		//���[�_�[���������
		::SCardFreeMemory(hContext, constants->PASORI_NAME);
		//���\�[�X�}�l�[�W�����������
		::SCardReleaseContext(hContext);
		return;
	}
};
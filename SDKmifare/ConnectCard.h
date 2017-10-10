#pragma once

#include <windows.h>
#include <winscard.h>
#include <stdio.h>
#include <assert.h>

#define PCSC_TRANS_BUFF_LEN	(262)
#define PCSC_RECV_BUFF_LEN	(262)

typedef struct {
	int           sendLength;
	unsigned char bCommand[PCSC_TRANS_BUFF_LEN];
} SENDCOMM;

public class ConnectCard {
	ConnectCard() {

	}

	/*�T�v�F�@��Ƃ̒ʐM���s�����߂̃��\�[�X�}�l�[�W�����m�ۂ��邽�߂̊֐�
	�����F�Ȃ�
	�߂�l�Funsigned long hContext�m�ۂ������\�[�X�}�l�[�W��
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	unsigned long EstablishContext() {
		SCARDCONTEXT hContext = 0;        //�m�ۂ������\�[�X�}�l�[�W���̃A�h���X
		LONG lResult;                     //���\�[�X�}�l�[�W�����m�ۂ����ۂ̌��ʂ��i�[���邽�߂̕ϐ�
		//���\�[�X�}�l�[�W�����m�ۂ��A���̌��ʂ��擾����
		lResult = ::SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hContext);
		//�����m�ۂɎ��s���Ă������O�𓊂���
		if (lResult != SCARD_S_SUCCESS) {
			//�G���[���e�ɂ�蕪��
			if (lResult == SCARD_E_NO_SERVICE) {
				//���\�[�X�}�l�[�W���̊m�ۂɎ��s�������̃G���[�𓊂���
				throw gcnew System::Exception(NO_SERVICE_ERROR);
			}
			//����ȊO�̎��͂��̑��G���[
			else {
				//���̑��̃G���[�Ƃ��ė�O�𓊂���
				throw gcnew System::Exception(ESTABLISH_ERROR);
			}
		}
		//�m�ۂ������\�[�X�}�l�[�W���̃A�h���X��Ԃ�
		return hContext;
	}

	/*�T�v�F�m�ۂ������\�[�X�}�l�[�W���̖��O���ړI�̃J�[�h���[�_�̖��O�ƈ�v���Ă��邩�𒲂ׂ邽�߂̊֐�
	�����FSCARDCONTEXT Context�F�m�ۂ������\�[�X�}�l�[�W��
	�߂�l�G�Ȃ�
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	void CheckReaderName(unsigned long Context) {
		LRSTR ReaderName = NULL;                      //�擾�������[�_�̖��O���i�[���邽�߂̕�����
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //�A���P�[�^
		LONG lResult;                                 //���O�𐳂����擾�ł������̔�����i�[���邽�߂̕�����
		//�m�ۂ������\�[�X�}�l�[�W���̃��[�_�̖��O���ׂ�
		lResult = ::SCardListReaders(Context, NULL, (LRSTR)&ReaderName, &dwAutoAllocate);
		//���s�������O�𓊂���
		if (lResult != SCARD_S_SUCCESS) {
			//�ړI�̃��[�_�[�ƈ���Ă����炻�̎|���O�Ƃ��ē�����
			if (lResult == SCARD_E_NO_READERS_AVAILABLE) {
				//���[�_�[���Ⴄ�|�̗�O�𓊂���
				throw gcnew System::Exception(NO_READERS_ERROR);
			}//����ȊO�̃G���[�͕ʂ̃��b�Z�[�W�𓊂���
			else {
				//���炩�̃G���[���������ď����𒆒f�����|���O�Ƃ��ē�����
				throw gcnew System::Exception(ERROR);
			}
		}
		//�ړI�̃��[�_�[�̖��O�ƈ���Ă����炻�̎|���O�Ƃ��ē`����
		if (_tcsnmp(pszExpectesReaderName, lpszReaderName, _tcslen(pszExceptedReaderName)) != 0) {
			//���[�_�[���Ⴄ�|���O�Ƃ��ē�����
			throw gcnew System::Exception(NO_READERS_ERROR);
		}
		//�J�[�h�A���[�_�[�Ƃ̐ڑ����I������
		EndConnect(Context, Card);
		return;
	}

	/*�T�v�F�J�[�h�փf�[�^����M�Ȃǂ̃R�}���h�𑗐M���邽�߂̊֐�
	�����Funsigned long�F���[�_�[�ւ̃��\�[�X�}�l�[�W��
		�Funsigned long�F�J�[�h�ւ̃n���h��
		�FSENDCOMM SendComm�F�J�[�h�֑��M����R�}���h
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	unsigned char Transmit(unsigned long hContext, unsigned long hCard, SENDCOMM SendComm) {
		BYTE RecvBuf[3 + BLOCK_COUNT][PCSC_RECV_BUFF_LEN] = { '\0' };
		DWORD ResponseSize = 0;
		//�S�ẴR�}���h�𑗐M����܂ŌJ��Ԃ�
		for (int i = 0; SendComm[i].sendLength > -1; i++) {
			//��M�̍ő�T�C�Y���擾����
			ResponseSize = sizeof(RecvBuf);
			//�R�}���h�𑗐M���āA���ʂƃ��X�|���X�ւ̃|�C���^���擾����
			lResult = ::SCardTransmit(hCard, CatdProtocol2PCI(dwActiveProtocol), SendComm[i].bCommand, SendComm[i].sendLength, NULL, RecvBuf, &ResponseSize);
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
				RecvBuf[i][j] = RecvBuf[j];
			}
		}
		//�쐬�����������ԋp����
		return RecvBuf;
	}
};
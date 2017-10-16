#pragma once

#include <windows.h>
#include <winscard.h>
#include <stdio.h>
#include <assert.h>
#include "CONSTANTS.h"

#pragma comment (lib, "winscard.lib")

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

	/*�T�v�F�@��Ƃ̒ʐM���s�����߂̃��\�[�X�}�l�[�W�����m�ۂ��邽�߂̊֐�
	�����F�Ȃ�222222222222
	�߂�l�FSCARDCONTEXT hContext�m�ۂ������\�[�X�}�l�[�W��
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	SCARDCONTEXT EstablishContext() {
		SCARDCONTEXT hContext = 0;        //�m�ۂ������\�[�X�}�l�[�W���̃A�h���X
		LONG lResult;                     //���\�[�X�}�l�[�W�����m�ۂ����ۂ̌��ʂ��i�[���邽�߂̕ϐ�
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
	�����FSCARDCONTEXT Context�F�m�ۂ������\�[�X�}�l�[�W��
	�߂�l�G�Ȃ�
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	void CheckReaderName(SCARDCONTEXT Context) {
//		std::cout >> constants->PASORI_NAME.c_str();
		LPTSTR ReaderName = NULL;                      //�擾�������[�_�̖��O���i�[���邽�߂̕�����
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //�A���P�[�^
		LONG lResult;                                 //���O�𐳂����擾�ł������̔�����i�[���邽�߂̕�����
		//�m�ۂ������\�[�X�}�l�[�W���̃��[�_�̖��O���ׂ�
		lResult = ::SCardListReaders(Context, NULL, (LPTSTR)&ReaderName, &dwAutoAllocate);
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
//		if (ReaderName != constants->PASORI_NAME) {
			//���[�_�[���Ⴄ�|���O�Ƃ��ē�����
		//	throw gcnew System::Exception(NO_READERS_ERROR);
	//		EndConnect(Context);
//		}
		//�J�[�h�A���[�_�[�Ƃ̐ڑ����I������
		return;
	}

	/*�T�v�F�J�[�h�փf�[�^����M�Ȃǂ̃R�}���h�𑗐M���邽�߂̊֐�
	�����FSCARDCONTEXT�F���[�_�[�ւ̃��\�[�X�}�l�[�W��
		�FSCARDHANDLE�F�J�[�h�ւ̃n���h��
		�FSENDCOMM SendComm�F�J�[�h�֑��M����R�}���h
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
		std::vector<std::vector<unsigned char>> Transmit(std::vector<CONSTANTGROUP::SENDCOMM> SendComm) {
		LONG lResult = 0;        //�ڑ����ʂ��i�[���邽�߂̕ϐ�
		SCARD_READERSTATE readerstate;    //���[�_�̏�Ԃ��i�[���邽�߂̍\����
		SCARDHANDLE card = NULL;
		SCARDCONTEXT hContext = EstablishContext();
		DWORD ActiveProtocol = 0; //�v���g�R��
		LPTSTR ReaderName = NULL;                      //�擾�������[�_�̖��O���i�[���邽�߂̕�����
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //�A���P�[�^
													  //	LONG lResult;                                 //���O�𐳂����擾�ł������̔�����i�[���邽�߂̕�����
													  //�m�ۂ������\�[�X�}�l�[�W���̃��[�_�̖��O���ׂ�
		lResult = ::SCardListReaders(hContext, NULL, (LPTSTR)&ReaderName, &dwAutoAllocate);
		/*		//���[�_�[�̏�Ԃ��ω��i�J�[�h���������ꂽ�Ƃ��Ɂj���̏�Ԃ�ǂݎ��֐�
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
		}*/
		//�J�[�h�Ƃ̐ڑ����J�n����
		lResult = ::SCardConnect(hContext, ReaderName, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &card, &ActiveProtocol);
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
			//		EndConnect(hContext, *hCard);
		}
		unsigned char RecvBuf[PCSC_RECV_BUFF_LEN] = { '\0' };
		std::vector<std::vector<unsigned char>> RetBuf = { {'\0'} };
		unsigned long ResponseSize = 0;
		//unsigned long lResult;
		//�S�ẴR�}���h�𑗐M����܂ŌJ��Ԃ�
		for (int i = 0; SendComm[i].sendLength > -1; i++) {
			//��M�̍ő�T�C�Y���擾����
			ResponseSize = sizeof(RecvBuf);
			//�R�}���h�𑗐M���āA���ʂƃ��X�|���X�ւ̃|�C���^���擾����
			lResult = ::SCardTransmit(card, CardProtocol2PCI(ActiveProtocol), SendComm[i].sendCommand, SendComm[i].sendLength, NULL, RecvBuf, &ResponseSize);
			//�R�}���h�̑��M�Ɏ��s������G���[�𓊂���i�����ł̓R�}���h�����ꂽ���ǂ����̂ݔ���j
			if (lResult != SCARD_S_SUCCESS) {
				//��O�𓊂���
				throw gcnew System::Exception("Error");
				//���[�_�[�Ƃ̒ʐM�A�J�[�h�Ƃ̒ʐM���I������
				EndConnect(hContext, card);
			}
			for (UINT uiRespIdx = 0; uiRespIdx < ResponseSize; uiRespIdx++) {
				_ftprintf_s(stdout, _T("%02X"), RecvBuf[uiRespIdx]);
				if ((uiRespIdx + 1) >= ResponseSize) {
					_ftprintf_s(stdout, _T("\n"));
				}
				else {
					_ftprintf_s(stdout, _T(" "));
				}
			}
			//�󂯎�������ׂẴ��X�|���X���i�[����i���2�����͑��M���ۂ̔���Ȃ̂Ŋi�[���Ȃ��̂��߁j
/*			for (int j = 0; j < ResponseSize - 2; j++) {
				//�󂯎�������X�|���X��ԋp�p�̕�����Ɋi�[����
				RetBuf[i].push_back(RecvBuf[j]);
			}
			_ftprintf_s(stdout, _T("%02X"), RecvBuf[ResponseSize -2]);
			_ftprintf_s(stdout, _T("%02X"), RecvBuf[ResponseSize - 1]);*/
		}
		//�쐬�����������ԋp����
		return RetBuf;
	}

	/*�T�v:�J�[�h���[�_�̏�Ԃ��擾���A�J�[�h���u���ꂽ�Ƃ��ɃJ�[�h��ǂݍ��ފ֐�
	����:SCARDCONTEXT hContext:�m�ۂ������\�[�X�}�l�[�W���̃A�h���X
	    :SCARDHANDLE *hCard:�J�[�h�ւ̃|�C���^
	�߂�l:DWORD ActiveProtocol:�J�ʂ����v���g�R��
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	unsigned long CardConnect(SCARDCONTEXT hContext, SCARDHANDLE hCard) {
		LONG lResult = 0;        //�ڑ����ʂ��i�[���邽�߂̕ϐ�
		SCARD_READERSTATE readerstate;    //���[�_�̏�Ԃ��i�[���邽�߂̍\����
		SCARDHANDLE card = NULL;
		DWORD ActiveProtocol = 0; //�v���g�R��
		LPTSTR ReaderName = NULL;                      //�擾�������[�_�̖��O���i�[���邽�߂̕�����
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //�A���P�[�^
	//	LONG lResult;                                 //���O�𐳂����擾�ł������̔�����i�[���邽�߂̕�����
													  //�m�ۂ������\�[�X�}�l�[�W���̃��[�_�̖��O���ׂ�
		lResult = ::SCardListReaders(hContext, NULL, (LPTSTR)&ReaderName, &dwAutoAllocate);
/*		//���[�_�[�̏�Ԃ��ω��i�J�[�h���������ꂽ�Ƃ��Ɂj���̏�Ԃ�ǂݎ��֐�
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
		}*/
		//�J�[�h�Ƃ̐ڑ����J�n����
		lResult = ::SCardConnect(hContext, ReaderName, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &ActiveProtocol);
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
	//		EndConnect(hContext, *hCard);
		}
		return ActiveProtocol;
	}

	/*�T�v:���[�_�[�Ɛڑ����A�J�[�h��t�҂���Ԃɂ���֐�
	����:�Ȃ�
	�߂�l:SCARDCONTEXT:Context:�m�ۂ������\�[�X�}�l�[�W���̃A�h���X
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	SCARDCONTEXT WaitingCard() {
		SCARDCONTEXT Context = 0;    //�m�ۂ������\�[�X�}�l�[�W���̃A�h���X���i�[����ϐ�
		//���\�[�X�}�l�[�W�����m�ۂ���
		Context = EstablishContext();
		//���[�_�[�̖��O���ƍ����A�ړI�̂��̂Ɛڑ��ł��Ă��邩���m�F����
		CheckReaderName(Context);
		//�m�ۂ����\�[�X�}�l�[�W����ԋp����
		return Context;
	}

	/*�T�v:�J�[�h����у��[�_�[�Ƃ̐ڑ����I������֐�
	����:SCARDCONTEXT hContext:�m�ۂ��Ă������\�[�X�}�l�[�W��
	:SCARDHANDLE hCard:�ڑ����Ă����J�[�h
	�߂�l:�Ȃ�
	�쐬��:2017.10.10
	�쐬��:K.Asada*/
	void EndConnect(SCARDCONTEXT hContext, SCARDHANDLE hCard) {
		//�J�[�h�Ƃ̐ڑ����I������
		::SCardDisconnect(hCard, SCARD_LEAVE_CARD);
		//���[�_�[���������
		::SCardFreeMemory(hContext, CONSTANTGROUP::PASORI_NAME);
		//���\�[�X�}�l�[�W�����������
		::SCardReleaseContext(hContext);
		return;
	}

	/*�T�v:���[�_�[�Ƃ̐ڑ����I������֐�
	����:SCARDCONTEXT hContext:�m�ۂ��Ă������\�[�X�}�l�[�W��
	�߂�l:�Ȃ�
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada*/
	void EndConnect(SCARDCONTEXT hContext) {
		//���[�_�[���������
		::SCardFreeMemory(hContext, CONSTANTGROUP::PASORI_NAME);
		//���\�[�X�}�l�[�W�����������
		::SCardReleaseContext(hContext);
		return;
	}

	/*�T�v:���[�_�[�Ƃ̒ʐM�̓�����ƂȂ�֐�
	����:std::vector<SENDCOMM> sendcomm:���[�_�[�֑��M����R�}���h
	�߂�l:std::vector<std::vector<unsigned char>> recvdata:�J�[�h�����M�����f�[�^
	�쐬��:2017.10.16
	�쐬��:K.Asada*/
};
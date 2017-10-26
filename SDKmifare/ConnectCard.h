#pragma once

#include <windows.h>
#include <winscard.h>
#include <stdio.h>
#include <assert.h>
#include <msclr/gcroot.h>
#include <vector>
#include "CONSTANTS.h"

#pragma comment (lib, "winscard.lib")

#define PCSC_TRANS_BUFF_LEN	(262)
#define PCSC_RECV_BUFF_LEN	(262)

using namespace CONSTANTGROUP;

static LPTSTR PASORI_NAME = _T("Sony FeliCa Port/PaSoRi 3.0 0");

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

	msclr::gcroot<CONSTANTGROUP::ConstantString^> Constants = gcnew CONSTANTGROUP::ConstantString();

	/*�T�v:�|�[�����O���J�n���邽�߂̊֐�
	����:SCARDCONTEXT hContext:�m�ۂ������\�[�X�}�l�[�W���̃A�h���X
	    :SCARDHANDLE hCard:�m�ۂ����J�[�h�̃A�h���X
		:DWORD ActiveProtocol:�m�ۂ����v���g�R��
	�߂�l:�Ȃ�
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	void BeginPolling(SCARDCONTEXT &hContext, SCARDHANDLE &hCard, DWORD &ActiveProtocol) {
		//���\�[�X�}�l�[�W�����m�ۂ���
		Establish(hContext);
		//�|�[�����O���J�n����
		Polling(hContext);
		//�J�[�h�Ɛڑ�����
		CardConnect(hContext, hCard, ActiveProtocol);
		//�|�[�����O���I������
		return;
	}

	/*�T�v�F�@��Ƃ̒ʐM���s�����߂̃��\�[�X�}�l�[�W�����m�ۂ��邽�߂̊֐�
	�����FSCARDCONTEXT &hContext:���\�[�X�}�l�[�W���̊i�[��
	�߂�l�FSCARDCONTEXT hContext�m�ۂ������\�[�X�}�l�[�W��
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada
	�X�V���e:�V�d�l�����ɔ����֐����A������ύX
	�X�V��:2017.10.24
	�X�V��:K.Asada*/
	void Establish(SCARDCONTEXT &hContext) {
		LONG lResult;                     //���\�[�X�}�l�[�W�����m�ۂ����ۂ̌��ʂ��i�[���邽�߂̕ϐ�
		//���\�[�X�}�l�[�W�����m�ۂ��A���̌��ʂ��擾����
		lResult = ::SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hContext);
		//�����m�ۂɎ��s���Ă������O�𓊂���
		if (lResult != SCARD_S_SUCCESS) {
			//�G���[���e�ɂ�蕪��
			if (lResult == SCARD_E_NO_SERVICE) {
				//���\�[�X�}�l�[�W���̊m�ۂɎ��s�������̃G���[�𓊂���
				throw gcnew System::Exception(Constants->NO_SERVICE_ERROR);
			}
			//����ȊO�̎��͂��̑��G���[
			else {
				//���̑��̃G���[�Ƃ��ė�O�𓊂���
				throw gcnew System::Exception(Constants->ERROR_MESSAGE);
			}
		}
		//�m�ۂ������\�[�X�}�l�[�W���̃A�h���X��Ԃ�
		return;
	}

	/*�T�v:�|�[�����O�����s����֐�
	����:SCARDHANDLE &hContext:�J�[�h�̃A�h���X
	�߂�l:�Ȃ�
	�쐬��:2017.10.24
	�쐬��:K.Asada*/
	void Polling(SCARDHANDLE &hContext) {
		LONG lResult = 0;    //�����̌��ʂ��i�[����ϐ�
		SCARD_READERSTATE readerstate;
		//���[�_�[�̃X�e�[�^�X�Ƃ���"Pasori"���w�肷��
		readerstate.szReader = PASORI_NAME;
		//���[�_�[�̏�Ԃ𖢒m�ɂ���i�ǂ�ȕω����E����悤�Ɂj
		readerstate.dwCurrentState = SCARD_STATE_UNAWARE;
		//���[�_�[�̌��݂̏�Ԃ��擾����
		lResult = SCardGetStatusChange(hContext, 0, &readerstate, 1);
		//�J�[�h����������Ă��Ȃ��ꍇ
		if (readerstate.dwEventState & SCARD_STATE_EMPTY) {
			//���[�_�[�̌��݂̏�Ԃ��J�[�h�Ȃ��ɐݒ肷��
			readerstate.dwCurrentState = readerstate.dwEventState;
			//�|�[�����O���J�n���A�J�[�h����������Ȃ���΃G���[
			if (SCardGetStatusChange(hContext, INFINITE, &readerstate, 1) != 0) {
				//�J�[�h����������Ă��Ȃ��|�̃G���[�𓊂���
				throw gcnew System::Exception(Constants->REMOVE_ERROR);
			}
		}
		//����ɃJ�[�h��ǂݎ�ꂽ��߂�
		return;
	}

	/*�T�v�F�J�[�h�փf�[�^����M�Ȃǂ̃R�}���h�𑗐M���邽�߂̊֐�
	�����FSCARDCONTEXT�F���[�_�[�ւ̃��\�[�X�}�l�[�W��
		�FSCARDHANDLE�F�J�[�h�ւ̃n���h��
		�FSENDCOMM SendComm�F�J�[�h�֑��M����R�}���h
	�쐬���F2017.10.10
	�쐬�ҁFK.Asada
	�X�V���e:�V�d�l�����ɔ���������ύX
	�X�V��:2017.10.24
	�X�V��:K.Asada*/
		std::vector<std::vector<unsigned char>> Transmit(SCARDCONTEXT hContext, SCARDHANDLE hCard, DWORD ActiveProtocol, std::vector<CONSTANTGROUP::SENDCOMM> SendComm) {
		LONG lResult = 0;        //�ڑ����ʂ��i�[���邽�߂̕ϐ�
		SCARD_READERSTATE readerstate;    //���[�_�̏�Ԃ��i�[���邽�߂̍\����
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //�A���P�[�^
		unsigned char RecvBuf[PCSC_RECV_BUFF_LEN] = { '\0' };
		std::vector<std::vector<unsigned char>> RetBuf = std::vector<std::vector<unsigned char>>(BLOCK_COUNT, std::vector<unsigned char>(0));
		unsigned long ResponseSize = 0;
		int blockindex = -1;
		//�S�ẴR�}���h�𑗐M����܂ŌJ��Ԃ�
		for (int i = 0; SendComm[i].sendLength > -1; i++) {
			//�Z�L�����e�B�u���b�N�ɃA�N�Z�X���悤�Ƃ��Ă�����G���[�𓊂���
			if (SendComm[i].sendCommand[3] % 4 == 3) {
				//�G���[�𓊂���
				throw gcnew System::Exception("���������t���ł��B");
			}
			//��M�̍ő�T�C�Y���擾����
			ResponseSize = sizeof(RecvBuf);
			//�R�}���h�𑗐M���āA���ʂƃ��X�|���X�ւ̃|�C���^���擾����
			lResult = ::SCardTransmit(hCard, CardProtocol2PCI(ActiveProtocol), SendComm[i].sendCommand, SendComm[i].sendLength, NULL, RecvBuf, &ResponseSize);
			//�R�}���h�̑��M�Ɏ��s������G���[�𓊂���i�����ł̓R�}���h�����ꂽ���ǂ����̂ݔ���j
			if (lResult != SCARD_S_SUCCESS) {
				//��O�𓊂���
				throw gcnew System::Exception(Constants->ERROR_MESSAGE);
				//���[�_�[�Ƃ̒ʐM�A�J�[�h�Ƃ̒ʐM���I������
				EndConnect(hContext, hCard);
			}
			for (UINT RespIdx = 0; RespIdx < ResponseSize; RespIdx++) {
				if (RespIdx == 0 && ResponseSize != 2) {
					RetBuf[++blockindex].push_back(RecvBuf[RespIdx]);
				}
				//��M�f�[�^�̖�����̃f�[�^�͒ʐM���ۂ̔���Ȃ̂œǂݔ�΂�
				else if (RespIdx < ResponseSize - 2) {
					//��M�����f�[�^��ԋp�p�̔z��Ɋi�[����
					RetBuf[blockindex].push_back(RecvBuf[RespIdx]);
				}
				//������̃f�[�^���R���\�[���ɕ\������
				else {
					//�R�}���h�̑��M���ʂ��ǂ��Ȃ�������\������
					_ftprintf_s(stdout, _T("%02X"), RecvBuf[RespIdx]);
				}
			}
		}
		//�쐬�����������ԋp����
		return RetBuf;
	}

	/*�T�v:�J�[�h���[�_�̏�Ԃ��擾���A�J�[�h���u���ꂽ�Ƃ��ɃJ�[�h��ǂݍ��ފ֐�
	����:SCARDCONTEXT hContext:�m�ۂ������\�[�X�}�l�[�W���̃A�h���X
		:SCARDHANDLE hCard:�J�[�h�ւ̃|�C���^
	�߂�l:DWORD ActiveProtocol:�J�ʂ����v���g�R��
	�쐬��:2017.10.10
	�쐬��:K.Asada
	�X�V���e:�V�d�l�����ɔ���������ύX
	�X�V��:2017.10.24
	�X�V��:K.Asada*/
	void CardConnect(SCARDCONTEXT hContext, SCARDHANDLE &hCard, DWORD &ActiveProtocol) {
		LONG lResult = 0;        //�ڑ����ʂ��i�[���邽�߂̕ϐ�
		DWORD dwAutoAllocate = SCARD_AUTOALLOCATE;    //�A���P�[�^
		//�J�[�h�Ƃ̐ڑ����J�n����
		lResult = ::SCardConnect(hContext, PASORI_NAME, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &ActiveProtocol);
		//�ڑ����ʂ����s�Ȃ��O�𓊂���
		if (lResult != SCARD_S_SUCCESS) {
			//�J�[�h���Ȃ����Ƃ̃G���[�Ȃ�
			if (lResult == SCARD_W_REMOVED_CARD) {
				//�J�[�h���Ȃ��|��`����G���[�𓊂���
				throw gcnew System::Exception(Constants->REMOVE_ERROR);
			}//����ȊO�̃G���[�̎��͕ʂ̗�O��`����
			else {
				throw gcnew System::Exception(Constants->ERROR_MESSAGE);
			}
			//�ڑ����I������
			EndConnect(hContext, hCard);
		}
		//�m�ۂ����v���g�R����ԋp����
		return;
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
//		::SCardFreeMemory(hContext, PASORI_NAME);
		//���\�[�X�}�l�[�W�����������
		::SCardReleaseContext(hContext);
		return;
	}
};
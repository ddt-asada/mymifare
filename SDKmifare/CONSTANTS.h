#pragma once

#define PCSC_TRANS_BUFF_LEN	(262)

#include <tchar.h>

/*概要:定数クラス
作成日:2017.10.10
作成者:K.Asada*/
namespace CONSTANTGROUP {
	public ref class ConstantString {
	public:
		ConstantString() {

		}

		//新規作成時に表示されるメッセージ
		static System::String^ NEW_MESSAGE = "新規で作成します。\n情報を入力してください。";
		//カードをかざす指示のメッセージ
		static System::String^ SET_CARD_MESSAGE = "カードをかざしてください";
		//作成完了時のメッセージ
		static System::String^ FINISH_MESSAGE = "カードが作成されました";
		//操作キャンセル時のメッセージ
		static System::String^ CANCEL_MESSAGE = "操作が中断されました。";
		//退館時のメッセージ
		static System::String^ LEAVE_MESSAGE = "退館しました。";
		//入館時のメッセージ
		static System::String^ ENTER_MESSAGE = "入館しました。";
		//例外発生時のメッセージ
		static System::String^ ERROR_MESSAGE = "エラーが発生しました。";
		//スマートカードサービスが動いていない時のメッセージ
		static System::String^ NO_SERVICE_ERROR = "スマートカードサービスが稼働していません。";
		//カードが設置されていないときのメッセージ
		static System::String^ REMOVE_ERROR = "カードが検知できません。";
		//ユーザーIDが登録されていないときのメッセージ
		static System::String^ ID_NOT_FOUND_ERROR = "対象のIDが見つかりません。";
		//パスワードが間違っているときのときのメッセージ
		static System::String^ PASS_NOT_FOUND_ERROR = "パスワードが違います。";
		//入力された文字数が既定の文字数を超えているときのメッセージ
		static System::String^ OVER_ERROR_MESSAGE = "文字数制限を超えています。\n入力しなおしてください。";
	};
		//送信コマンド用構造体
		typedef struct send{
			int           sendLength;
			unsigned char sendCommand[PCSC_TRANS_BUFF_LEN];
		} SENDCOMM;

		union ITOC {
			unsigned short int num;
			char bytes[sizeof(unsigned short int)];
		};

		//書き込みの始点となるブロック
		static const int BEGIN_BLOCK = 8;
		//書き込みの終点となるブロック
		static const int END_BLOCK = 33;
		//書き込むブロックの数
		static const int BLOCK_COUNT = END_BLOCK - BEGIN_BLOCK;
		//ユーザー名が格納されているブロック番号
		static const int NAME_INDEX = 0;
		//ユーザーフリガナが格納されているブロック番号
		static const int KANA_INDEX = 1;
		//ユーザーIDが格納されているブロック番号
		static const int UID_INDEX = 2;
		//パスワードが格納されているブロック番号
		static const int PASS_INDEX = 2;
		//属性が格納されているブロック番号
		static const int ELEM_INDEX = 10;
		//権限が格納されているブロック番号
		static const int ADM_INDEX = 10;
		//職種が格納されているブロック番号
		static const int OCCUP_INDEX = 10;
		//部署が格納されているブロック番号
		static const int DEPART_INDEX = 10;
		//役職が格納されているブロック番号
		static const int POS_INDEX = 10;
		//住所が格納されているブロック番号
		static const int ADRESS_1_INDEX = 5;
		//住所が格納されているブロック番号
		static const int ADRESS_2_INDEX = 6;
		//住所が格納されているブロック番号
		static const int ADRESS_3_INDEX = 7;
		//住所が格納されているブロック番号
		static const int ADRESS_4_INDEX = 8;
		//住所が格納されているブロック番号
		static const int ADRESS_5_INDEX = 9;
		//電話番号が格納されているブロック番号
		static const int TELL_INDEX = 4;
		//誕生日が格納されているブロック番号
		static const int BIRTH_INDEX = 3;
		//年月が格納されているブロック番号
		static const int YEAR_INDEX = 11;
		//入退館日が格納されているブロック番号
		static 	const int TIMES_1_INDEX = 11;
		//入退館日が格納されているブロック番号
		static const int TIMES_2_INDEX = 12;
		//入退館日が格納されているブロック番号
		static 	const int TIMES_3_INDEX = 13;
		//入退館日が格納されているブロック番号
		static const int TIMES_4_INDEX = 14;
		//入退館日が格納されているブロック番号
		static 	const int LEAVE_1_INDEX = 15;
		//入退館日が格納されているブロック番号
		static const int LEAVE_2_INDEX = 16;
		//入退館日が格納されているブロック番号
		static const int LEAVE_3_INDEX = 17;
		//入退館日が格納されているブロック番号
		static const int LEAVE_4_INDEX = 18;
		//属性の1ビット目の名前
		static const char* ELEM_NAME1 = "一般人";
		//属性の2ビット目の名前
		static const char* ELEM_NAME2 = "管理者";
		//属性の3ビット目の名前
		static const char* ELEM_NAME3 = "要注意人物";
		//属性の4ビット目の名前
		static const char* ELEM_NAME4 = "危険人物";
		//権限の1ビット目の名前
		static const char* ADM_NAME1 = "一般";
		//権限の2ビット目の名前
		static const char* ADM_NAME2 = "管理者";
		//職種の1ビット目の名前
		static const char* OCCUP_NAME1 = "営業";
		//職種の2ビット目の名前
		static const char* OCCUP_NAME2 = "総務";
		//職種の3ビット目の名前
		static const char* OCCUP_NAME3 = "事務";
		//職種の4ビット目の名前
		static const char* OCCUP_NAME4 = "PG";
		//部署の1ビット目の名前
		static const char* DEPART_NAME1 = "営業部";
		//部署の2ビット目の名前
		static const char* DEPART_NAME2 = "総務部";
		//部署の3ビット目の名前
		static const char* DEPART_NAME3 = "経理部";
		//部署の4ビット目の名前
		static const char* DEPART_NAME4 = "開発部";
		//役職の1ビット目の名前
		static const char* POS_NAME1 = "パート";
		//役職の2ビット目の名前
		static const char* POS_NAME2 = "研修";
		//役職の3ビット目の名前
		static const char* POS_NAME3 = "一般社員";
		//役職の4ビット目の名前
		static const char* POS_NAME4 = "部長";
	static const SENDCOMM LOADKEY = { 11,{ 0xFF,0x82,0x00,0x00,0x06,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF } };
	//セクター認証コマンド、各セクターにアクセスする前に行わなければならない(詳細はリファレンス参照)
	// General Authenticate
	static const SENDCOMM AUTHENTICATE = { 10,{ 0xFF,0x86,0x00,0x00,0x05,0x01,0x00,BEGIN_BLOCK,0x60,0x00 } };
	//データ受信コマンド、カードのデータを受信する際に使用(詳細はリファレンス参照)
	//ReadBinary
	static const SENDCOMM READCARD = { 5,{ 0xFF,0xB0,0x00,BEGIN_BLOCK,0x00 } };
	//データ送信コマンド、カードにデータを送信する際に使用(詳細はリファレンス参照)
	//UpdateBinary
	static const SENDCOMM SENDCARD = { 21,{ 0xFF,0xD6,0x00,BEGIN_BLOCK,0x10 } };
	//送信コマンドの終わりをしめすコマンド
	static const SENDCOMM ENDCOMMAND = { -1, NULL };
}
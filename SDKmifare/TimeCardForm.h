#pragma once

#include <vector>
#include <string>
#include "CONSTANTS.h"

namespace sdkmifare {

	using namespace CONSTANTGROUP;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// TimeCardForm の概要
	/// </summary>
	public ref class TimeCardForm : public System::Windows::Forms::Form
	{
	public:
		TimeCardForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~TimeCardForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::PictureBox^  pictureBox2;


	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(401, 51);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::White;
			this->pictureBox2->Location = System::Drawing::Point(0, 200);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(401, 51);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			// 
			// TimeCardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(339, 270);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"TimeCardForm";
			this->Text = L"TimeCardForm";
			this->Load += gcnew System::EventHandler(this, &TimeCardForm::TimeCardForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public:
		std::vector<std::vector<unsigned char>>* carddata = new std::vector<std::vector<unsigned char>>();    //カードより取得したデータ
		ConstantString^ Constants = gcnew ConstantString();    //定数クラスをインスタンス化

	private:
		/*概要:タイムカードの表を作成する関数
		引数:std::vector<std::vecor<unsigned char>> data:カードより受信したデータ
		戻り値:System::Drawing::Bitmap^ img:作成した表画像
		作成日:2017.10.18
		作成者:K.Asada*/
		System::Drawing::Bitmap^ CreateTimes(std::vector<std::vector<unsigned char>> data) {
			std::vector<std::string> entertimes;    //入館日を格納する文字列
			std::vector<std::string> leavetimes;    //退館日を格納する文字列
			int index = 0;    //ループ回数を設定するための変数
			//カードデータより入館日を取得する
			entertimes = this->ConvEnterTimes(data);
			//カードデータより退館日を取得する
			leavetimes = this->ConvLeaveTimes(data);
			//入館日の要素数を取得する
			index = entertimes.size();
			System::Drawing::Bitmap^ img = gcnew Bitmap(200 * 2 + 1, 50 * index + 1);    //画像用の空のビットマップを作成
			System::Drawing::Graphics^ gr = System::Drawing::Graphics::FromImage(img);   //描画用のグラフィッククラスをインスタンス化
			System::Drawing::Font^ font = gcnew System::Drawing::Font(System::Drawing::FontFamily::GenericSansSerif, 12, System::Drawing::FontStyle::Regular);    //文字列描画用のフォントをインスタンス化
			//入館日の走査を行う
			for (int i = 0; i < entertimes.size(); i++) {
				//表画像の格子を描画する
				gr->DrawRectangle(Pens::Black, 0, 50 * i, 200, 50);
				//表画像の格子を描画する
				gr->DrawRectangle(Pens::Black, 200, 50 * i, 200, 50);
				//入館日を描画する
				gr->DrawString(gcnew String(entertimes[i].c_str()), font, Brushes::Black, 0, 50*i);
				
			}
			//退館日の走査を行う
			for (int i = 0; i < leavetimes.size(); i++) {
				//退館日を描画する
				gr->DrawString(gcnew String(leavetimes[i].c_str()), font, Brushes::Black, 200, 50 * i);
			}
			//作成した画像を返却する
			return img;
		}

		/*概要:タイムカードのタイトル部分を作成する関数
		引数:std::vector<std::vecor<unsigned char>> data:カードより受信したデータ
		戻り値:System::Drawing::Bitmap^ img:作成した表画像
		作成日:2017.10.18
		作成者:K.Asada*/
		System::Drawing::Bitmap^ InitPict(std::vector<std::vector<unsigned char>> data) {
			std::string years;    //年月を格納するための文字列
			//カードデータより年月を取得する
			years = this->ConvYears(data);
			//空のビットマップを生成する
			System::Drawing::Bitmap^ img = gcnew Bitmap(200 * 2 + 1, 100 +1);
			//描画用のグラフィッククラスインスタンス化
			System::Drawing::Graphics^ gr = System::Drawing::Graphics::FromImage(img);
			//文字列描画用のフォントをインスタンス化
			System::Drawing::Font^ font = gcnew System::Drawing::Font(System::Drawing::FontFamily::GenericSansSerif, 12, System::Drawing::FontStyle::Regular);
			//表画像の格子を描画する
			gr->DrawRectangle(Pens::Black, 0, 0, 200, 50);
			//表画像の格子を描画する
			gr->DrawRectangle(Pens::Black, 200, 0, 200, 50);
			//表画像の格子を描画する
			gr->DrawRectangle(Pens::Black, 0, 50, 200, 50);
			//表画像の格子を描画する
			gr->DrawRectangle(Pens::Black, 200, 50, 200, 50);
			//年月を描画する
			gr->DrawString("年月", font, Brushes::Black, 0, 0);
			//年月を描画する
			gr->DrawString(gcnew String(years.c_str()), font, Brushes::Black, 200, 0);
			//入館日を描画する
			gr->DrawString("入館日", font, Brushes::Black, 0, 50);
			//退館日を描画する
			gr->DrawString("退館日", font, Brushes::Black, 200, 50);
			//作成した画像を返す
			return img;
		}

		/*概要:カードに格納された日時分情報を文字列に変換する関数
		引数:std::vector<std::vcotr<unsigned char>> data:カードデータ
		戻り値:std::vector<string> times:日時分を文字列に変換した配列
		作成日:2017.10.16
		作成者:K.Asada*/
private: std::vector<std::string> ConvEnterTimes(std::vector<std::vector<unsigned char>> data) {
	try {
		std::vector<std::string> times;        //日時分を文字列に変換したものを格納するための配列
		ITOC gettimes;                         //カードデータの中にあるchar型の数値をunsigned int型に変換するための共有体
		int day = 0;                           //取得した日を格納する変数
		int hour = 0;                          //取得した時間を格納する変数
		int min = 0;                           //取得した分を格納する変数
		int timeindex = TIMES_1_INDEX;
		//カードデータにある日時分情報を走査していく
		for (int i = 1; data[timeindex][i * 2] != ' '; i++) {
			//カードデータより日時分の上位8ビットを取得する
			gettimes.bytes[1] = data[timeindex][i * 2];
			//カードデータより日時分の下位8ビットを取得する
			gettimes.bytes[0] = data[timeindex][i * 2 + 1];
			//取得した日時分を日に変換する
			day = gettimes.num / 1440;
			//取得した日時分を時に変換する
			hour = gettimes.num / 60 - day * 24;
			//取得した日時分を分に変換する
			min = gettimes.num - 1440 * day - 60 * hour;
			//変換した日時分を連結して文字列を完成させる
			times.push_back(std::to_string(day) + "日" + std::to_string(hour) + "時" + std::to_string(min) + "分" + '\n');
			if (i == 7) {
				i = -1;
				timeindex++;
			}
		}
		//変換した文字列を返却する
		return times;
	}
	catch (System::IndexOutOfRangeException^ e) {
		System::Console::WriteLine(e);
	}
}

		 /*概要:カードに格納された退館時間を取得するための関数
		 引数:std::vector<std::vcotr<unsigned char>> data:カードデータ
		 戻り値:std::vector<string> times:日時分を文字列に変換した配列
		 作成日:2017.10.17
		 作成者:K.Asada*/
		 private: std::vector<std::string> ConvLeaveTimes(std::vector<std::vector<unsigned char>> data) {
			 try {
				std::vector<std::string> times;        //日時分を文字列に変換したものを格納するための配列
				 ITOC gettimes;                         //カードデータの中にあるchar型の数値をunsigned int型に変換するための共有体
				 int day = 0;                           //取得した日を格納する変数
				 int hour = 0;                          //取得した時間を格納する変数
				 int min = 0;                           //取得した分を格納する変数
				 int timeindex = LEAVE_1_INDEX;
				 //カードデータにある日時分情報を走査していく
				 for (int i = 0; data[timeindex][i * 2] != ' '; i++) {
					 //カードデータより日時分の上位8ビットを取得する
					 gettimes.bytes[1] = data[timeindex][i * 2];
					 //カードデータより日時分の下位8ビットを取得する
					 gettimes.bytes[0] = data[timeindex][i * 2 + 1];
					 //取得した日時分を日に変換する
					 day = gettimes.num / 1440;
					 //取得した日時分を時に変換する
					 hour = gettimes.num / 60 - day * 24;
					 //取得した日時分を分に変換する
					 min = gettimes.num - 1440 * day - 60 * hour;
					 //変換した日時分を連結して文字列を完成させる
					 times.push_back(std::to_string(day) + "日" + std::to_string(hour) + "時" + std::to_string(min) + "分" + '\n');
					 if (i == 7) {
						 i = -1;
						 timeindex++;
					 }
				 }
				 //変換した文字列を返却する
				 return times;
			 }
			 catch (System::IndexOutOfRangeException^ e) {
				 System::Console::WriteLine(e);
			 }
		 }

				  /*概要:カードに格納された年月情報を文字列に変換するための関数
				  引数:std::vector<std::vector<unsigned char>> data:カードより取得したデータ
				  戻り値:std::vector<std::string> years:文字列に変換した年月
				  作成日:2017.10.16
				  作成者:K.Asada*/
private: std::string ConvYears(std::vector<std::vector<unsigned char>> data) {
	try {
		std::string years;        //変換した文字列を格納する
		ITOC getyears;            //カードより取得した年月をunsigned int型に変換するための共有体
		int year = 0;             //取得した年
		int month = 0;            //取得した月
								  //カードデータより年月の上位8ビットを取得する
		getyears.bytes[1] = data[YEAR_INDEX][0];
		//カードデータより年月の下位8ビットを取得する
		getyears.bytes[0] = data[YEAR_INDEX][1];
		//年月を年に変換する
		year = getyears.num / 12;
		//年月を月に変換する
		month = getyears.num % 12;
		//変換した年月を連結して文字列を完成させる
		years = (std::to_string(year) + "年" + std::to_string(month) + "月");
		//変換した文字列を返却する
		return years;
	}
	catch (System::IndexOutOfRangeException^ e) {
		System::Console::WriteLine(e);
	}
}
	private: System::Void TimeCardForm_Load(System::Object^  sender, System::EventArgs^  e) {
		//タイトル部分の表画像を作成する
		this->pictureBox1->Image = this->InitPict(*this->carddata);
		//表画像の中身を作成する
		this->pictureBox2->Image = this->CreateTimes(*this->carddata);
	}
};
}

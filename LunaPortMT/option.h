#pragma once

#include "stdafx.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Diagnostics;

namespace LunaPortMT {

	/// <summary>
	/// option の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class option : public System::Windows::Forms::Form
	{
	public:
		option(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		‾option()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxGameExe;
	private: System::Windows::Forms::Button^  buttonGameExe;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxReplayFolder;
	private: System::Windows::Forms::Button^  buttonReplayFolder;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownMaxConnections;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownMaxStages;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownStageSelect;
	private: System::Windows::Forms::CheckBox^  checkBoxName;
	private: System::Windows::Forms::CheckBox^  checkBoxInputrate;
	private: System::Windows::Forms::CheckBox^  checkBoxFramerate;

	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Button^  buttonApply;
	private: System::Windows::Forms::Button^  buttonCancel;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::TabControl^  tabControlOption;
	private: System::Windows::Forms::TabPage^  tabPagePath;
	private: System::Windows::Forms::TabPage^  tabPageGame;
	private: System::Windows::Forms::TabPage^  tabPageColor;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  buttonNoticeSound;

	private: System::Windows::Forms::TextBox^  textBoxNoticeSound;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  buttonVSSound;

	private: System::Windows::Forms::TextBox^  textBoxVSSound;

	private: System::Windows::Forms::CheckBox^  checkBoxHitJudge;
	private: System::Windows::Forms::GroupBox^  groupBoxStage;

	private: System::Windows::Forms::GroupBox^  groupBoxReplayVersion;




	private: System::Windows::Forms::GroupBox^  groupBoxPath;
	private: System::Windows::Forms::GroupBox^  groupBoxSound;
	private: System::Windows::Forms::GroupBox^  groupBoxView;
	private: System::Windows::Forms::GroupBox^  groupBoxNet;

	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::GroupBox^  groupBoxNameColor;
	private: System::Windows::Forms::GroupBox^  groupBoxMessageColor;
	private: System::Windows::Forms::GroupBox^  groupBoxOthersColor;
	private: System::Windows::Forms::GroupBox^  groupBoxStateColor;
	private: System::Windows::Forms::Button^  buttonClientName;
	private: System::Windows::Forms::Button^  buttonHostName;
	private: System::Windows::Forms::Button^  buttonServerName;
	private: System::Windows::Forms::Button^  buttonWatchState;
	private: System::Windows::Forms::Button^  buttonVSState;
	private: System::Windows::Forms::Button^  buttonRestState;
	private: System::Windows::Forms::Button^  buttonDebugMessage;
	private: System::Windows::Forms::Button^  buttonErrorMessage;
	private: System::Windows::Forms::Button^  buttonSystemMessage;
	private: System::Windows::Forms::Button^  buttonNoticeBack;
	private: System::Windows::Forms::Button^  buttonCommentBack;
	private: System::Windows::Forms::Button^  buttonSecret;
	private: System::Windows::Forms::GroupBox^  groupBoxRun;

	private: System::Windows::Forms::CheckBox^  checkBoxWindowSize;
	private: System::Windows::Forms::CheckBox^  checkBoxVersus;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownTime;
	private: System::Windows::Forms::CheckBox^  checkBoxDivide;

	private: System::Windows::Forms::RadioButton^  radioButtonReplayVersion2;
	private: System::Windows::Forms::RadioButton^  radioButtonReplayVersion1;






	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonReplayFolder = (gcnew System::Windows::Forms::Button());
			this->textBoxReplayFolder = (gcnew System::Windows::Forms::TextBox());
			this->buttonGameExe = (gcnew System::Windows::Forms::Button());
			this->textBoxGameExe = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownMaxConnections = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDownStageSelect = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownMaxStages = (gcnew System::Windows::Forms::NumericUpDown());
			this->checkBoxName = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxInputrate = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxFramerate = (gcnew System::Windows::Forms::CheckBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->buttonApply = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->tabControlOption = (gcnew System::Windows::Forms::TabControl());
			this->tabPagePath = (gcnew System::Windows::Forms::TabPage());
			this->groupBoxPath = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxSound = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBoxVSSound = (gcnew System::Windows::Forms::TextBox());
			this->buttonNoticeSound = (gcnew System::Windows::Forms::Button());
			this->buttonVSSound = (gcnew System::Windows::Forms::Button());
			this->textBoxNoticeSound = (gcnew System::Windows::Forms::TextBox());
			this->tabPageGame = (gcnew System::Windows::Forms::TabPage());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownTime = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBoxRun = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxWindowSize = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxHitJudge = (gcnew System::Windows::Forms::CheckBox());
			this->groupBoxNet = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxView = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxVersus = (gcnew System::Windows::Forms::CheckBox());
			this->groupBoxStage = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxReplayVersion = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxDivide = (gcnew System::Windows::Forms::CheckBox());
			this->radioButtonReplayVersion2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonReplayVersion1 = (gcnew System::Windows::Forms::RadioButton());
			this->tabPageColor = (gcnew System::Windows::Forms::TabPage());
			this->groupBoxMessageColor = (gcnew System::Windows::Forms::GroupBox());
			this->buttonDebugMessage = (gcnew System::Windows::Forms::Button());
			this->buttonErrorMessage = (gcnew System::Windows::Forms::Button());
			this->buttonSystemMessage = (gcnew System::Windows::Forms::Button());
			this->groupBoxOthersColor = (gcnew System::Windows::Forms::GroupBox());
			this->buttonSecret = (gcnew System::Windows::Forms::Button());
			this->buttonCommentBack = (gcnew System::Windows::Forms::Button());
			this->buttonNoticeBack = (gcnew System::Windows::Forms::Button());
			this->groupBoxStateColor = (gcnew System::Windows::Forms::GroupBox());
			this->buttonWatchState = (gcnew System::Windows::Forms::Button());
			this->buttonVSState = (gcnew System::Windows::Forms::Button());
			this->buttonRestState = (gcnew System::Windows::Forms::Button());
			this->groupBoxNameColor = (gcnew System::Windows::Forms::GroupBox());
			this->buttonClientName = (gcnew System::Windows::Forms::Button());
			this->buttonHostName = (gcnew System::Windows::Forms::Button());
			this->buttonServerName = (gcnew System::Windows::Forms::Button());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownMaxConnections))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownStageSelect))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownMaxStages))->BeginInit();
			this->tabControlOption->SuspendLayout();
			this->tabPagePath->SuspendLayout();
			this->groupBoxPath->SuspendLayout();
			this->groupBoxSound->SuspendLayout();
			this->tabPageGame->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownTime))->BeginInit();
			this->groupBoxRun->SuspendLayout();
			this->groupBoxNet->SuspendLayout();
			this->groupBoxView->SuspendLayout();
			this->groupBoxStage->SuspendLayout();
			this->groupBoxReplayVersion->SuspendLayout();
			this->tabPageColor->SuspendLayout();
			this->groupBoxMessageColor->SuspendLayout();
			this->groupBoxOthersColor->SuspendLayout();
			this->groupBoxStateColor->SuspendLayout();
			this->groupBoxNameColor->SuspendLayout();
			this->SuspendLayout();
			// 
			// buttonReplayFolder
			// 
			this->buttonReplayFolder->Location = System::Drawing::Point(312, 76);
			this->buttonReplayFolder->Name = L"buttonReplayFolder";
			this->buttonReplayFolder->Size = System::Drawing::Size(24, 20);
			this->buttonReplayFolder->TabIndex = 4;
			this->buttonReplayFolder->Text = L"...";
			this->buttonReplayFolder->UseVisualStyleBackColor = true;
			this->buttonReplayFolder->Click += gcnew System::EventHandler(this, &option::buttonReplayFolder_Click);
			// 
			// textBoxReplayFolder
			// 
			this->textBoxReplayFolder->AllowDrop = true;
			this->textBoxReplayFolder->Location = System::Drawing::Point(16, 76);
			this->textBoxReplayFolder->Name = L"textBoxReplayFolder";
			this->textBoxReplayFolder->Size = System::Drawing::Size(296, 19);
			this->textBoxReplayFolder->TabIndex = 3;
			this->textBoxReplayFolder->TextChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			this->textBoxReplayFolder->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &option::textBoxReplayFolder_DragDrop);
			this->textBoxReplayFolder->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &option::textBoxReplayFolder_DragEnter);
			// 
			// buttonGameExe
			// 
			this->buttonGameExe->Location = System::Drawing::Point(312, 36);
			this->buttonGameExe->Name = L"buttonGameExe";
			this->buttonGameExe->Size = System::Drawing::Size(24, 19);
			this->buttonGameExe->TabIndex = 2;
			this->buttonGameExe->Text = L"...";
			this->buttonGameExe->UseVisualStyleBackColor = true;
			this->buttonGameExe->Click += gcnew System::EventHandler(this, &option::buttonGameExe_Click);
			// 
			// textBoxGameExe
			// 
			this->textBoxGameExe->AllowDrop = true;
			this->textBoxGameExe->Location = System::Drawing::Point(16, 36);
			this->textBoxGameExe->Name = L"textBoxGameExe";
			this->textBoxGameExe->Size = System::Drawing::Size(296, 19);
			this->textBoxGameExe->TabIndex = 1;
			this->textBoxGameExe->TextChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			this->textBoxGameExe->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &option::textBoxGameExe_DragDrop);
			this->textBoxGameExe->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &option::textBoxGameExe_DragEnter);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 60);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(98, 12);
			this->label2->TabIndex = 0;
			this->label2->Text = L"リプレイ保存フォルダ";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"実行ファイル";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(16, 20);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(65, 12);
			this->label5->TabIndex = 0;
			this->label5->Text = L"最大接続数";
			// 
			// numericUpDownMaxConnections
			// 
			this->numericUpDownMaxConnections->Location = System::Drawing::Point(112, 16);
			this->numericUpDownMaxConnections->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownMaxConnections->Name = L"numericUpDownMaxConnections";
			this->numericUpDownMaxConnections->Size = System::Drawing::Size(40, 19);
			this->numericUpDownMaxConnections->TabIndex = 1;
			this->numericUpDownMaxConnections->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownMaxConnections->ValueChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// numericUpDownStageSelect
			// 
			this->numericUpDownStageSelect->Location = System::Drawing::Point(112, 44);
			this->numericUpDownStageSelect->Name = L"numericUpDownStageSelect";
			this->numericUpDownStageSelect->Size = System::Drawing::Size(40, 19);
			this->numericUpDownStageSelect->TabIndex = 2;
			this->numericUpDownStageSelect->ValueChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(16, 48);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(67, 12);
			this->label7->TabIndex = 0;
			this->label7->Text = L"対戦ステージ";
			// 
			// numericUpDownMaxStages
			// 
			this->numericUpDownMaxStages->Location = System::Drawing::Point(112, 16);
			this->numericUpDownMaxStages->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownMaxStages->Name = L"numericUpDownMaxStages";
			this->numericUpDownMaxStages->Size = System::Drawing::Size(40, 19);
			this->numericUpDownMaxStages->TabIndex = 1;
			this->numericUpDownMaxStages->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownMaxStages->ValueChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// checkBoxName
			// 
			this->checkBoxName->AutoSize = true;
			this->checkBoxName->Location = System::Drawing::Point(16, 20);
			this->checkBoxName->Name = L"checkBoxName";
			this->checkBoxName->Size = System::Drawing::Size(78, 16);
			this->checkBoxName->TabIndex = 1;
			this->checkBoxName->Text = L"ニックネーム";
			this->checkBoxName->UseVisualStyleBackColor = true;
			this->checkBoxName->CheckedChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// checkBoxInputrate
			// 
			this->checkBoxInputrate->AutoSize = true;
			this->checkBoxInputrate->Location = System::Drawing::Point(16, 92);
			this->checkBoxInputrate->Name = L"checkBoxInputrate";
			this->checkBoxInputrate->Size = System::Drawing::Size(93, 16);
			this->checkBoxInputrate->TabIndex = 4;
			this->checkBoxInputrate->Text = L"インプットレート";
			this->checkBoxInputrate->UseVisualStyleBackColor = true;
			this->checkBoxInputrate->CheckedChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// checkBoxFramerate
			// 
			this->checkBoxFramerate->AutoSize = true;
			this->checkBoxFramerate->Location = System::Drawing::Point(16, 68);
			this->checkBoxFramerate->Name = L"checkBoxFramerate";
			this->checkBoxFramerate->Size = System::Drawing::Size(88, 16);
			this->checkBoxFramerate->TabIndex = 3;
			this->checkBoxFramerate->Text = L"フレームレート";
			this->checkBoxFramerate->UseVisualStyleBackColor = true;
			this->checkBoxFramerate->CheckedChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(16, 20);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(79, 12);
			this->label6->TabIndex = 0;
			this->label6->Text = L"最大ステージ数";
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(152, 272);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(64, 24);
			this->buttonOK->TabIndex = 7;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &option::buttonOK_Click);
			// 
			// buttonApply
			// 
			this->buttonApply->Location = System::Drawing::Point(224, 272);
			this->buttonApply->Name = L"buttonApply";
			this->buttonApply->Size = System::Drawing::Size(64, 24);
			this->buttonApply->TabIndex = 8;
			this->buttonApply->Text = L"適用";
			this->buttonApply->UseVisualStyleBackColor = true;
			this->buttonApply->Click += gcnew System::EventHandler(this, &option::buttonApply_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->Location = System::Drawing::Point(296, 272);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(64, 24);
			this->buttonCancel->TabIndex = 9;
			this->buttonCancel->Text = L"キャンセル";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &option::buttonCancel_Click);
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->Description = L"リプレイ保存フォルダ";
			// 
			// tabControlOption
			// 
			this->tabControlOption->Controls->Add(this->tabPagePath);
			this->tabControlOption->Controls->Add(this->tabPageGame);
			this->tabControlOption->Controls->Add(this->tabPageColor);
			this->tabControlOption->Dock = System::Windows::Forms::DockStyle::Top;
			this->tabControlOption->Location = System::Drawing::Point(0, 0);
			this->tabControlOption->Name = L"tabControlOption";
			this->tabControlOption->SelectedIndex = 0;
			this->tabControlOption->Size = System::Drawing::Size(377, 268);
			this->tabControlOption->TabIndex = 0;
			// 
			// tabPagePath
			// 
			this->tabPagePath->Controls->Add(this->groupBoxPath);
			this->tabPagePath->Controls->Add(this->groupBoxSound);
			this->tabPagePath->Location = System::Drawing::Point(4, 21);
			this->tabPagePath->Name = L"tabPagePath";
			this->tabPagePath->Padding = System::Windows::Forms::Padding(3);
			this->tabPagePath->Size = System::Drawing::Size(369, 243);
			this->tabPagePath->TabIndex = 0;
			this->tabPagePath->Text = L"パス";
			this->tabPagePath->UseVisualStyleBackColor = true;
			// 
			// groupBoxPath
			// 
			this->groupBoxPath->Controls->Add(this->label1);
			this->groupBoxPath->Controls->Add(this->textBoxGameExe);
			this->groupBoxPath->Controls->Add(this->buttonReplayFolder);
			this->groupBoxPath->Controls->Add(this->buttonGameExe);
			this->groupBoxPath->Controls->Add(this->label2);
			this->groupBoxPath->Controls->Add(this->textBoxReplayFolder);
			this->groupBoxPath->Location = System::Drawing::Point(8, 8);
			this->groupBoxPath->Name = L"groupBoxPath";
			this->groupBoxPath->Size = System::Drawing::Size(352, 108);
			this->groupBoxPath->TabIndex = 1;
			this->groupBoxPath->TabStop = false;
			this->groupBoxPath->Text = L"基本パス";
			// 
			// groupBoxSound
			// 
			this->groupBoxSound->Controls->Add(this->label3);
			this->groupBoxSound->Controls->Add(this->label4);
			this->groupBoxSound->Controls->Add(this->textBoxVSSound);
			this->groupBoxSound->Controls->Add(this->buttonNoticeSound);
			this->groupBoxSound->Controls->Add(this->buttonVSSound);
			this->groupBoxSound->Controls->Add(this->textBoxNoticeSound);
			this->groupBoxSound->Location = System::Drawing::Point(8, 128);
			this->groupBoxSound->Name = L"groupBoxSound";
			this->groupBoxSound->Size = System::Drawing::Size(352, 108);
			this->groupBoxSound->TabIndex = 2;
			this->groupBoxSound->TabStop = false;
			this->groupBoxSound->Text = L"音声ファイル";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(16, 20);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(79, 12);
			this->label3->TabIndex = 0;
			this->label3->Text = L"対戦のお知らせ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(16, 60);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(79, 12);
			this->label4->TabIndex = 0;
			this->label4->Text = L"告知のお知らせ";
			// 
			// textBoxVSSound
			// 
			this->textBoxVSSound->AllowDrop = true;
			this->textBoxVSSound->Location = System::Drawing::Point(16, 36);
			this->textBoxVSSound->Name = L"textBoxVSSound";
			this->textBoxVSSound->Size = System::Drawing::Size(296, 19);
			this->textBoxVSSound->TabIndex = 1;
			this->textBoxVSSound->TextChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			this->textBoxVSSound->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &option::textBoxVSSound_DragDrop);
			this->textBoxVSSound->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &option::textBoxVSSound_DragEnter);
			// 
			// buttonNoticeSound
			// 
			this->buttonNoticeSound->Location = System::Drawing::Point(312, 76);
			this->buttonNoticeSound->Name = L"buttonNoticeSound";
			this->buttonNoticeSound->Size = System::Drawing::Size(24, 19);
			this->buttonNoticeSound->TabIndex = 4;
			this->buttonNoticeSound->Text = L"...";
			this->buttonNoticeSound->UseVisualStyleBackColor = true;
			this->buttonNoticeSound->Click += gcnew System::EventHandler(this, &option::buttonNoticeSound_Click);
			// 
			// buttonVSSound
			// 
			this->buttonVSSound->Location = System::Drawing::Point(312, 36);
			this->buttonVSSound->Name = L"buttonVSSound";
			this->buttonVSSound->Size = System::Drawing::Size(24, 19);
			this->buttonVSSound->TabIndex = 2;
			this->buttonVSSound->Text = L"...";
			this->buttonVSSound->UseVisualStyleBackColor = true;
			this->buttonVSSound->Click += gcnew System::EventHandler(this, &option::buttonVSSound_Click);
			// 
			// textBoxNoticeSound
			// 
			this->textBoxNoticeSound->AllowDrop = true;
			this->textBoxNoticeSound->Location = System::Drawing::Point(16, 76);
			this->textBoxNoticeSound->Name = L"textBoxNoticeSound";
			this->textBoxNoticeSound->Size = System::Drawing::Size(296, 19);
			this->textBoxNoticeSound->TabIndex = 3;
			this->textBoxNoticeSound->TextChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			this->textBoxNoticeSound->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &option::textBoxNoticeSound_DragDrop);
			this->textBoxNoticeSound->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &option::textBoxNoticeSound_DragEnter);
			// 
			// tabPageGame
			// 
			this->tabPageGame->Controls->Add(this->groupBox1);
			this->tabPageGame->Controls->Add(this->groupBoxRun);
			this->tabPageGame->Controls->Add(this->groupBoxNet);
			this->tabPageGame->Controls->Add(this->groupBoxView);
			this->tabPageGame->Controls->Add(this->groupBoxStage);
			this->tabPageGame->Controls->Add(this->groupBoxReplayVersion);
			this->tabPageGame->Location = System::Drawing::Point(4, 21);
			this->tabPageGame->Name = L"tabPageGame";
			this->tabPageGame->Padding = System::Windows::Forms::Padding(3);
			this->tabPageGame->Size = System::Drawing::Size(369, 243);
			this->tabPageGame->TabIndex = 1;
			this->tabPageGame->Text = L"ゲーム";
			this->tabPageGame->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->numericUpDownTime);
			this->groupBox1->Location = System::Drawing::Point(192, 136);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(168, 44);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"フェイクタイマー";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(16, 20);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(53, 12);
			this->label8->TabIndex = 0;
			this->label8->Text = L"制限時間";
			// 
			// numericUpDownTime
			// 
			this->numericUpDownTime->Location = System::Drawing::Point(112, 16);
			this->numericUpDownTime->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {99, 0, 0, 0});
			this->numericUpDownTime->Name = L"numericUpDownTime";
			this->numericUpDownTime->Size = System::Drawing::Size(40, 19);
			this->numericUpDownTime->TabIndex = 0;
			this->numericUpDownTime->ValueChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// groupBoxRun
			// 
			this->groupBoxRun->Controls->Add(this->checkBoxWindowSize);
			this->groupBoxRun->Controls->Add(this->checkBoxHitJudge);
			this->groupBoxRun->Location = System::Drawing::Point(8, 168);
			this->groupBoxRun->Name = L"groupBoxRun";
			this->groupBoxRun->Size = System::Drawing::Size(168, 68);
			this->groupBoxRun->TabIndex = 3;
			this->groupBoxRun->TabStop = false;
			this->groupBoxRun->Text = L"格ツク";
			// 
			// checkBoxWindowSize
			// 
			this->checkBoxWindowSize->AutoSize = true;
			this->checkBoxWindowSize->Location = System::Drawing::Point(16, 44);
			this->checkBoxWindowSize->Name = L"checkBoxWindowSize";
			this->checkBoxWindowSize->Size = System::Drawing::Size(112, 16);
			this->checkBoxWindowSize->TabIndex = 2;
			this->checkBoxWindowSize->Text = L"640 x 480 で起動";
			this->checkBoxWindowSize->UseVisualStyleBackColor = true;
			this->checkBoxWindowSize->CheckedChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// checkBoxHitJudge
			// 
			this->checkBoxHitJudge->AutoSize = true;
			this->checkBoxHitJudge->Location = System::Drawing::Point(16, 20);
			this->checkBoxHitJudge->Name = L"checkBoxHitJudge";
			this->checkBoxHitJudge->Size = System::Drawing::Size(111, 16);
			this->checkBoxHitJudge->TabIndex = 1;
			this->checkBoxHitJudge->Text = L"当たり判定の表示";
			this->checkBoxHitJudge->UseVisualStyleBackColor = true;
			this->checkBoxHitJudge->CheckedChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// groupBoxNet
			// 
			this->groupBoxNet->Controls->Add(this->numericUpDownMaxConnections);
			this->groupBoxNet->Controls->Add(this->label5);
			this->groupBoxNet->Location = System::Drawing::Point(192, 192);
			this->groupBoxNet->Name = L"groupBoxNet";
			this->groupBoxNet->Size = System::Drawing::Size(168, 44);
			this->groupBoxNet->TabIndex = 6;
			this->groupBoxNet->TabStop = false;
			this->groupBoxNet->Text = L"回線設定";
			// 
			// groupBoxView
			// 
			this->groupBoxView->Controls->Add(this->checkBoxVersus);
			this->groupBoxView->Controls->Add(this->checkBoxName);
			this->groupBoxView->Controls->Add(this->checkBoxFramerate);
			this->groupBoxView->Controls->Add(this->checkBoxInputrate);
			this->groupBoxView->Location = System::Drawing::Point(192, 8);
			this->groupBoxView->Name = L"groupBoxView";
			this->groupBoxView->Size = System::Drawing::Size(168, 116);
			this->groupBoxView->TabIndex = 4;
			this->groupBoxView->TabStop = false;
			this->groupBoxView->Text = L"タイトルバー";
			// 
			// checkBoxVersus
			// 
			this->checkBoxVersus->AutoSize = true;
			this->checkBoxVersus->Location = System::Drawing::Point(16, 44);
			this->checkBoxVersus->Name = L"checkBoxVersus";
			this->checkBoxVersus->Size = System::Drawing::Size(60, 16);
			this->checkBoxVersus->TabIndex = 2;
			this->checkBoxVersus->Text = L"対戦数";
			this->checkBoxVersus->UseVisualStyleBackColor = true;
			this->checkBoxVersus->CheckedChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// groupBoxStage
			// 
			this->groupBoxStage->Controls->Add(this->numericUpDownMaxStages);
			this->groupBoxStage->Controls->Add(this->label6);
			this->groupBoxStage->Controls->Add(this->label7);
			this->groupBoxStage->Controls->Add(this->numericUpDownStageSelect);
			this->groupBoxStage->Location = System::Drawing::Point(8, 8);
			this->groupBoxStage->Name = L"groupBoxStage";
			this->groupBoxStage->Size = System::Drawing::Size(168, 72);
			this->groupBoxStage->TabIndex = 1;
			this->groupBoxStage->TabStop = false;
			this->groupBoxStage->Text = L"ステージ";
			// 
			// groupBoxReplayVersion
			// 
			this->groupBoxReplayVersion->Controls->Add(this->checkBoxDivide);
			this->groupBoxReplayVersion->Controls->Add(this->radioButtonReplayVersion2);
			this->groupBoxReplayVersion->Controls->Add(this->radioButtonReplayVersion1);
			this->groupBoxReplayVersion->Location = System::Drawing::Point(8, 88);
			this->groupBoxReplayVersion->Name = L"groupBoxReplayVersion";
			this->groupBoxReplayVersion->Size = System::Drawing::Size(168, 72);
			this->groupBoxReplayVersion->TabIndex = 2;
			this->groupBoxReplayVersion->TabStop = false;
			this->groupBoxReplayVersion->Text = L"リプレイファイル";
			// 
			// checkBoxDivide
			// 
			this->checkBoxDivide->AutoSize = true;
			this->checkBoxDivide->Location = System::Drawing::Point(16, 48);
			this->checkBoxDivide->Name = L"checkBoxDivide";
			this->checkBoxDivide->Size = System::Drawing::Size(90, 16);
			this->checkBoxDivide->TabIndex = 2;
			this->checkBoxDivide->Text = L"自動振り分け";
			this->checkBoxDivide->UseVisualStyleBackColor = true;
			this->checkBoxDivide->CheckedChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// radioButtonReplayVersion2
			// 
			this->radioButtonReplayVersion2->AutoSize = true;
			this->radioButtonReplayVersion2->Location = System::Drawing::Point(16, 20);
			this->radioButtonReplayVersion2->Name = L"radioButtonReplayVersion2";
			this->radioButtonReplayVersion2->Size = System::Drawing::Size(66, 16);
			this->radioButtonReplayVersion2->TabIndex = 1;
			this->radioButtonReplayVersion2->TabStop = true;
			this->radioButtonReplayVersion2->Text = L"圧縮する";
			this->radioButtonReplayVersion2->UseVisualStyleBackColor = true;
			this->radioButtonReplayVersion2->CheckedChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// radioButtonReplayVersion1
			// 
			this->radioButtonReplayVersion1->AutoSize = true;
			this->radioButtonReplayVersion1->Location = System::Drawing::Point(88, 20);
			this->radioButtonReplayVersion1->Name = L"radioButtonReplayVersion1";
			this->radioButtonReplayVersion1->Size = System::Drawing::Size(59, 16);
			this->radioButtonReplayVersion1->TabIndex = 1;
			this->radioButtonReplayVersion1->TabStop = true;
			this->radioButtonReplayVersion1->Text = L"無圧縮";
			this->radioButtonReplayVersion1->UseVisualStyleBackColor = true;
			this->radioButtonReplayVersion1->CheckedChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// tabPageColor
			// 
			this->tabPageColor->Controls->Add(this->groupBoxMessageColor);
			this->tabPageColor->Controls->Add(this->groupBoxOthersColor);
			this->tabPageColor->Controls->Add(this->groupBoxStateColor);
			this->tabPageColor->Controls->Add(this->groupBoxNameColor);
			this->tabPageColor->Location = System::Drawing::Point(4, 21);
			this->tabPageColor->Name = L"tabPageColor";
			this->tabPageColor->Padding = System::Windows::Forms::Padding(3);
			this->tabPageColor->Size = System::Drawing::Size(369, 243);
			this->tabPageColor->TabIndex = 2;
			this->tabPageColor->Text = L"カラー";
			this->tabPageColor->UseVisualStyleBackColor = true;
			// 
			// groupBoxMessageColor
			// 
			this->groupBoxMessageColor->Controls->Add(this->buttonDebugMessage);
			this->groupBoxMessageColor->Controls->Add(this->buttonErrorMessage);
			this->groupBoxMessageColor->Controls->Add(this->buttonSystemMessage);
			this->groupBoxMessageColor->Location = System::Drawing::Point(192, 8);
			this->groupBoxMessageColor->Name = L"groupBoxMessageColor";
			this->groupBoxMessageColor->Size = System::Drawing::Size(168, 104);
			this->groupBoxMessageColor->TabIndex = 3;
			this->groupBoxMessageColor->TabStop = false;
			this->groupBoxMessageColor->Text = L"メッセージ";
			// 
			// buttonDebugMessage
			// 
			this->buttonDebugMessage->BackColor = System::Drawing::SystemColors::Window;
			this->buttonDebugMessage->Location = System::Drawing::Point(16, 76);
			this->buttonDebugMessage->Name = L"buttonDebugMessage";
			this->buttonDebugMessage->Size = System::Drawing::Size(136, 20);
			this->buttonDebugMessage->TabIndex = 3;
			this->buttonDebugMessage->Text = L"デバッグ";
			this->buttonDebugMessage->UseVisualStyleBackColor = false;
			this->buttonDebugMessage->Click += gcnew System::EventHandler(this, &option::buttonDebugMessage_Click);
			this->buttonDebugMessage->ForeColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// buttonErrorMessage
			// 
			this->buttonErrorMessage->BackColor = System::Drawing::SystemColors::Window;
			this->buttonErrorMessage->Location = System::Drawing::Point(16, 48);
			this->buttonErrorMessage->Name = L"buttonErrorMessage";
			this->buttonErrorMessage->Size = System::Drawing::Size(136, 20);
			this->buttonErrorMessage->TabIndex = 2;
			this->buttonErrorMessage->Text = L"エラー";
			this->buttonErrorMessage->UseVisualStyleBackColor = false;
			this->buttonErrorMessage->Click += gcnew System::EventHandler(this, &option::buttonErrorMessage_Click);
			this->buttonErrorMessage->ForeColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// buttonSystemMessage
			// 
			this->buttonSystemMessage->BackColor = System::Drawing::SystemColors::Window;
			this->buttonSystemMessage->Location = System::Drawing::Point(16, 20);
			this->buttonSystemMessage->Name = L"buttonSystemMessage";
			this->buttonSystemMessage->Size = System::Drawing::Size(136, 20);
			this->buttonSystemMessage->TabIndex = 1;
			this->buttonSystemMessage->Text = L"システム";
			this->buttonSystemMessage->UseVisualStyleBackColor = false;
			this->buttonSystemMessage->Click += gcnew System::EventHandler(this, &option::buttonSystemMessage_Click);
			this->buttonSystemMessage->ForeColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// groupBoxOthersColor
			// 
			this->groupBoxOthersColor->Controls->Add(this->buttonSecret);
			this->groupBoxOthersColor->Controls->Add(this->buttonCommentBack);
			this->groupBoxOthersColor->Controls->Add(this->buttonNoticeBack);
			this->groupBoxOthersColor->Location = System::Drawing::Point(192, 132);
			this->groupBoxOthersColor->Name = L"groupBoxOthersColor";
			this->groupBoxOthersColor->Size = System::Drawing::Size(168, 104);
			this->groupBoxOthersColor->TabIndex = 4;
			this->groupBoxOthersColor->TabStop = false;
			this->groupBoxOthersColor->Text = L"その他";
			// 
			// buttonSecret
			// 
			this->buttonSecret->BackColor = System::Drawing::SystemColors::Window;
			this->buttonSecret->Location = System::Drawing::Point(16, 76);
			this->buttonSecret->Name = L"buttonSecret";
			this->buttonSecret->Size = System::Drawing::Size(136, 20);
			this->buttonSecret->TabIndex = 3;
			this->buttonSecret->Text = L"？？？";
			this->buttonSecret->UseVisualStyleBackColor = false;
			this->buttonSecret->Click += gcnew System::EventHandler(this, &option::buttonSecret_Click);
			this->buttonSecret->ForeColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// buttonCommentBack
			// 
			this->buttonCommentBack->ForeColor = System::Drawing::SystemColors::WindowText;
			this->buttonCommentBack->Location = System::Drawing::Point(16, 48);
			this->buttonCommentBack->Name = L"buttonCommentBack";
			this->buttonCommentBack->Size = System::Drawing::Size(136, 20);
			this->buttonCommentBack->TabIndex = 2;
			this->buttonCommentBack->Text = L"コメントの背景";
			this->buttonCommentBack->UseVisualStyleBackColor = false;
			this->buttonCommentBack->BackColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			this->buttonCommentBack->Click += gcnew System::EventHandler(this, &option::buttonCommentBack_Click);
			// 
			// buttonNoticeBack
			// 
			this->buttonNoticeBack->ForeColor = System::Drawing::SystemColors::WindowText;
			this->buttonNoticeBack->Location = System::Drawing::Point(16, 20);
			this->buttonNoticeBack->Name = L"buttonNoticeBack";
			this->buttonNoticeBack->Size = System::Drawing::Size(136, 20);
			this->buttonNoticeBack->TabIndex = 1;
			this->buttonNoticeBack->Text = L"告知メッセージの背景";
			this->buttonNoticeBack->UseVisualStyleBackColor = false;
			this->buttonNoticeBack->BackColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			this->buttonNoticeBack->Click += gcnew System::EventHandler(this, &option::buttonNoticeBack_Click);
			// 
			// groupBoxStateColor
			// 
			this->groupBoxStateColor->Controls->Add(this->buttonWatchState);
			this->groupBoxStateColor->Controls->Add(this->buttonVSState);
			this->groupBoxStateColor->Controls->Add(this->buttonRestState);
			this->groupBoxStateColor->Location = System::Drawing::Point(8, 132);
			this->groupBoxStateColor->Name = L"groupBoxStateColor";
			this->groupBoxStateColor->Size = System::Drawing::Size(168, 104);
			this->groupBoxStateColor->TabIndex = 2;
			this->groupBoxStateColor->TabStop = false;
			this->groupBoxStateColor->Text = L"状態";
			// 
			// buttonWatchState
			// 
			this->buttonWatchState->ForeColor = System::Drawing::SystemColors::WindowText;
			this->buttonWatchState->Location = System::Drawing::Point(16, 76);
			this->buttonWatchState->Name = L"buttonWatchState";
			this->buttonWatchState->Size = System::Drawing::Size(136, 20);
			this->buttonWatchState->TabIndex = 3;
			this->buttonWatchState->Text = L"観戦中";
			this->buttonWatchState->UseVisualStyleBackColor = false;
			this->buttonWatchState->BackColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			this->buttonWatchState->Click += gcnew System::EventHandler(this, &option::buttonWatchState_Click);
			// 
			// buttonVSState
			// 
			this->buttonVSState->ForeColor = System::Drawing::SystemColors::WindowText;
			this->buttonVSState->Location = System::Drawing::Point(16, 48);
			this->buttonVSState->Name = L"buttonVSState";
			this->buttonVSState->Size = System::Drawing::Size(136, 20);
			this->buttonVSState->TabIndex = 2;
			this->buttonVSState->Text = L"対戦中";
			this->buttonVSState->UseVisualStyleBackColor = false;
			this->buttonVSState->BackColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			this->buttonVSState->Click += gcnew System::EventHandler(this, &option::buttonVSState_Click);
			// 
			// buttonRestState
			// 
			this->buttonRestState->ForeColor = System::Drawing::SystemColors::WindowText;
			this->buttonRestState->Location = System::Drawing::Point(16, 20);
			this->buttonRestState->Name = L"buttonRestState";
			this->buttonRestState->Size = System::Drawing::Size(136, 20);
			this->buttonRestState->TabIndex = 1;
			this->buttonRestState->Text = L"休憩中";
			this->buttonRestState->UseVisualStyleBackColor = false;
			this->buttonRestState->BackColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			this->buttonRestState->Click += gcnew System::EventHandler(this, &option::buttonRestState_Click);
			// 
			// groupBoxNameColor
			// 
			this->groupBoxNameColor->Controls->Add(this->buttonClientName);
			this->groupBoxNameColor->Controls->Add(this->buttonHostName);
			this->groupBoxNameColor->Controls->Add(this->buttonServerName);
			this->groupBoxNameColor->Location = System::Drawing::Point(8, 8);
			this->groupBoxNameColor->Name = L"groupBoxNameColor";
			this->groupBoxNameColor->Size = System::Drawing::Size(168, 104);
			this->groupBoxNameColor->TabIndex = 1;
			this->groupBoxNameColor->TabStop = false;
			this->groupBoxNameColor->Text = L"名前";
			// 
			// buttonClientName
			// 
			this->buttonClientName->BackColor = System::Drawing::SystemColors::Window;
			this->buttonClientName->Location = System::Drawing::Point(16, 76);
			this->buttonClientName->Name = L"buttonClientName";
			this->buttonClientName->Size = System::Drawing::Size(136, 20);
			this->buttonClientName->TabIndex = 3;
			this->buttonClientName->Text = L"クライアント";
			this->buttonClientName->UseVisualStyleBackColor = false;
			this->buttonClientName->Click += gcnew System::EventHandler(this, &option::buttonClientName_Click);
			this->buttonClientName->ForeColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// buttonHostName
			// 
			this->buttonHostName->BackColor = System::Drawing::SystemColors::Window;
			this->buttonHostName->Location = System::Drawing::Point(16, 48);
			this->buttonHostName->Name = L"buttonHostName";
			this->buttonHostName->Size = System::Drawing::Size(136, 20);
			this->buttonHostName->TabIndex = 2;
			this->buttonHostName->Text = L"ホスト";
			this->buttonHostName->UseVisualStyleBackColor = false;
			this->buttonHostName->Click += gcnew System::EventHandler(this, &option::buttonHostName_Click);
			this->buttonHostName->ForeColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// buttonServerName
			// 
			this->buttonServerName->BackColor = System::Drawing::SystemColors::Window;
			this->buttonServerName->Location = System::Drawing::Point(16, 20);
			this->buttonServerName->Name = L"buttonServerName";
			this->buttonServerName->Size = System::Drawing::Size(136, 20);
			this->buttonServerName->TabIndex = 1;
			this->buttonServerName->Text = L"サーバ";
			this->buttonServerName->UseVisualStyleBackColor = false;
			this->buttonServerName->Click += gcnew System::EventHandler(this, &option::buttonServerName_Click);
			this->buttonServerName->ForeColorChanged += gcnew System::EventHandler(this, &option::ApplyButtonEnable);
			// 
			// colorDialog1
			// 
			this->colorDialog1->FullOpen = true;
			// 
			// option
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(377, 301);
			this->Controls->Add(this->tabControlOption);
			this->Controls->Add(this->buttonApply);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonOK);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"option";
			this->ShowInTaskbar = false;
			this->Text = L"オプション";
			this->Load += gcnew System::EventHandler(this, &option::option_Load);
			this->Shown += gcnew System::EventHandler(this, &option::option_Shown);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &option::option_FormClosed);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownMaxConnections))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownStageSelect))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownMaxStages))->EndInit();
			this->tabControlOption->ResumeLayout(false);
			this->tabPagePath->ResumeLayout(false);
			this->groupBoxPath->ResumeLayout(false);
			this->groupBoxPath->PerformLayout();
			this->groupBoxSound->ResumeLayout(false);
			this->groupBoxSound->PerformLayout();
			this->tabPageGame->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownTime))->EndInit();
			this->groupBoxRun->ResumeLayout(false);
			this->groupBoxRun->PerformLayout();
			this->groupBoxNet->ResumeLayout(false);
			this->groupBoxNet->PerformLayout();
			this->groupBoxView->ResumeLayout(false);
			this->groupBoxView->PerformLayout();
			this->groupBoxStage->ResumeLayout(false);
			this->groupBoxStage->PerformLayout();
			this->groupBoxReplayVersion->ResumeLayout(false);
			this->groupBoxReplayVersion->PerformLayout();
			this->tabPageColor->ResumeLayout(false);
			this->groupBoxMessageColor->ResumeLayout(false);
			this->groupBoxOthersColor->ResumeLayout(false);
			this->groupBoxStateColor->ResumeLayout(false);
			this->groupBoxNameColor->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	protected:
		void AdviceGameExe(){
			textBoxGameExe->Text = gcnew String("右のボタンを押してパスを設定してください");
			textBoxGameExe->Focus();
		}

		// option.cpp
		void SaveOptions(bool apply);

	public:
		bool GameExePathError;

		void SetGameExePath(String^% path){
			textBoxGameExe->Text = path;
		}

	private:
		System::Void option_Load(System::Object^  sender, System::EventArgs^  e) {
			textBoxGameExe->MaxLength      = _MAX_PATH;
			textBoxReplayFolder->MaxLength = _MAX_PATH;
			textBoxVSSound->MaxLength      = _MAX_PATH;
			textBoxNoticeSound->MaxLength  = _MAX_PATH;

			textBoxGameExe->Text      = gcnew String(LPMTOPTION.GAME_EXE);
			textBoxReplayFolder->Text = gcnew String(LPMTOPTION.REPLAY_FOLDER);
			textBoxVSSound->Text      = gcnew String(LPMTOPTION.VS_SOUND);
			textBoxNoticeSound->Text  = gcnew String(LPMTOPTION.NOTICE_SOUND);
			numericUpDownMaxConnections->Value = LPMTOPTION.MAX_CONNECTIONS;
			numericUpDownMaxStages->Value      = LPMTOPTION.MAX_STAGES;
			numericUpDownStageSelect->Value    = LPMTOPTION.STAGE_SELECT;
			numericUpDownTime->Value           = LPMTOPTION.TIME_LIMIT;
			checkBoxHitJudge->Checked          = LPMTOPTION.HIT_JUDGE;
			checkBoxName->Checked              = LPMTOPTION.DISPLAY_NAMES;
			checkBoxVersus->Checked            = LPMTOPTION.DISPLAY_VERSUS;
			checkBoxFramerate->Checked         = LPMTOPTION.DISPLAY_FRAMERATE;
			checkBoxInputrate->Checked         = LPMTOPTION.DISPLAY_INPUTRATE;
			checkBoxDivide->Checked            = LPMTOPTION.REPLAY_DIVIDE;
			checkBoxWindowSize->Checked        = LPMTOPTION.CHANGE_WINDOW_SIZE;

			if(LPMTOPTION.REPLAY_VERSION == 2){
				radioButtonReplayVersion1->Checked = false;
				radioButtonReplayVersion2->Checked = true;
			}
			else{
				radioButtonReplayVersion1->Checked = true;
				radioButtonReplayVersion2->Checked = false;
			}

			buttonServerName->ForeColor    = Color::FromArgb(LPMTCOLOR.SERVER_NAME);
			buttonHostName->ForeColor      = Color::FromArgb(LPMTCOLOR.HOST_NAME);
			buttonClientName->ForeColor    = Color::FromArgb(LPMTCOLOR.CLIENT_NAME);
			buttonRestState->BackColor     = Color::FromArgb(LPMTCOLOR.REST_STATE);
			buttonVSState->BackColor       = Color::FromArgb(LPMTCOLOR.VS_STATE);
			buttonWatchState->BackColor    = Color::FromArgb(LPMTCOLOR.WATCH_STATE);
			buttonSystemMessage->ForeColor = Color::FromArgb(LPMTCOLOR.SYSTEM_MESSAGE);
			buttonErrorMessage->ForeColor  = Color::FromArgb(LPMTCOLOR.ERROR_MESSAGE);
			buttonDebugMessage->ForeColor  = Color::FromArgb(LPMTCOLOR.DEBUG_MESSAGE);
			buttonNoticeBack->BackColor    = Color::FromArgb(LPMTCOLOR.NOTICE_BACK);
			buttonCommentBack->BackColor   = Color::FromArgb(LPMTCOLOR.COMMENT_BACK);
			buttonSecret->ForeColor        = Color::FromArgb(LPMTCOLOR.SECRET);

			if(LPMTWS.DIALOG_LEFT > 0 && LPMTWS.DIALOG_TOP > 0){
				this->StartPosition = FormStartPosition::Manual;
				this->Location = Point(LPMTWS.DIALOG_LEFT, LPMTWS.DIALOG_TOP);
			}

			buttonApply->Enabled = false;
		}

		System::Void option_Shown(System::Object^  sender, System::EventArgs^  e) {
			if(GameExePathError){
				AdviceGameExe();
			}
		}

		System::Void option_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			LPMTWS.DIALOG_LEFT = this->Location.X;
			LPMTWS.DIALOG_TOP  = this->Location.Y;

			this->Owner->Focus();
		}

		System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
			if(buttonApply->Enabled){
				buttonApply->Enabled = false;

				SaveOptions(false);
			}

			this->Close();
		}

		System::Void buttonApply_Click(System::Object^  sender, System::EventArgs^  e) {
			buttonApply->Enabled = false;

			SaveOptions(true);
		}

		System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
			this->Close();
		}

		System::Void buttonGameExe_Click(System::Object^  sender, System::EventArgs^  e) {
			openFileDialog1->Title  = gcnew String("2D格闘ツクール2nd.の実行ファイル");
			openFileDialog1->Filter = gcnew String("exe file (*.exe)|*.exe");

			if(openFileDialog1->ShowDialog() == ::DialogResult::OK){
				FileVersionInfo^ info = FileVersionInfo::GetVersionInfo(openFileDialog1->FileName);

				if(info->FileDescription == "２Ｄ格闘ツクール2nd."){
					textBoxGameExe->Text = openFileDialog1->FileName;
				}
				else{
					textBoxGameExe->Text = "2D格闘ツクール2nd.の実行ファイルではありません";
					textBoxGameExe->SelectAll();
					textBoxGameExe->Focus();
				}
			}
		}

		System::Void buttonReplayFolder_Click(System::Object^  sender, System::EventArgs^  e) {
			if(folderBrowserDialog1->ShowDialog() == ::DialogResult::OK){
				textBoxReplayFolder->Text = folderBrowserDialog1->SelectedPath;
			}
		}

		System::Void buttonVSSound_Click(System::Object^  sender, System::EventArgs^  e) {
			openFileDialog1->Title  = gcnew String("対戦時に鳴らす音声ファイル");
			openFileDialog1->Filter = gcnew String("wav file (*.wav)|*.wav");

			if(openFileDialog1->ShowDialog() == ::DialogResult::OK){
				textBoxVSSound->Text = openFileDialog1->FileName;
			}
		}

		System::Void buttonNoticeSound_Click(System::Object^  sender, System::EventArgs^  e) {
			openFileDialog1->Title  = gcnew String("告知受信時に鳴らす音声ファイル");
			openFileDialog1->Filter = gcnew String("wav file (*.wav)|*.wav");

			if(openFileDialog1->ShowDialog() == ::DialogResult::OK){
				textBoxNoticeSound->Text = openFileDialog1->FileName;
			}
		}

		System::Void ApplyButtonEnable(System::Object^  sender, System::EventArgs^  e) {
			buttonApply->Enabled = true;
		}

		System::Void buttonServerName_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonServerName->ForeColor = colorDialog1->Color;
			}
		}

		System::Void buttonHostName_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonHostName->ForeColor = colorDialog1->Color;
			}
		}

		System::Void buttonClientName_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonClientName->ForeColor = colorDialog1->Color;
			}
		}

		System::Void buttonRestState_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonRestState->BackColor = colorDialog1->Color;
			}
		}

		System::Void buttonVSState_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonVSState->BackColor = colorDialog1->Color;
			}
		}

		System::Void buttonWatchState_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonWatchState->BackColor = colorDialog1->Color;
			}
		}

		System::Void buttonSystemMessage_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonSystemMessage->ForeColor = colorDialog1->Color;
			}
		}

		System::Void buttonErrorMessage_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonErrorMessage->ForeColor = colorDialog1->Color;
			}
		}

		System::Void buttonDebugMessage_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonDebugMessage->ForeColor = colorDialog1->Color;
			}
		}

		System::Void buttonNoticeBack_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonNoticeBack->BackColor = colorDialog1->Color;
			}
		}

		System::Void buttonCommentBack_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonCommentBack->BackColor = colorDialog1->Color;
			}
		}

		System::Void buttonSecret_Click(System::Object^  sender, System::EventArgs^  e) {
			if(colorDialog1->ShowDialog() == ::DialogResult::OK){
				buttonSecret->ForeColor = colorDialog1->Color;
			}
		}

		System::Void textBoxGameExe_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			e->Effect = DragDropEffects::None;

			if(e->Data->GetDataPresent(DataFormats::FileDrop)){
				array<String^>^ file = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop, false));
				String^ extension = Path::GetExtension(file[0])->ToLower();
				FileVersionInfo^ info = FileVersionInfo::GetVersionInfo(file[0]);

				if(extension == ".exe" && info->FileDescription == "２Ｄ格闘ツクール2nd."){
					e->Effect = DragDropEffects::All;
				}
			}
		}

		System::Void textBoxGameExe_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			if(e->Data->GetDataPresent(DataFormats::FileDrop)){
				textBoxGameExe->Text = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop, false))[0];
			}
		}

		System::Void textBoxReplayFolder_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			e->Effect = DragDropEffects::None;

			if(e->Data->GetDataPresent(DataFormats::FileDrop)){
				array<String^>^ file = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop, false));
				String^ extension = Path::GetExtension(file[0]);

				if(extension == String::Empty){
					e->Effect = DragDropEffects::All;
				}
			}
		}

		System::Void textBoxReplayFolder_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			if(e->Data->GetDataPresent(DataFormats::FileDrop)){
				textBoxReplayFolder->Text = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop, false))[0];
			}
		}

		System::Void textBoxVSSound_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			e->Effect = DragDropEffects::None;

			if(e->Data->GetDataPresent(DataFormats::FileDrop)){
				array<String^>^ file = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop, false));
				String^ extension = Path::GetExtension(file[0])->ToLower();

				if(extension == ".wav"){
					e->Effect = DragDropEffects::All;
				}
			}
		}

		System::Void textBoxVSSound_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			if(e->Data->GetDataPresent(DataFormats::FileDrop)){
				textBoxVSSound->Text = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop, false))[0];
			}
		}

		System::Void textBoxNoticeSound_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			e->Effect = DragDropEffects::None;

			if(e->Data->GetDataPresent(DataFormats::FileDrop)){
				array<String^>^ file = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop, false));
				String^ extension = Path::GetExtension(file[0])->ToLower();

				if(extension == ".wav"){
					e->Effect = DragDropEffects::All;
				}
			}
		}

		System::Void textBoxNoticeSound_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
			if(e->Data->GetDataPresent(DataFormats::FileDrop)){
				textBoxNoticeSound->Text = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop, false))[0];
			}
		}
};
}

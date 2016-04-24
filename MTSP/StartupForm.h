#pragma once

#include "stdafx.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace MTSP {

	/// <summary>
	/// StartupForm の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class StartupForm : public System::Windows::Forms::Form
	{
	public:
		StartupForm(void)
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
		‾StartupForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^  radioButtonServer;
	private: System::Windows::Forms::RadioButton^  radioButtonHost;
	private: System::Windows::Forms::RadioButton^  radioButtonClient;
	private: System::Windows::Forms::Label^  labelIP;
	private: System::Windows::Forms::TextBox^  textBoxIP;
	private: System::Windows::Forms::Label^  labelOpenPort;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownOpenPort;

	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::TabControl^  tabControlStartUp;
	private: System::Windows::Forms::TabPage^  tabPageMode;
	private: System::Windows::Forms::TabPage^  tabPageOption;
	private: System::Windows::Forms::TabPage^  tabPageWelcome;

	private: System::Windows::Forms::Label^  labelName;
	private: System::Windows::Forms::TextBox^  textBoxName;
	private: System::Windows::Forms::Label^  labelPort;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownPort;
	private: System::Windows::Forms::Label^  labelMaxConnection;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownMaxConnection;

	private: System::Windows::Forms::RichTextBox^  richTextBoxWelcome;
	private: System::Windows::Forms::Label^  labelComment;
	private: System::Windows::Forms::TextBox^  textBoxComment;
	private: System::Windows::Forms::TabPage^  tabPageCipher;
	private: System::Windows::Forms::Button^  buttonEncryption;
	private: System::Windows::Forms::TextBox^  textBoxAfterIP;
	private: System::Windows::Forms::TextBox^  textBoxBeforeIP;
	private: System::Windows::Forms::Label^  labelAfterIP;
	private: System::Windows::Forms::Label^  labelBeforeIP;
	private: System::Windows::Forms::CheckBox^  checkBoxDNS;

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
			this->radioButtonServer = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonHost = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonClient = (gcnew System::Windows::Forms::RadioButton());
			this->labelIP = (gcnew System::Windows::Forms::Label());
			this->textBoxIP = (gcnew System::Windows::Forms::TextBox());
			this->labelOpenPort = (gcnew System::Windows::Forms::Label());
			this->numericUpDownOpenPort = (gcnew System::Windows::Forms::NumericUpDown());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->tabControlStartUp = (gcnew System::Windows::Forms::TabControl());
			this->tabPageMode = (gcnew System::Windows::Forms::TabPage());
			this->checkBoxDNS = (gcnew System::Windows::Forms::CheckBox());
			this->tabPageOption = (gcnew System::Windows::Forms::TabPage());
			this->textBoxComment = (gcnew System::Windows::Forms::TextBox());
			this->labelComment = (gcnew System::Windows::Forms::Label());
			this->labelPort = (gcnew System::Windows::Forms::Label());
			this->numericUpDownMaxConnection = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelMaxConnection = (gcnew System::Windows::Forms::Label());
			this->textBoxName = (gcnew System::Windows::Forms::TextBox());
			this->labelName = (gcnew System::Windows::Forms::Label());
			this->numericUpDownPort = (gcnew System::Windows::Forms::NumericUpDown());
			this->tabPageWelcome = (gcnew System::Windows::Forms::TabPage());
			this->richTextBoxWelcome = (gcnew System::Windows::Forms::RichTextBox());
			this->tabPageCipher = (gcnew System::Windows::Forms::TabPage());
			this->buttonEncryption = (gcnew System::Windows::Forms::Button());
			this->textBoxAfterIP = (gcnew System::Windows::Forms::TextBox());
			this->textBoxBeforeIP = (gcnew System::Windows::Forms::TextBox());
			this->labelAfterIP = (gcnew System::Windows::Forms::Label());
			this->labelBeforeIP = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownOpenPort))->BeginInit();
			this->tabControlStartUp->SuspendLayout();
			this->tabPageMode->SuspendLayout();
			this->tabPageOption->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownMaxConnection))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownPort))->BeginInit();
			this->tabPageWelcome->SuspendLayout();
			this->tabPageCipher->SuspendLayout();
			this->SuspendLayout();
			// 
			// radioButtonServer
			// 
			this->radioButtonServer->AutoSize = true;
			this->radioButtonServer->Location = System::Drawing::Point(4, 10);
			this->radioButtonServer->Name = L"radioButtonServer";
			this->radioButtonServer->Size = System::Drawing::Size(56, 16);
			this->radioButtonServer->TabIndex = 1;
			this->radioButtonServer->Text = L"Server";
			this->radioButtonServer->UseVisualStyleBackColor = true;
			this->radioButtonServer->CheckedChanged += gcnew System::EventHandler(this, &StartupForm::radioButtonServer_CheckedChanged);
			// 
			// radioButtonHost
			// 
			this->radioButtonHost->AutoSize = true;
			this->radioButtonHost->Location = System::Drawing::Point(4, 34);
			this->radioButtonHost->Name = L"radioButtonHost";
			this->radioButtonHost->Size = System::Drawing::Size(47, 16);
			this->radioButtonHost->TabIndex = 1;
			this->radioButtonHost->Text = L"Host";
			this->radioButtonHost->UseVisualStyleBackColor = true;
			this->radioButtonHost->CheckedChanged += gcnew System::EventHandler(this, &StartupForm::radioButtonHost_CheckedChanged);
			// 
			// radioButtonClient
			// 
			this->radioButtonClient->AutoSize = true;
			this->radioButtonClient->Location = System::Drawing::Point(4, 58);
			this->radioButtonClient->Name = L"radioButtonClient";
			this->radioButtonClient->Size = System::Drawing::Size(53, 16);
			this->radioButtonClient->TabIndex = 1;
			this->radioButtonClient->Text = L"Client";
			this->radioButtonClient->UseVisualStyleBackColor = true;
			this->radioButtonClient->CheckedChanged += gcnew System::EventHandler(this, &StartupForm::radioButtonClient_CheckedChanged);
			// 
			// labelIP
			// 
			this->labelIP->AutoSize = true;
			this->labelIP->Location = System::Drawing::Point(72, 16);
			this->labelIP->Name = L"labelIP";
			this->labelIP->Size = System::Drawing::Size(104, 12);
			this->labelIP->TabIndex = 0;
			this->labelIP->Text = L"Server名 or 接続先";
			// 
			// textBoxIP
			// 
			this->textBoxIP->Location = System::Drawing::Point(72, 32);
			this->textBoxIP->Name = L"textBoxIP";
			this->textBoxIP->Size = System::Drawing::Size(204, 19);
			this->textBoxIP->TabIndex = 2;
			// 
			// labelOpenPort
			// 
			this->labelOpenPort->AutoSize = true;
			this->labelOpenPort->Location = System::Drawing::Point(152, 60);
			this->labelOpenPort->Name = L"labelOpenPort";
			this->labelOpenPort->Size = System::Drawing::Size(57, 12);
			this->labelOpenPort->TabIndex = 0;
			this->labelOpenPort->Text = L"開放ポート";
			// 
			// numericUpDownOpenPort
			// 
			this->numericUpDownOpenPort->Location = System::Drawing::Point(212, 56);
			this->numericUpDownOpenPort->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {65535, 0, 0, 0});
			this->numericUpDownOpenPort->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1024, 0, 0, 0});
			this->numericUpDownOpenPort->Name = L"numericUpDownOpenPort";
			this->numericUpDownOpenPort->Size = System::Drawing::Size(64, 19);
			this->numericUpDownOpenPort->TabIndex = 4;
			this->numericUpDownOpenPort->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {7500, 0, 0, 0});
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(136, 108);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(68, 24);
			this->buttonOK->TabIndex = 6;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &StartupForm::buttonOK_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Location = System::Drawing::Point(208, 108);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(68, 24);
			this->buttonCancel->TabIndex = 7;
			this->buttonCancel->Text = L"フリープレイ";
			this->buttonCancel->UseVisualStyleBackColor = true;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &StartupForm::buttonCancel_Click);
			// 
			// tabControlStartUp
			// 
			this->tabControlStartUp->Controls->Add(this->tabPageMode);
			this->tabControlStartUp->Controls->Add(this->tabPageOption);
			this->tabControlStartUp->Controls->Add(this->tabPageWelcome);
			this->tabControlStartUp->Controls->Add(this->tabPageCipher);
			this->tabControlStartUp->Dock = System::Windows::Forms::DockStyle::Top;
			this->tabControlStartUp->Location = System::Drawing::Point(0, 0);
			this->tabControlStartUp->Name = L"tabControlStartUp";
			this->tabControlStartUp->SelectedIndex = 0;
			this->tabControlStartUp->Size = System::Drawing::Size(289, 104);
			this->tabControlStartUp->TabIndex = 0;
			// 
			// tabPageMode
			// 
			this->tabPageMode->Controls->Add(this->checkBoxDNS);
			this->tabPageMode->Controls->Add(this->labelIP);
			this->tabPageMode->Controls->Add(this->labelOpenPort);
			this->tabPageMode->Controls->Add(this->radioButtonServer);
			this->tabPageMode->Controls->Add(this->numericUpDownOpenPort);
			this->tabPageMode->Controls->Add(this->radioButtonHost);
			this->tabPageMode->Controls->Add(this->radioButtonClient);
			this->tabPageMode->Controls->Add(this->textBoxIP);
			this->tabPageMode->Location = System::Drawing::Point(4, 21);
			this->tabPageMode->Name = L"tabPageMode";
			this->tabPageMode->Padding = System::Windows::Forms::Padding(3);
			this->tabPageMode->Size = System::Drawing::Size(281, 79);
			this->tabPageMode->TabIndex = 0;
			this->tabPageMode->Text = L"モード選択";
			this->tabPageMode->UseVisualStyleBackColor = true;
			// 
			// checkBoxDNS
			// 
			this->checkBoxDNS->AutoSize = true;
			this->checkBoxDNS->Location = System::Drawing::Point(72, 58);
			this->checkBoxDNS->Name = L"checkBoxDNS";
			this->checkBoxDNS->Size = System::Drawing::Size(47, 16);
			this->checkBoxDNS->TabIndex = 3;
			this->checkBoxDNS->Text = L"DNS";
			this->checkBoxDNS->UseVisualStyleBackColor = true;
			// 
			// tabPageOption
			// 
			this->tabPageOption->Controls->Add(this->textBoxComment);
			this->tabPageOption->Controls->Add(this->labelComment);
			this->tabPageOption->Controls->Add(this->labelPort);
			this->tabPageOption->Controls->Add(this->numericUpDownMaxConnection);
			this->tabPageOption->Controls->Add(this->labelMaxConnection);
			this->tabPageOption->Controls->Add(this->textBoxName);
			this->tabPageOption->Controls->Add(this->labelName);
			this->tabPageOption->Controls->Add(this->numericUpDownPort);
			this->tabPageOption->Location = System::Drawing::Point(4, 21);
			this->tabPageOption->Name = L"tabPageOption";
			this->tabPageOption->Padding = System::Windows::Forms::Padding(3);
			this->tabPageOption->Size = System::Drawing::Size(281, 79);
			this->tabPageOption->TabIndex = 1;
			this->tabPageOption->Text = L"オプション";
			this->tabPageOption->UseVisualStyleBackColor = true;
			// 
			// textBoxComment
			// 
			this->textBoxComment->Location = System::Drawing::Point(72, 32);
			this->textBoxComment->Name = L"textBoxComment";
			this->textBoxComment->Size = System::Drawing::Size(204, 19);
			this->textBoxComment->TabIndex = 2;
			// 
			// labelComment
			// 
			this->labelComment->AutoSize = true;
			this->labelComment->Location = System::Drawing::Point(4, 36);
			this->labelComment->Name = L"labelComment";
			this->labelComment->Size = System::Drawing::Size(38, 12);
			this->labelComment->TabIndex = 4;
			this->labelComment->Text = L"コメント";
			// 
			// labelPort
			// 
			this->labelPort->AutoSize = true;
			this->labelPort->Location = System::Drawing::Point(152, 60);
			this->labelPort->Name = L"labelPort";
			this->labelPort->Size = System::Drawing::Size(57, 12);
			this->labelPort->TabIndex = 0;
			this->labelPort->Text = L"接続ポート";
			// 
			// numericUpDownMaxConnection
			// 
			this->numericUpDownMaxConnection->Location = System::Drawing::Point(72, 56);
			this->numericUpDownMaxConnection->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownMaxConnection->Name = L"numericUpDownMaxConnection";
			this->numericUpDownMaxConnection->Size = System::Drawing::Size(40, 19);
			this->numericUpDownMaxConnection->TabIndex = 3;
			this->numericUpDownMaxConnection->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// labelMaxConnection
			// 
			this->labelMaxConnection->AutoSize = true;
			this->labelMaxConnection->Location = System::Drawing::Point(4, 60);
			this->labelMaxConnection->Name = L"labelMaxConnection";
			this->labelMaxConnection->Size = System::Drawing::Size(65, 12);
			this->labelMaxConnection->TabIndex = 0;
			this->labelMaxConnection->Text = L"最大接続数";
			// 
			// textBoxName
			// 
			this->textBoxName->Location = System::Drawing::Point(72, 8);
			this->textBoxName->Name = L"textBoxName";
			this->textBoxName->Size = System::Drawing::Size(204, 19);
			this->textBoxName->TabIndex = 1;
			// 
			// labelName
			// 
			this->labelName->AutoSize = true;
			this->labelName->Location = System::Drawing::Point(4, 12);
			this->labelName->Name = L"labelName";
			this->labelName->Size = System::Drawing::Size(59, 12);
			this->labelName->TabIndex = 0;
			this->labelName->Text = L"ニックネーム";
			// 
			// numericUpDownPort
			// 
			this->numericUpDownPort->Location = System::Drawing::Point(212, 56);
			this->numericUpDownPort->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {65535, 0, 0, 0});
			this->numericUpDownPort->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1024, 0, 0, 0});
			this->numericUpDownPort->Name = L"numericUpDownPort";
			this->numericUpDownPort->Size = System::Drawing::Size(64, 19);
			this->numericUpDownPort->TabIndex = 4;
			this->numericUpDownPort->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {7500, 0, 0, 0});
			// 
			// tabPageWelcome
			// 
			this->tabPageWelcome->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tabPageWelcome->Controls->Add(this->richTextBoxWelcome);
			this->tabPageWelcome->Location = System::Drawing::Point(4, 21);
			this->tabPageWelcome->Name = L"tabPageWelcome";
			this->tabPageWelcome->Padding = System::Windows::Forms::Padding(3);
			this->tabPageWelcome->Size = System::Drawing::Size(281, 79);
			this->tabPageWelcome->TabIndex = 2;
			this->tabPageWelcome->Text = L"Welcomeメッセージ";
			this->tabPageWelcome->UseVisualStyleBackColor = true;
			// 
			// richTextBoxWelcome
			// 
			this->richTextBoxWelcome->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBoxWelcome->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBoxWelcome->Location = System::Drawing::Point(3, 3);
			this->richTextBoxWelcome->MaxLength = 127;
			this->richTextBoxWelcome->Name = L"richTextBoxWelcome";
			this->richTextBoxWelcome->Size = System::Drawing::Size(273, 71);
			this->richTextBoxWelcome->TabIndex = 1;
			this->richTextBoxWelcome->Text = L"";
			// 
			// tabPageCipher
			// 
			this->tabPageCipher->Controls->Add(this->buttonEncryption);
			this->tabPageCipher->Controls->Add(this->textBoxAfterIP);
			this->tabPageCipher->Controls->Add(this->textBoxBeforeIP);
			this->tabPageCipher->Controls->Add(this->labelAfterIP);
			this->tabPageCipher->Controls->Add(this->labelBeforeIP);
			this->tabPageCipher->Location = System::Drawing::Point(4, 21);
			this->tabPageCipher->Name = L"tabPageCipher";
			this->tabPageCipher->Padding = System::Windows::Forms::Padding(3);
			this->tabPageCipher->Size = System::Drawing::Size(281, 79);
			this->tabPageCipher->TabIndex = 3;
			this->tabPageCipher->Text = L"IPの変換";
			this->tabPageCipher->UseVisualStyleBackColor = true;
			// 
			// buttonEncryption
			// 
			this->buttonEncryption->Location = System::Drawing::Point(132, 32);
			this->buttonEncryption->Name = L"buttonEncryption";
			this->buttonEncryption->Size = System::Drawing::Size(84, 20);
			this->buttonEncryption->TabIndex = 2;
			this->buttonEncryption->Text = L"変換する";
			this->buttonEncryption->UseVisualStyleBackColor = true;
			this->buttonEncryption->Click += gcnew System::EventHandler(this, &StartupForm::buttonEncryption_Click);
			// 
			// textBoxAfterIP
			// 
			this->textBoxAfterIP->Location = System::Drawing::Point(72, 56);
			this->textBoxAfterIP->Name = L"textBoxAfterIP";
			this->textBoxAfterIP->ReadOnly = true;
			this->textBoxAfterIP->Size = System::Drawing::Size(204, 19);
			this->textBoxAfterIP->TabIndex = 3;
			// 
			// textBoxBeforeIP
			// 
			this->textBoxBeforeIP->Location = System::Drawing::Point(72, 8);
			this->textBoxBeforeIP->Name = L"textBoxBeforeIP";
			this->textBoxBeforeIP->Size = System::Drawing::Size(204, 19);
			this->textBoxBeforeIP->TabIndex = 1;
			this->textBoxBeforeIP->TextChanged += gcnew System::EventHandler(this, &StartupForm::textBoxBeforeIP_TextChanged);
			// 
			// labelAfterIP
			// 
			this->labelAfterIP->AutoSize = true;
			this->labelAfterIP->Location = System::Drawing::Point(4, 60);
			this->labelAfterIP->Name = L"labelAfterIP";
			this->labelAfterIP->Size = System::Drawing::Size(61, 12);
			this->labelAfterIP->TabIndex = 0;
			this->labelAfterIP->Text = L"変換後のIP";
			// 
			// labelBeforeIP
			// 
			this->labelBeforeIP->AutoSize = true;
			this->labelBeforeIP->Location = System::Drawing::Point(4, 12);
			this->labelBeforeIP->Name = L"labelBeforeIP";
			this->labelBeforeIP->Size = System::Drawing::Size(61, 12);
			this->labelBeforeIP->TabIndex = 0;
			this->labelBeforeIP->Text = L"変換前のIP";
			// 
			// StartupForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->buttonCancel;
			this->ClientSize = System::Drawing::Size(289, 137);
			this->ControlBox = false;
			this->Controls->Add(this->tabControlStartUp);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->buttonCancel);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"StartupForm";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"スタートアップ";
			this->Load += gcnew System::EventHandler(this, &StartupForm::StartupForm_Load);
			this->Shown += gcnew System::EventHandler(this, &StartupForm::StartupForm_Shown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownOpenPort))->EndInit();
			this->tabControlStartUp->ResumeLayout(false);
			this->tabPageMode->ResumeLayout(false);
			this->tabPageMode->PerformLayout();
			this->tabPageOption->ResumeLayout(false);
			this->tabPageOption->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownMaxConnection))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownPort))->EndInit();
			this->tabPageWelcome->ResumeLayout(false);
			this->tabPageCipher->ResumeLayout(false);
			this->tabPageCipher->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		System::Void StartupForm_Load(System::Object^  sender, System::EventArgs^  e) {
			textBoxIP->MaxLength      = MAX_NAME;
			textBoxName->MaxLength    = MAX_NAME;
			textBoxComment->MaxLength = MAX_NAME;

			switch(MTOPTION.CONNECTION_TYPE){
			case CT_SERVER:
			default:
				radioButtonServer->Checked = true;
				labelIP->Text = gcnew String("Server名を入力してください");

				numericUpDownPort->Enabled = false;
				break;
			case CT_HOST:
				radioButtonHost->Checked = true;
				labelIP->Text = gcnew String("接続先IPを入力してください");

				richTextBoxWelcome->Enabled = false;
				break;
			case CT_CLIENT:
				radioButtonClient->Checked = true;
				labelIP->Text = gcnew String("接続先IPを入力してください");

				numericUpDownOpenPort->Enabled = false;
				richTextBoxWelcome->Enabled    = false;
				break;
			}

			textBoxIP->Text = gcnew String(MTOPTION.CONNECTION_IP);
			numericUpDownOpenPort->Value = MTOPTION.OPEN_PORT;
			checkBoxDNS->Checked = MTOPTION.DNS;

			textBoxName->Text = gcnew String(MTOPTION.NAME);
			numericUpDownPort->Value = MTOPTION.PORT;
			numericUpDownMaxConnection->Value = MTOPTION.MAX_CONNECTION;

			textBoxComment->Text = gcnew String(MTOPTION.COMMENT);
			richTextBoxWelcome->Text = gcnew String(MTOPTION.WELCOME);
		}

		System::Void StartupForm_Shown(System::Object^  sender, System::EventArgs^  e) {
			buttonOK->Focus();
		}

		System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
			IntPtr mp;

			if(radioButtonServer->Checked){
				MTOPTION.CONNECTION_TYPE = CT_SERVER;
			}
			else if(radioButtonHost->Checked){
				MTOPTION.CONNECTION_TYPE = CT_HOST;
			}
			else if(radioButtonClient->Checked){
				MTOPTION.CONNECTION_TYPE = CT_CLIENT;
			}
			else{
				MTOPTION.CONNECTION_TYPE = CT_FREE;
			}

			mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxIP->Text);
			_tcscpy_s(MTOPTION.CONNECTION_IP, static_cast<PTCHAR>(mp.ToPointer()));
			Runtime::InteropServices::Marshal::FreeHGlobal(mp);

			// 名前チェック
			if(textBoxName->Text->Length == 0){
				textBoxName->Text = gcnew String(MTOPTION.NAME);

				if(textBoxName->Text->Length == 0){
					textBoxName->Text = gcnew String("名無しさん");
				}
			}

			mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxName->Text);
			_tcscpy_s(MTOPTION.NAME, static_cast<PTCHAR>(mp.ToPointer()));
			Runtime::InteropServices::Marshal::FreeHGlobal(mp);

			MTOPTION.OPEN_PORT      = (UINT)numericUpDownOpenPort->Value;
			MTOPTION.PORT           = (UINT)numericUpDownPort->Value;
			MTOPTION.MAX_CONNECTION = (UINT)numericUpDownMaxConnection->Value;

			MTOPTION.DNS = checkBoxDNS->Checked;

			mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxComment->Text);
			_tcscpy_s(MTOPTION.COMMENT, static_cast<PTCHAR>(mp.ToPointer()));
			Runtime::InteropServices::Marshal::FreeHGlobal(mp);

			mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(richTextBoxWelcome->Text);
			_tcscpy_s(MTOPTION.WELCOME, static_cast<PTCHAR>(mp.ToPointer()));
			Runtime::InteropServices::Marshal::FreeHGlobal(mp);

			this->Close();
		}

		System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
			MTOPTION.CONNECTION_TYPE = CT_FREE;

			this->Close();
		}

		System::Void radioButtonServer_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			labelIP->Text = gcnew String("Server名を入力してください");
			numericUpDownOpenPort->Enabled = true;
			numericUpDownPort->Enabled     = false;
			checkBoxDNS->Enabled           = false;
			richTextBoxWelcome->Enabled    = true;

			buttonOK->Enabled = true;
		}

		System::Void radioButtonHost_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			labelIP->Text = gcnew String("接続先を入力してください");
			numericUpDownOpenPort->Enabled = true;
			numericUpDownPort->Enabled     = true;
			checkBoxDNS->Enabled           = true;
			richTextBoxWelcome->Enabled    = false;
		}

		System::Void radioButtonClient_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			labelIP->Text = gcnew String("接続先を入力してください");
			numericUpDownOpenPort->Enabled = false;
			numericUpDownPort->Enabled     = true;
			checkBoxDNS->Enabled           = true;
			richTextBoxWelcome->Enabled    = false;
		}

		System::Void textBoxBeforeIP_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			if(Net::IPAddress::TryParse(textBoxBeforeIP->Text, gcnew Net::IPAddress(0)) == false){
				buttonEncryption->Enabled = false;
			}
			else{
				buttonEncryption->Enabled = true;
			}
		}

		System::Void buttonEncryption_Click(System::Object^  sender, System::EventArgs^  e) {
			textBoxAfterIP->Text = EncryptionIP(textBoxBeforeIP->Text);
			textBoxBeforeIP->Text = Net::IPAddress(DecryptionIP(textBoxAfterIP->Text)).ToString();
		}
};
}

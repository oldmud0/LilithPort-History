#include "stdafx.h"
#include "OptionForm.h"
#include "MainForm.h"

using namespace LilithPort;

void OptionForm::SaveOption(bool apply){
	MainForm^ parent = safe_cast<MainForm^>(this->Owner);

	try{
		FileVersionInfo^ info = FileVersionInfo::GetVersionInfo(textBoxGameExe->Text);

		if(info->FileDescription != "２Ｄ格闘ツクール2nd." && info->FileDescription != "２Ｄ格闘ツクール９５"){
			throw gcnew Exception;
		}
	}
	catch(Exception^){
		textBoxGameExe->Text = gcnew String("格闘ツクールの実行ファイルではありません");
	}

	IntPtr mp;

	// パス
	mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxGameExe->Text);
	_tcscpy_s(MTOPTION.GAME_EXE, static_cast<PTCHAR>(mp.ToPointer()));
	Runtime::InteropServices::Marshal::FreeHGlobal(mp);

	mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxReplayFolder->Text);
	_tcscpy_s(MTOPTION.REPLAY_FOLDER, static_cast<PTCHAR>(mp.ToPointer()));
	Runtime::InteropServices::Marshal::FreeHGlobal(mp);

	mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxVSSound->Text);
	_tcscpy_s(MTOPTION.VS_SOUND, static_cast<PTCHAR>(mp.ToPointer()));
	Runtime::InteropServices::Marshal::FreeHGlobal(mp);

	mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxNoticeSound->Text);
	_tcscpy_s(MTOPTION.NOTICE_SOUND, static_cast<PTCHAR>(mp.ToPointer()));
	Runtime::InteropServices::Marshal::FreeHGlobal(mp);

	mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxEnterSound->Text);
	_tcscpy_s(MTOPTION.ENTER_SOUND, static_cast<PTCHAR>(mp.ToPointer()));
	Runtime::InteropServices::Marshal::FreeHGlobal(mp);

	mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(KeywordSoundtextBox->Text);
	_tcscpy_s(MTOPTION.KEYWORD_SOUND, static_cast<PTCHAR>(mp.ToPointer()));
	Runtime::InteropServices::Marshal::FreeHGlobal(mp);

	// コメント
	if(textBoxComment->Text != gcnew String(MTOPTION.COMMENT)){
		mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxComment->Text);
		_tcscpy_s(MTOPTION.COMMENT, static_cast<PTCHAR>(mp.ToPointer()));
		Runtime::InteropServices::Marshal::FreeHGlobal(mp);

		parent->ChangeComment(textBoxComment->Text);
	}

	// ゲーム
	MTOPTION.MAX_STAGE      = (UINT)numericUpDownMaxStage->Value;
	MTOPTION.STAGE_SELECT   = (UINT)numericUpDownStageSelect->Value;
	MTOPTION.ROUND          = (UINT)numericUpDownRound->Value;
	MTOPTION.TIMER          = (UINT)numericUpDownTimer->Value;
	MTOPTION.SIMULATE_DELAY = (UINT)numericUpDownSimDelay->Value;

	MTOPTION.DISPLAY_NAME      = checkBoxName->Checked;
	MTOPTION.DISPLAY_VERSUS    = checkBoxVersus->Checked;
	MTOPTION.DISPLAY_FRAMERATE = checkBoxFramerate->Checked;
	MTOPTION.DISPLAY_RAND      = checkBoxRand->Checked;

	MTOPTION.REPLAY_DIVIDE      = checkBoxDivide->Checked;
	MTOPTION.CHANGE_WINDOW_SIZE = checkBoxWindowSize->Checked;

	MTOPTION.MAX_CONNECTION = (UINT)numericUpDownMaxConnection->Value;
	MTOPTION.BGM_VOLUME     = (UINT)trackBarBGM->Value * 5;
	MTOPTION.SE_VOLUME      = (UINT)trackBarSE->Value * 5;

	if(radioButtonReplayVersion2->Checked){
		MTOPTION.REPLAY_VERSION = 2;
	}
	else{
		MTOPTION.REPLAY_VERSION = 1;
	}

	// 当たり判定
	if(MTOPTION.HIT_JUDGE != checkBoxHitJudge->Checked){
		MTOPTION.HIT_JUDGE = checkBoxHitJudge->Checked;

		// ゲーム起動中なら即時変更
		if(MTINFO.INITIALIZED && MTINFO.PROCESS != NULL){
			DWORD b = MTOPTION.HIT_JUDGE;

			if(MTINFO.KGT2K){
				WriteProcessMemory(MTINFO.PROCESS, (LPVOID)HIT_JUDGE, &b, 4, NULL);
			}
			else{
				WriteProcessMemory(MTINFO.PROCESS, (LPVOID)HIT_JUDGE_95, &b, 4, NULL);
			}
		}
	}

	//　色
	MTCOLOR.SERVER_NAME    = buttonServerName->ForeColor.ToArgb();
	MTCOLOR.HOST_NAME      = buttonHostName->ForeColor.ToArgb();
	MTCOLOR.CLIENT_NAME    = buttonClientName->ForeColor.ToArgb();
	MTCOLOR.REST_STATE     = buttonRestState->BackColor.ToArgb();
	MTCOLOR.VS_STATE       = buttonVSState->BackColor.ToArgb();
	MTCOLOR.WATCH_STATE    = buttonWatchState->BackColor.ToArgb();
	MTCOLOR.SYSTEM_MESSAGE = buttonSystemMessage->ForeColor.ToArgb();
	MTCOLOR.ERROR_MESSAGE  = buttonErrorMessage->ForeColor.ToArgb();
	MTCOLOR.DEBUG_MESSAGE  = buttonDebugMessage->ForeColor.ToArgb();
	MTCOLOR.NOTICE_BACK    = buttonNoticeBack->BackColor.ToArgb();
	MTCOLOR.COMMENT_BACK   = buttonCommentBack->BackColor.ToArgb();
	MTCOLOR.SECRET         = buttonSecret->ForeColor.ToArgb();

	// 色を反映させる
	parent->ResetColor();

	// 値のチェック
	CheckMTOption();

	if(apply){
		textBoxGameExe->Text      = gcnew String(MTOPTION.GAME_EXE);
		textBoxReplayFolder->Text = gcnew String(MTOPTION.REPLAY_FOLDER);
		textBoxVSSound->Text      = gcnew String(MTOPTION.VS_SOUND);
		textBoxNoticeSound->Text  = gcnew String(MTOPTION.NOTICE_SOUND);
		textBoxEnterSound->Text   = gcnew String(MTOPTION.ENTER_SOUND);
		KeywordSoundtextBox->Text = gcnew String(MTOPTION.KEYWORD_SOUND);
	}
}

#include "stdafx.h"
#include "option.h"
#include "Form1.h"

using namespace LunaPortMT;

void option::SaveOptions(bool apply){
	IntPtr mp;

	try{
		FileVersionInfo^ info = FileVersionInfo::GetVersionInfo(textBoxGameExe->Text);

		if(info->FileDescription != "２Ｄ格闘ツクール2nd."){
			throw gcnew Exception;
		}
	}
	catch(Exception^){
		textBoxGameExe->Text = gcnew String("2D格闘ツクール2nd.の実行ファイルではありません");
	}

	// パス
	mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxGameExe->Text);
	_tcscpy_s(LPMTOPTION.GAME_EXE, static_cast<PTCHAR>(mp.ToPointer()));
	Runtime::InteropServices::Marshal::FreeHGlobal(mp);

	mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxReplayFolder->Text);
	_tcscpy_s(LPMTOPTION.REPLAY_FOLDER, static_cast<PTCHAR>(mp.ToPointer()));
	Runtime::InteropServices::Marshal::FreeHGlobal(mp);

	mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxVSSound->Text);
	_tcscpy_s(LPMTOPTION.VS_SOUND, static_cast<PTCHAR>(mp.ToPointer()));
	Runtime::InteropServices::Marshal::FreeHGlobal(mp);

	mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(textBoxNoticeSound->Text);
	_tcscpy_s(LPMTOPTION.NOTICE_SOUND, static_cast<PTCHAR>(mp.ToPointer()));
	Runtime::InteropServices::Marshal::FreeHGlobal(mp);

	// ゲーム
	LPMTOPTION.MAX_STAGES   = (UINT)numericUpDownMaxStages->Value;
	LPMTOPTION.STAGE_SELECT = (UINT)numericUpDownStageSelect->Value;
	LPMTOPTION.TIME_LIMIT   = (UINT)numericUpDownTime->Value;

	LPMTOPTION.DISPLAY_NAMES     = checkBoxName->Checked;
	LPMTOPTION.DISPLAY_VERSUS    = checkBoxVersus->Checked;
	LPMTOPTION.DISPLAY_FRAMERATE = checkBoxFramerate->Checked;
	LPMTOPTION.DISPLAY_INPUTRATE = checkBoxInputrate->Checked;

	LPMTOPTION.REPLAY_DIVIDE      = checkBoxDivide->Checked;
	LPMTOPTION.CHANGE_WINDOW_SIZE = checkBoxWindowSize->Checked;

	LPMTOPTION.MAX_CONNECTIONS = (UINT)numericUpDownMaxConnections->Value;

	if(radioButtonReplayVersion2->Checked){
		LPMTOPTION.REPLAY_VERSION = 2;
	}
	else{
		LPMTOPTION.REPLAY_VERSION = 1;
	}

	// 当たり判定
	if(LPMTOPTION.HIT_JUDGE != checkBoxHitJudge->Checked){
		LPMTOPTION.HIT_JUDGE = checkBoxHitJudge->Checked;

		// ゲーム起動中なら即時変更
		if(LUNAPORT.INITIALIZED && LUNAPORT.PROCESS != NULL){
			DWORD b = LPMTOPTION.HIT_JUDGE;

			WriteProcessMemory(LUNAPORT.PROCESS, (LPVOID)HIT_JUDGE, &b, 4, NULL);
			FlushInstructionCache(LUNAPORT.PROCESS, NULL, 0);
		}
	}

	//　色
	LPMTCOLOR.SERVER_NAME    = buttonServerName->ForeColor.ToArgb();
	LPMTCOLOR.HOST_NAME      = buttonHostName->ForeColor.ToArgb();
	LPMTCOLOR.CLIENT_NAME    = buttonClientName->ForeColor.ToArgb();
	LPMTCOLOR.REST_STATE     = buttonRestState->BackColor.ToArgb();
	LPMTCOLOR.VS_STATE       = buttonVSState->BackColor.ToArgb();
	LPMTCOLOR.WATCH_STATE    = buttonWatchState->BackColor.ToArgb();
	LPMTCOLOR.SYSTEM_MESSAGE = buttonSystemMessage->ForeColor.ToArgb();
	LPMTCOLOR.ERROR_MESSAGE  = buttonErrorMessage->ForeColor.ToArgb();
	LPMTCOLOR.DEBUG_MESSAGE  = buttonDebugMessage->ForeColor.ToArgb();
	LPMTCOLOR.NOTICE_BACK    = buttonNoticeBack->BackColor.ToArgb();
	LPMTCOLOR.COMMENT_BACK   = buttonCommentBack->BackColor.ToArgb();
	LPMTCOLOR.SECRET         = buttonSecret->ForeColor.ToArgb();

	// 色を反映させる
	Form1^ parent = safe_cast<Form1^>(this->Owner);
	parent->ResetColor();

	// 値のチェック
	CheckLPMTOptions();

	if(apply){
		textBoxGameExe->Text      = gcnew String(LPMTOPTION.GAME_EXE);
		textBoxReplayFolder->Text = gcnew String(LPMTOPTION.REPLAY_FOLDER);
		textBoxVSSound->Text      = gcnew String(LPMTOPTION.VS_SOUND);
		textBoxNoticeSound->Text  = gcnew String(LPMTOPTION.NOTICE_SOUND);

		numericUpDownStageSelect->Value = LPMTOPTION.STAGE_SELECT;
	}
}

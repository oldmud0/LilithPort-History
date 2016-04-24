// LunaPortMT.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"
#include "Form1.h"

using namespace LunaPortMT;

// グローバル
LUNA_PORT LUNAPORT;
LUNA_PORT_MT_OPTION LPMTOPTION;
LUNA_PORT_MT_WINDOW_STATE LPMTWS;
LUNA_PORT_MT_COLOR LPMTCOLOR;

CRITICAL_SECTION CS_CAPTION;

void LoadLPMTOptions();
void SaveLPMTOptions();
void CheckLPMTOptions();

void WriteErrorLog(String^ text, String^ caption)
{
	StreamWriter^ sw = gcnew StreamWriter(gcnew String(LPMTOPTION.PATH) + "error.log", true, Encoding::Default);
	try{
		sw->WriteLine("-------------------------------------------------------------------------------");
		sw->WriteLine("{0} {1} [{2}]", DateTime::Now.ToLongDateString(), DateTime::Now.ToLongTimeString(), caption);
		sw->WriteLine();
		sw->Write(text);
		sw->WriteLine();
		sw->WriteLine();
		sw->WriteLine();
	}
	finally{
		if(sw != nullptr){
			sw->Close();
			delete sw;
		}
	}
}

void ApplicationThreadException(Object^ sender, Threading::ThreadExceptionEventArgs^ e)
{
	WriteErrorLog(e->Exception->ToString(), "ThreadException");

	MessageBox::Show("突然ですがプログラム終了のお知らせです。", "緊急事態発生");

	Application::Exit();
}

void ApplicationUnhandledException(Object^ sender, UnhandledExceptionEventArgs^ e)
{
	WriteErrorLog(safe_cast<Exception^>(e->ExceptionObject)->ToString(), "UnhandledException");

	MessageBox::Show("突然ですがプログラム終了のお知らせです。", "例外が飛んできました");

	Application::Exit();
}

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// コントロールが作成される前に、Windows XP ビジュアル効果を有効にします
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// 自プログラムのパス
	TCHAR drive[_MAX_DRIVE], dir[_MAX_DIR];

	GetModuleFileName(NULL, LPMTOPTION.PATH, _MAX_PATH);
	_tsplitpath_s(LPMTOPTION.PATH, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0);
	_stprintf_s(LPMTOPTION.PATH, _T("%s%s"), drive, dir);

#ifdef _DEBUG
	LUNAPORT.DEBUG = true;
	LUNAPORT.CHECK_RAND = true;
#endif

	LoadLPMTOptions();
	CheckLPMTOptions();

	// 乱数の初期化＆まぜまぜ
	XorShift((UINT)DateTime::Now.Ticks);
	XorShift();
	XorShift();
	XorShift();

	InitializeCriticalSection(&CS_CAPTION);

	// 未処理の例外をキャッチ
	Application::ThreadException += gcnew ThreadExceptionEventHandler(ApplicationThreadException);
	Threading::Thread::GetDomain()->UnhandledException += gcnew UnhandledExceptionEventHandler(ApplicationUnhandledException);

	// メイン ウィンドウを作成して、実行します
	Application::Run(gcnew Form1());

	DeleteCriticalSection(&CS_CAPTION);

	SaveLPMTOptions();

	return 0;
}

void LoadLPMTOptions()
{
	TCHAR ini[_MAX_PATH];

	_stprintf_s(ini, _T("%sLunaPortMT.ini"), LPMTOPTION.PATH);

	LPMTOPTION.CONNECTION_TYPE = GetPrivateProfileInt(_T("LunaPortMT"), _T("ConnectType"), 0, ini);
	GetPrivateProfileString(_T("LunaPortMT"), _T("ConnectIP"),    _T(""),           LPMTOPTION.CONNECTION_IP,  MAX_NAME,  ini);
	GetPrivateProfileString(_T("LunaPortMT"), _T("Welcome"),      _T(""),           LPMTOPTION.WELCOME,        MAX_TITLE, ini);
	GetPrivateProfileString(_T("LunaPortMT"), _T("GameExe"),      _T("game.exe"),   LPMTOPTION.GAME_EXE,      _MAX_PATH,  ini);
	GetPrivateProfileString(_T("LunaPortMT"), _T("ReplayFolder"), _T("Replay"),     LPMTOPTION.REPLAY_FOLDER, _MAX_PATH,  ini);
	GetPrivateProfileString(_T("LunaPortMT"), _T("VSSound"),      _T("vs.wav"),     LPMTOPTION.VS_SOUND,      _MAX_PATH,  ini);
	GetPrivateProfileString(_T("LunaPortMT"), _T("NoticeSound"),  _T("notice.wav"), LPMTOPTION.NOTICE_SOUND,  _MAX_PATH,  ini);
	GetPrivateProfileString(_T("LunaPortMT"), _T("Name"),         _T("名無しさん"), LPMTOPTION.NAME,           MAX_NAME,  ini);
	GetPrivateProfileString(_T("LunaPortMT"), _T("Comment"),      _T(""),           LPMTOPTION.COMMENT,        MAX_NAME,  ini);
	LPMTOPTION.PORT               = GetPrivateProfileInt(_T("LunaPortMT"), _T("Port"),          7500, ini);
	LPMTOPTION.OPEN_PORT          = GetPrivateProfileInt(_T("LunaPortMT"), _T("OpenPort"),      7500, ini);
	LPMTOPTION.MAX_CONNECTIONS    = GetPrivateProfileInt(_T("LunaPortMT"), _T("MaxConnections"),   1, ini);
	LPMTOPTION.MAX_STAGES         = GetPrivateProfileInt(_T("LunaPortMT"), _T("MaxStages"),        1, ini);
	LPMTOPTION.STAGE_SELECT       = GetPrivateProfileInt(_T("LunaPortMT"), _T("StageSelect"),      0, ini);
	LPMTOPTION.TIME_LIMIT         = GetPrivateProfileInt(_T("LunaPortMT"), _T("TimeLimit"),        0, ini);
	LPMTOPTION.HIT_JUDGE          = GetPrivateProfileInt(_T("LunaPortMT"), _T("HitJudge"),         0, ini) == 1 ? true : false;
	LPMTOPTION.DISPLAY_NAMES      = GetPrivateProfileInt(_T("LunaPortMT"), _T("DisplayNames"),     0, ini) == 1 ? true : false;
	LPMTOPTION.DISPLAY_VERSUS     = GetPrivateProfileInt(_T("LunaPortMT"), _T("DisplayVersus"),    0, ini) == 1 ? true : false;
	LPMTOPTION.DISPLAY_FRAMERATE  = GetPrivateProfileInt(_T("LunaPortMT"), _T("DisplayFramerate"), 0, ini) == 1 ? true : false;
	LPMTOPTION.DISPLAY_INPUTRATE  = GetPrivateProfileInt(_T("LunaPortMT"), _T("DisplayInputrate"), 0, ini) == 1 ? true : false;
	LPMTOPTION.REPLAY_DIVIDE      = GetPrivateProfileInt(_T("LunaPortMT"), _T("ReplayDivide"),     0, ini) == 1 ? true : false;
	LPMTOPTION.CHANGE_WINDOW_SIZE = GetPrivateProfileInt(_T("LunaPortMT"), _T("ChangeWindowSize"), 0, ini) == 1 ? true : false;
	LPMTOPTION.CHAT_HISTORY       = GetPrivateProfileInt(_T("LunaPortMT"), _T("ChatHistory"),     20, ini);
	LPMTOPTION.DELAY              = GetPrivateProfileInt(_T("LunaPortMT"), _T("Delay"),            0, ini);
	LPMTOPTION.REPLAY_VERSION     = GetPrivateProfileInt(_T("LunaPortMT"), _T("ReplayVersion"),    2, ini);
	LPMTOPTION.RECORD_REPLAY      = GetPrivateProfileInt(_T("LunaPortMT"), _T("RecordReplay"),     0, ini) == 1 ? true : false;
	LPMTOPTION.ALLOW_SPECTATORS   = GetPrivateProfileInt(_T("LunaPortMT"), _T("AllowSpectators"),  0, ini) == 1 ? true : false;
	LPMTOPTION.AFTER_REST         = GetPrivateProfileInt(_T("LunaPortMT"), _T("AfterRest"),        0, ini) == 1 ? true : false;

	LPMTWS.LEFT        = GetPrivateProfileInt(_T("State"), _T("Left"),       0, ini);
	LPMTWS.TOP         = GetPrivateProfileInt(_T("State"), _T("Top"),        0, ini);
	LPMTWS.WIDTH       = GetPrivateProfileInt(_T("State"), _T("Width"),      0, ini);
	LPMTWS.HEIGHT      = GetPrivateProfileInt(_T("State"), _T("Height"),     0, ini);
	LPMTWS.SPLITTER    = GetPrivateProfileInt(_T("State"), _T("Splitter"),   0, ini);
	LPMTWS.DIALOG_LEFT = GetPrivateProfileInt(_T("State"), _T("DialogLeft"), 0, ini);
	LPMTWS.DIALOG_TOP  = GetPrivateProfileInt(_T("State"), _T("DialogTop"),  0, ini);

	LPMTCOLOR.SERVER_NAME    = GetPrivateProfileInt(_T("Color"), _T("ServerName"),    Color::ForestGreen.ToArgb(), ini);
	LPMTCOLOR.HOST_NAME      = GetPrivateProfileInt(_T("Color"), _T("HostName"),      Color::MediumBlue.ToArgb(),  ini);
	LPMTCOLOR.CLIENT_NAME    = GetPrivateProfileInt(_T("Color"), _T("ClientName"),    Color::Black.ToArgb(),       ini);
	LPMTCOLOR.REST_STATE     = GetPrivateProfileInt(_T("Color"), _T("RestState"),     Color::Khaki.ToArgb(),       ini);
	LPMTCOLOR.VS_STATE       = GetPrivateProfileInt(_T("Color"), _T("VSState"),       Color::Salmon.ToArgb(),      ini);
	LPMTCOLOR.WATCH_STATE    = GetPrivateProfileInt(_T("Color"), _T("WatchState"),    Color::PaleGreen.ToArgb(),   ini);
	LPMTCOLOR.SYSTEM_MESSAGE = GetPrivateProfileInt(_T("Color"), _T("SystemMessage"), Color::Teal.ToArgb(),        ini);
	LPMTCOLOR.ERROR_MESSAGE  = GetPrivateProfileInt(_T("Color"), _T("ErrorMessage"),  Color::Red.ToArgb(),         ini);
	LPMTCOLOR.DEBUG_MESSAGE  = GetPrivateProfileInt(_T("Color"), _T("DebugMessage"),  Color::DarkOrange.ToArgb(),  ini);
	LPMTCOLOR.NOTICE_BACK    = GetPrivateProfileInt(_T("Color"), _T("NoticeBack"),    Color::PowderBlue.ToArgb(),  ini);
	LPMTCOLOR.COMMENT_BACK   = GetPrivateProfileInt(_T("Color"), _T("CommentBack"),   Color::MistyRose.ToArgb(),   ini);
	LPMTCOLOR.SECRET         = GetPrivateProfileInt(_T("Color"), _T("Secret"),        Color::HotPink.ToArgb(),     ini);

	// Welcomeのタブを改行に
	int len = _tcslen(LPMTOPTION.WELCOME);

	for(int i = 0; i < len; i++){
		if(LPMTOPTION.WELCOME[i] == _T('¥t')){
			LPMTOPTION.WELCOME[i] = _T('¥n');
		}
	}
}

void SaveLPMTOptions()
{
	// 改行をタブに置換
	int len = _tcslen(LPMTOPTION.WELCOME);

	for(int i = 0; i < len; i++){
		if(LPMTOPTION.WELCOME[i] == _T('¥n')){
			LPMTOPTION.WELCOME[i] = _T('¥t');
		}
	}

	TCHAR ini[_MAX_PATH], buf[MAX_NAME];

	_stprintf_s(ini, _T("%sLunaPortMT.ini"), LPMTOPTION.PATH);

	_itot_s(LPMTOPTION.CONNECTION_TYPE, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("ConnectType"),  buf,                      ini);
	WritePrivateProfileString(_T("LunaPortMT"), _T("ConnectIP"),    LPMTOPTION.CONNECTION_IP, ini);
	WritePrivateProfileString(_T("LunaPortMT"), _T("Welcome"),      LPMTOPTION.WELCOME,       ini);
	WritePrivateProfileString(_T("LunaPortMT"), _T("GameExe"),      LPMTOPTION.GAME_EXE,      ini);
	WritePrivateProfileString(_T("LunaPortMT"), _T("ReplayFolder"), LPMTOPTION.REPLAY_FOLDER, ini);
	WritePrivateProfileString(_T("LunaPortMT"), _T("VSSound"),      LPMTOPTION.VS_SOUND,      ini);
	WritePrivateProfileString(_T("LunaPortMT"), _T("NoticeSound"),  LPMTOPTION.NOTICE_SOUND,  ini);
	WritePrivateProfileString(_T("LunaPortMT"), _T("Name"),         LPMTOPTION.NAME,          ini);
	WritePrivateProfileString(_T("LunaPortMT"), _T("Comment"),      LPMTOPTION.COMMENT,       ini);
	_itot_s(LPMTOPTION.PORT, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("Port"), buf, ini);
	_itot_s(LPMTOPTION.OPEN_PORT, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("OpenPort"), buf, ini);
	_itot_s(LPMTOPTION.MAX_CONNECTIONS, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("MaxConnections"), buf, ini);
	_itot_s(LPMTOPTION.MAX_STAGES, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("MaxStages"), buf, ini);
	_itot_s(LPMTOPTION.STAGE_SELECT, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("StageSelect"), buf, ini);
	_itot_s(LPMTOPTION.TIME_LIMIT, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("TimeLimit"), buf, ini);
	_itot_s(LPMTOPTION.HIT_JUDGE, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("HitJudge"), buf, ini);
	_itot_s(LPMTOPTION.DISPLAY_NAMES, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("DisplayNames"), buf, ini);
	_itot_s(LPMTOPTION.DISPLAY_VERSUS, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("DisplayVersus"), buf, ini);
	_itot_s(LPMTOPTION.DISPLAY_FRAMERATE, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("DisplayFramerate"), buf, ini);
	_itot_s(LPMTOPTION.DISPLAY_INPUTRATE, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("DisplayInputrate"), buf, ini);
	_itot_s(LPMTOPTION.REPLAY_DIVIDE, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("ReplayDivide"), buf, ini);
	_itot_s(LPMTOPTION.CHANGE_WINDOW_SIZE, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("ChangeWindowSize"), buf, ini);
	_itot_s(LPMTOPTION.CHAT_HISTORY, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("ChatHistory"), buf, ini);
	_itot_s(LPMTOPTION.DELAY, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("Delay"), buf, ini);
	_itot_s(LPMTOPTION.REPLAY_VERSION, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("ReplayVersion"), buf, ini);
	_itot_s(LPMTOPTION.RECORD_REPLAY, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("RecordReplay"), buf, ini);
	_itot_s(LPMTOPTION.ALLOW_SPECTATORS, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("AllowSpectators"), buf, ini);
	_itot_s(LPMTOPTION.AFTER_REST, buf, 10);
	WritePrivateProfileString(_T("LunaPortMT"), _T("AfterRest"), buf, ini);

	_itot_s(LPMTWS.LEFT, buf, 10);
	WritePrivateProfileString(_T("State"), _T("Left"), buf, ini);
	_itot_s(LPMTWS.TOP, buf, 10);
	WritePrivateProfileString(_T("State"), _T("Top"), buf, ini);
	_itot_s(LPMTWS.WIDTH, buf, 10);
	WritePrivateProfileString(_T("State"), _T("Width"), buf, ini);
	_itot_s(LPMTWS.HEIGHT, buf, 10);
	WritePrivateProfileString(_T("State"), _T("Height"), buf, ini);
	_itot_s(LPMTWS.SPLITTER, buf, 10);
	WritePrivateProfileString(_T("State"), _T("Splitter"), buf, ini);
	_itot_s(LPMTWS.DIALOG_LEFT, buf, 10);
	WritePrivateProfileString(_T("State"), _T("DialogLeft"), buf, ini);
	_itot_s(LPMTWS.DIALOG_TOP, buf, 10);
	WritePrivateProfileString(_T("State"), _T("DialogTop"), buf, ini);

	_ultot_s(LPMTCOLOR.SERVER_NAME, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("ServerName"), buf, ini);
	_ultot_s(LPMTCOLOR.HOST_NAME, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("HostName"), buf, ini);
	_ultot_s(LPMTCOLOR.CLIENT_NAME, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("ClientName"), buf, ini);
	_ultot_s(LPMTCOLOR.REST_STATE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("RestState"), buf, ini);
	_ultot_s(LPMTCOLOR.VS_STATE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("VSState"), buf, ini);
	_ultot_s(LPMTCOLOR.WATCH_STATE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("WatchState"), buf, ini);
	_ultot_s(LPMTCOLOR.SYSTEM_MESSAGE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("SystemMessage"),buf, ini);
	_ultot_s(LPMTCOLOR.ERROR_MESSAGE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("ErrorMessage"), buf, ini);
	_ultot_s(LPMTCOLOR.DEBUG_MESSAGE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("DebugMessage"), buf, ini);
	_ultot_s(LPMTCOLOR.NOTICE_BACK, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("NoticeBack"), buf, ini);
	_ultot_s(LPMTCOLOR.COMMENT_BACK, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("CommentBack"), buf, ini);
	_ultot_s(LPMTCOLOR.SECRET, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("Secret"), buf, ini);
}

void CheckLPMTOptions()
{
	TCHAR buf[_MAX_PATH];

	// 相対パス -> 絶対パス
	_tchdir(LPMTOPTION.PATH);

	_tsplitpath_s(LPMTOPTION.GAME_EXE, NULL, 0, NULL, 0, NULL, 0, buf, _MAX_EXT);
	if(_tcscmp(buf, _T(".exe")) == 0){
		if(LPMTOPTION.GAME_EXE[1] != ':'){
			_tcscpy_s(buf, LPMTOPTION.GAME_EXE);
			_tfullpath(LPMTOPTION.GAME_EXE, buf, _MAX_PATH);
		}
	}

	if(LPMTOPTION.REPLAY_FOLDER[1] != ':'){
		_tcscpy_s(buf, LPMTOPTION.REPLAY_FOLDER);
		_tfullpath(LPMTOPTION.REPLAY_FOLDER, buf, _MAX_PATH);
	}

	if(LPMTOPTION.VS_SOUND[1] != ':'){
		_tcscpy_s(buf, LPMTOPTION.VS_SOUND);
		_tfullpath(LPMTOPTION.VS_SOUND, buf, _MAX_PATH);
	}

	if(LPMTOPTION.NOTICE_SOUND[1] != ':'){
		_tcscpy_s(buf, LPMTOPTION.NOTICE_SOUND);
		_tfullpath(LPMTOPTION.NOTICE_SOUND, buf, _MAX_PATH);
	}

	// 絶対パスに変換されるとドライブ名が小文字になるのが気になっていけない
	LPMTOPTION.GAME_EXE[0]      = _totupper(LPMTOPTION.GAME_EXE[0]);
	LPMTOPTION.REPLAY_FOLDER[0] = _totupper(LPMTOPTION.REPLAY_FOLDER[0]);
	LPMTOPTION.VS_SOUND[0]      = _totupper(LPMTOPTION.VS_SOUND[0]);
	LPMTOPTION.NOTICE_SOUND[0]  = _totupper(LPMTOPTION.NOTICE_SOUND[0]);

	// ステージ
	if(LPMTOPTION.STAGE_SELECT > LPMTOPTION.MAX_STAGES){
		LPMTOPTION.STAGE_SELECT = LPMTOPTION.MAX_STAGES;
	}
}

void SetCaption()
{
	EnterCriticalSection(&CS_CAPTION);

	if(LUNAPORT.HWND != NULL){
		SetWindowText(LUNAPORT.HWND, LUNAPORT.TITLE);
	}
	else{
		LUNAPORT.HWND = FindWindow(_T("KGT2KGAME"), NULL);

		if(LUNAPORT.HWND != NULL){
			// 最前面表示
			if(LUNAPORT.SHOW_TOP == false){
				SetWindowPos(LUNAPORT.HWND, HWND_TOPMOST,   0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
				SetWindowPos(LUNAPORT.HWND, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);

				LUNAPORT.SHOW_TOP = true;
			}

			GetWindowText(LUNAPORT.HWND, LUNAPORT.ORIGINAL_TITLE, sizeof(LUNAPORT.ORIGINAL_TITLE));

			if(_tcslen(LUNAPORT.ORIGINAL_TITLE) == 0){
				LUNAPORT.HWND = NULL;
			}
		}
	}

	LeaveCriticalSection(&CS_CAPTION);
}

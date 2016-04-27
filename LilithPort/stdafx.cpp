// stdafx.cpp : 標準インクルード LilithPort.pch のみを
// 含むソース ファイルは、プリコンパイル済みヘッダーになります。
// stdafx.obj にはプリコンパイル済み型情報が含まれます。

#include "stdafx.h"

extern CRITICAL_SECTION CS_CAPTION;

// 落ちる前にエラー内容をロギング
void WriteErrorLog(String^ text, String^ caption)
{
	IO::StreamWriter^ sw = gcnew IO::StreamWriter(gcnew String(MTOPTION.PATH) + "error.log", true, Encoding::Default);
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

// 例外調査
void ApplicationThreadException(Object^ sender, Threading::ThreadExceptionEventArgs^ e)
{
	WriteErrorLog(e->Exception->ToString(), "ThreadException");

	MessageBox::Show("突然ですがLilithPort終了のお知らせです。", "緊急事態発生");

	Application::Exit();
}

// 主にコンソールアプリの例外
void ApplicationUnhandledException(Object^ sender, UnhandledExceptionEventArgs^ e)
{
	WriteErrorLog(safe_cast<Exception^>(e->ExceptionObject)->ToString(), "UnhandledException");

	MessageBox::Show("突然ですがLilithPort終了のお知らせです。", "例外が飛んできました");

	Application::Exit();
}

// iniの読み込み
void LoadMTOption()
{
	TCHAR ini[_MAX_PATH];
	TCHAR tmpName[MAX_TITLE];
	TCHAR tmpIP[MAX_TITLE];
	const TCHAR *nameP1, *nameP2, *ipP1, *ipP2;
	int nameLen, ipLen;

	_stprintf_s(ini, _T("%sLilithPort.ini"), MTOPTION.PATH);

	MTOPTION.CONNECTION_TYPE = GetPrivateProfileInt(_T("LilithPort"),   _T("ConnectType"), 0, ini);
	GetPrivateProfileString(_T("LilithPort"), _T("ServerName"),         _T(""),            MTOPTION.SERVER_NAME,    MAX_NAME,  ini);
	GetPrivateProfileString(_T("LilithPort"), _T("ConnectIP"),          _T(""),            MTOPTION.CONNECTION_IP,  MAX_NAME,  ini);
	GetPrivateProfileString(_T("LilithPort"), _T("Welcome"),            _T(""),            MTOPTION.WELCOME,        MAX_TITLE, ini);
	GetPrivateProfileString(_T("LilithPort"), _T("GameExe"),            _T("game.exe"),    MTOPTION.GAME_EXE,      _MAX_PATH,  ini);
	GetPrivateProfileString(_T("LilithPort"), _T("ReplayFolder"),       _T("Replay"),      MTOPTION.REPLAY_FOLDER, _MAX_PATH,  ini);
	GetPrivateProfileString(_T("LilithPort"), _T("VSSound"),            _T("vs.wav"),      MTOPTION.VS_SOUND,      _MAX_PATH,  ini);
	GetPrivateProfileString(_T("LilithPort"), _T("NoticeSound"),        _T("notice.wav"),  MTOPTION.NOTICE_SOUND,  _MAX_PATH,  ini);
	GetPrivateProfileString(_T("LilithPort"), _T("EnterSound"),         _T("enter.wav"),   MTOPTION.ENTER_SOUND,   _MAX_PATH,  ini);
	GetPrivateProfileString(_T("LilithPort"), _T("KeywordSound"),       _T("keyword.wav"), MTOPTION.KEYWORD_SOUND, _MAX_PATH,  ini);
	GetPrivateProfileString(_T("LilithPort"), _T("Name"),               _T("名無しさん"),  MTOPTION.NAME,           MAX_NAME,  ini);
	GetPrivateProfileString(_T("LilithPort"), _T("Comment"),            _T(""),            MTOPTION.COMMENT,        MAX_NAME,  ini);

	MTOPTION.BOOKMARK_COUNT     = GetPrivateProfileInt(_T("LilithPort"), _T("BookMarkCount"),    0, ini);

	// ブックマーク情報を配列に分割抽出
	if(MTOPTION.BOOKMARK_COUNT > 0) {
		GetPrivateProfileString(_T("LilithPort"), _T("BookMarkServerName"), _T(""), tmpName, MAX_TITLE, ini);
		GetPrivateProfileString(_T("LilithPort"), _T("BookMarkConnectIP"),  _T(""), tmpIP, MAX_TITLE, ini);

		nameP1 = tmpName;
		ipP1 = tmpIP;
		for(UINT i=0;i < MTOPTION.BOOKMARK_COUNT;i++) {
			nameP2 = _tcschr(nameP1, _T(','));
			ipP2 = _tcschr(ipP1, _T(','));

			if (nameP2 != NULL){
				nameLen = (int)(nameP2 - nameP1);
				ipLen = (int)(ipP2 - ipP1);
			}else{
				nameLen = (int)_tcslen(nameP1);
				ipLen = (int)_tcslen(ipP1);
			}

			_tcsncpy_s(tmpName, _countof(tmpName), nameP1, nameLen);
			_tcsncpy_s(tmpIP, _countof(tmpIP), ipP1, ipLen);
			tmpName[nameLen] = NULL;
			tmpIP[ipLen] = NULL;

			_tcscpy_s(MTOPTION.BOOKMARK_SERVER_NAME[i], tmpName);
			_tcscpy_s(MTOPTION.BOOKMARK_CONNECTION_IP[i], tmpIP);

			if (nameP2 != NULL){
				nameP1 = nameP2 + 1;
				ipP1 = ipP2 + 1;
			}else{
				break;
			}
		}
	}

	MTOPTION.PORT               = GetPrivateProfileInt(_T("LilithPort"), _T("Port"),          7500, ini);
	MTOPTION.OPEN_PORT          = GetPrivateProfileInt(_T("LilithPort"), _T("OpenPort"),      7500, ini);
	MTOPTION.AUTO_SAVE          = GetPrivateProfileInt(_T("LilithPort"), _T("AutoSave"),         0, ini);
	MTOPTION.MAX_CONNECTION     = GetPrivateProfileInt(_T("LilithPort"), _T("MaxConnection"),    1, ini);
	MTOPTION.BGM_VOLUME         = GetPrivateProfileInt(_T("LilithPort"), _T("BGMVolume"),      100, ini);
	MTOPTION.SE_VOLUME          = GetPrivateProfileInt(_T("LilithPort"), _T("SEVolume"),       100, ini);
	MTOPTION.MAX_STAGE          = GetPrivateProfileInt(_T("LilithPort"), _T("MaxStage"),         1, ini);
	MTOPTION.STAGE_SELECT       = GetPrivateProfileInt(_T("LilithPort"), _T("StageSelect"),      0, ini);
	MTOPTION.ROUND              = GetPrivateProfileInt(_T("LilithPort"), _T("Round"),            2, ini);
	MTOPTION.TIMER              = GetPrivateProfileInt(_T("LilithPort"), _T("Timer"),            0, ini);
	MTOPTION.SIMULATE_DELAY     = GetPrivateProfileInt(_T("LilithPort"), _T("SimulateDelay"),    0, ini);
	MTOPTION.HIT_JUDGE          = GetPrivateProfileInt(_T("LilithPort"), _T("HitJudge"),         0, ini) == 1 ? true : false;
	MTOPTION.DISPLAY_NAME       = GetPrivateProfileInt(_T("LilithPort"), _T("DisplayName"),      1, ini) == 1 ? true : false;
	MTOPTION.DISPLAY_VERSUS     = GetPrivateProfileInt(_T("LilithPort"), _T("DisplayVersus"),    1, ini) == 1 ? true : false;
	MTOPTION.DISPLAY_FRAMERATE  = GetPrivateProfileInt(_T("LilithPort"), _T("DisplayFramerate"), 1, ini) == 1 ? true : false;
	MTOPTION.DISPLAY_RAND       = GetPrivateProfileInt(_T("LilithPort"), _T("DisplayRand"),      0, ini) == 1 ? true : false;
	MTOPTION.REPLAY_DIVIDE      = GetPrivateProfileInt(_T("LilithPort"), _T("ReplayDivide"),     0, ini) == 1 ? true : false;
	MTOPTION.CHANGE_WINDOW_SIZE = GetPrivateProfileInt(_T("LilithPort"), _T("ChangeWindowSize"), 0, ini) == 1 ? true : false;
	MTOPTION.CHAT_HISTORY       = GetPrivateProfileInt(_T("LilithPort"), _T("ChatHistory"),     20, ini);
	MTOPTION.DELAY              = GetPrivateProfileInt(_T("LilithPort"), _T("Delay"),            0, ini);
	MTOPTION.INTERVAL           = GetPrivateProfileInt(_T("LilithPort"), _T("Interval"),         1, ini);
	MTOPTION.REPLAY_VERSION     = GetPrivateProfileInt(_T("LilithPort"), _T("ReplayVersion"),    2, ini);
	MTOPTION.RECORD_REPLAY      = GetPrivateProfileInt(_T("LilithPort"), _T("RecordReplay"),     0, ini) == 1 ? true : false;
	MTOPTION.ALLOW_SPECTATOR    = GetPrivateProfileInt(_T("LilithPort"), _T("AllowSpectator"),   0, ini) == 1 ? true : false;
	MTOPTION.LOG_LOCK           = GetPrivateProfileInt(_T("LilithPort"), _T("LogLock"),          0, ini) == 1 ? true : false;
	MTOPTION.KEYWORD_FLASH      = GetPrivateProfileInt(_T("LilithPort"), _T("KeywordFlash"),     1, ini) == 1 ? true : false;
	MTOPTION.AFTER_REST         = GetPrivateProfileInt(_T("LilithPort"), _T("AfterRest"),        0, ini) == 1 ? true : false;

	MTWS.LEFT        = GetPrivateProfileInt(_T("State"), _T("Left"),       0, ini);
	MTWS.TOP         = GetPrivateProfileInt(_T("State"), _T("Top"),        0, ini);
	MTWS.WIDTH       = GetPrivateProfileInt(_T("State"), _T("Width"),      0, ini);
	MTWS.HEIGHT      = GetPrivateProfileInt(_T("State"), _T("Height"),     0, ini);
	MTWS.SPLITTER    = GetPrivateProfileInt(_T("State"), _T("Splitter"),   0, ini);
	MTWS.DIALOG_LEFT = GetPrivateProfileInt(_T("State"), _T("DialogLeft"), 0, ini);
	MTWS.DIALOG_TOP  = GetPrivateProfileInt(_T("State"), _T("DialogTop"),  0, ini);

	MTCOLOR.SERVER_NAME    = GetPrivateProfileInt(_T("Color"), _T("ServerName"),    Color::ForestGreen.ToArgb(), ini);
	MTCOLOR.HOST_NAME      = GetPrivateProfileInt(_T("Color"), _T("HostName"),      Color::MediumBlue.ToArgb(),  ini);
	MTCOLOR.CLIENT_NAME    = GetPrivateProfileInt(_T("Color"), _T("ClientName"),    Color::Black.ToArgb(),       ini);
	MTCOLOR.REST_STATE     = GetPrivateProfileInt(_T("Color"), _T("RestState"),     Color::Khaki.ToArgb(),       ini);
	MTCOLOR.VS_STATE       = GetPrivateProfileInt(_T("Color"), _T("VSState"),       Color::Salmon.ToArgb(),      ini);
	MTCOLOR.WATCH_STATE    = GetPrivateProfileInt(_T("Color"), _T("WatchState"),    Color::PaleGreen.ToArgb(),   ini);
	MTCOLOR.SYSTEM_MESSAGE = GetPrivateProfileInt(_T("Color"), _T("SystemMessage"), Color::Teal.ToArgb(),        ini);
	MTCOLOR.ERROR_MESSAGE  = GetPrivateProfileInt(_T("Color"), _T("ErrorMessage"),  Color::Red.ToArgb(),         ini);
	MTCOLOR.DEBUG_MESSAGE  = GetPrivateProfileInt(_T("Color"), _T("DebugMessage"),  Color::DarkOrange.ToArgb(),  ini);
	MTCOLOR.NOTICE_BACK    = GetPrivateProfileInt(_T("Color"), _T("NoticeBack"),    Color::PowderBlue.ToArgb(),  ini);
	MTCOLOR.COMMENT_BACK   = GetPrivateProfileInt(_T("Color"), _T("CommentBack"),   Color::MistyRose.ToArgb(),   ini);
	MTCOLOR.SECRET         = GetPrivateProfileInt(_T("Color"), _T("Secret"),        Color::HotPink.ToArgb(),     ini);

	// Welcomeのタブを改行に
	int len = _tcslen(MTOPTION.WELCOME);

	for(int i = 0; i < len; i++){
		if(MTOPTION.WELCOME[i] == _T('¥t')){
			MTOPTION.WELCOME[i] = _T('¥n');
		}
	}
	
}

// iniに書き出し
void SaveMTOption()
{
	// 改行をタブに置換
	int len = _tcslen(MTOPTION.WELCOME);

	for(int i = 0; i < len; i++){
		if(MTOPTION.WELCOME[i] == _T('¥n')){
			MTOPTION.WELCOME[i] = _T('¥t');
		}
	}

	TCHAR ini[_MAX_PATH], buf[MAX_NAME];
	TCHAR tmpStrName[MAX_TITLE] = L"";
	TCHAR tmpStrIP[MAX_TITLE] = L"";

	_stprintf_s(ini, _T("%sLilithPort.ini"), MTOPTION.PATH);

	_itot_s(MTOPTION.CONNECTION_TYPE, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("ConnectType"),          buf,                             ini);
	WritePrivateProfileString(_T("LilithPort"), _T("ServerName"),           MTOPTION.SERVER_NAME,            ini);
	WritePrivateProfileString(_T("LilithPort"), _T("ConnectIP"),            MTOPTION.CONNECTION_IP,          ini);
	WritePrivateProfileString(_T("LilithPort"), _T("Welcome"),              MTOPTION.WELCOME,                ini);
	WritePrivateProfileString(_T("LilithPort"), _T("GameExe"),              MTOPTION.GAME_EXE,               ini);
	WritePrivateProfileString(_T("LilithPort"), _T("ReplayFolder"),         MTOPTION.REPLAY_FOLDER,          ini);
	WritePrivateProfileString(_T("LilithPort"), _T("VSSound"),              MTOPTION.VS_SOUND,               ini);
	WritePrivateProfileString(_T("LilithPort"), _T("NoticeSound"),          MTOPTION.NOTICE_SOUND,           ini);
	WritePrivateProfileString(_T("LilithPort"), _T("EnterSound"),           MTOPTION.ENTER_SOUND,            ini);
	WritePrivateProfileString(_T("LilithPort"), _T("KeywordSound"),         MTOPTION.KEYWORD_SOUND,          ini);
	WritePrivateProfileString(_T("LilithPort"), _T("Name"),                 MTOPTION.NAME,                   ini);
	WritePrivateProfileString(_T("LilithPort"), _T("Comment"),              MTOPTION.COMMENT,                ini);

	if(MTOPTION.BOOKMARK_COUNT > 0) {

		// ブックマーク情報連結処理
		for(UINT i=0;i < MTOPTION.BOOKMARK_COUNT;i++) {
			if(gcnew String(MTOPTION.BOOKMARK_SERVER_NAME[i]) != ""){
				_stprintf_s(tmpStrName, _T("%s%s,"), tmpStrName, MTOPTION.BOOKMARK_SERVER_NAME[i]);
				_stprintf_s(tmpStrIP, _T("%s%s,"), tmpStrIP, MTOPTION.BOOKMARK_CONNECTION_IP[i]);
			}
		}
		WritePrivateProfileString(_T("LilithPort"), _T("BookMarkServerName"),   tmpStrName, ini);
		WritePrivateProfileString(_T("LilithPort"), _T("BookMarkConnectIP"),    tmpStrIP,   ini);

		_itot_s((MTOPTION.BOOKMARK_COUNT - MTOPTION.BOOKMARK_DELETED_COUNT), buf, 10);
		WritePrivateProfileString(_T("LilithPort"), _T("BookMarkCount"), buf, ini);
	}

	_itot_s(MTOPTION.PORT, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("Port"), buf, ini);
	_itot_s(MTOPTION.OPEN_PORT, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("OpenPort"), buf, ini);
	_itot_s(MTOPTION.AUTO_SAVE, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("AutoSave"), buf, ini);
	_itot_s(MTOPTION.MAX_CONNECTION, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("MaxConnection"), buf, ini);
	_itot_s(MTOPTION.BGM_VOLUME, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("BGMVolume"), buf, ini);
	_itot_s(MTOPTION.SE_VOLUME, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("SEVolume"), buf, ini);
	_itot_s(MTOPTION.MAX_STAGE, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("MaxStage"), buf, ini);
	_itot_s(MTOPTION.STAGE_SELECT, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("StageSelect"), buf, ini);
	_itot_s(MTOPTION.ROUND, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("Round"), buf, ini);
	_itot_s(MTOPTION.TIMER, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("Timer"), buf, ini);
	_itot_s(MTOPTION.SIMULATE_DELAY, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("SimulateDelay"), buf, ini);
	_itot_s(MTOPTION.HIT_JUDGE, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("HitJudge"), buf, ini);
	_itot_s(MTOPTION.DISPLAY_NAME, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("DisplayName"), buf, ini);
	_itot_s(MTOPTION.DISPLAY_VERSUS, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("DisplayVersus"), buf, ini);
	_itot_s(MTOPTION.DISPLAY_FRAMERATE, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("DisplayFramerate"), buf, ini);
	_itot_s(MTOPTION.DISPLAY_RAND, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("DisplayRand"), buf, ini);
	_itot_s(MTOPTION.REPLAY_DIVIDE, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("ReplayDivide"), buf, ini);
	_itot_s(MTOPTION.CHANGE_WINDOW_SIZE, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("ChangeWindowSize"), buf, ini);
	_itot_s(MTOPTION.CHAT_HISTORY, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("ChatHistory"), buf, ini);
	_itot_s(MTOPTION.DELAY, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("Delay"), buf, ini);
	_itot_s(MTOPTION.INTERVAL, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("Interval"), buf, ini);
	_itot_s(MTOPTION.REPLAY_VERSION, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("ReplayVersion"), buf, ini);
	_itot_s(MTOPTION.RECORD_REPLAY, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("RecordReplay"), buf, ini);
	_itot_s(MTOPTION.ALLOW_SPECTATOR, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("AllowSpectator"), buf, ini);
	_itot_s(MTOPTION.LOG_LOCK, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("LogLock"), buf, ini);
	_itot_s(MTOPTION.KEYWORD_FLASH, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("KeywordFlash"), buf, ini);
	_itot_s(MTOPTION.AFTER_REST, buf, 10);
	WritePrivateProfileString(_T("LilithPort"), _T("AfterRest"), buf, ini);
	_itot_s(MTWS.LEFT, buf, 10);
	WritePrivateProfileString(_T("State"), _T("Left"), buf, ini);
	_itot_s(MTWS.TOP, buf, 10);
	WritePrivateProfileString(_T("State"), _T("Top"), buf, ini);
	_itot_s(MTWS.WIDTH, buf, 10);
	WritePrivateProfileString(_T("State"), _T("Width"), buf, ini);
	_itot_s(MTWS.HEIGHT, buf, 10);
	WritePrivateProfileString(_T("State"), _T("Height"), buf, ini);
	_itot_s(MTWS.SPLITTER, buf, 10);
	WritePrivateProfileString(_T("State"), _T("Splitter"), buf, ini);
	_itot_s(MTWS.DIALOG_LEFT, buf, 10);
	WritePrivateProfileString(_T("State"), _T("DialogLeft"), buf, ini);
	_itot_s(MTWS.DIALOG_TOP, buf, 10);
	WritePrivateProfileString(_T("State"), _T("DialogTop"), buf, ini);

	_ultot_s(MTCOLOR.SERVER_NAME, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("ServerName"), buf, ini);
	_ultot_s(MTCOLOR.HOST_NAME, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("HostName"), buf, ini);
	_ultot_s(MTCOLOR.CLIENT_NAME, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("ClientName"), buf, ini);
	_ultot_s(MTCOLOR.REST_STATE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("RestState"), buf, ini);
	_ultot_s(MTCOLOR.VS_STATE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("VSState"), buf, ini);
	_ultot_s(MTCOLOR.WATCH_STATE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("WatchState"), buf, ini);
	_ultot_s(MTCOLOR.SYSTEM_MESSAGE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("SystemMessage"),buf, ini);
	_ultot_s(MTCOLOR.ERROR_MESSAGE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("ErrorMessage"), buf, ini);
	_ultot_s(MTCOLOR.DEBUG_MESSAGE, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("DebugMessage"), buf, ini);
	_ultot_s(MTCOLOR.NOTICE_BACK, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("NoticeBack"), buf, ini);
	_ultot_s(MTCOLOR.COMMENT_BACK, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("CommentBack"), buf, ini);
	_ultot_s(MTCOLOR.SECRET, buf, 10);
	WritePrivateProfileString(_T("Color"), _T("Secret"), buf, ini);
}

// 設定値を軽くチェック
void CheckMTOption()
{
	TCHAR buf[_MAX_PATH];

	// 相対パス -> 絶対パス
	_tchdir(MTOPTION.PATH);

	_tsplitpath_s(MTOPTION.GAME_EXE, NULL, 0, NULL, 0, NULL, 0, buf, _MAX_EXT);
	if(_tcscmp(buf, _T(".exe")) == 0){
		if(MTOPTION.GAME_EXE[1] != ':'){
			_tcscpy_s(buf, MTOPTION.GAME_EXE);
			_tfullpath(MTOPTION.GAME_EXE, buf, _MAX_PATH);
		}
	}

	if(MTOPTION.REPLAY_FOLDER[1] != ':'){
		_tcscpy_s(buf, MTOPTION.REPLAY_FOLDER);
		_tfullpath(MTOPTION.REPLAY_FOLDER, buf, _MAX_PATH);
	}

	if(MTOPTION.VS_SOUND[1] != ':'){
		_tcscpy_s(buf, MTOPTION.VS_SOUND);
		_tfullpath(MTOPTION.VS_SOUND, buf, _MAX_PATH);
	}

	if(MTOPTION.NOTICE_SOUND[1] != ':'){
		_tcscpy_s(buf, MTOPTION.NOTICE_SOUND);
		_tfullpath(MTOPTION.NOTICE_SOUND, buf, _MAX_PATH);
	}

	if(MTOPTION.ENTER_SOUND[1] != ':'){
		_tcscpy_s(buf, MTOPTION.ENTER_SOUND);
		_tfullpath(MTOPTION.ENTER_SOUND, buf, _MAX_PATH);
	}

	if(MTOPTION.KEYWORD_SOUND[1] != ':'){
		_tcscpy_s(buf, MTOPTION.KEYWORD_SOUND);
		_tfullpath(MTOPTION.KEYWORD_SOUND, buf, _MAX_PATH);
	}

	// 絶対パスに変換されるとドライブ名が小文字になるのが気になっていけない
	MTOPTION.GAME_EXE[0]      = _totupper(MTOPTION.GAME_EXE[0]);
	MTOPTION.REPLAY_FOLDER[0] = _totupper(MTOPTION.REPLAY_FOLDER[0]);
	MTOPTION.VS_SOUND[0]      = _totupper(MTOPTION.VS_SOUND[0]);
	MTOPTION.NOTICE_SOUND[0]  = _totupper(MTOPTION.NOTICE_SOUND[0]);
	MTOPTION.ENTER_SOUND[0]   = _totupper(MTOPTION.ENTER_SOUND[0]);
	MTOPTION.KEYWORD_SOUND[0] = _totupper(MTOPTION.KEYWORD_SOUND[0]);
}

// 対戦中のタイトルバー
void SetCaption()
{
	EnterCriticalSection(&CS_CAPTION);

	if(MTINFO.HWND != NULL){
		SetWindowText(MTINFO.HWND, MTINFO.TITLE);
	}
	else{
		if(MTINFO.KGT2K){
			MTINFO.HWND = FindWindow(_T("KGT2KGAME"), NULL);
		}
		else{
			MTINFO.HWND = FindWindow(_T("KGT95GAME"), NULL);
		}

		if(MTINFO.HWND != NULL){
			// 最前面表示
			if(MTINFO.SHOW_TOP == false){
				// 格ツク95ウィンドウサイズ変更
				if(MTOPTION.CHANGE_WINDOW_SIZE && MTINFO.KGT2K == false){
					RECT rc;
					SetRect(&rc, 0, 0, 640, 480);
					AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, true, 0);
					SetWindowPos(MTINFO.HWND, NULL, GetSystemMetrics(SM_CXSCREEN)/2 - 320, GetSystemMetrics(SM_CYSCREEN)/2 - 240, rc.right - rc.left, rc.bottom - rc.top, 0);
				}

				SetWindowPos(MTINFO.HWND, HWND_TOPMOST,   0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
				SetWindowPos(MTINFO.HWND, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);

				MTINFO.SHOW_TOP = true;
			}

			GetWindowText(MTINFO.HWND, MTINFO.ORIGINAL_TITLE, sizeof(MTINFO.ORIGINAL_TITLE));

			if(_tcslen(MTINFO.ORIGINAL_TITLE) == 0 || _tcscmp(MTINFO.ORIGINAL_TITLE, _T("２Ｄ格闘ツクール９５")) == 0){
				MTINFO.HWND = NULL;
			}
		}
	}

	LeaveCriticalSection(&CS_CAPTION);
}

// 暗号復号用乱数
UINT CipherRand(UINT32 seed)
{
	static UINT32 a[4] = {1812433254, 3713160357, 3109174145, 64984499};

	if(seed == 0){
		UINT t = (a[0]^(a[0] << 11));

		a[0] = a[1]; a[1] = a[2]; a[2] = a[3];
		return (a[3] = (a[3]^(a[3] >> 19))^(t^(t >> 8)));
	}
	else{
		for(int i = 0; i < 4; i++){
			a[i] = seed = 1812433253*(seed^(seed >> 30)) + i;
		}
	}

	return 0;
}

// 通常用
UINT XorShift(UINT32 seed)
{
	static UINT32 a[4] = {1812433254, 3713160357, 3109174145, 64984499};

	if(seed == 0){
		UINT t = (a[0]^(a[0] << 11));

		a[0] = a[1]; a[1] = a[2]; a[2] = a[3];
		return (a[3] = (a[3]^(a[3] >> 19))^(t^(t >> 8)));
	}
	else{
		for(int i = 0; i < 4; i++){
			a[i] = seed = 1812433253*(seed^(seed >> 30)) + i;
		}
	}

	return 0;
}

// ランダムステージ用
UINT RandomStage(UINT32 seed)
{
	static UINT32 a[4] = {1812433254, 3713160357, 3109174145, 64984499};

	if(seed == 0){
		UINT t = (a[0]^(a[0] << 11));

		a[0] = a[1]; a[1] = a[2]; a[2] = a[3];
		return (a[3] = (a[3]^(a[3] >> 19))^(t^(t >> 8)));
	}
	else{
		for(int i = 0; i < 4; i++){
			a[i] = seed = 1812433253*(seed^(seed >> 30)) + i;
		}
	}

	return 0;
}


// IPのエンコード
// (元は謎の暗号化処理だったがBase64で代替)
String^ EncryptionIP(String^ ip)
{
	String ^ipString;
	try {
		ipString = Int64(Net::IPAddress::Parse(ip)->Address).ToString();
	}
	catch (ArgumentNullException^) {
		return "変換失敗。IPぬるぽエラー";
	}
	catch (FormatException^) {
		return "変換失敗。IP形式エラー";
	}

	array<Byte> ^binaryData = gcnew array<Byte>(11);
	binaryData = System::Text::Encoding::ASCII->GetBytes(ipString);

	String ^ipBase64;
	try {
		ipBase64 = Convert::ToBase64String(binaryData);
	}
	catch (ArgumentNullException^) {
		return "変換失敗。Base64ぬるぽエラー";
	}
	catch (FormatException^) {
		return "変換失敗。Base64形式エラー";
	}

	return ipBase64;
}

// IPのデコード
_int64 DecryptionIP(String^ cipher_ip)
{
	array<Byte> ^binaryData;

	try {
		binaryData = Convert::FromBase64String(cipher_ip);
	}
	catch (ArgumentNullException^) {
		throw gcnew ArgumentNullException;
		return 0;
	}
	catch (FormatException^) {
		throw gcnew FormatException;
		return 0;
	}

	return Convert::ToInt64(Encoding::ASCII->GetString(binaryData));
}
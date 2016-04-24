// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
#pragma once
#pragma warning(disable: 4100)

// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <mmsystem.h>
#include <deque>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "winmm.lib")

using namespace System;

extern void WriteErrorLog(String^ text, String^ caption);

extern void CheckLPMTOptions();
extern void ChangeStageValue();
extern void SetCaption();

// DEBUG PROCESS
const UINT KBD_CONTROLS_LEN = 10;
const UINT JOY_CONTROLS_LEN = 7;

const BYTE NOP = 0x90;

const UINT P1_KBD_CONTROLS = 0x00425980;
const UINT P2_KBD_CONTROLS = 0x00425991;
const UINT P1_JOY_CONTROLS = 0x00445710;
const UINT P2_JOY_CONTROLS = 0x00445717;

const UINT CONTROL_CHANGE = 0x0041B588;

const UINT STICK_SELECTION = 0x004144CB;
const BYTE STICK_SELECTION_CODE[] = {0x6A,0x00};

const UINT KBD_WRITEBACK = 0x00414FCA;
const BYTE KBD_WRITEBACK_CODE[] = {0x90,0x8B,0x15,0x7C,0x1F,0x54,0x00,0x90,0x90,0x90,0x90,0x90};
const UINT JOY_WRITEBACK = 0x0041502C;
const BYTE JOY_WRITEBACK_CODE[] = {0x90,0x8B,0x15,0x7C,0x1F,0x54,0x00,0x90,0x90,0x90,0x90,0x90};

const UINT RANDOM_SEED = 0x0041FB1C;
const UINT RAND_FUNC = 0x00417A22;
const BYTE RAND_FUNC_CODE[] = {0xCC,0x90,0x90,0x90,0x90};

const UINT HIT_JUDGE = 0x0042470C;
const UINT HIT_JUDGE_SET = 0x00414C90;
const BYTE HIT_JUDGE_SET_CODE[] = {0x90,0x90,0x90,0x90,0x90,0x90};

const UINT VS_ROUND = 0x0040897F;
const BYTE VS_ROUND_CODE[] = {0xCC};
const UINT ROUND_ESI = 0x004EDCAC;
const UINT ROUND_END = 0x00409715;
const BYTE ROUND_END_CODE[] = {0xCC,0x90,0x90,0x90,0x90,0x90};

const UINT MODE_SELECT = 0x00408306;
const BYTE MODE_SELECT_CODE[] = {0xCC,0x90,0x90,0x90,0x90};

const UINT DEFAULT_TIME = 0x00430114;
const UINT TIME_LIMIT = 0x00470050;
const UINT TIMER_RESET1 = 0x00408B0A;
const BYTE TIMER_RESET1_CODE[] = {0xCC,0x90,0x90,0x90,0x90};
const UINT TIMER_RESET2 = 0x00408A85;
const BYTE TIMER_RESET2_CODE[] = {0xCC,0x90,0x90,0x90,0x90,0x90};
const UINT TIMER_DECREASE = 0x00408E50;
const BYTE TIMER_DECREASE_CODE[] = {0xCC,0x90,0x90,0x90,0x90};

const UINT P1_HP = 0x004DFC85;
const UINT P1_MAX_HP = 0x004DFC91;
const UINT P1_STATE = 0x0047033E;
const UINT P2_HP = 0x004EDCC4;
const UINT P2_MAX_HP = 0x004EDCD0;
const UINT P2_STATE = 0x004704BC;

const UINT STAGE_SELECT = 0x00408756;
const UINT STAGE_SELECT_BREAK = 0x00408756;
const BYTE STAGE_SELECT_CODE[] = {0xCC,0x90,0x90,0x90,0x90};

const UINT LOCAL_P_FUNC  = 0x0041B588;
const UINT LOCAL_P_BREAK = 0x0041B591;
const BYTE LOCAL_P_FUNC_CODE[] = {0xCC,0x90,0x90,0x90,0xE8,0xAF,0x8D,0xFF,0xFF,0xCC,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90};
const UINT LOCAL_P_JUMPBACK = 0x0041B5B9;
const BYTE LOCAL_P_JUMPBACK_CODE[2][5] = {{0xE9,0x82,0x91,0xFF,0xFF},{0xE9,0x9D,0x91,0xFF,0xFF}};

const UINT REMOTE_P_FUNC  = 0x0041B5BE;
const UINT REMOTE_P_BREAK = 0x0041B5C0;
const BYTE REMOTE_P_FUNC_CODE[] = {0x90,0x90,0xCC,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90};
const UINT REMOTE_P_JUMPBACK = 0x0041B5E3;
const BYTE REMOTE_P_JUMPBACK_CODE[2][5] = {{0xE9,0x58,0x91,0xFF,0xFF},{0xE9,0x73,0x91,0xFF,0xFF}};

const UINT P1_JUMP = 0x0041473B;
const BYTE P1_JUMP_CODE[2][5] = {{0xE9,0x48,0x6E,0x00,0x00},{0xE9,0x7E,0x6E,0x00,0x00}};
const UINT P2_JUMP = 0x00414756;
const BYTE P2_JUMP_CODE[2][5] = {{0xE9,0x2D,0x6E,0x00,0x00},{0xE9,0x63,0x6E,0x00,0x00}};

const UINT PLAY_HOOKS = 0x0041B760;
const BYTE PLAY_HOOKS_CODE[] = {0xE8,0xDB,0x8B,0xFF,0xFF,0xCC,0xE9,0xD5,0x8F,0xFF,0xFF,0xE8,0xD0,0x8B,0xFF,0xFF,0xCC,0xE9,0xE5,0x8F,0xFF,0xFF};
const UINT PLAY_P1_JUMP  = 0x0041473B;
const UINT PLAY_P1_BREAK = 0x0041B765;
const BYTE PLAY_P1_JUMP_CODE[] = {0xE9,0x20,0x70,0x00,0x00};
const UINT PLAY_P2_JUMP  = 0x00414756;
const UINT PLAY_P2_BREAK = 0x0041B770;
const BYTE PLAY_P2_JUMP_CODE[] = {0xE9,0x10,0x70,0x00,0x00};

const UINT SINGLE_JUMP = 0x0041471B;
const BYTE SINGLE_JUMP_CODE[] = {0xE9,0x56,0x70,0x00,0x00};

const UINT SINGLE_FUNC = 0x0041B776;
const BYTE SINGLE_FUNC_CODE[] = {0xCC,0xE8,0xC4,0x8B,0xFF,0xFF,0xCC,0xE9,0x9E,0x8F,0xFF,0xFF};
const UINT SINGLE_BREAK_CONTROL = 0x0041B776;
const UINT SINGLE_BREAK_INPUT   = 0x0041B77C;

const UINT FRAME_FUNC  = 0x0041B782;
const UINT FRAME_BREAK = 0x0041B782;
const BYTE FRAME_FUNC_CODE[] = {0xCC,0xA1,0x6C,0x47,0x42,0x00,0xE9,0x88,0x94,0xFE,0xFF};
const UINT FRAME_JUMP = 0x00404C10;
const BYTE FRAME_JUMP_CODE[] = {0xE9,0x6D,0x6B,0x01,0x00};


// 設定項目
const UINT MAX_NAME   = 32;
const UINT MAX_ID     = 0x3FFF;
const UINT MAX_TITLE  = 256;
const UINT MAX_PACKET = 256;

const BYTE PROTOCOL_VERSION = 7;
const UINT TIME_OUT = 3000;

typedef struct _LUNA_PORT
{
	bool   DEBUG;
	bool   CHECK_RAND;
	bool   INITIALIZED;
	bool   SHOW_TOP;
	UINT32 SEED;
	HANDLE PROCESS;
	DWORD  PROCESS_ID;
	HWND   HWND;
	BYTE   KBD_BUFFER[KBD_CONTROLS_LEN];
	BYTE   JOY_BUFFER[JOY_CONTROLS_LEN];
	bool   CONTROL;  // 0:P1 1:P2
	TCHAR  P1_NAME[MAX_NAME];
	TCHAR  P2_NAME[MAX_NAME];
	TCHAR  ORIGINAL_TITLE[MAX_TITLE];
	TCHAR  TITLE[MAX_TITLE];
} LUNA_PORT;

typedef struct _LUNA_PORT_MT_OPTION
{
	TCHAR PATH[_MAX_PATH];
	UINT  CONNECTION_TYPE;
	TCHAR CONNECTION_IP[MAX_NAME];
	TCHAR WELCOME[MAX_TITLE/2];
	TCHAR GAME_EXE[_MAX_PATH];
	TCHAR REPLAY_FOLDER[_MAX_PATH];
	TCHAR VS_SOUND[_MAX_PATH];
	TCHAR NOTICE_SOUND[_MAX_PATH];
	TCHAR NAME[MAX_NAME];
	TCHAR COMMENT[MAX_NAME];
	UINT  PORT;
	UINT  OPEN_PORT;
	UINT  MAX_CONNECTIONS;
	UINT  MAX_STAGES;
	UINT  STAGE_SELECT;
	UINT  TIME_LIMIT;
	bool  HIT_JUDGE;
	bool  DISPLAY_NAMES;
	bool  DISPLAY_VERSUS;
	bool  DISPLAY_FRAMERATE;
	bool  DISPLAY_INPUTRATE;
	bool  REPLAY_DIVIDE;
	bool  CHANGE_WINDOW_SIZE;
	UINT  CHAT_HISTORY;
	UINT  DELAY;
	UINT  REPLAY_VERSION;
	bool  RECORD_REPLAY;
	bool  ALLOW_SPECTATORS;
	bool  AFTER_REST;
} LUNA_PORT_MT_OPTION;

typedef struct _LUNA_PORT_MT_WINDOW_STATE
{
	int LEFT;
	int TOP;
	int WIDTH;
	int HEIGHT;
	int SPLITTER;
	int DIALOG_LEFT;
	int DIALOG_TOP;
} LUNA_PORT_MT_WINDOW_STATE;

typedef struct _LUNA_PORT_MT_COLOR
{
	UINT32 SERVER_NAME;
	UINT32 HOST_NAME;
	UINT32 CLIENT_NAME;
	UINT32 REST_STATE;
	UINT32 VS_STATE;
	UINT32 WATCH_STATE;
	UINT32 SYSTEM_MESSAGE;
	UINT32 ERROR_MESSAGE;
	UINT32 DEBUG_MESSAGE;
	UINT32 NOTICE_BACK;
	UINT32 COMMENT_BACK;
	UINT32 SECRET;
} LUNA_PORT_MT_COLOR;

typedef struct _REPLAY_DATA
{
	UINT16 KEY;
	BYTE   COUNT;
} REPLAY_DATA;

typedef struct _REPLAY_INFO
{
	TCHAR  VERSION;
	bool   CONTROL;
	UINT16 KEY[2];
	BYTE   COUNT[2];

	std::deque<REPLAY_DATA> DEQUE[2];
} REPLAY_INFO;

typedef enum {
	CT_SERVER,
	CT_HOST,
	CT_CLIENT,
	CT_FREE,
} CONNECTION_TYPE;

typedef enum {
	MS_FREE,
	MS_REST,
	MS_VS,
	MS_WATCH,
	MS_COUCH,
	MS_READY,
} MEMBER_STATE;

typedef enum {
	LV_NAME,
	LV_COMMENT,
} LIST_VIEW;

typedef enum {
	RT_FREE = 1,
	RT_VS,
	RT_PLAYBACK,
	RT_WATCH,
} RUN_TYPE;

typedef enum {
	PH_PING,
	PH_PONG,
	PH_PING_PROXY,       // 2:送信者ID 2:送信先ID サーバ経由間接PING
	PH_PINGPONG,
	PH_PONG_PROXY,
	PH_REQ_CONNECTION,   // 1:protocol 1:name_l n:name 1:comment_l n:comment
	PH_REQ_CONNECTION_H, // HOSTな接続要求
	PH_RES_CONNECTION,   // 1:server_name_l n:server_name 2:ID 1:name_l n:name 1:comment_l n:comment 1:state
	PH_MESSAGE,          // 2:ID 1:msg_l n:msg
	PH_NOTICE,           // 1:len n:notice
	PH_REQ_LIST,         // 2:ID 0で全員分
	PH_RES_LIST,         // 2:ID 1:name_l n:name 1:comment_l n:comment 1:state 4:IP 2:Port + 暗号
	PH_NEW_MEMBER,       // 上と同じ
	PH_QUIT,             // 2:ID
	PH_LOST,             // 2:ID
	PH_CHANGE_STATE,     // 2:ID 1:STATE
	PH_REQ_STATE,        // 2:ID
	PH_RES_STATE,        // 2:ID 1:STATE
	PH_REQ_VS,           // 2:ID
	PH_RES_VS,           // 1:state
	PH_REQ_VS_PING,      // 1:ID 5個バラでsend
	PH_RES_VS_PONG,      // 1秒間に4個以上受信で対戦開始
	PH_REQ_VS_DELAY,     // 1:delay
	PH_RES_VS_DELAY,     // 1:delay 4:seed localとhostで大きな値にあわせる
	PH_VS_DATA,          // 4:frame n:data 4*delay個分送信
	PH_REQ_VS_DATA,      // 4:frame パケット来てないので緊急要請
	PH_RES_VS_DATA,      // 4:frame 2:input
	PH_VS_END,
	PH_REQ_WATCH,        // 2:ID
	PH_RES_WATCH,        // 1:state (2:P1ID 2:P2ID 4:seed)  state = 0:観戦開始+() 1:観戦不許可 2:満席 3:遅刻
	PH_WATCH_DATA,       // 4:frame 40:10フレーム分のデータ
	PH_WATCH_END,        // 2:ID 自分のと同じIDなら観戦終了、他のIDならリストから削除
	PH_SECRET,           // 1:type n:typeごとにいろいろ
} LUNA_PORT_PACKET_HEADER;

typedef enum {
	ST_PING,             // 4:time
	ST_PONG,
} SECRET_TYPE;

typedef enum {
	VS_REQ,
	VS_PING,
	VS_DELAY,
	VS_STANDBY,
	VS_DATA,
	VS_END,
	VS_TIMEOUT,
} VERSUS_SEQUENCE;

extern LUNA_PORT LUNAPORT;
extern LUNA_PORT_MT_OPTION LPMTOPTION;
extern LUNA_PORT_MT_WINDOW_STATE LPMTWS;
extern LUNA_PORT_MT_COLOR LPMTCOLOR;


public ref class PacketPacker
{
public:
	PacketPacker(void)
	{
		Length = 0;
		Packet = gcnew array<BYTE>(MAX_PACKET);
	}

protected:
	‾PacketPacker()
	{
		if(Packet != nullptr){
			delete Packet;
		}
	}

public:
	int Length;
	array<BYTE>^ Packet;

	void Pack(BYTE data){
		Packet[Length] = data;
		Length++;
	}

	void Pack(array<BYTE>^% data){
		Array::Copy(data, 0, Packet, Length, data->Length);
		Length += data->Length;
	}

	void Clear(){
		Length = 0;
		Packet->Clear(Packet, 0, MAX_PACKET);
	}
};

public ref class PacketDivider
{
public:
	int Length;
	array<BYTE>^ Packet;

	PacketDivider(array<BYTE>^% datagram)
	{
		Length = 0;
		Packet = datagram;
	}

	BYTE Divide(){
		return Packet[Length++];
	}

	array<BYTE>^ Divide(int length){
		array<BYTE>^ data = gcnew array<BYTE>(length);

		Array::Copy(Packet, Length, data, 0, length);
		Length += length;

		return data;
	}
};

// 暗号復号用乱数
inline UINT CipherRand(UINT seed = 0)
{
	static UINT a[4] = {1812433254, 3713160357, 3109174145, 64984499};

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
inline UINT XorShift(UINT seed = 0)
{
	static UINT a[4] = {1812433254, 3713160357, 3109174145, 64984499};

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

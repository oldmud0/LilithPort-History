#include "stdafx.h"
#include "Form1.h"

using namespace LunaPortMT;

void Form1::Begin()
{
	MemberInfo^ me = gcnew MemberInfo;
	me->IP_EP   = gcnew IPEndPoint(0, 0);
	me->ID      = 0;
	me->NAME    = gcnew String(LPMTOPTION.NAME);
	me->COMMENT = gcnew String(LPMTOPTION.COMMENT);
	me->TYPE    = LPMTOPTION.CONNECTION_TYPE;
	me->STATE   = MS_FREE;

	MemberList->Add(me);
	listBoxMember->Items->Add(me->NAME);

	try{
		// 回線設定
		if(LPMTOPTION.CONNECTION_TYPE == CT_SERVER || LPMTOPTION.CONNECTION_TYPE == CT_HOST){
			UDP = gcnew UdpClient(LPMTOPTION.OPEN_PORT);
		}
		else if(LPMTOPTION.CONNECTION_TYPE == CT_CLIENT){
			UDP = gcnew UdpClient;
		}
	}
	catch(SocketException^ e){
		UDP = nullptr;

		if(e->ErrorCode == WSAEADDRINUSE){
			WriteMessage("開放ポートが他のアプリケーションで使用されています。¥n", ErrorMessageColor);
		}
		else{
			WriteMessage(String::Format("UDPの初期化に失敗しました。({0})¥n", e->ErrorCode), ErrorMessageColor);
			if(LUNAPORT.DEBUG) WriteMessage(e->ToString() + "¥n", DebugMessageColor);
		}
	}

	// ネットに接続
	if(UDP != nullptr){
		ServerName = gcnew String(LPMTOPTION.CONNECTION_IP);

		if(LPMTOPTION.CONNECTION_TYPE == CT_SERVER){
			// 鯖受信開始
			UDP->BeginReceive(gcnew AsyncCallback(ReceivePackets), this);

			// ソナー軌道
			Ranging = true;
			SonarThread = gcnew Thread(gcnew ThreadStart(this, &Form1::RunSonar));
			SonarThread->Start();

			this->Text += String::Format("  [Server : {0}]", ServerName);
			WriteMessage("サーバの準備が完了しました。¥n", SystemMessageColor);
		}
		else{
			// クライアント
			IPEndPoint^ ep = gcnew IPEndPoint(0, 0);

			if(IPAddress::TryParse(ServerName, ep->Address)){
				ep = gcnew IPEndPoint(IPAddress::Parse(ServerName), LPMTOPTION.PORT);
			}
			else{
				WriteMessage("接続先のアドレスが不正です。¥n", ErrorMessageColor);
				Restart();
			}

			PacketPacker^ pp = gcnew PacketPacker;
			array<BYTE>^ name = Encoding::Unicode->GetBytes(me->NAME);
			array<BYTE>^ cmnt = Encoding::Unicode->GetBytes(me->COMMENT);

			pp->Pack(LPMTOPTION.CONNECTION_TYPE == CT_CLIENT ? (BYTE)PH_REQ_CONNECTION : (BYTE)PH_REQ_CONNECTION_H);
			pp->Pack(PROTOCOL_VERSION);
			pp->Pack((BYTE)name->Length);
			pp->Pack(name);
			pp->Pack((BYTE)cmnt->Length);
			pp->Pack(cmnt);

			// サーバに接続要求
			UDP->Send(pp->Packet, pp->Length, ep);

			try{
				// 返信待ち
				UDP->Client->ReceiveTimeout = TIME_OUT;
				array<BYTE>^ rcv = UDP->Receive(ep);
				UDP->Client->ReceiveTimeout = 0;

				PacketDivider^ pd = gcnew PacketDivider(rcv);

				// 接続OK
				if(pd->Divide() == PH_RES_CONNECTION){
					int len = pd->Divide();

					ServerName = Encoding::Unicode->GetString(pd->Divide(len));
					MemberList[0]->ID = BitConverter::ToUInt16(pd->Divide(2), 0);

					if(MemberList[0]->ID > MAX_ID){
						throw gcnew SocketException;
					}

					MemberInfo^ mi = gcnew MemberInfo;
					mi->IP_EP    = ep;
					mi->ID       = 0;
					mi->TYPE     = CT_SERVER;
					mi->NUM_VS   = 0;
					mi->RESPONSE = timeGetTime();

					// 名前
					len = pd->Divide();
					mi->NAME = Encoding::Unicode->GetString(pd->Divide(len));

					// コメント
					len = pd->Divide();
					mi->COMMENT = Encoding::Unicode->GetString(pd->Divide(len));

					// 状態
					mi->STATE = pd->Divide();

					MemberList->Add(mi);

					switch(ListView){
					case LV_NAME:
						listBoxMember->Items->Add(mi->NAME);
						break;

					case LV_COMMENT:
						if(mi->COMMENT->Length > 0){
							listBoxMember->Items->Add(mi->COMMENT);
						}
						else{
							listBoxMember->Items->Add(gcnew String("#"));
						}
						break;
					}

					// 蔵受信開始
					UDP->BeginReceive(gcnew AsyncCallback(ReceivePackets), this);

					if(LPMTOPTION.CONNECTION_TYPE == CT_HOST){
						this->Text += String::Format("  [Host : {0}]", ServerName);
					}
					else{
						this->Text += String::Format("  [Client : {0}]", ServerName);
					}
					WriteMessage(String::Format("{0}に接続しました。 (ID = {1})¥n", ServerName, me->ID), SystemMessageColor);

					if(ServerName[0] == '@'){
						WriteMessage("チャット禁止サーバです。¥n", SystemMessageColor);
					}

					// 鯖主のコメント表示
					//WriteComment(mi->NAME, mi->TYPE, mi->COMMENT);

					// メンバーリストを要求
					pp->Clear();
					pp->Pack(PH_REQ_LIST);
					pp->Pack(0);
					pp->Pack(0);
					UDP->Send(pp->Packet, pp->Length, ep);

					// ソナー起動
					Ranging = true;
					SonarThread = gcnew Thread(gcnew ThreadStart(this, &Form1::RunSonar));
					SonarThread->Start();
				}
				else{
					throw gcnew SocketException;
				}
			}
			catch(SocketException^ e){
				Leave(false);

				WriteMessage("サーバに接続できませんでした。¥n", ErrorMessageColor);

				if(me->ID == 0xFFFF){
					WriteMessage(String::Format("{0}は満室です。¥n", ServerName), ErrorMessageColor);
				}
				else if(me->ID == 0xFFFE){
					WriteMessage("プロトコルのバージョンが違います。¥n", ErrorMessageColor);
				}
				else if(me->ID > MAX_ID){
					WriteMessage(String::Format("{0}はこれ以上IDを発行できません。¥n", ServerName), ErrorMessageColor);
				}

				if(e->ErrorCode == WSAECONNRESET){
					WriteMessage("サーバのポートが開いていません。¥n", ErrorMessageColor);
				}
				else if(e->ErrorCode != 0){
					WriteMessage(e->ToString() + "¥n", ErrorMessageColor);
				}
			}
		}
	}
	else if(LPMTOPTION.CONNECTION_TYPE != CT_FREE){
		Leave(false);
	}
	else{
		this->Text += "  [Free Play]";
	}
}

void Form1::PacketSendAllMember(array<BYTE>^% datagram, int bytes, UINT received_id)
{
	Monitor::Enter(MemberList);
	try{
		for(int i = 1; i < MemberList->Count; i++){
			if(received_id != MemberList[i]->ID){
				UDP->BeginSend(datagram, bytes, MemberList[i]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);
			}
		}
	}
	finally{
		Monitor::Exit(MemberList);
	}
}

void Form1::PacketSendIDMember(array<BYTE>^% datagram, int bytes, UINT id)
{
	Monitor::Enter(MemberList);
	try{
		for(int i = 1; i < MemberList->Count; i++){
			if(id == MemberList[i]->ID){
				UDP->Send(datagram, bytes, MemberList[i]->IP_EP);
				break;
			}
		}
	}
	finally{
		Monitor::Exit(MemberList);
	}
}

void Form1::SendPackets(IAsyncResult^ asyncResult)
{
	UdpClient^ udp = (UdpClient^)asyncResult->AsyncState;

	try{
		udp->EndSend(asyncResult);
	}
	catch(ObjectDisposedException^){
	}
}

void Form1::ReceivePackets(IAsyncResult^ asyncResult)
{
	int i;
	UINT16 id;
	array<BYTE> ^send;

	Form1^ form = safe_cast<Form1^>(asyncResult->AsyncState);
	IPEndPoint^ ep = gcnew IPEndPoint(IPAddress::Any, 0);

	try{
		array<BYTE>^ rcv = UDP->EndReceive(asyncResult, ep);
		UDP->BeginReceive(gcnew AsyncCallback(ReceivePackets), form);

		switch(rcv[0]){
		case PH_PING:
			rcv[0] = PH_PONG;
			UDP->Send(rcv, rcv->Length, ep);
			break;

		case PH_PONG:
			if(rcv->Length == 1 && Ping > 0){
				form->WriteMessage(String::Format("Ping : {0}ms¥n", timeGetTime() - Ping), SystemMessageColor);
				Ping = 0;
			}
			break;

		case PH_PING_PROXY:
			rcv[0] = PH_PINGPONG;
			id = BitConverter::ToUInt16(rcv, 3);

			form->PacketSendIDMember(rcv, rcv->Length, id);
			break;

		case PH_PINGPONG:
			rcv[0] = PH_PONG_PROXY;
			UDP->Send(rcv, rcv->Length, ep);
			break;

		case PH_PONG_PROXY:
			rcv[0] = PH_PONG;
			id = BitConverter::ToUInt16(rcv, 1);

			form->PacketSendIDMember(rcv, rcv->Length, id);
			break;

		case PH_REQ_CONNECTION:
		case PH_REQ_CONNECTION_H:
			// 鯖じゃないのに接続要求が来た
			if(LPMTOPTION.CONNECTION_TYPE != CT_SERVER){
				break;
			}

			Monitor::Enter(MemberList);
			try{
				array<BYTE>^ a_id;
				array<BYTE>^ saba = Encoding::Unicode->GetBytes(ServerName);
				array<BYTE>^ name = Encoding::Unicode->GetBytes(MemberList[0]->NAME);
				array<BYTE>^ cmnt = Encoding::Unicode->GetBytes(MemberList[0]->COMMENT);

				MemberInfo^ mi;
				PacketPacker^  pp = gcnew PacketPacker;
				PacketDivider^ pd = gcnew PacketDivider(rcv);

				i = pd->Divide() == PH_REQ_CONNECTION ? CT_CLIENT : CT_HOST;

				// サーバ名
				pp->Pack(PH_RES_CONNECTION);
				pp->Pack((BYTE)saba->Length);
				pp->Pack(saba);

				// IDの発行
				if(MemberList->Count > (int)LPMTOPTION.MAX_CONNECTIONS){
					// 満室
					a_id = gcnew array<BYTE>{ 0xFF, 0xFF };
				}
				else if(pd->Divide() != PROTOCOL_VERSION){
					// プロトコル違い
					a_id = gcnew array<BYTE>{ 0xFE, 0xFF };
				}
				else{
					a_id = BitConverter::GetBytes(++IDCounter);

					if(IDCounter <= MAX_ID){
						if(IDCounter == MAX_ID){
							form->WriteMessage("発行IDが限界に達しました。¥n", ErrorMessageColor);
						}

						// メンバー登録
						mi = gcnew MemberInfo;
						mi->IP_EP    = ep;
						mi->ID       = IDCounter;
						mi->TYPE     = i;
						mi->STATE    = MS_FREE;
						mi->NUM_VS   = 0;
						mi->RESPONSE = timeGetTime();

						// 名前
						i = pd->Divide();
						mi->NAME = Encoding::Unicode->GetString(pd->Divide(i));

						// コメント
						i = pd->Divide();
						mi->COMMENT = Encoding::Unicode->GetString(pd->Divide(i));

						MemberList->Add(mi);

						switch(ListView){
						case LV_NAME:
							form->listBoxMember->Items->Add(mi->NAME);
							break;

						case LV_COMMENT:
							if(mi->COMMENT->Length > 0){
								form->listBoxMember->Items->Add(mi->COMMENT);
							}
							else{
								form->listBoxMember->Items->Add(gcnew String("#"));
							}
							break;
						}

						if(mi->COMMENT->Length > 0){
							form->WriteComment(mi->NAME, mi->TYPE, mi->COMMENT);
						}
						else{
							form->WriteMessage(String::Format("{0}が入室しました。¥n", mi->NAME), SystemMessageColor);
						}

						if(LUNAPORT.DEBUG){
							form->WriteMessage(String::Format("Connect from {0}:{1}¥n", ep->Address, ep->Port), DebugMessageColor);
						}
					}
					else if(IDCounter > MAX_ID){
						IDCounter = MAX_ID;
					}
				}

				// ID
				pp->Pack(a_id);

				// 鯖主のニックネーム
				pp->Pack((BYTE)name->Length);
				pp->Pack(name);

				// 鯖主のコメント
				pp->Pack((BYTE)cmnt->Length);
				pp->Pack(cmnt);

				// 状態
				pp->Pack((BYTE)MemberList[0]->STATE);

				// 登録完了
				UDP->Send(pp->Packet, pp->Length, ep);

				if(mi != nullptr){
					pp->Clear();

					// 全員に入室を通知
					name = Encoding::Unicode->GetBytes(mi->NAME);
					cmnt = Encoding::Unicode->GetBytes(mi->COMMENT);
					array<BYTE>^ address = ep->Address->GetAddressBytes();
					array<BYTE>^ port = BitConverter::GetBytes((UINT16)ep->Port);

					a_id[1] |= mi->TYPE << 6;

					pp->Pack(PH_NEW_MEMBER);
					pp->Pack(a_id);
					pp->Pack((BYTE)name->Length);
					pp->Pack(name);
					pp->Pack((BYTE)cmnt->Length);
					pp->Pack(cmnt);
					pp->Pack(MS_FREE);
					pp->Pack(address);
					pp->Pack(port);

					// 簡易暗号
					Monitor::Enter(ServerName);
					try{
						CipherRand(ServerName->GetHashCode());

						for(i = 1; i < pp->Length; i++){
							pp->Packet[i] ^= CipherRand();
						}
					}
					finally{
						Monitor::Exit(ServerName);
					}

					for(i = 1; i < MemberList->Count - 1; i++){
						UDP->BeginSend(pp->Packet, pp->Length, MemberList[i]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);
					}
				}
			}
			finally{
				Monitor::Exit(MemberList);
			}

			// Welcomeメッセージ
			i = _tcslen(LPMTOPTION.WELCOME)*2;

			if(i > 0){
				Thread::Sleep(50);

				PacketPacker^ pp = gcnew PacketPacker;

				pp->Pack(PH_NOTICE);
				pp->Pack((BYTE)i);
				pp->Pack(Encoding::Unicode->GetBytes(gcnew String(LPMTOPTION.WELCOME)));

				UDP->Send(pp->Packet, pp->Length, ep);
			}
			break;

		case PH_MESSAGE:
			if(ServerName[0] == '@'){
				break;
			}

			if(LPMTOPTION.CONNECTION_TYPE == CT_SERVER){
				form->TalkMessage(BitConverter::ToUInt16(rcv, 1), rcv);
			}
			else{
				// 受信ONLY
				form->TalkMessage(0xFFFF, rcv);
			}
			break;

		case PH_NOTICE:
			if(UDP != nullptr){
				form->WriteNotice(Encoding::Unicode->GetString(rcv, 2, rcv[1]));
			}
			break;

		case PH_REQ_LIST:
			if(LPMTOPTION.CONNECTION_TYPE != CT_SERVER){
				return;
			}
			else{
				id = BitConverter::ToUInt16(rcv, 1);
				array<BYTE> ^a_id, ^name, ^cmnt, ^address, ^port;
				PacketPacker^ pp = gcnew PacketPacker;

				Monitor::Enter(MemberList);
				try{
					for(i = 1; i < MemberList->Count; i++){
						// id == 0で全員分
						if(id == 0 || id == MemberList[i]->ID){
							a_id = BitConverter::GetBytes((UINT16)(MemberList[i]->ID | MemberList[i]->TYPE << 14));
							name = Encoding::Unicode->GetBytes(MemberList[i]->NAME);
							cmnt = Encoding::Unicode->GetBytes(MemberList[i]->COMMENT);
							address = MemberList[i]->IP_EP->Address->GetAddressBytes();
							port = BitConverter::GetBytes((UINT16)MemberList[i]->IP_EP->Port);

							pp->Clear();
							pp->Pack(PH_RES_LIST);
							pp->Pack(a_id);
							pp->Pack((BYTE)name->Length);
							pp->Pack(name);
							pp->Pack((BYTE)cmnt->Length);
							pp->Pack(cmnt);
							pp->Pack((BYTE)MemberList[i]->STATE);
							pp->Pack(address);
							pp->Pack(port);

							// 簡易暗号
							Monitor::Enter(ServerName);
							try{
								CipherRand(ServerName->GetHashCode());

								for(int j = 1; j < pp->Length; j++){
									pp->Packet[j] ^= CipherRand();
								}
							}
							finally{
								Monitor::Exit(ServerName);
							}

							UDP->BeginSend(pp->Packet, pp->Length, ep, gcnew AsyncCallback(SendPackets), UDP);

							if(id > 0){
								break;
							}
						}
					}

					if(id > 0 && i >= MemberList->Count){
						if(LUNAPORT.DEBUG){
							form->WriteMessage(String::Format("ERROR > 未登録者({0})の検索¥n", id), DebugMessageColor);
						}
					}
				}
				finally{
					Monitor::Exit(MemberList);
				}
			}
			break;

		case PH_RES_LIST:
		case PH_NEW_MEMBER:
			// 簡易復号
			Monitor::Enter(ServerName);
			try{
				CipherRand(ServerName->GetHashCode());

				for(i = 1; i < rcv->Length; i++){
					rcv[i] ^= CipherRand();
				}
			}
			finally{
				Monitor::Exit(ServerName);
			}

			id = BitConverter::ToUInt16(rcv, 1);

			if((id & 0x3FFF) != MemberList[0]->ID){
				int len;
				PacketDivider^ pd = gcnew PacketDivider(rcv);
				pd->Length = 3;

				Monitor::Enter(MemberList);
				try{
					MemberInfo^ mi = gcnew MemberInfo;
					mi->IP_EP  = gcnew IPEndPoint(0, 0);
					mi->ID     = id & 0x3FFF;
					mi->TYPE   = id >> 14;
					mi->NUM_VS = 0;

					// 名前
					len = pd->Divide();
					mi->NAME = Encoding::Unicode->GetString(pd->Divide(len));

					// コメント
					len = pd->Divide();
					mi->COMMENT = Encoding::Unicode->GetString(pd->Divide(len));

					// 状態
					mi->STATE = pd->Divide();

					// エンドポイント
					mi->IP_EP->Address = gcnew IPAddress(pd->Divide(4));
					mi->IP_EP->Port    = BitConverter::ToUInt16(pd->Divide(2), 0);

					MemberList->Add(mi);

					switch(ListView){
					case LV_NAME:
						form->listBoxMember->Items->Add(mi->NAME);
						break;

					case LV_COMMENT:
						if(mi->COMMENT->Length > 0){
							form->listBoxMember->Items->Add(mi->COMMENT);
						}
						else{
							form->listBoxMember->Items->Add(gcnew String("#"));
						}
						break;
					}

					// 挨拶代わり
					UDP->Send(gcnew array<BYTE>{PH_PING}, 1, mi->IP_EP);

					if(rcv[0] == PH_NEW_MEMBER){
						if(mi->COMMENT->Length > 0){
							form->WriteComment(mi->NAME, mi->TYPE, mi->COMMENT);
						}
						else{
							form->WriteMessage(String::Format("{0}が入室しました。¥n", mi->NAME), SystemMessageColor);
						}
					}
				}
				finally{
					Monitor::Exit(MemberList);
				}
			}
			break;

		case PH_QUIT:
		case PH_LOST:
			id = BitConverter::ToUInt16(rcv, 1);

			Monitor::Enter(MemberList);
			try{
				if(LPMTOPTION.CONNECTION_TYPE == CT_SERVER){
					int member = 0;
					// 全員に通達
					for(i = 1; i < MemberList->Count; i++){
						if(id != MemberList[i]->ID){
							UDP->BeginSend(rcv, rcv->Length, MemberList[i]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);
						}
						else{
							member = i;
						}
					}

					if(member > 0){
						form->WriteMessage(MemberList[member]->NAME + "が退室しました。¥n", SystemMessageColor);

						// 観戦中止
						if(MemberList[0]->STATE == MS_WATCH || MemberList[0]->STATE == MS_COUCH){
							if(TargetID == MemberList[member]->ID){
								form->QuitWatch(false);
							}
						}
						MemberList->RemoveAt(member);
						form->listBoxMember->Items->RemoveAt(member);
					}
				}
				else{
					if(id == 0){
						form->WriteMessage(ServerName + "がシャットダウンしました。¥n", SystemMessageColor);
						MemberList[0]->STATE = 0xFF;
					}
					else if(id == 0xFFFF){
						form->WriteMessage(ServerName + "には登録されていません。¥n時間を置いて再接続してみてください。¥n", ErrorMessageColor);
						MemberList[0]->STATE = 0xFF;
					}
					else{
						for(i = 0; i < MemberList->Count; i++){
							if(id == MemberList[i]->ID){
								if(i == 0){
									form->WriteMessage("サーバとの接続が切断されました。¥n", ErrorMessageColor);
									MemberList[0]->STATE = 0xFF;
								}
								else{
									if(rcv[0] == PH_QUIT){
										form->WriteMessage(MemberList[i]->NAME + "が退室しました。¥n", SystemMessageColor);
									}
									else{
										form->WriteMessage(MemberList[i]->NAME + "の回線が途切れました。¥n", ErrorMessageColor);
									}

									// 観戦中止
									if(MemberList[0]->STATE == MS_WATCH || MemberList[0]->STATE == MS_COUCH){
										if(TargetID == MemberList[i]->ID){
											form->QuitWatch(false);
										}
									}

									MemberList->RemoveAt(i);
									form->listBoxMember->Items->RemoveAt(i);
								}

								break;
							}
						}
					}
				}
			}
			finally{
				Monitor::Exit(MemberList);
			}

			if(MemberList[0]->STATE == 0xFF){
				form->Leave(false);
			}
			break;

		case PH_CHANGE_STATE:
			id = BitConverter::ToUInt16(rcv, 1);

			Monitor::Enter(MemberList);
			try{
				for(i = 0; i < MemberList->Count; i++){
					if(id == MemberList[i]->ID){
						MemberList[i]->STATE = rcv[3];
						form->listBoxMember->Refresh();

						if(LPMTOPTION.CONNECTION_TYPE != CT_SERVER){
							break;
						}
					}
					else if(i != 0 && LPMTOPTION.CONNECTION_TYPE == CT_SERVER){
						UDP->BeginSend(rcv, rcv->Length, MemberList[i]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);
					}
				}
			}
			finally{
				Monitor::Exit(MemberList);
			}
			break;

		case PH_REQ_STATE:
			id = BitConverter::ToUInt16(rcv, 1);

			Monitor::Enter(MemberList);
			try{
				send = gcnew array<BYTE>(4){ PH_RES_STATE, rcv[1], rcv[2], 0xFF };

				if(LPMTOPTION.CONNECTION_TYPE == CT_SERVER){
					for(i = 0; i < MemberList->Count; i++){
						if(id == MemberList[i]->ID){
							send[3] = (BYTE)MemberList[i]->STATE;
							break;
						}
					}
				}
				else if(id == MemberList[0]->ID){
					send[3] = (BYTE)MemberList[0]->STATE;
				}

				UDP->Send(send, send->Length, ep);
			}
			finally{
				Monitor::Exit(MemberList);
			}
			break;

		case PH_RES_STATE:
			id = BitConverter::ToUInt16(rcv, 1);

			Monitor::Enter(MemberList);
			try{
				for(i = 1; i < MemberList->Count; i++){
					if(id == MemberList[i]->ID){
						MemberList[i]->RESPONSE = timeGetTime();

						if(rcv[3] == 0xFF){
							// そんな人いなかった
							form->WriteMessage(MemberList[i]->NAME + "は既にいませんでした。¥n", SystemMessageColor);

							if(LPMTOPTION.CONNECTION_TYPE == CT_SERVER){
								// 全員に通達
								rcv[0] = PH_LOST;

								for(int j = 1; j < MemberList->Count; j++){
									if(id != MemberList[j]->ID){
										UDP->BeginSend(rcv, 3, MemberList[j]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);
									}
								}
							}
							else{
								// いなかった通知 応急処置Ver
								// 蔵からのみ見えている状態
								// サーバには情報がないので間接的に通知してもらう
								rcv[0] = PH_LOST;
								rcv[1] = 0xFF;
								rcv[2] = 0xFF;
								UDP->Send(rcv, 3, MemberList[i]->IP_EP);
							}

							MemberList->RemoveAt(i);
							form->listBoxMember->Items->RemoveAt(i);
						}
						else if(MemberList[i]->STATE != rcv[3]){
							if(LUNAPORT.DEBUG) form->WriteMessage(String::Format(MemberList[i]->NAME + " > state:{0}¥n", rcv[3]), DebugMessageColor);
							form->WriteMessage(MemberList[i]->NAME + "の状態を更新しました。¥n", SystemMessageColor);
							MemberList[i]->STATE = rcv[3];
							form->listBoxMember->Refresh();
						}
						break;
					}
				}
			}
			finally{
				Monitor::Exit(MemberList);
			}
			break;

		case PH_REQ_VS:
			// 準備時間が長すぎた場合は新規接続受付
			if(NetVS != nullptr && MemberList[0]->STATE == MS_READY){
				if((timeGetTime() - NetVS->START_UP) > TIME_OUT*2 + 1000){
					MemberList[0]->STATE = MS_FREE;
					delete NetVS;
					NetVS = nullptr;
				}
			}

			send = gcnew array<BYTE>(2);
			send[0] = PH_RES_VS;
			send[1] = (BYTE)MemberList[0]->STATE;

			// 格ツクじゃないよ
			try{
				FileVersionInfo^ info = FileVersionInfo::GetVersionInfo(gcnew String(LPMTOPTION.GAME_EXE));

				if(info->FileDescription != "２Ｄ格闘ツクール2nd."){
					throw gcnew Exception;
				}
			}
			catch(Exception^){
				form->WriteMessage("2D格闘ツクール2nd.の実行ファイルではありません。¥n", ErrorMessageColor);
				form->WriteMessage("オプションで実行ファイルのパスを設定してください。¥n", ErrorMessageColor);
				send[1] = 0xFF;
			}

			UDP->BeginSend(send, send->Length, ep, gcnew AsyncCallback(SendPackets), UDP);

			if(send[1] == MS_FREE){
				MemberList[0]->STATE = MS_READY;

				id = BitConverter::ToUInt16(rcv, 1);

				Monitor::Enter(MemberList);
				try{
					for(i = 0; i < MemberList->Count; i++){
						if(id == MemberList[i]->ID) break;
					}

					if(i >= MemberList->Count){
						form->WriteMessage("リストにいない人物からの対戦要求がありました。¥n", ErrorMessageColor);
						MemberList[0]->STATE = MS_FREE;

						if(LPMTOPTION.CONNECTION_TYPE != CT_SERVER){
							// 知らない人がいたのでサーバに問い合わせ
							array<BYTE>^ send = gcnew array<BYTE>(3){ PH_REQ_LIST };
							Array::Copy(BitConverter::GetBytes(id), 0, send, 1, 2);
							UDP->Send(send, 3, MemberList[1]->IP_EP);
						}
						break;
					}

					NetVS = gcnew VersusInfo;
					NetVS->SEQUENCE = VS_DELAY;
					NetVS->SLEEPING = false;
					NetVS->WAITING  = false;
					NetVS->START_UP = timeGetTime();
					NetVS->IP_EP    = ep;
					NetVS->PING     = gcnew array<UINT>(5){ 0, 0, 0, 0, 0 };
					NetVS->PONG     = gcnew array<UINT>(5){ 0, 0, 0, 0, 0 };
					NetVS->SEND     = gcnew array<BYTE>(32){ PH_VS_DATA };
					NetVS->L_FRAME  = 0;
					NetVS->L_READ   = 0;
					NetVS->R_FRAME  = 0;
					NetVS->R_READ   = 0;

					// 観戦用ID
					P1ID = MemberList[0]->ID;
					P2ID = id;

					// 名前
					_tcscpy_s(LUNAPORT.P1_NAME, LPMTOPTION.NAME);

					IntPtr mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(MemberList[i]->NAME);
					_tcscpy_s(LUNAPORT.P2_NAME, static_cast<PTCHAR>(mp.ToPointer()));
					Runtime::InteropServices::Marshal::FreeHGlobal(mp);

					// 対戦回数
					MemberList[i]->NUM_VS++;

					form->WriteMessage(MemberList[i]->NAME, NameColor[MemberList[i]->TYPE]);
					form->WriteMessage("から対戦の申し込みです。¥n", SystemMessageColor);
				}
				finally{
					Monitor::Exit(MemberList);
				}
			}
			break;

		case PH_RES_VS:
			if(rcv[1] != MS_FREE){
				switch(rcv[1]){
				case MS_REST:
					form->WriteMessage("挑戦相手は休憩中です。¥n", SystemMessageColor);
					break;
				case MS_VS:
					form->WriteMessage("挑戦相手は対戦中です。¥n", SystemMessageColor);
					break;
				case MS_WATCH:
				case MS_COUCH:
					form->WriteMessage("挑戦相手は観戦中です。¥n", SystemMessageColor);
					break;
				case MS_READY:
					form->WriteMessage("挑戦相手は他の人と対戦準備中です。¥n", SystemMessageColor);
					break;
				default:
					form->WriteMessage("挑戦相手が対戦出来る状態ではありません。¥n", SystemMessageColor);
					break;
				}
			}
			else if(NetVS != nullptr){
				NetVS->SEQUENCE = VS_PING;

				if(VersusThread != nullptr && VersusThread->IsAlive && NetVS->SLEEPING){
					VersusThread->Interrupt();
				}
			}
			break;

		case PH_REQ_VS_PING:
			rcv[0] = PH_RES_VS_PONG;
			UDP->Send(rcv, rcv->Length, ep);
			break;

		case PH_RES_VS_PONG:
			if(NetVS != nullptr){
				NetVS->PONG[rcv[1]] = timeGetTime();

				for(id = 0, i = 0; id < 5; id++){
					if(NetVS->PONG[id] > 0){
						i++;

						if(i == 4){
							if(NetVS->SEQUENCE == VS_PING){
								NetVS->SEQUENCE = VS_DELAY;
							
								if(VersusThread != nullptr && VersusThread->IsAlive && NetVS->SLEEPING){
									VersusThread->Interrupt();
								}
							}
							break;
						}
					}
				}
			}
			break;

		case PH_REQ_VS_DELAY:
			if(NetVS != nullptr && NetVS->SEQUENCE == VS_DELAY){
				UINT32 seed;
				send = gcnew array<BYTE>(6){ PH_RES_VS_DELAY };

				seed = XorShift();

				// ディレイ
				if(LPMTOPTION.DELAY == 0 || rcv[1] > LPMTOPTION.DELAY){
					send[1] = rcv[1];
				}
				else{
					send[1] = (BYTE)LPMTOPTION.DELAY;
				}

				NetVS->SEQUENCE = VS_DATA;
				NetVS->DELAY    = send[1];
				NetVS->LOCAL    = gcnew array<UINT16>(NetVS->DELAY*4);
				NetVS->REMOTE   = gcnew array<UINT16>(NetVS->DELAY*4);

				for(i = 0; i < NetVS->LOCAL->Length; i++){
					NetVS->LOCAL[i]  = 0xFFFF;
					NetVS->REMOTE[i] = 0xFFFF;
				}

				for(UINT i = 0; i < NetVS->DELAY; i++){
					NetVS->LOCAL[i] = 0x0000;
				}

				LUNAPORT.SEED = seed;

				Array::Copy(BitConverter::GetBytes(seed), 0, send, 2, 4);
				UDP->Send(send, send->Length, ep);

				LUNAPORT.CONTROL = 0;

				// 対戦開始
				form->WriteMessage(String::Format("対戦を開始します。(delay:{0})¥n", NetVS->DELAY), SystemMessageColor);

				// 音でお知らせ
				try{
					Media::SoundPlayer^ wav = gcnew Media::SoundPlayer(gcnew String(LPMTOPTION.VS_SOUND));
					wav->Play();
				}
				catch(Exception^){
				}

				GameThread = gcnew Thread(gcnew ParameterizedThreadStart(form, &Form1::RunGame));
				GameThread->Start((UINT)RT_VS);
			}
			break;

		case PH_RES_VS_DELAY:
			if(NetVS != nullptr){
				NetVS->DELAY  = rcv[1];
				NetVS->LOCAL  = gcnew array<UINT16>(NetVS->DELAY*4);
				NetVS->REMOTE = gcnew array<UINT16>(NetVS->DELAY*4);

				for(i = 0; i < NetVS->LOCAL->Length; i++){
					NetVS->LOCAL[i]  = 0xFFFF;
					NetVS->REMOTE[i] = 0xFFFF;
				}

				for(UINT i = 0; i < NetVS->DELAY; i++){
					NetVS->LOCAL[i] = 0x0000;
				}

				LUNAPORT.SEED = BitConverter::ToUInt32(rcv, 2);

				if(VersusThread != nullptr && VersusThread->IsAlive && NetVS->SEQUENCE == VS_DELAY && NetVS->SLEEPING){
					NetVS->SEQUENCE = VS_STANDBY;
					VersusThread->Interrupt();
				}
			}
			break;

		case PH_VS_END:
			if(NetVS != nullptr){
				form->WriteMessage("対戦の終了通知を受け取りました。¥n", SystemMessageColor);

				NetVS->SEQUENCE = VS_END;
				form->QuitGame();

				Monitor::Enter(NetVS->REMOTE);
				try{
					if(NetVS->WAITING == 2){
						NetVS->WAITING = 1;
						Monitor::Pulse(NetVS->REMOTE);
					}
				}
				finally{
					Monitor::Exit(NetVS->REMOTE);
				}

				if(LUNAPORT.DEBUG) form->WriteMessage(String::Format("Frame > {0}¥n", NetVS->L_FRAME), DebugMessageColor);
			}
			break;

		case PH_VS_DATA:
			if(NetVS != nullptr && NetVS->SEQUENCE == VS_DATA){
				UINT f = BitConverter::ToUInt32(rcv, 1);

				Monitor::Enter(NetVS->REMOTE);
				try{
					if(NetVS->R_FRAME > f + NetVS->DELAY){
						if(LUNAPORT.DEBUG) form->WriteMessage(String::Format("無効なパケット(遅延) > {0} / {1}¥n", f, NetVS->R_FRAME), DebugMessageColor);
						break;
					}
					else if(f > NetVS->R_FRAME + NetVS->DELAY){
						// まずこない
						if(LUNAPORT.DEBUG) form->WriteMessage(String::Format("無効なパケット(先行) > {0} / {1}¥n", f, NetVS->R_FRAME), DebugMessageColor);
						break;
					}

					for(UINT i = 0; i <= NetVS->DELAY; i++){
						if((f + i) < NetVS->R_FRAME){
							continue;
						}

						NetVS->REMOTE[(f + i) % NetVS->REMOTE->Length] = BitConverter::ToUInt16(rcv, 5 + i*2);

						if((f + i) == NetVS->R_FRAME && NetVS->WAITING == 2){
							NetVS->WAITING = 1;
							Monitor::Pulse(NetVS->REMOTE);
						}
					}
				}
				finally{
					Monitor::Exit(NetVS->REMOTE);
				}
			}
			break;

		case PH_REQ_VS_DATA:
			if(NetVS != nullptr && NetVS->SEQUENCE == VS_DATA){
				send = gcnew array<BYTE>(7);
				send[0] = PH_RES_VS_DATA;
				Array::Copy(rcv, 1, send, 1, 4);
				send[5] = 0xFF;
				send[6] = 0xFF;

				UINT f = BitConverter::ToUInt32(rcv, 1);

				Monitor::Enter(NetVS->LOCAL);
				try{
					if(f >= NetVS->L_FRAME + NetVS->DELAY){
						if(LUNAPORT.DEBUG) form->WriteMessage(String::Format("無効なパケット(先行要求) > {0} / {1}¥n", f, NetVS->L_FRAME), DebugMessageColor);
						UDP->BeginSend(send, send->Length, ep, gcnew AsyncCallback(SendPackets), UDP);
						break;
					}
					else if(NetVS->L_FRAME > f + NetVS->DELAY*2){
						// 既にデータがないのでこれがくるとゲームにならない
						if(LUNAPORT.DEBUG) form->WriteMessage(String::Format("無効なパケット(遅延要求) > {0} / {1}¥n", f, NetVS->L_FRAME), DebugMessageColor);
						break;
					}

					if(LUNAPORT.DEBUG) form->WriteMessage(String::Format("要求パケット > {0} / {1}¥n", f, NetVS->L_FRAME), DebugMessageColor);

					Array::Copy(BitConverter::GetBytes(NetVS->LOCAL[f % NetVS->LOCAL->Length]), 0, send, 5, 2);
					UDP->BeginSend(send, send->Length, ep, gcnew AsyncCallback(SendPackets), UDP);
				}
				finally{
					Monitor::Exit(NetVS->LOCAL);
				}
			}
			break;

		case PH_RES_VS_DATA:
			if(NetVS != nullptr && NetVS->WAITING > 0){
				UINT32 f = BitConverter::ToUInt32(rcv, 1);

				Monitor::Enter(NetVS->REMOTE);
				try{
					if(f != NetVS->R_FRAME) break;

					UINT16 w = BitConverter::ToUInt16(rcv, 5);

					NetVS->REMOTE[NetVS->R_READ] = w;

					if(LUNAPORT.DEBUG) form->WriteMessage(String::Format("返信パケット > {0} : {1}¥n", f, w), DebugMessageColor);

					if(NetVS->WAITING == 2){
						NetVS->WAITING = 1;
						Monitor::Pulse(NetVS->REMOTE);
					}
				}
				finally{
					Monitor::Exit(NetVS->REMOTE);
				}
			}
			break;

		case PH_REQ_WATCH:
			rcv[0] = PH_RES_WATCH;
			id = BitConverter::ToUInt16(rcv, 1);

			if(LPMTOPTION.ALLOW_SPECTATORS == false){
				// 観戦不許可
				rcv[1] = 1;
				UDP->Send(rcv, 2, ep);
				break;
			}
			else if(SpectatorList->Count >= (int)LPMTOPTION.MAX_CONNECTIONS){
				// 満席
				rcv[1] = 2;
				UDP->Send(rcv, 2, ep);
				break;
			}
			else if(InputFrame > (UINT)InputHistory->Length - 150){
				// 遅刻
				rcv[1] = 3;
				UDP->Send(rcv, 2, ep);
				break;
			}
			else if(WatchTarget != nullptr && id == TargetID){
				// 相互観戦
				rcv[1] = 4;
				UDP->Send(rcv, 2, ep);
				break;
			}
			else{
				SpectatorInfo^ si = gcnew SpectatorInfo;
				si->ID    = id;
				si->IP_EP = ep;
				si->FRAME = 0;

				if(SpectacleThread != nullptr && SpectacleThread->IsAlive && AllowWatch){
					// 既にはじめてる
					send = gcnew array<BYTE>(10);
					send[0] = PH_RES_WATCH;
					send[1] = 0;
					Array::Copy(BitConverter::GetBytes(P1ID), 0, send, 2, 2);
					Array::Copy(BitConverter::GetBytes(P2ID), 0, send, 4, 2);
					Array::Copy(BitConverter::GetBytes(LUNAPORT.SEED), 0, send, 6, 4);
					
					UDP->Send(send, send->Length, ep);

					// なかなかデンジャラスなSleep
					Thread::Sleep(100);
				}

				Monitor::Enter(InputHistory);
				try{
					SpectatorList->Add(si);
				}
				finally{
					Monitor::Exit(InputHistory);
				}

				Monitor::Enter(MemberList);
				try{
					for(i = 0 ; i < MemberList->Count; i++){
						if(id == MemberList[i]->ID){
							break;
						}
					}

					if(i >= MemberList->Count){
						// 外来客
						form->WriteMessage("観戦者が来ました。¥n", SystemMessageColor);
					}
					else{
						form->WriteMessage(MemberList[i]->NAME + "が観戦に来ました。¥n", SystemMessageColor);
					}
				}
				finally{
					Monitor::Exit(MemberList);
				}
			}
			break;

		case PH_RES_WATCH:
			if(rcv[1] > 0){
				switch(rcv[1]){
				case 1:
					form->WriteMessage("観戦が許可されていませんでした。¥n", SystemMessageColor);
					break;

				case 2:
					form->WriteMessage("観戦席は満席でした。¥n", SystemMessageColor);
					break;

				case 3:
					form->WriteMessage("観戦に間に合いませんでした。¥n", SystemMessageColor);
					break;

				case 4:
					form->WriteMessage("既に相手がこちらを観戦対象にしていました。¥n", SystemMessageColor);
					break;
				}

				form->QuitWatch(false);
			}
			else{
				if(MemberList[0]->STATE == MS_WATCH || MemberList[0]->STATE == MS_COUCH){
					ZeroMemory(LUNAPORT.P1_NAME, sizeof(LUNAPORT.P1_NAME));
					ZeroMemory(LUNAPORT.P2_NAME, sizeof(LUNAPORT.P2_NAME));

					P1ID = BitConverter::ToUInt16(rcv, 2);
					P2ID = BitConverter::ToUInt16(rcv, 4);
					LUNAPORT.SEED = BitConverter::ToUInt32(rcv, 6);

					IntPtr mp;
					int c = 0;

					Monitor::Enter(MemberList);
					try{
						// 名前
						for(i = 0; i < MemberList->Count; i++){
							if(MemberList[i]->ID == P1ID){
								mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(MemberList[i]->NAME);
								_tcscpy_s(LUNAPORT.P1_NAME, static_cast<PTCHAR>(mp.ToPointer()));
								Runtime::InteropServices::Marshal::FreeHGlobal(mp);

								c++;
							}
							else if(MemberList[i]->ID == P2ID){
								mp = Runtime::InteropServices::Marshal::StringToHGlobalAuto(MemberList[i]->NAME);
								_tcscpy_s(LUNAPORT.P2_NAME, static_cast<PTCHAR>(mp.ToPointer()));
								Runtime::InteropServices::Marshal::FreeHGlobal(mp);

								c++;
							}

							if(c == 2) break;
						}
					}
					finally{
						Monitor::Exit(MemberList);
					}

					for(i = 0; i < WatchHistory->Length; i++){
						WatchHistory[i] = 0xFFFF;
					}
					WaitingWatch = 1;

					GameThread = gcnew Thread(gcnew ParameterizedThreadStart(form, &Form1::RunGame));
					GameThread->Start((UINT)RT_WATCH);

					form->WriteMessage("観戦を開始します。¥n", SystemMessageColor);
				}
			}
			break;

		case PH_WATCH_DATA:
			if(WatchTarget != nullptr && WaitingWatch > 0){
				UINT32 f = BitConverter::ToUInt32(rcv, 1);

				if(f > WatchFrame + WatchHistory->Length - 20){
					form->WriteMessage("同期が取れなくなったため観戦を中止します。¥n", ErrorMessageColor);
					form->QuitWatch(true);
				}

				Monitor::Enter(WatchHistory);
				try{
					if(WatchFrame > f + 20){
						if(LUNAPORT.DEBUG) form->WriteMessage(String::Format("観戦パケット(遅延) > {0} / {1}¥n", f, WatchFrame), DebugMessageColor);
						break;
					}

					for(UINT i = 0; i < 20; i++){
						if((f + i) < WatchFrame){
							continue;
						}

						WatchHistory[(f + i) % WatchHistory->Length] = BitConverter::ToUInt16(rcv, 5 + i*2);

						if((f + i) == WatchFrame && WaitingWatch == 2){
							WaitingWatch = 1;
							Monitor::Pulse(WatchHistory);
						}
					}
				}
				finally{
					Monitor::Exit(WatchHistory);
				}
			}
			break;

		case PH_WATCH_END:
			id = BitConverter::ToUInt16(rcv, 1);

			if(id == MemberList[0]->ID){
				// 閉幕のお知らせ
				form->WriteMessage("観戦の終了通知を受け取りました。¥n", SystemMessageColor);
				form->QuitWatch(false);
			}
			else{
				// 観戦中止のお知らせ
				Monitor::Enter(InputHistory);
				try{
					if(LUNAPORT.DEBUG) form->WriteMessage(String::Format("観戦中止 > {0}¥n", id), DebugMessageColor);

					for(i = 0; i < SpectatorList->Count; i++){
						if(id == SpectatorList[i]->ID){
							SpectatorList->RemoveAt(i);
							break;
						}
					}
				}
				finally{
					Monitor::Exit(InputHistory);
				}
			}
			break;

		case PH_SECRET:
			switch(rcv[1]){
			case ST_PING:
				rcv[1] = ST_PONG;
				UDP->Send(rcv, rcv->Length, ep);
				break;

			default:
				break;
			}
			break;

		default:
			if(LUNAPORT.DEBUG){
				form->WriteMessage(String::Format("Unknown Socket > {0} from {1}¥n", rcv[0], ep->ToString()), DebugMessageColor);
			}
			break;
		}
	}
	catch(ObjectDisposedException^){
		// UDP接続終了
		if(UDP != nullptr){
			UDP = nullptr;
			form->WriteMessage("回線を切断しました。¥n", SystemMessageColor);
		}
	}
	catch(SocketException^ e){
		UDP->BeginReceive(gcnew AsyncCallback(ReceivePackets), form);

		if(e->ErrorCode == WSAECONNRESET){
			// パケットが弾かれた
			if(LUNAPORT.DEBUG) form->WriteMessage("あいさつ¥n", DebugMessageColor);
		}
		else{
			form->WriteMessage(String::Format("ソケットエラー({0})¥n", e->ErrorCode), ErrorMessageColor);
			if(LUNAPORT.DEBUG) form->WriteMessage(e->ToString() + "¥n", DebugMessageColor);
		}
	}
	catch(Exception^ e){
		form->WriteMessage(e->ToString() + "¥n", ErrorMessageColor);
	}
}

void Form1::RunSonar()
{
	int i, j;
	bool leave = false;
	array<BYTE>^ send = gcnew array<BYTE>(3){ PH_REQ_STATE, 0x00, 0x00 };

	SonarSleeping = false;

	// 20sに一度パケットを送り、100s以上応答がなかったら切断する
	while(Ranging){
		SonarSleeping = true;
		try{
			Thread::Sleep(20*1000);
		}
		catch(ThreadInterruptedException^){
		}
		SonarSleeping = false;

		if(!Ranging) return;

		Monitor::Enter(MemberList);
		try{
			if(LPMTOPTION.CONNECTION_TYPE == CT_SERVER){
				listBoxMember->BeginUpdate();

				for(i = 1; i < MemberList->Count; i++){
					Array::Copy(BitConverter::GetBytes(MemberList[i]->ID), 0, send, 1, 2);

					if((timeGetTime() - MemberList[i]->RESPONSE) > 100*1000){
						WriteMessage(MemberList[i]->NAME + "との通信が途絶えました。¥n", ErrorMessageColor);

						send[0] = PH_LOST;

						for(j = 1; j < MemberList->Count; j++){
							UDP->BeginSend(send, send->Length, MemberList[j]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);
						}

						MemberList->RemoveAt(i);
						listBoxMember->Items->RemoveAt(i);

						send[0] = PH_REQ_STATE;
						i--;
					}
					else{
						// 確認パケ
						UDP->BeginSend(send, send->Length, MemberList[i]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);
					}
				}

				listBoxMember->EndUpdate();
			}
			else{
				if((timeGetTime() - MemberList[1]->RESPONSE) > 100*1000){
					WriteMessage("サーバとの通信が途絶えました。¥n", ErrorMessageColor);
					leave   = true;
					Ranging = false;
				}
				else{
					UDP->Send(send, send->Length, MemberList[1]->IP_EP);
				}
			}
		}
		finally{
			Monitor::Exit(MemberList);
		}
	}

	if(leave){
		Leave(false);
	}
}

void Form1::RunGame(Object^ obj)
{
	UINT run_type = (UINT)obj;
	bool record_replay    = LPMTOPTION.RECORD_REPLAY;
	bool allow_spectators = LPMTOPTION.ALLOW_SPECTATORS;
	UINT time_limit       = LPMTOPTION.TIME_LIMIT * 100;

	Media::SoundPlayer^ wav;

	if(time_limit > 0){
		String^ path = gcnew String(LPMTOPTION.PATH);
		path += "time.wav";
		wav = gcnew Media::SoundPlayer(path);
	}

	TCHAR wdir[_MAX_PATH], buf[_MAX_PATH], drive[_MAX_DRIVE];
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DEBUG_EVENT de;
	CONTEXT c;
	HANDLE thread = NULL;
	DWORD thread_id = 0;
	DWORD state, e_code, e_address, mem;
	DWORD frames = 0, now, last_sec = 0, inputs = 0;
	int i, append_cap, def_time, last_cap = 0, num_vs = 0, p1_win = 0, p2_win = 0, timer = 0, rand_count = 0;
	bool vs_end = true, single_p = 0;

	LUNAPORT.INITIALIZED = false;
	LUNAPORT.SHOW_TOP = false;
	ZeroMemory(LUNAPORT.ORIGINAL_TITLE, sizeof(LUNAPORT.ORIGINAL_TITLE));
	ZeroMemory(LUNAPORT.TITLE, sizeof(LUNAPORT.TITLE));

	// リプレイファイル
	BinaryWriter^ bw = nullptr;
	BinaryReader^ br = nullptr;

	REPLAY_INFO ri;
	// dequeがあるため初期化は手動で
	ri.CONTROL = 0;
	ri.KEY[0] = ri.KEY[1] = 0xFFFF;
	ri.COUNT[0] = ri.COUNT[1] = 0;

	try{
		String ^path, ^file;
		array<TCHAR>^ header = gcnew array<TCHAR>{'L', 'P', 'M', 'T', 'R'};
		BYTE len;

		if(run_type == RT_PLAYBACK){
			br = gcnew BinaryReader(File::OpenRead(ReplayFilePath));

			// ヘッダ
			br->ReadChars(header->Length);
			ri.VERSION = br->ReadChar();

			// P1ネーム
			len = br->ReadByte();
			for(i = 0; i < len; i++){
				LUNAPORT.P1_NAME[i] = br->ReadChar();
			}

			// P2ネーム
			len = br->ReadByte();
			for(i = 0; i < len; i++){
				LUNAPORT.P2_NAME[i] = br->ReadChar();
			}

			// 乱数シード
			LUNAPORT.SEED = br->ReadUInt32();
		}
		else if(record_replay){
			path = gcnew String(LPMTOPTION.REPLAY_FOLDER);

			// ゲーム別にリプレイを振り分け
			if(LPMTOPTION.REPLAY_DIVIDE){
				path += "¥¥" + Path::GetFileNameWithoutExtension(gcnew String(LPMTOPTION.GAME_EXE));
			}

			if(!Directory::Exists(path)){
				Directory::CreateDirectory(path);
			}

			// フェイクタイマーを使用
			if(time_limit > 0){
				file = String::Format("{0}_", LPMTOPTION.TIME_LIMIT);
			}
			else{
				file = String::Empty;
			}

			if(run_type == RT_VS){
				file += String::Format("{0}_vs_{1}_{2}.mtr", gcnew String(LUNAPORT.P1_NAME), gcnew String(LUNAPORT.P2_NAME), DateTime::Now.ToString("yyMMdd-HHmmss"));
			}
			else{
				file += String::Format("{0}_{1}.mtr", gcnew String(LUNAPORT.P1_NAME), DateTime::Now.ToString("yyMMdd-HHmmss"));
			}

			path += "¥¥" + file;
			bw = gcnew BinaryWriter(File::Create(path));

			WriteMessage(String::Format("¥"{0}¥"にリプレイファイルを作成します。¥n", file), SystemMessageColor);

			// ヘッダ
			bw->Write(header);

			switch(LPMTOPTION.REPLAY_VERSION){
			case 1:
				ri.VERSION = _T('1');
				break;

			case 2:
			default:
				ri.VERSION = _T('2');
				break;
			}

			bw->Write(ri.VERSION);

			// P1ネーム
			len = (BYTE)_tcslen(LUNAPORT.P1_NAME);
			bw->Write(len);
			for(i = 0; i < len; i++){
				bw->Write(LUNAPORT.P1_NAME[i]);
			}

			// P2ネーム
			len = (BYTE)_tcslen(LUNAPORT.P2_NAME);
			bw->Write(len);
			for(i = 0; i < len; i++){
				bw->Write(LUNAPORT.P2_NAME[i]);
			}

			// 乱数シード
			bw->Write(LUNAPORT.SEED);
		}
	}
	catch(IOException^ e){
		WriteMessage(String::Format("ERROR > リプレイファイル¥n{0}¥n", e->ToString()), ErrorMessageColor);

		if(bw != nullptr){
			bw->Close();
			bw = nullptr;
		}
	}

	// 名前表示用
	int is_p2 = _tcslen(LUNAPORT.P2_NAME);

	// ランダムステージ用
	srand(LUNAPORT.SEED);

	// 観戦パケ送信準備
	if(allow_spectators){
		AllowWatch = false;
		InputFrame = 0;

		SpectacleThread = gcnew Thread(gcnew ThreadStart(this, &Form1::RunSpectacle));
		SpectacleThread->Start();
	}

	// 対戦中通知
	if(run_type != RT_WATCH){
		ChangeState((BYTE)MS_VS);
	}

	try{
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);

		// 作業ディレクトリ
		_tsplitpath_s(LPMTOPTION.GAME_EXE, drive, _MAX_DRIVE, buf, _MAX_DIR, NULL, 0, NULL, 0);
		_stprintf_s(wdir, _T("%s%s"), drive, buf);

		if(CreateProcess(LPMTOPTION.GAME_EXE, NULL, NULL, NULL, false, DEBUG_PROCESS, NULL, wdir, &si, &pi)){
			if(run_type == RT_PLAYBACK){
				WriteMessage(String::Format("¥"{0}¥"を再生します。¥n", Path::GetFileName(ReplayFilePath)), SystemMessageColor);
			}
			else{
				WriteMessage(String::Format("{0}を起動します。¥n", Path::GetFileNameWithoutExtension(gcnew String(LPMTOPTION.GAME_EXE))), SystemMessageColor);
			}
		}
		else{
			WriteMessage(String::Format("ERROR({0}) > ¥"{1}¥"が開けませんでした。¥n", GetLastError(), gcnew String(LPMTOPTION.GAME_EXE)), ErrorMessageColor);
			return;
		}

		LUNAPORT.PROCESS    = pi.hProcess;
		LUNAPORT.PROCESS_ID = pi.dwProcessId;

		while(WaitForDebugEvent(&de, INFINITE)){
			state = DBG_CONTINUE;

			switch(de.dwDebugEventCode){
			case EXCEPTION_DEBUG_EVENT:
				e_code    = de.u.Exception.ExceptionRecord.ExceptionCode;
				e_address = (DWORD)de.u.Exception.ExceptionRecord.ExceptionAddress;

				// ログの流れ方が尋常じゃなくなるので封印
				//if(LUNAPORT.DEBUG){
				//	WriteMessage(String::Format("EXCEPTION_DEBUG_EVENT > {0:X8}@{1:X8}¥n", e_code, e_address), DebugMessageColor);
				//}

				if(e_code == EXCEPTION_ACCESS_VIOLATION){
					ULONG_PTR info0 = de.u.Exception.ExceptionRecord.ExceptionInformation[0];
					ULONG_PTR info1 = de.u.Exception.ExceptionRecord.ExceptionInformation[1];

					if(LUNAPORT.DEBUG){
						WriteMessage(String::Format("EXCEPTION_ACCESS_VIOLATION > {0:X8}@{1:X8} : {2}@{3:X8}¥n", e_code, e_address, info0 ? "read" : "write", info1), DebugMessageColor);
					}

					state = DBG_EXCEPTION_NOT_HANDLED;
					Thread::Sleep(3000);
				}

				if(e_code == EXCEPTION_BREAKPOINT){

					if(de.dwThreadId != thread_id) break;

					switch(e_address){
					case CONTROL_CHANGE:
						// 常に1P入力
						ReadProcessMemory(pi.hProcess, (LPVOID)P1_KBD_CONTROLS, LUNAPORT.KBD_BUFFER, sizeof(LUNAPORT.KBD_BUFFER), NULL);
						WriteProcessMemory(pi.hProcess, (LPVOID)P2_KBD_CONTROLS, LUNAPORT.KBD_BUFFER, sizeof(LUNAPORT.KBD_BUFFER), NULL);
						ReadProcessMemory(pi.hProcess, (LPVOID)P1_JOY_CONTROLS, LUNAPORT.JOY_BUFFER, sizeof(LUNAPORT.JOY_BUFFER), NULL);
						WriteProcessMemory(pi.hProcess, (LPVOID)P2_JOY_CONTROLS, LUNAPORT.JOY_BUFFER, sizeof(LUNAPORT.JOY_BUFFER), NULL);
						WriteProcessMemory(pi.hProcess, (LPVOID)STICK_SELECTION, STICK_SELECTION_CODE, sizeof(STICK_SELECTION_CODE), NULL);

						// キーコンフィグ無効
						WriteProcessMemory(pi.hProcess, (LPVOID)KBD_WRITEBACK, KBD_WRITEBACK_CODE, sizeof(KBD_WRITEBACK_CODE), NULL);
						WriteProcessMemory(pi.hProcess, (LPVOID)JOY_WRITEBACK, JOY_WRITEBACK_CODE, sizeof(JOY_WRITEBACK_CODE), NULL);

						// JoyStickボタン無効
						WriteProcessMemory(pi.hProcess, (LPVOID)CONTROL_CHANGE, &NOP, 1, NULL);

						FlushInstructionCache(pi.hProcess, NULL, 0);
						break;

					case VS_ROUND:
						if(vs_end){
							num_vs++;
							vs_end = false;
						}

						c.ContextFlags = CONTEXT_INTEGER;
						GetThreadContext(thread, &c);

						c.Eax++;

						SetThreadContext(thread, &c);
						FlushInstructionCache(pi.hProcess, NULL, 0);
						break;

					case ROUND_END:
						ReadProcessMemory(pi.hProcess, (LPVOID)ROUND_ESI, &mem, 4, NULL);

						c.ContextFlags = CONTEXT_INTEGER;
						GetThreadContext(thread, &c);

						c.Esi = mem;

						if(vs_end == false){
							// 対戦終了時は２回飛んでくる
							if(c.Eax == c.Edx){
								p1_win++;
								vs_end = true;
							}
							if(c.Eax == c.Esi){
								p2_win++;
								vs_end = true;
							}

							if(vs_end){
								timer = 0;
							}
						}

						SetThreadContext(thread, &c);
						FlushInstructionCache(pi.hProcess, NULL, 0);
						break;

					case MODE_SELECT:
						if(wav->IsLoadCompleted == false){
							try{
								wav->Play();
							}
							catch(Exception^){
							}
						}

						c.ContextFlags = CONTEXT_INTEGER;
						GetThreadContext(thread, &c);

						c.Esi = 1;

						SetThreadContext(thread, &c);
						FlushInstructionCache(pi.hProcess, NULL, 0);
						break;

					case TIMER_RESET1:
					case TIMER_RESET2:
						timer = time_limit;
						ReadProcessMemory(pi.hProcess, (LPVOID)DEFAULT_TIME, &def_time, 4, NULL);

						if(def_time == 0){
							mem = 0xFFFFFFFF;
							WriteProcessMemory(pi.hProcess, (LPVOID)TIME_LIMIT, &mem, 4, NULL);
						}
						else{
							WriteProcessMemory(pi.hProcess, (LPVOID)TIME_LIMIT, &timer, 4, NULL);
						}
						break;

					case TIMER_DECREASE:
						c.ContextFlags = CONTEXT_INTEGER;
						GetThreadContext(thread, &c);

						// 偽タイマー使用かつ格ツク本体のタイマーを使用するようにしていたらこっちで制御
						if(timer > 0 && def_time > 0){
							c.Eax = timer + 98;
						}
						else{
							ReadProcessMemory(pi.hProcess, (LPVOID)TIME_LIMIT, &mem, 4, NULL);
							c.Eax = mem;
						}

						SetThreadContext(thread, &c);
						FlushInstructionCache(pi.hProcess, NULL, 0);

						if(timer > 1){
							timer--;

							if(timer == 3001 || timer == 1001 || timer == 501 || timer == 401 || timer == 301 || timer == 201 || timer == 101){
								try{
									wav->Play();
								}
								catch(Exception^){
								}
							}

							if(timer == 1){
								DWORD s1, s2;

								ReadProcessMemory(pi.hProcess, (LPVOID)P1_STATE, &s1, 4, NULL);
								ReadProcessMemory(pi.hProcess, (LPVOID)P2_STATE, &s2, 4, NULL);

								if(s1 & 0x0C || s2 & 0x0C){
									timer++;
									break;
								}

								DWORD hp1, max1, hp2, max2;
								ReadProcessMemory(pi.hProcess, (LPVOID)P1_HP, &hp1, 4, NULL);
								ReadProcessMemory(pi.hProcess, (LPVOID)P1_MAX_HP, &max1, 4, NULL);
								ReadProcessMemory(pi.hProcess, (LPVOID)P2_HP, &hp2, 4, NULL);
								ReadProcessMemory(pi.hProcess, (LPVOID)P2_MAX_HP, &max2, 4, NULL);

								hp1 = hp1 * 1000 / max1;
								hp2 = hp2 * 1000 / max2;

								if(hp1 == hp2){
									hp1 = hp2 = 0;
								}
								else if(hp1 > hp2){
									hp2 = 0;
								}
								else{
									hp1 = 0;
								}

								if(hp1 == 0){
									WriteProcessMemory(pi.hProcess, (LPVOID)P1_HP, &hp1, 4, NULL);
								}
								if(hp2 == 0){
									WriteProcessMemory(pi.hProcess, (LPVOID)P2_HP, &hp2, 4, NULL);
								}
							}
						}
						break;

					case RAND_FUNC:
						rand_count++;
						ReadProcessMemory(pi.hProcess, (LPVOID)RANDOM_SEED, &mem, 4, NULL);

						c.ContextFlags = CONTEXT_INTEGER;
						GetThreadContext(thread, &c);

						c.Eax = mem;

						SetThreadContext(thread, &c);
						FlushInstructionCache(pi.hProcess, NULL, 0);
						break;

					case STAGE_SELECT_BREAK:
						c.ContextFlags = CONTEXT_INTEGER;
						GetThreadContext(thread, &c);

						if(LPMTOPTION.STAGE_SELECT == 0){
							c.Eax = rand() % LPMTOPTION.MAX_STAGES;
						}
						else{
							c.Eax = LPMTOPTION.STAGE_SELECT - 1;
						}

						SetThreadContext(thread, &c);
						FlushInstructionCache(pi.hProcess, NULL, 0);
						break;

					case LOCAL_P_BREAK:
					case REMOTE_P_BREAK:
						inputs++;

						c.ContextFlags = CONTEXT_INTEGER;
						GetThreadContext(thread, &c);

						if(e_address == LOCAL_P_BREAK){
							c.Eax = LocalInput((UINT16)c.Eax);
						}
						else{
							c.Eax = RemoteInput();
						}

						if(record_replay || allow_spectators){
							RecordInput((UINT16)c.Eax, bw, ri, allow_spectators);
						}

						SetThreadContext(thread, &c);
						FlushInstructionCache(pi.hProcess, NULL, 0);
						break;

					case SINGLE_BREAK_INPUT:
						inputs++;

					case PLAY_P1_BREAK:
					case PLAY_P2_BREAK:
						inputs++;

						c.ContextFlags = CONTEXT_INTEGER;
						GetThreadContext(thread, &c);

						if(run_type == RT_VS){
							if(LUNAPORT.CONTROL == single_p){
								RemoteInput();
								c.Eax = LocalInput((UINT16)c.Eax);
							}
							else{
								LocalInput(0);
								c.Eax = RemoteInput();
							}
						}
						else if(run_type == RT_WATCH && WaitingWatch > 0){
							// 観戦バッファから読み込み
							c.Eax = WatchHistory[WatchFrame % WatchHistory->Length];

							if(c.Eax == 0xFFFF){
								Monitor::Enter(WatchHistory);
								try{
									WaitingWatch = 2;
									Monitor::Wait(WatchHistory, TIME_OUT*2);
								}
								finally{
									Monitor::Exit(WatchHistory);
								}

								c.Eax = WatchHistory[WatchFrame % WatchHistory->Length];

								if(c.Eax == 0xFFFF && WaitingWatch == 2){
									WriteMessage("タイムアウトしたため観戦を終了します。¥n", ErrorMessageColor);
									QuitWatch(true);
								}
							}

							Monitor::Enter(WatchHistory);
							try{
								WatchHistory[WatchFrame % WatchHistory->Length] = 0xFFFF;
								WatchFrame++;
							}
							finally{
								Monitor::Exit(WatchHistory);
							}
						}
						else if(run_type == RT_PLAYBACK){
							c.Eax = ReadReplayData(br, ri);
						}

						if(record_replay || allow_spectators){
							RecordInput((UINT16)c.Eax, bw, ri, allow_spectators);
						}

						SetThreadContext(thread, &c);
						FlushInstructionCache(pi.hProcess, NULL, 0);
						break;

					case SINGLE_BREAK_CONTROL:
						c.ContextFlags = CONTEXT_INTEGER;
						GetThreadContext(thread, &c);
						single_p = c.Ecx & 1;
						break;

					case FRAME_BREAK:
						frames++;
						now = timeGetTime();

						if(now - last_sec >= 1000){
							append_cap = 0;

							_tcscpy_s(LUNAPORT.TITLE, LUNAPORT.ORIGINAL_TITLE);

							if(time_limit > 0){
								append_cap = _stprintf_s(LUNAPORT.TITLE, _T("%s < %02d >"), LUNAPORT.TITLE, timer/100);
							}
							if(LPMTOPTION.DISPLAY_NAMES){
								if(is_p2 == 0){
									append_cap = _stprintf_s(LUNAPORT.TITLE, _T("%s [Player:%s]"), LUNAPORT.TITLE, LUNAPORT.P1_NAME);
								}
								else{
									append_cap = _stprintf_s(LUNAPORT.TITLE, _T("%s [%s vs %s]"), LUNAPORT.TITLE, LUNAPORT.P1_NAME, LUNAPORT.P2_NAME);
								}
							}
							if(LPMTOPTION.DISPLAY_VERSUS){
								append_cap = _stprintf_s(LUNAPORT.TITLE, _T("%s 対戦数:%d (%d - %d)"), LUNAPORT.TITLE, num_vs, p1_win, p2_win);
							}
							if(LPMTOPTION.DISPLAY_FRAMERATE){
								append_cap = _stprintf_s(LUNAPORT.TITLE, _T("%s fps:%3d"), LUNAPORT.TITLE, frames);
							}
							if(LPMTOPTION.DISPLAY_INPUTRATE){
								append_cap = _stprintf_s(LUNAPORT.TITLE, _T("%s input:%3d"), LUNAPORT.TITLE, inputs/2);
							}

							if(rand_count > 0){
								append_cap = _stprintf_s(LUNAPORT.TITLE, _T("%s rand:%d"), LUNAPORT.TITLE, rand_count - 1);

								rand_count = 1;
							}

							frames = 0;
							inputs = 0;
							last_sec = now;

							if(append_cap > 0 || last_cap > 0 || LUNAPORT.HWND == NULL){
								last_cap = append_cap;

								Thread^ cap = gcnew Thread(gcnew ThreadStart(&SetCaption));
								cap->Start();
							}
						}
						break;
					}
				}
				break;

			case CREATE_THREAD_DEBUG_EVENT:
				if(LUNAPORT.DEBUG){
					WriteMessage("CREATE_THREAD_DEBUG_EVENT¥n", DebugMessageColor);
				}
				break;

			case CREATE_PROCESS_DEBUG_EVENT:
				if(LUNAPORT.DEBUG){
					WriteMessage("CREATE_PROCESS_DEBUG_EVENT¥n", DebugMessageColor);
				}

				thread    = de.u.CreateProcessInfo.hThread;
				thread_id = de.dwThreadId;

				// ここから書き換えゾーン
				mem = LPMTOPTION.HIT_JUDGE;
				WriteProcessMemory(pi.hProcess, (LPVOID)HIT_JUDGE, &mem, 4, NULL);
				WriteProcessMemory(pi.hProcess, (LPVOID)HIT_JUDGE_SET, HIT_JUDGE_SET_CODE, sizeof(HIT_JUDGE_SET_CODE), NULL);
				WriteProcessMemory(pi.hProcess, (LPVOID)VS_ROUND, VS_ROUND_CODE, sizeof(VS_ROUND_CODE), NULL);
				WriteProcessMemory(pi.hProcess, (LPVOID)ROUND_END, ROUND_END_CODE, sizeof(ROUND_END_CODE), NULL);

				if(time_limit > 0){
					WriteProcessMemory(pi.hProcess, (LPVOID)MODE_SELECT, MODE_SELECT_CODE, sizeof(MODE_SELECT_CODE), NULL);
					WriteProcessMemory(pi.hProcess, (LPVOID)TIMER_RESET1, TIMER_RESET1_CODE, sizeof(TIMER_RESET1_CODE), NULL);
					WriteProcessMemory(pi.hProcess, (LPVOID)TIMER_RESET2, TIMER_RESET2_CODE, sizeof(TIMER_RESET2_CODE), NULL);
					WriteProcessMemory(pi.hProcess, (LPVOID)TIMER_DECREASE, TIMER_DECREASE_CODE, sizeof(TIMER_DECREASE_CODE), NULL);
				}

				WriteProcessMemory(pi.hProcess, (LPVOID)RANDOM_SEED, &LUNAPORT.SEED, 4, NULL);
				WriteProcessMemory(pi.hProcess, (LPVOID)STAGE_SELECT, STAGE_SELECT_CODE, sizeof(STAGE_SELECT_CODE), NULL);
				WriteProcessMemory(pi.hProcess, (LPVOID)LOCAL_P_FUNC, LOCAL_P_FUNC_CODE, sizeof(LOCAL_P_FUNC_CODE), NULL);
				WriteProcessMemory(pi.hProcess, (LPVOID)LOCAL_P_JUMPBACK, LOCAL_P_JUMPBACK_CODE[LUNAPORT.CONTROL], 5, NULL);
				WriteProcessMemory(pi.hProcess, (LPVOID)REMOTE_P_FUNC, REMOTE_P_FUNC_CODE, sizeof(REMOTE_P_FUNC_CODE), NULL);
				WriteProcessMemory(pi.hProcess, (LPVOID)REMOTE_P_JUMPBACK, REMOTE_P_JUMPBACK_CODE[!LUNAPORT.CONTROL], 5, NULL);

				if(LUNAPORT.CHECK_RAND){
					rand_count = 1;

					WriteProcessMemory(pi.hProcess, (LPVOID)RAND_FUNC, RAND_FUNC_CODE, sizeof(RAND_FUNC_CODE), NULL);
				}

				// タイトルバー
				WriteProcessMemory(pi.hProcess, (LPVOID)FRAME_FUNC, FRAME_FUNC_CODE, sizeof(FRAME_FUNC_CODE), NULL);
				WriteProcessMemory(pi.hProcess, (LPVOID)FRAME_JUMP, FRAME_JUMP_CODE, sizeof(FRAME_JUMP_CODE), NULL);

				if(run_type == RT_VS || record_replay || allow_spectators){
					WriteProcessMemory(pi.hProcess, (LPVOID)SINGLE_FUNC, SINGLE_FUNC_CODE, sizeof(SINGLE_FUNC_CODE), NULL);
					WriteProcessMemory(pi.hProcess, (LPVOID)SINGLE_JUMP, SINGLE_JUMP_CODE, sizeof(SINGLE_JUMP_CODE), NULL);
				}

				if(run_type == RT_VS){
					WriteProcessMemory(pi.hProcess, (LPVOID)P1_JUMP, P1_JUMP_CODE[LUNAPORT.CONTROL], 5, NULL);
					WriteProcessMemory(pi.hProcess, (LPVOID)P2_JUMP, P2_JUMP_CODE[!LUNAPORT.CONTROL], 5, NULL);
				}
				else{
					WriteProcessMemory(pi.hProcess, (LPVOID)PLAY_HOOKS, PLAY_HOOKS_CODE, sizeof(PLAY_HOOKS_CODE), NULL);
					WriteProcessMemory(pi.hProcess, (LPVOID)PLAY_P1_JUMP, PLAY_P1_JUMP_CODE, sizeof(PLAY_P1_JUMP_CODE), NULL);
					WriteProcessMemory(pi.hProcess, (LPVOID)PLAY_P2_JUMP, PLAY_P2_JUMP_CODE, sizeof(PLAY_P2_JUMP_CODE), NULL);
				}

				FlushInstructionCache(pi.hProcess, NULL, 0);

				// ウィンドウサイズを640x480に
				if(LPMTOPTION.CHANGE_WINDOW_SIZE){
					TCHAR val[32];

					_stprintf_s(buf, _T("%sgame.ini"), wdir);

					if(File::Exists(gcnew String(buf))){
						_itot_s(640, val, 10);
						WritePrivateProfileString(_T("GamePlay"), _T("GameWindowSize_x"), val, buf);
						_itot_s(480, val, 10);
						WritePrivateProfileString(_T("GamePlay"), _T("GameWindowSize_y"), val, buf);
					}
				}

				LUNAPORT.INITIALIZED = true;
				break;

			case EXIT_THREAD_DEBUG_EVENT:
				if(LUNAPORT.DEBUG){
					WriteMessage("EXIT_THREAD_DEBUG_EVENT¥n", DebugMessageColor);
				}
				break;

			case EXIT_PROCESS_DEBUG_EVENT:
				if(LUNAPORT.DEBUG){
					WriteMessage("EXIT_PROCESS_DEBUG_EVENT¥n", DebugMessageColor);
				}
				break;

			case LOAD_DLL_DEBUG_EVENT:
				if(LUNAPORT.DEBUG){
					TCHAR buf[MAX_PATH];
					LONG_PTR data;

					ReadProcessMemory(pi.hProcess, de.u.LoadDll.lpImageName, &data, sizeof(LONG_PTR), NULL);
					ReadProcessMemory(pi.hProcess, (LPVOID)data, buf, sizeof(TCHAR)*MAX_PATH, NULL);

					WriteMessage(String::Format("LOAD_DLL_DEBUG_EVENT > ¥"{0}¥"¥n", gcnew String(buf)), DebugMessageColor);
				}
				break;

			case UNLOAD_DLL_DEBUG_EVENT:
				if(LUNAPORT.DEBUG){
					WriteMessage("UNLOAD_DLL_DEBUG_EVENT¥n", DebugMessageColor);
				}
				break;

			case OUTPUT_DEBUG_STRING_EVENT:
				if(LUNAPORT.DEBUG){
					int size = de.u.DebugString.nDebugStringLength;
					char *str = (char *)malloc(size);
					ReadProcessMemory(pi.hProcess, de.u.DebugString.lpDebugStringData, str, size, NULL);

					if(str[size-2] == '¥n'){
						str[size-2] = '¥0';
					}

					WriteMessage(String::Format("OUTPUT_DEBUG_STRING_EVENT > {0}¥n", gcnew String(str)), DebugMessageColor);
					free(str);
				}
				break;

			case RIP_EVENT:
				if(LUNAPORT.DEBUG){
					WriteMessage("RIP_EVENT¥n", DebugMessageColor);
				}
				break;
			}

			if(de.dwDebugEventCode == EXIT_PROCESS_DEBUG_EVENT) break;

			ContinueDebugEvent(de.dwProcessId, de.dwThreadId, state);
		}
	}
	catch(Exception^ e){
		WriteMessage(e->ToString() + "¥n", ErrorMessageColor);
	}
	finally{
		AllowWatch = false;
		InputFrame = 0;

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);

		if(br != nullptr){
			br->Close();
		}
		if(bw != nullptr){
			bw->Write(ri.KEY[0]);
			bw->Write(ri.COUNT[0]);
			bw->Write((UINT16)(ri.KEY[1] | 0x0800));
			bw->Write(ri.COUNT[1]);

			bw->Close();
		}

		if(LUNAPORT.INITIALIZED){
			if(WaitingWatch > 0){
				WaitingWatch = 0;
				WriteMessage("観戦を中止します。¥n", SystemMessageColor);
			}
			else if(_tcslen(LUNAPORT.ORIGINAL_TITLE) > 0){
				WriteMessage(String::Format("{0}を終了します。¥n", gcnew String(LUNAPORT.ORIGINAL_TITLE)), SystemMessageColor);
			}
			else{
				WriteMessage("ゲームを終了します。¥n", SystemMessageColor);
			}
		}

		if(NetVS != nullptr && NetVS->SEQUENCE == VS_DATA){
			NetVS->SEQUENCE = VS_END;
			UDP->Send(gcnew array<BYTE>{ PH_VS_END }, 1, NetVS->IP_EP);

			// ロック開放待ち
			Monitor::Enter(NetVS->LOCAL);
			Monitor::Exit(NetVS->LOCAL);
			Monitor::Enter(NetVS->REMOTE);
			Monitor::Exit(NetVS->REMOTE);

			delete NetVS;
			NetVS = nullptr;
		}

		if(allow_spectators){
			AllowWatch = false;
			SpectacleThread->Join();
		}

		if(AfterCloseUDP){
			AfterCloseUDP = false;
			UDP->Close();
		}
		else if(run_type == RT_WATCH){
			QuitWatch(true);
		}
		else{
			// 対戦終了を通知
			if(LPMTOPTION.AFTER_REST && run_type == RT_VS){
				ChangeState((BYTE)MS_REST);
			}
			else{
				ChangeState((BYTE)MS_FREE);
			}
		}

		LUNAPORT.INITIALIZED = false;
		LUNAPORT.SHOW_TOP    = false;
		LUNAPORT.PROCESS     = NULL;
		LUNAPORT.PROCESS_ID  = 0;
		LUNAPORT.HWND        = NULL;
		ZeroMemory(LUNAPORT.ORIGINAL_TITLE, sizeof(LUNAPORT.ORIGINAL_TITLE));
		ZeroMemory(LUNAPORT.TITLE, sizeof(LUNAPORT.TITLE));

		if(IsFormClosing){
			this->Close();
		}
	}
}

void Form1::RunVersus()
{
	array<BYTE>^ send = gcnew array<BYTE>(3);

	try{
		// 対戦要求
		send[0] = PH_REQ_VS;
		Array::Copy(BitConverter::GetBytes(MemberList[0]->ID), 0, send, 1, 2);
		UDP->Send(send, 3, NetVS->IP_EP);

		NetVS->SLEEPING = true;
		try{
			Thread::Sleep(TIME_OUT);
		}
		catch(ThreadInterruptedException^){
		}
		NetVS->SLEEPING = false;

		if(NetVS->SEQUENCE != VS_PING){
			WriteMessage("対戦相手からの応答がありませんでした。¥n", ErrorMessageColor);
			return;
		}

		// PINGで帯域調査
		send[0] = PH_REQ_VS_PING;

		for(BYTE i = 0; i < 5; i++){
			NetVS->PING[i] = timeGetTime();
			send[1] = i;
			UDP->Send(send, 2, NetVS->IP_EP);

			Thread::Sleep(10);
		}

		if(NetVS->SEQUENCE == VS_PING){
			NetVS->SLEEPING = true;
			try{
				// 最低でも１秒間にパケ４つは欲しいところ
				Thread::Sleep(1000);
			}
			catch(ThreadInterruptedException^){
			}
			NetVS->SLEEPING = false;
		}

		if(NetVS->SEQUENCE != VS_DELAY){
			WriteMessage("回線が不安定です。¥n", ErrorMessageColor);
			return;
		}

		// DELAYの設定
		send[0] = PH_REQ_VS_DELAY;

		if(LPMTOPTION.DELAY == 0){
			// オート設定
			int d = 0, c = 0;

			for(int i = 0; i < 5; i++){
				if(NetVS->PONG[i] > 0){
					d += NetVS->PONG[i] - NetVS->PING[i];
					c++;

					if(c == 4) break;
				}
			}

			if(c < 4){
				WriteMessage("ディレイ値の計算が正常に行われませんでした。¥n", ErrorMessageColor);
				return;
			}

			c = d/40 + 2;  // Delay = PING/10 + 2

			if(c > 9) c = 9;

			NetVS->DELAY = c;
		}
		else{
			NetVS->DELAY = LPMTOPTION.DELAY;
		}

		send[1] = (BYTE)NetVS->DELAY;
		UDP->Send(send, 2, NetVS->IP_EP);

		NetVS->SLEEPING = true;
		try{
			Thread::Sleep(TIME_OUT);
		}
		catch(ThreadInterruptedException^){
		}
		NetVS->SLEEPING = false;

		if(NetVS->SEQUENCE != VS_STANDBY){
			WriteMessage("対戦準備が完了しませんでした。¥n", ErrorMessageColor);
			return;
		}

		NetVS->SEQUENCE = VS_DATA;

		// 対戦開始
		WriteMessage(String::Format("対戦を開始します。(delay:{0})¥n", NetVS->DELAY), SystemMessageColor);

		GameThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &Form1::RunGame));
		GameThread->Start((UINT)RT_VS);
	}
	finally{
		if(NetVS->SEQUENCE < VS_DATA){
			MemberList[0]->STATE = MS_FREE;

			delete NetVS;
			NetVS = nullptr;
		}
	}
}

void Form1::RunSpectacle()
{
	int i, d;
	UINT32 frame = 0, s_frame;

	// 開始合図
	array<BYTE>^ send = gcnew array<BYTE>(10);
	send[0] = PH_RES_WATCH;
	send[1] = 0;
	Array::Copy(BitConverter::GetBytes(P1ID), 0, send, 2, 2);
	Array::Copy(BitConverter::GetBytes(P2ID), 0, send, 4, 2);
	Array::Copy(BitConverter::GetBytes(LUNAPORT.SEED), 0, send, 6, 4);

	Monitor::Enter(InputHistory);
	try{
		for(i = 0; i < SpectatorList->Count; i++){
			UDP->BeginSend(send, send->Length, SpectatorList[i]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);
		}
	}
	finally{
		Monitor::Exit(InputHistory);
	}

	Thread::Sleep(100);

	// データ送信準備
	send = gcnew array<BYTE>(45){ PH_WATCH_DATA };

	// 準備完了
	AllowWatch = true;

	// データ送信
	while(AllowWatch){
		Monitor::Enter(InputHistory);
		try{
			frame = InputFrame;

			for(i = 0; i < SpectatorList->Count; i++){
				s_frame = SpectatorList[i]->FRAME;
/*
				// データは既にバッファからなくなってる
				if(frame > s_frame && (frame - s_frame) >= (UINT)InputHistory->Length - 20){
					if(LUNAPORT.DEBUG) WriteMessage(String::Format("観戦者の追い出し > {0} / {1}¥n", SpectatorList[i]->ID, SpectatorList->Count), DebugMessageColor);

					send[0] = PH_WATCH_END;
					Array::Copy(BitConverter::GetBytes(SpectatorList[i]->ID), 0, send, 1, 2);
					UDP->BeginSend(send, 3, SpectatorList[i]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);

					SpectatorList->RemoveAt(i);
					i--;

					send[0] = PH_WATCH_DATA;
					continue;
				}
*/
				// 5フレームごとに10フレーム分送る
				if(s_frame + 20 < frame){
					Array::Copy(BitConverter::GetBytes(s_frame), 0, send, 1, 4);

					for(d = 0; d < 20; d++){
						Array::Copy(BitConverter::GetBytes(InputHistory[(s_frame + d) % InputHistory->Length]), 0, send, 5 + d*2, 2);
					}

					UDP->BeginSend(send, send->Length, SpectatorList[i]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);

					// 0frameの時は念のため２個送信
					if(s_frame == 0){
						UDP->BeginSend(send, send->Length, SpectatorList[i]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);
					}

					SpectatorList[i]->FRAME += 10;
				}
			}
		}
		finally{
			Monitor::Exit(InputHistory);
		}

		// ちょっとだけ休憩
		Thread::Sleep(20);
	}

	// 終了合図
	send[0] = PH_WATCH_END;

	Monitor::Enter(InputHistory);
	try{
		for(i = 0; i < SpectatorList->Count; i++){
			Array::Copy(BitConverter::GetBytes(SpectatorList[i]->ID), 0, send, 1, 2);
			UDP->BeginSend(send, 3, SpectatorList[i]->IP_EP, gcnew AsyncCallback(SendPackets), UDP);
		}

		SpectatorList->Clear();
	}
	finally{
		Monitor::Exit(InputHistory);
	}
}

UINT16 Form1::LocalInput(UINT16 eax)
{
	// 左右同時押し禁止 if((eax & 3) == 3) eax ^= 2
	if((eax & 0x0003) == 0x0003){
		eax &= 0xFFFD;
	}

	Monitor::Enter(NetVS->LOCAL);
	try{
		NetVS->LOCAL[(NetVS->L_READ + NetVS->DELAY) % NetVS->LOCAL->Length] = eax;
		eax = NetVS->LOCAL[NetVS->L_READ];

		// 送信開始
		Array::Copy(BitConverter::GetBytes(NetVS->L_FRAME), 0, NetVS->SEND, 1, 4);

		UINT i;

		for(i = 0; i <= NetVS->DELAY; i++){
			Array::Copy(BitConverter::GetBytes(NetVS->LOCAL[(NetVS->L_READ + i) % NetVS->LOCAL->Length]), 0, NetVS->SEND, 5 + i*2, 2);
		}

		UDP->BeginSend(NetVS->SEND, 5 + i*2, NetVS->IP_EP, gcnew AsyncCallback(SendPackets), UDP);

		NetVS->L_FRAME++;
		NetVS->L_READ++;
		NetVS->L_READ %= NetVS->LOCAL->Length;
	}
	finally{
		Monitor::Exit(NetVS->LOCAL);
	}

	return eax;
}

UINT16 Form1::RemoteInput()
{
	if(NetVS->SEQUENCE != VS_DATA) return 0;

	UINT16 eax;

	eax = NetVS->REMOTE[NetVS->R_READ];

	// パケ来てない
	if(eax == 0xFFFF){
		Monitor::Enter(NetVS->REMOTE);
		try{
			// 今来てるかも
			NetVS->WAITING = 2;
			Monitor::Wait(NetVS->REMOTE, NetVS->DELAY*10);
			eax = NetVS->REMOTE[NetVS->R_READ];
		}
		finally{
			Monitor::Exit(NetVS->REMOTE);
		}
	}

	// ロスった？
	if(eax == 0xFFFF){
		NetVS->WAITING = 1;

		array<BYTE>^ send = gcnew array<BYTE>(5){ PH_REQ_VS_DATA };
		Array::Copy(BitConverter::GetBytes(NetVS->R_FRAME), 0, send, 1, 4);

		UINT i = 0;

		while(NetVS->SEQUENCE == VS_DATA){
			UDP->BeginSend(send, send->Length, NetVS->IP_EP, gcnew AsyncCallback(SendPackets), UDP);

			Monitor::Enter(NetVS->REMOTE);
			try{
				NetVS->WAITING = 2;
				Monitor::Wait(NetVS->REMOTE, NetVS->DELAY*10);
			}
			finally{
				Monitor::Exit(NetVS->REMOTE);
			}

			if(NetVS->WAITING == 2){
				NetVS->WAITING = 1;
				if(++i > 100){
					NetVS->SEQUENCE = VS_TIMEOUT;
				}
				continue;
			}

			eax = NetVS->REMOTE[NetVS->R_READ];

			if(eax != 0xFFFF){
				break;
			}
			else{
				i = 0;
				// ここがかの有名なラグの生産地です
				// Delay*10 / 2   ディレイの半フレーム分は待機してもよさそう？
				Thread::Sleep(NetVS->DELAY*5);
			}
		}

		if(eax == 0xFFFF && NetVS->SEQUENCE == VS_TIMEOUT){
			WriteMessage("タイムアウトしたため対戦を終了します。¥n", ErrorMessageColor);
			if(LUNAPORT.DEBUG) WriteMessage(String::Format("Frame > L:{0} / R:{1} (delay:{2})¥n", NetVS->L_FRAME, NetVS->R_FRAME, NetVS->DELAY), DebugMessageColor);

			QuitGame();
			return 0;
		}

		NetVS->WAITING = 0;
	}

	if(NetVS->SEQUENCE != VS_DATA) return 0;

	if((eax & 0x0003) == 0x0003){
		WriteMessage("不正パケットの受信 > 左右同時押し¥n", ErrorMessageColor);
		if(LUNAPORT.DEBUG) WriteMessage(String::Format("IP = {0}¥n", NetVS->IP_EP->Address), DebugMessageColor);

		QuitGame();
		return 0xFFFF;
	}

	Monitor::Enter(NetVS->REMOTE);
	try{
		NetVS->REMOTE[NetVS->R_READ] = 0xFFFF;

		NetVS->R_FRAME++;
		NetVS->R_READ++;
		NetVS->R_READ %= NetVS->REMOTE->Length;
	}
	finally{
		Monitor::Exit(NetVS->REMOTE);
	}

	return eax;
}

UINT16 Form1::ReadReplayData(BinaryReader^ br, REPLAY_INFO& ri)
{
	if(br == nullptr){
		return 0;
	}

	UINT16 eax;

	try{
		if(ri.VERSION == _T('1')){
			eax = br->ReadUInt16();
		}
		else{
			// リプレイファイルのRLEデコード
			if(ri.COUNT[ri.CONTROL] == 0){
				REPLAY_DATA rd;
				bool ctrl;

				if(ri.DEQUE[ri.CONTROL].size() > 0){
					// キューにデータあり
					rd = ri.DEQUE[ri.CONTROL].front();
					ri.DEQUE[ri.CONTROL].pop_front();
				}
				else{
					rd.KEY   = br->ReadUInt16();
					rd.COUNT = br->ReadByte();
					ctrl     = (rd.KEY & 0x0800) > 0 ? true : false;

					while(ctrl != ri.CONTROL){
						// キューに退避
						ri.DEQUE[ctrl].push_back(rd);

						// 再読み込み
						rd.KEY   = br->ReadUInt16();
						rd.COUNT = br->ReadByte();
						ctrl     = (rd.KEY & 0x0800) > 0 ? true : false;
					}
				}

				ri.KEY[ri.CONTROL]   = rd.KEY & 0x07FF;
				ri.COUNT[ri.CONTROL] = rd.COUNT;
			}
			else{
				ri.COUNT[ri.CONTROL]--;
			}

			eax = ri.KEY[ri.CONTROL];

			ri.CONTROL ^= 1;
		}
	}
	catch(EndOfStreamException^){
		WriteMessage("リプレイファイルの再生が終了しました。¥n", SystemMessageColor);

		br->Close();
		br = nullptr;

		QuitGame();
		return 0;
	}
	catch(ObjectDisposedException^){
		br = nullptr;

		return 0;
	}

	return eax;
}

void Form1::RecordInput(UINT16 eax, BinaryWriter^ bw, REPLAY_INFO& ri, bool watch)
{
	// リプレイファイルの記録
	if(bw != nullptr){
		if(ri.VERSION == _T('1')){
			bw->Write(eax);
		}
		else{
			// RLE
			if(ri.KEY[ri.CONTROL] == 0xFFFF){
				// 初回
				ri.KEY[ri.CONTROL] = eax;
			}
			else{
				if(eax == ri.KEY[ri.CONTROL]){
					// 一周してきた
					if(ri.COUNT[ri.CONTROL] == 0xFF){
						bw->Write((UINT16)(ri.KEY[ri.CONTROL] | ri.CONTROL << 11));
						bw->Write(ri.COUNT[ri.CONTROL]);

						ri.COUNT[ri.CONTROL] = 0;
					}
					else{
						ri.COUNT[ri.CONTROL]++;
					}
				}
				else{
					bw->Write((UINT16)(ri.KEY[ri.CONTROL] | ri.CONTROL << 11));
					bw->Write(ri.COUNT[ri.CONTROL]);

					ri.KEY[ri.CONTROL]   = eax;
					ri.COUNT[ri.CONTROL] = 0;
				}
			}

			ri.CONTROL ^= 1;
		}
	}

	// 観戦OK
	if(watch && UDP != nullptr){
		Monitor::Enter(InputHistory);
		try{
			InputHistory[InputFrame % InputHistory->Length] = eax;
			InputFrame++;
		}
		finally{
			Monitor::Exit(InputHistory);
		}
	}
}

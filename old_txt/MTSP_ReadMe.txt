================================================================================
 【 ソフト名 】 MT Special Edition
 【ランタイム】 .NET Framework 2.0/3.5
 【 開発環境 】 Windows XP  +  Visual C++ 2008 Express Edition
 【   備考   】 転載等は自己責任で
================================================================================

■ 概要
  「2D格闘ツクール95/2nd.」用UDPチャット機能付きネット対戦支援ツールです。
  動作には「.NET Framework 3.5」が必要になります。
  プログラムが起動しない人は↓から手に入れてきてください。

  .NET Framework デベロッパー センター
  http://msdn.microsoft.com/ja-jp/netframework/default.aspx

  2000ユーザは、同封の「Win2k対応版」を使用してください。
  その際必要になるランタイムは「.NET Framework 2.0」です。
  また、3.5がうまくインストール出来ないorめんどくさい、という人もこちらを使用してください。

  Vistaユーザの方は、互換モードを変更することで動作するようになる、との報告があります。
  うまく動作しない場合には、互換モードをXPに変更するなどして試してみてください。


■ 注意
  当ソフトウェアはエンターブレインの許可を取らずに作成してあります。
  使用や配布の停止要請が来た場合には、直ちに従ってください。
  また、発生したバグや問題点をエンターブレインやゲーム製作者に問い合わせるのは、絶対に止めください。


■ 対応している格闘ツクールのバージョン
・95  : 1.20.0.2
・2nd : 1.0.2.0


■ 機能一覧
・チャット
・ネット対戦
・リプレイの保存/再生
・観戦

  UDPの特性上、相手にパケットが届かないこともあるので、大事なことは２度言ってください。
  ネット対戦中の左右キーの同時入力は、後ろキー入力に自動変更されます。
  蔵同士でもPingが帰ってくるようならば、ネット対戦が出来る可能性があります。

  観戦は対象が対戦を開始しても、５秒くらいまでなら観戦できます。
  また、相手がどのような状態(リプレイファイルの再生等)でも観戦対象に出来ます。
  ただし、負担を減らすため同期など細かい手順は全て省いてますので、
  対戦とは比べ物にならないほどタイムアウトが出やすくなってます。

  観戦する人を観戦することで、パケットのリレーが行えます。(観戦リレー)
  これによりネット対戦者の負担を減らすことが可能です。

  格ツク95で遊ぶ場合、起動時にオプションの『JoyStick』をOFFにします。
  これをしておかないと多くの環境でゲームを起動させることが出来ないためです。
  パッドを使用したい時は、「JoyToKey」や「JoyAdapter」などの外部ツールを使用してください。


■ 画面説明
┏━┳━━━┓  ① メンバーリスト
┃  ┃  ②  ┃
┃①┃      ┃  ② ログウィンドウ
┃  ┣━③━┫
┗━┻━━━┛  ③ 入力欄


■ 使い方
  起動するとスタートアップダイアログが表示されます。

フリープレイ : ネット接続せずにプログラムを起動します。

[モード選択]
・Server(鯖) : 鯖を立て、蔵を受け入れるようにします。鯖名は32文字まで。
・Host       : ポートを開放した状態で鯖に接続します。確実にネット対戦が出来そうな蔵です。
・Client(蔵) : ポートを開放せずに鯖に接続します。ポート開放が無理そうな時はこのモードで起動してください。

・DNS        : チェックを入れている場合、接続先に入力した文字列をホスト名として扱います。
・開放ポート : 接続の待ち受けをするポートです。
               事前にルータ等の設定で開放したポート番号を入力してください。
               デフォルトでは、UDP:7500を使用します。
               サーバはUDP:7500推奨ですが、Hostは開いてさえいれば好きなポートでかまいません。

  接続先を入力する際、文字列の最後に「:ポート番号」を付け足すことで、接続ポートを変更する手間が省けます。

  サーバ名のはじめに特定の記号を付ける事で、特殊なサーバを立てることが出来ます。
・+鯖名 : 混在サーバモードで鯖を立てます。ランダム対戦不可、対戦に使用するゲームをチェックするのが特徴です。
・@鯖名 : チャット禁止サーバを立てます。
・#鯖名 : 匿名サーバモードで鯖を立てます。チャット禁止に加え、名前やコメントが一切表示されなくなり、
          右クリック後のメニュー「対戦する」が全てランダム対戦(/vs)になります。

[オプション]
・ニックネーム : メンバーリストに表示される名前です。
・コメント     : 入室時、及びポップアップに表示される文章です。一言添えたい時にどうぞ。
・最大接続数   : サーバ及び観戦で受け入れる最大人数を設定します。
                 後でいくらでも好きに変更できますので適当に入力しても大丈夫です。
・接続ポート   : サーバが開放しているポートを設定します。
                 サーバによっては7500以外のポートを使用している場合がありますので、その際は変更してください。

[Welcomeメッセージ]
  クライアントが接続して来た時に、ここに書かれたメッセージを自動送信します。

[IPの変換]
  IPを文字列に変換することで、IPを載せるリスクを多少なりとも軽減します。
  サーバを公開する際は、この機能で生成された文字列を使用してください。

◆ 鯖を立てるときの流れ
１．自分のIPを「IPの変換」タブの「変換前のIP」のところに入力
２．変換ボタンを押す
３．「変換後のIP」のところに出てきた文字列をコピペしてみんなに伝える
４．Serverモードで起動する

◆ 鯖に繋ぐときの流れ
１．接続先のところに、鯖の人が張った文字列を入力する
２．ポートを開放していたらHostモード、開放していなかったらClientモードで起動する


■ メンバーリスト
  Server/Host/Clientの違いで文字の色が、対戦中/休憩中/観戦中で背景の色が変わります。
  マウスでの操作は以下の通り。

[左ダブルクリック]
  ダブルクリックした対象により、いくつかの機能が使用できます。
  
・自分     : 休憩状態の切り替えや、対戦/観戦の中止が出来ます。
・メンバー : 状態を再取得し、ついでにPingを送ります。
・それ以外 : メンバーリストの表示を切り替えます。

[右クリック]
・対戦する : 選んだ人と対戦します。自分で自分に対戦すると一人プレイ用にゲームを起動します。
・観戦する : 選んだ人のプレイを観戦します。なお、休憩中でも観戦は可能です。
・Ping     : ちょっとした回線チェックにどうぞ。

休憩状態 : 休憩中の人にはネット対戦を申し込むことが出来なくなります。
           休憩中でも観戦は可能なため、一息入れたい時などにどうぞ。


■ オプション

◆ 設定
  オプションダイアログが表示されます。
  パスを設定する箇所は、ドラッグ＆ドロップによる指定も可能です。

[基本]
実行ファイルのパス   : ゲーム実行に必要なパスを設定します。これが適切に設定されていないとまともに動きません。
リプレイ保存フォルダ : リプレイファイルを保存するフォルダです。
自動振り分け         : ゲームごとにフォルダを作成し、そこにリプレイファイルを保存するようにします。

<回線設定>
最大接続数 : スタートアップ時の設定と同じです。
コメント   : コメントを編集します。チャット禁止サーバの時は、次回起動時まで変更が保留になります。

[音声]
対戦のお知らせ : 対戦を申し込まれた時に再生されます。
告知のお知らせ : サーバからの告知メッセージを受信した時に再生されます。
入室のお知らせ : 新メンバーが入室した時に再生されます。

[ゲーム]
<対戦設定>
最大ステージ数 : ゲームが使用しているステージ数を設定します。
                 プレイするゲームより多くのステージ数を設定した場合、エラーを起こします。
対戦ステージ   : 0を選ぶことで、対戦ステージがランダムで選ばれるようになります。
                 また、この値を最大ステージ数よりも大きくした場合、２つのステージ間をループするようになります。
ラウンド数     : 対戦するラウンド数です。格ツク95の場合、この値は無視され2ラウンド対戦になります。
ゲームタイマー : 対戦時の制限時間です。0で無制限になります。

<格ツク>
当たり判定の表示 : 格ツクのHitJudgeを有効にします。
640 x 480 で起動 : ゲーム起動時にウィンドウサイズを変更します。

<タイトルバー>
ニックネーム   : プレイヤー名、及び対戦者名を表示します。
対戦数         : 対戦回数と勝利回数を表示します。
フレームレート : 描画回数(キー入力回数％)。描画回数は体感速度、キー入力回数は格ツク内部の速度です。
乱数の使用回数 : 100フレームの間に使用された乱数の回数です。

<シミュレート>
ディレイ : １人プレイ時のみ、それも基本1P側のみ有効です。"0"で無効になります。
           ネット対戦時の入力ディレイをシミュレートします。

<リプレイファイル>
  リプレイファイルを圧縮するかどうかを指定します。

[カラー]
  各カラーの変更が行えます。
  デフォルトカラーに戻したい時は、プログラムが起動していない状態で、
  iniファイルの[Color]セクションの該当項目を削除してください。
  言ってることがよくわからなかったら、ini自体を削除するのが手っ取り早いです。

[音量]
BGM       : ループ再生させる音声ファイルの音量を設定します。
SE        : BGM以外の音声ファイルの音量を設定します。
SW シンセ : MIDIの音量を変更できますが、環境によっては使えません。

◆ ディレイ
  ネット対戦時に、キー入力から実際に反映されるまでのフレーム数です。
  少ないほど動作が機敏になりますが、ラグが発生しやすくなります。
  逆に大きいほど緩慢になる代わりに安定しますが、いざラグが発生した時の被害が大きくなります。
  こればかりは回線相性に左右されるので、いろいろ試して適切な値を探してください。

[Auto]
  対戦を申し込まれる方(Host側)をP1、申し込む方(Client側)をP2とします。

  ネット対戦時は両者の設定値で数値の大きい方に合わせます。
  P2がAutoに設定してある場合、対戦直前に回線速度を計りディレイ値を計算します。

  Delay = (Ping / 10) + 2    Max:12

  << よくわかる Delay Auto >>
  ・ P2 : Pingを使ってディレイを計算し、P1に渡す
                    ↓
  ・ P1 : Autoなら値をそのまま、数値を指定していたら大きい方の値を返す
                    ↓
  ・ P2 : 返ってきたディレイ値を使う
  
      P1    P2
     数値  数値  :  大きい方
     Auto  数値  :  P2の値
     Auto  Auto  :  計算値
     数値  Auto  :  計算値とP1の値を比べて大きい方

◆ リプレイファイルの保存
  チェックしていると、リプレイの再生以外で起動したゲームのリプレイを保存します。
  気がつくと異常な数のファイルが溜まっていて、整理を投げ出したくなります。

◆ 観戦の許可
  「最大接続数」で設定した人数分、観戦者を受け入れることが出来ます。
  また、観戦者がいる状態でチェックをはずすと、全ての観戦者を追い出します。
  多少なりとも対戦に影響が出るので、回線やマシンスペックに余裕がないときは切っておきましょう。

◆ ネット対戦後に一息入れる
  ネット対戦後に自動で休憩状態に入ります。
  対戦の後は優雅なティータイムで過ごしたい……そんなセレブにオススメの設定です。


■ 超簡易パス変更機能
  メインウィンドに格ツクの実行ファイルをドラッグ＆ドロップすることで、
  オプションを開かなくても手軽にパスの変更が出来ます。
  また、この機能で変更した場合に限りオプションの対戦設定が
  そのゲームのiniファイルにあわせ自動変更されます。


■ 入力欄あれこれ

◆ 告知
  サーバの人はメッセージを入力後、Ctrlキーを押しながらEnterキーを押すことで、
  チャットの可否に関わらず、メンバー全員に告知メッセージを送信することが出来ます。
  その際、メッセージに"_"(アンダースコア)が含まれていた場合、改行に自動変換されます。

  例えば「告知_メッセージ_です」と入力して送信すると、以下のように表示されます。

  告知
  メッセージ
  です

◆ コマンドの説明
  入力欄で"/"から始まるテキストを入力すると、いろいろな機能が使えたりします。

・/help    : コマンドの一覧を表示します。

・/clear   : 全てのログを削除します。

・/log     : 色つきテキストのRTF形式でログを保存します。
             ショートカットなどからログの保存を選んだ場合はTXT形式になります。

・/debug   : デバッグモードを切り替えます。デフォルトはオフです。
             オンの場合、デバッグに役立ちそうな情報を表示するようになりますが、ログが流れやすくなります。
             流れやすくなるだけで済めばいいのですが、対戦中は目に見えてfpsが下がります。
             またオンにした状態でプログラムを終了させると、"log.rtf"というログファイルが勝手に作られます。

・/vs      : ネット接続時＆自分がフリー状態の時のみ使用可能です。
             ランダムに選んだメンバーに対戦を挑みます。

・/game    : 一人用モードでゲームを起動します。

・/replay  : 保存していたリプレイファイルを再生します。

・/quit    : 起動中のゲームを終了させます。

・/restart : フリープレイの時のみ使用可能。プログラムをモード選択からやり直します。

・/rest    : 休憩状態の切り替えを行います。

・/list    : リストの表示を名前とコメントで切り替えます。

・/leave   : 鯖主なら鯖のシャットダウンを、蔵なら鯖から退室し、フリープレイに移行します。

・/exit    : プログラムを終了します。




■ あとがき
  Q. 鯖に接続できません
  A. DNSのチェックをはずしてください

  Q. 熱帯でズレます
  A. 入れ替えたステージは元に戻しておいてください


  熱帯でステージ設定が共有されるようになり、乱数使用ステージを気兼ねなく選べるようになったぞ！
  でも重たいステージだけは簡便な！

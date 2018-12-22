
## MapleMacro(UWSC) Ver 1.2
#### ★lib
*	ゲームマスターからの返答要求に自動レスポンスを行う機能を追加
	*	GM確認 : checkGameMaster()
	*	レスポンス文字列(5パターンからランダム)の取得 : getResponse()
	*	レスポンス文字列を用いて返答を行う : responseToGameMaster(getResponse())
*	画像認識用Helperメソッド追加 : picPathHelper("画像名")
　　　if chkimg("../picture/hoge.bmp")と書いていたところをpicPathHelplerに渡すことで画像ディレクトリパスと拡張子を省略できます。
　　　if chkimg(picPathHelper("hoge")) は　if chkimg("../picture/hoge.bmp")と同等です。

## MapleMacro(UWSC) Ver 1.3
#### ★Illium
*	イリウムスクリプトの全体的な改善とスクリプトの追加
#### ★lib
*	重くなってフリーズする対処法として定期的にメモリ解放を行う処理の追加
コマンド : # empty.exe *  
(WindowsServer2003 Resource Kit Tools)


## MapleMacro(UWSC) Ver 1.4
#### ★Illium
*	アーケインリバー狩場のスクリプトの追加
#### ★lib/MapleLibrary
*	ゲームマスター対策の改善
*	緊急時にスクリーンショットを保存する機能を追加
#### ★Common/Message
*	メッセージ定義追加

## MapleMacro Ver 1.5
#### ★GUI
* GUIの追加(Lumi,Kannna,Util)
#### ★Illium
* チューチューアイランド対応
#### ★MapleManagement
* ファイルの読み書きをし、処理を分岐させる
ほか色々な事をここで管理する

## MapleMacro Ver 1.6
#### ★History(新規)
* 履歴管理ファイルを追加しました。
	*	バグ修正履歴(BugFIX.txt)
	*	開発予定(DevelopList.txt)
#### ★lib
*	wait(sleepTime)追加
引数sleepTIme秒待機するメソッド


## MapleMacro Ver 1.6.1
#### ★Util/MapleUtil.uws
*	シュガータイム対応 -> getSugarTime()
スレッドを起動して30秒に1回受取確認を行います。
スレッド起動判定はMapleManagementクラスでiniファイルを読み込んで行います。
#### ★Common/Initialization.uws(新規追加)
*	共通初期化処理を行うようにします。

## Maplemacro Ver 1.6.2
#### ★/bin/ScriptExecutor.uws 新規追加
*	コマンドプロンプトから主要スクリプトを呼び出せます。
多言語からのAPIとして用意しました。
UWSCpath スクリプト名(path) で呼び出せます。
####★/var/log/MapleMacro/xxx.log
*	ログファイルの出力先を変更
共有して運用している場合は、MacroLog-"ユーザー名".log が個別に作成され出力されます。
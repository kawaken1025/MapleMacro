MapleMacro(UWSC) Ver 1.2<br>
★lib<br>
　　・ゲームマスターからの返答要求に自動レスポンスを行う機能を追加<br>
　　　GM確認 : checkGameMaster()<br>
　　　レスポンス文字列(5パターンからランダム)の取得 : getResponse()<br>
　　　レスポンス文字列を用いて返答を行う : responseToGameMaster(getResponse())<br>
　　・画像認識用Helperメソッド追加 : picPathHelper("画像名")<br>
　　　if chkimg("../picture/hoge.bmp")<br>
　　　と書いていたところをpicPathHelplerに渡すことで画像ディレクトリパスと拡張子を省略できます。<br>
　　　if chkimg(picPathHelper("hoge")) は　if chkimg("../picture/hoge.bmp")と同等です。<br><br>

MapleMacro(UWSC) Ver 1.3<br>
　★Illium<br>
　　・イリウムスクリプトの全体的な改善とスクリプトの追加<br>
　★lib<br>
　　・重くなってフリーズする対処法として定期的にメモリ解放を行う処理の追加<br>
　　コマンド : # empty.exe * <br>
　　(WindowsServer2003 Resource Kit Tools)<br>
<br><br>

MapleMacro(UWSC) Ver 1.4<br>
　★Illium<br>
　　・アーケインリバー狩場のスクリプトの追加<br>
　★lib/MapleLibrary<br>
　　・ゲームマスター対策の改善<br>
　　・緊急時にスクリーンショットを保存する機能を追加<br>
　★Common/Message<br>
　　・メッセージ定義追加<br><br>

MapleMacro Ver 1.5<br>
　★GUI<br>
　　・GUIの追加(Lumi,Kannna,Util)<br>
　★Illium<br>
　　・チューチューアイランド対応<br>
　★MapleManagement<br>
　　・ファイルの読み書きをし、処理を分岐させる<br>
　　ほか色々な事をここで管理する予定(PG中)<br><br>

MapleMacro Ver 1.6<br>
　★History(新規)<br>
　　履歴管理ファイルを追加しました。<br>
　　・バグ修正履歴(BugFIX.txt)<br>
　　・開発予定(DevelopList.txt)<br>
　★lib<br>
　　・wait(sleepTime)追加<br>
　　　引数sleepTIme秒待機するメソッド<br><br>

MapleStory Ver 1.6.1<br>
　★Util/MapleUtil.uws<br>
　　・シュガータイム対応 -> getSugarTime()<br>
　　 スレッドを起動して30秒に1回受取確認を行います。<br>
　　 スレッド起動判定はMapleManagementクラスでiniファイルを読み込んで行います。<br>
　★Common/Initialization.uws(新規追加)<br>
　　・共通初期化処理を行うようにします。<br><br>

MapleStory Ver 1.6.2<br>
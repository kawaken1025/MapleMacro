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
　★History(新規)
　　履歴管理ファイルを追加しました。
　　・バグ修正履歴(BugFIX.txt)
　　・開発予定(DevelopList.txt)
　★lib
　　・wait(sleepTime)追加
　　　引数sleepTIme秒待機するメソッド

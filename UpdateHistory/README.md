MapleMacro(UWSC) Ver 1.2
★lib
   ・ゲームマスターからの返答要求に自動レスポンスを行う機能を追加
     GM確認 : checkGameMaster()
     レスポンス文字列(5パターンからランダム)の取得 : getResponse()
     レスポンス文字列を用いて返答を行う : responseToGameMaster(getResponse())
   ・画像認識用Helperメソッド追加 : picPathHelper("画像名")
     if chkimg("../picture/hoge.bmp")
     と書いていたところをpicPathHelplerに渡すことで画像ディレクトリパスと拡張子を省略できます。
     if chkimg(picPathHelper("hoge")) は　if chkimg("../picture/hoge.bmp")と同等です。

MapleMacro(UWSC) Ver 1.3

★Illium
　・イリウムスクリプトの全体的な改善とスクリプトの追加
★lib
  ・重くなってフリーズする対処法として定期的にメモリ解放を行う処理の追加
   コマンド : # empty.exe *
   (WindowsServer2003 Resource Kit Tools)

MapleMacro(UWSC) Ver 1.4

★Illium
  ・アーケインリバー狩場のスクリプトの追加
★lib/MapleLibrary
  ・ゲームマスター対策の改善
  ・緊急時にスクリーンショットを保存する機能を追加
★Common/Message
  ・メッセージ定義追加
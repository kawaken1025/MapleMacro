# MapleUWSC_Macro
現在進行形で作成中のものから数年前に作ってメンテしていないものまで多数

★GUIで今回実現しようと思ってたこと<br>
  →hogehoge.uwsをGUIから実行させたい<br>

　<実行方法><br>
  "UWSC.exeのパス" "実行する.uwsスクリプトのパス"　をコマンドとしてprocessに渡す <br>
  例:"C:\UWSC\UWSC.exe C:\MapleMacro\Luminous\ケーヴロードの通路(上).uws" <br>
  <br>
  <未解決事項><br>
  パスをプログラム上でベタ書き状態で渡すと実行してくれるが、<br>
  将来的に設定ファイルから取得することを想定して<br>
  変数文字列連結させてコマンドを組み立てると実行してもらえない。<br>

  <該当プログラム><br>
  MapleAssistTool.cs 41行目<br>
  <br>
  //ボタンを押した際に呼び出され実行するコマンドを組み立てる<br>
  //グローバル変数のUWSパスとこの中で設定される.uws文字列を連結させる<br>
  private async void CaveLoadAisleUp_Click(object sender, EventArgs e)<br>
      組み立てたコマンドをexecCmd()メソッドにコマンドを渡してコマンドを実行してもらう <br>

 ->ベタで書いたコマンド文字列を渡すと実行される<br>
 ->文字列を連結させたものを渡すと実行されない<br>

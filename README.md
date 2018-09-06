# MapleUWSC_Macro
現在進行形で作成中のものから数年前に作ってメンテしていないものまで多数

#★GUIで今回実現しようと思ってたこと
  →hogehoge.uwsをGUIから実行させたい

　<実行方法>
  "UWSC.exeのパス" "実行する.uwsスクリプトのパス"　をコマンドとしてprocessに渡す
  例:"C:\UWSC\UWSC.exe C:\MapleMacro\Luminous\ケーヴロードの通路(上).uws"
  
  <未解決事項>
  パスをプログラム上でベタ書き状態で渡すと実行してくれるが、
  将来的に設定ファイルから取得することを想定して
  変数文字列連結させてコマンドを組み立てると実行してもらえない。

  <該当プログラム>
  MapleAssistTool.cs 41行目

  //ボタンを押した際に呼び出され実行するコマンドを組み立てる
  //グローバル変数のUWSパスとこの中で設定される.uws文字列を連結させる
  private async void CaveLoadAisleUp_Click(object sender, EventArgs e)
      組み立てたコマンドをexecCmd()メソッドにコマンドを渡してコマンドを実行してもらう

 ->ベタで書いたコマンド文字列を渡すと実行される
 ->文字列を連結させたものを渡すと実行されない

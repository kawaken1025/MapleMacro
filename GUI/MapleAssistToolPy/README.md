## MapleAssitTool ( GUI )

## 概要
UWSCスクリプトをGUIからキックする
UWSCアプリからのスクリプトの選択の手間を省くためのGUI

## 画面説明

![default](https://user-images.githubusercontent.com/35024331/52203403-827d8800-28b4-11e9-81ab-296ffc54f4ff.PNG)
左の職業を選択すると使用可能スクリプトが右の画面に表示されます。
静的に表示しているので、できれば動的にディレクトリの中を見て表示させるようにはしたい。。。
execModeはPythonスクリプトがないため未対応。
左下のSettingボタンはパスを設定する設定画面ですが、保存がうまく動作しないため非対応。

## 使用方法
### VisualStudioでビルド
GitHubから落としたMapleAssistToolPyソリューションファイル(.sln)を開きます。
開いたらReleaseでビルドします。
![default](https://user-images.githubusercontent.com/35024331/52203728-5b738600-28b5-11e9-8f3d-04a573745ab4.PNG)

./MapleAssistToolPy/bin/Release/
にMapleAssistToolPy.exeが出来ていればOKです。

### パスの設定
先ほどリリースビルドしたディレクトリの中からMapleAssistToolPy.exe.configを開きます。
(./MapleAssistToolPy/bin/Release/MapleAssistToolPy.exe.config)

![default](https://user-images.githubusercontent.com/35024331/52204087-801c2d80-28b6-11e9-8c4e-6e62810a546f.PNG)
UWSC.exeを置いてあるパスとマクロ一式の最上位絶対パスを設定します。
設定したら保存してください。

これでGUI上からUWSCスクリプトをkickできる・・・はずです。
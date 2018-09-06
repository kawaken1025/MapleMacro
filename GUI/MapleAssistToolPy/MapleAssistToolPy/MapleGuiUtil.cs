using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace MapleAssistToolPy
{
	
	class MapleGuiUtil
	{
		[DllImport("KERNEL32.DLL")]
		public static extern uint
		  GetPrivateProfileString(string lpAppName,
		  string lpKeyName, string lpDefault,
		  StringBuilder lpReturnedString, uint nSize,
		  string lpFileName);
		private string userName = Environment.UserName;       // ユーザー名を取得する

		public void execStartUp(bool execMode, string dir ,string macroName)
		{
			
			StopButton stopButton = new StopButton(macroName);
			settingStopButton(stopButton);
			stopButton.Show();

			execScript(execMode,dir,macroName);

		}

		public void settingStopButton(StopButton stopButton)
		{
			stopButton.Left = 800;
			stopButton.Top = 800;
			stopButton.StartPosition = FormStartPosition.Manual;
		}



		public int execScript(bool execMode,string dir,string macroName)
		{
			//UWSCボタンが選択されている場合true
			if (execMode)
			{
				//execCmd(dir,macroName);
			}
			else
			{
				//pythonCmd += " PY";

			}

			return 0;
		}

		//public void execCmd(string dir,string macroName)
		//{
		//	string uwscPath  = "\"" + System.Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory) + "\\UWSC\\UWSC.exe\" ";
		//	string macroPath = "\"C:\\Users\\test\\Desktop\\FileServer\\010_マクロ\\MapleMacro\\";
		//	string cmd = uwscPath + macroPath + dir + "\\" + macroName + ".uws\"";

			

		//	System.Diagnostics.Process p = new System.Diagnostics.Process();
		//	Console.WriteLine(cmd);
		//	//ComSpec(cmd.exe)のパスを取得して、FileNameプロパティに指定
		//	p.StartInfo.FileName = System.Environment.GetEnvironmentVariable("ComSpec");
		//	//出力を読み取れるようにする
		//	p.StartInfo.UseShellExecute = false;
		//	p.StartInfo.RedirectStandardOutput = true;
		//	p.StartInfo.RedirectStandardInput = false;
		//	//ウィンドウを表示しないようにする
		//	p.StartInfo.CreateNoWindow = true;
		//	//コマンドラインを指定（"/c"は実行後閉じるために必要）
		//	p.StartInfo.Arguments = @"/c " + cmd;

		//	//起動
		//	p.Start();

		//	//出力を読み取る
		//	string results = p.StandardOutput.ReadToEnd();

		//	//プロセス終了まで待機する
		//	//WaitForExitはReadToEndの後である必要がある
		//	//(親プロセス、子プロセスでブロック防止のため)
		//	p.WaitForExit();
		//	p.Close();

		//	//出力された結果を表示
		//	Console.WriteLine(results);
		//}


	}
}
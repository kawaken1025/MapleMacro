using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.Serialization;
using System.IO;
using Newtonsoft.Json;

namespace MapleAssistToolPy
{


	public partial class MapleAssistTool : Form
	{
		public string cmd = "";
		public MapleAssistTool()
		{
			InitializeComponent();
			this.LuminousPanel.Visible = true;
			this.UtilPanel.Visible = false;
			this.KannnaPanel.Visible = false;
		}

		MapleGuiUtil util = new MapleGuiUtil();

		private void LuminousButton_Click(object sender, EventArgs e)
		{
			this.LuminousPanel.Visible = true;
			this.UtilPanel.Visible = false;
			this.KannnaPanel.Visible = false;
		}


		//今回の問題のところ
		//ボタンを押した際にcmd変数のコマンドをプロセスに渡す設定
		private async void CaveLoadAisleUp_Click(object sender, EventArgs e)
		{
			//ひとまずCドライブにUWSCフォルダと.uwsファイルがある想定
			//ベタ書きでコマンドを設定(こっちは動く)
			cmd = "C:\\UWSC\\UWSC.exe C:\\MapleMacro\\Luminous\\ケーヴロードの通路(上).uws";
			Console.WriteLine("ベタ書きcmd=" + cmd);

			//UWSCパスと実行する.uwsスクリプトパスを変数に設定
			//UWSCパスはiniかどっかで将来的にユーザー側で設定させる予定
			string uwscExePath = "C:\\UWSC\\UWSC.exe "; //空白1文字
			string ScriptPath =  "C:\\MapleMacro\\Luminous\\ケーヴロードの通路(上).uws";
			//連結
			cmd = uwscExePath + ScriptPath;
			Console.WriteLine("文字列連結cmd=" + cmd);

			//execCmdにcmd変数を渡してコマンドプロンプトで実行させる
			await execCmd(cmd,this.CaveLoadAisleUp.Text);
			
		}

		private void MapleUnion_Click(object sender, EventArgs e)
		{
			util.execStartUp(this.UWSC_RadioButton.Checked, "Luminous",MapleUnion.Text);
		}

		private void UtilButton_Click(object sender, EventArgs e)
		{
			this.LuminousPanel.Visible = false;
			this.UtilPanel.Visible = true;
			this.KannnaPanel.Visible = false;
		}
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++
		// description : 非同期でスクリプトを起動する
		// param       : $1:CommandLine $2:ScriptName
		// comment     : executeCommand
		// return      : None
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++
		static async Task execCmd(string cmd, string macroName)
		{
			System.Diagnostics.Process p = new System.Diagnostics.Process();
			//ComSpec(cmd.exe)のパスを取得して、FileNameプロパティに指定
			p.StartInfo.FileName = System.Environment.GetEnvironmentVariable("ComSpec");
			//出力を読み取れるようにする
			p.StartInfo.UseShellExecute = false;
			p.StartInfo.RedirectStandardOutput = true;
			p.StartInfo.RedirectStandardInput = false;
			p.StartInfo.CreateNoWindow = true;
			//ウィンドウを表示しないようにする
			p.StartInfo.CreateNoWindow = true;
			//コマンドラインを指定（"/c"は実行後閉じるために必要）
			p.StartInfo.Arguments = @"/c " + cmd;
			p.EnableRaisingEvents = true;

			//起動
			p.Start();

		}

		private void KannnaButton_Click(object sender, EventArgs e)
		{
			this.LuminousPanel.Visible = false;
			this.UtilPanel.Visible = false;
			this.KannnaPanel.Visible = true;
		}
	}
}

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
		public string cmd  = "";
		public string job  = "";
		public string uwscExePath = @"C:\UWSC\UWSC.exe ";
		public MapleAssistTool()
		{
			InitializeComponent();
			this.LuminousPanel.Visible = true;
			this.UtilPanel.Visible = false;
			this.KannnaPanel.Visible = false;
			job = @"Luminous\";
		}

		MapleGuiUtil util;



		private async void CaveLoadAisleUp_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand("ケーヴロードの通路(上).uws"));
		}

		private async void MapleUnion_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand("MapleUnion.uws"));
		}

		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// Util群
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		private async void CoreCreate_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand("CoreCreate.uws"));
		}

		private async void CoreOpen_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand("CoreOpen.uws"));
		}

		private async void CoreBreak_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand("CoreBreak.uws"));
		}

		private async void BuyFamiliar_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand("BuyFamiliar.uws"));
		}

		private async void SellEquipment_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand("SellEquipment.uws"));
		}


		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// メニューバーの切り替えを行うメソッド群
		// グローバル変数jobに実行ディレクトリを設定する
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		private void LuminousButton_Click(object sender, EventArgs e)
		{
			this.LuminousPanel.Visible = true;
			this.UtilPanel.Visible = false;
			this.KannnaPanel.Visible = false;
			job = @"Luminous\";
		}

		private void UtilButton_Click(object sender, EventArgs e)
		{
			this.LuminousPanel.Visible = false;
			this.UtilPanel.Visible = true;
			this.KannnaPanel.Visible = false;
			job = @"Util\";
		}


		private void KannnaButton_Click(object sender, EventArgs e)
		{
			this.LuminousPanel.Visible = false;
			this.UtilPanel.Visible = false;
			this.KannnaPanel.Visible = true;
			job = @"Kannna\";
		}

		private string setCommand(string macroName)
		{
			return uwscExePath + @"\\KAWAKEN\FileServer\010_マクロ\MapleMacro\" + job + macroName;
		}

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++
		// description : スクリプトを起動する
		// param       : $2:ScriptName
		// comment     : executeCommand
		// return      : None
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++
		static async Task execCmd(string cmd)
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


	}
}

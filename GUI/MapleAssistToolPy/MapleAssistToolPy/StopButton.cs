using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapleAssistToolPy
{
	public partial class StopButton : Form
	{
		private string mcrName = "";
		public StopButton(string macroName)
		{
			this.mcrName = macroName; 
			InitializeComponent();
			this.execMacroName.Text = macroName;
		}

		private void Stop_Click(object sender, EventArgs e)
		{
			//notepadのプロセスを取得
			System.Diagnostics.Process[] ps =
				System.Diagnostics.Process.GetProcessesByName("uwsc");

			foreach (System.Diagnostics.Process p in ps)
			{
				//クローズメッセージを送信する
				p.CloseMainWindow();

				//プロセスが終了するまで最大10秒待機する
				p.WaitForExit(10000);
				//プロセスが終了したか確認する
				if (p.HasExited)
				{
					Console.WriteLine("uwscが終了しました。");
				}
				else
				{
					Console.WriteLine("uwscが終了しませんでした。");
				}
			}
		}

		public int stopScript()
		{
			return 0;
		}
	}
}

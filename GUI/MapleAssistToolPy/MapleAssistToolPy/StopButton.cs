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
			Process p = Process.Start("UWSC.exe");
			// 起動したプロセスを終了させる
			p.CloseMainWindow();
			p.Close();

			// プロセスを強制終了させる
			p.Kill();
			//stop画面を閉じる
			this.Close();
		}

		public int stopScript()
		{
			return 0;
		}
	}
}

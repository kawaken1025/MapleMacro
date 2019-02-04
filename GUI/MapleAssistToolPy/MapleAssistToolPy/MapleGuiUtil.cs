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

		public async Task execStartUp(string macroName)
		{

			StopButton stopButton = new StopButton(macroName);
			settingStopButton(stopButton);
			stopButton.Show();
			return;

		}

		public void settingStopButton(StopButton stopButton)
		{
			stopButton.Left = 800;
			stopButton.Top = 800;
			stopButton.StartPosition = FormStartPosition.Manual;
		}
	}
}
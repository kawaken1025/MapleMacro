using System;
using System.Threading.Tasks;
using System.Windows.Forms;
using MapleAssistToolPy.Common.Enumlation;
using System.Configuration;

namespace MapleAssistToolPy
{
    public partial class MapleAssistTool : Form
	{
		public string cmd  = "";
		public string job  = "";
		private  string execScript = "";
		public string uwscExePath = ConfigurationManager.AppSettings.Get("uwsc_exe_path") + " ";
		public string user = Environment.MachineName;
		private MapleGuiUtil util = new MapleGuiUtil();

		/// <summary>
		/// default constructor
		/// </summary>
		public MapleAssistTool()
		{
			InitializeComponent();
			this.LuminousPanel.Visible = true;
			this.UtilPanel.Visible = false;
			this.KannnaPanel.Visible = false;
			job = @"Luminous\";
		}

		
		/// <summary>
		/// ケーヴロードの通路(上).uws呼び出し
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private async void CaveLoadAisleUp_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand(ScriptNameEnum.CaveloadAisleUp.ObtainScriptName()));
		}

		/// <summary>
		/// MapleUnion.uws呼び出し
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private async void MapleUnion_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand(ScriptNameEnum.MapleUnion.ObtainScriptName()));
		}

		/// <summary>
		/// 押されたボタンのスクリプト名を設定
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		private async void CoreCreate_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand(ScriptNameEnum.CoreCreate.ObtainScriptName()));
		}

		private async void CoreOpen_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand(ScriptNameEnum.CoreOpen.ObtainScriptName()));
		}

		private async void CoreBreak_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand(ScriptNameEnum.CoreBreak.ObtainScriptName()));
		}

		private async void BuyFamiliar_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand(ScriptNameEnum.BuyFamiliar.ObtainScriptName()));
		}

		private async void SellEquipment_Click(object sender, EventArgs e)
		{
			await execCmd(setCommand(ScriptNameEnum.SellEquipment.ObtainScriptName()));
		}


	    /// <summary>
		/// ボタンを押された職業のパスを設定するメソッド群
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
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

		/// <summary>
		/// UWSCスクリプト実行コマンドの引数に設定するパスを設定
		/// 将来的にはどこか設定画面をつけたい
		/// </summary>
		/// <param name="macroName"></param>
		/// <returns></returns>
		private string setCommand(string macroName)
		{
			return uwscExePath + ConfigurationManager.AppSettings.Get("macro_dir_path") + @"\" + job + macroName;
		}

		/// <summary>
		/// スクリプトの呼び出し
		/// </summary>
		/// <param name="scriptName"></param>
		/// <returns></returns>
		static async Task execCmd(string scriptName)
		{
			try
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
				p.StartInfo.Arguments = @"/c " + scriptName;
				p.EnableRaisingEvents = true;

				//起動
				p.Start();
				return;
			}
			catch (Exception e)
			{
				//握りつぶす
			}



		}

		private void SettingButton_Click(object sender, EventArgs e)
		{
			SettingView view = new SettingView();
			view.Show();
		}
	}
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;
using System.Collections.Specialized;

namespace MapleAssistToolPy
{
	public partial class SettingView : Form
	{
		public SettingView()
		{
			InitializeComponent();
			DirTextBox.Text = ConfigurationManager.AppSettings.Get("macro_dir_path");
			uwscTextBox.Text = ConfigurationManager.AppSettings.Get("uwsc_exe_path");
		}

		private void UWSCpathButton_Click(object sender, EventArgs e)
		{
			//OpenFileDialogクラスのインスタンスを作成
			OpenFileDialog ofd = new OpenFileDialog();

			//はじめのファイル名を指定する
			//はじめに「ファイル名」で表示される文字列を指定する
			ofd.FileName = "default.html";
			//はじめに表示されるフォルダを指定する
			//指定しない（空の文字列）の時は、現在のディレクトリが表示される
			ofd.InitialDirectory = @"C:\";
			//[ファイルの種類]に表示される選択肢を指定する
			//指定しないとすべてのファイルが表示される
			ofd.Filter = "HTMLファイル(*.html;*.htm)|*.html;*.htm|すべてのファイル(*.*)|*.*";
			//[ファイルの種類]ではじめに選択されるものを指定する
			//2番目の「すべてのファイル」が選択されているようにする
			ofd.FilterIndex = 2;
			//タイトルを設定する
			ofd.Title = "開くファイルを選択してください";
			//ダイアログボックスを閉じる前に現在のディレクトリを復元するようにする
			ofd.RestoreDirectory = true;
			//存在しないファイルの名前が指定されたとき警告を表示する
			//デフォルトでTrueなので指定する必要はない
			ofd.CheckFileExists = true;
			//存在しないパスが指定されたとき警告を表示する
			//デフォルトでTrueなので指定する必要はない
			ofd.CheckPathExists = true;

			//ダイアログを表示する
			if (ofd.ShowDialog() == DialogResult.OK)
			{
				//	System.IO.StreamWriter sw = new System.IO.StreamWriter(
				//		@"./Conf/UWSC_PATH",
				//		false,
				//		System.Text.Encoding.GetEncoding("shift_jis"));

				//	sw.Write(ofd.FileName);
				//閉じる
				//	sw.Close();
			}
		}

		private void button3_Click(object sender, EventArgs e)
		{
			Configuration config = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
			config.AppSettings.Settings["macro_dir_path"].Value = DirTextBox.Text;
			config.AppSettings.Settings["uwsc_exe_path"].Value = uwscTextBox.Text;
			config.Save(ConfigurationSaveMode.Full);
			ConfigurationManager.RefreshSection("appSettings");
			
		}
	}
}

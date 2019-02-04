namespace MapleAssistToolPy
{
	partial class MapleAssistTool
	{
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows フォーム デザイナーで生成されたコード

		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MapleAssistTool));
			this.MenuPanel = new System.Windows.Forms.Panel();
			this.PythonRadioButton = new System.Windows.Forms.RadioButton();
			this.UWSC_RadioButton = new System.Windows.Forms.RadioButton();
			this.execModeLabel = new System.Windows.Forms.Label();
			this.SettingButton = new System.Windows.Forms.Button();
			this.LuminousButton = new System.Windows.Forms.Button();
			this.KannnaButton = new System.Windows.Forms.Button();
			this.UtilButton = new System.Windows.Forms.Button();
			this.LuminousPanel = new System.Windows.Forms.Panel();
			this.label1 = new System.Windows.Forms.Label();
			this.MapleUnion = new System.Windows.Forms.Button();
			this.ChuChu = new System.Windows.Forms.Button();
			this.honsyo3 = new System.Windows.Forms.Button();
			this.CaveLoadAisleUp = new System.Windows.Forms.Button();
			this.UtilPanel = new System.Windows.Forms.Panel();
			this.BuyFamiliar = new System.Windows.Forms.Button();
			this.MapleUtility = new System.Windows.Forms.Label();
			this.CoreCreate = new System.Windows.Forms.Button();
			this.SellEquipment = new System.Windows.Forms.Button();
			this.CoreBreak = new System.Windows.Forms.Button();
			this.CoreOpen = new System.Windows.Forms.Button();
			this.KannnaPanel = new System.Windows.Forms.Panel();
			this.label2 = new System.Windows.Forms.Label();
			this.CaveLoadWait = new System.Windows.Forms.Button();
			this.置きカンナ = new System.Windows.Forms.Button();
			this.カンナアイテム回収回復 = new System.Windows.Forms.Button();
			this.MenuPanel.SuspendLayout();
			this.LuminousPanel.SuspendLayout();
			this.UtilPanel.SuspendLayout();
			this.KannnaPanel.SuspendLayout();
			this.SuspendLayout();
			// 
			// MenuPanel
			// 
			this.MenuPanel.BackColor = System.Drawing.SystemColors.ActiveCaption;
			this.MenuPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.MenuPanel.Controls.Add(this.PythonRadioButton);
			this.MenuPanel.Controls.Add(this.UWSC_RadioButton);
			this.MenuPanel.Controls.Add(this.execModeLabel);
			this.MenuPanel.Controls.Add(this.SettingButton);
			this.MenuPanel.Controls.Add(this.LuminousButton);
			this.MenuPanel.Controls.Add(this.KannnaButton);
			this.MenuPanel.Controls.Add(this.UtilButton);
			this.MenuPanel.Location = new System.Drawing.Point(0, -2);
			this.MenuPanel.Name = "MenuPanel";
			this.MenuPanel.Size = new System.Drawing.Size(126, 498);
			this.MenuPanel.TabIndex = 0;
			// 
			// PythonRadioButton
			// 
			this.PythonRadioButton.AutoSize = true;
			this.PythonRadioButton.Location = new System.Drawing.Point(65, 20);
			this.PythonRadioButton.Name = "PythonRadioButton";
			this.PythonRadioButton.Size = new System.Drawing.Size(58, 16);
			this.PythonRadioButton.TabIndex = 6;
			this.PythonRadioButton.Text = "Python";
			this.PythonRadioButton.UseVisualStyleBackColor = true;
			// 
			// UWSC_RadioButton
			// 
			this.UWSC_RadioButton.AutoSize = true;
			this.UWSC_RadioButton.Checked = global::MapleAssistToolPy.Properties.Settings.Default.UWSC_Button;
			this.UWSC_RadioButton.Cursor = System.Windows.Forms.Cursors.Default;
			this.UWSC_RadioButton.DataBindings.Add(new System.Windows.Forms.Binding("Checked", global::MapleAssistToolPy.Properties.Settings.Default, "UWSC_Button", true, System.Windows.Forms.DataSourceUpdateMode.OnPropertyChanged));
			this.UWSC_RadioButton.Location = new System.Drawing.Point(4, 20);
			this.UWSC_RadioButton.Name = "UWSC_RadioButton";
			this.UWSC_RadioButton.Size = new System.Drawing.Size(55, 16);
			this.UWSC_RadioButton.TabIndex = 5;
			this.UWSC_RadioButton.TabStop = true;
			this.UWSC_RadioButton.Text = "UWSC";
			this.UWSC_RadioButton.UseVisualStyleBackColor = true;
			// 
			// execModeLabel
			// 
			this.execModeLabel.AutoSize = true;
			this.execModeLabel.Location = new System.Drawing.Point(3, 5);
			this.execModeLabel.Name = "execModeLabel";
			this.execModeLabel.Size = new System.Drawing.Size(56, 12);
			this.execModeLabel.TabIndex = 0;
			this.execModeLabel.Text = "execMode";
			// 
			// SettingButton
			// 
			this.SettingButton.Location = new System.Drawing.Point(0, 471);
			this.SettingButton.Name = "SettingButton";
			this.SettingButton.Size = new System.Drawing.Size(123, 24);
			this.SettingButton.TabIndex = 4;
			this.SettingButton.Text = "Setting";
			this.SettingButton.UseVisualStyleBackColor = true;
			this.SettingButton.Click += new System.EventHandler(this.SettingButton_Click);
			// 
			// LuminousButton
			// 
			this.LuminousButton.Location = new System.Drawing.Point(0, 41);
			this.LuminousButton.Name = "LuminousButton";
			this.LuminousButton.Size = new System.Drawing.Size(123, 54);
			this.LuminousButton.TabIndex = 2;
			this.LuminousButton.Text = "Luminous";
			this.LuminousButton.UseVisualStyleBackColor = true;
			this.LuminousButton.Click += new System.EventHandler(this.LuminousButton_Click);
			// 
			// KannnaButton
			// 
			this.KannnaButton.Location = new System.Drawing.Point(0, 93);
			this.KannnaButton.Name = "KannnaButton";
			this.KannnaButton.Size = new System.Drawing.Size(123, 54);
			this.KannnaButton.TabIndex = 4;
			this.KannnaButton.Text = "Kannna";
			this.KannnaButton.UseVisualStyleBackColor = true;
			this.KannnaButton.Click += new System.EventHandler(this.KannnaButton_Click);
			// 
			// UtilButton
			// 
			this.UtilButton.Location = new System.Drawing.Point(0, 145);
			this.UtilButton.Name = "UtilButton";
			this.UtilButton.Size = new System.Drawing.Size(123, 54);
			this.UtilButton.TabIndex = 3;
			this.UtilButton.Text = "Util";
			this.UtilButton.UseVisualStyleBackColor = true;
			this.UtilButton.Click += new System.EventHandler(this.UtilButton_Click);
			// 
			// LuminousPanel
			// 
			this.LuminousPanel.BackColor = System.Drawing.Color.Transparent;
			this.LuminousPanel.Controls.Add(this.label1);
			this.LuminousPanel.Controls.Add(this.MapleUnion);
			this.LuminousPanel.Controls.Add(this.ChuChu);
			this.LuminousPanel.Controls.Add(this.honsyo3);
			this.LuminousPanel.Controls.Add(this.CaveLoadAisleUp);
			this.LuminousPanel.Location = new System.Drawing.Point(132, 3);
			this.LuminousPanel.Name = "LuminousPanel";
			this.LuminousPanel.Size = new System.Drawing.Size(503, 314);
			this.LuminousPanel.TabIndex = 1;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label1.Location = new System.Drawing.Point(15, 13);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(128, 24);
			this.label1.TabIndex = 8;
			this.label1.Text = "Job:Luminous";
			// 
			// MapleUnion
			// 
			this.MapleUnion.Location = new System.Drawing.Point(8, 141);
			this.MapleUnion.Name = "MapleUnion";
			this.MapleUnion.Size = new System.Drawing.Size(123, 54);
			this.MapleUnion.TabIndex = 7;
			this.MapleUnion.Text = "ユニオン";
			this.MapleUnion.UseVisualStyleBackColor = true;
			this.MapleUnion.Click += new System.EventHandler(this.MapleUnion_Click);
			// 
			// ChuChu
			// 
			this.ChuChu.Location = new System.Drawing.Point(8, 35);
			this.ChuChu.Name = "ChuChu";
			this.ChuChu.Size = new System.Drawing.Size(123, 54);
			this.ChuChu.TabIndex = 6;
			this.ChuChu.Text = "チューチュー(奥)";
			this.ChuChu.UseVisualStyleBackColor = true;
			// 
			// honsyo3
			// 
			this.honsyo3.Location = new System.Drawing.Point(137, 36);
			this.honsyo3.Name = "honsyo3";
			this.honsyo3.Size = new System.Drawing.Size(123, 54);
			this.honsyo3.TabIndex = 5;
			this.honsyo3.Text = "本性が現れる場所3";
			this.honsyo3.UseVisualStyleBackColor = true;
			// 
			// CaveLoadAisleUp
			// 
			this.CaveLoadAisleUp.Location = new System.Drawing.Point(266, 35);
			this.CaveLoadAisleUp.Name = "CaveLoadAisleUp";
			this.CaveLoadAisleUp.Size = new System.Drawing.Size(123, 54);
			this.CaveLoadAisleUp.TabIndex = 3;
			this.CaveLoadAisleUp.Text = "ケーヴロードの通路(上)";
			this.CaveLoadAisleUp.UseVisualStyleBackColor = true;
			this.CaveLoadAisleUp.Click += new System.EventHandler(this.CaveLoadAisleUp_Click);
			// 
			// UtilPanel
			// 
			this.UtilPanel.BackColor = System.Drawing.Color.Transparent;
			this.UtilPanel.Controls.Add(this.BuyFamiliar);
			this.UtilPanel.Controls.Add(this.MapleUtility);
			this.UtilPanel.Controls.Add(this.CoreCreate);
			this.UtilPanel.Controls.Add(this.SellEquipment);
			this.UtilPanel.Controls.Add(this.CoreBreak);
			this.UtilPanel.Controls.Add(this.CoreOpen);
			this.UtilPanel.Location = new System.Drawing.Point(132, 3);
			this.UtilPanel.Name = "UtilPanel";
			this.UtilPanel.Size = new System.Drawing.Size(503, 305);
			this.UtilPanel.TabIndex = 2;
			// 
			// BuyFamiliar
			// 
			this.BuyFamiliar.Location = new System.Drawing.Point(138, 35);
			this.BuyFamiliar.Name = "BuyFamiliar";
			this.BuyFamiliar.Size = new System.Drawing.Size(123, 54);
			this.BuyFamiliar.TabIndex = 9;
			this.BuyFamiliar.Text = "ファミリア購入";
			this.BuyFamiliar.UseVisualStyleBackColor = true;
			this.BuyFamiliar.Click += new System.EventHandler(this.BuyFamiliar_Click);
			// 
			// MapleUtility
			// 
			this.MapleUtility.AutoSize = true;
			this.MapleUtility.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.MapleUtility.Location = new System.Drawing.Point(19, 12);
			this.MapleUtility.Name = "MapleUtility";
			this.MapleUtility.Size = new System.Drawing.Size(113, 24);
			this.MapleUtility.TabIndex = 8;
			this.MapleUtility.Text = "MapleUtility";
			// 
			// CoreCreate
			// 
			this.CoreCreate.Location = new System.Drawing.Point(266, 95);
			this.CoreCreate.Name = "CoreCreate";
			this.CoreCreate.Size = new System.Drawing.Size(123, 54);
			this.CoreCreate.TabIndex = 7;
			this.CoreCreate.Text = "コア作成";
			this.CoreCreate.UseVisualStyleBackColor = true;
			this.CoreCreate.Click += new System.EventHandler(this.CoreCreate_Click);
			// 
			// SellEquipment
			// 
			this.SellEquipment.Location = new System.Drawing.Point(8, 35);
			this.SellEquipment.Name = "SellEquipment";
			this.SellEquipment.Size = new System.Drawing.Size(123, 54);
			this.SellEquipment.TabIndex = 6;
			this.SellEquipment.Text = "装備売却";
			this.SellEquipment.UseVisualStyleBackColor = true;
			this.SellEquipment.Click += new System.EventHandler(this.SellEquipment_Click);
			// 
			// CoreBreak
			// 
			this.CoreBreak.Location = new System.Drawing.Point(8, 95);
			this.CoreBreak.Name = "CoreBreak";
			this.CoreBreak.Size = new System.Drawing.Size(123, 54);
			this.CoreBreak.TabIndex = 5;
			this.CoreBreak.Text = "コア分解";
			this.CoreBreak.UseVisualStyleBackColor = true;
			this.CoreBreak.Click += new System.EventHandler(this.CoreBreak_Click);
			// 
			// CoreOpen
			// 
			this.CoreOpen.Location = new System.Drawing.Point(137, 95);
			this.CoreOpen.Name = "CoreOpen";
			this.CoreOpen.Size = new System.Drawing.Size(123, 54);
			this.CoreOpen.TabIndex = 3;
			this.CoreOpen.Text = "コア開封";
			this.CoreOpen.UseVisualStyleBackColor = true;
			this.CoreOpen.Click += new System.EventHandler(this.CoreOpen_Click);
			// 
			// KannnaPanel
			// 
			this.KannnaPanel.BackColor = System.Drawing.Color.Transparent;
			this.KannnaPanel.Controls.Add(this.label2);
			this.KannnaPanel.Controls.Add(this.CaveLoadWait);
			this.KannnaPanel.Controls.Add(this.置きカンナ);
			this.KannnaPanel.Controls.Add(this.カンナアイテム回収回復);
			this.KannnaPanel.Location = new System.Drawing.Point(132, 3);
			this.KannnaPanel.Name = "KannnaPanel";
			this.KannnaPanel.Size = new System.Drawing.Size(503, 314);
			this.KannnaPanel.TabIndex = 3;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Font = new System.Drawing.Font("メイリオ", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label2.Location = new System.Drawing.Point(15, 13);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(110, 24);
			this.label2.TabIndex = 8;
			this.label2.Text = "Job:Kannna";
			// 
			// CaveLoadWait
			// 
			this.CaveLoadWait.Location = new System.Drawing.Point(8, 35);
			this.CaveLoadWait.Name = "CaveLoadWait";
			this.CaveLoadWait.Size = new System.Drawing.Size(123, 54);
			this.CaveLoadWait.TabIndex = 6;
			this.CaveLoadWait.Text = "ケーヴロードの通路(上)回収";
			this.CaveLoadWait.UseVisualStyleBackColor = true;
			// 
			// 置きカンナ
			// 
			this.置きカンナ.Location = new System.Drawing.Point(137, 36);
			this.置きカンナ.Name = "置きカンナ";
			this.置きカンナ.Size = new System.Drawing.Size(123, 54);
			this.置きカンナ.TabIndex = 5;
			this.置きカンナ.Text = "置きカンナ";
			this.置きカンナ.UseVisualStyleBackColor = true;
			// 
			// カンナアイテム回収回復
			// 
			this.カンナアイテム回収回復.Location = new System.Drawing.Point(266, 35);
			this.カンナアイテム回収回復.Name = "カンナアイテム回収回復";
			this.カンナアイテム回収回復.Size = new System.Drawing.Size(123, 54);
			this.カンナアイテム回収回復.TabIndex = 3;
			this.カンナアイテム回収回復.Text = "アイテム回収";
			this.カンナアイテム回収回復.UseVisualStyleBackColor = true;
			// 
			// MapleAssistTool
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
			this.ClientSize = new System.Drawing.Size(751, 495);
			this.Controls.Add(this.UtilPanel);
			this.Controls.Add(this.KannnaPanel);
			this.Controls.Add(this.LuminousPanel);
			this.Controls.Add(this.MenuPanel);
			this.Name = "MapleAssistTool";
			this.Text = "MapleAssistTool version : 0.3";
			this.MenuPanel.ResumeLayout(false);
			this.MenuPanel.PerformLayout();
			this.LuminousPanel.ResumeLayout(false);
			this.LuminousPanel.PerformLayout();
			this.UtilPanel.ResumeLayout(false);
			this.UtilPanel.PerformLayout();
			this.KannnaPanel.ResumeLayout(false);
			this.KannnaPanel.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Panel MenuPanel;
		private System.Windows.Forms.Button LuminousButton;
		private System.Windows.Forms.Button UtilButton;
		private System.Windows.Forms.Button KannnaButton;
		private System.Windows.Forms.Button SettingButton;
		private System.Windows.Forms.Panel LuminousPanel;
		private System.Windows.Forms.Label execModeLabel;
		private System.Windows.Forms.RadioButton radioButton2;
		private System.Windows.Forms.GroupBox excModeGroup;
		private System.Windows.Forms.RadioButton radioButton1;
		private System.Windows.Forms.RadioButton UWSC_RadioButton;
		private System.Windows.Forms.RadioButton PythonRadioButton;
		private System.Windows.Forms.Button CaveLoadAisleUp;
		private System.Windows.Forms.Button MapleUnion;
		private System.Windows.Forms.Button ChuChu;
		private System.Windows.Forms.Button honsyo3;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Panel UtilPanel;
		private System.Windows.Forms.Button BuyFamiliar;
		private System.Windows.Forms.Label MapleUtility;
		private System.Windows.Forms.Button CoreCreate;
		private System.Windows.Forms.Button SellEquipment;
		private System.Windows.Forms.Button CoreBreak;
		private System.Windows.Forms.Button CoreOpen;
		private System.Windows.Forms.Panel KannnaPanel;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button CaveLoadWait;
		private System.Windows.Forms.Button 置きカンナ;
		private System.Windows.Forms.Button カンナアイテム回収回復;
	}
}


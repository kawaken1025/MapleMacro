namespace MapleAssistToolPy
{
	partial class StopButton
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.startText = new System.Windows.Forms.Label();
			this.timeHHMMDD = new System.Windows.Forms.Label();
			this.Stop = new System.Windows.Forms.Button();
			this.execMacroName = new System.Windows.Forms.Label();
			this.execMacroNameLabel = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// startText
			// 
			this.startText.AutoSize = true;
			this.startText.Location = new System.Drawing.Point(12, 9);
			this.startText.Name = "startText";
			this.startText.Size = new System.Drawing.Size(61, 12);
			this.startText.TabIndex = 0;
			this.startText.Text = "[起動時間]";
			// 
			// timeHHMMDD
			// 
			this.timeHHMMDD.AutoSize = true;
			this.timeHHMMDD.Location = new System.Drawing.Point(19, 23);
			this.timeHHMMDD.Name = "timeHHMMDD";
			this.timeHHMMDD.Size = new System.Drawing.Size(45, 12);
			this.timeHHMMDD.TabIndex = 1;
			this.timeHHMMDD.Text = "00:00:00";
			// 
			// Stop
			// 
			this.Stop.Font = new System.Drawing.Font("メイリオ", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.Stop.Location = new System.Drawing.Point(21, 47);
			this.Stop.Name = "Stop";
			this.Stop.Size = new System.Drawing.Size(316, 105);
			this.Stop.TabIndex = 2;
			this.Stop.Text = "StopScript";
			this.Stop.UseVisualStyleBackColor = true;
			this.Stop.Click += new System.EventHandler(this.Stop_Click);
			// 
			// execMacroName
			// 
			this.execMacroName.AutoSize = true;
			this.execMacroName.Location = new System.Drawing.Point(138, 23);
			this.execMacroName.Name = "execMacroName";
			this.execMacroName.Size = new System.Drawing.Size(64, 12);
			this.execMacroName.TabIndex = 3;
			this.execMacroName.Text = "ScriptName";
			// 
			// execMacroNameLabel
			// 
			this.execMacroNameLabel.AutoSize = true;
			this.execMacroNameLabel.Location = new System.Drawing.Point(129, 9);
			this.execMacroNameLabel.Name = "execMacroNameLabel";
			this.execMacroNameLabel.Size = new System.Drawing.Size(63, 12);
			this.execMacroNameLabel.TabIndex = 4;
			this.execMacroNameLabel.Text = "[起動マクロ]";
			// 
			// StopButton
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(358, 164);
			this.Controls.Add(this.execMacroNameLabel);
			this.Controls.Add(this.execMacroName);
			this.Controls.Add(this.Stop);
			this.Controls.Add(this.timeHHMMDD);
			this.Controls.Add(this.startText);
			this.Name = "StopButton";
			this.Text = "StopButton";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label startText;
		private System.Windows.Forms.Label timeHHMMDD;
		private System.Windows.Forms.Button Stop;
		private System.Windows.Forms.Label execMacroName;
		private System.Windows.Forms.Label execMacroNameLabel;
	}
}
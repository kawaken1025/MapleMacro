namespace MapleAssistToolPy
{
	partial class SettingView
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
			this.uwscTextBox = new System.Windows.Forms.TextBox();
			this.DirTextBox = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.UWSCpathButton = new System.Windows.Forms.Button();
			this.MacroDirectoryButton = new System.Windows.Forms.Button();
			this.button3 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// uwscTextBox
			// 
			this.uwscTextBox.Location = new System.Drawing.Point(117, 28);
			this.uwscTextBox.Name = "uwscTextBox";
			this.uwscTextBox.Size = new System.Drawing.Size(348, 19);
			this.uwscTextBox.TabIndex = 0;
			// 
			// DirTextBox
			// 
			this.DirTextBox.Location = new System.Drawing.Point(117, 55);
			this.DirTextBox.Name = "DirTextBox";
			this.DirTextBox.Size = new System.Drawing.Size(348, 19);
			this.DirTextBox.TabIndex = 1;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(35, 31);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(76, 12);
			this.label1.TabIndex = 2;
			this.label1.Text = "UWSC.exeパス";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(12, 58);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(99, 12);
			this.label2.TabIndex = 3;
			this.label2.Text = "マクロディレクトリパス";
			// 
			// UWSCpathButton
			// 
			this.UWSCpathButton.Location = new System.Drawing.Point(471, 28);
			this.UWSCpathButton.Name = "UWSCpathButton";
			this.UWSCpathButton.Size = new System.Drawing.Size(27, 19);
			this.UWSCpathButton.TabIndex = 4;
			this.UWSCpathButton.Text = "...";
			this.UWSCpathButton.UseVisualStyleBackColor = true;
			this.UWSCpathButton.Click += new System.EventHandler(this.UWSCpathButton_Click);
			// 
			// MacroDirectoryButton
			// 
			this.MacroDirectoryButton.Location = new System.Drawing.Point(471, 56);
			this.MacroDirectoryButton.Name = "MacroDirectoryButton";
			this.MacroDirectoryButton.Size = new System.Drawing.Size(27, 19);
			this.MacroDirectoryButton.TabIndex = 5;
			this.MacroDirectoryButton.Text = "...";
			this.MacroDirectoryButton.UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(373, 97);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(125, 42);
			this.button3.TabIndex = 6;
			this.button3.Text = "保存";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new System.EventHandler(this.button3_Click);
			// 
			// SettingView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(504, 154);
			this.Controls.Add(this.button3);
			this.Controls.Add(this.MacroDirectoryButton);
			this.Controls.Add(this.UWSCpathButton);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.DirTextBox);
			this.Controls.Add(this.uwscTextBox);
			this.Name = "SettingView";
			this.Text = "SettingViews";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox uwscTextBox;
		private System.Windows.Forms.TextBox DirTextBox;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button UWSCpathButton;
		private System.Windows.Forms.Button MacroDirectoryButton;
		private System.Windows.Forms.Button button3;
	}
}
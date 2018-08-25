namespace WindowsFormsApplication1
{
    partial class teach
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
            this.teachForm1 = new CommonUI.TeachForm();
            this.SuspendLayout();
            // 
            // teachForm1
            // 
            this.teachForm1.Location = new System.Drawing.Point(7, 1);
            this.teachForm1.Name = "teachForm1";
            this.teachForm1.Size = new System.Drawing.Size(1122, 482);
            this.teachForm1.TabIndex = 0;
            // 
            // teach
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1133, 495);
            this.Controls.Add(this.teachForm1);
            this.Name = "teach";
            this.Text = "teach";
            this.ResumeLayout(false);

        }

        #endregion

        private CommonUI.TeachForm teachForm1;
    }
}
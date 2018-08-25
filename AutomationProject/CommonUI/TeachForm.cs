using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace CommonUI
{
    public partial class TeachForm : UserControl
    {
      //  private TeachSet_CS _TeachSet;//现Teach表

        public TeachForm()
        {
            InitializeComponent();

            InitUI();
        }


        private void InitUI()
        {
            gridTeachData.Columns[1].Width = 180;
            gridTeachData.Columns[2].Width = 200;
            gridTeachData.Columns[3].Width = 210;
            gridTeachData.Columns[4].Width = 140;
        }

        public void UpdateTable()
        {
            gridTeachData.Rows.Clear();

            //if (_TeachSet == null)
            //{
            //    return;
            //}


            //foreach (var item in _TeachSet.Items)
            //{
            //    gridTeachData.Rows.Add(
            //        item.Category,
            //        item.DisplayName,
            //        item.Keys,
            //        item.Values,
            //        item.Updated.ToString("yyyy-MM-dd HH:mm:ss"),
            //        item.Description,
            //        item.Name);
            //}

            gridTeachData.GroupTemplate.Column = ColumnCategory;
            gridTeachData.Sort(ColumnCategory, ListSortDirection.Ascending);
        }


    }
}

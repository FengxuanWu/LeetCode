using Client.Public;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Client.BasicInfo
{
    /// <summary>
    /// Drug.xaml 的交互逻辑
    /// </summary>
    public partial class DrugInfo : Window
    {
        public DrugInfo()
        {
            InitializeComponent();
            Init();
        }

        private void Init()
        {
            InitData();
            InitEvent();
        }
        private void InitData()
        {
            int page = int.Parse(Page.Text)-1;
            int row = int.Parse(Rows.Text);
            string sql = string.Format("SELECT ID,[批准文号],[产品名称],[英文名称],[商品名],[剂型],[规格],[生产单位],[生产地址],[产品类别],[批准日期],[原批准文号],[药品本位码],[备注],[其他]  FROM [Drug].[dbo].[DrugDic] order by ID offset {0} rows  fetch next {1} rows only",
                page * row, row);
            DataTable dt = SQL.QueryForDataTable(sql);
            datagrid1.ItemsSource = dt.DefaultView;
        }
        private void InitEvent()
        {
            this.NewAdd.Click += NewAdd_Click;
            this.ReFlush.Click += ReFlush_Click;
            this.PrePage.Click += PrePage_Click;
            this.NextPage.Click += NextPage_Click;
            datagrid1.MouseDoubleClick += Datagrid1_MouseDoubleClick;
        }

        private void Datagrid1_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            var a = this.datagrid1.SelectedItem;
            var b = a as DataRowView;

            DataRow dr = b.Row;//微软提供的唯一的转换DataRow
            EditDrug editDrug = new EditDrug((DataRow)dr);
            editDrug.ShowDialog();
        }

        private void NextPage_Click(object sender, RoutedEventArgs e)
        {
            int page = int.Parse(Page.Text) - 1;
            page += 1;
            Page.Text = page.ToString();
            InitData();
        }

        private void PrePage_Click(object sender, RoutedEventArgs e)
        {
            int page = int.Parse(Page.Text) - 1;
            page -= 1;
            if (page <= 0)
                page = 1;
            Page.Text = page.ToString();
            InitData();
        }

        private void ReFlush_Click(object sender, RoutedEventArgs e)
        {
            InitData();
        }

        private void NewAdd_Click(object sender, RoutedEventArgs e)
        {
            EditDrug editDrug = new EditDrug();

            editDrug.ShowDialog();
        }
    }

    public class CommonClass
    {
        public int ID { set; get; }
        public string Name { set; get; }
    }
}

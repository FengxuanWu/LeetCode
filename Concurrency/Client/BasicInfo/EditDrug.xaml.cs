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
    /// EditDrug.xaml 的交互逻辑
    /// </summary>
    public partial class EditDrug : Window
    {
        private readonly int operate;
        private readonly int ID;
        public EditDrug(DataRow dataRow)
        {
            InitializeComponent();
            Init();
            this.operate = 1;
            try
            {
                ID = int.Parse(dataRow["ID"].ToString());
                txt_CPMC.Text = dataRow["产品名称"].ToString();
                txt_PZWH.Text = dataRow["批准文号"].ToString();
                txt_EnglishName.Text = dataRow["英文名称"].ToString();
                txt_SPM.Text = dataRow["商品名"].ToString();
                com_jx.Text = dataRow["剂型"].ToString();
                txt_GG.Text = dataRow["规格"].ToString();
                txt_SCDW.Text = dataRow["生产单位"].ToString();
                txt_SCDZ.Text = dataRow["生产地址"].ToString();
                txt_CPLB.Text = dataRow["产品类别"].ToString();
                txt_PZRQ.Text = dataRow["批准日期"].ToString();
                txt_YPZWH.Text = dataRow["原批准文号"].ToString();
                txt_YPBWM.Text = dataRow["药品本位码"].ToString();
                txt_BZ.Text = dataRow["备注"].ToString();
                txt_QT.Text = dataRow["其他"].ToString();
            }
            catch(Exception ex)
            {
                throw new Exception("运行异常!");
            }
            
        }

        public EditDrug()
        {
            InitializeComponent();
            Init();
            this.operate = 0;
        }

        private void Init()
        {
            this.Save.Click += Save_Click;
            this.Cancle.Click += Cancle_Click;
            InitData();
        }

        private void InitData()
        {
            List<CommonClass> list = new List<CommonClass>();
            list.Add(new CommonClass { ID = 0,Name = "丸剂(水丸)" });
            list.Add(new CommonClass { ID = 1, Name = "片剂" });
            list.Add(new CommonClass { ID = 2, Name = "针剂" });
            list.Add(new CommonClass { ID = 3, Name = "干粉" });
            com_jx.ItemsSource = list;
            com_jx.DisplayMemberPath = "Name";
            com_jx.SelectedValuePath = "ID";

            List<CommonClass> list1 = new List<CommonClass>();
            list1.Add(new CommonClass { ID = 0, Name = "中药" });
            list1.Add(new CommonClass { ID = 1, Name = "西药" });
            list1.Add(new CommonClass { ID = 2, Name = "中成药" });
            list1.Add(new CommonClass { ID = 2, Name = "其他" });
            txt_CPLB.ItemsSource = list;
            txt_CPLB.DisplayMemberPath = "Name";
            txt_CPLB.SelectedValuePath = "ID";
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            string sql;
            if(this.operate == 0)
            {
                sql = string.Format("INSERT INTO [Drug].[dbo].[DrugDic]" +
                    "([批准文号],[产品名称],[英文名称],[商品名],[剂型],[规格],[生产单位]," +
                    "[生产地址],[产品类别],[批准日期],[原批准文号],[药品本位码],[备注],[其他]) VALUES" +
                    "('{0}','{1}','{2}','{3}','{4}','{5}','{6}','{7}','{8}','{9}','{10}','{11}','{12}','{13}')",txt_PZWH.Text,txt_CPMC.Text,
                    txt_EnglishName.Text,txt_SPM.Text,com_jx.Text,txt_GG.Text,txt_SCDW.Text,txt_SCDZ.Text,
                    txt_CPLB.Text,txt_PZRQ.Text,txt_YPZWH.Text,txt_YPBWM.Text,txt_BZ.Text,txt_QT.Text);
            }
            else
            {
                sql = string.Format("UPDATE [Drug].[dbo].[DrugDic] SET [批准文号] = '{0}'," +
                    "[产品名称] = '{1}',[英文名称] = '{2}',[商品名] = '{3}',[剂型] = '{4}',[规格] = '{5}',[生产单位] = '{6}'," +
                    "[生产地址] = '{7}',[产品类别] = '{8}',[批准日期] = '{9}',[原批准文号] ='{10}',[药品本位码] ='{11}'," +
                    "[备注] = '{12}',[其他] = '{13}' WHERE ID = '{14}'", txt_PZWH.Text, txt_CPMC.Text,
                    txt_EnglishName.Text, txt_SPM.Text, com_jx.Text, txt_GG.Text, txt_SCDW.Text, txt_SCDZ.Text,
                    txt_CPLB.Text, txt_PZRQ.Text, txt_YPZWH.Text, txt_YPBWM.Text, txt_QT.Text, txt_BZ.Text,ID);
            }
            bool ans = SQL.InsertAndUpdate(sql);
            if(ans)
            {
                MessageBox.Show("编辑成功!");                
            }
            else
            {
                MessageBox.Show("编辑失败!");
            }
        }

        private void Cancle_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}

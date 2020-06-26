using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Public
{
    public static class SQL
    {
        private static readonly string localCon = "server=127.0.0.1;database=AnyImage;uid=muser;pwd=fa@ligh#";
        public static DataTable QueryForDataTable(string sql)
        {
            SqlConnection con = new SqlConnection
            {
                ConnectionString = localCon
            };
            con.Open();
            SqlCommand com = new SqlCommand();
            com.Connection = con;
            com.CommandType = CommandType.Text;
            com.CommandText = sql;
            SqlDataAdapter adapter = new SqlDataAdapter(com);
            DataTable dt = new DataTable();
            adapter.Fill(dt);
            SqlDataReader dr = com.ExecuteReader();//执行SQL语句
            dr.Close();//关闭执行
            con.Close();
            return dt;
        }

        public static bool InsertAndUpdate(string sql)
        {
            SqlConnection con = new SqlConnection
            {
                ConnectionString = localCon
            };
            con.Open();
            SqlCommand com = new SqlCommand();
            com.Connection = con;
            com.CommandType = CommandType.Text;
            com.CommandText = sql;
            int ans = com.ExecuteNonQuery();
            con.Close();
            return ans > 0;
        }
    }
}

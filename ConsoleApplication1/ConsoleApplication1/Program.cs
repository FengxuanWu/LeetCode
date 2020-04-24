using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Security.Cryptography;
using System.Text;

namespace ConsoleApplication1
{
    class Program
    {
        static String appKey = "wnw";
        static String appSecret = "yyyyyyyssss7ysdfhksdf1";
        static String nonce = createUUid();
        static String timestamp = ((long)(DateTime.Now - new DateTime(1970, 1, 1)).TotalMilliseconds).ToString();

        static String createUUid()
        {
            String res = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
            StringBuilder sb = new StringBuilder();
            Random rand = new Random();
            for (int i = 0; i < res.Length; ++i)
            {
                if (res[i] == 'x' || res[i] == 'y')
                {
                    int r = (int)(rand.NextDouble() * 16);
                    r = res[i] == 'x' ? r : (r & 0x3 | 0x8);
                    sb.Append(r.ToString("X"));
                }
                else
                    sb.Append(res[i]);
            }

            return sb.ToString();
        }

        static string calAes(string data, string Key)
        {
            RijndaelManaged aes = new RijndaelManaged();
            byte[] key = Encoding.Default.GetBytes(Key);
            byte[] d = Encoding.ASCII.GetBytes(data);
            byte[] iv;
            aes.Padding = PaddingMode.PKCS7;
            aes.Mode = CipherMode.ECB;

            using (ICryptoTransform encrypt = aes.CreateEncryptor(key, ))
            {
                byte[] dest = encrypt.TransformFinalBlock(d, 0, d.Length);
                encrypt.Dispose();
                return Convert.ToBase64String(dest);
            }
        }

        static string calcMd5(string data)
        {
            MD5 md5 = MD5.Create();
            return Convert.ToBase64String(md5.ComputeHash(Encoding.UTF8.GetBytes(data)));
        }

        static string calSigNature(string data, string key)
        {
            byte[] data_bytes = Encoding.Default.GetBytes(data);
            byte[] key_byte = Encoding.Default.GetBytes(key);
            HMACSHA256 sha256 = new HMACSHA256(key_byte);
            return Convert.ToBase64String(sha256.ComputeHash(data_bytes));
        }

        static Dictionary<String, String> headersToSign(Dictionary<String, String> reqHeaders)
        {
            Dictionary<String, String> headers = new Dictionary<String,String>();

            foreach(KeyValuePair<String, String> key_val in reqHeaders)
            {
                String name = key_val.Key.ToLower();
                if (name == "x-service-id"
                    || name == "x-service-method"
                    || name == "x-ca-timestamp"
                    || name == "x-content-md5"
                    || name == "x-ca-key"
                    || name == "x-ca-nonce")
                {
                    headers.Add(name, reqHeaders[name]);
                }
            }

            headers.Add("x-ca-key", appKey);    
	        headers.Add("x-ca-nonce", nonce);   
	       // headers.Add("x-content-md5",md5);
            headers.Add("x-ca-timestamp", timestamp);

            return headers;
        }

        static void Main(string[] args)
        {
            //Console.Out.WriteLine(nonce);
            //Console.Out.WriteLine(timestamp);
            //Console.Out.WriteLine(calSigNature("Message", appSecret));
            //Console.Out.WriteLine(calcMd5(""));
            Console.Out.WriteLine(calAes("Message", "abc"));
        }
    }
}

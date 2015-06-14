using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CayWG
{
    class TextMessage
    {
        char m;
        char u;
        char r;
        string username;
        string receivername;
        string message;


        public string data;
        public int len;

        public TextMessage(){
            
        }

        public TextMessage(string user, string receiver, string mes)
        {
            setMessage(user, receiver, mes);
        }

        public void setMessage(string user, string receiver, string mes)
        {
            username = user;
            receivername = receiver;
            message = mes;

            m = 'm';
            u = (char)username.Length;
            r = (char)receiver.Length;

            data = "";
            data += m;
            data += u;
            data += r;
            data += user;
            data += receiver;
            data += mes;
            
        }

        public string readData(string rData)
        {
            data = rData;

            m = data[0];
            if (m != 'm')
                return "HATA!!!|n";
            u = data[1];
            r = data[2];

            username = data.Substring(3, (int)u);
            receivername = data.Substring((int)u+3, (int)r);
            message = data.Substring((int)r + (int)u + 3);



            return username+" : "+message;
        }

    }
}

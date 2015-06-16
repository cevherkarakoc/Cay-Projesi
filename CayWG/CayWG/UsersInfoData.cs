using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CayWG
{
    class UsersInfoData
    {
        char u='u';
        string users;
        public string data;

        public string[] GetUsersName()
        {
            return data.Substring(1).Split(',');
        }



    }
}

//GNU GPL 2.0 ile lisanslıdır.
#include <signal.h>
#include <cstdio>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <sstream>
#include <stdlib.h>

using namespace std;

void windowsSocketControl();
void socketCreateControl(int sock);
string IntToString ( int sayi )
{
  ostringstream oss;

  oss<< sayi;
  return oss.str();
}

int main()
{
    int sock,dataSize,port;
    char data[1024], isim[32],mesaj[989], adres[64],bos[1],okuyucu[1024],portS[32],*sockS;
    string tmp_str;
    struct hostent *he;
    struct sockaddr_in server_addr;


    windowsSocketControl();

    cout<<"IP giriniz : ";
    cin.getline(adres,64);
    he = gethostbyname(adres);//Sunucu ip

    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // Soket olusturuldu.
    socketCreateControl(sock); //Soket hata kontrülü
    do{
    cout<<"\Baglanmak istediginiz port numarasini giriniz(1024-12345) : ";
    cin>>portS;
    port = atoi(portS);
    }while(port<1024 || port>12345);


    /*==========Adresleme Başlıyor.==========*/
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr=*((struct in_addr *)he->h_addr);
    server_addr.sin_port=htons(port);
    memset(&(server_addr.sin_zero), '\0', 8);
    /*==========Adresleme Tamamlandı.==========*/

    cin.getline(bos,1);//Cin ardınden gelen getline sorunu için çözüm
    cout<<"Kullanici adinizi giriniz : ";
    cin.getline(isim,32);

    if (connect(sock, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1)
        cout<<"Bir hata oldu."<<endl;

    //tmp_str = IntToString(sock);
    //sockS = (char*)tmp_str.c_str();
    strcpy(okuyucu,"start ./okuyucu.exe ");
    strcat(okuyucu," ");
    strcat(okuyucu,adres);
    strcat(okuyucu," ");
    strcat(okuyucu,portS);
    //strcat(okuyucu," ");
    //strcat(okuyucu,sockS);

    system(okuyucu);

    while(1)
    {
        cin.getline(mesaj,989);

        strcpy(data,isim);
        strcat(data," : ");
        strcat(data,mesaj);
        strcat(data,"\n");

        dataSize = strlen(data);
        send(sock,data,dataSize,0);


    }

    closesocket(sock);
    WSACleanup();
    return 0;

}

void windowsSocketControl()
{
    WSAData version;
    WORD mkword=MAKEWORD(2,2);
    int what=WSAStartup(mkword,&version);
    if(what!=0)
        cout<<"Bu WSA surumu desteklenmiyor! - \n"<<WSAGetLastError()<<endl;
    else
        cout<<"WSA surumu destekleniyor.\n"<<endl;
}

void socketCreateControl(int sock)
{
    if(sock==INVALID_SOCKET)
        cout<<"Soket olusturulken hata oldu!\n";

    else
        cout<<"Soket basari ile olusturuldu.\n";
}

//GNU GPL 2.0 ile lisanslıdır.
#include <signal.h>
#include <cstdio>
#include <iostream>
#include <winsock2.h>

using namespace std;

void windowsSocketControl();
void socketCreateControl(int sock);

int main()
{
    int sock,dataSize,port;
    char data[1024], adres[64];
    struct hostent *he;
    struct sockaddr_in server_addr;

    windowsSocketControl();

    cout<<"IP giriniz : ";
    cin.getline(adres,64);
    he = gethostbyname(adres);//Sunucu ip

    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // Soket olusturuldu.
    socketCreateControl(sock); //Soket hata kontrülü

    do{
    cout<<"\nBaglanmak istediginiz port numarasini giriniz(1024-12345) : ";
    cin>>port;
    }while(port<1024 || port>12345);

    /*==========Adresleme Başlıyor.==========*/
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr=*((struct in_addr *)he->h_addr);
    server_addr.sin_port=htons(port);
    memset(&(server_addr.sin_zero), '\0', 8);
    /*==========Adresleme Tamamlandı.==========*/

    if (connect(sock, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1)
        cout<<"Sunucuya baglanılamadı."<<endl;

    while(1)
    {
        dataSize=recv(sock,data,1024, 0);
        data[dataSize] = '/0';
        cout<<data<<endl;

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

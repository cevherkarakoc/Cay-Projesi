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
    int sin_size,sock,connecter,i,j,gelenData;
    char data[1024];
    fd_set   baglananlar,gecici;
    struct sockaddr_in server_addr,client_addr;

    windowsSocketControl(); //WSA sürüm kontrolü ve hata denetimi

    FD_ZERO(&baglananlar); // Ana kümeyi ve gecici kümeyi temizle
    FD_ZERO(&gecici);


    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // Soket olusturuldu.
    socketCreateControl(sock); //Soket hata kontrülü

    /*==========Adresleme Başlıyor.==========*/
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_port=htons(5000);
    memset(&(server_addr.sin_zero), '\0', 8);
    /*==========Adresleme Tamamlandı.==========*/

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr ))== -1)
    {
        cout<<"Soket ve Sistem baglantısında hata oldu!.\n";
    }
    if (listen(sock, 5) == -1)
    {
        cout<<"Soket dinlemesinde basarisiz oldu!.\n";
    }
    cout<<"\nBir baglanti olusmasi bekleniyor...\n";


    FD_SET(sock, &baglananlar);

    while(1)
    {
        gecici = baglananlar;
        if(select(0, &gecici, NULL, NULL, NULL)==-1)
            cout<<endl<<"Soketler dinlenemiyor!"<<endl;
        i =gecici.fd_array[0];

        if(i == sock)
        {
            sin_size = sizeof(struct sockaddr_in);
            connecter = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
            FD_SET(connecter, &baglananlar);
            cout<<"\nBaglandi : "<<inet_ntoa(client_addr.sin_addr)<<" , "<<ntohs(client_addr.sin_port)<<endl;
        }
        else
        {
            if(gelenData=recv(i,data,sizeof(data),0)<=0)
            {
                if(gelenData ==0)
                    cout<<endl<<"Karşı taraf ile baglanti koptu!"<<endl;
                else
                    cout<<endl<<"Baglanti Hatasi!"<<endl;

                closesocket(i);
                FD_CLR(i, &baglananlar);
            }
            else
            {

                for(j=0; j<baglananlar.fd_count; j++)
                {
                    if(baglananlar.fd_array[j] != sock && baglananlar.fd_array[j] != i)
                    {
                        if(send(baglananlar.fd_array[j],data,sizeof(data),0) <=0){
                            cout<<endl<<"Veri Gonderme Hatasi!"<<endl;
                        }
                    }
                }
                cout<<data;
            }
        }
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

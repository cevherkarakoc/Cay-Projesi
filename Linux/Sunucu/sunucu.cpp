#include "iostream"
#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "sys/select.h"
#include "sys/time.h"
#include "unistd.h"
#include "string.h"
#include "sys/file.h"

using namespace std;

void soketKontrol(int );

int main()
{
    int sock,port,connecter,i,j,gelenData,fdmax;
    socklen_t sin_size;
    char data[1024];
    fd_set baglananlar,gecici;


    struct sockaddr_in server_addr,client_addr;

    FD_ZERO(&baglananlar);
    FD_ZERO(&gecici);
    sock=socket(AF_INET,SOCK_STREAM,0);
    soketKontrol(sock);
    do
    {
        cout <<"\nKullanmak istediginiz port numarasini giriniz(1024-12345) : ";
        cin >>port;
    }
    while(port < 1024 || port >12345);
    //Adreslemeye geciliyor.
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_port=htons(port);
    memset(&(server_addr.sin_zero), '\0', 8);
    //Adresleme tamam...

    if(bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr ))== -1)
    {
        cout<<"Soket ve Sistem baglantısında hata oldu!.\n";
    }
    if (listen(sock, 5) == -1)
    {
        cout<<"Soket dinlemesinde basarisiz oldu!.\n";
    }
    cout<<"\nBir baglanti olusmasi bekleniyor...\n";
    FD_SET(sock, &baglananlar);
    fdmax=sock;
    while(1)
    {

        gecici = baglananlar;

        if(select(fdmax+1, &gecici, NULL , NULL, NULL)==-1)
            cout<<endl<<"Soketler dinlenemiyor!"<<endl;
        for(i=0; i<=fdmax; i++)
        {
            if(FD_ISSET(i,&gecici))
            {

                if(i == sock)
                {
                    sin_size = sizeof(client_addr);
                    connecter = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
                    FD_SET(connecter, &baglananlar);
                    cout<<connecter<<"  "<<sock<<endl;
                    if(connecter>fdmax)
                    {
                        fdmax=connecter;
                    }
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
                        close(i);
                        FD_CLR(i, &baglananlar);
                    }
                    else
                    {
                        for(j=0; j<=fdmax; j++)
                        {
                            if(FD_ISSET(j,&baglananlar))
                            if(j != sock && j != i)
                            {
                                if(send(j,data,sizeof(data),0) <=0)
                                {
                                    cout<<endl<<"Veri Gonderme Hatasi!"<<endl;
                                }
                            }
                        }
                        cout<<data<<endl;
                    }
                }
            }
        }
    }

    return 0;
}
void soketKontrol(int soket)
{

    if(soket==-1)
        cout << "Soket olusumu basarisizdir."<<endl;
    else
        cout <<"Soket olusumu basarilidir."<<endl;

}

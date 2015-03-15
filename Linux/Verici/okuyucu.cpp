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
#include "netdb.h"
using namespace std;

void soketKontrol(int );

int main()
{
int sock,dataSize,port;
char data[1024], adres[64];
struct hostent *he;
struct sockaddr_in server_addr;

cout<<"IP giriniz : ";
cin.getline(adres,64);
he = gethostbyname(adres);//Sunucu ip
sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); // Soket olusturuldu.
soketKontrol(sock); //Soket hata kontrülü
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
close(sock);


return 0;
}
void soketKontrol(int soket)
{

    if(soket==-1)
        cout << "Soket olusumu basarisizdir."<<endl;
    else
        cout <<"Soket olusumu basarilidir."<<endl;

}

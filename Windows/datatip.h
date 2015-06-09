
class TextMessage{

    unsigned char m;
    char userName[32];
    char receiverName[32];
    char message[959];


    public:
    char data[1024];
    int len;
    textMessage(){
        m='m';
    }
    TextMessage(char uN[32],char rN[32], char mes[960]){
        m='m';
        setMessage(uN,rN,mes);
    }
    void setMessage(char uN[32],char rN[32], char mes[960]){
        strcpy(userName,uN);
        strcpy(receiverName,rN);
        strcpy(message,mes);

        data[0]=m;
        data[1]=strlen(userName);
        data[2]=strlen(receiverName);
        int j=3;
        for(int i=0;i<(int)data[1];i++){
            data[j++]=userName[i];
        }
        for(int i=0;i<(int)data[2];i++){
            data[j++]=receiverName[i];
        }
        for(int i=0;i<strlen(message);i++){
            data[j++]=message[i];
        }
        data[j++]='\n';
        data[j]='\0';

        len = 5+(int)data[1]+(int)data[2]+strlen(message);
    }

};

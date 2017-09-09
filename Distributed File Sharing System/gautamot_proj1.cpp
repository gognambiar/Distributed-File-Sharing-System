#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <stdio.h>

  
#define TRUE   1
#define FALSE  0
#define STDIN 1

//----Server Global Objects//
int szls = 0,max_clients = 30,eff,lss,czls = 0,lzls = 0;
char message[200],masteraddr[30];

class iplist
{
public : 
int slno;
char hostname[30];
int portnum;
char ipa[15];

void setvalues(int pt, char *ipad, int s)
{

if(strcmp(ipad, "128.205.36.8") == 0)
{
strcpy(hostname,"timberlake.cse.buffalo.edu");
}

else if(strcmp(ipad, "128.205.36.33") == 0)
{
strcpy(hostname,"highgate.cse.buffalo.edu");
}

else if(strcmp(ipad, "128.205.36.34") == 0)
{
strcpy(hostname,"euston.cse.buffalo.edu");
}

else if(strcmp(ipad, "128.205.36.35") == 0)
{
strcpy(hostname,"embankment.cse.buffalo.edu");
}

else if(strcmp(ipad, "128.205.36.36") == 0)
{
strcpy(hostname,"underground.cse.buffalo.edu");
}

else
{
strcpy(hostname, "sample");
}

slno = s+1;
portnum = pt;
strcpy(ipa, ipad);
//szls = s + 1;
};

void listm()
{
if(strcmp(this->ipa,"-2"))
{
printf("%d \t %s \t %s \t %d \n", slno, hostname, ipa, portnum);
}
};

}serverip[10],clientip[10],listnlist[10];;


void setbuffer()
{
int eff;
char sln[4],ptnumb[30];
message[0] = '\0';
strcat(message,"ACTIVE CONNECTIONS ON THE SERVER\n");
for(eff = 0; eff < szls; eff++)
{
if(strcmp(serverip[eff].ipa,"-2"))
{
sprintf(sln,"%d",serverip[eff].slno);
sprintf(ptnumb, "%d", serverip[eff].portnum);
strcat(message,sln);
strcat(message," ");
strcat(message,serverip[eff].hostname);
strcat(message," ");
strcat(message,serverip[eff].ipa);
strcat(message," ");
strcat(message,ptnumb);
strcat(message,"\n");
}
}
};

//----Server Global Objects//



int master_socket,sockfd,flrg = 0,connectfs[5];
char origpt[20],cblr[300],blr1[200],clno,clipad[40];

void HELP()
{
    printf("The following options are available : \n");
    printf("1. HELP\n");
    printf("2. CREATOR\n");
    printf("3. DISPLAY\n");
    printf("4. REGISTER (Format : REGISTER <IP> <PORTNO>)\n");
    printf("5. CONNECT (Format : CONNECT <IP or HOSTNAME> <PORTNO>)\n");
    printf("6. LIST\n");
    printf("7. TERMINATE (Format : TERMINATE <Peer Connection ID>)\n");
    printf("8. QUIT\n");
    printf("9. GET\n");
    printf("10. PUT\n");
}

void CREATOR ()
{
    printf("NAME : GAUTAM OTHAYOTH GANAPATHYADAN\n");
    printf("UBIT NAME : gautamot\n");
    printf("EMAIL : gautamot@buffalo.edu\n");
}

int DISPLAY(int port1)
{

    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs (&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family==AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            if(strcmp(ifa->ifa_name,"eth0") == 0 || strcmp(ifa->ifa_name,"em2") == 0) 
            printf("Interface: %s\tAddress: %s and port number is %d\n", ifa->ifa_name, addr,port1);
        }
    }

    freeifaddrs(ifap);
    return 0;
}

void storeip()
{

    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs (&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family==AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            if(strcmp(ifa->ifa_name,"eth0") == 0 || strcmp(ifa->ifa_name,"em2") == 0) 
            {
            strcpy(clipad, addr);
            }
        }
    }

    freeifaddrs(ifap);
}


int REGISTER(char *ip, char *port_no)
{
    int portno,n;
    struct sockaddr_in serv_addr;
    char buffer[256];
    struct hostent *server;
    portno = atoi(port_no);

    if(strcmp(ip, "128.205.36.8") == 0)
    {
    server = gethostbyname("timberlake.cse.buffalo.edu"); 
    }    

    else if(strcmp(ip, "0.0.0.0") == 0)
    {
    server = gethostbyname("ubunturos64"); 
    }
     
    else
    {
    printf("Please enter the correct server\n");
    return 0;
    }

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        printf("ERROR opening socket\n");


    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        {printf("ERROR connecting - Invalid Port Number\n"); return 0;}
        strcpy(masteraddr,"128.205.36.8");
    clientip[0].setvalues(portno,masteraddr,0);//correct here
    czls = 1;    
    flrg = 1;
    flrg = 1;
    bzero(buffer,256);
strcpy(buffer,origpt);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         printf("ERROR writing to socket\n");
    return 0;
}

int CONNECT(char *ip, char *port_no, int uuu)
{
int portno,n,uu,hh,flrg =0;
    struct sockaddr_in serv_addr;
    char buffer[256],chk[40],ipstore[40];;
    struct hostent *server;
    portno = atoi(port_no);

    storeip();
    if(strcmp(clipad,ip) == 0)
    {
    printf("Self Connection is not allowed\n");
    return 0;
    }

    if(strstr(cblr, ip) == NULL)
    {
    printf("The Peer is not registered with the server,message : %s,ip : %s\n",message,ip);
    return 0;
    }
    
    for(hh = 1;hh<czls; hh++)
    {
    if(strcmp(clientip[hh].ipa,"-2"))
    {
    if((strcmp(clientip[hh].ipa,ip) == 0) || (strcmp(clientip[hh].hostname,ip) == 0))
    {
    printf("Duplicate Connection is not allowed\n");
    return 0;
    }
    }
    }

    for(hh = 1;hh<lzls; hh++)
    {
    if(strcmp(listnlist[hh].ipa,"-2"))
    {
    if((strcmp(listnlist[hh].ipa,ip) == 0) || (strcmp(listnlist[hh].hostname,ip) == 0))
    {
    printf("Duplicate Connection is not allowed\n");
    return 0;
    }
    }
    }
    

    if(strcmp(ip, "128.205.36.8") == 0 || strcmp(ip, "timberlake.cse.buffalo.edu") == 0)
    {
    printf("Please use REGISTER command to connect to the server\n");
    return 0;
    }    
    
    else if(strcmp(ip, "128.205.36.33") == 0 || strcmp(ip, "highgate.cse.buffalo.edu") == 0)
    {
    if(strcmp(ip, "highgate.cse.buffalo.edu") == 0)
    {
    flrg = 1;strcpy(ipstore,"128.205.36.33");
    }
    server = gethostbyname("highgate.cse.buffalo.edu"); 
    }
    
    else if(strcmp(ip, "128.205.36.34") == 0 || strcmp(ip, "euston.cse.buffalo.edu") == 0)
    {
    if(strcmp(ip, "euston.cse.buffalo.edu") == 0)
    {
    flrg = 1;strcpy(ipstore,"128.205.36.34");
    }
    server = gethostbyname("euston.cse.buffalo.edu"); 
    }    

    else if(strcmp(ip, "128.205.36.35") == 0 || strcmp(ip, "embankment.cse.buffalo.edu") == 0)
    {
    if(strcmp(ip, "embankment.cse.buffalo.edu") == 0)
    {
    flrg = 1;strcpy(ipstore,"128.205.36.35");
    }
    server = gethostbyname("embankment.cse.buffalo.edu"); 
    }
    
    else if(strcmp(ip, "128.205.36.36") == 0 || strcmp(ip, "underground.cse.buffalo.edu") == 0)
    {
    if(strcmp(ip, "underground.cse.buffalo.edu") == 0)
    {
    flrg = 1;strcpy(ipstore,"128.205.36.36");
    }
    server = gethostbyname("underground.cse.buffalo.edu"); 
    }


    else if(strcmp(ip, "0.0.0.0") == 0)
    {
    server = gethostbyname("ubunturos64"); 
    }

    else
    {
    printf("Client doesn't exist, Please try again\n");
    return 0;
    }

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    for (uu = 0; uu < max_clients; uu++) 
    {
      if( connectfs[uu] == 0 )
      {
      connectfs[uu] = socket(AF_INET, SOCK_STREAM, 0);
      if (connectfs[uu] < 0) 
        {printf("ERROR opening socket\n");return 0;}
      break;
      }
    }    

    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(connectfs[uu],(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        {printf("ERROR connecting\n");return 0;}
    printf("Connected to Peer ip %s\n",ip);
    if(flrg == 1)
    {
    listnlist[uu].setvalues(portno,ipstore,uu+4);
    }
    else
    {
    listnlist[uu].setvalues(portno,ip,uu+4);
    }
    if(lzls < uu+1)
    {
    lzls = uu+1;
    }
    bzero(buffer,256);
strcpy(buffer,origpt);
    n = write(connectfs[uu],buffer,strlen(buffer));
    if (n < 0) 
         printf("ERROR writing to socket\n");
    return 0;

}
int main(int argc , char *argv[])
{
if(argv[1][0] == 'c')
{//------------Client Code starts
strcpy(origpt,argv[2]);

struct sockform
{
int fdnum;
int portnum;
char ipa[15];
};
    

struct sockform serverip1[10];

int opt = TRUE,addrlen , new_socket , client_socket[30], activity, i , valread , sd,j,k=9,l=0,m,max_sd,jj,ii,PORT,ss,tt,u=0,ww,n0,n00,jjj,cfs;

    struct sockaddr_in address;
      
    char buffer[1025],buf[25],bfr[25],brr[25],bfrc[50],brrc[50],blr[300];
    fd_set readfds,connfs;
 
    for (i = 0; i < max_clients; i++) 
    {
        client_socket[i] = 0;
    }
      
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
    {
        printf("socket failed");
        exit(EXIT_FAILURE);
    }
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        printf("setsockopt");
        exit(EXIT_FAILURE);
    }
    PORT = atoi(argv[2]);  
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    serverip1[0].fdnum = master_socket; 
    serverip1[0].portnum = ntohs(address.sin_port);
    strcpy(serverip1[0].ipa,inet_ntoa(address.sin_addr));
      
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        printf("bind failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);
     
    if (listen(master_socket, 3) < 0)
    {
        printf("listen");
        exit(EXIT_FAILURE);
    }
     
    addrlen = sizeof(address);
    puts("Waiting for connections ...\n");
    printf("Please enter your option :\n");       
    HELP();
    while(TRUE) 
    {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        FD_SET(STDIN, &readfds);
        
        max_sd = master_socket;
        if(STDIN > max_sd)
{ max_sd = STDIN;
}

if(sockfd > 0)
{
FD_SET(sockfd, &readfds);
}
if(sockfd > max_sd)
{
max_sd = sockfd;
}


        for ( jjj = 0 ; jjj < 3 ; jjj++) 
        {
            cfs = connectfs[jjj];             
            if(cfs > 0)
                FD_SET(cfs , &readfds);
             
            if(cfs > max_sd)
                max_sd = cfs;
        }//close this


        for ( i = 0 ; i < max_clients ; i++) 
        {
            sd = client_socket[i];
             
            if(sd > 0)
                FD_SET( sd , &readfds);
             
            if(sd > max_sd)
                max_sd = sd;
        }
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
    
        if ((activity < 0) && (errno!=EINTR)) 
        {
            printf("select error");
        }
        int cnt;


if(FD_ISSET(STDIN, &readfds)) 
{
fgets(buf,40,stdin);
buf[strlen(buf)-1]='\0';
if(strcmp(buf, "HELP") == 0)
{
HELP();
}
else if(strcmp(buf, "CREATOR") == 0)
{
CREATOR();
}
else if(strcmp(buf, "DISPLAY") == 0)
{
DISPLAY(PORT);
}

else if(strncmp(buf, "REGISTER", 8) == 0)
{
for(jj = 0; buf[9 + jj] != '\0';jj++)
{
if(buf[9 + jj] == ' ')
{
break;
}
bfr[jj] = buf[9 + jj];
}//aa

bfr[jj]='\0';

jj += 10;//int
ii=0;
while(buf[ii] != '\0')
{
brr[ii] = buf[ii+jj];//chr
ii++;
}
brr[ii]='\0';

REGISTER(bfr,brr);

}

else if(strcmp(buf, "LIST") == 0)
{
for(lss = 0; lss < czls; lss++)
{
 clientip[lss].listm();
}
for(lss = 0; lss < lzls; lss++)
{
 listnlist[lss].listm();
}
}

else if(strncmp(buf, "TERMINATE", 9) == 0)
{
if(buf[10] == '1')
{
printf("You can't terminate the server\n");
}
char nos[10],mgdis[20];
for(lss = 0; lss < czls; lss++)
{
sprintf(nos,"%d",clientip[lss].slno);
printf("buffer is %c, nos is %c, czls is %d\n",buf[10],nos[0],czls);
if(buf[10] == nos[0])
{
strcpy(clientip[lss].ipa,"-2");
sd = client_socket[lss-1];
printf("Disconnecting Peer\n");
strcpy(mgdis,"Peer Disconnected Remotely\n");
if(send(client_socket[lss-1], mgdis, strlen(mgdis), 0) != strlen(mgdis) ) 
{
perror("send");
}
u--;
close(sd);
client_socket[lss-1] = 0;
break;
}
}

for(lss = 0; lss < lzls; lss++)
{
char nos1[10];
sprintf(nos1,"%d",listnlist[lss].slno);
if(buf[10] == nos1[0])
{
strcpy(listnlist[lss].ipa,"-2");
cfs = connectfs[lss];
printf("Disconnecting Peer\n");
u--;
close(cfs);
connectfs[lss] = 0;
break;
}
}
}




else if(strncmp(buf, "CONNECT", 7) == 0)
{
if(u<3)
{for(ss = 0; buf[8 + ss] != '\0';ss++)
{
if(buf[8 + ss] == ' ')
{
break;
}
bfrc[ss] = buf[8 + ss];
}//aa

bfrc[ss]='\0';

ss += 9;//int
tt=0;
while(buf[tt] != '\0')
{
brrc[tt] = buf[tt+ss];//chr
tt++;
}
brrc[tt]='\0';
CONNECT(bfrc,brrc,u);
u++;
}
else
{
printf("Maximum number of connections reached\n");
}
}

else if(strcmp(buf, "QUIT") == 0)
{
n00 = write(sockfd,buf,strlen(buf));
if (n00 < 0) 
printf("ERROR writing to socket");
}

else
{
printf("Enter a correct option according to the list of commands given in CAPS\n");
}

printf("Please enter your option :\n");
}

        if (FD_ISSET(master_socket, &readfds)) {
if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                printf("accept");
                exit(EXIT_FAILURE);
            }
            printf("New connection , ip is : %s\n" ,inet_ntoa(address.sin_addr));
            int n1,n2;char bur[50];
            bzero(bur,256);
            n1 = read(new_socket,bur,255);
            if (n1 < 0) printf("ERROR reading from socket");
            
            printf("New connection,ip is : %s\n",inet_ntoa(address.sin_addr));
            
            n2 = atoi(bur);  
               
            for (i = 0; i < max_clients; i++) 
            {
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    clientip[i+1].setvalues(n2,inet_ntoa(address.sin_addr),i+1);
                    printf("----------------------\n");
                    for(eff = 0; eff <= i+1; eff++)
                    {
                    clientip[eff].listm();
                    }
                    if(czls < eff)
                    {
                    czls = eff;
                    }
                    printf("Adding to list of sockets as %d\n" , i);
                    break;
                }
            }
	    	    
        }
         

if (FD_ISSET(sockfd, &readfds))
{
int n;
    bzero(blr,256);
    n = read(sockfd,blr,255);
    if (n < 0) 
         {printf("ERROR reading from socket\n");break;}
    if(n == 0)
    {
    for ( jjj = 0 ; jjj < 3 ; jjj++)
    {
    cfs = connectfs[jjj];
    if(cfs > 0)
    {
    close(cfs);
    connectfs[jjj] = 0;
    }
    }
    close(sockfd);
    break;
    }
    printf("%s\n",blr);
    strcpy(cblr,blr);
}




for ( jjj = 0 ; jjj < 3 ; jjj++)
{
cfs = connectfs[jjj];
if (FD_ISSET(cfs, &readfds))
{
int n11;
    bzero(blr1,256);
    n11 = read(cfs,blr1,255);
    printf("%s",blr1);
    if (n11 < 0) 
         {printf("ERROR reading from socket\n");break;}
    if(n11 == 0)
    {
    close(cfs);
    connectfs[jjj] = 0;
    strcpy(listnlist[jjj].ipa,"-2");
    break;
    }
    //printf("%s\n",blr);
}
}//close this


        for (i = 0; i < max_clients; i++) 
        {
            sd = client_socket[i];
              
            if (FD_ISSET( sd , &readfds)) 
            {
                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s\n" , inet_ntoa(address.sin_addr));
                    int fee;
                    for(fee = 0; fee < czls; fee++)
                    {
                    if(strcmp(inet_ntoa(address.sin_addr), clientip[fee].ipa) == 0)
                    {
                    strcpy(clientip[fee].ipa,"-2");
                    }
                    }
                    close( sd );
                    client_socket[i] = 0;
                    
                }
                 
                else
                {
                    buffer[valread] = '\0';
                    send(sd , buffer , strlen(buffer) , 0 );
                }
            }
        }
    }
     
}//----------------Client Code ends

//-----------------Server code starts
else if(argv[1][0] == 's')
{

int opt = TRUE,master_socket , addrlen , new_socket , client_socket[30], activity, i , valread , sd,j,k =9,l = 0,m,max_sd,eff,kk,fee,effd,PORT;
    struct sockaddr_in address;
      
    char buffer[1025],buf[25],prtn[30],ptnumb[30], sln[4],slchar[4],msgdis[100];
    fd_set readfds,connfs;
 
    for (i = 0; i < max_clients; i++) 
    {
        client_socket[i] = 0;
    }
      
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0) 
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
  
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    PORT = atoi(argv[2]);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    strcpy(masteraddr,"128.205.36.8");
    serverip[0].setvalues(ntohs(address.sin_port),masteraddr,0);//correct here
    szls = 1;  
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);
     
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
     
    addrlen = sizeof(address);
    puts("Waiting for connections ...");
    printf("Please enter your option :\nPlease note that you can enter only HELP, CREATOR, DISPLAY AND QUIT for the server\n");
    HELP();
    while(TRUE) 
    {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        FD_SET(STDIN, &readfds);
        max_sd = master_socket;
if(STDIN > max_sd)
{ max_sd = STDIN;
}


        for ( i = 0 ; i < max_clients ; i++) 
        {
            sd = client_socket[i];
             
            if(sd > 0)
                FD_SET( sd , &readfds);
             
            if(sd > max_sd)
                max_sd = sd;
        }
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
    
        if ((activity < 0) && (errno!=EINTR)) 
        {
            printf("select error");
        }

if(FD_ISSET(STDIN, &readfds)) 
{
fgets(buf,40,stdin);
buf[strlen(buf)-1]='\0';
if(strcmp(buf, "HELP") == 0)
{
HELP();
}
else if(strcmp(buf, "CREATOR") == 0)
{
CREATOR();
}
else if(strcmp(buf, "DISPLAY") == 0)
{
DISPLAY(PORT);
}

else if(strcmp(buf, "QUIT") == 0)
{
int nkk;
printf("Quitting Server\n");
setbuffer();
for (nkk = 0; nkk < max_clients; nkk++) 
        {
         if(client_socket[nkk] > 0)
         {
         if( send(client_socket[nkk], message, strlen(message), 0) != strlen(message) ) 
         {
                perror("send");
         }
         }
        }
  close(master_socket);
  for (nkk = 0; nkk < max_clients; nkk++) 
  {
  sd = client_socket[nkk];
  close(sd);
  }
  exit(0);

}
else
{
printf("Enter a valid option from the list of commands, type HELP to get the List of commands\n");
}
printf("Please enter your option :\n");
}


        if (FD_ISSET(master_socket, &readfds)) {
if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            int n1,n2;char bur[50];
            bzero(bur,256);
            n1 = read(new_socket,bur,255);
            if (n1 < 0) printf("ERROR reading from socket");
            
            printf("New connection,ip is : %s\n",inet_ntoa(address.sin_addr));
            
            n2 = atoi(bur);  
              
            for (i = 0; i < max_clients; i++) 
            {
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    serverip[i+1].setvalues(n2,inet_ntoa(address.sin_addr),i+1);
                    printf("----------------------\n");
                    for(eff = 0; eff <= i+1; eff++)
                    {
                    serverip[eff].listm();
                    }
                    if(szls < eff)
                    {
                    szls = eff;
                    }
                    break;
                }

            }
            
            setbuffer();
        for (kk = 0; kk < max_clients; kk++) 
        {
         if(client_socket[kk] > 0)
         {
         if( send(client_socket[kk], message, strlen(message), 0) != strlen(message) ) 
         {
                perror("send");
         }
         }
        }         
        }
         


        for (i = 0; i < max_clients; i++) 
        {
            sd = client_socket[i];
              
            if (FD_ISSET( sd , &readfds)) 
            {
                valread = read( sd , buffer, 1024);
                if (valread == 0)
                {
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    
                    for(fee = 0; fee <= szls; fee++)
                    {
                    if(strcmp(inet_ntoa(address.sin_addr), serverip[fee].ipa) == 0)
                    {
                    strcpy(serverip[fee].ipa,"-2");
                    }
                    }
                    close( sd );
                    client_socket[i] = 0;
           
                    setbuffer();
			for (kk = 0; kk < max_clients; kk++) 
			{
			 if(client_socket[kk] > 0)
			 {
			 if( send(client_socket[kk], message, strlen(message), 0) != strlen(message) ) 
			 {
				perror("send");
			 }
			 }
			}   
              }
                        

                else if(strncmp(buffer, "TERMINATE", 9) == 0)
                {   
                    for(effd = 0; effd < szls; effd++)
                    {
                    sprintf(slchar,"%d",serverip[effd].slno);
                    if(buffer[10] == slchar[0])                    
                    {
                    strcpy(serverip[effd].ipa,"-2");
                    sd = client_socket[effd-1];
                    strcpy(msgdis,"Client has been remotely disconnected\n");
                    if(send(client_socket[effd-1], msgdis, strlen(msgdis), 0) != strlen(msgdis) ) 
	            {
		    perror("send");
		    }
                    close(sd);
                    client_socket[effd-1] = 0;
                    break;
                    }
                    }
                    setbuffer();
		    for (kk = 0; kk < max_clients; kk++) 
		    {
	            if(client_socket[kk] > 0)
	            {
		    if( send(client_socket[kk], message, strlen(message), 0) != strlen(message) ) 
	            {
		    perror("send");
		    }
		    }
		    }  
                }
                
                else if(strncmp(buffer, "QUIT", 4) == 0)
                {
                close( sd );
                client_socket[i] = 0;
                strcpy(serverip[i+1].ipa,"-2");
                setbuffer();
		    for (kk = 0; kk < max_clients; kk++) 
		    {
		    if(client_socket[kk] > 0)
		    {
		    if( send(client_socket[kk], message, strlen(message), 0) != strlen(message) ) 
		    {
		    perror("send");
		    }
		    }
		    }
                }
                else
                {
                
                }
            }
        }
    }

}
//--------------------------Server code ends
else
{
printf("Please enter the correct format: <program> <c or s for client or server> <portnumber>\n");
}
    return 0;
} 




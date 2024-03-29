#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "tipo.h"
//#define msg mensagem


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    struct mensagem msg;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

char cidades[43][20]={"0","san francisco"/*1*/,"portland"/*2*/,"seatle"/*3*/,"los angeles"/*4*/,"san diego"/*5*/,"palm springs"/*7*/ //cidades 1 a 7 noroeste
                        ,"grand canyon"/*8*/,"lake tahoe"/*9*/,"boise"/*10*/,"yellowstone"/*11*///cidades 8 a 11 noroeste
                        ,"denver"/*12*/,"colorado springs"/*13*/,"aspem"/*14*/,"vail"/*15*/,"salt lake city"/*16*/,"las vegas"/*17*/,"phoenix"/*18*/,"albuquerque"/*19*///cidades 12 a 19 nordeste
                        ,"san antonio"/*20*/,"dallas"/*21*/,"st louis"/*22*/,"houston"/*23*/,"nova orleans"/*24*///cidades 20 a 24 nordeste
                        ,"miami"/*25*/,"fort lauderdale"/*26*/,"orlando"/*27*/,"atlanta","memphis","little rock"/*28*/,"kansas city"/*29*/,"minneapolis"/*30*/,"omaha"/*31*///cidades 25 a 31 sudoeste
                        ,"milwaukee"/*32*/,"chicago"/*33*/,"detroit"/*34*/,"indianapolis"/*35*/,"richmond"/*36*/,"washington"/*37*/,"nova york"/*38*/,//cidades 32 a 38 sudeste
                        "boston"/*39*/,"albany"/*40*/,"nashville"/*41*///cidades 39 a 42
                        };
int grafo[43][43] = {
                                        { 0,   1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,   34,   35,   36,   37,   38,   39,   40,  41,  42},
            /*1 = "SAN FRANCISCO"*/     { 1,   0,  640,    0,  380,    0,    0,    0,  300,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*2 = "PORTLAND"*/          { 2, 640,    0,  170,    0,    0,    0,    0,    0,  420,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*3 = "SEATLE"*/            { 3,   0,  170,    0,    0,    0,    0,    0,    0,  500,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*4 = "LOS ANGELES"*/       { 4, 380,    0,    0,    0,  120,  160,    0,    0,    0,    0,    0,    0,    0,    0,    0,  270,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*5 = "SAN DIEGO"*/         { 5,   0,    0,    0,  120,    0,  140,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  350,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*6 = "PALM SPRINGS"*/      { 6,   0,    0,    0,  160,  140,    0,  440,  780,    0,    0,    0,    0,    0,    0,    0,  290,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*7 = "GRAND CANYON"*/      { 7,   0,    0,    0,    0,    0,  440,    0,    0,    0,    0,    0,    0,    0,    0,    0,  470,  360,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*8 = "LAKE TAHOE"*/        { 8, 300,  580,    0,    0,    0,  780,    0,    0,  420,    0,    0,    0,    0,    0,  520,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*9 = "BOISE"*/             { 9,   0,  420,  500,    0,    0,    0,    0,  420,    0,  670,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*10 = "YELLOWSTONE"*/      { 10,  0,    0,    0,    0,    0,    0,    0,    0,  670,    0,  930,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 1340,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*11 = "DENVER"*/           { 11,  0,    0,    0,    0,    0,    0,    0,    0,    0,  930,    0,  120,  170,  160,  530,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  540,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*12 = "COLORADO SPRINGS"*/ { 12,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  120,    0,  180,    0,    0,    0,    0,    0,    0,  730,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*13 = "ASPEM"*/            { 13,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  170,  180,    0,   80,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*14 = "VAIL"*/             { 14,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  160,    0,   80,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*15 = "SALT LAKE CITY"*/   { 15,  0,    0,    0,    0,    0,    0,    0,  520,    0,    0,  530,    0,    0,    0,    0,  420,  660,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*16 = "LAS VEGAS"*/        { 16,  0,    0,    0,  270,    0,  290,  470,    0,    0,    0,    0,    0,    0,    0,  420,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*17 = "PHOENIX"*/          { 17,  0,    0,    0,    0,  350,    0,  360,    0,    0,    0,    0,    0,    0,    0,  660,    0,    0,  350,  990, 1070,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*18 = "ALBUQUERQUE"*/      { 18,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*19 = "SAN ANTONIO"*/      { 19,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  990,    0,    0,  280,    0,  310,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*20 = "DALLAS"*/           { 20,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  730,    0,    0,    0,    0, 1070,    0,  280,    0,    0,  250,    0,    0,    0,    0,  790,    0,  320,  550,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*21 = "ST LOUIS"*/         { 21,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  290,  400,  250,    0,    0,    0,  300,    0,  250,    0,    0,    0,    0,    0,   0},
            /*22 = "HOUSTON"*/          { 22,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  310,  250,    0,    0,  530,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*23 = "NOVA ORLEANS"*/     { 23,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  530,    0,  860,    0,  640,  470,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*24 = "MIAMI"*/            { 24,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  860,    0,   30,  230,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*25 = "FORT LAUDERDALE"*/  { 25,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   30,    0,  180,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*26 = "ORLANDO"*/          { 26,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  640,  230,  180,    0,  440,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*27 = "ATLANTA"*/          { 27,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  790,    0,    0,  470,    0,    0,  440,    0,  390,    0,    0,    0,    0,    0,    0,    0,    0,  560,    0,    0,    0,    0, 240},
            /*28 = "MEMPHIS"*/          { 28,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  290,    0,    0,    0,    0,    0,  390,    0,  140,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 210},
            /*29 = "LITTLE ROCK"*/      { 29,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  320,  400,    0,    0,    0,    0,    0,    0,  140,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*30 = "KANSAS CITY"*/      { 30,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  550,  250,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  190,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*31 = "MINNEAPOLIS"*/      { 31,  0,    0,    0,    0,    0,    0,    0,    0,    0, 1340,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  380,  340,  410,    0,    0,    0,    0,    0,    0,    0,   0},
            /*32 = "OMAHA"*/            { 32,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  540,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  190,  380,    0,    0,  470,    0,    0,    0,    0,    0,    0,    0,   0},
            /*33 = "MILWAUKEE"*/        { 33,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  340,    0,    0,   90,    0,    0,    0,    0,    0,    0,    0,   0},
            /*34 = "CHICAGO"*/          { 34,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  300,    0,    0,    0,    0,    0,    0,    0,    0,    0,  410,  470,   90,    0,  280,  180,    0,  700,    0,    0,    0,   0},
            /*35 = "DETROIT"*/          { 35,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  280,    0,    0,    0,  530,  640,    0,  650,   0},
            /*36 = "INDIANAPOLIS"*/     { 36,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  250,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  180,    0,    0,    0,  590,    0,    0,    0, 290},
            /*37 = "RICHMOND"*/         { 37,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  560,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  200,    0,    0,    0, 710},
            /*38 = "WASHINGTON"*/       { 38,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  700,  530,  590,  200,    0,  240,    0,    0,   0},
            /*39 = "NOVA YORK"*/        { 39,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  640,    0,    0,  240,    0,  210,  150,   0},
            /*40 = "BOSTON"*/           { 40,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  210,    0,  170,   0},
            /*41 = "ALBANY"*/           { 41,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  650,    0,    0,    0,  150,  170,    0,   0},
            /*42 = "NASHVILLE"*/        { 42,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0}};


	int flag=0;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) error("ERROR connecting");

    printf("ID --- Cidades  \n");
    for(int i=1;i<43;i++){
        if(i!=18) printf("%d --- %s\n",i,cidades[i]);
    }
    do{
        printf("\n1 - De cidade para outra \n2 - Tour pelo EUA\n3 - Sair\nOp: ");
        scanf("%d",&msg.escolha);
        if(msg.escolha==1)flag=1;
        else if(msg.escolha==2)flag=1;
        else if(msg.escolha==3)exit(0);
    }while(flag==0);

    printf("Cidade inicial: ");
    scanf("%d",&msg.in);
    fflush(stdin);

    if(msg.escolha==2) msg.out=msg.in;

    else if(msg.escolha==1){
        printf("Cidade Final: ");
        scanf("%d",&msg.out);
    }
    printf("-----------------LOADING BEST ROUTE-------------------\n");

    n = write(sockfd,(char*)&msg,sizeof msg);

    if (n < 0) error("ERROR writing to socket");
    //bzero(msg,sizeof msg);

    n = read(sockfd,(char*)&msg,5000);
    if (n < 0) error("ERROR reading from socket");

    int i=1;
    printf("%s - %s - (%d km)\n",cidades[msg.caminho_min[0]],cidades[msg.caminho_min[1]],grafo[msg.caminho_min[0]][msg.caminho_min[1]]);

    while(msg.caminho_min[i]!=msg.out){
        printf("%s - %s - (%d km)\n",cidades[msg.caminho_min[i]],cidades[msg.caminho_min[i+1]],grafo[msg.caminho_min[i]][msg.caminho_min[i+1]]);
        i++;
    }

    printf("\n custo: %d\n",msg.custo_min);

    close(sockfd);
    return 0;
}   
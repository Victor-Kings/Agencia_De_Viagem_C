
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "tipo.h"

using namespace std;


struct caminho
{
    int caminho[43]={0};
    int custo;
};
typedef struct caminho stack_element;
#include "stackld-1.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{

char cidades[43][20]={"0","san francisco"/*1*/,"portland"/*2*/,"seatle"/*3*/,"los angeles"/*4*/,"san diego"/*5*/,"palm springs"/*7*/ //cidades 1 a 7 noroeste
                        ,"grand canyon"/*8*/,"lake tahoe"/*9*/,"boise"/*10*/,"yellowstone"/*11*///cidades 8 a 11 noroeste
                        ,"denver"/*12*/,"colorado springs"/*13*/,"aspem"/*14*/,"vail"/*15*/,"salt lake city"/*16*/,"las vegas"/*17*/,"phoenix"/*18*/,"albuquerque"/*19*///cidades 12 a 19 nordeste
                        ,"san antonio"/*20*/,"dallas"/*21*/,"st louis"/*22*/,"houston"/*23*/,"nova orleans"/*24*///cidades 20 a 24 nordeste
                        ,"miami"/*25*/,"fort lauderdale"/*26*/,"orlando"/*27*/,"atlanta","memphis","little rock"/*28*/,"kansas city"/*29*/,"minneapolis"/*30*/,"omaha"/*31*///cidades 25 a 31 sudoeste
                        ,"milwaukee"/*32*/,"chicago"/*33*/,"detroit"/*34*/,"indianapolis"/*35*/,"richmond"/*36*/,"washington"/*37*/,"nova york"/*38*/,//cidades 32 a 38 sudeste
                        "boston"/*39*/,"albany"/*40*/,"nashville"/*41*///cidades 39 a 42
                        };


int grafo[43][43] = {
                                        { 0,   1,    2,    3,    4,    5,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,   33,   34,   35,   36,   37,   38,   39,   40,   41,  42},
            /*0 = "SAN FRANCISCO"*/     { 1,   0,  640,    0,  380,    0,    0,    0,  300,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*1 = "PORTLAND"*/          { 2, 640,    0,  170,    0,    0,    0,    0,  580,  420,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*2 = "SEATLE"*/            { 3,   0,  170,    0,    0,    0,    0,    0,    0,  500,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*3 = "LOS ANGELES"*/       { 4, 380,    0,    0,    0,  120,  160,    0,    0,    0,    0,    0,    0,    0,    0,    0,  270,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*4 = "SAN DIEGO"*/         { 5,   0,    0,    0,  120,    0,  140,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  350,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*5 = "PALM SPRINGS"*/      { 6,   0,    0,    0,  160,  140,    0,  440,  780,    0,    0,    0,    0,    0,    0,    0,  290,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*6 = "GRAND CANYON"*/      { 7,   0,    0,    0,    0,    0,  440,    0,    0,    0,    0,    0,    0,    0,    0,    0,  470,  360,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*7 = "LAKE TAHOE"*/        { 8, 300,  580,    0,    0,    0,  780,    0,    0,  420,    0,    0,    0,    0,    0,  520,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*8 = "BOISE"*/             { 9,   0,  420,  500,    0,    0,    0,    0,  420,    0,  670,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*9 = "YELLOWSTONE"*/       { 10,  0,    0,    0,    0,    0,    0,    0,    0,  670,    0,  930,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 1340,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*10 = "DENVER"*/           { 11,  0,    0,    0,    0,    0,    0,    0,    0,    0,  930,    0,  120,  170,  160,  530,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  540,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*11 = "COLORADO SPRINGS"*/ { 12,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  120,    0,  180,    0,    0,    0,    0,    0,    0,  730,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*12 = "ASPEM"*/            { 13,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  170,  180,    0,   80,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*13 = "VAIL"*/             { 14,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  160,    0,   80,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*14 = "SALT LAKE CITY"*/   { 15,  0,    0,    0,    0,    0,    0,    0,  520,    0,    0,  530,    0,    0,    0,    0,  420,  660,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*15 = "LAS VEGAS"*/        { 16,  0,    0,    0,  270,    0,  290,  470,    0,    0,    0,    0,    0,    0,    0,  420,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*16 = "PHOENIX"*/          { 17,  0,    0,    0,    0,  350,    0,  360,    0,    0,    0,    0,    0,    0,    0,  660,    0,    0,  350,  990, 1070,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*17 = "ALBUQUERQUE"*/      { 18,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*18 = "SAN ANTONIO"*/      { 19,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  990,    0,    0,  280,    0,  310,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*19 = "DALLAS"*/           { 20,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  730,    0,    0,    0,    0, 1070,    0,  280,    0,    0,  250,    0,    0,    0,    0,  790,    0,  320,  550,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*20 = "ST LOUIS"*/         { 21,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  290,  400,  250,    0,    0,    0,  300,    0,  250,    0,    0,    0,    0,    0,   0},
            /*21 = "HOUSTON"*/          { 22,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  310,  250,    0,    0,  530,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*22 = "NOVA ORLEANS"*/     { 23,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  530,    0,  860,    0,  640,  470,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*23 = "MIAMI"*/            { 24,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  860,    0,   30,  230,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*24 = "FORT LAUDERDALE"*/  { 25,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   30,    0,  180,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*25 = "ORLANDO"*/          { 26,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  640,  230,  180,    0,  440,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*26 = "ATLANTA"*/          { 27,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  790,    0,    0,  470,    0,    0,  440,    0,  390,    0,    0,    0,    0,    0,    0,    0,    0,  560,    0,    0,    0,    0, 240},
            /*27 = "MEMPHIS"*/          { 28,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  290,    0,    0,    0,    0,    0,  390,    0,  140,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 210},
            /*28 = "LITTLE ROCK"*/      { 29,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  320,  400,    0,    0,    0,    0,    0,    0,  140,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*29 = "KANSAS CITY"*/      { 30,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  550,  250,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  190,    0,    0,    0,    0,    0,    0,    0,    0,    0,   0},
            /*30 = "MINNEAPOLIS"*/      { 31,  0,    0,    0,    0,    0,    0,    0,    0,    0, 1340,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  380,  340,  410,    0,    0,    0,    0,    0,    0,    0,   0},
            /*31 = "OMAHA"*/            { 32,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  540,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  190,  380,    0,    0,  470,    0,    0,    0,    0,    0,    0,    0,   0},
            /*32 = "MILWAUKEE"*/        { 33,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  340,    0,    0,   90,    0,    0,    0,    0,    0,    0,    0,   0},
            /*33 = "CHICAGO"*/          { 34,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  300,    0,    0,    0,    0,    0,    0,    0,    0,    0,  410,  470,   90,    0,  280,  180,    0,  700,    0,    0,    0,   0},
            /*34 = "DETROIT"*/          { 35,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  280,    0,    0,    0,  530,  640,    0,  650,   0},
            /*35 = "INDIANAPOLIS"*/     { 36,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  250,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  180,    0,    0,    0,  590,    0,    0,    0, 290},
            /*36 = "RICHMOND"*/         { 37,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  560,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  200,    0,    0,    0, 710},
            /*37 = "WASHINGTON"*/       { 38,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  700,  530,  590,  200,    0,  240,    0,    0,   0},
            /*38 = "NOVA YORK"*/        { 39,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  640,    0,    0,  240,    0,  210,  150,   0},
            /*39 = "BOSTON"*/           { 40,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  210,    0,  170,   0},
            /*40 = "ALBANY"*/           { 41,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  650,    0,    0,    0,  150,  170,    0,   0},
            /*41 = "NASHVILLE"*/        { 42,  0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  240,  210,    0,    0,    0,    0,    0,    0,    0,  290,  710,    0,    0,    0,    0,   0}};




    int custo_min=99999,i,j,k,g=0,flag=0,flagesc=0,escolha=0;
    int caminho_min[42]={0},caminho_res[42]={0};
    int entrada,saida,custo_res;
    int m=0;

    Stack p;
    initStack(p);
    stack_element x;

    int sockfd, newsockfd, portno,aux;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
    struct mensagem msg;

    //socket---------------------
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

    // bzero(msg,sizeof msg);
     n = read(newsockfd,(int*)&msg,sizeof msg);
     if (n < 0) error("ERROR reading from socket");
    //spcket -----------------------------

    entrada=msg.in;
     if(msg.escolha==2){
        saida=msg.in;
    }else if(msg.escolha==1){
        saida=msg.out;
    }
     
     printf("\n\n -----LOADING-----\n");
     //entrada=aux;

     x.caminho[0]=entrada;
     x.custo=0;
     push(p,x);
    flag=0;

  while(!isEmpty(p))
     {
        m=0;
        x=pop(p);
        i=0;
        while(x.caminho[i]!=0)i++;

        /*if(x.caminho[i-1]==entrada&&i>35){ */
        if(escolha==1){
            if(x.caminho[i-1]==saida){
                if(x.custo<custo_min){
                    m=0;

                    custo_min=x.custo;
                    while(x.caminho[m]!=0){
                        caminho_min[m]=x.caminho[m];
                        m++;
                    }
                }
            }else flagesc =1;
        }else{
            if(x.caminho[i-1]==entrada&&i==42){ //if(x.caminho[i-1]==saida){
                if(x.custo<custo_min){
                    m=0;
                    custo_min=x.custo;
                    while(x.caminho[m]!=0){
                        caminho_min[m]=x.caminho[m];
                        m++;
                    }
                    break;
                }
            }else flagesc=1;
        }

         if(flagesc==1){
             j=1;
             while(x.caminho[i-1]!=grafo[j][0])j++;

             for(k=1;k<43;k++){

                 if(grafo[j][k]!=0){
                    custo_res=x.custo;
                    m=0;
                    g=0;

                    if(escolha==1){
                        while(x.caminho[g]!=0){
                                if(x.caminho[g]==grafo[0][k])flag =1;
                             g++;
                        }
                    }else{
                         if(grafo[0][k]==entrada&&i==41) flag=0;
                            else{
                                while(x.caminho[g]!=0){
                                        if(x.caminho[g]==grafo[0][k])flag =1;
                                     g++;
                                }
                             }

                    }

                    if(flag==0){
                     x.custo+=grafo[j][k];
                     x.caminho[i]=grafo[0][k];

                     if(custo_min>x.custo)
                     push(p,x);


                     x.custo=custo_res;
                     m=0;
                    }
                    flag=0;
                 }
             }
         }
        flagesc=0;
     }

/*
//----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
*/  

    i=1;

    msg.caminho_min[i-1]=caminho_min[0];
    printf("%s - %s - (%d km)\n",cidades[caminho_min[0]],cidades[caminho_min[1]],grafo[caminho_min[0]][caminho_min[1]]);

    while(caminho_min[i]!=saida){
        msg.caminho_min[i]=caminho_min[i];
        printf("%s - %s - (%d km)\n",cidades[caminho_min[i]],cidades[caminho_min[i+1]],grafo[caminho_min[i]][caminho_min[i+1]]);
        i++;
    }
    msg.caminho_min[i]=caminho_min[i];
    msg.custo_min=custo_min;
    printf("\n custo: %d i=%d\n",custo_min,i);

    n = write(newsockfd,(int*)&msg,5000);
    if (n < 0) error("ERROR writing to socket");
    close(newsockfd);
    close(sockfd);


    return 0;
}

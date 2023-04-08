#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int P;
    int D_entos;  //domi omadas
    int D_ektos;
    char name[50];
    char country[50];
}team;

int lc(FILE* ptr); //orismos synartisis line counter

int main(){
    team *t;
    int N,i=0;
    char filename[50];
    FILE* file;
    printf("Doste to onoma toy arxeioy: ");//eisagogi arxeiou
    scanf("%s",filename);
    file=fopen(filename,"r");
    if(file==NULL){
        printf("Problhma sto anoigma toy arxeioy");//elegxos arxeiou
        return 0;
    }
    N=lc(file); //poso omadon
    t=(team*)malloc(sizeof(team)*N+1); //ekxorisi pinaka domon
    if(t==NULL){
        printf("Problhma stin ekxorisi pinaka");
        return 0;
    }
    while(i!=N){
        fscanf(file,"%s %s %d %d",t[i].name,t[i].country,t[i].D_entos,t[i].D_ektos);
        i++;    //gemisma pinaka domon
    }
    free(t);
    return 0;
}
int lc(FILE* ptr){
    int counter=0,den,dek;
    char country[50],name[50];
    for(;!feof(ptr);counter++){
        fscanf(ptr,"%s %s %d %d",name,country,&den,&dek);
    }
    return counter;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int P;
    int D_entos;  //domi omadas
    int D_ektos;
    int passive_score;
    int active_score;
    int points;
    char name[50];
    char country[50];
}team;

int lc(FILE* ptr); //orismos synartisis line counter

int main(){
    team *t;
    int N,i=0,j,s1,s2,s;
    char filename[50];
    FILE* file;
    printf("Doste to onoma toy arxeioy: ");//eisagogi arxeiou
    scanf("%s",filename);
    file=fopen(filename,"r");
    if(file==NULL){
        printf("Problhma sto anoigma toy arxeioy");//elegxos arxeiou
        return 0;
    }
    N=lc(file);//poso omadon
    rewind(file);
    t=(team*)malloc(sizeof(team)*N+1); //ekxorisi pinaka domon
    if(t==NULL){
        printf("Problhma stin ekxorisi pinaka");
        return 0;
    }
    srand(time(NULL)); //arxikopoiisi fitrou
    while(i!=N){
        fscanf(file,"%s %s %d %d",t[i].name,t[i].country,t[i].D_entos,t[i].D_ektos);
        (t+i)->P=(t+i)->D_entos/10;
        (t+i)->points=0;
        i++;    //gemisma pinaka domon
    }
    for(i=0;i<N;i++){
        for(j=N-1;j>0;j--){
            if(i!=j){ 
                if(strcmp((t+i)->country,(t+j)->country)==0){
                    s1=50+rand()%(1+((t+i)->D_entos)/2)+2*((t+i)->P);
                    s2=50+rand()%(1+((t+j)->D_entos)/2)+2*((t+j)->P);
                    if(s1>s2){
                        if((t+i)->P==0)
                            (t+i)->P+=2;
                        else
                            (t+i)->P++;
                    }
                    else if(s1<s2){
                        if((t+j)->P==0)
                            (t+j)->P+=2;
                        else
                            (t+j)->P++;
                    }
                    else{
                        s=rand()%2;
                        if(s==1){
                            if((t+j)->P==0)
                                (t+j)->P+=2;
                            else
                                (t+j)->P++;
                        }
                        else{
                            if((t+i)->P==0)
                                (t+i)->P+=2;
                            else
                                (t+i)->P++;
                        }
                    }
                }
                else{
                    s1=50+rand()%(1+((t+i)->D_entos)/2)+2*((t+i)->P);
                    s2=50+rand()%(1+((t+j)->D_ektos)/2)+2*((t+j)->P);
                }
            }
        }
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

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

int lc(FILE* ptr); //orisma synartisis line counter
int pv(int x); //orisma synartisis psychology victory
int pl(int y); //orisma synartisis psychology loss
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
        (t+i)->passive_score=0;
        (t+i)->active_score=0;
        i++;    //gemisma pinaka domon
    }
    for(i=0;i<N;i++){
        for(j=0;j>N;j++){
            if(i!=j){ 
                if(strcmp((t+i)->country,(t+j)->country)==0){
                    s1=50+rand()%(1+((t+i)->D_entos)/2)+2*((t+i)->P);
                    s2=50+rand()%(1+((t+j)->D_entos)/2)+2*((t+j)->P);
                    if(s1>s2){
                        (t+i)->P=pv((t+i)->P);
                        (t+j)->P=pl((t+j)->P);
                        (t+i)->points+=2;
                        (t+j)->points++;
                        (t+i)->active_score+=s1;
                        (t+j)->passive_score+=s1;
                    }
                    else if(s1<s2){
                        (t+j)->P=pv((t+j)->P);
                        (t+i)->P=pl((t+i)->P);
                        (t+j)->points+=2;
                        (t+i)->points++;
                        (t+j)->active_score+=s2;
                        (t+i)->passive_score+=s2;
                    }
                    else{
                        s=rand()%2;
                        if(s==1){
                            (t+j)->P=pv((t+j)->P);
                            (t+i)->P=pl((t+i)->P);
                        }
                        else{
                            (t+i)->P=pv((t+i)->P);
                            (t+j)->P=pl((t+j)->P);
                        }
                    }
                }
                else{
                    s1=50+rand()%(1+((t+i)->D_entos)/2)+2*((t+i)->P);
                    s2=50+rand()%(1+((t+j)->D_ektos)/2)+2*((t+j)->P);
                    if(s1>s2){
                        (t+i)->P=pv((t+i)->P);
                        (t+j)->P=pl((t+j)->P);
                    }
                    else if(s1<s2){
                        (t+j)->P=pv((t+j)->P);
                        (t+i)->P=pl((t+i)->P);
                    }
                    else{
                        s=rand()%2;
                        if(s==1){
                            (t+j)->P=pv((t+j)->P);
                            (t+i)->P=pl((t+i)->P);
                        }
                        else{
                            (t+i)->P=pv((t+i)->P);
                            (t+j)->P=pl((t+j)->P);
                        }
                    }
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
int pv(int x){
    if(x==0){
        x+=2;
    }
    else{
        x++;
    }
    return x;
}
int pl(int y){
    if(y>0){
        y--;
    }
    return y;
}

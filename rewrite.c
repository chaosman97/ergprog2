#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
int pv(int x); //synartisi psychology victory
int pl(int y); //synartisi psychology loss
void score(int *z,int *w); //synartisi score
int main(){
char filename[50];
FILE* fp;
team *t,temp;
int counter=0,den,dek,i=0,j,s1,s2,s;
char country[50],name[50];
printf("Dose onoma arxeiou: ");
scanf("%s",filename);
fp=fopen(filename,"r");
if(fp==NULL){
printf("Problhma fopen");
return 0;
}
for(;!feof(fp);counter++){
    fscanf(fp,"%s %s %d %d",name,country,&den,&dek);
    //printf("%s %s %d %d\n",name,country,den,dek);
}
fclose(fp);
//printf("%d",counter);
t=(team*)malloc(sizeof(team)*counter);
if(t==NULL){
	printf("problhma malloc");
	return 0;
}
fp=fopen(filename,"r");
if(fp==NULL){
	printf("problhma fopen");
	return 0;
}
srand(time(NULL)); //arxikopoiisi fitrou
while(i<counter){
    fscanf(fp,"%s %s %d %d",name,country,&den,&dek);
    strcpy(t[i].name,name);
    strcpy(t[i].country,country);
    t[i].D_entos=den;
    t[i].D_ektos=dek;
    t[i].P=t[i].D_entos/10;
    t[i].points=0;
    t[i].passive_score=0;
    t[i].active_score=0;
    //printf("%s\t%s\t%d\t%d\n",t[i].name,t[i].country,t[i].D_entos,t[i].D_ektos);
    i++;    //gemisma pinaka domon
}
for(i=0;i<counter;i++){
        for(j=0;j>counter;j++){
            if(i!=j){ 
                if(strcmp(t[i].country,t[j].country)==0){
                    s1=50+rand()%(1+(t[i].D_entos)/2)+2*(t[i].P);
                    s2=50+rand()%(1+(t[j].D_entos)/2)+2*(t[j].P);
                    if(s1>s2){
                        t[i].P=pv(t[i].P);
                        t[j].P=pl(t[j].P);
                        t[i].points+=2;
                        t[j].points++;
                        t[i].active_score+=s1;
                        t[j].passive_score+=s1;
                        score(&t[i].points,&t[j].points);
                    }
                    else if(s1<s2){
                        t[j].P=pv(t[j].P);
                        t[i].P=pl(t[i].P);
                        t[j].points+=2;
                        t[i].points++;
                        t[j].active_score+=s2;
                        t[i].passive_score+=s2;
                        score(&t[j].points,&t[i].points);
                    }
                    else{
                        s=rand()%2;
                        if(s==1){
                            t[j].P=pv(t[j].P);
                            t[i].P=pl(t[i].P);
                            t[j].points++;
                        }
                        else{
                            t[i].P=pv(t[i].P);
                            t[j].P=pl(t[j].P);
                            t[i].points++;
                        }
                    }
                }
                else{
                    s1=50+rand()%(1+(t[i].D_entos)/2)+2*(t[i].P);
                    s2=50+rand()%(1+(t[j].D_ektos)/2)+2*(t[j].P);
                    if(s1>s2){
                        t[i].P=pv(t[i].P);
                        t[j].P=pl(t[j].P);
                        score(&t[i].points,&t[j].points);
                    }
                    else if(s1<s2){
                        t[j].P=pv(t[j].P);
                        t[i].P=pl(t[i].P);
                        score(&t[j].points,&t[i].points);
                    }
                    else{
                        s=rand()%2;
                        if(s==1){
                            t[j].P=pv(t[j].P);
                            t[i].P=pl(t[i].P);
                            t[j].points++;
                        }
                        else{
                            t[i].P=pv(t[i].P);
                            t[j].P=pl(t[j].P);
                            t[i].points++;
                        }
                    }
                }
            }
        }
    }
    for(i=0;i<=counter-1;i++){
        for(j=counter-2;j>i;j--){
            if(t[j-1].points<t[j].points){
                memcpy(&temp,&t[j-1],sizeof(team));
                memcpy(&t[j-1],&t[j],sizeof(team));
                memcpy(&t[j],&temp,sizeof(team));
            }
            if(t[j-1].points==t[j].points){
                if(((t[j-1].active_score)-(t[j-1].passive_score))<((t[j].active_score)-(t[j].passive_score))){
                memcpy(&temp,&t[j-1],sizeof(team));
                memcpy(&t[j-1],&t[j],sizeof(team));
                memcpy(&t[j],&temp,sizeof(team));
                }
            }
        }
    }
    for(i=0;i<8;i++){
        printf("%s %d %d %d %d\n",t[i].name,t[i].points,t[i].active_score,t[i].passive_score,(t[i].active_score)-(t[i].passive_score));
    }
    printf("<==================================================>\n");
    for(i=8;i<counter;i++){
        printf("%s %d %d %d %d\n",t[i].name,t[i].points,t[i].active_score,t[i].passive_score,((t[i].active_score)-(t[i].passive_score)));
    }
    fclose(fp);
    free(t);
return 0;
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
    if(y>0 && y<10){
        y--;
    }
    if(y==10){
        y-=2;
    }
    return y;
}
void score(int *z,int *w){
    //first the winner then the loser
    *z+=2;
    *w++;
}

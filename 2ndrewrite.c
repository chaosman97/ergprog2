#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct team{
int P;
char country[50];
char name[50];
int D_entos;
int D_ektos;
int victories;
int losses;
int passive_score;
int active_score;
int points;
}team;

int main(){
char filename[50];
FILE *fp,*fapotel;
team *t,temp,tmp[4];
int counter=0,den,dek,i=0,j,sg,sf,overt=1,c=0;
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
    t[i].losses=0;
    t[i].victories=0;
    t[i].passive_score=0;
    t[i].active_score=0;
    //printf("%s\t%s\t%d\t%d\n",t[i].name,t[i].country,t[i].D_entos,t[i].D_ektos);
    i++;    //gemisma pinaka domon
}
for (i=0;i<counter;i++){
    //printf("Buffered: %s %s %d %d\n",t[i].name,t[i].country,t[i].D_entos,t[i].D_ektos);
    t[i].P=(t[i].D_entos+5)/10;
}
fclose(fp);//kleisimo arxeiou
printf("Doste onoma arxeiou apotelesmaton: ");
scanf("%s",filename);
fapotel=fopen(filename,"w");
if(fapotel==NULL){
    printf("problhma fopen");
    return 0;
}
fprintf(fapotel,"ROUND 1\n");//start of round 1
for(i=0;i<counter;i++){
    for(j=0;j<counter;j++){
        if(i==j){continue;}
        if(strcmp(t[i].country,t[j].country)==0){
            //sg : score gypedouxou ->i sf: score filoksenoumenou -> j
            sg=50+rand( )%(1+t[i].D_entos/2) + 2*t[i].P;
            sf=50+rand( )%(1+t[i].D_entos/2) + 2*t[i].P;
        }
        else{
            sg=50+rand( )%(1+t[i].D_entos/2) + 2*t[i].P;
            sf=50+rand( )%(1+t[i].D_ektos/2) + 2*t[i].P;
        }
        if(sf==sg){
            if(rand()%2==0){
                sg++;
            }
            else{
                sf++;
            }
            overt=1;
        }
        else if(sg>sf){
            t[i].victories++;
            t[j].losses++;
            if(t[i].P==10){;}
            else if(t[i].P==0){
                t[i].P=2;
            }
            else{
                t[i].P++;
            }
            if(t[j].P==10){
                t[j].P=8;
            }
            else if(t[j].P==0){;}
            else{
                t[j].P--;
            }
        }
        else{
            t[j].victories++;
            t[i].losses++;
            if(t[j].P==10){;}
            else if(t[j].P==0){
                t[j].P=2;
            }
            else{
                t[j].P++;
            }
            if(t[i].P==10){
                t[i].P=8;
            }
            else if(t[i].P==0){;}
            else{
                t[i].P--;
            }
        }
        t[i].active_score+=sg;
        t[i].passive_score+=sf;
        t[j].active_score+=sf;
        t[j].passive_score+=sg;
        fprintf(fapotel,"\n %s - %s : %d - %d",t[i].name,t[j].name,sg,sf);
        if(overt==1){fprintf(fapotel,"\tOT");}
        overt=0;        
    }
}
for(i=0;i<counter;i++){
    t[i].points=(t[i].victories)*2+(t[i].losses)*1; //counting points
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
    printf("round 1 results\n");
    for(i=0;i<8;i++){
        printf("%d : %s %d %d %d %d\n",i+1,t[i].name,t[i].points,t[i].active_score,t[i].passive_score,(t[i].active_score)-(t[i].passive_score));
    }
    printf("<==================================================>\n");
    for(i=8;i<counter;i++){
        printf("%d : %s %d %d %d %d\n",i+1,t[i].name,t[i].points,t[i].active_score,t[i].passive_score,((t[i].active_score)-(t[i].passive_score)));
    }
    //end of round 1
    //start of round 2
    fprintf(fapotel,"\nROUND 2");
    printf("round 2 results");
    for(i=0;i<4;i++,j=8-i){
        if(strcmp(t[i].country,t[j].country)==0){
            //sg : score gypedouxou ->i sf: score filoksenoumenou -> j
            sg=50+rand( )%(1+t[i].D_entos/2) + 2*t[i].P;
            sf=50+rand( )%(1+t[i].D_entos/2) + 2*t[i].P;
        }
        else{
            sg=50+rand( )%(1+t[i].D_entos/2) + 2*t[i].P;
            sf=50+rand( )%(1+t[i].D_ektos/2) + 2*t[i].P;
        }
        if(sf==sg){
            if(rand()%2==0){
                sg++;
                memcpy(&tmp[c],&t[i],sizeof(team));
                c++;
            }
            else{
                sf++;
                memcpy(&tmp[c],&t[j],sizeof(team));
                c++;
            }
            overt=1;
        }
        else if(sg>sf){
            t[i].victories++;
            t[j].losses++;
            memcpy(&tmp[c],&t[i],sizeof(team));
            c++;
            if(t[i].P==10){;}
            else if(t[i].P==0){
                t[i].P=2;
            }
            else{
                t[i].P++;
            }
            if(t[j].P==10){
                t[j].P=8;
            }
            else if(t[j].P==0){;}
            else{
                t[j].P--;
            }
        }
        else{
            t[j].victories++;
            t[i].losses++;
            memcpy(&tmp[c],&t[i],sizeof(team));
            c++;
            if(t[j].P==10){;}
            else if(t[j].P==0){
                t[j].P=2;
            }
            else{
                t[j].P++;
            }
            if(t[i].P==10){
                t[i].P=8;
            }
            else if(t[i].P==0){;}
            else{
                t[i].P--;
            }
        }
        t[i].active_score+=sg;
        t[i].passive_score+=sf;
        t[j].active_score+=sf;
        t[j].passive_score+=sg;
        fprintf(fapotel,"\n %s - %s : %d - %d",t[i].name,t[j].name,sg,sf);
        printf("\n %s - %s : %d - %d",t[i].name,t[j].name,sg,sf);
        if(overt==1){
        fprintf(fapotel,"\tOT");
        printf("\tOT");}
        overt=0;  
    }
    printf("\n");
for(i=0;i<counter;i++){
    t[i].points=(t[i].victories)*2+(t[i].losses)*1; //counting points
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
//end of round 2
fclose(fapotel);
free(t);
return 0;
}//main end
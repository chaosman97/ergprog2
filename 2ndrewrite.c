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
int ff_vict;
}team;

int main(){
char filename[50];
FILE *fp,*fapotel;
team *t,temp,ff[4];
int counter=0,den,dek,i=0,j,h,sg,sf,overt=1,c=0;
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
    t[i].ff_vict=0;
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
            sf=50+rand( )%(1+t[j].D_entos/2) + 2*t[j].P;
        }
        else{
            sg=50+rand( )%(1+t[i].D_entos/2) + 2*t[i].P;
            sf=50+rand( )%(1+t[j].D_ektos/2) + 2*t[j].P;
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
        for(h=0;h<5;h++){
        if(strcmp(t[i].country,t[j].country)==0){
            //sg : score gypedouxou ->i sf: score filoksenoumenou -> j
            sg=50+rand( )%(1+t[i].D_entos/2) + 2*t[i].P;
            sf=50+rand( )%(1+t[j].D_entos/2) + 2*t[j].P;
        }
        else{
            sg=50+rand( )%(1+t[i].D_entos/2) + 2*t[i].P;
            sf=50+rand( )%(1+t[j].D_ektos/2) + 2*t[j].P;
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
            t[i].ff_vict++;
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
            t[j].ff_vict++;
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
        printf("\n %s - %s : %d - %d",t[i].name,t[j].name,sg,sf);
        if(overt==1){
        fprintf(fapotel,"\tOT");
        printf("\tOT");}
        overt=0;
        if(t[i].ff_vict==3){
            memcpy(&ff[c],&t[i],sizeof(team));
            c++;
            break;}
        else if(t[j].ff_vict==3){
            memcpy(&ff[c],&t[j],sizeof(team));
            c++;
            break;
        } 
    }
}
    c=0;
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
    //for(i=0;i<4;i++){
    //    printf("%s\n",ff[i].name);
    //}

//end of round 2
//start of ff
printf("Doste xora pou tha ginei to ff: ");
scanf("%s",country);
fprintf(fapotel,"\nFINAL FOUR");
for(i=0;i<2;i++){
    j=i+2;
if(strcmp(ff[i].country,country)==0&&strcmp(ff[j].country,country)!=0){
            //sg : score gypedouxou ->i sf: score filoksenoumenou -> j
            sg=50+rand( )%(1+ff[i].D_entos/2) + 2*ff[i].P;
            sf=50+rand( )%(1+ff[j].D_ektos/2) + 2*ff[j].P;
        }
        else if (strcmp(ff[j].country,country)==0&&strcmp(ff[i].country,country)!=0){
            sg=50+rand( )%(1+ff[i].D_ektos/2) + 2*ff[i].P;
            sf=50+rand( )%(1+ff[j].D_entos/2) + 2*ff[j].P;
        }
        else if(strcmp(ff[i].country,country)==0&&strcmp(ff[j].country,country)==0){
          sg=50+rand( )%(1+ff[i].D_entos/2) + 2*ff[i].P;
          sf=50+rand( )%(1+ff[j].D_entos/2) + 2*ff[j].P;
        }
        else{
            sg=50+rand( )%(1+ff[i].D_ektos/2) + 2*ff[i].P;
            sf=50+rand( )%(1+ff[j].D_ektos/2) + 2*ff[j].P;
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
            ff[i].victories++;
            ff[i].ff_vict++;
            ff[j].losses++;
            if(ff[i].P==10){;}
            else if(ff[i].P==0){
                ff[i].P=2;
            }
            else{
                ff[i].P++;
            }
            if(ff[j].P==10){
                ff[j].P=8;
            }
            else if(ff[j].P==0){;}
            else{
                ff[j].P--;
            }
        }
        else{
            ff[j].victories++;
            ff[j].ff_vict++;
            ff[i].losses++;
            if(ff[j].P==10){;}
            else if(ff[j].P==0){
                ff[j].P=2;
            }
            else{
                ff[j].P++;
            }
            if(ff[i].P==10){
                ff[i].P=8;
            }
            else if(ff[i].P==0){;}
            else{
                ff[i].P--;
            }
        }
        ff[i].active_score+=sg;
        ff[i].passive_score+=sf;
        ff[j].active_score+=sf;
        ff[j].passive_score+=sg;
        fprintf(fapotel,"\n %s - %s : %d - %d",ff[i].name,ff[j].name,sg,sf);
        printf("\n %s - %s : %d - %d",ff[i].name,ff[j].name,sg,sf);
        if(overt==1){
        fprintf(fapotel,"\tOT");
        printf("\tOT");}
        overt=0;
        if(ff[i].ff_vict>=4){
            memcpy(&temp,&ff[i],sizeof(team));
            memcpy(&ff[i],&ff[c],sizeof(team));
            memcpy(&ff[c],&temp,sizeof(team));
            c++;
        }
        else if(ff[j].ff_vict>=4){
            memcpy(&temp,&ff[j],sizeof(team));
            memcpy(&ff[j],&ff[c],sizeof(team));
            memcpy(&ff[c],&temp,sizeof(team));
            c++;
        }
}
c=0;
//for(i=0;i<4;i++){
//    printf("\n%s\n",ff[i].name);
//}
//end of ff
//start of semifinal
fprintf(fapotel,"\nSEMIFINAL");
printf("\nsemifinal");
if(strcmp(ff[2].country,country)==0&&strcmp(ff[3].country,country)!=0){
            //sg : score gypedouxou ->i sf: score filoksenoumenou -> j
            sg=50+rand( )%(1+ff[2].D_entos/2) + 2*ff[2].P;
            sf=50+rand( )%(1+ff[3].D_ektos/2) + 2*ff[3].P;
        }
        else if (strcmp(ff[3].country,country)==0&&strcmp(ff[2].country,country)!=0){
            sg=50+rand( )%(1+ff[2].D_ektos/2) + 2*ff[2].P;
            sf=50+rand( )%(1+ff[3].D_entos/2) + 2*ff[3].P;
        }
        else if(strcmp(ff[2].country,country)==0&&strcmp(ff[3].country,country)==0){
          sg=50+rand( )%(1+ff[2].D_entos/2) + 2*ff[2].P;
          sf=50+rand( )%(1+ff[3].D_entos/2) + 2*ff[3].P;
        }
        else{
            sg=50+rand( )%(1+ff[2].D_ektos/2) + 2*ff[2].P;
            sf=50+rand( )%(1+ff[3].D_ektos/2) + 2*ff[3].P;
        }
        if(sf==sg){
            if(rand()%2==0){
                sg++;
            }
            else{
                sf++;
		memcpy(&temp,&ff[3],sizeof(team));
		memcpy(&ff[3],&ff[2],sizeof(team));
		memcpy(&ff[2],&temp,sizeof(team));
            }
            overt=1;
        }
        else if(sg>sf){
            ff[2].victories++;
            ff[3].losses++;
            if(ff[2].P==10){;}
            else if(ff[2].P==0){
                ff[2].P=2;
            }
            else{
                ff[2].P++;
            }
            if(ff[3].P==10){
                ff[3].P=8;
            }
            else if(ff[3].P==0){;}
            else{
                ff[3].P--;
            }
        }
        else{
            ff[3].victories++;
            ff[2].losses++;
            if(ff[3].P==10){;}
            else if(ff[3].P==0){
                ff[3].P=2;
            }
            else{
                ff[3].P++;
            }
            if(ff[2].P==10){
                ff[2].P=8;
            }
            else if(ff[2].P==0){;}
            else{
                ff[2].P--;
            }
            memcpy(&temp,&ff[3],sizeof(team));
            memcpy(&ff[3],&ff[2],sizeof(team));
            memcpy(&ff[2],&temp,sizeof(team));
        }
        ff[2].active_score+=sg;
        ff[2].passive_score+=sf;
        ff[3].active_score+=sf;
        ff[3].passive_score+=sg;
        fprintf(fapotel,"\n %s - %s : %d - %d",ff[2].name,ff[3].name,sg,sf);
        printf("\n %s - %s : %d - %d",ff[2].name,ff[3].name,sg,sf);
        if(overt==1){
        fprintf(fapotel,"\tOT");
        printf("\tOT");}
        overt=0;
//end of semifinal
//start of final
fprintf(fapotel,"\nFINAL ROUND");
printf("\nfinal round");
if(strcmp(ff[0].country,country)==0&&strcmp(ff[1].country,country)!=0){
            //sg : score gypedouxou ->i sf: score filoksenoumenou -> j
            sg=50+rand( )%(1+ff[0].D_entos/2) + 2*ff[0].P;
            sf=50+rand( )%(1+ff[1].D_ektos/2) + 2*ff[1].P;
        }
        else if (strcmp(ff[1].country,country)==0&&strcmp(ff[0].country,country)!=0){
            sg=50+rand( )%(1+ff[0].D_ektos/2) + 2*ff[0].P;
            sf=50+rand( )%(1+ff[1].D_entos/2) + 2*ff[1].P;
        }
        else if(strcmp(ff[0].country,country)==0&&strcmp(ff[1].country,country)==0){
          sg=50+rand( )%(1+ff[0].D_entos/2) + 2*ff[0].P;
          sf=50+rand( )%(1+ff[1].D_entos/2) + 2*ff[1].P;
        }
        else{
            sg=50+rand( )%(1+ff[0].D_ektos/2) + 2*ff[0].P;
            sf=50+rand( )%(1+ff[1].D_ektos/2) + 2*ff[1].P;
        }
        if(sf==sg){
            if(rand()%2==0){
                sg++;
            }
            else{
                sf++;
		memcpy(&temp,&ff[1],sizeof(team));
		memcpy(&ff[1],&ff[0],sizeof(team));
		memcpy(&ff[0],&temp,sizeof(team));
            }
            overt=1;
        }
        else if(sg>sf){
            ff[0].victories++;
            ff[1].losses++;
            if(ff[0].P==10){;}
            else if(ff[0].P==0){
                ff[0].P=2;
            }
            else{
                ff[0].P++;
            }
            if(ff[j].P==10){
                ff[1].P=8;
            }
            else if(ff[1].P==0){;}
            else{
                ff[1].P--;
            }
        }
        else{
            ff[1].victories++;
            ff[0].losses++;
            if(ff[1].P==10){;}
            else if(ff[1].P==0){
                ff[1].P=2;
            }
            else{
                ff[1].P++;
            }
            if(ff[0].P==10){
                ff[0].P=8;
            }
            else if(ff[0].P==0){;}
            else{
                ff[0].P--;
            }
            memcpy(&temp,&ff[1],sizeof(team));
            memcpy(&ff[1],&ff[0],sizeof(team));
            memcpy(&ff[0],&temp,sizeof(team));
        }
        ff[0].active_score+=sg;
        ff[0].passive_score+=sf;
        ff[1].active_score+=sf;
        ff[1].passive_score+=sg;
        fprintf(fapotel,"\n %s - %s : %d - %d",ff[0].name,ff[1].name,sg,sf);
        printf("\n %s - %s : %d - %d",ff[0].name,ff[1].name,sg,sf);
        if(overt==1){
        fprintf(fapotel,"\tOT");
        printf("\tOT");}
        overt=0;
//end of final
//start of printing phase
printf("\nFINAL RESULTS");
for(i=0;i<4;i++){
    printf("\n%d: %s",i+1,ff[i].name);
}
//end of printing phase
fclose(fapotel);
free(t);
return 0;
}//main end

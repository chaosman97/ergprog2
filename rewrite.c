#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
char filename[50];
FILE* fp;
printf("Dose onoma arxeiou: ");
scanf("%s",filename);
fp=fopen(filename,"r");
if(fp==NULL){
printf("Problhma fopen");
return 0;
}
fclose(fp);
return 0;
}

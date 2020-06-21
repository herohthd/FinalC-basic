 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "tree.h"
long long randomz(long long minN, long long maxN){
    return minN + rand() % (maxN + 1 - minN);
}
char* itoa(long long i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}
char *generateName(char first[][10],char middle[][10]){
    char *rs = (char *)malloc(20*sizeof(char));
    int f,m;
    f = rand() % 12;
    m = rand() % 12;
    strcpy(rs,first[f]);
    strcat(rs,middle[m]);
    rs[strlen(rs)] = (char) randomz(65,65+7);
    return rs;
}
long long generateBalance(){
    return randomz(100000,10000000000);
}

int main(){
    char first_name[12][10]= {"Tran ","Nguyen ","Trinh ","Ta ","Dao ","Hoang ","Le ","Ly ","Vu ","Phan ","Dang ","Ngo "};
    char mid[12][10] = {"Van ","Ha ","Nguyet ","Nhat ","Bao ","Bach ","Bich ","Chi ","Diem ","Dieu ","Gia ","Ha "};
    tree head = NULL;
    FILE *fout = fopen("bank.db","w+");
    srand((int)time(0));
    long long r;
    for(int i = 0; i < 1000; ++i){
        char str[13]="\0";
        r = randomz(900000000,1000000000-1);
        //printf("%lld ",r);
        char sdt[13];
        itoa(r,str);
        strcpy( sdt,"0");
        strcat( sdt,str );
        //printf("%s \n",sdt);
        char *name = generateName(first_name,mid);
        //printf("%s \n",name);
        long long balance = generateBalance();
        //printf("%lld \n",balance);
        keyvalue n = createData(name,sdt,balance);
        insert(&head,n);
    }
    traversal(head,fout); 
    fclose(fout);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "bank.h"

tree read_db(FILE *fin){
    tree head = NULL;
    int num;
    fscanf(fin,"%d\n", &num);
    for(int i= 0 ; i < num ; i++){
        char name[25],tel[25];
        long long balance;
        fgets(name,25,fin);
        name[strlen(name)-1]='\0';
        fgets(tel,25,fin);
        tel[strlen(tel)-1]='\0';
        fscanf(fin,"%lld\n", &balance);
        insert(&head,createData(name,tel,balance));
    }
    return head;
}
int countPhone(tree node,keyvalue x){
    int rs = -1;
    for(int i = 0 ; i < node->total ; i++){
        if(strcmp(node->Account[i].telephone,x->telephone) == 0){
             rs = i;
             break;
        }
    }
    return rs;
}
int checkDuplicate(tree node,keyvalue x){
    for(int i = 0 ; i < node->total ;i++){
        if(strcmp(node->Account[i].name,x->name) == 0 && strcmp(node->Account[i].telephone,x->telephone) == 0)
            return 1;
    }
    return 0;
}
void printData(tree root){
    printf("%-25s%-25s%s\n","Name","Telephone","Balance");
    traversal(root);
}
void exportData(tree root,FILE *fout,int *times){
    if (root == NULL) return;
    exportData(root->left,fout,times);
    exportAccount(root,fout,times);
    exportData(root->right,fout,times);
}
void exportAccount(tree t,FILE *fout,int *times){
    for(int i = 0 ; i < t->total ; i++){
      if(times == 0) fprintf(fout,"%s\n%s\n%lld",t->Account[i].name,t->Account[i].telephone,t->Account[i].balance);
      else fprintf(fout,"\n%s\n%s\n%lld",t->Account[i].name,t->Account[i].telephone,t->Account[i].balance);
      (*times) += 1;
    }
}
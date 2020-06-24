#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "tree.h"
#include "bank.h"
#include<stdio_ext.h>

int main(){
    tree root = createTree();
    int choice;
    do{
        printf("1.Import Data\n2.Adding new information\n3.Searching\n4.Tranfer Money\n5.Delete Account by Name\n6.Exporting Data\n");
        scanf("%d",&choice);
        switch (choice){
            case 1:
                printf("Importing....\n");
                FILE *fin = fopen("bank.db","r+");
                root = read_db(fin);
                printData(root);
            break;
            case 2:
                printf("Enter the information\n");
                char name[25],telephone[25];
                long long balance;
                __fpurge(stdin);
                printf("Name: ");
                scanf("%[^\n]s",name);
                printf("Telephone: ");
                __fpurge(stdin);
                scanf("%[^\n]s",telephone);
                printf("Balance: ");
                __fpurge(stdin);
                scanf("%lld",&balance);
                keyvalue x = createData(name,telephone,balance);
                tree node = search(root,x);
                if(node != NULL){
                    if(checkDuplicate(node,x)){
                        printf("Duplicate Error\n");
                        continue;
                    }else{
                        insert(&root,x);
                    }
                }
                else{
                    insert(&root,x);
                }
                printData(root);
            break;
            case 3:
                __fpurge(stdin);
                printf("Name: ");
                scanf("%[^\n]s",name);
                node = search(root,createData(name,telephone,balance));
                if(node == NULL){
                    printf("Not found!!\n");
                    continue;
                }else{
                    if(node->total > 1){
                        __fpurge(stdin);
                        printf("Enter the telephone number\n");
                        scanf("%[^\n]",telephone);
                        int index = countPhone(node,createData(name,telephone,balance));
                        if(index == -1){
                            printf("Incorrect telephone number\n");
                            continue;
                        }else{
                            printf("%-25s%-25s%s\n","Name","Telephone","Balance");
                            printf("%-25s%-25s%lld\n",node->Account[index].name,node->Account[index].telephone,node->Account[index].balance);
                        }
                    }else{
                        int index = 0;
                        printf("%-25s%-25s%s\n","Name","Telephone","Balance");
                        printf("%-25s%-25s%lld\n",node->Account[index].name,node->Account[index].telephone,node->Account[index].balance);
                    }
                }
            break;
            case 4:
                printf("Tranfering Money:\n");
                tree first,second;
                int index1 = 0;
                int index2 = 0;
                NameError1:
                    printf("Enter the name of first account\n");
                    char first_account_name[25];
                    __fpurge(stdin);
                    scanf("%[^\n]s",first_account_name);
                    first = search(root,createData(first_account_name,telephone,balance));
                    if(first == NULL) goto NameError1;
                    if(first->total > 1){
                        TelephoneError1:
                            __fpurge(stdin);
                            printf("Enter the telephone\n");
                            scanf("%[^\n]s",telephone);
                            index1 = countPhone(first,createData(first_account_name,telephone,balance));
                            if(index1 == -1) goto TelephoneError1;
                    }
                NameError2:
                    printf("Enter the name of second account\n");
                    char second_account_name[25];
                    __fpurge(stdin);
                    scanf("%[^\n]s",second_account_name);
                    second = search(root,createData(second_account_name,telephone,balance));
                    if(second == NULL) goto NameError1;
                    if(second->total > 1){
                        TelephoneError2:
                            __fpurge(stdin);
                            printf("Enter the telephone\n");
                            scanf("%[^\n]s",telephone);
                            index2 = countPhone(second,createData(second_account_name,telephone,balance));
                            if(index2 == -1) goto TelephoneError2;
                    }
                __fpurge(stdin);
                long long money;
                do{
                    printf("Enter the number of money you want to tranfer\n");
                    scanf("%lld",&money);
                }while(money > first->Account[index1].balance);
                first->Account[index1].balance -= money;
                second->Account[index2].balance += money;
                printData(root);
            break;
            case 5:
                __fpurge(stdin);
                printf("Name: ");
                scanf("%[^\n]s",name);
                node = search(root,createData(name,telephone,balance));
                if (node == NULL){
                    printf("Not Exits\n");
                    continue;;
                }
                else
                    root = deleteNode(root,createData(name,telephone,balance));
                printData(root);
            break;
            case 6:
                printf("Exporting....\n");
                FILE *fout = fopen("bank_out.db","w+");
                int times = 0;
                int num = countNode(root);
                fprintf(fout,"%d",num);
                exportData(root, fout,&times);
            break;
        }
    }while(choice != 7);
}
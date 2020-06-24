#ifndef __BANK__
#define __BANK__
#include "tree.h"
tree read_db(FILE *fin);

int checkDuplicate(tree node,keyvalue x);

void printData(tree root);

int countPhone(tree node,keyvalue x);

void exportData(tree root,FILE *fout,int *times);

void exportAccount(tree t,FILE *fout,int *times);
#endif
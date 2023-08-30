#include <bits/stdc++.h>
using namespace std;
#include "def.h"        //全局变量定义
#include "judge.h"      //判断字符串类型
#include "tree.h"       //建立抽象语法树
#include "read.h"       //读取
#include "error.h"      //报错
#include "traverse.h"   //遍历语法树
#include "save.h"       //编排生成缩进源程序文件
#include "compile.h"    //编译
int main(){
    char filename[10];
    T=(Tree)malloc(sizeof(Node));   //总的根节点
    T->sum=0;
    strcpy(T->key1,"root");
    f[0]=T;     //f用于储存每层语句的根节点
    printf("输入需要编译的文件名：");
    scanf("%s",filename);
    fp=fopen(filename,"rb");
    while(fscanf(fp,"%c",&s[i])!=EOF) i++;  //将语句读入字符串
    fclose(fp);
    i=-1;
    printf("line  message\n");
    compile();     //编译
    if(nest>0) printf(" %d   expected '}'\n",l);     //复合语句层数报错
    else if(nest<0) printf(" %d   expected '}' deleted\n",l);
    if(strcmp(filename,"eg2.c")){
        printf("\n");
        PreOrderTraverse(f[0],0);   //遍历语法树
        fp=fopen("main.c","wb");
        save(f[0],0);   //遍历语法树并重新编排进源程序文件
        fclose(fp);
    }
    system("pause");
    return 0;
}

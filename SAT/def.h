#ifndef HEAD_H_INCLUDED            // 这个保证了头文件不会被重复定义
#define HEAD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define OK 1
#define ERROR 0
#define FOUND 1
#define NOTFOUND 0
#define NOANSWER 0
#define YES 1
#define NO 0
typedef int status;
typedef struct LiteralNode{
    int data;
    struct LiteralNode* right;
}LiteralNode;

typedef struct ClauseNode{
    struct LiteralNode* right;
    struct ClauseNode* next;
}ClauseNode;

ClauseNode* CnfParser(int* literal_num, char* filename, int init);   // 读取cnf文件创建子句集
status DpllSolver(ClauseNode* f, int* truth_table);                  // DPLL算法
#endif                                                               // HEAD_H_INCLUDED
#define EPOCH 5             // 重复运行次数
#define PATH_SIZE 1024      // 路径字符串大小


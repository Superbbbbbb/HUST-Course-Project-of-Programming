#include "def.h"
#include "dpll.h"
#include "read.h"

int main()
{
    int op=0,literal_num;
    char filename[PATH_SIZE];
    clock_t x=0,t=0;
    ClauseNode* s;
    while(1){
        system("cls");
        printf("\n\n");
        printf("         基于SAT的二进制数独游戏求解程序\n");
        printf("-------------------------------------------------\n");
        printf("     1. SAT算例求解       2. 数独（待完成）\n");
        printf("     0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0-2]: ");
        scanf("%d", &op);
        if(!op) break;
        else if(op==1){
            printf("\t请输入文件名：");
            scanf("%s",filename);                        // 获得路径
            CnfParser(&literal_num, filename, 1);                     // 先获得文字数，最后的1表明是初始化
            int truth_table[literal_num];                             // 真值表
            memset(truth_table,0,sizeof(truth_table)) ;                // 初始化真值表，这里把初始值设为1，也可改为0
            x=clock();
            s=CnfParser(&literal_num,filename,0);
            t+=clock()-x;
            printf("    time  ：%ldms\n\n",t);       // 输出结果
            if(DpllSolver(s,truth_table)){
                printf("    结果：子句集可满足\n");   // 有解
                printf("    解为：");                              // 打印真值为1的变元
                for(int k=0;k<literal_num; k++)    if(truth_table[k])  printf("%d ", k + 1);
                printf("\n");
            }
            else printf("    结果：子句集不可满足！\n");        // 无解
            getchar();
            getchar();
        }
        else{
            printf("\n    请重新输入！\n");
            getchar();
            getchar();
            continue;
        }
    }
    return 0;
}

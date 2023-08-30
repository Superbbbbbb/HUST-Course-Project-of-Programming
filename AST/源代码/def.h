typedef struct variable{//变量信息储存
    int type;           //数据类型或函数返回类型
    char name[100];     //变量或函数名
    int param_type;      //函数参数类型
    char param_name[100];//函数参数名字
    char array_size[100];     //数组变量大小
}variable;
typedef struct Node{    //语法树结点结构
    char key1[100];     //类型
    char key2[100];     //具体信息
    int sum;            //孩子数量
    Node* child[10];    //孩子们
}Node,*Tree;
typedef struct dfa{     //语法树结点结构
    int s,t;
}dfa;
dfa op;
variable st[100];   //变量信息
enum token_k{ERROR_TOKEN,PLUS,MINUS,PER,SLASH,ASTERISK,AND,OR,ASSIGN,BANG,LC,RC,LP,RP,LB,RB,LA,RA,SEMI,WELL,QUOT,DELIMIT};  //符号类型
enum string_k{VOID=22,INT,LONG,FLOAT,CHAR,IF,ELSE,FOR,WHILE,BREAK,CONTINUE,RETURN,CHAR_CONST,IDENT,INT_CONST,LONG_CONST,FLOAT_CONST,MACRO};
enum error_k{COMPOUND,CURVES,HEAD,FUN_FEW,FUN_MANY,FUN_VOID,FUN_NOTVOID,NO_EFFECT,PAREN,BRACKET,ARRAY,IDENTIFIER,LOOP,FLAG,IF_ELSE};   //报错类型
Tree T,f[10],r[5];
FILE *fp;
char s[100000],t[100],pr[10];
int i,j=1,k,l=1,n,nest,loop,temp,bracket,paren,pre;
bool c;
void compile();     //总编译函数
int subroutine();   //子程序调用
void delimit();     //注释
void save(Tree T,int d);    //生成缩进源程序文件
void oprator(Tree root,int x);  //运算符处理

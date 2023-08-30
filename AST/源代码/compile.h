Tree rt,tr;
void reassign(int x){   //更新运算符的父亲节点
    for(int ii=x;ii<5;ii++)
        r[ii]=T;
}
void recursion1(int x,int y){   //递归1 x表示优先级
    reassign(x);    //更新
    read();
    oprator(T,y);
}
void recursion2(int x,const char* tt){  //递归2 x表示优先级
    InsertNode(r[x],tt,2);     //插入运算符
    reassign(x+1);      //更新
    read();
    oprator(r[x],x);
}

void assign(){
    read();
    CreateNode("ID:",t);
    InsertNode(r[0],"assign:",3);
    CreateNode("ID:",pr);
    swap(T->child[0],T->child[1]);
}

void func(Tree root){       //函数调用处理，root为当前父亲结点
    T=root;
    CreateNode("function call:","\0");     //函数调用
    T=T->child[T->sum-1];
    CreateNode("name:",t);              //函数名
    if(op.t!=LP){              //没有参数
        error(NO_EFFECT);       //
        punc(';');
        return;
    }
    paren++;                    //括号层数加一
    CreateNode("param:","\0");  //参数
    T=T->child[T->sum-1];
    reassign(3);                //更新运算符的父亲节点
    read();
    if(!j){     //参数为空
        CreateNode("\0","void");
        if(st[k].param_type!=VOID) error(FUN_FEW);    //参数类型与定义不符，报错
    }
    else if(st[k].param_type==VOID&&strcmp(t,"void")) error(FUN_MANY);    //参数类型与定义不符，报错
    oprator(T,-1);
}

void oprator(Tree root,int x){  //x为当前的运算符优先级
    if(x<0) T=root;     //可以直接在root上加新结点
    else T=root->child[root->sum-1];    //在root的最后一个孩子节点加新结点
    if(j){
        if(op.s<34&&op.s>0||pre==RP){ //读到
            i-=j;i--;
            return;
        }
        declare_judge(); //判断变量或函数是否已声明
        if(k!=n&&st[k].param_type){   //函数调用
            tr=root;    //记录当前根节点
            func(T);
        }
        else if(k!=n&&st[k].array_size[0]&&op.t!=LB) error(ARRAY);   //数组赋值报错
        else CreateNode("ID:",t);
    }
    else if(op.t==RA){i--;return;}     //读到‘}’，返回
    else if(op.t==ASSIGN&&(pre==PLUS||pre==MINUS||pre==ASTERISK||pre==SLASH||pre==PER)){
        assign();
        return;
    }
    else if(op.t!=LP&&pre!=RB&&pre!=RP&&!(op.t==RP&&pre==RB)&&!(op.t==SEMI&&pre==LP)&&!(op.t==RP&&pre==LP)){
        strcpy(r[0]->key2,"null");
        r[0]->sum=0;
        printf(" %d   error: expected expression before '%c' token\n",l,s[i]);   //运算符前没有变量，报错
    }
    char str[3];
    str[0]=s[i],str[1]='\0';    //符号存入字符串
    switch(op.t){
        case SEMI: return;   //语句结束
        case LB:
            if(!st[k].array_size[0]) error(IDENTIFIER);   //非数组类型报错
            rt=root;    //记录当前根节点
            bracket++;  //方括号层数+1
            T=T->child[T->sum-1];
            CreateNode("subscript:","\0");
            T=T->child[T->sum-1];
            recursion1(3,-1);   //读数组下标
            break;
        case RB:
            bracket--;  //方括号层数-1
            if(bracket<0) return; //方括号数错误，返回
            T=rt;   //返回记录的根节点
            recursion1(3,0);    //递归
            break;
        case LP:
            tr=T;   //记录当前根节点
            paren++;    //括号数+1
            CreateNode("paren:","\0");
            T=T->child[T->sum-1];
            recursion1(1,-1);   //读括号内的算式
            break;
        case RP:
            if(paren<1) return; //条件语句结束，返回
            paren--;    //括号数-1pre
            T=tr;   //返回记录的根节点
            recursion1(1,0);
            break;
        case AND:case OR:  //优先级为1
            str[1]=s[i],str[2]='\0';
            if(s[i+1]==s[i]) i++;
            else printf(" %d   error: expected '%s'\n",l,str);   //只接受‘||’或‘&&’
            recursion2(1,str);
            break;
        case ASSIGN:case LA:case RA:case BANG: //优先级为2
            if(s[i+1]!='='&&op.t==ASSIGN){     //赋值
                InsertNode(f[nest],"assign:",1);
                recursion1(1,-1);
            }
            else{
                if(s[i+1]=='='){        //两个字符的运算符
                    if(op.t!=ASSIGN) str[1]=s[i+1],str[2]='\0';
                    i++;
                }
                recursion2(2,str);
            }
            break;
        case PLUS:case MINUS:  //优先级为3
            strcpy(pr,t);   //pr用于储存上一个字符串
            recursion2(3,str);
            break;
        case ASTERISK:case SLASH:case PER: //优先级为4
            strcpy(pr,t);
            recursion2(4,str);
            break;
        default: if(strcmp(f[nest]->key1,"for")) punc(';'); //不合法字符
    }
}

void var(Tree root,int x){
    paren=bracket=0;    //括号层数初始化
    for(int ii=0;ii<5;ii++) r[ii]=root; //将不同优先级的运算符的父亲节点都更新为当前根节电
    oprator(root,x);   //编译
    if(paren>0) error(PAREN);
    if(bracket>0) error(BRACKET);
}

void init(int type){        //将已定义的变量和函数保存在结构体数组中
    st[n].type=type;
    strcpy(st[n].name,t);
    st[n++].param_type=0;       //参数类型初始化为0
}

void compounds(const char* r){
    CreateNode(r,"sentence:");
    f[++nest]=T->child[T->sum-1];   //进入if，for，while或函数声明之下的语句
}

void compound_judge(){
    read();
    if(op.t==LC){
        if(j) error(COMPOUND);
        compounds("compound");
        compile();
    }
    else{
        c=1;
        i-=j;i--;
        compounds("expression");
        subroutine();
        nest--;
        c=0;
    }
}

void delimit(){         //注释处理
    int jj;
    char str[3];
    Tree tmp=T;
    T=f[nest];
    str[0]=s[i],str[1]=s[i+1],str[2]='\0';
    i+=2;
    if(s[i-1]=='/'){        //行注释
        char* note=strtok(s+i,"\r");    //读取换行符之前的所有字符
        i+=strlen(note);
        if(!c) CreateNode("line comment:",note);
    }
    else{       //块注释
        char note[100];
        for(jj=0;s[i]!='*'||s[i+1]!='/';i++,jj++){  //读取界定符之前的换行符
            note[jj]=s[i];
            if(s[i]==10) l++;
        }
        note[jj-1]='\0';i++;
        if(!c) CreateNode("block comment:",note);
        str[0]='*',str[1]='/';
    }
    T=tmp;
    if(!j) read();
}

void def_pre(){
    read();
    if(!strcmp(t,"include")){       //文件包含
        if(s[i]!=34&&s[i]!='<') error(HEAD);    //标点报错
        read();
        CreateNode("file","declaration:");
        T=T->child[T->sum-1];
        CreateNode("Name:",t);
        if(s[i]!=34&&s[i]!='>'||pre==34&&s[i]!=34||pre=='<'&&s[i]!='>')
            error(HEAD);        //标点报错
    }
    else if(!strcmp(t,"define")){   //宏定义
        read();         //读名字
        macroname_judge();       //命名合法性判断
        init(MACRO);        //储存宏定义
        CreateNode("macro","declaration:");
        T=T->child[T->sum-1];
        CreateNode("Name:",t);
        i++;
        char *tt=strtok(s+i,"\r");  //读定义内容
        i+=strlen(tt);
        CreateNode("value:",tt);
    }
}

void def_var(int type){     //变量和函数定义
    char str1[10],str2[10];
    strcpy(str1,t);
    read();
    name_judge();        //判断命名合法性
    init(type);
    if(op.t==LP&&!nest){   //函数声明
        temp=n-1;       //记录函数序号
        CreateNode("function","declaration:");
        f[++nest]=T->child[T->sum-1];
        T=f[nest];
        CreateNode("type:",str1);       //返回值类型
        CreateNode("name:",t);          //名字
        CreateNode("param:","\0");  //参数
        T=T->child[T->sum-1];
        read();
        if(!j){         //无参数
            op.s=VOID;
            strcpy(str1,"void");
        }
        else{
            switch(op.s){
                case VOID: strcpy(str1,"void");break;
                case CHAR: strcpy(str1,"char");break;
                case INT: strcpy(str1,"int");break;
                case LONG: strcpy(str1,"long");break;
                case FLOAT: strcpy(str1,"float");break;
                default: printf(" %d   error: wrong parameter type\n",l);    //不是数据类型关键字，报错
            }
        }
        st[n-1].param_type=op.s;     //储存参数类型
        CreateNode("type:",str1);
        if(op.s!=VOID){
            read();
            name_judge();    //判断命名合法性
            strcpy(st[n-1].param_name,t);     //储存参数名字
            CreateNode("name:",t);
        }
        punc(')');      //标点报错
        read();
        T=f[nest];
        if(op.t==LC){      //复合语句
            if(j) error(COMPOUND);      //若‘{’前有字符，报错
            compounds("compound");
            compile();
            nest--;         //定义结束后退出一层
            n=temp+1;       //函数内部变量删除
        }
        else{
            if(!punc(';')) i-=j,i--;    //标点报错
            nest--;
        }
        temp=0;
    }
    else if(op.t==LB){     //数组
        if(type!=CHAR) strcpy(str2,strcat(str1," array"));     //数组
        else strcpy(str2,"string");     //字符串
        if(!nest) CreateNode("extern","declaration:");      //外部变量
        else CreateNode("local","declaration:");     //局部变量
        T=f[nest]->child[f[nest]->sum-1];
        CreateNode("type:",str2);
        CreateNode("name:",t);
        read();
        punc(']');      //标点报错
        if(!num_judge(j)) printf(" %d   error: wrong number\n",l); //判断数字合法性
        strcpy(st[n-1].array_size,t);    //保存数组大小
        CreateNode("size:",t);
        read();
        punc(';');     //标点报错
    }
    else{
        if(!nest) CreateNode("extern","declaration:");
        else CreateNode("local","declaration:");
        T=T->child[T->sum-1];
        CreateNode("type:",str1);
        CreateNode("name:",t);
        punc(';');
    }
}

void command(){    //return,break,continue语句处理
    CreateNode(t,"\0");
    if(op.s==RETURN){
        if(nest<=0) error(FLAG);    //不在函数中，报错
        if(op.t!=SEMI){
            if(st[temp].type==VOID) error(FUN_VOID);    //函数返回值报错
            read();
            T=T->child[T->sum-1];
            var(T,-1);
        }
        else if(st[temp].type!=VOID) error(FUN_NOTVOID);    //函数返回值报错
    }
    else if(loop<=0)  error(LOOP);   //不在循环中，报错
    punc(';');
}

void go_if(){    //if语句处理
    CreateNode(t,"sentence:");
    punc('(');
    f[++nest]=T->child[T->sum-1];   //进入下一层
    T=f[nest];
    read();
    Tree root=T;        //保存根节点
    CreateNode("condition:","\0");  //条件
    T=T->child[T->sum-1];
    if(j) var(T,-1);    //处理条件语句
    else{
        error(CURVES);      //语句为空
        CreateNode("\0","null");
    }
    punc(')');      //标点报错
    T=f[nest];
    compound_judge();
    int fl=0;
    while(1){
        read();
        if(op.s==ELSE){      //读else
            fl++;
            read();
            T=root;
            if(op.s==IF){    //else-if语句处理
                fl++;
                CreateNode("condition:","\0");
                T=T->child[T->sum-1];
                punc('(');
                read();
                var(T,-1);      //处理条件语句
                punc(')');
                T=f[nest];
                compound_judge();
            }
            else{       //else语句处理
                i-=j;i--;
                compound_judge();
                break;
            }
        }
        else{
            i-=j;i--;  //没有else或else-if语句，重读
            break;
        }
    }
    if(fl) strcat(f[nest]->key1,"-else");
    if(fl>1) strcat(f[nest]->key1,"-if");
    nest--;     //退出一层
}

void go_for(){   //for循环
    if(j) var(T,-1);    //处理for的第一个赋值语句
    else CreateNode("\0","null");
    punc(';');
    if(strcmp(f[nest]->child[f[nest]->sum-1]->key1,"assign:"))
        error(NO_EFFECT);    //不是赋值语句，报错
    T=f[nest];
    CreateNode("condition:","\0");
    T=T->child[T->sum-1];
    read();
    if(j) var(T,-1);    //处理for的第二个条件语句
    else CreateNode("\0","null");
    punc(';');
    T=f[nest];
    read();
    if(j) var(T,-1);    //处理for的第三个赋值语句
    else CreateNode("\0","null");
}

void go_while(){     //while循环
    CreateNode("condition:","\0");
    T=T->child[T->sum-1];
    if(j) var(T,-1);    //处理条件语句
    else{
        error(CURVES);
        CreateNode("\0","null");
    }
}

void go_loop(int type){     //循环语句
    loop++;     //嵌套数+1
    punc('(');
    CreateNode(t,"sentence:");
    f[++nest]=T->child[T->sum-1];   //进入下一层
    T=f[nest];
    read();
    if(type==WHILE) go_while();     //while语句
    else go_for();       //for语句
    punc(')');
    T=f[nest];
    compound_judge();
    nest--;
    loop--;
}

void compile(){    //编译
    while(s[i]||j)      //读至文件结束
        if(!subroutine())
            return;
}

int subroutine(){
    read();
    if(!s[i]&&!j) return 1;
    if(op.t==RC){  //读到‘}’
        if(j) error(COMPOUND);
        nest--;     //退出一层
        return 0;
    }
    T=f[nest];
    if(!j&&op.t==WELL) def_pre();     //预处理
    else{
        switch(op.s){
            case VOID: case CHAR:case INT:case FLOAT:case LONG: def_var(op.s);break;
            case WHILE:case FOR: go_loop(op.s);break;
            case IF: go_if();break;
            case ELSE: error(IF_ELSE);break;   //else没有if，报错
            case BREAK:case CONTINUE:case RETURN: command();break;
            default: var(T,-1);     //函数调用或赋值语句处理
        }
    }
    return 1;
}

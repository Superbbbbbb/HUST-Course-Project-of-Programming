void CreateNode(const char* t1,const char* t2){     //新结点
    T->child[T->sum]=(Tree)malloc(sizeof(Node));    //新结点
    strcpy(T->child[T->sum]->key1,t1);          //字符串写入
    strcpy(T->child[T->sum]->key2,t2);
    T->child[T->sum++]->sum=0;          //孩子个数初始化为0
}

void InsertNode(Tree root,const char* str,int x){      //插入结点
    Tree p=(Tree)malloc(sizeof(Node));          //新结点
    p->sum=0;                                   //孩子个数初始化
    p->key1[0]=p->key2[0]='\0';
    if(x%2){
        strcpy(p->key1,str);               //字符串写入
        if(x==3) strcpy(p->key2," ");
    }
    else strcpy(p->key2,str);
    p->child[p->sum++]=root->child[root->sum-1];       //新结点作为父亲节点的孩子
    root->child[root->sum-1]=p;         //原孩子作为新结点的孩子
    T=p;
}

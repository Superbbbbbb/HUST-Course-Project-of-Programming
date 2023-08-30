void PreOrderTraverse(Tree T,int d){
    if(d){
        for(int ii=1;ii<d;ii++) printf("    ");     //缩进
        if(T->key1[0]) printf("%s ",T->key1);
        printf("%s\n",T->key2);
    }
    for(int ii=0;ii<T->sum;ii++)
        PreOrderTraverse(T->child[ii],d+1);     //遍历所有孩子
}

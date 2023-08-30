void indent(int d){     //缩进
    fputs("\n",fp);
    for(int i=1;i<d;i++)
        fputc('\t',fp);
}

void next(Tree T,int d){    //先序遍历所有孩子结点
    for(int i=0;i<T->sum;i++)
        save(T->child[i],d);
}

void InOrderTraverse(Tree T){       //中序遍历输出赋值语句或条件语句
    //printf("%s %s\n",T->key1,T->key2);
    if(T->sum){
        if(!strcmp(T->key1,"function call:")) next(T,2);  //函数调用
        else if(!strcmp(T->key1,"paren:")){     //括号
            fputc('(',fp);
            InOrderTraverse(T->child[0]);
            fputc(')',fp);
        }
        else if(!strcmp(T->key1,"subscript:")){ //方括号
            fputc('[',fp);
            InOrderTraverse(T->child[0]);
            fputc(']',fp);
        }
        else if(!strcmp(T->key1,"ID:")){    //数组
            fputs(T->key2,fp);
            InOrderTraverse(T->child[0]);
        }
        else{
            InOrderTraverse(T->child[0]);
            if(!strcmp(T->key2,"="))    //==
                fputs("==",fp);
            else fputs(T->key2,fp);
            InOrderTraverse(T->child[1]);
        }
    }
    else if(strcmp(T->key2,"void")) fputs(T->key2,fp);  //空
}

void save(Tree T,int d){
    //printf("%s %s\n",T->key1,T->key2);
    if(!d) next(T,d+1);
    else if(!strcmp(T->key1,"line comment:"))   //行注释
        fprintf(fp,"\t\t//%s",T->key2);
    else if(!strcmp(T->key1,"block comment:"))  //块注释
        fprintf(fp,"\n/*%s*/",T->key2);
    else if(!strcmp(T->key1,"size:")){      //数组大小
        fprintf(fp,"[%s]",T->key2);
        next(T,d);
    }
    else if(!strcmp(T->key1,"condition:"))  //条件语句
        InOrderTraverse(T->child[0]);
    else if(!strcmp(T->key1,"compound")){   //复合语句
        fputc('{',fp);
        next(T,d+1);
        indent(d);
        fputc('}',fp);
    }
    else if(!strcmp(T->key1,"expression"))      //单个语句
        next(T,d+1);
    else if(!strcmp(T->key1,"param:")){     //函数形参
        fputc('(',fp);
        if(T->sum==1) InOrderTraverse(T->child[0]);     //调用
        else next(T,d);     //定义
        fputc(')',fp);
    }
    else if(!strcmp(T->key1,"if")||!strcmp(T->key1,"if-else")||!strcmp(T->key1,"if-else-if")){     //if语句
        int tmp=0,fl=0;          //用于记录上一个else-if语句的序号
        for(int i=0;i<T->sum;i++){
            if(!strcmp(T->child[i]->key1,"condition:")){    //条件语句
                indent(d);
                if(i) fputs("else ",fp);    //else-if语句
                fputs("if(",fp);
                save(T->child[i],d);
                fputc(')',fp);
            }
            else if(!strcmp(T->child[i]->key2,"sentence:")){
                if(tmp==i-1&&tmp&&fl){      //else语句
                    indent(d);
                    fputs("else",fp);
                }
                tmp=i;
                fl=1;
                save(T->child[i],d);
            }
            else{       //有注释的情况
                tmp++;
                save(T->child[i],d);
            }
        }
    }
    else if(!strcmp(T->key1,"assign:")){    //赋值语句
        indent(d);
        if(!strcmp(T->key2," ")){
            T=T->child[1];
            fputs(T->child[0]->key2,fp);
            fprintf(fp,"%s=",T->key2);
            fputs(T->child[1]->key2,fp);
        }
        else{
            InOrderTraverse(T->child[0]);
            fputc('=',fp);
            InOrderTraverse(T->child[1]);
        }
        fputc(';',fp);
    }
    else if(!strcmp(T->key1,"function call:")){   //函数调用
        indent(d);
        next(T,d);
        fputc(';',fp);
    }
    else if(!strcmp(T->key1,"return")||!strcmp(T->key1,"continue")||!strcmp(T->key1,"break")){
        indent(d);
        fputs(T->key1,fp);
        if(T->sum){
            fputc(' ',fp);
            InOrderTraverse(T->child[0]);
        }
        fputc(';',fp);
    }
    else if(!strcmp(T->key2,"declaration:")){   //声明语句
        indent(d);
        if(!strcmp(T->key1,"file"))     //文件包含
            fprintf(fp,"#include<%s>",T->child[0]->key2);
        else if(!strcmp(T->key1,"macro")){    //宏定义
            fputs("#define ",fp);
            next(T,d);
        }
        else{
            next(T,d);
            if(strcmp(T->child[T->sum-1]->key1,"compound"))     //函数定义除外
                fputc(';',fp);
        }
    }
    else if(!strcmp(T->key2,"sentence:")){  //循环语句
        indent(d);
        fprintf(fp,"%s(",T->key1);
        if(!strcmp(T->key1,"for")){     //for
            for(int i=0;i<3;i++){
                if(strcmp(T->child[i]->key2,"null")){
                    if(!strcmp(T->child[i]->key1,"assign:")){   //赋值
                        InOrderTraverse(T->child[i]->child[0]);
                        fputc('=',fp);
                        InOrderTraverse(T->child[i]->child[1]);
                    }
                    else if(!T->child[i]->key1[0])  //无意义语句
                        InOrderTraverse(T->child[i]);
                    else save(T->child[i],d);   //条件语句
                }
                if(i<2) fputc(';',fp);
                else fputc(')',fp);
            }
            if(T->sum>3)    //有注释
                for(int ii=3;ii<T->sum;ii++)
                    save(T->child[ii],d);
        }
        else if(!strcmp(T->key1,"while")){  //while
            for(int i=0;i<T->sum;i++)
                if(!strcmp(T->child[i]->key1,"condition:")){
                    InOrderTraverse(T->child[i]->child[0]);     //条件语句
                    fputc(')',fp);
                }
                else save(T->child[i],d);
        }
    }
    else{
        if(!strcmp(T->key2,"string")) fputs("char",fp);  //字符串定义
        else if(strstr(T->key2," array"))        //数组定义
            for(int ii=0;T->key2[ii]!=' ';ii++)
                fputc(T->key2[ii],fp);
        else fputs(T->key2,fp);
        if(strcmp(T->key1,"name:")) fputc(' ',fp);  //名字后面不需要空格
        next(T,d);  //孩子们
    }
}

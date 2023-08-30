int punc(char x){   //标点报错
    if(s[i]!=x){
        if(x!=';') i--;
        printf(" %d   error: expected '%c'\n",l,x);
        return 0;
    }
    return 1;
}

int redeclare_judge(){
    for(int ii=0;ii<n;ii++)
        if(!strcmp(st[ii].name,t)){         //判断是否重复命名
            if(!st[ii].param_type){
                printf(" %d   error: redeclaration of '%s' with no linkage\n",l,t);
                return 0;
            }
        }
    return 1;
}

int var_judge(){
    for(k=0;k<n;k++)       //判断变量是否已声明过
        if(!strcmp(t,st[k].name))
            return k+1;
    return 0;
}

void name_judge(){            //判断命名是否合法
    if(!(t[0]>='a'&&t[0]<='z'||t[0]>='A'&&t[0]<='Z'||t[0]=='_')){       //第一个字符不能为数字
        printf(" %d   error: wrong name definiton\n",l);
        return;
    }
    if(key_judge()){         //是否为关键字
        printf(" %d   error: two or more data types in declaration specifiers\n",l);
        return;
    }
    for(int ii=0;ii<j;ii++)
        if(!(t[ii]>='0'&&t[ii]<='9'||t[ii]>='a'&&t[ii]<='z'||t[ii]>='A'&&t[ii]<='Z'||t[ii]=='_')){      //字符不合法
            printf(" %d   error: wrong name definiton\n",l);
            return;
        }
    redeclare_judge();
}

void declare_judge(){
    if(!var_judge()&&!num_judge(j)&&!char_judge()&&strcmp(t,st[temp].param_name)&&!key_judge())
        printf(" %d   error: %s undeclared\n",l,t);
    else if(num_judge(j)<0) printf(" %d   error: wrong number for '%s'\n",l,t);
    else if(char_judge()==-1) printf(" %d   warning: multi-character character constant\n",l);
}

void macroname_judge(){
    for(int ii=0;t[ii];ii++){
        if((t[ii]<'A'||t[ii]>'Z')&&t[ii]!='_'){         //判断宏定义命名中是否有不合法字符
            printf(" %d   error: wrong name defination\n",l);
            return;
        }
    }
    redeclare_judge();
}

void error(int x){  //其他部分报错
    switch(x){
        case COMPOUND: declare_judge();printf(" %d   error: expected ';' after '%s'\n",l,t);break;
        case CURVES: printf(" %d   error: expected expression before ')' token\n",l);break;
        case HEAD: printf(" %d   error: #include expects %dFILENAME%d or <FILENAME>\n",l,34,34);break;
        case FUN_FEW: printf(" %d   error: too few arguments to function\n",l);break;
        case FUN_MANY: printf(" %d   error: too many arguments to function\n",l);break;
        case FUN_VOID:printf(" %d   error: return statement with no value\n",l);break;
        case FUN_NOTVOID:printf(" %d   error: return-statement with a value in function returning 'void'\n",l);
        case NO_EFFECT: printf(" %d   warning: statement with no effect\n",l);break;
        case ARRAY:printf(" %d   error: incompatible types for '%s'\n",l,t);break;
        case IDENTIFIER:printf(" %d   error: '%s' is neither array nor pointer\n",l,t);break;
        case LOOP:printf(" %d   error: statement not within loop or switch\n",l);break;
        case FLAG:printf(" %d   error: statement not within function\n",l);break;
        case IF_ELSE:printf(" %d   error: 'else' without a previous 'if'\n",l);break;
        case PAREN:printf(" %d   error: expected ')'\n",l);break;
        case BRACKET:printf(" %d   error: expected ']'\n",l);break;
    }
}

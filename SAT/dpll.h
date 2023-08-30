status IsEmptyClause(ClauseNode* s){
    ClauseNode* tmp = s->next;
    while(tmp){
        if(!tmp->right) return 1;
        tmp=tmp->next;
    }
    return 0;
}

ClauseNode* IsUnitClause(ClauseNode* s){
    ClauseNode* tmp=s;
    while(tmp){
        if(tmp->right&&!tmp->right->right) return tmp;
        tmp=tmp->next;
    }
    return 0;
}

ClauseNode* DeleteLiteral(ClauseNode* s,int var){
    LiteralNode *l=s->right,*tmp;
    // 处理第一个文字
    if(l->data==-var)                  // 负变元
    {
        tmp=s->right->right;
        free(l);
        s->right=tmp;
        return s;
    }
    else if(l->data==var) return 0; // 正变元
    // 循环处理接下来的文字
    while(l){
        if(l->right&&l->right->data==-var){
            tmp=l->right;
            l->right=l->right->right;
            free(tmp);
        }
        else if(l->right&&l->right->data==var)  return 0;
        l=l->right;
    }
    return s;
}

ClauseNode* DeleteClause(ClauseNode* s){
    ClauseNode* tmp=s;
    LiteralNode* l;
    while(s->right){
        l=s->right;
        s->right=s->right->right;
        free(l);
    }
    s=s->next;
    free(tmp);              //再删除空子句
    return s;
}

status RemoveVar(ClauseNode* s, int var){
    ClauseNode *tmp=s->next,*last_tmp=s;
    while(tmp){
        tmp=DeleteLiteral(tmp,var);           // 删除子句里所有的负变元，如果遇到了正变元则返回NULL
        if(!tmp){
            tmp=DeleteClause(last_tmp->next);  // 与正变元相同则删除子句
            last_tmp->next=tmp;
            continue;
        }
        last_tmp=tmp;                          // 下一个子句
        tmp=tmp->next;
    }
    return OK;
}

ClauseNode* CopyClause(ClauseNode* s){
    ClauseNode* clause_tmp;
    LiteralNode *literal_tmp,*s_tmp=s->right;
    // 创建子句结点
    clause_tmp=(ClauseNode*)malloc(sizeof(ClauseNode));
    clause_tmp->next=NULL;
    clause_tmp->right=NULL;
    // 创建第一个文字结点
    if(s_tmp){
        literal_tmp=(LiteralNode *)malloc(sizeof(LiteralNode));
        literal_tmp->data=s_tmp->data;
        literal_tmp->right=NULL;
        s_tmp=s_tmp->right;
        clause_tmp->right=literal_tmp;
    }
    // 循环创建之后的文字结点
    while(s_tmp){
        literal_tmp->right=(LiteralNode *)malloc(sizeof(LiteralNode));
        literal_tmp->right->data=s_tmp->data;
        literal_tmp->right->right=NULL;
        literal_tmp=literal_tmp->right;
        s_tmp=s_tmp->right;
    }
    return clause_tmp;
}

ClauseNode* CopyS(ClauseNode* s){
    ClauseNode *s_new,*tmp,*origin=s->next;
    s_new=(ClauseNode*)malloc(sizeof(ClauseNode));
    s_new->right=NULL;
    tmp=s_new;
    while(origin){
        tmp->next=CopyClause(origin);  // 复制整个子句
        tmp=tmp->next;                 // 下一个
        origin=origin->next;
    }
    return s_new;
}

ClauseNode* AddClause(ClauseNode* s, int var){
    ClauseNode* tmp;
    tmp=(ClauseNode *)malloc(sizeof(ClauseNode));
    tmp->right=(LiteralNode*)malloc(sizeof(LiteralNode));
    tmp->right->data=var;
    tmp->right->right=NULL;
    tmp->next=s->next;
    s->next=tmp;
    return s;
}

status RecordTruth(ClauseNode* s, int* truth_table){
    int idx=abs(s->right->data)-1;   // 序号=绝对值-1
    if(s->right->data>0) truth_table[idx]=1;
    else truth_table[idx]=0;
    return 1;
}

status DpllSolver(ClauseNode* s,int* truth_table){
    ClauseNode* tmp=s;
    ClauseNode* unit_clause=IsUnitClause(tmp);    // 获得单子句
    // 单子句规则
    while(unit_clause){
        RecordTruth(unit_clause,truth_table);     // 记录单子句中的变元的真值
        int var=unit_clause->right->data;
        RemoveVar(s,var);
        if(!s->next) return 1;             // S为空
        else if(IsEmptyClause(s)) return 0;  //S中存在空子句
        tmp=s;
        unit_clause=IsUnitClause(tmp);  // 还存在单子句则继续循环
    }
    //分裂策略
    int var=s->next->right->data;                                   // 选变元
    if(DpllSolver(AddClause(CopyS(s),var),truth_table)) return 1;   // 变元的真值选对了,此处传入S的拷贝
    return DpllSolver(AddClause(s,-var),truth_table);               // 变元的真值选错了
}

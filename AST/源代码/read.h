void skip(){    //跳过空格，回车符,制表符和换行符
    while(s[i]==' '||s[i]==9||s[i]==10||s[i]==13){
        if(s[i]==10) l++;   //读到换行符，行数加一
        i++;        //读下一个字符
    }
}

void read(){
    pre=op.t;       //保存上一个标点或无意义字符
    i++;            //读下一个字符
    skip();         //跳过无意义字符
    for(j=0;judge();i++,j++)
        t[j]=s[i];          //字符串保存至t中
    if(!j&&s[i]=='-'){      //读负数
        t[0]='-';
        i++;
        skip();
        for(j=1;judge();i++,j++)
            t[j]=s[i];
    }
    t[j]='\0';
    skip();
    if(judge()) i--;    //如果最后读到的不是无意义字符，返回前一个字符
    //printf("%s %c\n",t,s[i]);
    op.s=op.t=0;
    if(j){
        if(num_judge(j)) op.s=num_judge(j); //数字
        else if(char_judge()) op.s=CHAR_CONST; //字符
        else if(key_judge()) op.s=key_judge();
        else op.s=IDENT;  //标识符
    }
    if(s[i]=='/'&&(s[i+1]=='/'||s[i+1]=='*')) delimit(); //读到注释界定符
    else{
        switch(s[i]){
            case '(': op.t=LP;break;
            case ')': op.t=RP;break;
            case '[': op.t=LB;break;
            case ']': op.t=RB;break;
            case '{': op.t=LC;break;
            case '}': op.t=RC;break;
            case '&': op.t=AND;break;
            case '|': op.t=OR;break;
            case '<': op.t=LA;break;
            case '>': op.t=RA;break;
            case '+': op.t=PLUS;break;
            case '-': op.t=MINUS;break;
            case '*': op.t=ASTERISK;break;
            case '/': op.t=SLASH;break;
            case '%': op.t=PER;break;
            case ';': op.t=SEMI;break;
            case '=': op.t=ASSIGN;break;
            case '!': op.t=BANG;break;
            case '#': op.t=WELL;break;
            case 34:case 39:op.t=QUOT;break;
            case ' ':case 13:case 10:case 0: return; //无意义字符，返回
            default: printf(" %d   error: error token\n",l);read();break;  //非法字符
        }
    }
}

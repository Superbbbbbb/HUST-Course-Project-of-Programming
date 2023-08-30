int num_judge(int jj){              //判断数字的类型
    int ii,cnt,x=INT_CONST;         //默认int
    char tt[10];
    if(t[0]=='-'){                  //处理负数
        strcpy(tt,t+1);
        jj--;
    }
    else strcpy(tt,t);
    if(tt[0]<'0'||tt[0]>'9') return 0;  //第一个字符不合法,不是数字
    if(jj>1){   //判断多位数
        if(jj>2&&t[1]!='x'&&t[1]!='X'&&(tt[jj-1]<'0'||tt[jj-1]>'9')){   //有后缀的数字
            if(tt[jj-1]!='L'&&tt[jj-1]!='l') return -1;
            jj--;
            for(ii=0;ii<jj;ii++)
                if(tt[ii]<'0'||tt[ii]>'9')
                    return -1;           //字符串中含有不是数字的数，返回0
            return LONG_CONST;              //返回long类型
        }
        if(tt[0]=='0'){                     //首位为0
            if(tt[1]=='0') return -1;        //第二位也为0，返回0
            else if(tt[1]=='.'){            //小数点为第二位的的float类型，如1.1
                for(ii=2;ii<jj;ii++)
                    if(tt[ii]<'0'||tt[ii]>'9')
                        return -1;           //字符串中含有不是数字的数，返回0
                return FLOAT_CONST;         //返回float类型
            }
            else if(tt[1]=='x'||tt[1]=='X'){    //十六进制数
                for(ii=2;ii<jj;ii++)
                    if(!(tt[ii]>='0'&&t[ii]<='9'||t[ii]>='a'&&t[ii]<='f'||t[ii]>='A'&&t[ii]<='F'))  //从第三位开始为0~9或a~f或A~F
                        return -1;
                return INT_CONST;
            }
            else{                               //八进制数
                for(ii=1;ii<jj;ii++)
                    if(tt[ii]<'0'||tt[ii]>'7')  //数字为0~7
                        return -1;
                return INT_CONST;
            }
        }
        else{
            for(cnt=ii=0;ii<jj;ii++){
                if(tt[ii]=='.'){        //如果包含小数点
                    cnt++;
                    x=FLOAT_CONST;      //为float类型
                }
                else if(tt[ii]<'0'||tt[ii]>'9'||cnt>1) return -1;    //出现0~9之外的数字或第二个小数点
            }
            return x;
        }
    }
    if(t[j-1]<'0'||t[j-1]>'9') return -1;    //判断一位数
    return INT_CONST;
}

char char_judge(){       //判断是否为字符
    if(t[0]!=39||t[j-1]!=39) return 0;
    if(j>3) return -1;  //字符过长，返回最后一个字符
    return 1;
}

int key_judge(){        //判断是否为关键字
    if(!strcmp(t,"char")) return CHAR;
    if(!strcmp(t,"int")) return INT;
    if(!strcmp(t,"long")) return LONG;
    if(!strcmp(t,"float")) return FLOAT;
    if(!strcmp(t,"for")) return FOR;
    if(!strcmp(t,"while")) return WHILE;
    if(!strcmp(t,"break")) return BREAK;
    if(!strcmp(t,"continue")) return CONTINUE;
    if(!strcmp(t,"else")) return ELSE;
    if(!strcmp(t,"if")) return IF;
    if(!strcmp(t,"return")) return RETURN;
    if(!strcmp(t,"void")) return VOID;
    return 0;
}

int judge(){        //判断是否是字符串中的合法字符
    if(s[i]>='0'&&s[i]<='9'||s[i]>='a'&&s[i]<='z'||s[i]>='A'&&s[i]<='Z'||s[i]=='.'||s[i]=='_'||s[i]==39) return 1;
    return 0;
}

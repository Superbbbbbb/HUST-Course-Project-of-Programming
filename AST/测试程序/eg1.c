#include<stdio.h>
#include<stdlib.h>
#define N 10
int a[100];
int b(int i){   //5
    int x;
    x=i+1;
    return x+056;      //Here is a line comment.
}
long n;     //10
/*
* Here is a block comment.
*/
void f();
int main(){
    int i;
    int j;
    float x;
    x=1.2;
    char c;
    char s[10];
    s[1]='y';
    n=12L;          //20
    c='t';
    f();
    i=i+j;
    for(i=1;i<=n||n>0;){    //Here is a line comment.
        a[i+1]=b(i+1)+1;
        j*=i;
        for(j=0;j<N;j=j+1)
            a[i]=a[i]*2+1;
    }
    i=-1;
    j=0x1a;
    while(j) {         //30
        i=i<n && (n!=2 || i*2+j/3-n%4>4);
        if(a[i]%2)
            j=(i+2)*j/5+6;
        else if(a[i]==3) j=j/2-j%(3+i);
        else j*=i;
        if(j){                   //35
            if(j<0) continue;
            else j=j-2;
        }
        else break;
    }                     //40
    return 0;
}

void f(){
    n=n+1;
    return;
}

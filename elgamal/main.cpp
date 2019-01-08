#include <iostream>
#include <stdlib.h>
#include<string>
#include<stdio.h>
#include <time.h>
#include <math.h>
#include"BigInt.h"
#include"BigPrime.h"
#include"MD5.h"
#include"file.h"
#define random(x) (rand()%x)

using namespace std;

string trans_H(string str)
{
    char a[32]="0";
    int i;
    int j = 0;
    for(i = 0; str[i] != '\0'; i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
        	a[j] = str[i];
        	j++;
		}
		else
		{
			continue;
		}
    }
        return a;
}


int main()
{
    /*
    int BigP=BigPrime(10);
    char str[10];
    sprintf(str,"%d",BigP);
    //cout<<str<<endl;
    /*
    公开密钥y,g,p
    */
    int i;
    cout<<"请输入要生成的bit位数"<<endl;
    cin>>i;
    cout<<endl;
    getPrime(i/8);
    BigInt p;
    string str;

    cout<<"选择的p为："<<endl;
    cin>>str;
    cout<<endl;
    p.values=str;

    //p.values=str;
    //p.values="187876178186193686973946126803229013719";
    //p.values="231375518946670117154372631004179458573";
    cout<<"素数p为"<<p<<endl;
    cout<<endl;

    BigInt g("2");

    //int x_n=rand()%(BigP-2)+1;
    int x_n=rand()%(100000)+1;
    BigInt x;
    char x_s[10];
    sprintf(x_s,"%d",x_n);
    x.values=x_s;
    //cout<<x_s<<endl;
    cout<<"挑选的随机x为："<<x<<endl;

    BigInt y = mod_fast(g,x,p);
    cout<<"计算得y为："<<y<<endl;
    cout<<endl;
    BigInt a("1");
    //p为大素数 g为本原元 x为 1≤x≤p-2 y=g^x(mod p)
    //y是公开密钥，而x是保密密钥

    BigInt k("5"),s,r,m,md,k1;//m,r,s是对消息的数字签名
    BigInt t1,t2;
    string txt;
    /*
    cout<<"请输入明文："<<endl;
    cin>>txt;
    */
    FileRead(&txt);
    cout<<"明文为："<<txt<<endl;
    cout<<endl;
    md.values=md5(txt);
    cout<<"md5加密后得："<<md.values<<endl;
    cout<<endl;
    string md_str;
    md_str=trans_H(md.values);
    //cout<<md_str<<endl;
    m.values=md_str;
    r=mod_fast(g,k,p);
    k1=mod_inverse(k,p-a);
    s=((m-x*r)*k1)%(p-a);
    cout<<"r:"<<r<<endl;
    cout << "s:"<<s << endl;
    cout<<endl;

    string str_y,str_r,str_s;
    cout<<"请输入对应的y:"<<endl;
    cin>>str_y;
    y.values=str_y;
    cout<<"此时的y为"<<y<<'\n'<<endl;
    cout<<"请输入对应的r:"<<endl;
    cin>>str_r;
    r.values=str_r;
    cout<<"此时的r为"<<r<<'\n'<<endl;
    cout<<"请输入对应的s:"<<endl;
    cin>>str_s;
    s.values=str_s;
    cout<<"此时的s为"<<s<<'\n'<<endl;

    cout<<"接下来验证签名------->"<<endl;
    t1=mod_fast(y,r,p);
    t2=mod_fast(r,s,p);
    cout << "t1:\n"<<t1<<'\n'<< endl;
    cout << "t2:\n"<<t2<<'\n'<< endl;
    if(((t1*t2)%p).values==mod_fast(g,m,p).values)
    {
        cout<<"对比成功！"<<endl;
    }else{
        cout<<"签名失败！"<<endl;
    }
    return 0;


}

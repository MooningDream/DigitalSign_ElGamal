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
    ������Կy,g,p
    */
    int i;
    cout<<"������Ҫ���ɵ�bitλ��"<<endl;
    cin>>i;
    cout<<endl;
    getPrime(i/8);
    BigInt p;
    string str;

    cout<<"ѡ���pΪ��"<<endl;
    cin>>str;
    cout<<endl;
    p.values=str;

    //p.values=str;
    //p.values="187876178186193686973946126803229013719";
    //p.values="231375518946670117154372631004179458573";
    cout<<"����pΪ"<<p<<endl;
    cout<<endl;

    BigInt g("2");

    //int x_n=rand()%(BigP-2)+1;
    int x_n=rand()%(100000)+1;
    BigInt x;
    char x_s[10];
    sprintf(x_s,"%d",x_n);
    x.values=x_s;
    //cout<<x_s<<endl;
    cout<<"��ѡ�����xΪ��"<<x<<endl;

    BigInt y = mod_fast(g,x,p);
    cout<<"�����yΪ��"<<y<<endl;
    cout<<endl;
    BigInt a("1");
    //pΪ������ gΪ��ԭԪ xΪ 1��x��p-2 y=g^x(mod p)
    //y�ǹ�����Կ����x�Ǳ�����Կ

    BigInt k("5"),s,r,m,md,k1;//m,r,s�Ƕ���Ϣ������ǩ��
    BigInt t1,t2;
    string txt;
    /*
    cout<<"���������ģ�"<<endl;
    cin>>txt;
    */
    FileRead(&txt);
    cout<<"����Ϊ��"<<txt<<endl;
    cout<<endl;
    md.values=md5(txt);
    cout<<"md5���ܺ�ã�"<<md.values<<endl;
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
    cout<<"�������Ӧ��y:"<<endl;
    cin>>str_y;
    y.values=str_y;
    cout<<"��ʱ��yΪ"<<y<<'\n'<<endl;
    cout<<"�������Ӧ��r:"<<endl;
    cin>>str_r;
    r.values=str_r;
    cout<<"��ʱ��rΪ"<<r<<'\n'<<endl;
    cout<<"�������Ӧ��s:"<<endl;
    cin>>str_s;
    s.values=str_s;
    cout<<"��ʱ��sΪ"<<s<<'\n'<<endl;

    cout<<"��������֤ǩ��------->"<<endl;
    t1=mod_fast(y,r,p);
    t2=mod_fast(r,s,p);
    cout << "t1:\n"<<t1<<'\n'<< endl;
    cout << "t2:\n"<<t2<<'\n'<< endl;
    if(((t1*t2)%p).values==mod_fast(g,m,p).values)
    {
        cout<<"�Աȳɹ���"<<endl;
    }else{
        cout<<"ǩ��ʧ�ܣ�"<<endl;
    }
    return 0;


}

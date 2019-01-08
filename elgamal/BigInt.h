#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>//reverse函数所需添加的头文件
using namespace std;
/*
大整数类
*/
class BigInt
{
    private:
        inline int compare(string s1, string s2)  //字符串比较
        {
            if(s1.size() < s2.size())
                return -1;
            else if(s1.size() > s2.size())
                return 1;
            else
                return s1.compare(s2);
        }
    public:
        bool flag;//true表示正数，false表示负数，0默认为正数
        string values;//保存所有位上的数字
        BigInt():values("0"),flag(true){};//构造函数
        BigInt(string str)//类型转换构造函数(默认为正整数)
        {
            values = str;
            flag = true;
        }
    public:
        friend ostream& operator << (ostream& os, const BigInt& bigInt);//重载输出操作符
        friend istream& operator>>(istream& is, BigInt& bigInt);//输入操作符重载
        BigInt operator+(const BigInt& rhs);//加法操作重载
        BigInt operator-(const BigInt& rhs);//减法操作重载
        BigInt operator*(const BigInt& rhs);//乘法操作重载
        BigInt operator/(const BigInt& rhs);//除法操作重载
        BigInt operator%(const BigInt& rhs);//求余操作重载
};
/*
重载流提取运算符'>>'，输出一个整数
*/
ostream& operator << (ostream& os, const BigInt& bigInt)
{
    if (!bigInt.flag)
    {
        os << '-';
    }
    os << bigInt.values;
    return os;
}
/*
重载流插入运算符'>>'，输入一个正整数
*/
istream& operator >> (istream& is, BigInt& bigInt)
{
    string str;
    is >> str;
    bigInt.values = str;
    bigInt.flag = true;
    return is;
}
/*
两个正整数相加
*/
BigInt BigInt::operator+(const BigInt& rhs)
{
    BigInt ret;
    ret.flag = true;//正整数相加恒为正数
    string lvalues(values), rvalues(rhs.values);
    //处理特殊情况
    if (lvalues == "0")
    {
        ret.values = rvalues;
        return ret;
    }
    if (rvalues == "0")
    {
        ret.values = lvalues;
        return ret;
    }
    //调整s1与s2的长度
    unsigned int i, lsize, rsize;
    lsize = lvalues.size();
    rsize = rvalues.size();
    if (lsize < rsize)
    {
        for (i = 0; i < rsize - lsize; i++)//在lvalues左边补零
        {
            lvalues = "0" + lvalues;
        }
    }
    else
    {
        for (i = 0; i < lsize - rsize; i++)//在rvalues左边补零
        {
            rvalues = "0" + rvalues;
        }
    }
    //处理本质情况
    int n1, n2;
    n2 = 0;
    lsize = lvalues.size();
    string res = "";
    reverse(lvalues.begin(), lvalues.end());//颠倒字符串，以方便从低位算起计算
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < lsize; i++)
    {
        n1 = (lvalues[i] - '0' + rvalues[i] - '0' + n2) % 10;//n1代表当前位的值
        n2 = (lvalues[i] - '0' + rvalues[i] - '0' + n2) / 10;//n2代表进位
        res = res + char(n1 + '0');
    }

    if (n2 == 1)
    {
        res = res + "1";
    }
    reverse(res.begin(), res.end());

    ret.values = res;
    return ret;
}
/*
两个正整数相减
*/
BigInt BigInt::operator-(const BigInt& rhs)
{
    BigInt ret;
    string lvalues(values), rvalues(rhs.values);
    //负数减负数
    if(flag==false&&rhs.flag==false)
    {
        string tmp = lvalues;
        lvalues = rvalues;
        rvalues = tmp;
    }
    //负数减正数
    if(flag==false&&rhs.flag==true)
    {
        BigInt res(lvalues);
        ret=res+rhs;
        ret.flag = false;
        return ret;
    }
    if(flag==true&&rhs.flag==false)
    {
        BigInt rel(lvalues),res(rhs.values);
        ret=rel+res;
        ret.flag = true;
        return ret;
    }
        //处理特殊情况
    if (rvalues == "0")
    {
        ret.values = lvalues;
        ret.flag = true;
        return ret;
    }
    if (lvalues == "0")
    {
        ret.values = rvalues;
        ret.flag = false;
        return ret;
    }
    //调整s1与s2的长度
    unsigned int i, lsize, rsize;
    lsize = lvalues.size();
    rsize = rvalues.size();
    if (lsize < rsize)
    {
        for (i = 0; i < rsize - lsize; i++)//在lvalues左边补零
        {
            lvalues = "0" + lvalues;
        }
    }
    else
    {
        for (i = 0; i < lsize - rsize; i++)//在rvalues左边补零
        {
            rvalues = "0" + rvalues;
        }
    }
    //调整使‘-’号前边的数大于后边的数
    int t = lvalues.compare(rvalues);//相等返回0，str1<str2返回负数，str1>str2返回正数
    if (t < 0)
    {
        ret.flag = false;
        string tmp = lvalues;
        lvalues = rvalues;
        rvalues = tmp;
    }
    else if (t == 0)
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    else
    {
        ret.flag = true;
    }
    //处理本质情况
    unsigned int j;
    lsize = lvalues.size();
    string res = "";
    reverse(lvalues.begin(), lvalues.end());//颠倒字符串，以方便从低位算起计算
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < lsize; i++)
    {
        if (lvalues[i] < rvalues[i])//不足，向前借一维
        {
            j = 1;
            while(lvalues[i+j] == '0')
            {
                lvalues[i+j] = '9';
                j++;
            }
            lvalues[i+j] -= 1;
            res = res + char(lvalues[i] + ':' - rvalues[i]);
        }
        else
        {
            res = res + char(lvalues[i] - rvalues[i] + '0');
        }
    }
    reverse(res.begin(), res.end());
    res.erase(0, res.find_first_not_of('0'));//去掉前导零

    ret.values = res;
    return ret;
}

/*
两个正整数相乘
*/
BigInt BigInt::operator*(const BigInt& rhs)
{
    BigInt ret;
    string lvalues(values), rvalues(rhs.values);
    //处理0或结果正负
    if (lvalues == "0" || rvalues == "0")
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    if(flag==false||rhs.flag==false)
    {
        ret.flag=false;
    }
    //处理特殊情况
    unsigned int lsize, rsize;
    lsize = lvalues.size();
    rsize = rvalues.size();
    string temp;
    BigInt res, itemp;
    //让lvalues的长度最长
    if (lvalues < rvalues)
    {
        temp = lvalues;
        lvalues = rvalues;
        rvalues = temp;
        lsize = lvalues.size();
        rsize = rvalues.size();
    }
    //处理本质情况
    int i, j, n1, n2, n3, t;
    reverse(lvalues.begin(), lvalues.end());//颠倒字符串
    reverse(rvalues.begin(), rvalues.end());

    for (i = 0; i < rsize; i++)
    {
        temp = "";
        n1 = n2 = n3 = 0;
        for (j = 0; j < i; j++)
        {
            temp = temp + "0";
        }
        n3 = rvalues[i] - '0';
        for (j = 0; j < lsize; j++)
        {
            t = (n3*(lvalues[j] - '0') + n2);
            n1 = t % 10;//n1记录当前位置的值
            n2 = t / 10;//n2记录进位的值
            temp = temp + char(n1 + '0');
        }
        if (n2)
        {
            temp = temp + char(n2 + '0');
        }
        reverse(temp.begin(), temp.end());
        itemp.values = temp;
        res = res + itemp;
    }

    ret.values = res.values;
    return ret;
}
/*
两个正整数相除
*/
BigInt BigInt::operator/(const BigInt& rhs)
{
    BigInt ret;
    string lvalues(values), rvalues(rhs.values);
    string quotient;
    string temp;
    //处理特殊情况
    if(rvalues == "0")
    {
        ret.values = "error";//输出错误
        ret.flag = true;
        return ret;
    }
    if(lvalues == "0")
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }

    if(compare(lvalues, rvalues) < 0)
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    else if(compare(lvalues, rvalues) == 0)
    {
        ret.values = "1";
        ret.flag = true;
        return ret;
    }
    else
    {
        //处理本质情况

        unsigned int lsize, rsize;
        lsize = lvalues.size();
        rsize = rvalues.size();
        int i;
        if(rsize > 1) temp.append(lvalues, 0, rsize-1);
        for(i = rsize - 1; i < lsize; i++)
        {
            temp = temp + lvalues[i];
            //试商
            for(char c = '9'; c >= '0'; c--)
            {
                BigInt t = (BigInt)rvalues * (BigInt)string(1, c);
                BigInt s = (BigInt)temp - t;

                if(s.flag == true)
                {
                    temp = s.values;
                    quotient = quotient + c;
                    break;
                }
            }
        }
    }
    //去除前导零
    quotient.erase(0, quotient.find_first_not_of('0'));
    ret.values = quotient;
    ret.flag = true;
    return ret;
}
/*
两个正整数取余
*/
BigInt BigInt::operator%(const BigInt& rhs)
{
    BigInt ret,kj(values),ki(rhs.values);
    string lvalues(values), rvalues(rhs.values);
    string quotient;
    string temp;
    //处理特殊情况
    if(rvalues == "0")
    {
        ret.values = "error";//输出错误
        ret.flag = true;
        return ret;
    }
    if(lvalues == "0")
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }

    if(compare(lvalues, rvalues) < 0)
    {
        if(flag==false)
        {
            ret.values=(ki-kj).values;
            ret.flag = true;
            return ret;
        }else{
            ret.values = lvalues;
            ret.flag = true;
            return ret;
        }
    }
    else if(compare(lvalues, rvalues) == 0)
    {
        ret.values = "0";
        ret.flag = true;
        return ret;
    }
    else
    {
        //处理本质情况
        unsigned int lsize, rsize;
        lsize = lvalues.size();
        rsize = rvalues.size();
        int i;
        if(rsize > 1) temp.append(lvalues, 0, rsize-1);
        for(i = rsize - 1; i < lsize; i++)
        {
            if(temp=="0"){
                temp=lvalues[i];
            }else{
                temp = temp + lvalues[i];
            }
            //试商
            for(char c = '9'; c >= '0'; c--)
            {
                BigInt t = (BigInt)rvalues * (BigInt)string(1, c);
                BigInt s = (BigInt)temp - t;

                if(s.flag == true)
                {
                    //cout<<s.values<<endl;
                    temp = s.values;
                    quotient = quotient + c;
                    break;
                }
            }
        }
    }
    //去除前导零
    quotient.erase(0, quotient.find_first_not_of('0'));
    ret.values = temp;
    ret.flag = true;
    return ret;
}
/*
一个大整数和一个小整数的取余
int divMod(string ch,int num)
{
    int s=0;
    for(int i=0;ch[i]!='\0';i++)
    s=(s*10+ch[i]-'0')%num;
    return s;
}*/

/*
欧几里德求GCD
*/
BigInt gcd(BigInt a,BigInt b)
{
    BigInt stemp;
    //cout<<a<<endl;
    //cout<<b<<endl;
    if((a-b).flag==false)//判断大小
    {
        stemp.values=a.values;
        a.values=b.values;
        b.values=stemp.values;
    }
    if(b.values=="0") return a;
    else return gcd(b,a%b);
}
/*
快速幂
*/
BigInt fast(BigInt a,BigInt b)
{
    BigInt aa=a,t("1"),k("2");
 //   int b2=atoi(b1[lsize-1].c_str());
    while(b.values!="0")
    {
        if((b%k).values!="0")
        {
            t=t*aa;
        }
        aa=aa*aa;
        b=b/k;
    }
    return t;
}
/*
快速幂模
*/
BigInt mod_fast(BigInt a,BigInt b,BigInt p)
{
    BigInt aa=a,t("1"),k("2");
 //   int b2=atoi(b1[lsize-1].c_str());
    while(b.values!="0")
    {
        if((b%k).values!="0")
        {
            t=(t%p)*(aa%p)%p;
        }
        aa=(aa%p)*(aa%p)%p;
        b=b/k;
    }
    return t%p;
}

/*
扩展欧几里德实现乘法逆
*/
BigInt extgcd(BigInt a, BigInt b, BigInt& x, BigInt& y)
{
    BigInt d(a.values);

    if(b.values != "0"){
        d = extgcd(b, a % b, y, x);
        y = y-(a / b) * x;
 //   cout<<"a:"<<a<<endl;
  //  cout<<"b:"<<b<<endl;
  //  cout<<"x:"<<x<<endl;
  //  cout<<"y:"<<y<<endl<<endl<<endl;
    }else {
        x.values = "1";
        y.values = "0";
    }
    return d;
}
BigInt mod_inverse(BigInt a, BigInt m)
{
    BigInt x, y;
    extgcd(a, m, x, y);
    if(x.flag==false)
    {
        x.flag=true;
        x=m-x;
    }
    return (m + x % m) % m;
}


/*BigInt trans_H(BigInt str)
{
    int i,j,k;
    j=strlen(str.vales)-1;
    for(i=0;i<j;i++,j--)
    {
        k = str.values[i];
        str.values[i] = str.values[j];
        str.values[j] = k;
    }
    BigInt m;
    BigInt H;
    H.values="16"
    m.values = "0";
    for(i=0;i<j;i++)
    {
        m.values=str.values[i] *
    }

    printf("%s\n",str);
}*/
#endif // BIGINT_H_INCLUDED




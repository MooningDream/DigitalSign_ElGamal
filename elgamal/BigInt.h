#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>//reverse����������ӵ�ͷ�ļ�
using namespace std;
/*
��������
*/
class BigInt
{
    private:
        inline int compare(string s1, string s2)  //�ַ����Ƚ�
        {
            if(s1.size() < s2.size())
                return -1;
            else if(s1.size() > s2.size())
                return 1;
            else
                return s1.compare(s2);
        }
    public:
        bool flag;//true��ʾ������false��ʾ������0Ĭ��Ϊ����
        string values;//��������λ�ϵ�����
        BigInt():values("0"),flag(true){};//���캯��
        BigInt(string str)//����ת�����캯��(Ĭ��Ϊ������)
        {
            values = str;
            flag = true;
        }
    public:
        friend ostream& operator << (ostream& os, const BigInt& bigInt);//�������������
        friend istream& operator>>(istream& is, BigInt& bigInt);//�������������
        BigInt operator+(const BigInt& rhs);//�ӷ���������
        BigInt operator-(const BigInt& rhs);//������������
        BigInt operator*(const BigInt& rhs);//�˷���������
        BigInt operator/(const BigInt& rhs);//������������
        BigInt operator%(const BigInt& rhs);//�����������
};
/*
��������ȡ�����'>>'�����һ������
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
���������������'>>'������һ��������
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
�������������
*/
BigInt BigInt::operator+(const BigInt& rhs)
{
    BigInt ret;
    ret.flag = true;//��������Ӻ�Ϊ����
    string lvalues(values), rvalues(rhs.values);
    //�����������
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
    //����s1��s2�ĳ���
    unsigned int i, lsize, rsize;
    lsize = lvalues.size();
    rsize = rvalues.size();
    if (lsize < rsize)
    {
        for (i = 0; i < rsize - lsize; i++)//��lvalues��߲���
        {
            lvalues = "0" + lvalues;
        }
    }
    else
    {
        for (i = 0; i < lsize - rsize; i++)//��rvalues��߲���
        {
            rvalues = "0" + rvalues;
        }
    }
    //���������
    int n1, n2;
    n2 = 0;
    lsize = lvalues.size();
    string res = "";
    reverse(lvalues.begin(), lvalues.end());//�ߵ��ַ������Է���ӵ�λ�������
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < lsize; i++)
    {
        n1 = (lvalues[i] - '0' + rvalues[i] - '0' + n2) % 10;//n1����ǰλ��ֵ
        n2 = (lvalues[i] - '0' + rvalues[i] - '0' + n2) / 10;//n2�����λ
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
�������������
*/
BigInt BigInt::operator-(const BigInt& rhs)
{
    BigInt ret;
    string lvalues(values), rvalues(rhs.values);
    //����������
    if(flag==false&&rhs.flag==false)
    {
        string tmp = lvalues;
        lvalues = rvalues;
        rvalues = tmp;
    }
    //����������
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
        //�����������
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
    //����s1��s2�ĳ���
    unsigned int i, lsize, rsize;
    lsize = lvalues.size();
    rsize = rvalues.size();
    if (lsize < rsize)
    {
        for (i = 0; i < rsize - lsize; i++)//��lvalues��߲���
        {
            lvalues = "0" + lvalues;
        }
    }
    else
    {
        for (i = 0; i < lsize - rsize; i++)//��rvalues��߲���
        {
            rvalues = "0" + rvalues;
        }
    }
    //����ʹ��-����ǰ�ߵ������ں�ߵ���
    int t = lvalues.compare(rvalues);//��ȷ���0��str1<str2���ظ�����str1>str2��������
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
    //���������
    unsigned int j;
    lsize = lvalues.size();
    string res = "";
    reverse(lvalues.begin(), lvalues.end());//�ߵ��ַ������Է���ӵ�λ�������
    reverse(rvalues.begin(), rvalues.end());
    for (i = 0; i < lsize; i++)
    {
        if (lvalues[i] < rvalues[i])//���㣬��ǰ��һά
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
    res.erase(0, res.find_first_not_of('0'));//ȥ��ǰ����

    ret.values = res;
    return ret;
}

/*
�������������
*/
BigInt BigInt::operator*(const BigInt& rhs)
{
    BigInt ret;
    string lvalues(values), rvalues(rhs.values);
    //����0��������
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
    //�����������
    unsigned int lsize, rsize;
    lsize = lvalues.size();
    rsize = rvalues.size();
    string temp;
    BigInt res, itemp;
    //��lvalues�ĳ����
    if (lvalues < rvalues)
    {
        temp = lvalues;
        lvalues = rvalues;
        rvalues = temp;
        lsize = lvalues.size();
        rsize = rvalues.size();
    }
    //���������
    int i, j, n1, n2, n3, t;
    reverse(lvalues.begin(), lvalues.end());//�ߵ��ַ���
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
            n1 = t % 10;//n1��¼��ǰλ�õ�ֵ
            n2 = t / 10;//n2��¼��λ��ֵ
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
�������������
*/
BigInt BigInt::operator/(const BigInt& rhs)
{
    BigInt ret;
    string lvalues(values), rvalues(rhs.values);
    string quotient;
    string temp;
    //�����������
    if(rvalues == "0")
    {
        ret.values = "error";//�������
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
        //���������

        unsigned int lsize, rsize;
        lsize = lvalues.size();
        rsize = rvalues.size();
        int i;
        if(rsize > 1) temp.append(lvalues, 0, rsize-1);
        for(i = rsize - 1; i < lsize; i++)
        {
            temp = temp + lvalues[i];
            //����
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
    //ȥ��ǰ����
    quotient.erase(0, quotient.find_first_not_of('0'));
    ret.values = quotient;
    ret.flag = true;
    return ret;
}
/*
����������ȡ��
*/
BigInt BigInt::operator%(const BigInt& rhs)
{
    BigInt ret,kj(values),ki(rhs.values);
    string lvalues(values), rvalues(rhs.values);
    string quotient;
    string temp;
    //�����������
    if(rvalues == "0")
    {
        ret.values = "error";//�������
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
        //���������
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
            //����
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
    //ȥ��ǰ����
    quotient.erase(0, quotient.find_first_not_of('0'));
    ret.values = temp;
    ret.flag = true;
    return ret;
}
/*
һ����������һ��С������ȡ��
int divMod(string ch,int num)
{
    int s=0;
    for(int i=0;ch[i]!='\0';i++)
    s=(s*10+ch[i]-'0')%num;
    return s;
}*/

/*
ŷ�������GCD
*/
BigInt gcd(BigInt a,BigInt b)
{
    BigInt stemp;
    //cout<<a<<endl;
    //cout<<b<<endl;
    if((a-b).flag==false)//�жϴ�С
    {
        stemp.values=a.values;
        a.values=b.values;
        b.values=stemp.values;
    }
    if(b.values=="0") return a;
    else return gcd(b,a%b);
}
/*
������
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
������ģ
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
��չŷ�����ʵ�ֳ˷���
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




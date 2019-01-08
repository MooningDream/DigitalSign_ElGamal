#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

// ����α����
const int MAX_ROW = 50;
size_t Pseudoprime()
{
    bool ifprime = false;
    size_t a = 0;
    int arr[MAX_ROW];   //����arrΪ{3��4��5��6...52}
    for (int i = 0; i<MAX_ROW; ++i)
    {
        arr[i] = i+3;
    }
    while (!ifprime)
    {
        srand((unsigned)time(0));
        ifprime = true;
        a = (rand()%10000)*2+3; //����һ����Χ��3��2003�������
        for (int j = 0; j<MAX_ROW; ++j)
        {
            if (a%arr[j] == 0)
            {
                ifprime = false;
                break;
            }
        }
    }
    return a;
}

size_t  repeatMod(size_t base, size_t n, size_t mod)//ģ�ظ�ƽ���㷨��(b^n)%m
{
    size_t a = 1;
    while(n)
    {
        if(n&1)
        {
            a = (a*base)%mod;
        }
        base = (base*base)%mod;
        n = n>>1;
    }
    return a;
}

//Miller-Rabin�������
bool rabinmiller(size_t n, size_t k)
{

    int s = 0;
    int temp = n-1;      
    while ((temp & 0x1) == 0 && temp)
    {
        temp = temp>>1;
        s++;
    }   //��n-1��ʾΪ(2^s)*t
    size_t t = temp;

    while(k--)  //�ж�k�����и��ʲ�����(1/4)^k
    {
        srand((unsigned)time(0));
        size_t b = rand()%(n-2)+2; //����һ��b(2��a ��n-2)

        size_t y = repeatMod(b,t,n); 
        if (y == 1 || y == (n-1))
            return true;
        for(int j = 1; j<=(s-1) && y != (n-1); ++j)
        {
            y = repeatMod(y,2,n);
            if (y == 1)
                return false;
        }
        if ( y != (n-1))
            return false;
    }
    return true;
}
//�򵥵�������ⷽ��
bool isprime(size_t n)
{
    if( n== 2)
    return true;
    for(int i = 2; i <=(int)sqrt((float)n) ; ++i)
    {
        if (n%i == 0)
            return false;
    }
    return true;
}
int main()
{
    size_t ret = Pseudoprime();
    cout<<ret<<endl;

    if (rabinmiller(ret,10))
        cout<<ret<<"������"<<endl;
    else
        cout<<ret<<"��������"<<endl;

    if (isprime(ret))
        cout<<ret<<"������"<<endl;
    else
        cout<<ret<<"��������"<<endl;

    return 0;
}


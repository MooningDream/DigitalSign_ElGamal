#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

// 生成伪素数
const int MAX_ROW = 50;
size_t Pseudoprime()
{
    bool ifprime = false;
    size_t a = 0;
    int arr[MAX_ROW];   //数组arr为{3，4，5，6...52}
    for (int i = 0; i<MAX_ROW; ++i)
    {
        arr[i] = i+3;
    }
    while (!ifprime)
    {
        srand((unsigned)time(0));
        ifprime = true;
        a = (rand()%10000)*2+3; //生成一个范围在3到2003里的奇数
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

size_t  repeatMod(size_t base, size_t n, size_t mod)//模重复平方算法求(b^n)%m
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

//Miller-Rabin素数检测
bool rabinmiller(size_t n, size_t k)
{

    int s = 0;
    int temp = n-1;      
    while ((temp & 0x1) == 0 && temp)
    {
        temp = temp>>1;
        s++;
    }   //将n-1表示为(2^s)*t
    size_t t = temp;

    while(k--)  //判断k轮误判概率不大于(1/4)^k
    {
        srand((unsigned)time(0));
        size_t b = rand()%(n-2)+2; //生成一个b(2≤a ≤n-2)

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
//简单的素数检测方法
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
        cout<<ret<<"是素数"<<endl;
    else
        cout<<ret<<"不是素数"<<endl;

    if (isprime(ret))
        cout<<ret<<"是素数"<<endl;
    else
        cout<<ret<<"不是素数"<<endl;

    return 0;
}


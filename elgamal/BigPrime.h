#ifndef BIGPRIME_H_INCLUDED
#define BIGPRIME_H_INCLUDED

#include<time.h>
#include<iostream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define SIZE 33

typedef struct Bigint
{
	unsigned char num[SIZE];
}Bigint;

typedef struct Bigint2
{
	unsigned char num[2*SIZE];
}Bigint2;


//初始化
Bigint Init(unsigned char str[], int length);
//复制
void Copy(Bigint &a, Bigint b);
//打印输出
void Print(Bigint a);
//计算长度
int Length(Bigint a);
int Length(Bigint2 a);
//比较大小
int Compare(Bigint a, Bigint b); //a>b,a=b,a<b分别输出1,0,-1
int Compare(Bigint2 a, Bigint2 b);
//左移loop个字节
Bigint MoveLeft(Bigint a, int loop);
Bigint2 MoveLeft(Bigint2 a, int loop);
//右移一个比特
void BitMoveRight(Bigint &a);
//扩充数组
Bigint2 Extend(Bigint a);
//截断数组
Bigint Narrow(Bigint2 a);
//生成随机数
Bigint BigRand(Bigint n);
Bigint BigRand(int bytes);

//基本运算
Bigint Add(Bigint a, Bigint b); // 加法: 输入a,b, 返回 a + b
Bigint2 Add(Bigint2 a, Bigint2 b); // 加法: 输入a,b, 返回 a + b
Bigint Sub(Bigint a, Bigint b); // 减法: 输入a>b, 返回 a - b
Bigint2 Sub(Bigint2 a, Bigint2 b); // 减法: 输入a>b, 返回 a - b
Bigint2 Mul(Bigint a, Bigint b); // 乘法: 输入a,b, 返回 a * b
Bigint Div(Bigint a, Bigint b); // 除法: 输入a,b, 返回 a / b
Bigint Mod(Bigint a, Bigint b); // 求余: 输入a,b, 返回 a % b

Bigint AddMod(Bigint a, Bigint b, Bigint n); // 模加: 输入a,b,模数n,返回 a + b mod n
Bigint SubMod(Bigint a, Bigint b, Bigint n); // 模减: 输入a>b,模数n,返回 a - b mod n
Bigint Sub2Mod(Bigint a, Bigint b, Bigint n); // 模减: 输入a,b,模数n,返回 a - b mod n
Bigint MulMod(Bigint a, Bigint b, Bigint n); // 模乘: 输入a,b,模数n,返回 a * b mod n
Bigint PowMod(Bigint a, Bigint b, Bigint n); // 模幂：输入a,b,模数n,返回 a ^ b mod n

//MillerRabin素性检测
bool MillerRabinKnl(Bigint &n);
bool MillerRabin(Bigint &n, long loop);
//生成bytes素数
Bigint GenPrime(int bytes);
//生成公私钥

Bigint Init(unsigned char str[], int length)
{
	Bigint res;
	if(length > SIZE)
	{
		length = SIZE;
	}
	int i;
	for(i = 0; i<length; i++)
		res.num[i] = str[length-1-i];
	for(i = length; i<SIZE; i++)
		res.num[i] = 0;
	return res;
}

void Copy(Bigint &a, Bigint b)
{
	for(int i = 0; i < SIZE; i++)
		a.num[i] = b.num[i];
}


/*
void Print_A(Bigint a)
{
	cout<<"该数字的数组形式是:"<<endl;

	if(Length(a) == 0)
		cout<<0<<endl;
	else
	{
		for(int i = Length(a)-1;i>=0;i--)
			cout<<dec<<uctoi(a.num[i])<<" ";
	}
	cout<<endl;
}
*/
/*
void Print_A(Bigint2 a)
{
	cout<<"该数字的数组形式是:"<<endl;

	if(Length(a) == 0)
		cout<<0<<endl;
	else
	{
		for(int i = Length(a)-1;i>=0;i--)
			cout<<dec<<uctoi(a.num[i])<<" ";
	}
	cout<<endl;
}
*/

void Print(Bigint a)
{
	int res[310];

	int i = 0;

	Bigint b = {0};
	Bigint c = {10};
	while(Compare(a,b) == 1)
	{
		res[i] = Mod(a,c).num[0];
		a = Div(a,c);
		i++;
	}
//	cout<<"该数字是:"<<endl;
	for(int j = i-1; j>=0; j--)
	{
		cout<<res[j];
	}
	cout<<endl;
}

int uctoi(unsigned char str)
{
	int res = 0;
	for(int i = 0; i<8;i++)
	{
		res = res + (((str>>i) & 1)<<i);
	}
	return res;
}

int Length(Bigint a)
{
	int i = SIZE-1;
	while(a.num[i] == 0 && i>=0)
	{
		i--;
	}
	return i + 1;
}

int Length(Bigint2 a)
{
	int i = 2*SIZE-1;
	while(a.num[i] == 0 && i>=0)
	{
		i--;
	}
	return i + 1;
}

int Compare(Bigint a, Bigint b)
{
	int a_len = Length(a);
	int b_len = Length(b);
	int max;
	if(a_len > b_len)
		max = a_len;
	else
		max = b_len;

	if( max == 0)
		return 0;
	else
	{
		for(int i = max-1; i >= 0; i--)
		{
			if(a.num[i] > b.num[i])
				return 1;
			if(a.num[i] < b.num[i])
				return -1;
		}
	}
	return 0;
}

int Compare(Bigint2 a, Bigint2 b)
{
	int a_len = Length(a);
	int b_len = Length(b);
	int max;
	if(a_len > b_len)
		max = a_len;
	else
		max = b_len;

	if( max == 0)
		return 0;
	else
	{
		for(int i = max-1; i >= 0; i--)
		{
			if(a.num[i] > b.num[i])
				return 1;
			if(a.num[i] < b.num[i])
				return -1;
		}
	}
	return 0;
}

Bigint MoveLeft(Bigint a, int loop)
{
	for(int i = Length(a)-1; i >= 0; i-- )
	{
		if( i + loop >= SIZE )
			continue;
		a.num[i + loop] = a.num[i];
	}
	for(int i = loop-1; i>=0; i--)
		a.num[i] = 0;
	return a;
}

Bigint2 MoveLeft(Bigint2 a, int loop)
{
	for(int i = Length(a)-1; i >= 0; i-- )
	{
		if( i + loop >= 2 * SIZE )
			continue;
		a.num[i + loop] = a.num[i];
	}
	for(int i = loop-1; i>=0; i--)
		a.num[i] = 0;
	return a;
}

void BitMoveRight(Bigint &a)
{
	a.num[0] = a.num[0] >> 1;
	int flag;
	for(int i = 1; i < SIZE; i++ )
	{
		flag = (a.num[i] & 0x01)<<7;
		a.num[i-1] = a.num[i-1] + flag;
		a.num[i] = a.num[i] >> 1;
	}
}


Bigint2 Extend(Bigint a)
{
	Bigint2 res = {0};
	for(int i = 0; i < SIZE; i++)
		res.num[i] = a.num[i];
	return res;
}

Bigint Narrow(Bigint2 a)
{
	Bigint res = {0};
	for(int i = 0; i < SIZE; i++)
		res.num[i] = a.num[i];
	return res;
}

Bigint BigRand(Bigint n)
{
	Bigint res = {0};
	for(int i = 0; i < SIZE; i++)
	{
		res.num[i] = rand() % 256;
	}
	res = Mod(res, n);
	return res;

}

Bigint BigRand(int bytes)
{
	Bigint res = {0};
	for(int i = 0; i < bytes-1; i++)
	{
		res.num[i] = rand() % 256;
	}
	res.num[bytes-1] = 128 + rand() % 128;
	if( !(res.num[0] & 0x01))
		res.num[0] = res.num[0] + 1;
	return res;
}

Bigint Add(Bigint a, Bigint b)
{
	Bigint c;
	unsigned short temp;
	unsigned char carry = 0;
	for(int i=0; i<SIZE;i++)
	{
		temp = a.num[i] + b.num[i] + carry;
		c.num[i] = temp & 0x00ff;
		carry = (temp >> 8) & 0xff;
	}
	return c;
}

Bigint Sub(Bigint a, Bigint b)
{
	if( Compare(a,b) == -1 )
	{
		cout<<"subtract error";
		return a;
	}
	Bigint c;
	short temp;
	unsigned char carry = 0;
	for(int i=0; i<SIZE;i++)
	{
		temp = a.num[i] - b.num[i] - carry;
		c.num[i] = temp & 0x00ff;
		carry = (temp >> 15) & 0x01;
	}
	return c;
}

Bigint2 Sub(Bigint2 a, Bigint2 b)
{
	if( Compare(a,b) == -1 )
	{
		cout<<"subtract error";
		return a;
	}
	Bigint2 c;
	short temp;
	unsigned char carry = 0;
	for(int i=0; i<2*SIZE;i++)
	{
		temp = a.num[i] - b.num[i] - carry;
		c.num[i] = temp & 0x00ff;
		carry = (temp >> 15) & 0x01;
	}
	return c;
}



Bigint2 Mul(Bigint a, Bigint b)
{
	Bigint2 c ={0};
	unsigned short temp;
	unsigned char carry;
	for(int i = 0; i < SIZE; i++)
	{
		carry = 0;
		for(int j = 0; j < SIZE; j++)
		{
			temp = a.num[i] * b.num[j] + c.num[i+j] + carry;
			c.num[i+j] = temp & 0x00ff;
			carry = (temp >> 8) & 0xff;
		}
	}
	c.num[2*SIZE - 1] = carry;
	return c;
}




Bigint Div(Bigint a, Bigint b)
{
	Bigint B = {0};
	Bigint c = {0};
	int len = Length(a) - Length(b);

	while(len >= 0)
	{
		B = MoveLeft(b,len);
		while( Compare(a,B) >= 0)
		{
			a = Sub(a,B);
			c.num[len]++;
		}
		len--;
	}
	return c;
}



Bigint Mod(Bigint a, Bigint b)
{
	if(Compare(a,b) < 0)
		return a;
	else
	{
		Bigint B = {0};
		int len = Length(a)-Length(b);

		while(len >= 0)
		{
			B = MoveLeft(b,len);
			while( Compare(a,B) >= 0)
				a = Sub(a,B);
			len--;
		}
		return a;
	}
}

Bigint2 Mod(Bigint2 a, Bigint2 b)
{
	if(Compare(a,b) < 0)
		return a;
	else
	{
		Bigint2 B = {0};
		int len = Length(a)-Length(b);

		while(len >= 0)
		{
			B = MoveLeft(b,len);
			while( Compare(a,B) >= 0)
				a = Sub(a,B);
			len--;
		}
		return a;
	}
}



Bigint AddMod(Bigint a, Bigint b, Bigint n)
{
	Bigint res;
	res = Add(a,b);
	return Mod(res,n);
}

Bigint SubMod(Bigint a, Bigint b, Bigint n)
{
	Bigint res;
	res = Sub(a,b);
	return Mod(res,n);
}

Bigint Sub2Mod(Bigint a, Bigint b, Bigint n)
{
	Bigint res;
	while(Compare(a,b)<0)
		a = Add(a,n);
	res = Sub(a,b);
	return res;
}


Bigint MulMod(Bigint a, Bigint b, Bigint n)
{
	Bigint2 res;
	res = Mul(a,b);
	return Narrow(Mod(res,Extend(n)));
}

Bigint PowMod(Bigint a, Bigint b, Bigint n)
{
	Bigint c = {1};
	Bigint temp = {1};
	while(Length(b) > 0)
	{
		while(!(b.num[0] & 1))
		{
			BitMoveRight(b);
			a = MulMod(a,a,n);
		}
		b = Sub(b,temp);
		c = MulMod(a,c,n);
	}
	return c;
}

bool MillerRabinKnl(Bigint &n)
{
	Bigint b,m,v,temp;
	Bigint j = {0};
	Bigint one = {1};
	Bigint two = {2};
	Bigint three = {3};
	m = Sub(n,one);
	while(!(m.num[0] & 0x01))
	{
		j = Add(j,one);
		BitMoveRight(m);
	}
	b = Add(two, BigRand(Sub(n,three)));
	v = PowMod(b,m,n);
	if(Compare(v,one) == 0)
		return 1;

	Bigint i = {1};

	temp = Sub(n,one);
	while(Compare(v,temp) < 0)
	{
		if(Compare(i,j) == 0)
			return 0;
		v = MulMod(v,v,n);
		i = Add(i,one);
	}
	return 1;
}

bool MillerRabin(Bigint &n,long loop)
{
	for(long i = 0; i<loop;i++)
	{
		if(!MillerRabinKnl(n))
			return 0;
	}
	return 1;
}

Bigint GenPrime(int bytes)
{
	Bigint res = BigRand(bytes);
//	Print(res);
	long loop = 20;
	long count = 0;
	while(!MillerRabin(res, loop))
	{
		res = BigRand(bytes);
//		Print(res);
		count ++;
	}
//	cout<<count<<endl;
	return res;

}

void getPrime (int i)
{
	//生成大素数
	cout<<"生成大素数:"<<endl;
	Bigint p1 = GenPrime(i);
	cout<<"p=";Print(p1);
	//Bigint p2 = GenPrime(i);
	//cout<<"p2=";Print(p2);
	cout<<endl;
}


#endif // BIGPRIME_H_INCLUDED

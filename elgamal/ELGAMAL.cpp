#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
/*
 * 全局参数
 * p：生成的大整数
 * g：p的素根
 * y：g^d次方
 * d：私钥
 */
mpz_t p,g,y,d;
/*
 * C1,C2 密文的两部分
 * m 明文
 */
mpz_t C1, C2;
mpz_t m;
/*
 * 使用了gmp库，这里是一些函数介绍
 * 素数判断：
 * int mpz_probab_prime_p (mpz_t n, int reps)
 * 判断 n 是否为素数,若 n 确定是素数则返回 2,如果 n 是概率素数 (不能完全
 * 确定) 那么返回 1,或者如果 n 确定是合数那么返回 0。
 * 这个函数首先做一些试除,然后再作 Miller-Rabin 概率素性判别。reps 控制这
 * 样的判别做多少次,5 到 10 是较合理的数值,更多次的判别可以减小合数被返
 * 回为概率素数的可能。
 * 调用 Miller-Rabin 判别和其他相似的判别组成的复合判别可能更为合理。判别
 * 失败的数可以知道是合数,但是通过判别的数可以是素数也可能是合数。只有
 * 极少数的合数可以通过判别,因此通过判别的数一般都被认为是素数。
 *
 * 随机数函数：
 * void mpz_urandomb(mpz_t rop,gmp_randstate_t state,unsigned long int n) [函数]
 * 产生一个均匀分布在 0 到 2^n − 1(包含) 范围内的随机整数。
 * 在激活这个函数之前必须先调用某个 gmp_randinit 函数对变量 state 进行初始化。
 *
 * 随机状态初始化：
 * void gmp_randinit_default (gmp_randstate_t state)  [函数]
 * 用默认算法初始化 state。这是速度与随机性之间的权衡,建议没有特殊要求的
 * 应用使用它。
 *
 * 输入：bits
 * 输出：生成一个范围在0~2^n - 1 的随机素数
 */
void random_prime(unsigned long int bits){
  gmp_randstate_t state;
  gmp_randinit_default(state);
  mpz_init(p);
  while(1){
    mpz_urandomb(p,state,bits);
    if(mpz_probab_prime_p(p,10) != 0)return;
  }
  return;
}
/*
 * 求本原根的算法
 * int mpz_init_set_str (mpz_t rop, char *str, int base) 赋值
 * void mpz_add (mpz_t rop, mpz_t op1, mpz_t op2) rop = op1 + op2
 * 输入：p
 * 输出：p的素根
 */
void root_nums(){
  const char* str = "1";
  const char* str2 = "2";
  mpz_t a,b,c;
  mpz_init(a);
  mpz_init(b);
  mpz_init(c);
  mpz_init_set_str(b,str,10);// b = 1; b作为累加的值
  mpz_init_set_str(a,str2,10);// a = 2;相当于累加器
  mpz_init_set_str(c,str2,10);// c = a;用于计算
  const int tempNum = 100;
  mpz_t temp[tempNum];
  for(int i = 0 ; i < tempNum ; i++){
    mpz_init(temp[i]);
  }
  int i,tempLength;//tempLength = 0;// temp数组中有意义的值的数量
  while(1){
    // 判断是否是本原根，如果是则返回，否则判断下一个数
    mpz_init_set(temp[0],a);
    mpz_init_set(c,a);
    for(i = 0 , tempLength = 1 ; i < tempNum ; ){
      mpz_mul(c,a,c);
      for(i = 0 ; i < tempLength ; i++){
        if(mpz_cmp(temp[i],c) ==0){
          break;
        }
      }
      if(i == tempLength){
        mpz_init_set(temp[tempLength++],c);
      }else {
        for(int k = 0 ; k < tempLength ; k++){
          mpz_init(temp[k]);
        }
        break;
      }
      if(tempLength == tempNum){
        mpz_init_set(g,c);
        return;
      }
    }
    mpz_add(a,a,b);
  }
}
/*
 * bits是生成的随机数的位数，2^bits
 * p是生成的随机素数
 * g是素数p的素根
 * y是素根g^d次方
 * 则d是私钥, (p,g,y)是公钥
 * 输入：bits
 * 输出：公钥(p,g,y),私钥(d)
 */
void elgamal_keygen(unsigned long int bits){
  random_prime(bits);
  gmp_randstate_t state;
  gmp_randinit_default(state);
  mpz_urandomm(d,state,p);
  root_nums();
  // y = (g^d)mod p;
  mpz_powm(y,g,d,p);
}
/*
 * m：信息
 * p,g,y：公钥
 * 输入：信息(m),公钥(p,g,y)
 * 输出：信息(m)的密文(C1,C2)
 */
void elgamal_encrypt(){
  gmp_randstate_t state;
  gmp_randinit_default(state);
  mpz_t result;
  mpz_init(result);
  mpz_urandomm(result,state,p);// result 是生成的随机数
  mpz_t K;
  mpz_init(K);
  mpz_powm(K,y,result,p);
  mpz_powm(C1,g,result,p);
  mpz_mul(C2,K,m);
  mpz_mod(C2,C2,p);
}
/*
 * 输入：密文(C1,C2),私钥(d),共同选择的素数(p)
 * 输出：明文(m)
 */
void elgamal_decrypty(){
  mpz_t K;
  mpz_init(K);
  mpz_powm(K,C1,d,p);// K = (C1^d)mod p
  // 求K在p上的逆元
  mpz_invert(K,K,p);
  mpz_mul(C2,C2,K);
  mpz_mod(m,C2,p);
}

int main(){
  mpz_t p,g,y,d;
  mpz_init(p);
  mpz_init(g);
  mpz_init(y);
  mpz_init(d);
  mpz_init(C1);
  mpz_init(C2);
  mpz_init(m);

  char *message = (char*)malloc(13);
  char *temp = (char*)malloc(3 * 13 + 1);
  printf("please input some message: \n");
  while(1){
    int i = 0 , j = 0 , x = 0,len = 0;
    for(i = 0,j = 0 ; i < 12 ; i++){
      scanf("%c",&message[i]);
      if(message[i] == '\n')break;
      // 将信息表示成三位，按照ASCII码
      x = message[i];
      temp[j + 2] = x % 10 + 48;
      x /= 10;
      temp[j + 1] = x % 10 + 48;
      temp[j] = x/10 + 48;
      j += 3;
      len += 3;
    }
    // 第一位加上5，避免第一位是0
    temp[0] += 5;
    message[i + 1] = '\0';
    temp[j + 1] = '\0';
    mpz_init_set_str(m,temp,10);
    elgamal_keygen(128);
    elgamal_encrypt();
    gmp_printf("加密的结果是：(%Zd,%Zd)\n",C1,C2);
    elgamal_decrypty();
    char* r = mpz_get_str(temp,10,m);
    //  前面加了5，这里要去除
    temp[0] -= 5;
    for(i = 0,j = 0 ; i < 12 && j < len ; i++){
      x = ((temp[j] - 48) * 10 + temp[j + 1] - 48) * 10 + temp[j + 2] - 48;
      message[i] = x;
      j += 3;
    }
    message[len + 1] = '\0';
    printf("解密的结果是：%s\n",message);
  }
  free(message);
  free(temp);
  mpz_clear(p);
  mpz_clear(g);
  mpz_clear(y);
  mpz_clear(d);
  mpz_clear(C1);
  mpz_clear(C2);
  mpz_clear(m);
  return 0;
}

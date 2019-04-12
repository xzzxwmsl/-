//1、取第 i 位左边的数字（高位），乘以 10 ^(i-1) ，得到基础值 a 。
//2、取第 i 位数字，计算修正值：
//1、如果大于 X，则结果为 a+ 10 ^(i-1) 。
//2、如果小于 X，则结果为 a 。
//3、如果等 X，则取第 i 位右边（低位）数字，设为 b ，最后结果为 a+b+1 。
// 以上为无需考虑数是奇数的情况，是奇数的情况做剪枝即可 
// 条件为1时的可供参考解决方式： https://blog.csdn.net/u013132035/article/details/80768636 
#include<iostream>
#include<cmath>
using namespace std;
const string rr="441684627"; //答案2 
const long R=707829217; //两质数之和 
const long Re=866278171; //最终的两个质数组成的数字 
bool isPrime(long n){
	if(n<=1 || n%2 == 0) return false;
	long sqr=(long)sqrt(1.0*n);
	for(int i=3;i<=sqr;i=i+2){
		if(n%i==0) return false;
	}
	return true;
} 

void findR(){ // 寻找质数R1，R2 
	long r1,r2; 
	long i=1;
	while(i+=2){
		if(!isPrime(i)) continue; //不是质数
		long j=R/i;
		if(R%j!=0 || !isPrime(j) ) continue; // j不是质数或者R/i 有余数
		r1=i;
		r2=R/i;
		break;		
	}
	cout<<r1<<"*"<<r2<<"="<<r1*r2<<endl;
}

void findR2(){ //寻找奇数列中3出现的次数 
	long long result=0;
	for(int i=1;i<=9;i++){
		int t=Re/int(pow(10,i-1))%10;// 第i位数字 
		if(t<3 && i==9) continue; // 最高位小于3，不必再计算 
		long High=Re/long(pow(10,i));
		long Low=Re%long(pow(10,i));
		long a=High*pow(10,i-1); //第i位的高位数字 
		long b=Low%long(pow(10,i-1)); //第i位的低位数字 
		
		if(t>3){
			if(i==1){
				result+=a+1;
				continue;
			}
		    result=result+ (a + pow(10,i-1) )/2;
		}
		else if(t==3){
			if(i==1){
				result+=a+1;
				continue;
			} 
			
			if(b%2==0) result=result+a/2+b/2;
			else result=result+a/2+(b+1)/2;
		}
		else if(t<3){
			if(i==1){
				 result=result+a; 
			}else result = result + a/2;
		}
		
	} 
	
	cout<<result<<endl;
}

void findR3(){ //暴力法寻找奇数列中3出现的次数 
	long sum=0;
	for(int i=1;i<=Re;i=i+2){
		int t=i;
		while(t!=0){
			if(t%10==3) sum++;
			t/=10;
		}
	}
	cout<<sum<<endl;
}

int main(){
	findR(); 
	findR2();
//    findR3(); // 不怕的可以取消注释感受下暴力法的时间 ,粗略估计计算时间半分钟 
   
    return 0; 
}

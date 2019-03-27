#include<stdlib.h>
#include<stdio.h>
#include"miracl.h"
#include"mirdef.h"

#include"Function.h"

int bitLength = 50000;
int bitKind = 10;
//char *filePath = "input1.txt";
char *filePath = "input2.txt";
big equations[2][MaxLines];			//存储读取到的方程组参数
static int length = 0;

int main()
{
	miracl *mip = mirsys(bitLength, bitKind);	//初始化系统

	//初始化方程参数数组
	for (int i = 0; i < 2; i++)					
			for (int j = 0; j < MaxLines; j++)
			equations[i][j] = mirvar(0);

	//从文件读取方程组参数
	length = ReadEquations();

	//判断是否互素
	for (int i = 0; i < length-1; i++)
	{
		for (int j = length-1; j> i; j--)
		{
			//存在 mi 和 mj 不互素
			if (IsCoprime(equations[1][i], equations[1][j])==0)
			{
				printf("不能直接利用中国剩余定理\n");
				goto END;
			}
		}
	}

	big multiplication = CalculateMultiplication(length);		//存储m=m1*m2*m3*...*mn

	big Mj[MaxLines];			//存储Mj
	big reciprocal[MaxLines];	//存储Mj的逆元

	//计算逆元
	for (int i = 0; i < length; i++)
	{
		//计算Mj
		Mj[i] = mirvar(0);
		//subdiv(multiplication, equations[1][i], Mj[i]);				//计算Mj[i] = m / mi
		Mj[i]=CalculateMultiplicationExceptSomeone(length, i);		//计算Mj[i] = m / mi
		//计算逆元
		reciprocal[i] = mirvar(0);
		reciprocal[i] = CalculateReciprocal(Mj[i], equations[1][i]);
	}
	
	//计算结果
	big result = mirvar(0);
	for (int i = 0; i < length; i++)
	{
		result = CalculateMod(result, CalculateProductMod(Mj[i], reciprocal[i], equations[0][i], multiplication), multiplication);
	}

	//打印结果
	char resultString[maxNumberLength];												//存储余数字符串形式
	cotstr(result, resultString);
	char multiplicationString[maxNumberLength];										//存储模数字符串形式
	cotstr(multiplication, multiplicationString);
	printf("计算结果为: %s \n\nmod \n\n%s\n",resultString,multiplicationString);	//打印结果
	goto END;

	//判断完毕
END:
	system("pause");
	return 0;
}
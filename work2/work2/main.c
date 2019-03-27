#include<stdlib.h>
#include<stdio.h>
#include"miracl.h"
#include"mirdef.h"

#include"Function.h"

int bitLength = 50000;
int bitKind = 10;
//char *filePath = "input1.txt";
char *filePath = "input2.txt";
big equations[2][MaxLines];			//�洢��ȡ���ķ��������
static int length = 0;

int main()
{
	miracl *mip = mirsys(bitLength, bitKind);	//��ʼ��ϵͳ

	//��ʼ�����̲�������
	for (int i = 0; i < 2; i++)					
			for (int j = 0; j < MaxLines; j++)
			equations[i][j] = mirvar(0);

	//���ļ���ȡ���������
	length = ReadEquations();

	//�ж��Ƿ���
	for (int i = 0; i < length-1; i++)
	{
		for (int j = length-1; j> i; j--)
		{
			//���� mi �� mj ������
			if (IsCoprime(equations[1][i], equations[1][j])==0)
			{
				printf("����ֱ�������й�ʣ�ඨ��\n");
				goto END;
			}
		}
	}

	big multiplication = CalculateMultiplication(length);		//�洢m=m1*m2*m3*...*mn

	big Mj[MaxLines];			//�洢Mj
	big reciprocal[MaxLines];	//�洢Mj����Ԫ

	//������Ԫ
	for (int i = 0; i < length; i++)
	{
		//����Mj
		Mj[i] = mirvar(0);
		//subdiv(multiplication, equations[1][i], Mj[i]);				//����Mj[i] = m / mi
		Mj[i]=CalculateMultiplicationExceptSomeone(length, i);		//����Mj[i] = m / mi
		//������Ԫ
		reciprocal[i] = mirvar(0);
		reciprocal[i] = CalculateReciprocal(Mj[i], equations[1][i]);
	}
	
	//������
	big result = mirvar(0);
	for (int i = 0; i < length; i++)
	{
		result = CalculateMod(result, CalculateProductMod(Mj[i], reciprocal[i], equations[0][i], multiplication), multiplication);
	}

	//��ӡ���
	char resultString[maxNumberLength];												//�洢�����ַ�����ʽ
	cotstr(result, resultString);
	char multiplicationString[maxNumberLength];										//�洢ģ���ַ�����ʽ
	cotstr(multiplication, multiplicationString);
	printf("������Ϊ: %s \n\nmod \n\n%s\n",resultString,multiplicationString);	//��ӡ���
	goto END;

	//�ж����
END:
	system("pause");
	return 0;
}
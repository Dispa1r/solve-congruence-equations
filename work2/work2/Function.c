#define  _CRT_SECURE_NO_WARNINGS
#include "Function.h"
#include "miracl.h"
#include "mirdef.h"

int ReadEquations()
{
	miracl *mip = mirsys(bitLength, bitKind);
	FILE *fp = fopen(filePath, "r");
	char numberString[maxNumberLength];  //�ַ�����
	//big number = mirvar(0);  //��������
	big temp[100];			 //��������
	//�����ļ�������
	if (fp == NULL)
	{
		printf("���������ļ�������\n");
		system("pause");
		return -1;
	}
	//��ȡ�����ַ���
	int length = 0;
	while (fgets(numberString, 501, fp) != NULL)
	{
		temp[length] = mirvar(0);
		cinstr(temp[length], numberString);
		length++;
	}
	//�ر��ļ�
	fclose(fp);
	//a�ĸ�����m�����
	if (length % 2 != 0)
	{
		printf("���ݸ�������\n");
		system("pause");
		return 0;
	}
	int len = length / 2; //���������
	//an,mnװ���ά����
	for (int i = 0; i < length; i++)
	{
		if (i < len)
		{
			equations[0][i] = temp[i];
		}
		else
		{
			equations[1][i % len] = temp[i];
		}
	}
	return len;
}

int IsCoprime(big x, big y) 
{
	miracl *mip = mirsys(bitLength, bitKind);
	big z = mirvar(0);
	big s = mirvar(1);
	egcd(x, y, z);
	if (compare(z, s) == 0)    //���Լ��Ϊ1��˵����������
		return 1;
	else
		return 0;
}

big CalculateMultiplication(int length)
{
	miracl *mip = mirsys(bitLength, bitKind);
	big m = mirvar(1);		//������
	for (int i = 0; i < length; i++)
	{
		multiply(m, equations[1][i], m);
	}
	return m;
}

big CalculateReciprocal(big Mj, big mj)
{
	miracl *mip = mirsys(bitLength, bitKind);
	big x = mirvar(0);
	copy(Mj, x);
	big y = mirvar(0);
	copy(mj, y);
	xgcd(x, y, x, x, x);
	return x;
}

big CalculateProductMod(big a, big b, big c, big d) {
	miracl *mip = mirsys(bitLength, bitKind);
	big temp = mirvar(0);
	multiply(a, b, temp);
	multiply(temp, c, temp);
	divide(temp, d, d);
	return temp;
}

big CalculateMod(big a, big b, big d) {
	miracl *mip = mirsys(bitLength, bitKind);
	big temp = mirvar(0);
	add(a, b, temp);    // temp = a + b
	divide(temp, d, d); // temp = temp % d
	return temp;
}

big  CalculateMultiplicationExceptSomeone(int length, int j) 
{
	miracl *mip = mirsys(bitLength, bitKind);
	big m = mirvar(1);		//������
	for (int i = 0; i < length; i++)
	{
		if (i == j)
		{
			continue;
		}
		multiply(m, equations[1][i], m);
	}
	return m;
}
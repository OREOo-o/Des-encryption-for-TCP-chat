#include<iostream>
#include<windows.h>
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

using namespace  std;

#pragma comment(lib,"ws2_32.lib")
int IP[64] = { //��ʼ��λ��
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7
	};
 
	int E[48] = { //��չ��λ��
		32, 1, 2, 3, 4, 5,
		4, 5, 6, 7, 8, 9,
		8, 9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1 };
 
	int PC1[56] = { //PC1��λ��64��>56��
		57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4 };
 
	int movetable[16] = { //ѭ����λ��
		1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
 
	int PC2[48] = { //PC2��λ��56��>48��
		14, 17, 11, 24, 1, 5,
		3, 28, 15, 6, 21, 10,
		23, 19, 12, 4, 26, 8,
		16, 7, 27, 20, 13, 2,
		41, 52, 31, 37, 47, 55,
		30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53,
		46, 42, 50, 36, 29, 32 };
 
	int S1[4][16] = { //S��λ��
		14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
		0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
		4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
		15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
	};
	int S2[4][16] = {
		15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
		3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
		0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
		13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
	};
	int S3[4][16] = {
		10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
		13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
		13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
		1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
	};
	int S4[4][16] = {
		7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
		13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
	};
	int S5[4][16] = {
		2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
		14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
		4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
		11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
	};
	int S6[4][16] = {
		12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
		10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
		9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
		4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
	};
	int S7[4][16] = {
		4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
		13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
		1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
		6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
	};
	int S8[4][16] = {
		13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
		1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
		7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
		2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
	};
	int P[32] = { //P��λ��
		16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,
		2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25
	};

	char cleartext[104]; //����
	int CBC[64];
	int result[13][64];
	int H[208];
	char secretText[208];
	int C[832];
	int M[13][8];
	char group[8]; //���飬8���ַ�һ��
	char secKey[9]={1,2,3,4,5,6,7,8}; //�̶����㷨�İ�λ�ַ���ԿΪ12345678
	int text[64]; //���һ������ת�ɶ����ƺ������
	int IP_replace[64]; //��ŵ�һ�γ�ʼ��λ�Ľ��
	int L0[32], Li[32], R0[32], Ri[32];//������������Ҹ�32λ
	int RE0[48]; //�Ұ벿�־���E��任���48λ
	int key[64]; //��������Կ
	int PC1_key[56]; //��Կkey����PC1�任��56λ
	int A[28]; //PC1_key���󲿷֣��Ա����ѭ������
	int B[28];//PC1_key���Ҳ��֣��Ա����ѭ������
	int keyAB[56]; //�ϲ�ѭ�����ƺ������ֵĽ��
	int K[16][48]; //16��ѭ�����Ʋ���������Կ
	int RK[48]; //RE0���K�Ľ��
	int RKS[8]; //����8��S���õ���8��ʮ����
	int SP[32]; //��RKS���е�ʮ���ƻ��ɶ�����
	int RKSP[32]; //SP����P�л�λ��Ľ��
	int iter_replace[64]; //��ž�������32λ��λ��Ľ��
	int iter_result[14][64]; //��ų�ʼ�����������о���DES�ķ���Ķ�����
	char init[9] = { "Carlchan" }; //init��ʼ������Carlchan
	int t, i, j, k, l, m, n;
	int r[8], c[8];
	
 
	
 void start(){
		//��������Կ
		for (i = 0; i < 8; i++) //����Կת����64λ���������ŵ�һά����key��
		{
			int a[8] = { 0,0,0,0,0,0,0,0 };
			m = secKey[i];
			for (j = 0; m != 0; j++)
			{
				a[j] = m % 2;
				m = m / 2;
			}
			for (j = 0; j < 8; j++)
				key[(i * 8) + j] = a[7 - j];
		}

 
		for (i = 0; i < 56; i++) //ͨ��PC1��λ����56λ��Կ����PC1_key��
			PC1_key[i] = key[PC1[i] - 1];
 
		for (i = 0; i < 28; i++) //�ֳ�A��B�����֣���28λ
		{
			A[i] = PC1_key[i];
			B[i] = PC1_key[i + 28];
		}
 
		for (t = 0; t < 16; t++)
		{
			if (movetable[t] == 1) //����ѭ����λ��Ai��Bi�ֱ�����move[t]λ
			{
				n = A[0];
				for (i = 0; i < 27; i++)
					A[i] = A[i + 1];
				A[27] = n;
				n = B[0];
				for (i = 0; i < 28; i++)
					B[i] = B[i + 1];
				B[27] = n;
			}
			else
			{
				n = A[0];
				m = A[1];
				for (i = 0; i < 26; i++)
					A[i] = A[i + 2];
				A[26] = n;
				A[27] = m;
				n = B[0];
				m = B[1];
				for (i = 0; i < 26; i++)
					B[i] = B[i + 2];
				B[26] = n;
				B[27] = m;
			}
 
			for (i = 0; i < 28; i++) //��A��B�ϲ���56λ
			{
				keyAB[i] = A[i];
				keyAB[i + 28] = B[i];
			}
 
			for (i = 0; i < 48; i++) //ͨ��PC2��λ����48λ��Կ
				K[t][i] = keyAB[PC2[i] - 1];
		}
 
		for (i = 0; i < 8; i++) //����ʼ������ת���ɶ����������浽����iter_result�ĵ�һ����
		{
			int a[8] = { 0,0,0,0,0,0,0,0 };
			m = init[i];
			for (j = 0; m != 0; j++)
			{
				a[j] = m % 2;
				m = m / 2;
			}
			for (j = 0; j < 8; j++)
				iter_result[0][(i * 8) + j] = a[7 - j];
		}
 }
		//���ܳ���
 
		void encode(char* a){
			
			strcpy(cleartext,a);
			//CBCģʽ�µļ���
			i = 0; //������ÿ8���ַ���Ϊһ�����飬����n������
			n = 0;
			while (cleartext[i] != '\0')
			{
				n++;
				i++;
			}
			k = n % 8;
			n = (n - 1) / 8 + 1;
 
			for (l = 0; l < n; l++)
			{
				if (l == (n - 1) && k != 0)
				{//��ÿ�������8���ַ��ŵ�����group��
					for (i = 0; i < k; i++) 
						group[i] = cleartext[i + (8 * l)];
					for (i = k; i < 8; i++)
						group[i] = ' ';//������ÿո񲹳�λ��
				}
				else
					for (i = 0; i < 8; i++)
						group[i] = cleartext[i + (8 * l)];
               //���õ�������ת���ɶ����������浽����text��
				for (i = 0; i < 8; i++) 
				{
					int a[8] = { 0,0,0,0,0,0,0,0 };
					m = group[i];
					for (j = 0; m != 0; j++)
					{
						a[j] = m % 2;
						m = m / 2;
					}
					for (j = 0; j < 8; j++)
						text[(i * 8) + j] = a[7 - j];
				}
                //ǰһ������������ǰ����
				for (i = 0; i < 64; i++) 
					text[i] = iter_result[l][i] ^ text[i];
 
 
				for (i = 0; i < 64; i++) //��ʼ��λ
					IP_replace[i] = text[IP[i] - 1];
 
				for (i = 0; i < 32; i++) //���������ָ�32λ
				{
					L0[i] = IP_replace[i];
					R0[i] = IP_replace[i + 32];
				}
 
				//ʮ���ε���
 
				for (t = 0; t < 16; t++)
				{
					for (i = 0; i < 48; i++) 
						RE0[i] = R0[E[i] - 1];//�Ұ벿��32λͨ��E����չ��48λ
 
					for (i = 0; i < 48; i++) //RE0��K���
						RK[i] = RE0[i] ^ K[t][i];
 
					for (i = 0; i < 8; i++) //��R��K�������Ľ��ͨ��Sλ�Ʊ�
					{
						r[i] = RK[(i * 6) + 0] * 2 + RK[(i * 6) + 5];
						c[i] = RK[(i * 6) + 1] * 8 + RK[(i * 6) + 2] * 4 + RK[(i * 6) + 3] * 2 + RK[(i * 6) + 4];
					}
					RKS[0] = S1[r[0]][c[0]];
					RKS[1] = S2[r[1]][c[1]];
					RKS[2] = S3[r[2]][c[2]];
					RKS[3] = S4[r[3]][c[3]];
					RKS[4] = S5[r[4]][c[4]];
					RKS[5] = S6[r[5]][c[5]];
					RKS[6] = S7[r[6]][c[6]];
					RKS[7] = S8[r[7]][c[7]];
 
					for (i = 0; i < 8; i++) //���ת��32λ�����ƴ���SP��
					{
						int b[4] = { 0,0,0,0 };
						m = RKS[i];
						for (j = 3; m != 0; j--)
						{
							b[j] = m % 2;
							m = m / 2;
						}
						for (j = 0; j < 4; j++)
							SP[j + (i * 4)] = b[j];
					}
 
					for (i = 0; i < 32; i++) //�����ƽ���پ���һ��P�л�λ
						RKSP[i] = SP[P[i] - 1];
 
					for (i = 0; i < 32; i++) //��ǰһ�ε����õ������������㣬�õ����ε������ұ�
						Ri[i] = L0[i] ^ RKSP[i];
 
					for (i = 0; i < 32; i++)
					{
						L0[i] = R0[i];
						R0[i] = Ri[i];
					}
				}
 
				//һ������32λ����
				for (i = 0; i < 32; i++)
					Li[i] = R0[i];
				for (i = 0; i < 32; i++)
					R0[i] = L0[i];
				for (i = 0; i < 32; i++)
					L0[i] = Li[i];
 
				for (i = 0; i < 32; i++) //���������ֺ������浽iter_replace��
					iter_replace[i] = L0[i];
				for (i = 32; i < 64; i++)
					iter_replace[i] = R0[i - 32];
 
				for (i = 0; i < 64; i++) //���г�ʼ��λ�������
					iter_result[l + 1][IP[i] - 1] = iter_replace[i];
 
				for (i = 0; i < 64; i++)
					result[l][i] = iter_result[l + 1][i];
			}
			for (j = 0; j < n; j++) //�Ѷ�����resultת��ʮ���ƴ浽H��
				for (i = 0; i < 16; i++)
					H[i + (j * 16)] = result[j][0 + (i * 4)] * 8 + result[j][1 + (i * 4)] * 4 + result[j][2 + (i * 4)] * 2 + result[j][3 + (i * 4)];

			for (i = 0; i < n * 16; i++)
			{
				if (H[i] < 10)
					secretText[i] = H[i] + 48;
				else if (H[i] == 10)
					secretText[i] = 'A';
				else if (H[i] == 11)
					secretText[i] = 'B';
				else if (H[i] == 12)
					secretText[i] = 'C';
				else if (H[i] == 13)
					secretText[i] = 'D';
				else if (H[i] == 14)
					secretText[i] = 'E';
				else if (H[i] == 15)
					secretText[i] = 'F';
			}
			for (i = l * 16; i < 208; i++)
				secretText[i] = '\0';//ע������Խ��
 
		}
 
 
		//���ܳ���
        void decode(char* b){
			strcpy(secretText,b);
			for (i = 0; i < 208; i++)
				H[i] = 0;
 
			for (i = 0; secretText[i] != '\0'; i++) //ʮ����������ת����ʮ���ƴ����H��
			{
				if (secretText[i] >= '0' && secretText[i] <= '9')
					H[i] = secretText[i] - '0';
				else if (secretText[i] >= 'A' && secretText[i] <= 'F')
					H[i] = secretText[i] - 'A' + 10;
				else if (secretText[i] >= 'a' && secretText[i] <= 'f')
					H[i] = secretText[i] - 'a' + 10;
			
			}
			n = i; //�����й���n���ַ�
			for (i = 0; i < n; i++) //��ʮ��������ת���ɶ����ƴ��������C��
			{
				int he[4] = { 0,0,0,0 };
				for (j = 3; H[i] != 0; j--)
				{
					he[j] = H[i] % 2;
					H[i] = H[i] / 2;
				}
				for (j = 0; j < 4; j++)
					C[j + (i * 4)] = he[j];
			}
 
			k = n / 16;
			for (l = 0; l < k; l++)
			{
				for (i = 0; i < 64; i++) //��ÿ�������Ӧ��64λ���������ķŵ�iter_result��
					iter_result[l + 1][i] = C[i + (l * 64)];
 
				//��ÿ��text����DES����
 
				for (i = 0; i < 64; i++) //���г�ʼ��λ
					IP_replace[i] = iter_result[l + 1][IP[i] - 1];
 
				for (i = 0; i < 32; i++) //�ֳ����������֣���32λ
				{
					L0[i] = IP_replace[i];
					R0[i] = IP_replace[i + 32];
				}
 
				//ʮ���ε���
				for (t = 0; t < 16; t++)
				{
					for (i = 0; i < 48; i++) //���Ұ벿��ͨ����չ��λ��E��32λ��չ��48λ
						RE0[i] = R0[E[i] - 1];
					for (i = 0; i < 48; i++) //RE0���K
						RK[i] = RE0[i] ^ K[15 - t][i];

					for (i = 0; i < 8; i++) //��S��任R���K�Ľ��
					{
						r[i] = RK[(i * 6) + 0] * 2 + RK[(i * 6) + 5];
						c[i] = RK[(i * 6) + 1] * 8 + RK[(i * 6) + 2] * 4 + RK[(i * 6) + 3] * 2 + RK[(i * 6) + 4];
					}
 
					RKS[0] = S1[r[0]][c[0]];
					RKS[1] = S2[r[1]][c[1]];
					RKS[2] = S3[r[2]][c[2]];
					RKS[3] = S4[r[3]][c[3]];
					RKS[4] = S5[r[4]][c[4]];
					RKS[5] = S6[r[5]][c[5]];
					RKS[6] = S7[r[6]][c[6]];
					RKS[7] = S8[r[7]][c[7]];
 
					for (i = 0; i < 8; i++) //�ѽ��ת��32λ�����ƴ���������SP��
					{
						int b[4] = { 0,0,0,0 };
						m = RKS[i];
						for (j = 3; m != 0; j--)
						{
							b[j] = m % 2;
							m = m / 2;
						}
						for (j = 0; j < 4; j++)
							SP[j + (i * 4)] = b[j];
					}
 
					for (i = 0; i < 32; i++) //�������ƽ���پ���һ��P�л�λ
						RKSP[i] = SP[P[i] - 1];
 
					for (i = 0; i < 32; i++) //��ǰһ�ε���������㣬�õ����ε������Ҳ�
						Ri[i] = L0[i] ^ RKSP[i];
 
					for (i = 0; i < 32; i++)
					{
						L0[i] = R0[i];
						R0[i] = Ri[i];
					}
				}
 
				//һ������32λ����
 
				for (i = 0; i < 32; i++)
					Li[i] = R0[i];
				for (i = 0; i < 32; i++)
					R0[i] = L0[i];
				for (i = 0; i < 32; i++)
					L0[i] = Li[i];
 
				//��ʼ��λ�������
 
				for (i = 0; i < 32; i++) //�����������ֺ������浽iter_replace��
					iter_replace[i] = L0[i];
				for (i = 32; i < 64; i++)
					iter_replace[i] = R0[i - 32];
 
				for (i = 0; i < 64; i++) //���г�ʼ��λ������� 
					text[IP[i] - 1] = iter_replace[i];
 
				for (i = 0; i < 64; i++) //ǰһ������������ǰ�����������ĵĶ����Ʒŵ�result��
					result[l][i] = iter_result[l][i] ^ text[i];
 
			}
 
			for (i = 0; i < (n / 16); i++) //��������ת��ʮ����
				for (j = 0; j < 8; j++)
					M[i][j] = result[i][(j * 8) + 0] * 128 + result[i][(j * 8) + 1] * 64 + result[i][(j * 8) + 2] * 32 + result[i][(j * 8) + 3] * 16 + result[i][(j * 8) + 4] * 8 + result[i][(j * 8) + 5] * 4 + result[i][(j * 8) + 6] * 2 + result[i][(j * 8) + 7];
 
			printf("Client: ");
			for (i = 0; i < (n / 16); i++)
				for (j = 0; j < 8; j++)
					printf("%c", M[i][j]);
			printf("\n");
		}

void main()
{
	start();
	//ǰ�����һ�����ǰ汾Э����
	WORD wVersionRequested;
	WSADATA wsaData;

	int err;
	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {


		return;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)

	{
		WSACleanup();
		return;
	}
	
	SOCKET server, cAddr;//����һ���׽���
	server = socket(AF_INET, SOCK_STREAM, 0);//����˵����IP����Э�顢��ʽ�׽��֡�Ĭ�ϲ���

	SOCKADDR_IN sAddr;//����������ĵ�ַ
	sAddr.sin_family = AF_INET;//Э��
	sAddr.sin_port = htons(1352);//�˿�
	sAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//����˵�IP��ַ

	bind(server, (SOCKADDR*)&sAddr, sizeof(SOCKADDR));//���������ĵ�ַ��Ϣ���׽��ֽ��а�

	listen(server, 5);//���м��������г���Ϊ5���ֽ�

	SOCKET sockConn;//���������׽���
	int len = sizeof(SOCKADDR);

	cout << "waiting for client connection" << endl;
	sockConn = accept(server, (SOCKADDR*)&cAddr, &len);//��������
	if (sockConn == INVALID_SOCKET)
	{
		cout << "ERROR:Connecting to client has failed." << endl;
		return;
	}
	else
	{
		cout << "Client has successfully connected" << endl;
	}

	char sendbuf[256];
	char recvbuf[256];
	while (1)
	{
		cout << "Server: ";
		cin >> sendbuf;
		if (strcmp(sendbuf, "quit") == 0)
		{
			break;
		}
		encode(sendbuf);
		send(sockConn,secretText,strlen(secretText)+1,0);//��������
		recv(sockConn,recvbuf,256,0);//��������
		decode(recvbuf);
	}
	closesocket(server);
	WSACleanup();
}

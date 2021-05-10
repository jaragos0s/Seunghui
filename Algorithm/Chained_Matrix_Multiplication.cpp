/* input.txt
7(number)
5
2
3
4
6
7
8
*/
/* A_1 X A_2 X A_3 X A_4 X A_5 X A_6 
M[i][j] : minimum  # of multiplication for A_i X ... X A_j
M[i][j] = min_(i <= k <= j-1) {M[i, k] + M[k+1, j] + d_(i-1)*d_k*d_j if i < j}
p[i][j] : a value of such k
*/

//2018114817 최승희
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int d[100];
int p[100][100];
int M[101][101];


void minmult(int n);
void print_order(int i, int j, ofstream &fout);
int main()
{
	string fileName;
	ofstream fout("output.txt", ios_base::out);
	int i, j, n;
	char number;
	char input[100];
	cout << "input file name?" << endl;
	cin >> fileName;
	ifstream fin(fileName, ios_base::in);
	
	fin >> number;
	n = number - '0';
	for (i = 1; i <= n; i++)
	{
		M[i][i] = 0;
		for (j = i + 1; j <= n; j++)
		{	
			M[i][j] = 10000;
			p[i][j] = 0;
		}
	}
	for (i = 0; i < n ; i++)
	{
		fin >> input[i];
		d[i] = input[i] - '0';
	}
	minmult(n);
	print_order(1, n-1, fout);

	fin.close();
	fout.close();
}

void minmult(int n)
{
	int i, j, k, sum, diagonal;

	for (diagonal = 1; diagonal < n; diagonal++)
	{
		for (i = 1; i < n - diagonal + 1; i++)
		{
			j = i + diagonal ;
			if (i < j)
			{
				for (k = i; k < j; k++)
				{
					sum = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
					if (M[i][j] > sum)
					{
						M[i][j] = sum;
						p[i][j] = k;			
					}
				}
			}
		}
	}
	return;
}
void print_order(int i, int j, ofstream &fout)
{
	if (i == j)
		fout << i << " ";
	else
	{
		int k = p[i][j];
		fout << "( ";
		print_order(i, k, fout);
		print_order(k + 1, j, fout);
		fout << ") ";
	}
	return;
}

//2018114817 ÃÖ½ÂÈñ
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define INF 1000000

void Path(int, int, int, FILE *f_out);

int **W, **length, **touch;

int main()
{
	FILE *f_in, *f_out;
	int i, j, min, temp, l;
	char input[30], one, buf;
	int n, row, col, flag;

	printf("input file name? ");
	scanf("%s", input);
	f_in = fopen(input, "r");
	f_out = fopen("output.txt", "w");
	fscanf(f_in, "%d", &n);
	/////////////////// Allocate Dynamic Memory /////////////////
	W = (int**)malloc(sizeof(int*) * (n + 2));
	length = (int**)malloc(sizeof(int*) * (n + 2));
	touch = (int**)malloc(sizeof(int*) * (n + 2));

	for (i = 0; i < n + 2; i++)
	{
		W[i] = (int*)malloc(sizeof(int) * (n + 2));
		length[i] = (int*)malloc(sizeof(int) * (n + 2));
		touch[i] = (int*)malloc(sizeof(int) * (n + 2));
	}

	///////////////// Read data from input file ////////////////////
	fscanf(f_in, "%c", &buf);

	for(i = 1; i < n + 1; i++)
	{
		for (j = 1; j < n + 1; j++)
		{
			length[i][j] = INF;
			touch[i][j] = 0;
			fscanf(f_in, "%c", &one);
			if (one == '1')
				W[i][j] = 0;
			else
				W[i][j] = 1;
		}
		fscanf(f_in, "%c", &buf); // '/n'
	}
	
	length[1][1] = 0;
	touch[1][1] = -1;
	row = col = 1;
	min = 0;
	do
	{
		temp = INF;
		l = length[row][col];
		if (row + 1 <= n) //¹ØÀ¸·Î
		{
			if (length[row + 1][col] >= INF)
				length[row + 1][col] = l + W[row + 1][col];
			if (temp > length[row + 1][col] && length[row + 1][col] != -1)
			{
				temp = length[row + 1][col];
				flag = 3;
			}
			if (touch[row + 1][col] == 0)
				touch[row + 1][col] = 1;
		}
		if (col > 1) //¿ÞÂÊ
		{
			if (length[row][col - 1] >= INF)
				length[row][col - 1] =l + W[row][col - 1];
			if (temp > length[row][col - 1] && length[row][col - 1] != -1)
			{
				temp = length[row][col - 1];
				flag = 4;
			}
			if (touch[row][col - 1] == 0)
				touch[row][col - 1] = 2;
		}
		if (row > 1) //À§·Î
		{
			if (length[row - 1][col] >= INF)
				length[row - 1][col] = l + W[row - 1][col];
			if (touch[row - 1][col] == 0)
				touch[row - 1][col] = 3;
			if (length[row - 1][col] != -1)
			{
				temp = length[row - 1][col];
				flag = 1;
			}

			if (touch[row - 1][col] == 0)
				touch[row - 1][col] = 3;
		}
		if (col + 1 <= n) //¿À¸¥ÂÊ
		{
			if (length[row][col + 1] >= INF)
				length[row][col + 1] =l + W[row][col + 1];
			if (temp > length[row][col + 1] && length[row][col + 1] != -1)
			{
				temp = length[row][col + 1];
				flag = 2;
			}
			if (touch[row][col + 1] == 0)
				touch[row][col + 1] = 4;
		}
		length[row][col] = -1;

		if (temp != min)
		{
			min = INF;
			for (i = 1; i < n + 1; i++)
			{
				for (j = 1; j < n + 1; j++)
				{
					if (length[i][j] >= 0 && length[i][j] < min)
					{
						min = length[i][j];
						row = i;
						col = j;
					}
				}
			}
		}
		else
		{
			switch (flag)
			{
			case 1: row--; break;
			case 2: col++; break;
			case 3: row++; break;
			case 4: col--; break;
			default: break;
			}
		}
	} while (length[n][n] == INF);

	fprintf(f_out, "%d\n", length[n][n]);
	Path(n, n, n, f_out);

	for (i = 0; i < n + 1; i++)
	{
		free(W[i]);
		free(length[i]);
		free(touch[i]);
	}
	free(W);
	free(length);
	free(touch);

	fclose(f_in);
	fclose(f_out);
	return 0;
}

void Path(int row, int col, int n, FILE* f_out)
{
	int flag = 0;
	if (row == 1 && col == 1)
		return;
	if (row == n && col == n)
		flag = 1;
	switch (touch[row][col])
	{
	case 1: row--; break;
	case 2: col++; break;
	case 3: row++; break;
	case 4: col--; break;
	default: break;
	}
	Path(row, col, n, f_out);
	fprintf(f_out, "%d %d\n", row, col);
	if (flag)
		fprintf(f_out, "%d %d\n", n, n);
	return;
}
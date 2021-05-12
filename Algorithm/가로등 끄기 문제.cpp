//2018114817 ÃÖ½ÂÈñ
#pragma warning (disable: 4996)
#include <stdio.h>
#include  <stdlib.h>
#define INF 1000000

void Path(int ***EE, int ***PP, int, int, int, FILE*);

int main()
{
	FILE *f_in, *f_out;
	int ***EE, ***PP, *WS, *D, *W;
	int i, j, k, goal;
	char input[30];
	int n, m;

	printf("input file name? ");
	scanf("%s", input);
	f_in = fopen(input, "r");
	f_out = fopen("output.txt", "w");
	fscanf(f_in, "%d", &n); 
	fscanf(f_in, "%d", &m);

	/////////////// Allocate Dynamic Memory /////////////////
	D = (int*)malloc(sizeof(int)*(n + 1));
	W = (int*)malloc(sizeof(int)*(n + 1));
	WS = (int*)malloc(sizeof(int)*(n + 1));
	EE = (int***)malloc(sizeof(int**)*(n + 1));
	PP = (int***)malloc(sizeof(int**)*(n + 1));

	for (i = 0; i < n + 1; i++)
	{
		EE[i] = (int**)malloc(sizeof(int*)*(n + 1));
		PP[i] = (int**)malloc(sizeof(int*)*(n + 1));
	}
	for (i = 0; i < n + 1; i++)
	{
		for (j = 0; j < n + 1; j++)
		{
			EE[i][j] = (int*)malloc(sizeof(int) * 3);
			PP[i][j] = (int*)malloc(sizeof(int) * 3);
		}
	}

	///////////////// Initialization ////////////////
	for (i = 0; i < n + 1; i++)
	{
		for (j = 0; j < n + 1; j++)
		{
			for (k = 0; k < 3; k++)
			{
				EE[i][j][k] = 0;
				PP[i][j][k] = 0;
			}
		}
	}
	/////////////// Read from input file //////////////////
	for (i = 1; i < n + 1; i++)
	{
		fscanf(f_in, "%d %d",&D[i],&W[i]);
	}
	

	WS[0] = 0;
	for (i = 1; i < n + 1; i++)
	{

		EE[i][i][1] = INF;
		EE[i][i][2] = INF;
		PP[i][i][1] = 0;
		PP[i][i][2] = 0;
		WS[i] = WS[i - 1] + W[i];
	}
	EE[m][m][1] = 0;
	EE[m][m][2] = 0;

	for (k = 1; k < n + 1; k++)
	{
		for (i = 1; i < n  + 1 - k; i++)
		{
			j = i + k;

			if (EE[i + 1][j][1] + (D[i + 1] - D[i]) * (WS[n] - (WS[j] - WS[i])) < EE[i + 1][j][2] + (D[j] - D[i]) * (WS[n] - (WS[j] - WS[i])))
			{
				EE[i][j][1] = EE[i + 1][j][1] + (D[i + 1] - D[i]) * (WS[n] - (WS[j] - WS[i]));
				PP[i][j][1] = i + 1;
			}
			else
			{
				EE[i][j][1] = EE[i + 1][j][2] + (D[j] - D[i]) * (WS[n] - (WS[j] - WS[i]));
				PP[i][j][1] = j;
			}

			if (EE[i][j - 1][1] + (D[j] - D[i]) * (WS[n] - (WS[j - 1] - WS[i - 1])) < EE[i][j - 1][2] + (D[j] - D[j - 1]) * (WS[n] - (WS[j - 1] - WS[i - 1])))
			{
				EE[i][j][2] = EE[i][j - 1][1] + (D[j] - D[i]) * (WS[n] - (WS[j - 1] - WS[i - 1]));
				PP[i][j][2] = i;
			}
			else
			{
				EE[i][j][2] = EE[i][j - 1][2] + (D[j] - D[j - 1]) * (WS[n] - (WS[j - 1] - WS[i - 1]));
				PP[i][j][2] = j - 1;
			}
		}
	}
	if (EE[1][n][1] < EE[1][n][2])
			goal = EE[1][n][1];
		else
			goal = EE[1][n][2];
		
	fprintf(f_out, "%d\n", goal);
	Path(EE, PP, n, 1, n, f_out);

	///////////// Free Memory ///////////////
	for (i = 0; i < n + 1; i++)
	{
		for (j = 0; j <  n + 1; j++)
		{
			free(EE[i][j]);
			free(PP[i][j]);
		}
	}

	for (i = 0; i < n + 1; i++)
	{
		free(EE[i]);
		free(PP[i]);
	}
	free(D);
	free(W);
	free(EE);
	free(WS);
	free(PP);
	fclose(f_in);
	fclose(f_out);

	return 0;
}

void Path(int ***EE, int ***PP, int n, int l, int r, FILE *f_out)
{ //////////////// Print Path /////////////////
	if (l == r)
		return;

	if (EE[l][r][1] < EE[l][r][2])
	{
		Path(EE, PP, n, l + 1, r, f_out);
		fprintf(f_out, "%d\n", PP[l][r][1]);

		if (l == 1 && r == n)
			fprintf(f_out, "%d\n", l);
	}
	else
	{
		Path(EE, PP, n, l, r - 1, f_out);
		fprintf(f_out, "%d\n", PP[l][r][2]);

		if (l == 1 && r == n)
			fprintf(f_out, "%d\n", r);
	}

}
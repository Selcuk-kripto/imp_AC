
// This code finds cryptographic properties (nonlinearity, absolute indicator, 
// algebraic degree, balancedness) of the Boolean functions given in
// Table 1 of the paper "Improved autocorrelation properties of balanced Boolean 
// functions on even number of variables" by Selçuk Kavut, Hakan Kutucu, 
// Subhamoy Maitra, Erol Özçekiç.

// The truth tables of these Boolean functions are given by the following files:
// "tt8.txt", "tt10_1.txt", "tt10_2.txt", "tt12_1.txt", "tt12_2.txt", "tt12_3.txt", 
// "tt14_1.txt", "tt14_12.txt", "tt16_1.txt", "tt16_2.txt", "tt18.txt", "tt20.txt",
// "tt22.txt", "tt24.txt", "tt26.txt", which are available at 
// https://github.com/Selcuk-kripto/imp_AC

// Compiled with Microsoft Visual C++ 2010.

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

#define Zn 26
#define Zm 67108864

FILE *out;

signed char *AT=(signed char *)malloc(Zm*sizeof(signed char));
signed char *BT=(signed char *)malloc(Zm*sizeof(signed char));
signed char	*TT=(signed char *)malloc(Zm*sizeof(signed char)); 
signed char	*TTs=(signed char *)malloc(Zm*sizeof(signed char)); 
int	*FW=(int *)malloc(Zm*sizeof(int)); 
long double *AC=(long double *)malloc(Zm*sizeof(long double));
long double *ACt=(long double *)malloc(Zm*sizeof(long double));

int Znx=1,Zmx=1;

int _tmain(int argc, _TCHAR* argv[])
{
	int acor(int *FW);
	void fastwh(int *FW, signed char *TTs);
	void fastwhld(long double *FW, long double *TTs);
	int findmax(int *tt);
	int anf(signed char *TT);

	int i,NL,acx,whz,fcnt;
	signed char x;
	char fname[6][10] = {"tt8.txt", "tt18.txt", "tt20.txt", "tt22.txt", "tt24.txt", "tt26.txt"};
	
	if (TT==0 || FW==0 || TTs==0 || AC==0 || ACt==0 || AT==0 || BT==0)
	{
		printf("Memory Allocation Error!");
		return 0;
	}

	while (Znx>26 || Znx<8 || (Znx%2)==1)
	{
		printf("\nEnter the number of variables (8, 10, ..., 26):");
		scanf("%d",&Znx);
		if (Znx>26 || Znx<8 || (Znx%2)==1)
			printf("\nYou have entered an invalid number of variables.");
	}

	for (i=0;i<Znx;i++)		Zmx=Zmx*2;

	if (Znx==8)			out=fopen("tt8.txt", "r");
	else if (Znx==18)	out=fopen("tt18.txt", "r");
	else if (Znx==20)	out=fopen("tt20.txt", "r");
	else if (Znx==22)	out=fopen("tt22.txt", "r");
	else if (Znx==24)	out=fopen("tt24.txt", "r");
	else if (Znx==26)	out=fopen("tt26.txt", "r");

	if (!(Znx==10 || Znx==12 || Znx==14 || Znx==16))
	{
		if (Znx==8)			fcnt=0;
		else if (Znx==18)	fcnt=1;
		else if (Znx==20)	fcnt=2;
		else if (Znx==22)	fcnt=3;
		else if (Znx==24)	fcnt=4;
		else if (Znx==26)	fcnt=5;

		i=0;
		while (!feof(out))
		{
			fscanf(out,"%d ",&x);
			TT[i]=x;
			i=i+1;
		}
		//Find nonlinearity, absolute indicator, and algebraic degree 
		for (i=0;i<Zmx;i++)
			TTs[i]=1-2*TT[i];
		fastwh(FW,TTs);
		NL=Zmx/2-findmax(FW)/2;
		acx=acor(FW);
		whz=0;
		if (FW[0]==0)
			whz=1;
		printf("\nCryptographic properties of %d-variable Boolean function in the file %s:",Znx,fname[fcnt]);
		if (whz==1)
			printf("\nNL=%d AI=%d d=%d Balancedness: Yes",NL,acx,anf(TT));
		else
			printf("\nNL=%d AI=%d d=%d Balancedness: No",NL,acx,anf(TT));
	}
	if (Znx==10)
	{
		out=fopen("tt10_1.txt", "r");
		i=0;
		while (!feof(out))
		{
			fscanf(out,"%d ",&x);
			TT[i]=x;
			i=i+1;
		}
		for (i=0;i<Zmx;i++)
			TTs[i]=1-2*TT[i];
		fastwh(FW,TTs);
		NL=Zmx/2-findmax(FW)/2;
		acx=acor(FW);
		whz=0;
		if (FW[0]==0)
			whz=1;
		printf("\nCryptographic properties of %d-variable Boolean function in the file tt10_1.txt:",Znx);
		if (whz==1)
			printf("\nNL=%d AI=%d d=%d Balancedness: Yes",NL,acx,anf(TT));
		else
			printf("\nNL=%d AI=%d d=%d Balancedness: No",NL,acx,anf(TT));

		out=fopen("tt10_2.txt", "r");
		i=0;
		while (!feof(out))
		{
			fscanf(out,"%d ",&x);
			TT[i]=x;
			i=i+1;
		}
		for (i=0;i<Zmx;i++)
			TTs[i]=1-2*TT[i];
		fastwh(FW,TTs);
		NL=Zmx/2-findmax(FW)/2;
		acx=acor(FW);
		whz=0;
		if (FW[0]==0)
			whz=1;
		printf("\nCryptographic properties of %d-variable Boolean function in the file tt10_2.txt:",Znx);
		if (whz==1)
			printf("\nNL=%d AI=%d d=%d Balancedness: Yes",NL,acx,anf(TT));
		else
			printf("\nNL=%d AI=%d d=%d Balancedness: No",NL,acx,anf(TT));
	}
	if (Znx==12)
	{
		out=fopen("tt12_1.txt", "r");
		i=0;
		while (!feof(out))
		{
			fscanf(out,"%d ",&x);
			TT[i]=x;
			i=i+1;
		}
		for (i=0;i<Zmx;i++)
			TTs[i]=1-2*TT[i];
		fastwh(FW,TTs);
		NL=Zmx/2-findmax(FW)/2;
		acx=acor(FW);
		whz=0;
		if (FW[0]==0)
			whz=1;
		printf("\nCryptographic properties of %d-variable Boolean function in the file tt12_1.txt:",Znx);
		if (whz==1)
			printf("\nNL=%d AI=%d d=%d Balancedness: Yes",NL,acx,anf(TT));
		else
			printf("\nNL=%d AI=%d d=%d Balancedness: No",NL,acx,anf(TT));

		out=fopen("tt12_2.txt", "r");
		i=0;
		while (!feof(out))
		{
			fscanf(out,"%d ",&x);
			TT[i]=x;
			i=i+1;
		}
		for (i=0;i<Zmx;i++)
			TTs[i]=1-2*TT[i];
		fastwh(FW,TTs);
		NL=Zmx/2-findmax(FW)/2;
		acx=acor(FW);
		whz=0;
		if (FW[0]==0)
			whz=1;
		printf("\nCryptographic properties of %d-variable Boolean function in the file tt12_2.txt:",Znx);
		if (whz==1)
			printf("\nNL=%d AI=%d d=%d Balancedness: Yes",NL,acx,anf(TT));
		else
			printf("\nNL=%d AI=%d d=%d Balancedness: No",NL,acx,anf(TT));

		out=fopen("tt12_3.txt", "r");
		i=0;
		while (!feof(out))
		{
			fscanf(out,"%d ",&x);
			TT[i]=x;
			i=i+1;
		}
		for (i=0;i<Zmx;i++)
			TTs[i]=1-2*TT[i];
		fastwh(FW,TTs);
		NL=Zmx/2-findmax(FW)/2;
		acx=acor(FW);
		whz=0;
		if (FW[0]==0)
			whz=1;
		printf("\nCryptographic properties of %d-variable Boolean function in the file tt12_3.txt:",Znx);
		if (whz==1)
			printf("\nNL=%d AI=%d d=%d Balancedness: Yes",NL,acx,anf(TT));
		else
			printf("\nNL=%d AI=%d d=%d Balancedness: No",NL,acx,anf(TT));
	}
	if (Znx==14)
	{
		out=fopen("tt14_1.txt", "r");
		i=0;
		while (!feof(out))
		{
			fscanf(out,"%d ",&x);
			TT[i]=x;
			i=i+1;
		}
		for (i=0;i<Zmx;i++)
			TTs[i]=1-2*TT[i];
		fastwh(FW,TTs);
		NL=Zmx/2-findmax(FW)/2;
		acx=acor(FW);
		whz=0;
		if (FW[0]==0)
			whz=1;
		printf("\nCryptographic properties of %d-variable Boolean function in the file tt14_1.txt:",Znx);
		if (whz==1)
			printf("\nNL=%d AI=%d d=%d Balancedness: Yes",NL,acx,anf(TT));
		else
			printf("\nNL=%d AI=%d d=%d Balancedness: No",NL,acx,anf(TT));

		out=fopen("tt14_2.txt", "r");
		i=0;
		while (!feof(out))
		{
			fscanf(out,"%d ",&x);
			TT[i]=x;
			i=i+1;
		}
		for (i=0;i<Zmx;i++)
			TTs[i]=1-2*TT[i];
		fastwh(FW,TTs);
		NL=Zmx/2-findmax(FW)/2;
		acx=acor(FW);
		whz=0;
		if (FW[0]==0)
			whz=1;
		printf("\nCryptographic properties of %d-variable Boolean function in the file tt14_2.txt:",Znx);
		if (whz==1)
			printf("\nNL=%d AI=%d d=%d Balancedness: Yes",NL,acx,anf(TT));
		else
			printf("\nNL=%d AI=%d d=%d Balancedness: No",NL,acx,anf(TT));
	}
	if (Znx==16)
	{
		out=fopen("tt16_1.txt", "r");
		i=0;
		while (!feof(out))
		{
			fscanf(out,"%d ",&x);
			TT[i]=x;
			i=i+1;
		}
		for (i=0;i<Zmx;i++)
			TTs[i]=1-2*TT[i];
		fastwh(FW,TTs);
		NL=Zmx/2-findmax(FW)/2;
		acx=acor(FW);
		whz=0;
		if (FW[0]==0)
			whz=1;
		printf("\nCryptographic properties of %d-variable Boolean function in the file tt16_1.txt:",Znx);
		if (whz==1)
			printf("\nNL=%d AI=%d d=%d Balancedness: Yes",NL,acx,anf(TT));
		else
			printf("\nNL=%d AI=%d d=%d Balancedness: No",NL,acx,anf(TT));

		out=fopen("tt16_2.txt", "r");
		i=0;
		while (!feof(out))
		{
			fscanf(out,"%d ",&x);
			TT[i]=x;
			i=i+1;
		}
		for (i=0;i<Zmx;i++)
			TTs[i]=1-2*TT[i];
		fastwh(FW,TTs);
		NL=Zmx/2-findmax(FW)/2;
		acx=acor(FW);
		whz=0;
		if (FW[0]==0)
			whz=1;
		printf("\nCryptographic properties of %d-variable Boolean function in the file tt16_2.txt:",Znx);
		if (whz==1)
			printf("\nNL=%d AI=%d d=%d Balancedness: Yes",NL,acx,anf(TT));
		else
			printf("\nNL=%d AI=%d d=%d Balancedness: No",NL,acx,anf(TT));
	}
	free(AC);
	free(ACt);
	free(AT);
	free(BT);
	free(TT);
	free(TTs);
	free(FW);
	fclose(out);
	return 0;
}

void fastwh(int *FW, signed char *TTs)
{	
	int i,j,i1,i2,i3,k1=2,k2=Zmx/2,k3=1,L1,temp1,temp2;
	for (i=0;i<Zmx;i++)
		FW[i]=TTs[i];
	for (i1=0;i1<Znx;i1++)  
	{
	   L1=1;
	   for (i2=0;i2<k2;i2++)
	   {
		  for (i3=0;i3<k3;i3++)
		  {
			 i=i3+L1-1; j=i+k3; 
		     temp1= FW[i]; temp2 = FW[j]; 
			 FW[i]=temp1+temp2;
		     FW[j]=temp1-temp2;
		  }
	      L1=L1+k1; 
	   }
	   k1=k1*2; k2=k2/2; k3=k3*2;
	}
}


int anf(signed char *TT)
{
	int i,j;
	for (i=0;i<Zmx;i++)	AT[i]=TT[i];
	int t1=1,t2,Zx,l1,l2,lx,u1,u2,ux;
	for (int k=0;k<Znx;k++)
	{
		t1=t1*2;
		t2=t1/2;
		Zx=Zmx/t1;
		for (int b=0;b<Zx;b++)
		{
			i=2*b;
			l1=t2*i;	u1=t2*(i+1);
			l2=t2*(i+1);u2=t2*(i+2);
			lx=t1*b;	ux=t1*(b+1);
			for (int j=l1;j<u1;j++)
			{
				BT[lx]=AT[j];
				lx=lx+1;
			}
			for (int j=l2;j<u2;j++)
			{
				BT[lx]=AT[j]^AT[l1];
				lx=lx+1;l1=l1+1;
			}
		}
		for (j=0;j<Zmx;j++)
			AT[j]=BT[j];
	}
	int ad=0,d;
	for (i=0;i<Zmx;i++)
		if (AT[i]!=0)
		{
			d=0;
			for (j=0;j<Znx;j++)
				if ((i&(1<<j))!=0)
					d=d+1;
			if (d>ad)
				ad=d;

		}
	return ad;
}

void fastwhld(long double *FW, long double *TTs)
{	
	int i,j,i1,i2,i3,k1=2,k2=Zmx/2,k3=1,L1;
	long double temp1,temp2;
	for (i=0;i<Zmx;i++)
		FW[i]=TTs[i];
	for (i1=0;i1<Znx;i1++)  
	{
	   L1=1;
	   for (i2=0;i2<k2;i2++)
	   {
		  for (i3=0;i3<k3;i3++)
		  {
			 i=i3+L1-1; j=i+k3; 
		     temp1= FW[i]; temp2 = FW[j]; 
			 FW[i]=temp1+temp2;
		     FW[j]=temp1-temp2;
		  }
	      L1=L1+k1; 
	   }
	   k1=k1*2; k2=k2/2; k3=k3*2;
	}
}

int acor(int *FW)
{
	int i;
	for (i=0;i<Zmx;i++)
		ACt[i]=((long double) FW[i])*((long double) FW[i]);
	fastwhld(AC,ACt);

	long double D,Maxi=-1;
	for (i=1;i<Zmx;i++)
	{
		D=AC[i];
		if (AC[i]<0)
			D=-AC[i];
		if (D>Maxi)
			Maxi=D;
	}
	Maxi=Maxi/Zmx;
	return ((int) Maxi);
}

int findmax(int *tt)
{
	int i;
	int D,Maxi=-1;
	for (i=0;i<Zmx;i++)
	{
		D=tt[i];
		if (tt[i]<0)
			D=-tt[i];
		if (D>Maxi)
			Maxi=D;
	}
	return Maxi;
}


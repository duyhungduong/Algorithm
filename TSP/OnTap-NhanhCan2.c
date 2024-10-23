#include <stdio.h>
#include <malloc.h>

typedef struct{
	int dau ,cuoi , da_dung;
	float do_dai;
}canh;
#define size 100
void readfile(char name[], canh a[][100], int *n){
	FILE* f;
	f = fopen(name , "r");
	if(f==NULL ){
		printf("Loiii\n");
		return;
	}
	int i, j ;
	fscanf( f,  "%d" , n);
	for( i= 0 ; i<*n ; i++)
		for(j=0; j<*n ; j++)
		{
			fscanf( f, "%f" , &a[i][j].do_dai);
			a[i][j].dau = i;
			a[i][j].cuoi = j;
			a[i][j].da_dung = 0;
		}
	fclose(f);
}

void in_ma_tran(canh a[][size], int n){
	int i,j ;
	printf("\n Ma tran cua bai toan da cho la:\n");
	for(i=0 ; i< n ; i++){
		for(j=0 ; j< n ; j++)
			printf("%c%c = %8.2f  ", a[i][j].dau+65 , a[i][j].cuoi+65 , a[i][j].do_dai);
		printf("\n");
	}
}

float canh_NN(canh a[][size] , int n ){
	float Cmin = 1000000;
	int i, j;
	for(i=0 ; i< n ; i++){
		for(j=0 ; j< n ; j++)
			if( i != j && !a[i][j].da_dung && a[i][j].do_dai < Cmin)
				Cmin = a[i][j].do_dai;
	}
	return Cmin;
}

float Can_Duoi (canh a[][size], int n , int i, float TGT ){
	return TGT + (n-i)*canh_NN(a, n);
}

int co_chu_trinh(canh x[], int i , int j){
	int k =0 ; int co_CT=0 ;
	while( k < i && !co_CT ){
		if(j == x[k].dau)
			co_CT = 1;
		else k++;
	}
	return co_CT;
}

void Cap_Nhat_PA_TNTT(canh a[][size] ,int n , float TGT , float* GNNTT, canh x[], canh PA[] ){
	int i;
	x[n-1]  = a[x[n-2].cuoi][x[0].dau];
	TGT = TGT + x[n-1].do_dai;
	if(*GNNTT > TGT){
		*GNNTT = TGT;  
		for(i=0 ; i<n ; i++) PA[i] = x[i];
	}
}

void Nhanh_Can(canh a[][size], int i, int dau, int n , float *TGT ,float *CD , float *GNNTT, canh x[], canh PA[]){
	int j ;
	for(j =0  ; j< n ; j++ ){
		if(dau!=j && !a[dau][j].da_dung && !co_chu_trinh(x, i, j)){

			*TGT = *TGT + a[dau][j].do_dai;
			*CD = Can_Duoi(a,  n, i + 1,*TGT);
			if (*CD < *GNNTT)
			{
				
				x[i]= a[dau][j];
				
				a[dau][j].da_dung =1 ;
				a[j][dau].da_dung =1 ;
				if(i == n-2 ) {
					Cap_Nhat_PA_TNTT(a, n, *TGT , GNNTT , x, PA);
				}else
					Nhanh_Can(a, i+1 , j , n, TGT ,CD ,GNNTT, x, PA );
			}
			a[j][dau].da_dung =0;
			a[dau][j].da_dung= 0;
			*TGT -= a[dau][j].do_dai;
				
		}
	}
}

void in_PA(canh PA[],int n){
	float sum=0 ;
	int i;
	printf("Phuong an Nhanh Can co ket qua la: \n");
	for(i=0 ; i< n ;i++){
		printf("%c%c = %8.2f\n" , PA[i].dau+65 , PA[i].cuoi+65 , PA[i].do_dai);
		sum+=PA[i].do_dai;
	}
	printf("\nTong do dai la %8.2f\n", sum);
}	

int main(){
	int n; canh a[size][size];
	readfile("TSP1.txt", a , &n);
	in_ma_tran(a, n);
	canh x[n], PA[n];
	float CD, TGT ,GNNTT;
	TGT = 0, CD = 0 ,GNNTT =11111111111;
	char tpxp;
	printf("Nhap A-E \n");
	scanf("%c", &tpxp);
	Nhanh_Can(a, 0 , tpxp-65 , n , &TGT, &CD ,&GNNTT , x ,PA);
	in_PA(PA, n);
	
}

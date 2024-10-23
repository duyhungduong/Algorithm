
#include <stdio.h>
#define size 50
void readfile(int a[][size], int *n){
	FILE *f;
	f = fopen ("Tam_giac_so.txt", "r");
	if(f==NULL){
		printf("Doi file loi\n");
		return ;
	}
	int i=0,j;
	while(!feof(f)){
		for(j=0; j<=i;j++){
			fscanf(f, "%d" , &a[i][j]);
		}
		i++;
	}
	*n = i;
	fclose(f);
}
void printdata(int a[][size], int n){
	int i,j;
	printf("Du lieu bai toan la: \n");
	for(i=0; i<n ; i++)	{
		for(j= 0 ; j<=i ; j++)
			printf("%-2d", a[i][j] );
		printf("\n");
	}		
}

int max_dong(int a[][size], int i){
	int k; int max = a[i][0];
	for(k= 1 ;k <=i ; k++)
		if(a[i][k]>max)
			max= a[i][k];
	return max;
}

int max(int a[][size], int i, int j){
	if(j==0 ) return (a[i][0] > a[i][1]) ? 0 : 1 ;
	if(a[i][j-1] > a[i][j] && a[i][j-1] > a[i][j+1]) return j-1;
	if(a[i][j] > a[i][j-1] && a[i][j] > a[i][j+1]) return j;
	if(a[i][j+1] > a[i][j-1] && a[i][j+1] > a[i][j]) return j+1;
}

void Can_Tren(int i , int j , int a[][size] , int TGT , int* CT, int n){
	int k ;
	*CT = TGT + a[i+1][max(a,i+1, j)];
	for(k= i+2 ; k< n ; k++){
		*CT += max_dong(a, k);
	}
}
void Cap_Nhat(float *GLNTT , float TGT , int x[],int PA[] , int n){
	int i;
	if(*GLNTT < TGT){
		*GLNTT = TGT ;
		for(i=0 ; i<n ; i++) PA[i] = x[i];
	}
}

void Nhanh_Can (int a[][size], int i , int j , int n , int *TGT ,int *CT , int *GLNTT ,int x[], int PA[]){
	int dau , cuoi ;
	if(j ==0 ){
		dau = 0, cuoi =1 ;
	}else{
		dau = j-1 , cuoi = j+1;
	}
	int k ; 
	for(k= dau ; k<= cuoi ; k++){
		*TGT += a[i][k];
		Can_Tren(i , k , a, *TGT , CT , n);
		if(*CT  > *GLNTT ){
			x[i] = a[i][k];
			if(i == n-1 )
				Cap_Nhat(GLNTT , *TGT, x , PA, n );
			else
				Nhanh_Can(a, i+1 , k, n, TGT ,CT ,GLNTT, x ,PA);
		}
		*TGT-= a[i][k];
		x[i] = 0;
	}
}
int giaiPA(int pa[],int n){
	int i , su=0;
	for(i=0 ; i<n ; i++) su+=pa[i];
	return su;
}

void printPA(int pa[], int n){
	printf("\n Phuong phap Nhanh Can bai toan Tam Giac So\n");
	int i ;
	printf("%d" , pa[0]);
	for(i=1 ; i< n ;i++) printf("= > %d" , pa[i]);
	printf("\n Tong gia tri: %d" , giaiPA(pa , n));
}
int main(){
    int a[size][size];
    int n;
    readfile( a , &n);
    printdata(a, n);

	int x[n], PA[n] , CT , TGT ,GLNTT;
	TGT = a[0][0] , GLNTT =TGT, x[0] = TGT ;
	Can_Tren(0 ,0 , a , TGT , &CT , n );

	Nhanh_Can(a, 1 , 0 , n, &TGT , &CT ,&GLNTT , x ,PA);
	printPA(PA , n);
}

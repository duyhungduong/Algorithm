#include  <stdio.h>
#define size 100
void readfile (char name[], int a[][size], int *n){
	FILE* f ;
	f = fopen (name, "r");
	if(f == NULL){
		printf("Loii\n");
		return;
	} 
	int i=0,j;
	while(!feof(f)){
		for(j=0 ; j<=i ; i++)
			fscanf( f , "%d" , &a[i][j]);
		i++;
	}
	*n= i ;
	fclose(f);
}

void in_data(int a[][size], int n){
	int i,j ; 
	printf("Du lieu bai toan la");
	for(i=0 ; i< n ; i++){
		for(j=0; j<=i ; j++)
			printf("%-3d", a[i][j]);
		printf("\n");
	}
}

int max_dong(int a[][size], int i){
	int max  = a[i][0];
	int k;
	for(k=0 ; k<=i ; k++)
		if(a[i][k] > max ){
			max = a[i][k];
		}
	return max;
}

int max(int a[][size], int i, int j){
	if(j==0)	return (a[i][0] > a[i][1] ) ? 0 : 1 ;
	if(a[i][j-1] > a[i][j] && a[i][j-1] > a[i][j+1])
		return j-1;
	if(a[i][j-1] < a[i][j] && a[i][j] > a[i][j+1])
		return j;
	if(a[i][j+1] > a[i][j] && a[i][j+1] > a[i][j-1])
		return j+1;
	
}

void Can_Tren(int i, int j , int a[][size], int TGT , int  *CT , int n){
	int k;
	*CT = TGT + a[i][max(a, i+1 , j)];
	for(k = i+2 ; k < n ; k++){
		*CT += max_dong(a, k);
	}
}


void Cap_Nhat_PA_TNTT(int TGT ,int *GLNTT, int x[], int PA[], int n){
	int i;
	if(*GLNTT < TGT ){
		*GLNTT = TGT ;
		for(i=0 ; i< n ; i++) PA[i] = x[i];
	}
}

void Nhanh_Can(int i , int j, int a[][size], int *TGT , int *CT, int *GLNTT, int x[],int PA[], int n){
	int k;
	int dau , cuoi ;
	if(j==0){
		dau = 0; cuoi =1 ;
	}else{
		dau = j-1 ; cuoi = j+1;
	}
	for(k = dau; k<=cuoi ; k++){
		*TGT += a[i][k];
		Can_Tren(i, k , a , *TGT , CT , n );
		if(*CT > *GLNTT ){
			x[i] = a[i][k];
			if(i == n-1 ){
				Cap_Nhat_PA_TNTT(*TGT , GLNTT , x, PA,  n );
			}else
				Nhanh_Can(i+1 , k , a, TGT , CT , GLNTT , x , PA, n );
		}
		x[i] = 0;
		*TGT -= a[i][k];
	}
}
int main(){
	int a[size][size];
	int n;
	readfile("Tam_giac_so.txt", a, &n);
	in_data(a, n);
	
//	int TGT, CT , GLNTT, x[n],  PA[n];
//	TGT = a[0][0];
//	Can_Tren(0, 0 , a, TGT , &CT ,n );
//	x[0] = TGT;
//	GLNTT = TGT; 
//	
//	Nhanh_Can(0 , 0 , a, &TGT , &CT , &GLNTT , x, PA, n);
//	
//	int o, sum=PA[0] ;
//	printf("%d ", PA[0]);
//	for(o=1  ; o< n ; o++){
//		sum+=PA[o];
//		printf(" => %d ", PA[0]);
//	}
//	printf("\nTong gia tri: %d" , sum);
}





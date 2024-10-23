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
//Phan tu lon nhat cua dong
int max(int a[][size], int i){
	int k, somax=a[i][0] ;
	for(k=1; k<=i ; k++){
		if(a[i][k]> somax){
			somax= a[i][k];
		}
	}
	return somax;
}
//Tim gia tri lon nhat cua dong ke tiep, xet 2 hoac 3 phan tu
int maxnext(int a[], int j){
	if(j==0)
		return (a[0]>a[1])? a[0]: a[1];
	if(a[j-1] >a[j] && a[j-1]> a[j+1])
		return a[j-1] ;
	if(a[j] >a[j-1]&& a[j]> a[j+1])
		return a[j];
	if(a[j+1]>a[j-1]&& a[j+1] >a[j])
		return a[j+1];	 
}

void Can_Tren(int i ,int j, int a[][size], int TGT , int *CT, int n){
	int k;
//Can Tren = Tong gia tri nut cha + so lon nhat trong 2 hoac 4 so chua dong ke tiep  
	*CT = TGT + maxnext(a[i+1], j );
//Cong voi so lon nhat cua cac dong tiep theo
	for(k= i+2; k<n ; k++){
		*CT = *CT + max(a , k); 
	} 
}  

void Khoi_tao_nut_goc(int* TGT, int *CT, int *GLNTT, int x[], int a[][size], int n) {
	*TGT = a[0][0];
	Can_Tren(0 , 0 , a, *TGT , CT , n );
	*GLNTT = *TGT;
	x[0]= *TGT ; 
}

void Cap_nhat_PATNTT (int TGT , int *GLNTT , int x[], int PA[], int n){
	int i;
	if(*GLNTT < TGT ){
		*GLNTT = TGT ;
		for(i=0 ; i< n; i++) PA[i] = x[i]; 
	} 
} 
void Nhanh_Can (int i , int j, int a[][size], int *TGT , int *CT, int *GLNTT, int x[], int PA[], int n) {
	int k ;
	int dau,cuoi;
	if(j==0 ){
		dau =0 ; 
		cuoi = 1; 
	} else{
		dau = j-1 ;
		cuoi = j+1; 
	} 
//Xet nut tuong dong voi i, cot k
for(k =dau ; k<=cuoi ; k++){
	*TGT = *TGT +a[i][k];
	Can_Tren(i, k, a, *TGT , CT , n ) ;
	if(*CT > *GLNTT ){
		x[i] = a[i][k];
		if(i==n-1)
			Cap_nhat_PATNTT(*TGT, GLNTT, x , PA , n );
		else 
			Nhanh_Can(i+1, k, a, TGT , CT ,GLNTT , x, PA, n);
	}
	//QUay lui xet
	x[i]= 0;
	*TGT = *TGT - a[i][k];

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
	int n ;
	readfile(a, &n);
	printdata(a, n);
	
	int x[n], pa[n], CT, TGT ,GLNTT;
	Khoi_tao_nut_goc(&TGT, &CT, &GLNTT, x, a, n);
	Nhanh_Can(1, 0 , a, &TGT , &CT ,&GLNTT, x, pa, n);
	printPA( pa , n);
	
	
	return 0;
}


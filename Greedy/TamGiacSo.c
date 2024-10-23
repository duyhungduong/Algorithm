#include <stdio.h>
#define size 100 
void readfile(char name[] ,int a[][size], int *n){
	FILE* f;
	f = fopen(name, "r");
	if(f == NULL){
		printf("Loiii\n");
		return ;
	} 
	int i=0;
	int j;
	while(!feof(f)){
		for(j =0 ; j<=i ; j++){
			fscanf(f, "%d" , &a[i][j]);
		}
		i++;
	}
	*n = i;
	fclose(f);
}

void in_dulieu_baitoan(int a[][size], int n){
	int i,j;
	for(i=0 ; i< n ; i++)
	{
		for(j = 0 ; j<=i ; j++)
			printf("%-3d", a[i][j]);
		printf("\n"); 
	}
}

int max(int a[][size] , int i, int j){
	if(j==0) return (a[i][0] > a[i][1]) ? 0 : 1; 
	if(a[i][j-1] > a[i][j] && a[i][j-1] > a[i][j+1])
		return j-1;
	if(a[i][j] > a[i][j-1] && a[i][j] > a[i][j+1])
		return j;
	if(a[i][j+1] > a[i][j] && a[i][j-1] < a[i][j+1])
		return j+1;
}

void greedy(int a[][size], int n , int x[]){
	x[0] = a[0][0];
	int i, k=0 ;
	for(i=1 ; i< n ; i++){
		k = max(a, i, k);
		x[i] = a[i][k];
	}
}

int sumPA(int x[], int n){
	int sum=0;
	int i;
	for(i=0 ; i<n ; i++) sum+=x[i];
	return sum;
}

void inPA(int x[], int n){
	int i;
	printf("Phuong an theo Greedy: \n");
	printf("%d ", x[0]);
	for(i=1; i<n ; i++){
		printf(" => %d " , x[i]);
	}
	printf("\nTong gia tri la: %d" , sumPA(x, n));
}
int main(){
	int a[size][size];
	int n ;
	readfile("Tam_giac_so.txt" , a, &n);
	in_dulieu_baitoan(a, n);  
	int x[n];
	greedy(a, n, x);
	inPA(x,n);
}



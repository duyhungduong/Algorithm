#include <stdio.h>
#define size 100
void readfile(char name[], int a[][size], int *n){
	FILE *f ;
	f = fopen (name , "r");
	if(f == NULL){
		printf("Loii\n");
		return ;
	}
	int i=0; int j;
	while(!feof(f)){
		for(j=0 ; j<=i ;j++ ){
			fscanf(f, "%d", &a[i][j]);
		}
		i++;
	}
	*n = i;
	fclose(f);
}

void in_data(int a[][size], int n){
	int i, j;
	for(i=0 ; i<n ; i++){
		for(j=0 ;j<=i; j++){
			printf("%-4d", a[i][j]);
		}
		printf("\n");
	}
		
}

int max(int a[][size], int i, int j){
	if(j==0)
		return (a[i][0] > a[i][1]) ? 0 : 1;
	if(a[i][j-1]>a[i][j] && a[i][j-1] > a[i][j+1])
		return j-1;
	if(a[i][j-1]<a[i][j] && a[i][j] > a[i][j+1])
		return j;
	if(a[i][j+1]>a[i][j] && a[i][j-1] < a[i][j+1])
		return j+1;
}

void greedy(int a[][size], int n , int pa[]){
	int i, j;
	pa[0] = a[0][0];
	j=0;
	for(i=1 ; i< n;i++){
		j= max(a , i , j);
		pa[i] = a[i][j];
	}
}

int sumPA(int pa[], int n){
	int sum=0;
	int i;
	for(i=0 ; i< n ;i++) sum+=pa[i];
	return sum;
}

void inPA(int pa[], int n){
	int i ;
	printf("%d ", pa[0]);
	for(i = 1 ; i< n; i++){
		printf(" => %d ", pa[i]);
	}
	printf("Tong gia tri la: %d ", sumPA(pa, n));
}

int main(){
	int a[size][size], n;
	readfile("Tam_giac_so.txt", a, &n);
	in_data(a, n);
	int pa[n];
	
	greedy(a, n, pa);
	inPA(pa , n);
}

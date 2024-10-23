#include <stdio.h>
#define size 100
void readfile(int a[][size] , int *n){
	FILE* f ;
	f = fopen("Tam_giac_so.txt", "r");
	if(f == NULL){
		printf("\nloiii\n");
		return ;
	}
	int i=0 ;
	int j;
	while(!feof(f)){
		for(j=0 ; j<=i; j++)
			fscanf(f, "%d", &a[i][j]);
		i++;
	}
	*n = i;
	fclose(f);
}

void in_dulieu(int a[][size] , int n){
	int i, j ;
	for(i=0 ; i<n ; i++){
		for(j= 0; j<=i ; j++)
			printf("%-3d", a[i][j]);
		printf("\n");
	}		
}

int max(int n , int a[][n], int i , int j ){
	if(j==0 ) return(a[i-1][0] > a[i-1][1] ) ? 0 : 1;
	if(j==i-1) return (a[i-1][i-1] > a[i-1][i-2] ) ? i-1 : i-2;
	if(j==i ) return i-1;
	
	if(a[i-1][j-1] > a[i-1][j] && a[i-1][j-1] > a[i-1][j+1])
		return j-1;
	if(a[i-1][j-1] < a[i-1][j] && a[i-1][j] > a[i-1][j+1])
		return j;
	if(a[i-1][j+1] > a[i-1][j] && a[i-1][j-1] < a[i-1][j+1])
		return j+1;
}


int cs_max_dongcuoi(int n, int f[][n]){
	int max = f[n-1][0];
	int index =0 ;
	int i;
	for(i=1 ; i<n ; i++ )
		if(f[n-1][i] > max){
			max = f[n-1][i];
			index  = i;
		}
			
	return index;
}


void tao_bang(int a[][size], int n, int f[][n]){
	f[0][0] = a[0][0];
	f[1][0] = a[1][0] + f[0][0];
	f[1][1] = a[1][1] + f[0][0];
	int i,j;
	for(i =2 ; i<n ; i++){
		for(j= 0 ; j<=i ; j++){
			int k = max(n, f, i, j);
			f[i][j] = a[i][j] + f[i-1][k];
		}
	}
}

void tra_bang(int a[][size], int n, int f[][n] , int pa[]){
	int k = cs_max_dongcuoi(n,f );
	
	printf("\n%d\n", k);
	pa[n-1] = a[n-1][k];
	int i;
	for(i= n-1 ; i>=1; i--){
		k = max(n, f, i , k);
		pa[i-1] = a[i-1][k];
	}
}



void in_bang(int n, int f[][n]){
	int i, j ;
	for(i=0 ; i<n ; i++){
		for(j= 0; j<=i ; j++)
			printf("%-3d", f[i][j]);
		printf("\n");
	}
}


int main(){
	int a[size][size];
	int n;
	readfile(a, &n);
	in_dulieu(a, n);
	
	int f[n][n];
	tao_bang(a , n, f);
	in_bang(n, f);
	int pa[n];
//	printf("max :%d  " , cs_max_dongcuoi(n , f));
	tra_bang(a, n, f, pa);
	int i; 
	for(i = 0 ; i < n ; i++) printf(" = > %d ", pa[i]);
}

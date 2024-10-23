#include <stdio.h>
#define size  50
void readfile(int a[][size] , int *n ){
	FILE *f;
	f= fopen ("Tam_giac_so.txt", "r");
	if(f == NULL){
		printf("LOIii")
		; return;
	}
	int i=0, j;
	while(!feof(f)){
		for(j=0; j<= i ;j++)	
			fscanf(f, "%d" , &a[i][j]);
		i++;
	}
	*n =i;
	fclose(f);
}
void printData(int a[][size], int n){
	int i, j;
	printf("Du lieu bai toan\n");
	for(i = 0 ; i<n ;i++){
		for(j = 0 ; j<= i ; j++)
			printf("%-2d",a[i][j] );
		printf("\n");
	}
}

int cs_max(int n , int f[][n], int i, int j){
	if(j== 0)
		return (f[i-1][0] > f[i-1][1]) ? 0 :1 ;
	if(j==i)
		return i-1;
	if(j==i-1)
		return (f[i-1][i-1] > f[i-1][i-2]) ? i-1 : i-2;
	
	
	if(f[i-1][j-1] > f[i-1][j] && f[i-1][j-1] > f[i-1][j+1])
		return j-1;
	if(f[i-1][j] > f[i-1][j-1] && f[i-1][j] > f[i-1][j+1])
		return j;
	if(f[i-1][j+1]> f[i-1][j-1] &&f[i-1][j+1] > f[i-1][j])
		return j+1;
}

void tao_bang(int a[][size], int n , int f[][n]){
	f[0][0] = a[0][0];
	f[1][0] = a[1][0] + f[0][0];
	f[1][1] = a[1][1] + f[0][0];
	int i,j ;
	
	for(i=2; i<n ; i++){
		for(j=0; j<=i; j++){
			int k = cs_max(n, f, i,j);
			f[i][j] = a[i][j] + f[i-1][k];
		}
	}
}

void  in_bang(int n , int f[][n]){
	printf("\nTa co bang F:\n");
	int i,j ;
	for(i=0; i<n ; i++){
		for(j=0 ; j<=i ; j++){
			printf("%-6d", f[i][j]);
		}
		printf("\n");
	}
}

int cs_max_dongcuoi(int f[], int j){
	int somax = f[0];
	int index = 0;
	int i;
	for(i = 1 ; i <= j ; i++)
		if(f[i] > somax){
			somax = f[i];
			index = i;
		}
	return index;
}

//	int max = f[0];
//    int i,index = 0;
//    for(i=1 ; i<=j ;i++){
//        if(f[i]> max){
//            max = f[i];
//            index = i;
//        }
//    }
//    return index;
void tra_bang(int a[][size] , int n , int f[][n], int pa[]){
	int i, j;
	j = cs_max_dongcuoi(f[n-1], n-1 );
	pa[n-1] = a[n-1][j];
	for(i= n-1 ; i>= 1 ; i--){
		j = cs_max(n, f , i, j);
		pa[i-1] = a[i-1][j];
	}
}
//	int i,j;
//    j = cs_max_dongcuoi(f[n-1], n-1);
//    pa[n-1] = a[n-1][j];
//    for(i=n-1 ; i>=1; i--){
//        j = cs_max(n,f,i,j);
//        pa[i-1] = a[i-1][j];
//    }
int sumPA(int pa[], int n){
	int sum=0;
	int i; for(i=0 ; i<n ;i++) sum+=pa[i];
	return sum;
}

void printPA(int pa[], int n ){
	printf("\n\nPhuong an Quy Hoach Dong:\n");
	printf("Duong di la:\n %d" ,pa[0]);
	int i;
	for(i=1; i< n ; i++){
		printf(" => %d" , pa[i]);	
	} 
	printf("\nTong gia tri la: %d ",sumPA(pa , n));
}
int main (){
	int a[size][size], n;
	readfile(a, &n );
	printData(a, n);
	
	int f[n][n], pa[n];
	tao_bang(a, n, f);
	in_bang(n, f);
	tra_bang(a, n, f, pa);
	printPA(pa, n);
}

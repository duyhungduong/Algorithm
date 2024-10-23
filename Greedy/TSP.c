#include <stdio.h>

typedef struct {
	int dau ,cuoi ;
	float do_dai;
}canh;

#define size 100
void realfile(char name[], canh a[], int *n){
	FILE* f;
	f = fopen(name ,"r");
	if(f == NULL){
		printf("Loii\n");
		return;
	}
	
	int i,j ,t, k=0;
	float temp;
	fscanf(f, "%d" , n);
	for(i = 0 ; i< *n ; i++){
		for(j= i ; j<*n; j++)
			if(j==i) for(t= 0; t<=j ; t++) fscanf(f, "%f" ,&temp);
			else{
				fscanf(f , "%f" , &a[k].do_dai );
				a[k].dau = i;
				a[k].cuoi = j;
				k++;
			}
	}
	fclose(f);
	
}

void in_Ds_canh(canh a[], int n ,int laPa){
	int i;
	float sum = 0;
	for(i = 0 ; i<n ; i++){
		printf("%-3d %c%c = %9.2f\n" ,i+1, a[i].dau + 65 , a[i].cuoi +65 , a[i].do_dai );
		if(laPa) sum+= a[i].do_dai;
	}
	if(laPa) printf("Tong chi phi: %9.2f", sum);
}

void swap(canh *x , canh *y){
	canh temp = *x;
	*x = *y;
	*y = temp;
}

void bubble_sort(canh a[], int n){
	int i,j;
	for(i= 0; i< n-1 ; i++)
		for(j=n-1 ; j> i ; j--){
			if(a[j].do_dai < a[j-1].do_dai)
				swap(&a[j], &a[j-1]);
		}
}

int dinhcap3(canh x[] ,int k, canh moi){
	int i=0 , dem=1 ;
	while(i<k && dem<=3){
		if(moi.dau == x[i].dau || moi.dau == x[i].cuoi)
			dem++;
		i++;
	}
	if(dem == 3 ) return 1;
	i =0 , dem =1 ;
	while(i<k && dem<=3){
		if(moi.cuoi == x[i].dau || moi.cuoi == x[i].cuoi)
			dem++;
		i++;
	}
	return dem==3;
}

void init_parent(int parent[], int n){
	int i;
	for(i=0 ; i< n ;i++)
		parent[i] = i;
}

int find_root(int parent[] , int u){
	while(u!=parent[u])
		u = parent[u];
	return u;
}

void update_parent(int parent[], int r1 , int r2){
	parent[r2] =r1;
}

int co_chu_trinh(int rdau , int rcuoi){
	return rdau == rcuoi;
}

void greedy(canh a[] , int n ,canh pa[]){
	int parent[n] ;
	init_parent(parent, n);
	int rdau , rcuoi;
	int j=0 , i;
	for(i=0 ; i<n*(n-1)/2 && j < n-1 ; i++){
		rdau = find_root(parent, a[i].dau);
		rcuoi = find_root(parent, a[i].cuoi);
		if(!dinhcap3(pa, j, a[i]) && !co_chu_trinh(rdau, rcuoi)){
			pa[j] = a[i];
			j++;
			update_parent(parent, rdau ,rcuoi);
		}
	}
	for(; i<n*(n-1)/2; i++){
		rdau = find_root(parent , a[i].dau);
		rcuoi = find_root(parent, a[i].cuoi);
		
		if(!dinhcap3(pa, j, a[i]) && co_chu_trinh(rdau, rcuoi)){
			pa[n-1] = a[i];
			break;
		}
	}
}

int main(){
	canh a[size];
	int n ;
	realfile("TSP1.txt" , a , &n);
	bubble_sort(a, n*(n-1)/2);
	canh x[n];
	greedy(a, n, x  );
	in_Ds_canh(a , n*(n-1)/2 , 0);
	printf("\nGreedy:\n");
	in_Ds_canh(x, n , 1);
	
}

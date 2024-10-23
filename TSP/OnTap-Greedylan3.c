#include <stdio.h>

typedef struct{
	int dau,cuoi;
	float do_dai;
}canh;

void readfile(char name[], canh a[], int *n){
	FILE *f;
	f =fopen ( name , "r");
	if(f == NULL){
		printf("Loi doc file\n\n\n");
		return;
	}
	int i,j , t;
	double temp;
	int k=0;
	fscanf(f , "%d" , n);
	for(i=0 ; i<*n ; i++)
		for(j=i ; j<*n ; j++ ){
			if(j==i) for(t=0; t<=j; t++) fscanf(f, "%f", &temp);
			else{
				fscanf(f, "%f", &a[k].do_dai);
				a[k].dau = i;
				a[k].cuoi = j;
				k++;
			}
		}
	fclose(f);
}
void in_ds_canh(canh a[], int n, int laPA){
	int i;
	double sum=0;
	for(i=0 ; i<n ; i++){
		printf("%-3d %c%c  = %8.2f\n", i+1, a[i].dau+65 , a[i].cuoi +65  ,a[i].do_dai );
		if(laPA) sum+=a[i].do_dai;
	}
	if(laPA) printf("\nTong gia tri: %8.2f", sum);
}

void swap(canh *x, canh *y){
	canh temp = *x;
	*x = *y;
	*y = temp;
}
void bubblesort(canh a[], int n){
	int i,j;
	for(i=0 ; i<n-1; i++)
		for(j=n-1 ; j>i; j--)
			if(a[j].do_dai < a[j-1].do_dai)
				swap(&a[j], &a[j-1]);
}

void init_forest(int parent[], int n){
	int i; 
	for(i=0 ; i<n ; i++)
		parent[i] = i;
}

int find_root(int parent[], int u){
	while(u!= parent[u])
		u = parent[u];
	return u;
}

int dinhcap3(canh pa[], int k , canh moi){
	int i=0 , dem =1 ;
	while(i < k && dem <3 ){
		if(moi.dau == pa[i].dau || moi.dau == pa[i].cuoi){
			dem++;
		}
		i++;
	}
	if(dem == 3) return 1;
	i  = 0 ; dem = 1;
	while (dem < 3 && i<k ){
		if(moi.cuoi == pa[i].dau || moi.cuoi == pa[i].cuoi){
			dem++;
		}
		i++;
	}
	return dem==3;
}
void update_forest(int parent [], int rdau, int rcuoi){
	parent[rcuoi] = rdau;
}

int chu_trinh(int rdau,int rcuoi){
	return rdau==rcuoi;
}
void greedy(canh a[], int n , canh pa[]){
	int i , j = 0 ;
	int parent [n];
	init_forest(parent, n);
	int rdau , rcuoi ;
	for(i = 0 ; i<n*(n-1)/2 && j<n-1 ; i++){
		rdau = find_root(parent , a[i].dau);
		rcuoi = find_root(parent, a[i].cuoi);
		if(!dinhcap3(pa, j , a[i]) && !chu_trinh(rdau , rcuoi)){
			pa[j] = a[i];
			j++;
			update_forest(parent, rdau ,rcuoi);
		}
	}
	
	for(; i<n*(n-1)/2 ; i++){
		rdau = find_root(parent, a[i].dau);
		rcuoi = find_root(parent, a[i].cuoi);
		if(!dinhcap3(pa, j, a[i]) && chu_trinh(rdau , rcuoi) ){
			pa[n-1] = a[i];
			break;
		}
	}
		
}

int main(){
	canh a[100];
	int n ;
	readfile("TSPData.txt" , a , &n );
	in_ds_canh(a, n*(n-1)/2 , 0);
//	printf("\n\nDanh sach sau khi sap xep cac canh\n");
	bubblesort(a, n*(n-1)/2);
	in_ds_canh(a, n*(n-2)/2, 0);
	
//	canh pa[n];
//	greedy(a , n, pa );
//	in_ds_canh(pa , n , 1);
	
}



#include <stdio.h>
typedef struct{
	int dau , cuoi;
	double do_dai;
}canh;

void readfromfile(char nam[], canh a[], int *n){
	FILE *f;
	f = fopen( nam ,"r" );
	if(f==NULL){
		printf("Ko doc duoc file\n");
		return ;
	}
	fscanf(f, "%d", n );
	int k=0;
	int i,j, t;
	double temp;
	for(i=0 ; i<*n ; i++)
		for(j = i ; j<*n ; j++){
			if(i==j) for(t=0; t<=j ; t++) fscanf(f , "%lf", &temp);
			else{
				fscanf(f, "%lf", &a[k].do_dai);
				a[k].dau = i;
				a[k].cuoi = j;
				k++;
			} 
		}
	fclose(f);
}

void in_ds_canh(canh a[], int n , int la_PA){
	int i ; double tong = 0;
	for(i=0 ; i< n ; i++){
		printf("%-3d %c%c = %lf\n", i+1 , a[i].dau+65 , a[i].cuoi+65 ,a[i].do_dai);
		if(la_PA) tong+= a[i].do_dai;
	}
	if(la_PA)printf("\n\nTong chi phi la: %lf\n", tong);
}

void swap(canh *a , canh *b ){
	canh temp = *a ;
	*a = *b ;
	*b = temp;
}

void bubble(canh a[], int n){
	int i,j;
	for(i=0 ; i< n-1 ; i++)
		for(j=n-1 ; j>i  ; j--)
			if(a[j].do_dai < a[j-1].do_dai)
				swap(&a[j], &a[j-1]);
}
int dinhcap3(canh pa[], int k , canh moi){
	int i=0, dem = 1;
	while( i < k && dem <= 3 ){
		if(moi.dau == pa[i].dau || moi.dau ==pa[i].cuoi)
			dem++;
		i++;
	}
	if(dem == 3 ) return 1;
	i=0; dem =1 ;
	while( i< k && dem <= 3){
		if(moi.cuoi == pa[i].dau || moi.cuoi == pa[i].cuoi)
			dem++;
		i++;
	}
	return dem ==3;
}

void initforest(int parent[], int n){
	int i;
	for(i=0 ; i<n ; i++)
		parent[i] = i;
}


int find_root(int parent[], int u){
	while(u != parent[u]){
		u = parent[u];
	}
	return u;
}
void updateforest(int parent[], int r1 , int r2){
	parent[r2] = r1;
}

int chu_trinh(int r1, int r2)
{
	return r1 == r2;
}


void greedy(canh a[], int n , canh pa[]){
	int i,j;
	int parent[n];
	initforest(parent, n);
	int rdau , rcuoi ;
	j=0;
	for(i=0 ; i<n*(n-1)/2 && j<n-1 ; i++){
		rdau = find_root(parent, a[i].dau );
		rdau = find_root(parent, a[i].cuoi);
		if(!dinhcap3(pa, j, a[i]) && !chu_trinh(rdau, rcuoi)){
			pa[j] = a[i];
			j++;
			updateforest(parent, rdau, rcuoi);
		}
	}
	for(; i<n*(n-1)/2 ; i++){
		rdau = find_root(parent, a[i].dau);
		rcuoi = find_root(parent, a[i].cuoi);
		if(!dinhcap3(pa ,j, a[i])&& chu_trinh(rdau , rcuoi)){
			pa[j] = a[i];
			break;
		}
	}
}

int main(){
	canh a[100];
	int n;
	readfromfile("TSPData.txt", a , &n);
	in_ds_canh(a, n*(n-1)/2 ,0);
	
	bubble(a, n*(n-1)/2);
	printf("\nDanh sach sau khi sap xep la:\n");
	in_ds_canh(a, n*(n-1)/2 ,0);
	canh pa[n];
	greedy(a, n*(n-1)/2, pa);
	in_ds_canh(pa, n , 1);
	
}

#include <stdio.h>
#include <malloc.h>
typedef struct {
	float DG, TL, GT;
	int So_DV_Duoc_Chon;
	char ten[30];
}DoVat;

DoVat* readfile(char name[], float *w, int *n){
	FILE *f;
	f = fopen(name, "r");
	if(f ==NULL){
		printf("Loiii\n");
		return;
	}
	int i=0  ;
	DoVat* a;
	a = (DoVat*) malloc(sizeof(DoVat));
	fscanf(f, "%f" , w);
	while(!feof(f)){
		fscanf( f , "%f%f%[^\n]", &a[i].TL , &a[i].GT , &a[i].ten );
		a[i].DG = a[i].GT/a[i].TL;
		a[i].So_DV_Duoc_Chon = 0;
		i++;
		a = realloc(a, sizeof(DoVat)*(i+1));
	}
	*n = i;
	fclose(f);
	return a;
}

void in_ds_DV (DoVat* a, int n , float w){
	int i;
	float sumTL =0 , sumGT =0 ; 
	for(i =0 ; i< n ; i++){
		printf("%-3d %-20s %9.2f %9.2f %9.2f %3d\n" , i+1, a[i].ten , a[i].TL , a[i].GT , a[i].DG , a[i].So_DV_Duoc_Chon );
		sumTL += a[i].So_DV_Duoc_Chon*a[i].TL;
		sumGT += a[i].So_DV_Duoc_Chon*a[i].GT;
	}
	printf("\nBalo co the chua: %9.2f\n" ,w);
	printf("Tong TL hien tai: %9.2f, Tong Gia Tri hien tai: %9.2f", sumTL , sumGT);
}

void swap(DoVat* x, DoVat* y ){
	DoVat temp = *x; *x =*y ; *y = temp;
}

void bubblesort(DoVat* a, int n){
	int i, j;
	for(i= 0 ; i< n-1 ;i++)
		for(j= n-1 ; j>i ; j-- )
			if(a[j].DG > a[j-1].DG )
				swap(&a[j] , &a[j-1]);
}

void greedy(DoVat* a, int n , float w){
	int i;
	for(i= 0 ; i< n ; i++){
		a[i].So_DV_Duoc_Chon = (w/a[i].TL);
		w-= a[i].So_DV_Duoc_Chon*a[i].TL;
	}
}

int main(){
	float w; int n ;
	DoVat* a = readfile("CaiTui1.txt" , &w, &n);
	bubblesort(a, n);
	greedy(a, n ,w);
	in_ds_DV(a, n ,w);
	
}

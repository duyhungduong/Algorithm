#include <stdio.h>
#include <malloc.h>
#include <string.h>


typedef struct{
	float DG,TL,GT;
	char ten[50];
	int sodovatduocchon;
}DoVat;

DoVat* readfile(float *w, int *n){
	FILE *f ;
	f = fopen("CaiTui1.txt", "r");
	if(f==NULL){
		printf("Loi\n");
		return;
	}
	DoVat* dsdv;
	fscanf(f,"%f" ,w );
	int i= 0 ;
	dsdv = (DoVat*) malloc(sizeof(DoVat));
	while(!feof(f)){
		fscanf(f , "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT , &dsdv[i].ten);
		dsdv[i].DG  = dsdv[i].GT/dsdv[i].TL;
		dsdv[i].sodovatduocchon = 0;
		i++;
		dsdv = realloc(dsdv, sizeof(DoVat)*(i+1));
		
	}
	*n = i;
	fclose(f);
	return dsdv;
}
void greedy(DoVat* dsdv, int n, float w ){
	int i;
	for(i=0 ; i<n ; i++){
		dsdv[i].sodovatduocchon = (w/dsdv[i].TL);
		w -= dsdv[i].sodovatduocchon*dsdv[i].TL;
	}
}
void swap(DoVat *a, DoVat *b){
	DoVat temp  = *a;
	*a = *b;
	*b = temp;
}

void bubblesort(DoVat* dsdv, int n){
	int i,j;
	for(i=0; i<n-1 ; i++)
		for(j=n-1; j>i ;j--)
			if(dsdv[j].DG > dsdv[j-1].DG)
				swap(&dsdv[j] , &dsdv[j-1]);
}

void InDSDV(DoVat *dsdv , int n , float w){
	int i;
	float tongTL = 0.0 , tonggt = 0.0;
	printf("\nPhuong an thu duoc tu ky that ThamAn nhu sau : \n");
	
	printf("|---|--------------------|---------|---------|-----------|-------------------|\n");
	printf("|STT|-----Ten Do Vat-----|T. Luong |-Cia Tri-|--Don Gia--|So Do Vat Duoc Chon|\n");
	printf("|---|--------------------|---------|---------|-----------|-------------------|\n");
	for (i=0; i<n ; i++){
		printf("|%-3d|%-20s|%9.2f|%9.2f|           |  %8d         |\n", i+1, dsdv[i].ten, dsdv[i].TL, dsdv[i].GT, dsdv[i].sodovatduocchon);
		tonggt = tonggt + dsdv[i].sodovatduocchon*dsdv[i].GT;
		tongTL = tongTL + dsdv[i].sodovatduocchon*dsdv[i].TL;
	}
	
	printf("|---|--------------------|---------|---------|-----------|-------------------|\n");
	printf("\nTrong luong cua balo = %-9.2f\n " ,w);
	printf("\nTong trong luong cac vat duoc chon la : %-9.2f\n\n Tong gia tri la: %-9.2f", tongTL, tonggt);


}
int main(){
	DoVat* dsdv;
	int n;float w;
	dsdv = readfile(&w, &n);
	
	bubblesort(dsdv, n);
	greedy(dsdv, n , w);
	InDSDV(dsdv , n ,w);
	free(dsdv);
	
}


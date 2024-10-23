#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct{
    char tenDV[20];
    float DG, GT, TL;
    int so_dv_dc_chon;
}DoVat;

DoVat* readfromfile(float *w , int *n){
    FILE *f; 
    f = fopen("CaiTui1.txt", "r");
    fscanf(f, "%f" , w);
    DoVat* dsdv;
    dsdv = (DoVat*)malloc(sizeof(DoVat));
    if(f == NULL){
        printf("Loiiiii!!!!!!");
        return ;
    }
    int i=0;
    while(!feof(f)){
        fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT , &dsdv[i].tenDV);
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
        dsdv[i].so_dv_dc_chon = 0 ;
        i++;
        dsdv = realloc(dsdv , sizeof(DoVat)*(i+1));
    }
    *n=i;
    fclose(f);
    return dsdv;
}
void swap(DoVat *x , DoVat *y){
    DoVat temp = *x ;
    *x = *y ;
    *y = temp;
}
void bubblesort(DoVat *dsdv , int m){
    int i, j;
    for(i=0 ; i<m-1; i++)
        for(j=m-1 ; j>i ; j--)
            if(dsdv[j].DG > dsdv[j-1].DG)
                swap(&dsdv[j], &dsdv[j-1]);
}

void indsdv(DoVat *dsdv, int n , float w){
    int i ;
    float sumTL=0.0, sumGT =0.0;
    printf("Greeedy: \n\n");
    for(i=0 ; i<n ; i++){
        printf("%-3d|%-20s|%9.2f|%9.2f|%9.2f|%3d\n", i+1,dsdv[i].tenDV, dsdv[i].TL , dsdv[i].GT, dsdv[i].DG, dsdv[i].so_dv_dc_chon);
        sumTL+=dsdv[i].so_dv_dc_chon*dsdv[i].TL;
        sumGT+=dsdv[i].so_dv_dc_chon*dsdv[i].GT;
    }
    printf("\n");
    printf("Tong Gt: %9.2f\n", sumGT);
    printf("Tong TL: %9.2f, Ban dau la: %9.2f\n", sumTL, w);
}

void greedy(DoVat* dsdv , int n , float w ){
	int i;
	for (i=0; i<n ; i++){
		dsdv[i].so_dv_dc_chon = (w/dsdv[i].TL);
		w = w-dsdv[i].so_dv_dc_chon*dsdv[i].TL;
	}
}


int main(){
    int n ;
    float w;
    DoVat* dsdv;
    dsdv = readfromfile(&w, &n);
    bubblesort(dsdv , n);
    greedy(dsdv, n ,w);
    indsdv(dsdv, n ,w);
    free(dsdv);
}

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
    char tenDV[20];
    float TL,GT,DG;
    int soDVduocchon;
}DoVat;

DoVat* readfromfile(float *w, int *n){
    FILE *f;
    f = fopen("CaiTui1.txt", "r");
    fscanf(f, "%f", w);
    DoVat *dsdv;
    dsdv = (DoVat*) malloc (sizeof(DoVat));
    int i =0 ;
    while(!feof(f)){
        fscanf(f, "%f%f%[^\n]" , &dsdv[i].TL , &dsdv[i].GT, &dsdv[i].tenDV);
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
        dsdv[i].soDVduocchon =0;
        i++;
        dsdv = realloc(dsdv, sizeof(DoVat)*(i+1));

    }
    *n =i ;
    fclose;
    return dsdv;
}
void swap(DoVat *x, DoVat *y){
    DoVat t = *x;
    *x = *y;
    *y = t;
}
void bubblesort(DoVat *dsdv, int m){
    int i, j;
    for(i=0; i<m-1 ;i++)
        for(j=m-1; j>i;j++)
            if(dsdv[j].DG > dsdv[j-1].DG)
                swap(&dsdv[j], &dsdv[j-1]);
}
void inDsdv(DoVat *dsdv , int n , float w){
    int i;
    float tongTL = 0, tongGT = 0; 
    printf("\n phuong an duoc tu ky thuat GREEDY nhu sau: \n");

    printf("|---|--------------------|---------|---------|-----------|-------------------|\n");
	printf("|STT|-----Ten Do Vat-----|T. Luong |-Cia Tri-|--Don Gia--|So Do Vat Duoc Chon|\n");
	printf("|---|--------------------|---------|---------|-----------|-------------------|\n");
    for(i=0 ; i <n ; i++){
        printf("|%-3d|%-20s|%9.2f|%9.2f|           |  %8d         |\n", i+1 , dsdv[i].tenDV , dsdv[i].TL , dsdv[i].GT , dsdv[i].soDVduocchon);
        tongGT += dsdv[i].soDVduocchon*dsdv[i].DG;
        tongTL += dsdv[i].soDVduocchon*dsdv[i].TL;
    }
    printf("|---|--------------------|---------|---------|-----------|-------------------|\n");
	printf("\nTrong luong cua balo = %-9.2f\n " ,w);
	printf("\nTong trong luong cac vat duoc chon la : %-9.2f\n\n Tong gia tri la: %-9.2f", tongTL, tongGT);
}
void greedy(DoVat *dsdv, int n , float w){
    int i ;
    for (i=0 ; i<n ; i++){
        dsdv[i].soDVduocchon = (w/dsdv[i].TL);
        w = w-dsdv[i].soDVduocchon*dsdv[i].TL;
    }
}
int main (){
    int n ;
    float w;
    DoVat* dsdv;
    dsdv = readfromfile (&w, &n);
    bubblesort(dsdv, n);
    greedy(dsdv, n ,w);
    inDsdv(dsdv,n,w);
    free(dsdv);
}
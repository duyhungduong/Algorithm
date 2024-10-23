#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct{
    char tenDV[20];
    float DG, GT, TL;
    int SL, so_dv_dc_chon;
}DoVat;

DoVat* readfromfile(float *w , int *n){
    FILE *f; 
    f = fopen("CaiTui3.txt", "r");
    fscanf(f, "%f" , w);
    DoVat* dsdv;
    dsdv = (DoVat*)malloc(sizeof(DoVat));
    if(f == NULL){
        printf("Loiiiii!!!!!!");
        return ;
    }
    int i=0;
    while(!feof(f)){
        fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT ,&dsdv[i].SL, &dsdv[i].tenDV);
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
    printf("NhanhCan: \n\n");
    for(i=0 ; i<n ; i++){
        printf("%-3d|%-20s|%9.2f|%9.2f|%9.2f|%5d|%3d\n", i+1,dsdv[i].tenDV, dsdv[i].TL , dsdv[i].GT, dsdv[i].DG, dsdv[i].SL,dsdv[i].so_dv_dc_chon);
        sumTL+=dsdv[i].so_dv_dc_chon*dsdv[i].TL;
        sumGT+=dsdv[i].so_dv_dc_chon*dsdv[i].GT;
    }
    printf("\n");
    printf("Tong Gt: %9.2f\n", sumGT);
    printf("Tong TL: %9.2f, Ban dau la: %9.2f\n", sumTL, w);
}
void tao_nut_goc(float w, float* tlconlai, float* ct, float* gialntt, float* tgt , float don_gia_lon_nhat){
    *tgt = 0;
    *tlconlai = w;
    *ct = *tlconlai*don_gia_lon_nhat;
    *gialntt = 0;
}
void cap_nhat_pa_tntt(float tgt, float* gialntt, int x[], DoVat* dsdv, int n ){
    int i;
    if(*gialntt < tgt ){
        *gialntt = tgt;
        for(i=0; i<n ; i++)
            dsdv[i].so_dv_dc_chon = x[i];
    }
}
int min(int a, int b){
    return a<b ? a:b;
}
void nhanh_can(int i , float *tgt, float *ct, float *tlconlai, float* gialntt, int x[], DoVat* dsdv, int n){
    int j ;
    int sodovatlonnhatcothechon = min(dsdv[i].SL , *tlconlai/dsdv[i].TL);

    for(j=sodovatlonnhatcothechon; j>=0; j--){
        *tgt = *tgt + j*dsdv[i].GT;
        *tlconlai -=  j*dsdv[i].TL;
        *ct = *tgt + *tlconlai*dsdv[i+1].DG;
        if(*ct > *gialntt){
            x[i] = j;
            if((i==n-1)||(*tlconlai==0.0)){
                cap_nhat_pa_tntt(*tgt, gialntt, x, dsdv, n);
            }
            else
                nhanh_can(i+1, tgt, ct, tlconlai , gialntt, x ,dsdv, n);
        }
        x[i]= 0;
        *tgt -= j*dsdv[i].GT;
        *tlconlai += j*dsdv[i].TL;
    }
}


int main(){
    DoVat* dsdv;
    int n ;
    float w;
    float ct, tgt, tlconlai, gialntt;
    dsdv = readfromfile(&w, &n);
    int x[n];
    bubblesort(dsdv, n);
    tao_nut_goc(w, &tlconlai , &ct, &gialntt, &tgt , dsdv[0].DG);
    nhanh_can(0, &tgt , &ct, &tlconlai, &gialntt, x, dsdv, n);
    indsdv(dsdv, n,w);
    
    free(dsdv);
}

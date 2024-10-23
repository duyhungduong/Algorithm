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
// void taobang(DoVat* dsdv, int n , int w, float f[][w+1], int x[][w+1]){
//     int xk ,yk , k;
//     int xmax, v;
//     float fmax;
//     for(v= 0 ; v<=w ; v++){
//         x[0][v] = v/dsdv[0].TL;
//         f[0][v] = x[0][v] * dsdv[0].GT;
//     }
//     for(k=1 ; k<n ; k++){
//         for((v=0 ; v<=w ;v++)){
//             fmax = f[k-1][v];
//             xmax = 0;
//             yk = v/dsdv[k].TL;
//             for(xk=1; xk<=yk ;xk++){
//                 if(f[k-1][v-xk*dsdv[k].Tl)
//             }
//         }
//     }
// }

void taobang(DoVat* dsdv, int n ,int w, float f[][w+1], int x[][w+1]){
    int xk, yk,k;
    int xmax;
    int v;
    float fmax ;
//Dien gia tri cho dong dau
    for(v=0;v<=w;v++){
        x[0][v] = v/dsdv[0].TL;
        x[0][v] = x[0][v]*dsdv[0].GT;
    }
//Dien cac dong con lai
    for(k=0 ; k<n ; k++)
        for(v=0; v<=w; v++) {
            fmax = f[k-1][v];
            xmax =0; 
            yk = v/dsdv[k].TL;
            for(xk =1 ; xk<=yk ; xk++){
                if(f[k-1][v - xk * dsdv[k].TL]+xk*dsdv[k].GT > fmax){
                    fmax = f[k-1][v - xk*dsdv[k].TL + xk*dsdv[k].GT];
                    xmax = xk;
                }
            }
            f[k][v] = fmax ;
            x[k][v] = xmax;
        }
}

void in_bang(int n, int w, float f[][w+1], int x [][w+1]){
    int v,k;
    printf("Bang F:\n");
    for(k=0; k<n; k++){
        for(v=0 ; v<=w ;v++){
            printf("%c%4.1f|%2d", 186,f[k][v], x[k][v]);
        }
        printf("%c\n",186);
    }
}

void tra_bang(DoVat* dsdv, int n ,int w, int x[][w+1]){
    int k, v;
    v =w ;
    for(k=n-1 ; k>= 0 ; k--){
        dsdv[k].so_dv_dc_chon = x[k][v];
        v= v-x[k][v]*dsdv[k].TL;
    }
}

int main(){
    int n ;
    float w;
    DoVat* dsdv;
    dsdv = readfromfile(&w, &n);
    
    indsdv(dsdv, n ,w);
    free(dsdv);
}

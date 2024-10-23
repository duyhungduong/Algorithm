#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct{
	float TL,DG,GT;
	int SL, So_DV_Duoc_Chon;
	char ten[30];
}DoVat;

DoVat* readfile(char name[], float *w , int *n){
	FILE *f ;
	f =fopen (name , "r");
	if(f==NULL){
		printf("Loii\n");
		return ;
	}
	DoVat* dsdv ;
	dsdv = (DoVat*) malloc(sizeof(DoVat));
	int i=0;
	fscanf(f , "%f" , w);
	while(!feof(f)){
		fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL , &dsdv[i].GT , &dsdv[i].SL , &dsdv[i].ten);
		dsdv[i].So_DV_Duoc_Chon = 0;
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
		i++;
		dsdv = realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}

void InDSDV (DoVat* dsdv, int n , float w ){
	int i;
	float tongT = 0 , tongL =0 ;
	for(i=0 ; i<n ;i++){
		printf("%-3d %30s %9.2f %9.2f %9.2f %3d %3d\n", i+1 , dsdv[i].ten , dsdv[i].TL , dsdv[i].GT , dsdv[i].DG , dsdv[i].SL , dsdv[i].So_DV_Duoc_Chon);
		tongT+= dsdv[i].So_DV_Duoc_Chon*dsdv[i].GT;
		tongL+=dsdv[i].So_DV_Duoc_Chon*dsdv[i].TL;
	}
	printf("\nTong trong luong balo la: %9.2f\n", w);
	printf("\nTong gia tri: %9.2f", tongT);
	printf("\nTong trong luong hien tai: %9.2f", tongL);
}

void swap(DoVat *x, DoVat *y ){
	DoVat temp = *x ;
	*x = *y ;
	*y = temp;
}

void bubble_sort(DoVat* dsdv , int n ){
	int i,j ;
	for(i =0 ; i< n-1 ; i++)
		for(j = n-1 ; j> i ; j--)
			if(dsdv[j].DG > dsdv[j-1].DG )
				swap(&dsdv[j], &dsdv[j-1]);
}
void Cap_Nhat_PA_TNTT(float TGT ,float* GiaLNTT , float* CT , int x[] , DoVat* a , int n){
    int i;
    if(*GiaLNTT < TGT ){
        *GiaLNTT = TGT ;
        for(i=0 ; i<n ;i++ )
            a[i].So_DV_Duoc_Chon = x[i];
    }
}
int min(int a, int b){
    return a<b?a:b;
}
void NhanhCan(int i ,float* TGT ,float* CT ,float* TLConLai , float* GiaLNTT, int x[], DoVat* a, int n){
    int j = 0;
    int So_DV_toida = min(a[i].SL , *TLConLai/a[i].TL);
    for(j= So_DV_toida ; j>=0 ; j--){
        *TGT += j*a[i].GT;
        *TLConLai -=j*a[i].TL;
        *CT = *TGT + *TLConLai*a[i].DG;
        if(*CT > *GiaLNTT){
            x[i] = j;
            if((i==n-1) || *TLConLai == 0){
                Cap_Nhat_PA_TNTT(*TGT , GiaLNTT , CT , x, a,  n);
            }else
                NhanhCan(i+1, TGT , CT , TLConLai , GiaLNTT , x , a, n);
        }
        *TGT -= j*a[i].GT;
        *TLConLai +=j*a[i].TL;
        x[i] = 0;
    }
}


int main(){
	DoVat* dsdv; 
	int n;
	float w; 
	dsdv = readfile("CaiTui3.txt", &w ,&n );
	bubble_sort(dsdv, n);
	float CT ,TGT ,TLConLai, GiaLNTT;
    int x[n];
    TGT = 0;
    GiaLNTT = 0;
    CT = w*dsdv[0].DG;
    TLConLai = w;
	
    NhanhCan(0, &TGT , &CT , &TLConLai , &GiaLNTT , x,dsdv, n );
    InDSDV(dsdv , n, w);
	free(dsdv);
}

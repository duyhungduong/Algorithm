#include <stdio.h> 
#include <malloc.h>
#include <string.h>
typedef struct {
	float TL, DG, GT ;
	char ten[30];
	int SL, So_dv_duoc_chon;  
}DoVat;

DoVat* readfile(char name[],float *w, int *n){
	FILE* f;
	f = fopen(name , "r");
	if(f==NULL){
		printf("Loiii\n");
		return;
	}
	int i=0;
	DoVat *dsdv;
	dsdv = (DoVat*) malloc(sizeof(DoVat));
	fscanf(f , "%f", w);
	while(!feof(f)){
		fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL ,&dsdv[i].GT , &dsdv[i].SL ,&dsdv[i].ten);
		dsdv[i].So_dv_duoc_chon = 0 ;
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
		i++;
		dsdv = realloc(dsdv , sizeof(DoVat)*(i+1) );
	}
	*n =i ;
	fclose(f);
	return dsdv;
}
void swap(DoVat *a , DoVat* b){
	DoVat temp = *a ;
	*a = *b;
	*b = temp;
}

void bubble_sort(DoVat *a, int n){
	int i,j;
	for(i=0 ; i<n-1 ; i++)
		for(j=n-1 ; j>i; j--)
			if(a[j].DG > a[j-1].DG)
				swap(&a[j], &a[j-1]); 
}
void InDSDV(DoVat* dsdv , int n , float w){
	int i ;
	float TongTL = 0.0 , TongGT = 0.0 ;
	printf("\n Phuong an thu duoc tu Ky thuat NHANH CAN nhu sau: \n");
	printf("|---|--------------------|---------|---------|--------|---------|---------------|\n");
	printf("|STT|---  Ten Do Vat  ---|-T.Luong-|-Gia Tri-|So luong| Don Gia |So DV duoc chon|\n");
	printf("|---|--------------------|---------|---------|--------|---------|---------------|\n");
	for (i=0 ; i<n ;i++){
			printf("|%-3d|%-20s|%9.2f|%9.2f|%5d   |%9.2f|%8d   	|\n", i+1, dsdv[i].ten, dsdv[i].TL, dsdv[i].GT, dsdv[i].SL, dsdv[i].DG, dsdv[i].So_dv_duoc_chon);
			TongGT = TongGT + dsdv[i].So_dv_duoc_chon*dsdv[i].GT;
			TongTL = TongTL + dsdv[i].So_dv_duoc_chon*dsdv[i].TL;
	}
	printf("|---|--------------------|---------|---------|--------|---------|---------------|\n");
	printf("\nTrong luong cua balo = %9.2f\n", w);
	printf("\nTrong luong cac vat duoc chon = %9.2f\n", TongTL);
	printf("\nGia tri cua balo = %9.2f\n", TongGT);
}int min(int a, int b){
	return a<b ? a:b;
}


void Tao_Nut_Goc(float w, float* TLConLai, float* CT, float* GiaLNTT, float* TGT , float Don_Gia_Lon_Nhat){
	*TGT = 0 ;
	*TLConLai = w;
	*CT = *TLConLai*Don_Gia_Lon_Nhat;
	*GiaLNTT = 0;
}

void Cap_Nhat_PA_TNTT(float TGT ,float* GiaLNTT, int x[], DoVat* dsdv, int n){
	int i;
	if(*GiaLNTT < TGT){
		*GiaLNTT = TGT ;
		for(i=0; i< n ; i++)
			dsdv[i].So_dv_duoc_chon =x[i];
	}
}
void NhanhCan(int i, float* TGT , float* CT, float* TLConLai,float* GiaLNTT, int x[], DoVat* dsdv, int n ){
	int j;
	int So_Do_Vat_Lon_Nhat_Co_The_Chon = min(dsdv[i].SL , *TLConLai/dsdv[i].TL);
	for(j=So_Do_Vat_Lon_Nhat_Co_The_Chon ; j>=0; j--){
		*TGT = *TGT + j*dsdv[i].GT ; 
		*TLConLai = *TLConLai - j*dsdv[i].TL;
		*CT = *TGT + *TLConLai*dsdv[i+1].DG;
		if(*CT >*GiaLNTT){
			x[i] = j;
			if(i == n-1 || (*TLConLai == 0)){
				Cap_Nhat_PA_TNTT(*TGT, GiaLNTT , x ,dsdv, n);
			}else{
				NhanhCan(i+1, TGT , CT , TLConLai , GiaLNTT , x ,dsdv , n);
			}
		}
		x[i] = 0;
		*TGT = *TGT - j*dsdv[i].GT ; 
		*TLConLai += j*dsdv[i].TL ;
	}
}
int main(){
	DoVat* dsdv ; 
	int n;
	float w;
	
	dsdv = readfile("CaiTui3.txt",  &w , &n  );
	bubble_sort(dsdv , n);
	
	float TLConLai, CT , TGT , GiaLNTT;
	int x[n]; 
	TLConLai = w;
	CT = w*dsdv[0].DG;
	TGT = 0;
	GiaLNTT =0;
	NhanhCan(0 , &TGT , &CT ,&TLConLai , &GiaLNTT , x ,dsdv , n);  
	InDSDV(dsdv, n , w);
	free(dsdv);
}

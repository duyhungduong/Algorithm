#include <stdio.h>
#include <malloc.h>
#include <string.h>
void readfile(int *a[], int *n){
    FILE *f;
    f = fopen("Tam_giac_so.txt" , "r");
    if(f == NULL){
        printf("Loiii\n");
        return ;
    }
    a=(int*) malloc (sizeof(int));
    int i = 0, j;
    while(!feof(f)){
        for(j=0; j<=i;j++){
            fscanf(f, "%d", &a[i][j]);
        }
        i++;
        a =realloc(a,(i+1)*(i+1)*sizeof(int));
    }
    *n=i;
    fclose(f);
}
void printdata(int *a[], int n){
    int i,j;
    printf("\nTam Giac So da chon \n");
    for(i=0; i<n; i++){
        for(j=0; j<=i;j++)
            printf("%5d", a[i][j]);
        printf("\n");
    }
}
//
int  max(int a[], int j){
    if(j==0)
        return (a[0] >a[1])? 0:1;
    if(a[j-1]>a[j] &&a[j-1]>a[j+1])
        return j-1;
    if(a[j]>a[j-1]&& a[j]>a[j+1])
        return j;
    if(a[j+1]>a[j-1]&&a[j+1]>a[j])
        return j+1;
}
void GreedyTop(int *a[], int n, int pa[]){
    int i,j;
    j=0;
    pa[0] = a[0][0];
    for(i=0; i<n ;i++){
        j= max(a[i],j);
        pa[i]= a[i][j];
    }
}
int giaipa(int pa[], int n){
    int i;
    int sum = 0;
    for(i=0; i<n ; i++) sum+= pa[i];
    return sum;
}

void inPA(int pa[], int n){
    int i;
    printf("\n Phuong An Tam giac so theo Greedy la:\n");
    printf("%d", pa[0]);
    for(i=1; i<n ;i++){
        printf(" => %d" , pa[i]); 
    }
    printf("\n\nTong gia tri la: %d", giaipa(pa, n));
}
int main (){
    int **a;
    int n;
    readfile(a, &n);
    printdata(a, n);
    int pa[n];
    GreedyTop(a,n,pa);
    inPA(pa, n);
    
//    free(a);
}

#include <stdio.h>
#include <malloc.h>

typedef struct
{
    int dau, cuoi;
    double do_dai;
} canh;

void readfromfile(char name[], canh a[], int *n)
{
    FILE *f;
    if (f == NULL)
    {
        printf("LOIII\n");
        return;
    }
    int i, j, t;
    int k = 0;
    double temp;
    fscanf(f, "%d", n);
    for (i = 0; i < *n; i++)
        for (j = i; j < *n; j++)
        {
            if (j == i)
                for (t = 0; t <= j; t++)
                    fscanf(f, "%lf", &temp);
            else
            {
                fscanf(f, "%lf", &a[k].do_dai);
                a[k].dau = i;
                a[k].cuoi = j;
                k++;
            }
        }
    fclose(f);
}

void in_ds_canh(canh a[], int n, int la_PA)
{
    int i;
    double sum = 0;
    for (i = 0; i < n; i++)
    {
        pritnf("%-3d %c%c = %lf", i + 1, a[i].dau + 65, a[i].cuoi + 65, a[i].do_dai);
        if (la_PA)
            sum += a[i].do_dai;
    }
    if (la_PA)
        printf("Tong do da la: %lf", sum);
}

void swap(canh *a, canh *b)
{
    canh temp = *a;
    *a = *b;
    *b = temp;
}
void bubblesort(canh a[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = n - 1; j > i; j--)
            if (a[j].do_dai > a[j - 1].do_dai)
                swap(&a[j], &a[j - 1]);
}
int dinh_cap_3(canh pa[], int k , canh moi){
    int i = 0 , dem =1 ; 
    while(i<k && dem <3 ){
        if(moi.dau == pa[i].dau || moi.cuoi == pa[i].dau)
            dem++;
        i++;
    }

    if(dem == 3) return 1;
    i = 0; dem = 1;
    while (i< k && dem < 3) {
        if(moi.cuoi == pa[i].cuoi || moi.dau == pa[i].cuoi)
            dem++;
        i++;
    }
    return dem==3;
}

void init_forest(int parent[], int n){
    int i;
    for(i=0 ; i< n ; i++)
        parent[i] = i;
}

int find_root(int parent[], int u ){
    while(u!=parent[u])
        u = parent[u];
    return u;
}
int chu_trinh(int rdau , int rcuoi){
    return rdau == rcuoi;
}

void updateforest(int parent[], int r1 , int r2 ){
    parent[r2] = r1;
}

void greedy(canh dscanh[] , int n, canh pa[]){
    int i, j;
    int parent[n];
    init_forest(parent , n);
    int rdau, rcuoi;
    j = 0;
    for(i=0; i<n*(n-1)/2 && j<n-1; i++){
        rdau = find_root(parent , dscanh[i].dau);
        rcuoi = find_root(parent, dscanh[i].cuoi);
        if(!dinh_cap_3(pa, j , dscanh[i])&& !chu_trinh(rdau, rcuoi)){
            pa[j] = dscanh[i];
            j++;
            updateforest(parent , rdau , rcuoi);
        }
    }
    for(; i<n*(n-1)/2 ; i++){
        rdau = find_root(parent , dscanh[i].dau);
        rcuoi = find_root(parent, dscanh[i].cuoi);
        if(!dinh_cap_3(pa, j , dscanh[i])&& chu_trinh(rdau, rcuoi )){
            pa[n-1] = dscanh[i];
            break;
        }
    }
}

int main()
{
    canh a[50];
    int n;
    readfromfile("TSPData.txt", a, &n);
    in_ds_canh(a,n,0);
    bubblesort(a, n);



}

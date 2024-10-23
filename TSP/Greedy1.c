#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define size 66
typedef struct
{
    double do_dai;
    int dau, cuoi;
} canh;

void read_file(char file_name[], canh a[], int *n)
{
    FILE *f;
    f = fopen(file_name, "r");
    if (f == NULL)
    {
        printf("LOIIIIIII!!!!!!");
        return;
    }
    // n la so dinh 5 , 6, 12
    fscanf(f, "%d", n);
    int k = 0;
    int i, j, t;
    double giatriboqua;
    for (i = 0; i < *n; i++)
    {
        for (j = i; j < *n; j++)
        {
            if (i == j)
                for (t = 0; t <= j; t++)
                    fscanf(f, "%lf", &giatriboqua);
            else
            {
                fscanf(f, "%lf", &a[k].do_dai);
                a[k].dau = i;
                a[k].cuoi = j;
                k++;
            }
        }
    }
    fclose(f);
}
void in_ds_canh(canh a[], int n, int la_PA)
{
    int i;
    double tong = 0.0;
    for (i = 0; i < n; i++)
    {
        printf("%3d %c%c = %8.2lf\n", i + 1, a[i].dau + 65, a[i].cuoi + 65, a[i].do_dai);
        if (la_PA)
            tong += a[i].do_dai;
    }
    if (la_PA)
        printf("Tong = %8.2lf\n", tong);
}
void swap(canh *x, canh *y)
{
    canh temp = *x;
    *x = *y;
    *y = temp;
}

void bubblesort(canh a[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = n - 1; j > i; j--)
            if (a[j].do_dai < a[i].do_dai)
                swap(&a[j], &a[i]);
}

// Xac dinh dinh cap 3
int dinhcap3(canh pa[], int k, canh moi)
{
    int i = 0, dem = 1;
    while (i < k && dem < 3)
    {
        if (moi.dau == pa[i].dau || moi.dau == pa[i].cuoi)
        {
            dem++;
        }
        i++;
    }
    if (dem == 3)
        return 1;
    i = 0;
    dem = 1;
    while (i < k && dem < 3)
    {
        if (moi.cuoi == pa[i].dau || moi.cuoi == pa[i].cuoi)
            dem++;
        i++;
    }
    return dem == 3;
}
void init_forest(int parent[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        parent[i] = i;
}
int find_root(int parent[], int u)
{
    while (u != parent[u])
        u = parent[u];
    return u;
}
int chu_trinh(int rdau, int rcuoi)
{
    return rdau == rcuoi;
}
void updateforest(int parent[], int r1, int r2)
{
    parent[r2] = r1;
}
void greedy(canh dscanh[], int n, canh pa[])
{
    int i, j;
    int parent[n];
    init_forest(parent, n);
    int rdau, rcuoi;
    j = 0;
    // Chon cac canh nho nhat ko tao thanh dinh cap 3 va ko tao chu trinh de dua vao phuong an PA
    for (i = 0; i < n * (n - 1) / 2 && j < n - 1; i++)
    {
        rdau = find_root(parent, dscanh[i].dau);
        rcuoi = find_root(parent, dscanh[i].cuoi);
        if (!dinhcap3(pa, j, dscanh[i]) && !chu_trinh(rdau, rcuoi))
        {
            // Do ko tao dinh cap 3 va chu trinh nen dua canh vao phuong an
            pa[j] = dscanh[i];
            j++;
            updateforest(parent, rdau, rcuoi);
        }
        // Luc nay cay phuong an da co n-1 canh
        // Tim mot canh trong so cac canh chua xet dua vao PA neu no ko tao thanh
    }
    // Ko can khoi tao gia tri ban dau cho i
    for (; i < n * (n - 1) / 2; i++)
    {
        rdau = find_root(parent, dscanh[i].dau);
        rcuoi = find_root(parent, dscanh[i].cuoi);
        if (!dinhcap3(pa, j, dscanh[i]) && chu_trinh(rdau, rcuoi))
        {
            pa[n - 1] = dscanh[i];
            break;
        }
    }
}

int main()
{
    canh ds_canh[size];
    int n;
    read_file("TSPData.txt", ds_canh, &n);
    printf("Danh sach cua do thi \n");

    bubblesort(ds_canh, n * (n - 1) / 2);
    printf("Danh sach cac canh cua do thi sa Sap Xep \n");

    canh PA[n];
    greedy(ds_canh, n, PA);
    printf("Phuong an GREEDY (Tham an)\n");
    in_ds_canh(PA, n, 1);

    return 0;
}

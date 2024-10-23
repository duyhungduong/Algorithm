#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define size 100
typedef struct
{
    /* data */
    int dau, cuoi;
    int da_dung;
    float do_dai;
} canh;

void readfile(char name[], canh a[][100], int *n)
{
    FILE *f;
    f = fopen(name, "r");
    if (f == NULL)
    {
        printf("Loii\n");
        return;
    }
    int i, j, t;

    fscanf(f, "%d", n);
    for (i = 0; i < *n; i++)
        for (j = 0; j < *n; j++)
        {
            fscanf(f, "%f", &a[i][j].do_dai);
            a[i][j].dau = i;
            a[i][j].cuoi = j;
            a[i][j].da_dung = 0;
        }

    fclose(f);
}

void in_ma_tran(canh a[][size], int n)
{
    int i, j;
    printf("Ma tran trong so cua Do Thi \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf(" %c%c=%8.2f", a[i][j].dau + 65, a[i][j].cuoi + 65, a[i][j].do_dai);
        printf("\n");
    }
}
int co_chu_trinh(canh x[], int k, int ke_tiep)
{
    int i = 0, co_CT = 0;
    while (i < k && !co_CT)
    {
        if (ke_tiep == x[i].dau)
            co_CT = 1;
        else
            i++;
    }
    return co_CT;
}

float canh_NN(canh a[][size], int n)
{
    float Cmin = 3.40282e+38; // Gan cho 1 so thuc lon nhat de so sanh
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i != j && !a[i][j].da_dung && a[i][j].do_dai < Cmin)
                Cmin = a[i][j].do_dai;
        }
    }
    return Cmin;
}
float can_duoi(canh a[][size], float TGT, int n, int i)
{ // n = so thanh so, i la bac cua can duoi trong cay
    return TGT + (n - i) * canh_NN(a, n);
}

void Cap_Nhat_PA_TNTT(canh a[][100], int n, float TGT, float *GNNTT, canh x[], canh PA[])
{
    int i;
    x[n - 1] = a[x[n - 2].cuoi][x[0].dau];
    TGT += x[n - 1].do_dai;
    if (*GNNTT > TGT)
    {
        *GNNTT = TGT;
        for (i = 0; i < n; i++)
            PA[i] = x[i];
    }
}
void Nhanh_Can(canh a[][100], int n, int i, int dau, float *TGT, float *CD, float *GNNTT, canh x[], canh PA[])
{
    int j;
    for (j = 0; j < n; j++)
        if (dau != j && !a[dau][j].da_dung && !co_chu_trinh(x, i, j))
        {
            *TGT += a[dau][j].do_dai;
            *CD = can_duoi(a, *TGT, n, i + 1);
            if (*CD < *GNNTT){
                x[i] = a[dau][j];
                a[dau][j].da_dung = 1;
                a[j][dau].da_dung = 1;

                if (i == n - 2)
                    Cap_Nhat_PA_TNTT(a, n, *TGT, GNNTT, x, PA);
                else
                    Nhanh_Can(a, n, i + 1, j, TGT, CD, GNNTT, x, PA);
            }
            *TGT -= a[dau][j].do_dai;
            a[dau][j].da_dung = 0;
            a[j][dau].da_dung = 0;
        }
}

void in_PA(canh PA[], int n)
{
    int i;
    float sum = 0.0;
    printf("\n Phuong an tim dc:\n");
    for (i = 0; i < n; i++)
    {
        sum += PA[i].do_dai;
        printf("Canh %c%c= %8.2f \n", PA[i].dau + 65, PA[i].cuoi + 65, PA[i].do_dai);
    }
    printf("Tong do dai cac canh cua chu trinh = %8.2f", sum);
}
//
int main()
{
    canh a[100][100];
    int n;
    readfile("TSP1.txt", a, &n);
    in_ma_tran(a, n);

    float TGT = 0, CD = 1000000, GNNTT = 0;
    canh x[n], PA[n];
    char tpxp = 'A';

    fflush(stdin);
    printf("\n Xuat phat tu thanh pho nao? Mot trong cac thanh pho tu A den %c ", n - 1 + 65);
    //    scanf("%c" , &tpxp);
    if (tpxp >= 97)
        tpxp -= 32; // Doi chu thuong thanh chu hoa
    Nhanh_Can(a, n, 0, tpxp - 65, &TGT, &CD, &GNNTT, x, PA);
    in_PA(PA, n);
}

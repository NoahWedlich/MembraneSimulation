#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 50001
#define M 21
#define SWAP(a,b) {double temp=(a);(a)=(b);(b)=temp;}


int length[4], neigh[N][7], dim, nr_lattice;
double  pos[N][3];
int t_total, t_plot;
int lengthall;
double quotf, jc, aver;
double step_max;
double period(double);

void make_neighbors(int);
void transfer1(int, int*);
int transfer2(int*);
void make_mc();
double  calc_interaction(int);
void  make_initialization();

int main_old()
{
    int i, t;
    double sum;

    dim = 2;
    lengthall = 8;
    t_total = 10000;
    t_plot = 2000;
    srand(123);
    quotf = pow(2.0, -31.0);
    make_neighbors(lengthall);
    make_initialization();
    jc = 100;
    step_max = 0.1;
    for (t = 1; t <= t_total; t++)
    {
        for (i = 0; i <= nr_lattice; i++) make_mc();
        if (t % t_plot == 0 && t > t_total / 2)
        {
            sum = 0;
            for (i = 0; i < nr_lattice; i++)
            {
                sum += pos[i][3] / nr_lattice;
            }
            printf("%lf\n", sum);
        }
    }
}

double period(double dx)
{
    if (dx > lengthall / 2) dx -= lengthall;
    else
        if (dx < -lengthall / 2) dx += lengthall;
    return (dx);
}


void make_mc()
{
    int i, j;
    double deltaener;
    double interaction_old, interaction_new, dstep[4];

    i = rand() % nr_lattice;
    interaction_old = calc_interaction(i);
    for (j = 1; j <= 3; j++)
        dstep[j] = (2 * (quotf * rand()) - 1) * step_max;
    if (i == 0)
        for (j = 1; j <= 3; j++)
            dstep[j] = 0;
    if (i == lengthall / 2)
        dstep[3] = 0;
    if (i == lengthall / 2 + lengthall * lengthall / 2)
        dstep[3] = 0;
    for (j = 1; j <= 3; j++)
        pos[i][j] += dstep[j];
    interaction_new = calc_interaction(i);
    deltaener = interaction_new - interaction_old;
    if (rand() * quotf > exp(-deltaener)) for (j = 1; j <= 3; j++) pos[i][j] -= dstep[j];
}

void transfer1(int m, int* vec)
{
    int mm, j;
    mm = nr_lattice / length[1];
    for (j = 1; j <= dim; j++)
    {
        vec[j] = m / mm;
        m -= (mm * vec[j]);
        if (j < dim)
            mm /= length[j + 1];
    }
}



int transfer2(int* vec)
{
    int j;
    int m = 0;
    int mm = 1;
    for (j = 1; j <= dim; j++)
    {
        m += vec[dim + 1 - j] * mm;
        mm *= length[dim + 1 - j];
    }
    return(m);
}



void make_neighbors(int lengthall)
{
    int i, j, k, l, vec[4], m, keep;

    nr_lattice = 1;
    for (i = 1; i <= dim; i++)
    {
        length[i] = lengthall;
        nr_lattice *= length[i];
    }

    for (i = 0; i < nr_lattice; i++)
    {
        transfer1(i, vec);
        l = 0;
        for (j = 1; j <= dim; j++)

            for (k = -1; k <= 1; k += 2)
            {
                keep = vec[j];
                vec[j] += k;
                if (vec[j] >= length[j])
                {
                    vec[j] -= length[j];
                }
                else
                {
                    if (vec[j] < 0)
                    {
                        vec[j] += length[j];
                    }
                }

                m = transfer2(vec);
                neigh[i][l] = m;
                vec[j] = keep;
                l++;
            }
    }
}

double  calc_interaction(int i)
{
    int j, k;
    double r2, x;
    double interaction = 0;
    for (j = 0; j < 2 * dim; j++)
    {
        r2 = 0; for (k = 1; k <= 3; k++) { x = period(pos[i][k] - pos[neigh[i][j]][k]);  r2 += x * x; }
        if (r2 > 1) interaction += jc * (r2 - 1) * (r2 - 1);
        else        interaction += 5 * jc * (r2 - 1) * (r2 - 1);
    }
    return(interaction);
}

void  make_initialization()
{
    int i;
    int vec[4];
    for (i = 0; i < nr_lattice; i++)
    {
        transfer1(i, vec);
        pos[i][1] = vec[1];
        pos[i][2] = vec[2];
    }
}
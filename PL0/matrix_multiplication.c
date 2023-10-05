#include <stdio.h>
#include <stdlib.h>

int **multiplex(int **m1, int **m2,int rows1, int cols1, int rows2, int cols2)
{
    if (cols1 != rows2)
    {
        return NULL;
    }

    int **result = (int **)malloc(rows1 * sizeof(int *));
    for (int i = 0; i < rows1; i++)
    {
        result[i] = (int *)malloc(cols2 * sizeof(int));
    }

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++)
            {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return result;
}

int main()
{   
    int rows1 = 512;
    int cols1 = 512;
    int rows2 = 512;
    int cols2 = 512;

    int **m1 = (int **)malloc(rows1 * sizeof(int *));
    for (int i = 0; i < rows1; i++)
    {
        m1[i] = (int *)malloc(cols1 * sizeof(int));
        for (int j = 0; j < cols1; j++)
        {
            m1[i][j] = i + j;
        }
    }

    int **m2 = (int **)malloc(rows2 * sizeof(int *));
    for (int i = 0; i < rows2; i++)
    {
        m2[i] = (int *)malloc(cols2 * sizeof(int));
        for (int j = 0; j < cols2; j++)
        {
            m2[i][j] = i + j;
        }
    }

    int **resultado = multiplex(m1, m2, rows1, cols1, rows2, cols2);

    if (resultado != NULL)
    {

        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < cols2; j++)
            {
                printf("%d\t", resultado[i][j]);
            }
            printf("\n");
        }

    }
    else
    {
        printf("As dimensões não são compatíveis para multiplicação.\n");
    }

    return 0;
}
#include <iostream>
#include <ctime>

int main()
{
    int N = 7;
    int M = 10;

    int** matrix = new int* [N];
    for (int i = 0; i < N; i++)
        matrix[i] = new int[M];

    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrix[i][j] = 1 + rand() % 101;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            std::cout.width(5);
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            if (matrix[j][0] < matrix[i][0])
            {
                int* tmp = matrix[j];
                matrix[j] = matrix[i];
                matrix[i] = tmp;
            }
        }
    }

    std::cout << std::endl << std::endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            std::cout.width(5);
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < N; i++)
        delete[] matrix[i];
    delete[] matrix;
}

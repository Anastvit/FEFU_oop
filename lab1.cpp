#include <iostream>
#include <cmath>
#include <limits>

double func(double x, int n)
{
    double y = 0;

    for (int k = 1; k <= n; k++)
    {
        y += (pow(x, (2 * k - 2)) / (2 * k - 1));
    }
    y += 0.5 * x;

    return y;
}

int main()
{
    double x;
    int n;

    std::cout << "x=";
    std::cin >> x;
    if (std::cin.fail())
    {
        std::cout << "Invalid input." << std::endl << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }

    std::cout << "n=";
    std::cin >> n;
    if (std::cin.fail())
    {
        std::cout << "Invalid input." << std::endl << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }

    std::cout << "function value=" << func(x, n) << std::endl;

    return 0;
}

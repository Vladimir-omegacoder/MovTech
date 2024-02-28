#include <iostream>
#include <Windows.h>
#include <random>





template <typename T>
void print_vector(const T* vector, size_t size)
{

    std::cout << "Vector:\n";
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << vector[i] << ' ';
    }
    std::cout << '\n';

}

template <typename T>
void print_matrix(const T* matrix, size_t size)
{

    std::cout << "Matrix:\n";
    for (size_t i = 0; i < size; ++i)
    {
        for (size_t j = 0; j < size; ++j)
        {
            std::cout << matrix[i * size + j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

}



size_t get_available_memory()
{

    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    std::cout << "Total physical memory: " << status.ullTotalPhys << " bytes\n";
    std::cout << "Available physical memory: " << status.ullAvailPhys << " bytes\n";

    return status.ullAvailPhys;

}



template <typename T>
time_t test(size_t N ,const T& min, const T& max, bool show_input = false, bool show_output = false)
{

    T* vector = new T[N];
    T* matrix = new T[N * N];
    T* result = new T[N] {};

    std::random_device rd;
    std::uniform_int_distribution<T> dist(min, max);


    for (size_t i = 0; i < N; ++i)
    {
        vector[i] = dist(rd);
    }
    for (size_t i = 0; i < N * N; ++i)
    {
        matrix[i] = dist(rd);
    }

    if (show_input)
    {
        std::cout << "Vector:\n";
        print_vector(vector, N);
        std::cout << '\n';

        std::cout << "Matrix:\n";
        print_matrix(matrix, N * N);
        std::cout << '\n';
    }
    

    result[0] += matrix[0] * vector[0];
    for (size_t i = 1; i < N * N; ++i)
    {
        result[i % N] += matrix[i] * vector[i / N];
    }

    delete[] vector;
    delete[] matrix;

    if (show_output)
    {
        std::cout << "Result:\n";
        print_vector(result, N);
        std::cout << '\n';
    }

    delete[] result;

    return 0;

}



int main()
{

    typedef int chosen_type;

    size_t N = (-1 + sqrt(-2 + 4 * get_available_memory() / sizeof(chosen_type)) / 2);

    std::cout << "N: " << N << '\n';

    test<chosen_type>(N, 0, 10, true, true);

    return 0;

}
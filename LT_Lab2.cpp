#include <iostream>
#include <Windows.h>
#include <random>
#include <chrono>
#include <fstream>





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



size_t get_available_memory(std::ofstream& fout)
{

    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);

    return status.ullAvailPhys;

}



template <typename T>
double test(size_t N ,const T& min, const T& max, bool show_input = false, bool show_output = false)
{

    T* vector = new T[N];
    T* matrix = new T[N * N];
    T* result = new T[N] {};

    std::random_device rd;
    std::uniform_real_distribution<double> dist(min, max);

    /*for (size_t i = 0; i < N; ++i)
    {
        vector[i] = dist(rd);
    }
    for (size_t i = 0; i < N * N; ++i)
    {
        matrix[i] = dist(rd);
    }*/

    if (show_input)
    {
        std::cout << "Vector:\n";
        print_vector(vector, N);
        std::cout << '\n';

        std::cout << "Matrix:\n";
        print_matrix(matrix, N * N);
        std::cout << '\n';
    }
    


    auto start = std::chrono::high_resolution_clock::now();
    result[0] += matrix[0] * vector[0];
    for (size_t i = 1; i < N * N; ++i)
    {
        result[i % N] += matrix[i] * vector[i / N];
    }
    auto end = std::chrono::high_resolution_clock::now();



    delete[] vector;
    delete[] matrix;

    if (show_output)
    {
        std::cout << "Result:\n";
        print_vector(result, N);
        std::cout << '\n';
    }

    delete[] result;



    auto elapsed_time = end - start;

    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();

}

template <typename T>
double vector_by_matrix(T* vector, T* matrix, T* result, size_t N)
{

    auto start = std::chrono::high_resolution_clock::now();
    result[0] += matrix[0] * vector[0];
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            result[i] += vector[i] * matrix[i + j * N];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_time = end - start;

    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();

}

template <typename T>
double matrix_by_vector(T* vector, T* matrix, T* result, size_t N)
{

    auto start = std::chrono::high_resolution_clock::now();
    result[0] += matrix[0] * vector[0];
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            result[i] += vector[i] * matrix[i + j * N];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_time = end - start;

    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();

}



int main()
{

    std::ofstream fout;
    fout.open("info.csv");
    if (!fout.is_open())
    {
        std::cerr << "File error.\n";
        return -1;
    }



    typedef double chosen_type;



    chosen_type min, max;
    std::cout << "Enter min and max values for elements: ";
    std::cin >> min >> max;
    fout << "Lower bound: " << min << " ;" << "Upper bound: " << max << '\n';

    fout << "\n====== TESTS ======\n";
    fout << "N;time(ms);Max N;\n";
    for (size_t N = 1000, max_N = 1001; N <= max_N; N += 1000)
    {
        max_N = (-1 + sqrt(-2 + 4 * get_available_memory(fout) / sizeof(chosen_type)) / 2);
        double time = test<chosen_type>(N, min, max, 0, 0);
        fout << N << ';' << time << ';' << max_N << ";\n";
    }



    return 0;

}
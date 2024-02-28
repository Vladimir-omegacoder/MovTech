#include <iostream>
#include <Windows.h>
#include <random>
#include <chrono>
#include <fstream>





template <typename T>
void print_vector(const T* vector, size_t size)
{

    for (size_t i = 0; i < size; ++i)
    {
        std::cout << vector[i] << ' ';
    }
    std::cout << '\n';

}

template <typename T>
void print_matrix(const T* matrix, size_t size)
{

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
double vector_by_matrix_advanced(T* vector, T* matrix, T* result, size_t N)
{

    for (size_t i = 0; i < N; ++i)
    {
        result[i] = T();
    }

    auto start = std::chrono::high_resolution_clock::now();
    result[0] += matrix[0] * vector[0];
    for (size_t i = 1; i < N * N; ++i)
    {
        result[i % N] += matrix[i] * vector[i / N];
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_time = end - start;

    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();

}

template <typename T>
double vector_by_matrix(T* vector, T* matrix, T* result, size_t N)
{

    for (size_t i = 0; i < N; ++i)
    {
        result[i] = T();
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            result[i] += vector[j] * matrix[i + j * N];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_time = end - start;

    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count();

}

template <typename T>
double matrix_by_vector(T* vector, T* matrix, T* result, size_t N)
{

    for (size_t i = 0; i < N; ++i)
    {
        result[i] = T();
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            result[i] += matrix[i * N + j] * vector[j];
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



    typedef int chosen_type;



    chosen_type min, max;
    std::cout << "Enter min and max values for elements: ";
    std::cin >> min >> max;
    fout << "Lower bound: " << min << " ;" << "Upper bound: " << max << '\n';


    const size_t N = 3;
    chosen_type* vector = new chosen_type[N];
    chosen_type* matrix = new chosen_type[N * N];
    chosen_type* result = new chosen_type[N]{};

    std::random_device rd;
    std::uniform_real_distribution<double> dist(min, max);

    for (size_t i = 0; i < N; ++i)
    {
        vector[i] = dist(rd);
    }
    for (size_t i = 0; i < N * N; ++i)
    {
        matrix[i] = dist(rd);
    }



    /*std::cout << "Vector:\n";
    print_vector(vector, N);
    std::cout << '\n';

    std::cout << "Matrix:\n";
    print_matrix(matrix, N);
    std::cout << '\n';

    vector_by_matrix(vector, matrix, result, N);
    std::cout << "vector_by_matrix:\n";
    print_vector(result, N);
    std::cout << '\n';

    matrix_by_vector(vector, matrix, result, N);
    std::cout << "matrix_by_vector:\n";
    print_vector(result, N);
    std::cout << '\n';

    vector_by_matrix_advanced(vector, matrix, result, N);
    std::cout << "vector_by_matrix_advanced:\n";
    print_vector(result, N);
    std::cout << '\n';*/


    fout << "\n====== TESTS ======\n";
    fout << "N;time(ms);Max N;\n";
    for (size_t N = 1000, max_N = 1000; N <= max_N; N += 1000)
    {
        max_N = (-1 + sqrt(-2 + 4 * get_available_memory(fout) / sizeof(chosen_type)) / 2);
        double time = vector_by_matrix_advanced<chosen_type>(N, min, max, 0, 0);
        fout << N << ';' << time << ';' << max_N << ";\n";
    }



    delete[] vector;
    delete[] matrix;
    delete[] result;

    return 0;

}
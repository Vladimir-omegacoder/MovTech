#include <iostream>
#include <Windows.h>




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
time_t test()
{

    size_t N = (-1 + sqrt(-2 + 4 * get_available_memory() / sizeof(T)) / 2);

    std::cout << "Max N: " << N << '\n';

    T* vector = new T[N];
    T* matrix = new T[N * N];



    delete[] vector;
    delete[] matrix;

    return 0;

}



int main()
{

    test<int>();

    return 0;

}
#include "ex1.h"

void v_add_naive(double* x, double* y, double* z) {
    #pragma omp parallel
    {
        for(int i=0; i<ARRAY_SIZE; i++)
            z[i] = x[i] + y[i];
    }
}

// Adjacent Method
void v_add_optimized_adjacent(double* x, double* y, double* z) {
    // TODO: Implement this function
    // Do NOT use the `for` directive here!
    #pragma omp parallel
    {
        int threads = omp_get_num_threads();
        int cur_thread = omp_get_thread_num();

        for (int i = cur_thread; i < ARRAY_SIZE; i += threads)
            z[i] = x[i] + y[i];
    }
}

// Chunks Method
// void v_add_optimized_chunks(double* x, double* y, double* z) {
//     // TODO: Implement this function
//     // Do NOT use the `for` directive here!
//     int threads = 0;
//     #pragma omp parallel
//     {
//         threads = omp_get_num_threads();
//         int cur_thread = omp_get_thread_num();
//         int i = threads * cur_thread;
//         int bound = threads * (cur_thread + 1);

//         for (int j = i; j < bound; j++)
//             z[j] = x[j] + y[j];
//     }
//     for (int i = threads * (threads - 1); i < ARRAY_SIZE; i++)
//         z[i] = x[i] + y[i];
// }

void v_add_optimized_chunks(double* x, double* y, double* z) {
    // TODO: Implement this function
    // Do NOT use the `for` directive here!
    int threads = 0;
    int bound = 0;
    #pragma omp parallel
    {
        threads = omp_get_num_threads();
        int cur_thread = omp_get_thread_num();
        bound = ARRAY_SIZE / threads;

        for (int j = bound * cur_thread; j < bound * (cur_thread + 1); j++)
            z[j] = x[j] + y[j];
    }
    for (int i = bound * threads; i < ARRAY_SIZE; i++)
        z[i] = x[i] + y[i];
}

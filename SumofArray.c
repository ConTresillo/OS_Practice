#include <pthread.h>
#include <stdio.h>

int arr[1000];
int sum1 = 0, sum2 = 0;

typedef struct {
    int start;
    int end;
    int* sum;
} ThreadArgs;

void* sum_part(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    *(args->sum) = 0;
    for (int i = args->start; i < args->end; i++) {
        *(args->sum) += arr[i];
    }
    pthread_exit(NULL);
}

int main() {
    // (You should fill arr[] with actual data here.)
    for(int i=0; i<1000; i++){
        arr[i] = i;
    }

    pthread_t t1, t2;
    ThreadArgs args1 = {0, 500, &sum1};
    ThreadArgs args2 = {500, 1000, &sum2};

    pthread_create(&t1, NULL, sum_part, &args1);
    pthread_create(&t2, NULL, sum_part, &args2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Total Sum = %d\n", sum1 + sum2);
    return 0;
}

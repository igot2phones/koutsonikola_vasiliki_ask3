// to mono pou den oloklirothike einai h to " κάθε thread να επεξεργάζεται διαφορετικό κομμάτι ενός πίνακα C (ΝxN)"
// ola ta ypoloipa exoun oloklirothei
#include <stdio.h>
#include <stdlib.h> //gia to malloc
#include <sys/time.h>
#include <pthread.h>

#define size 3

int ***ar; // o triplos pointer/pinakas pou tha ftiaxnei 3 2d pinakes dynamika

void memory_allocation();
void fill_ar();
void print_ar();
void *differece();

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    int T = atoi(argv[2]);
    if ( N < 0 || N > 15 || T < 0 || N % T != 0){ // elegxos gia ta oria
        printf("Error: incorrect arguments\n");
        return 0;
    }
    pthread_t threads[T];
    memory_allocation(N);
    fill_ar(N);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    for (int i = 0; i < T; i++) {
        pthread_create(&threads[i], NULL, differece, (void *)&N);
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end, NULL);
    print_ar(N);
    printf("\n\nTime: %ld microseconds\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
    printf("Number of threads: %d\n", T);
    free(ar); //apodesmeush mnhmhs
    return 0;
}

// o xristos kai h panagia na mas voithisoun me ta pointers

void memory_allocation(int N) {
    ar = (int ***)malloc(size * sizeof(int **)); 
    for (int i = 0; i < size; i++) {
        ar[i] = (int **)malloc(N * sizeof(int *)); 
        for (int j = 0; j < N; j++) {
            ar[i][j] = (int *)malloc(N * sizeof(int)); //desmeush mnhmhs gia tous pinakes ar[i][j]
        }
    }
    return;
}

void fill_ar(int N) {
    srand(time(NULL));
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                ar[0][j][k] = rand() % 11;
            }
        }
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                ar[1][j][k] = rand() % 11;
            }
        }
    return;
    }

void print_ar(int N) {
    for (int i = 0; i < size; i++){
        printf("\nPinakas %d:\n",i+1);
        for (int ii = 0; ii < N; ii++){
            printf("\n"); // gia na einai pio wraio to output
            for (int iii = 0; iii < N; iii++){
                printf("%d ",ar[i][ii][iii]);
            }
        }
    }
    
}

void *differece(void *arg){
    int N = *((int *)arg); // metatroph se int
    for (int i = 0; i < N; i++) {
        for (int ii = 0; ii < N; ii++) {
            ar[2][i][ii] = ar[0][i][ii] - ar[1][i][ii];
        }
    }
}
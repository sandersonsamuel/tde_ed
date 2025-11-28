#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ----------------------
// BUBBLE SORT
// ----------------------
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    int trocou;

    for (i = 0; i < n - 1; i++) {
        trocou = 0;
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                trocou = 1;
            }
        }
        if (!trocou) break; // já ordenado
    }
}

// ----------------------
// INSERTION SORT
// ----------------------
void insertionSort(int arr[], int n) {
    int i, chave, j;

    for (i = 1; i < n; i++) {
        chave = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

// ----------------------
// QUICKSORT
// ----------------------
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int temp;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ----------------------
// FUNÇÃO PARA GERAR VETOR
// ----------------------
void gerarVetor(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100000; // valores aleatórios
}

// ----------------------
// FUNÇÃO PARA COPIAR VETOR
// ----------------------
void copiarVetor(int origem[], int destino[], int n) {
    for (int i = 0; i < n; i++)
        destino[i] = origem[i];
}

// ----------------------
// FUNÇÃO DE TESTE DE TEMPO
// ----------------------
double testarTempo(void (*sortFunc)(int[], int), int arr[], int n) {
    clock_t inicio = clock();
    sortFunc(arr, n);
    clock_t fim = clock();

    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// ----------------------
// MAIN
// ----------------------
int main() {
    srand(time(NULL));

    int tamanhos[] = {1000, 5000, 20000};
    int qtdTestes = 3;

    printf("\n===== TESTE DE ALGORITMOS DE ORDENACAO =====\n");

    for (int t = 0; t < qtdTestes; t++) {
        int n = tamanhos[t];
        int *original = malloc(n * sizeof(int));
        int *v1 = malloc(n * sizeof(int));
        int *v2 = malloc(n * sizeof(int));
        int *v3 = malloc(n * sizeof(int));

        gerarVetor(original, n);
        copiarVetor(original, v1, n);
        copiarVetor(original, v2, n);
        copiarVetor(original, v3, n);

        printf("\n--- Testando com %d elementos ---\n", n);

        // Bubble Sort
        double tempoBubble = testarTempo(bubbleSort, v1, n);
        printf("Bubble Sort:    %.5f segundos\n", tempoBubble);

        // Insertion Sort
        double tempoInsertion = testarTempo(insertionSort, v2, n);
        printf("Insertion Sort: %.5f segundos\n", tempoInsertion);

        // QuickSort
        clock_t inicio = clock();
        quickSort(v3, 0, n - 1);
        clock_t fim = clock();
        double tempoQuick = (double)(fim - inicio) / CLOCKS_PER_SEC;

        printf("QuickSort:      %.5f segundos\n", tempoQuick);

        free(original);
        free(v1);
        free(v2);
        free(v3);
    }

    printf("\n===== FIM DOS TESTES =====\n");
    return 0;
}

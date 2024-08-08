#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256

// Узел дерева Хаффмана
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// Структура минимальной кучи (очереди)
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// Создание нового узла дерева Хаффмана
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Создание минимальной кучи (очереди)
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Обмен двух узлов
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Просеивание вниз для поддержания структуры минимальной кучи
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Вытягивание минимального узла из кучи
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Вставка узла в кучу
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Создание минимальной кучи и добавление узлов
struct MinHeap* buildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

// Построение дерева Хаффмана
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = buildMinHeap(data, freq, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// Печать кодов Хаффмана (рекурсивная функция)
void printCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// Создание кодов Хаффмана и запись их в массив codes
void storeCodes(struct MinHeapNode* root, int arr[], int top, char* codes[], int* freq) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, codes, freq);
    }
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, codes, freq);
    }
    if (!(root->left) && !(root->right)) {
        codes[(unsigned char)root->data] = (char*)malloc(top + 1);
        for (int i = 0; i < top; ++i)
            codes[(unsigned char)root->data][i] = arr[i] + '0';
        codes[(unsigned char)root->data][top] = '\0';
        freq[(unsigned char)root->data] = root->freq;
    }
}

// Сжатие файла
void compressFile(const char* inputFileName, const char* archiveFileName) {
    FILE* inFile = fopen(inputFileName, "rb");
    if (!inFile) {
        printf("Не удалось открыть файл для чтения\n");
        return;
    }

    int freq[256] = {0};
    char ch;
    while (fread(&ch, sizeof(char), 1, inFile))
        freq[(unsigned char)ch]++;

    fseek(inFile, 0, SEEK_SET);

    char data[256];
    int freqNonZero[256];
    int size = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            data[size] = (char)i;
            freqNonZero[size] = freq[i];
            size++;
        }
    }

    struct MinHeapNode* root = buildHuffmanTree(data, freqNonZero, size);

    char* codes[256] = {0};
    int arr[MAX_TREE_HT];
    storeCodes(root, arr, 0, codes, freq);

    FILE* outFile = fopen(archiveFileName, "wb");
    if (!outFile) {
        printf("Не удалось открыть файл для записи\n");
        return;
    }

    fwrite(freq, sizeof(freq), 1, outFile);

    unsigned char byte = 0;
    int bitCount = 0;
    while (fread(&ch, sizeof(char), 1, inFile)) {
        char* code = codes[(unsigned char)ch];
        while (*code) {
            byte = byte << 1 | (*code++ - '0');
            bitCount++;
            if (bitCount == 8) {
                fwrite(&byte, sizeof(byte), 1, outFile);
                bitCount = 0;
            }
        }
    }

    if (bitCount > 0) {
        byte <<= (8 - bitCount);
        fwrite(&byte, sizeof(byte), 1, outFile);
    }

    fclose(inFile);
    fclose(outFile);

    for (int i = 0; i < 256; ++i) {
        if (codes[i]) {
            free(codes[i]);
        }
    }
}

// Распаковка файла
void decompressFile(const char* archiveFileName, const char* outputFileName) {
    FILE* inFile = fopen(archiveFileName, "rb");
    if (!inFile) {
        printf("Не удалось открыть файл для чтения\n");
        return;
    }

    int freq[256] = {0};
    fread(freq, sizeof(freq), 1, inFile);

    char data[256];
    int freqNonZero[256];
    int size = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            data[size] = (char)i;
            freqNonZero[size] = freq[i];
            size++;
        }
    }

    struct MinHeapNode* root = buildHuffmanTree(data, freqNonZero, size);

    FILE* outFile = fopen(outputFileName, "wb");
    if (!outFile) {
        printf("Не удалось открыть файл для записи\n");
        return;
    }

    struct MinHeapNode* current = root;
    unsigned char byte;
    while (fread(&byte, sizeof(byte), 1, inFile)) {
        for (int i = 0; i < 8; ++i) {
            if (byte & 0x80)
                current = current->right;
            else
                current = current->left;

            byte <<= 1;

            if (!current->left && !current->right) {
                fwrite(&current->data, sizeof(current->data), 1, outFile);
                current = root;
            }
        }
    }

    fclose(inFile);
    fclose(outFile);
}

// Главная функция
int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Использование: %s <input_file> <-c|-x> <output_file>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[2], "-c") == 0) {
        compressFile(argv[1], argv[3]);
    } else if (strcmp(argv[2], "-x") == 0) {
        decompressFile(argv[1], argv[3]);
    } else {
        printf("Неизвестная команда: %s\n", argv[2]);
        return 1;
    }

    return 0;
}

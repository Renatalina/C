#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TREE_HT 256

struct MinHeapNode {
    unsigned char item;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(unsigned char item, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    if (!temp) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    if (!minHeap) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    if (!minHeap->array) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

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

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(unsigned char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(unsigned char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;

    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void getCodes(struct MinHeapNode* root, int arr[], int top, char codes[256][MAX_TREE_HT]) {
    if (root->left) {
        arr[top] = 0;
        getCodes(root->left, arr, top + 1, codes);
    }
    if (root->right) {
        arr[top] = 1;
        getCodes(root->right, arr, top + 1, codes);
    }
    if (isLeaf(root)) {
        for (int i = 0; i < top; i++) {
            codes[root->item][i] = arr[i] + '0';
        }
        codes[root->item][top] = '\0';
    }
}

void writeEncodedFile(char* input_file, char* output_file, char codes[256][MAX_TREE_HT]) {
    FILE* file = fopen(input_file, "r");
    if (!file) {
        fprintf(stderr, "Cannot open input file: %s\n", input_file);
        return;
    }
    FILE* out_file = fopen(output_file, "a"); // Изменено на режим "a" для добавления данных 
    if (!out_file) {
        fprintf(stderr, "Cannot open output file: %s\n", output_file);
        fclose(file);
        return;
    }

    unsigned char ch;
    while (fscanf(file, "%c", &ch) != EOF) {
        fprintf(out_file, "%s", codes[ch]);
    }

    fclose(file);
    fclose(out_file);
}


void decodeFile(struct MinHeapNode* root, char* encoded_file, char* decoded_file, long start_pos) {
    FILE* in_file = fopen(encoded_file, "rb");
    if (!in_file) {
        fprintf(stderr, "Cannot open encoded file: %s\n", encoded_file);
        return;
    }
    fseek(in_file, start_pos, SEEK_SET);  // Move the pointer to the start of encoded data
    FILE* out_file = fopen(decoded_file, "wb");
    if (!out_file) {
        fprintf(stderr, "Cannot open output file: %s\n", decoded_file);
        fclose(in_file);
        return;
    }

    struct MinHeapNode* current = root;
    int bit;
    unsigned char byte;
    while (fread(&byte, 1, 1, in_file) == 1) {
        for (int i = 7; i >= 0; i--) {
            bit = (byte >> i) & 1;
            current = (bit == 0) ? current->left : current->right;
            printf("%c", current);
            if (isLeaf(current)) {
                fwrite(&current->item, 1, 1, out_file);
                current = root;                
            }
        }
    }

    fclose(in_file);
    fclose(out_file);
}
void saveFrequency(FILE* file, int freq[256]) {
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            fprintf(file, "%c:%d\n", i, freq[i]);
        }
    }
    fprintf(file, "\n");
}

void loadFrequency(FILE* file, int freq[256], unsigned char data[256], int* size) {
    char ch;
    int frequency;
    *size = 0;

    while (true) {
        int result = fscanf(file, "%c:%d\n", &ch, &frequency);
        if (result == EOF) break; // Check for end of file
        if (result != 2) continue; // Skip invalid lines
        data[*size] = ch;
        freq[(unsigned char)ch] = frequency;
        (*size)++;
    }
}


int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Usage to compress: %s <input> -c <output>\n", argv[0]);
        printf("Usage to decompress: %s <input> -x <output>\n", argv[0]);
        return 1;
    }

    char* input_file = argv[1];
    char* operation = argv[2];
    char* output_file = argv[3];

    FILE* file;
    int freq[256] = {0};
    int size = 0;
    unsigned char data[256];

    struct MinHeapNode* root;
    int arr[MAX_TREE_HT], top = 0;
    char codes[256][MAX_TREE_HT] = {0};

    if (strcmp(operation, "-c") == 0) {
        file = fopen(input_file, "r");
        if (!file) {
            fprintf(stderr, "Cannot open input file: %s\n", input_file);
            return 1;
        }

        unsigned char ch;
        while (fscanf(file, "%c", &ch) != EOF) {
            if (freq[ch] == 0) 
            data[size++] = ch;
            freq[ch]++;
        }
        fclose(file);

        file = fopen(output_file, "w");
        saveFrequency(file, freq);
        root = buildHuffmanTree(data, freq, size);
        getCodes(root, arr, top, codes);
        writeEncodedFile(input_file, output_file, codes);
        fclose(file);
        
        printf("Compressed %s into %s\n", input_file, output_file);
    } else if (strcmp(operation, "-x") == 0) {
        file = fopen(input_file, "r");
    if (!file) {
        fprintf(stderr, "Cannot open encoded file: %s\n", input_file);
        return 1;
    }

    loadFrequency(file, freq, data, &size);
    long start_pos = ftell(file) + 1; // Получаем текущую позицию в файле и учитываем переход на новую строку

    root = buildHuffmanTree(data, freq, size);

    decodeFile(root, input_file, output_file, start_pos);

    printf("Decompressed %s into %s\n", input_file, output_file);
    fclose(file);

    } else {
        fprintf(stderr, "Invalid operation. Use -c to compress, -x to decompress.\n");
        return 1;
    }

    return 0;
} 
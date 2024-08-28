#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
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

struct MinHeap* buildMinHeapFromFreq(int freq[]) {
    struct MinHeap* minHeap = createMinHeap(256);
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            minHeap->array[minHeap->size] = newNode((char)i, freq[i]);
            minHeap->size++;
        }
    }
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(int freq[]) {
    struct MinHeap* minHeap = buildMinHeapFromFreq(freq);
    while (minHeap->size != 1) {
        struct MinHeapNode *left = extractMin(minHeap), *right = extractMin(minHeap);
        struct MinHeapNode *top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void storeCodes(struct MinHeapNode* root, int arr[], int top, char* codes[]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, codes);
    }
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, codes);
    }
    if (!(root->left) && !(root->right)) {
        codes[(unsigned char)root->data] = (char*)malloc(top + 1);
        for (int i = 0; i < top; ++i)
            codes[(unsigned char)root->data][i] = arr[i] + '0';
        codes[(unsigned char)root->data][top] = '\0';
    }
}

void compressFile(const char* inputFileName, const char* archiveFileName) {
    FILE* inFile = fopen(inputFileName, "rb");
    if (!inFile) {
        perror("Cannot open file to read");
        return;
    }

    unsigned int freq[256] = {0};
    char ch;
    while (fread(&ch, sizeof(char), 1, inFile)) {
        freq[(unsigned char)ch]++;
    }

    fseek(inFile, 0, SEEK_SET);

    struct MinHeapNode* root = buildHuffmanTree(freq);

    char* codes[256] = {0};
    int arr[MAX_TREE_HT];
    storeCodes(root, arr, 0, codes);

    FILE* outFile = fopen(archiveFileName, "wb");
    if (!outFile) {
        perror("Cannot open file to write");
        fclose(inFile);
        return;
    }

    if (fwrite(freq, sizeof(freq), 1, outFile) < 1) {
        perror("Failed to write frequencies to file");
        fclose(inFile);
        fclose(outFile);
        return;
    }

    unsigned char buffer = 0;
    int bitCount = 0;
    while (fread(&ch, sizeof(char), 1, inFile)) {
        char* code = codes[(unsigned char)ch];
        while (*code) {
            buffer = (buffer << 1) | (*code++ - '0');
            bitCount++;
            if (bitCount == 8) {
                if (fwrite(&buffer, sizeof(char), 1, outFile) < 1) {
                    perror("Failed to write data to file");
                    fclose(inFile);
                    fclose(outFile);
                    return;
                }
                buffer = 0;
                bitCount = 0;
            }
        }
    }

    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        if (fwrite(&buffer, sizeof(char), 1, outFile) < 1) {
            perror("Failed to write the final bits to file");
            fclose(inFile);
            fclose(outFile);
            return;
        }
        // Write the count of significant bits in the last byte
        if (fwrite(&bitCount, sizeof(char), 1, outFile) < 1) {
            perror("Failed to write the bit count to file");
            fclose(inFile);
            fclose(outFile);
            return;
        }
    }

    fclose(inFile);
    fclose(outFile);

    for (int i = 0; i < 256; ++i) {
        if (codes[i]) {
            free(codes[i]);
        }
    }
}


void decompressFile(const char* archiveFileName, const char* outputFileName) {
    FILE* inFile = fopen(archiveFileName, "rb");
    if (!inFile) {
        perror("Cannot open file to read");
        return;
    }

    int freq[256] = {0};
    if (fread(freq, sizeof(freq), 1, inFile) < 1) {
        perror("Failed to read frequencies from file");
        fclose(inFile);
        return;
    }

    struct MinHeapNode* root = buildHuffmanTree(freq);

    FILE* outFile = fopen(outputFileName, "wb");
    if (!outFile) {
        perror("Cannot open file to write");
        fclose(inFile);
        return;
    }

    fseek(inFile, -1, SEEK_END); // Move to the last byte that contains the valid bits count
    long dataSize = ftell(inFile) - sizeof(freq); // Calculate the data size

    unsigned char lastByteInfo;
    fread(&lastByteInfo, sizeof(char), 1, inFile); // Read the last byte to get the count of significant bits

    fseek(inFile, sizeof(freq), SEEK_SET); // Move to the start of the encoded data

    struct MinHeapNode* current = root;
    int bit;
    unsigned char byte;
    long totalBits = (dataSize - 1) * 8 + lastByteInfo; // Adjusting the bits count

    while (totalBits > 0 && fread(&byte, sizeof(byte), 1, inFile) == 1) {
        for (int i = 0; i < 8; i++) {
            if (--totalBits < 0) break; // Ensure we don't read past the valid bits
            bit = (byte >> (7 - i)) & 1;
            current = bit ? current->right : current->left;

            if (!current->left && !current->right) {
                fwrite(&current->data, sizeof(char), 1, outFile);
                current = root;
            }
        }
    }

    fclose(inFile);
    fclose(outFile);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <-c|-x> <output_file>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[2], "-c") == 0) {
        compressFile(argv[1], argv[3]);
    } else if (strcmp(argv[2], "-x") == 0) {
        decompressFile(argv[1], argv[3]);
    } else {
        printf("Unknown command: %s\n", argv[2]);
        return 1;
    }

    return 0;
}

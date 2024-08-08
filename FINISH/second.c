// Нам нужно написать код Хаффмана для сжатия данных.
// У нас есть файл input.txt с текстом, который нужно сжать в файл archive.
// С помощью команды "huff input.txt -c archive" мы должны сжать файл input.txt в файл archive.
// С помощью команды "huff archive -x output.txt" мы должны распаковать файл archive в файл output.txt.
// Вам нужно написать код для сжатия и распаковки данных.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_TREE_HT 256

struct MinHeapNode {
    char item;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(char item, unsigned freq)
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)
{
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

int isSizeOne(struct MinHeap* minHeap)
{
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

int isLeaf(struct MinHeapNode* root)
{
    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char item[], int freq[], int size)
{
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(item[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char item[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(item, freq, size);
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

void printCodes(struct MinHeapNode* root, int arr[], int top, char codes[256][256], FILE* out)
{
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, codes, out);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, codes, out);
    }

    if (isLeaf(root)) {
        fprintf(out, "%c: ", root->item);
        for (int i = 0; i < top; ++i) {
            fprintf(out, "%d", arr[i]);
            sprintf(codes[(unsigned char) root->item] + i, "%d", arr[i]);
        }
        fprintf(out, "\n");
    }
}

void HuffmanCodes(char item[], int freq[], int size, FILE* out)
{
    struct MinHeapNode* root = buildHuffmanTree(item, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    char codes[256][256] = {0};
    printCodes(root, arr, top, codes, out);

    for (int i = 0; i < 256; ++i) {
        if (codes[i][0]) {
            printf("%c: %s\n", i, codes[i]);
        }
    }
}

void saveTree(struct MinHeapNode* root, FILE* out) {
    if (root == NULL) {
        fprintf(out, "#");
        return;
    }
    fprintf(out, "%c", root->item);
    saveTree(root->left, out);
    saveTree(root->right, out);
}

struct MinHeapNode* loadTree(FILE* in) {
    char c = fgetc(in);
    if (c == '#') {
        return NULL;
    }
    struct MinHeapNode* node = newNode(c, 0);
    node->left = loadTree(in);
    node->right = loadTree(in);
    return node;
}

void saveCodes(struct MinHeapNode* root, int arr[], int top, FILE* out) {
    if (root->left) {
        arr[top] = 0;
        saveCodes(root->left, arr, top + 1, out);
    }

    if (root->right) {
        arr[top] = 1;
        saveCodes(root->right, arr, top + 1, out);
    }

    if (isLeaf(root)) {
        fprintf(out, "%c:", root->item);
        for (int i = 0; i < top; ++i) {
            fprintf(out, "%d", arr[i]);
        }
        fprintf(out, "\n");
    }
}

void compress(char* input, char* output) {
    FILE* in = fopen(input, "r");
    FILE* out = fopen(output, "wb");

    char item[256];
    int freq[256] = {0};
    int size = 0;

    char c;
    while ((c = fgetc(in)) != EOF) {
        if (freq[c] == 0) {
            item[size] = c;
            size++;
        }
        freq[c]++;
    }

    struct MinHeapNode* root = buildHuffmanTree(item, freq, size);
    saveTree(root, out);
    fprintf(out, "\n");

    int arr[MAX_TREE_HT], top = 0;
    char codes[256][256] = {0};
    saveCodes(root, arr, top, out);

    rewind(in);
    char buf = 0;
    int bit_count = 0;
    while ((c = fgetc(in)) != EOF) {
        const char* code = codes[(unsigned char)c];
        for (int i = 0; code[i]; ++i) {
            buf = (buf << 1) | (code[i] - '0');
            bit_count++;
            if (bit_count == 8) {
                fputc(buf, out);
                buf = 0;
                bit_count = 0;
            }
        }
    }
    if (bit_count > 0) {
        buf <<= (8 - bit_count);
        fputc(buf, out);
    }

    fclose(in);
    fclose(out);
}

void decompress(char* input, char* output) {
    FILE* in = fopen(input, "rb");
    FILE* out = fopen(output, "w");

    if (!in || !out) {
        perror("Failed to open file");
        return;
    }

    struct MinHeapNode* root = loadTree(in);
    fgetc(in); // Skip newline after tree

    struct MinHeapNode* cur = root;
    int bit_count = 0;
    char buf;

    while ((buf = fgetc(in)) != EOF) {
        for (int i = 0; i < 8; ++i) {
            int bit = (buf >> (7 - i)) & 1;
            cur = bit ? cur->right : cur->left;
            if (isLeaf(cur)) {
                fputc(cur->item, out);
                cur = root; // Go back to the root
            }
        }
    }

    fclose(in);
    fclose(out);
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        printf("Usage: %s <input> -c <output> or %s <input> -x <output>\n", argv[0], argv[0]);
        return 1;
    }

    if (strcmp(argv[2], "-c") == 0) {
        compress(argv[1], argv[3]);
    } else if (strcmp(argv[2], "-x") == 0) {
        decompress(argv[1], argv[3]);
    } else {
        printf("Usage: %s <input> -c <output> or %s <input> -x <output>\n", argv[0], argv[0]);
        return 1;
    }

    return 0;
}


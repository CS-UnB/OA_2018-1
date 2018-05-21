//LE5_OA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID -1 /* setted as the symbol of the non-leaf nodes */
#define N 256   /* how many symbols are accepted */

enum { ENCODE, DECODE }; /* program options */

/* Describes each tree node */
struct node {
    int is_zero;
    int is_root;
    int is_leaf;
    
    struct node *parent;
    struct node *left_child;
    struct node *right_child;
    
    unsigned char symbol;
    int value;
    int order;
};
typedef struct node Node;

/* Describes each symbol, containing a pointer to its node in the tree */
struct symbol {
    char symbol;
    Node *tree;
};
typedef struct symbol Symbol;

/* Creates the initial tree just containing the root node.
 * returns: a pointer to the root.
 */
Node* build_tree() {
    Node *tree = (Node*)malloc(sizeof(Node));
    tree->is_zero = 1;
    tree->is_root = 1;
    tree->is_leaf = 1;
    
    tree->parent        = NULL;
    tree->left_child    = NULL;
    tree->right_child    = NULL;
    
    tree->symbol    = INVALID;
    tree->value     = 0;
    tree->order     = N * 2; /* generally 512 (considering char = 8 bits) */
    
    return tree;
}

/* Obtains the tree node based on its symbol.
 * symbol: the desired symbol.
 * symbols: the array of all symbols.
 * returns: a pointer to the tree node corresponding to the passed symbol. If the node does not exist, a NULL pointer is returned.
 */
Node* get_tree(unsigned char symbol, Symbol **symbols) {
    Symbol *symbol_ptr = symbols[(unsigned int)symbol];

    if (!symbol_ptr) {
        return NULL;
    }
    
    return symbol_ptr->tree;
}

/* Reverse an array of integers
 * code: the array that will be reserved;
 * codeSize: how many elements are contained in the array.
 */
void reserve(int *code, int codeSize) {
    if (code == NULL) {
        printf("reserve: tried to reverse a NULL code.\n");
        return;
    }
    
    int *start = code;
    int *end = code+(codeSize-1);
    
    while (start < end) {
        int temp    = *start;
        *start      = *end;
        *end        = temp;
        start++;
        end--;
    }
}

/* Returns an array of integers (i.e. 0 and 1s) containing the code corresponding to the given node.
 * node: the tree node.
 * n: the number of digits in the array that will be returned.
 * returns an array of integers containing the code.
 */
int* code_of(Node *node, int *n) {
    Node *current = node;
    int *code = (int*)malloc(sizeof(int) * N * 2); /* worst case */
    
    int i = 0;
    while (!current->is_root) {
        Node *parent = current->parent;
        code[i] = (parent->left_child == current) ? 0 : 1;
        current = current->parent;
        i++;
    }
    reserve(code, i);
    
    *n = i;
    return code;
}

/* Creates a new child.
 * parent: the parent node that will be created.
 * is_zero: 1 if the node is a ZERO node, or 0 otherwise.
 * is_root: 1 if the created node is a root node, or 0 otherwise.
 * symbol: the symbol attributed to the node.
 * value: the value attributed to the node.
 * order: the order attributed to the node.
 * returns: the created node.
 */
Node* add_leaf(Node *parent, int is_zero, int is_root, unsigned char symbol, int value, int order) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->is_zero       = is_zero;
    node->is_root       = is_root;
    node->is_leaf       = 1;
    node->parent        = parent;
    node->left_child    = NULL;
    node->right_child   = NULL;
    node->symbol        = symbol;
    node->value         = value;
    node->order         = order;
    return node;
}

/* Adds a new symbol in the tree and in the array of symbols
 * symbol: the symbol that will be inserted
 * zeroNode: reference to where the node ZERO points to.
 * symbols: the array of symbols
 * returns: the leaf node's (that contains the added symbol) parent.
 */
Node* add_symbol(unsigned char symbol, Node **zeroNode, Symbol **symbols) {
    Node *leftNode = add_leaf(*zeroNode, 1, 0, INVALID, 0, (*zeroNode)->order - 2);
    Node *rightNode = add_leaf(*zeroNode, 0, 0, symbol, 1, (*zeroNode)->order - 1);
    
    Node *previousZeroNode      = *zeroNode;
    (*zeroNode)->is_zero        = 0;
    (*zeroNode)->is_leaf        = 0;
    (*zeroNode)->left_child     = leftNode;
    (*zeroNode)->right_child    = rightNode;
    
    unsigned int symbolIndex    = (unsigned int)symbol;
    symbols[symbolIndex]        = (Symbol*)malloc(sizeof(Symbol));
    symbols[symbolIndex]->symbol= symbol;
    symbols[symbolIndex]->tree  = rightNode;
    
    *zeroNode = leftNode;
    
    return previousZeroNode;
}

/* Searches for the node that has the same value as the input node (with a maximum order value).
 * currMax: the input node.
 * root: the tree's root.
 * returns: the node that has the same value as the input node (with a maximum order value). if it doesn't exist, NULL is returned.
 */
Node* replace(Node *currMax, Node *root) {
    Node *result = currMax;
    
    if (root->value > result->value && !root->is_leaf) {
        Node *greatestLeft = replace(result, root->left_child);
        if (greatestLeft) result = greatestLeft;
        
        Node *greatestRight = replace(result, root->right_child);
        if (greatestRight) result = greatestRight;
    } else if (root->value == result->value && root->order > result->order) {
        result = root;
    }
    
    return (result != currMax) ? result : NULL;
}

/* Swap nodes.
 * Note: the orders are not swapped, since they are independent from the node's content.
 */
void swap(Node *n1, Node *n2) {
    int tempOrder = n1->order;
    n1->order = n2->order;
    n2->order = tempOrder;
    
    if (n1->parent->left_child == n1) {
        n1->parent->left_child = n2;
    } else {
        n1->parent->right_child = n2;
    }
    
    if (n2->parent->left_child == n2) {
        n2->parent->left_child = n1;
    } else {
        n2->parent->right_child = n1;
    }
    
    Node *temp = n1->parent;
    n1->parent = n2->parent;
    n2->parent = temp;
}

/* Updates the tree based on an initial node.
 * currNode: the starting node that will be updated.
 * root: the tree's root.
 */
void update(Node *currNode, Node *root) {
    while (!currNode->is_root) {
        Node *replaceNode = replace(currNode, root);
        
        /* se replaceNode for o pai de currentNode, eles nao podem ser trocados */
        if (replaceNode && currNode->parent != replaceNode) {
            swap(currNode, replaceNode);
        }
        
        (currNode->value)++;
        currNode = currNode->parent;
    }
    
    (currNode->value)++;
}

/* Adds a code (of 0 and 1s) to the output buffer. When the buffer gets full, it will be written in the file.
 * code: the code that will be added into the output buffer. WHen the buffer gets full, it will be written in the file.
 * codeSize: how many bits are contained in code.
 * fp: the output file.
 * buffer: the input buffer.
 * bufferSize: how many bits in buffer are waiting to be written.
 * returns: the new buffer. 
 */
unsigned char code_to_buffer(int *code, int codeSize, FILE *fp, unsigned char buffer, int *bufferSize) {
    unsigned char currBuffer = buffer;
    
    int i;
    for (i = 0; i < codeSize; i++) {
        unsigned char bit = ((unsigned char) code[i]) << (*bufferSize - 1);
        currBuffer = currBuffer | bit;
        
        (*bufferSize)--;
        
        if (*bufferSize == 0) {
            fwrite(&currBuffer, sizeof(unsigned char), 1, fp);
            currBuffer = 0;
            *bufferSize = 8;
        }
    }
    
    return currBuffer;
}

/* Adds a byte into the output buffer. If the buffer is not previously empty, a byte will be written in the output file.
 * byte: the byte that will be written in the buffer.
 * fp: The output file.
 * buffer: the input buffer.
 * bufferSize: how many bits in the buffer are waiting to be written.
 * returns: the new buffer.
 */
unsigned char byte_to_buffer(char byte, FILE *fp, unsigned char buffer, int *bufferSize) {
    unsigned char currBuffer = buffer;
    
    int howManyBitsWillBeWritten = *bufferSize;
    int shiftSize = 8 - howManyBitsWillBeWritten;
    unsigned char tempByte = ((unsigned char) byte) >> shiftSize;
    currBuffer = currBuffer | tempByte;
    
    fwrite(&currBuffer, sizeof(unsigned char), 1, fp);
    
    currBuffer = byte << howManyBitsWillBeWritten;
    
    return (*bufferSize == 8) ? 0 : currBuffer;
}

/* Writes the buffer in the output file.
 * Also writes the last byte containing the amount of bits that the decoder will read in the next to last byte.
 *
 * fp: the output file.
 * buffer: the input buffer.
 * bufferSize: how many bits should be written in the buffer.
 */
void leftover_bits(FILE *fp, unsigned char buffer, int bufferSize) {
    if (bufferSize < 8) {
        fwrite(&buffer, sizeof(unsigned char), 1, fp);
    }
    
    /* Writes in the last byte how many bits should be read by the decoded in the next to last byte. */
    buffer = (bufferSize == 8) ? 8 : 8 - bufferSize;
    fwrite(&buffer, sizeof(unsigned char), 1, fp);
}

/* Encodes the file.
 * fp_in: the input file (the one that will be encoded).
 * fp_out: the output file.
 */
void encode(FILE *fp_in, FILE *fp_out) {
    Node *root = build_tree();
    Node *zeroNode = root;
    
    unsigned char buffer = 0;
    int bufferSize = 8;
    
    Symbol **symbols = (Symbol**)calloc(N, sizeof(Symbol*)); /* initializing with 0s */
    
    unsigned char currByte;
    while (fread(&currByte, sizeof(unsigned char), 1, fp_in) > 0) {
        Node *symbolTree = get_tree(currByte, symbols);
        
        if (symbolTree) {
            int codeSize;
            int *symbolCode = code_of(symbolTree, &codeSize);
            buffer = code_to_buffer(symbolCode, codeSize, fp_out, buffer, &bufferSize);
            
            update(symbolTree, root);
            free(symbolCode);
        } else {
            int codeSize;
            
            int *zeroCode = code_of(zeroNode, &codeSize);
            buffer = code_to_buffer(zeroCode, codeSize, fp_out, buffer, &bufferSize);
            buffer = byte_to_buffer(currByte, fp_out, buffer, &bufferSize);
            
            Node *newNode = add_symbol(currByte, &zeroNode, symbols);
            update(newNode, root);
            free(zeroCode);
        }
    }
    
    leftover_bits(fp_out, buffer, bufferSize);
}

/* Read the next bit to be read in the biffer and returns it.
 * fp: input file (that will be read in case the buffer limit is reached).
 * buffer: the input buffer, that can be updated in case a read operation if performed in the input file.
 * bufferSize: how many bits there are left to be read in the buffer.
 * fileSize: the filesize (until its next to last byte).
 * readHowManyBitsAtTheEnd: how many bits should be read in the next to last byte.
 * returns: the bit (0 or 1).
 */
int read_bit(FILE *fp, unsigned char *buffer, int *bufferSize, long int fileSize, int readHowManyBitsAtTheEnd) {
    if (*bufferSize == 0) {
        *bufferSize = 8;
        fread(buffer, sizeof(unsigned char), 1, fp);
    }
    
    if (readHowManyBitsAtTheEnd != 8) {
        if (ftell(fp) == fileSize && readHowManyBitsAtTheEnd <= (8 - *bufferSize)) return -1;
    }
    
    if (ftell(fp) > fileSize || feof(fp)) return -1;
    
    (*bufferSize)--;
    
    return (*buffer >> *bufferSize) & 1;
}

/* Reads the next 8 bits to be read and return it as a char.
 * fp: input file (that will be read in case the buffer limit is reached).
 * buffer: the input buffer, that can be updated in case a read operation if performed in the input file.
 * bufferSize: how many bits there are left to be read in the buffer.
 * fileSize: the filesize (until its next to last byte).
 * readHowManyBitsAtTheEnd: how many bits should be read in the next to last byte.
 * returns: the read byte.
 */
char read_byte(FILE *fp, unsigned char *buffer, int *bufferSize, long int fileSize, int readHowManyBitsAtTheEnd) {
    char result = 0;
    
    int i, bit;
    for (i = 0; i < 8; i++) {
        bit = read_bit(fp, buffer, bufferSize, fileSize, readHowManyBitsAtTheEnd);
        bit = bit << (7-i);
        result |= bit;
    }
    
    return result;
}

/* Decodes the file
 * fp_in: input file (the one that will be decoded)
 * fp_out: the output file
 */
void decode(FILE *fp_in, FILE *fp_out) {
    Node *root = build_tree();
    Node *zeroNode = root;
    
    unsigned char buffer = 0;
    int bufferSize = 0;
    
    Symbol **symbols = (Symbol**)calloc(N, sizeof(Symbol*)); /* initializing with 0s */
    
    /* Obtains the file size (excluding the last byte). */
    fseek(fp_in, -1, SEEK_END);
    long int fileSize = ftell(fp_in);
    
    /* Reads the last byte, which contains the number of bits that should be read in the previous byte */
    unsigned char readHowManyBitsAtTheEnd;
    fread(&readHowManyBitsAtTheEnd, sizeof(unsigned char), 1, fp_in);
    rewind(fp_in);
    
    while (!feof(fp_in)) {
        Node *currNode = root;
        
        int endOfFile = 0;
        while (!currNode->is_leaf && !endOfFile) {
            int bit = read_bit(fp_in, &buffer, &bufferSize, fileSize, readHowManyBitsAtTheEnd);
            if (bit == 0) {
                currNode = currNode->left_child;
            } else if (bit == 1) {
                currNode = currNode->right_child;
            } else {
                endOfFile = 1;
            }
        }
        
        if (endOfFile) break;
        
        unsigned char c;
        if (currNode->is_zero) {
            c = read_byte(fp_in, &buffer, &bufferSize, fileSize, readHowManyBitsAtTheEnd);
            currNode = add_symbol(c, &zeroNode, symbols);
        } else {
            c = currNode->symbol;
        }
        
        fwrite(&c, sizeof(unsigned char), 1, fp_out);
        update(currNode, root);
    }
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
        printf("Usage:\n");
		printf("\t./fgk input_file output_file -c (to encode)\n");
		printf("\t./fgk input_file output_file -d (to decode)\n");
		exit(1);
	}
	
    FILE *fp_in;
    FILE *fp_out;
    int option;
    
    /* input file */
    fp_in = fopen(argv[1], "rb");
    while (fp_in == NULL) {
        char in_file[100];
        printf("The file %s could not be opened. Try again: ", argv[1]);
        scanf("%s", in_file);
        fp_in = fopen(in_file, "rb");
    }

    /* output file */
    fp_out = fopen(argv[2], "wb");

    /* option: encode or decode */
    if (strcmp(argv[3], "-c") == 0 || strcmp(argv[3], "-C") == 0) {
        option = ENCODE;
    } else if (strcmp(argv[3], "-d") == 0 || strcmp(argv[3], "-D") == 0) {
        option = DECODE;
    } else {
        char opt;
        do {
            printf("Invalid option, type 'c' to encode or 'd' to decode: ");
            scanf("%c", &opt);
            getchar();
        } while (opt != 'c' && opt != 'C' && opt != 'd' && opt != 'D');
        option = (opt == 'c' || opt == 'C') ? ENCODE : DECODE;
    }
    
    if (option == ENCODE) {
        encode(fp_in, fp_out);
        printf("The file was encoded successfully.\n");
    } else {
        decode(fp_in, fp_out);
        printf("The file was decoded successfully\n");
    }
    
    fclose(fp_in);
    fclose(fp_out);
    
    return 0;
}
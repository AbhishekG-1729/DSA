#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Block {
    size_t size;
    bool free;
    struct Block* prev;
    struct Block* next;
} Block;
Block* head = NULL;
Block* create_block(size_t size) {
    Block* block = (Block*)malloc(sizeof(Block));
    if (!block) {
        perror("Failed to allocate block");
        exit(EXIT_FAILURE);
    }
    block->size = size;
    block->free = true;
    block->prev = NULL;
    block->next = NULL;
    return block;
}
void initialize_memory(size_t sizes[], int n) {
    Block* current = NULL;
    for (int i = 0; i < n; i++) {
        Block* block = create_block(sizes[i]);
        if (head == NULL) {
            head = block;
            current = block;
        } else {
            current->next = block;
            block->prev = current;
            current = block;
        }
    }
}
Block* first_fit_alloc(size_t size) {
    Block* current = head;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            current->free = false;
            printf("Allocated block of size %zu\n", current->size);
            return current;
        }
        current = current->next;
    }
    printf("No suitable block found for size %zu\n", size);
    return NULL;
}
void free_block(Block* block) {
    if (block != NULL && !block->free) {
        block->free = true;
        printf("Freed block of size %zu\n", block->size);
    }
}
void print_memory() {
    Block* current = head;
    int index = 1;
    printf("Memory Blocks:\n");
    while (current != NULL) {
        printf("Block %d: Size = %zu, %s\n", index, current->size, current->free ? "Free" : "Allocated");
        current = current->next;
        index++;
    }
    printf("\n");
}
int main() {
    int n;
    printf("Enter number of memory blocks: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input for number of blocks.\n");
        return 1;
    }
    size_t* block_sizes = (size_t*)malloc(n * sizeof(size_t));
    if (!block_sizes) {
        perror("Failed to allocate memory for block sizes");
        return 1;
    }
    printf("Enter sizes of %d memory blocks:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%zu", &block_sizes[i]) != 1 || block_sizes[i] == 0) {
            printf("Invalid input for block size.\n");
            free(block_sizes);
            return 1;
        }
    }
    initialize_memory(block_sizes, n);
    free(block_sizes);
    print_memory();
    int alloc_count;
    printf("Enter number of allocations: ");
    if (scanf("%d", &alloc_count) != 1 || alloc_count <= 0) {
        printf("Invalid input for number of allocations.\n");
        return 1;
    }
    Block** allocated_blocks = (Block**)malloc(alloc_count * sizeof(Block*));
    if (!allocated_blocks) {
        perror("Failed to allocate memory for allocated blocks");
        return 1;
    }
    for (int i = 0; i < alloc_count; i++) {
        size_t alloc_size;
        printf("Enter allocation size #%d: ", i + 1);
        if (scanf("%zu", &alloc_size) != 1 || alloc_size == 0) {
            printf("Invalid input for allocation size.\n");
            free(allocated_blocks);
            return 1;
        }
        allocated_blocks[i] = first_fit_alloc(alloc_size);
    }
    print_memory();
    free(allocated_blocks);
    Block* current = head;
    while (current != NULL) {
        Block* next = current->next;
        free(current);
        current = next;
    }
    return 0;
}

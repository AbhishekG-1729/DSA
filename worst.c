#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Block 
{
    size_t size;
    bool free;
    struct Block* prev;
    struct Block* next;
} Block;
Block* head = NULL;
Block* create_block(size_t size) 
{
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
void initialize_memory(size_t sizes[], int n) 
{
    Block* current = NULL;
    for (int i = 0; i < n; i++) 
    {
        Block* block = create_block(sizes[i]);
        if (head == NULL) 
        {
            head = block;
            current = block;
        } 
        else 
        {
            current->next = block;
            block->prev = current;
            current = block;
        }
    }
}
Block* worst_fit_alloc(size_t size) 
{
    Block* current = head;
    Block* worst_block = NULL;
    size_t worst_size = 0; 
    while (current != NULL) 
    {
        if (current->free && current->size >= size && current->size > worst_size) 
        {
            worst_size = current->size;
            worst_block = current;
        }
        current = current->next;
    }
    if (worst_block != NULL) 
    {
        worst_block->free = false;
        printf("Allocated block of size %zu\n", worst_block->size);
        return worst_block;
    }
    printf("No suitable block found for size %zu\n", size);
    return NULL;
}
void free_block(Block* block) 
{
    if (block && !block->free) 
    {
        block->free = true;
        printf("Freed block of size %zu\n", block->size);
    }
}
void print_memory() 
{
    Block* current = head;
    int index = 1;
    printf("Memory Blocks:\n");
    while (current) 
    {
        printf("Block %d: Size = %zu, %s\n", index, current->size, current->free ? "Free" : "Allocated");
        current = current->next;
        index++;
    }
    printf("\n");
}
int main() 
{
    size_t block_sizes[] = {100, 500, 200, 300, 600};
    int n = sizeof(block_sizes) / sizeof(block_sizes[0]);
    initialize_memory(block_sizes, n);
    print_memory();
    Block* b1 = worst_fit_alloc(212);  
    Block* b2 = worst_fit_alloc(417);  
    print_memory();
    free_block(b1);
    print_memory();
    Block* b3 = worst_fit_alloc(100);  
    print_memory();
    return 0;
}

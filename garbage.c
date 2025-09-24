#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Block 
{
    size_t size;
    bool allocated; 
    struct Block* prev;
    struct Block* next;
} Block;
Block* head = NULL;
Block* create_block(size_t size) 
{
    Block* block = (Block*)malloc(sizeof(Block));
    if (!block) 
    {
        perror("Failed to allocate block");
        exit(EXIT_FAILURE);
    }
    block->size = size;
    block->allocated = false;  
    block->prev = NULL;
    block->next = NULL;
    return block;
}
void initialize_blocks(size_t sizes[], int n) 
{
    Block* current = NULL;
    for (int i = 0; i < n; i++) 
    {
        Block* block = create_block(sizes[i]);
        if (head == NULL) 
        {
            head = block;
            current = block;
        } else 
        {
            current->next = block;
            block->prev = current;
            current = block;
        }
    }
}
Block* allocate_block(size_t size) 
{
    Block* current = head;
    while (current) {
        if (!current->allocated && current->size >= size) 
        {
            current->allocated = true;
            printf("Allocated block of size %zu\n", current->size);
            return current;
        }
        current = current->next;
    }
    printf("No block available for size %zu\n", size);
    return NULL;
}
void free_block(Block* block) 
{
    if (block && block->allocated) 
    {
        block->allocated = false;
        printf("Freed block of size %zu\n", block->size);
    }
}
void garbage_collect() 
{
    Block* current = head;
    while (current && current->next) 
    {
        if (!current->allocated && !current->next->allocated) 
        {
            Block* next_block = current->next;
            current->size += next_block->size;
            current->next = next_block->next;
            if (next_block->next) 
            {
                next_block->next->prev = current;
            }
            printf("Merged two free blocks into size %zu\n", current->size);
            free(next_block);
        } else {
            current = current->next;
        }
    }
}
void print_blocks() 
{
    Block* current = head;
    printf("Memory Blocks:\n");
    while (current) 
    {
        printf("Block at %p - Size: %zu - %s\n",
               (void*)current, current->size,
               current->allocated ? "Allocated" : "Free");
        current = current->next;
    }
    printf("\n");
}
int main() 
{
    size_t sizes[] = {100, 200, 150, 300};
    int n = sizeof(sizes) / sizeof(sizes[0]);
    initialize_blocks(sizes, n);
    print_blocks();
    Block* b1 = allocate_block(150);
    Block* b2 = allocate_block(100);
    print_blocks();
    free_block(b1);
    free_block(b2);
    print_blocks();
    garbage_collect();
    print_blocks();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
        if (!head) 
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
Block* first_fit_alloc(size_t size) 
{
    Block* current = head;
    while (current) 
    {
        if (current->free && current->size >= size) 
        {
            current->free = false;
            printf("[First Fit] Allocated block of size %zu\n", current->size);
            return current;
        }
        current = current->next;
    }
    printf("[First Fit] No suitable block found for size %zu\n", size);
    return NULL;
}
Block* best_fit_alloc(size_t size) 
{
    Block* current = head;
    Block* best_block = NULL;
    size_t best_size = (size_t)-1; 
    while (current) 
    {
        if (current->free && current->size >= size && current->size < best_size) 
        {
            best_size = current->size;
            best_block = current;
        }
        current = current->next;
    }
    if (best_block) 
    {
        best_block->free = false;
        printf("[Best Fit] Allocated block of size %zu\n", best_block->size);
        return best_block;
    }
    printf("[Best Fit] No suitable block found for size %zu\n", size);
    return NULL;
}
Block* worst_fit_alloc(size_t size) 
{
    Block* current = head;
    Block* worst_block = NULL;
    size_t worst_size = 0;
    while (current) 
    {
        if (current->free && current->size >= size && current->size > worst_size) 
        
        {
            worst_size = current->size;
            worst_block = current;
        }
        current = current->next;
    }
    if (worst_block) 
    {
        worst_block->free = false;
        printf("[Worst Fit] Allocated block of size %zu\n", worst_block->size);
        return worst_block;
    }
    printf("[Worst Fit] No suitable block found for size %zu\n", size);
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
void garbage_collect() {
    Block* current = head;
    int merged_count = 0;
    while (current && current->next) 
    {
        if (current->free && current->next->free) 
        {
            Block* next_block = current->next;
            current->size += next_block->size;
            current->next = next_block->next;
            if (next_block->next) 
            {
                next_block->next->prev = current;
            }
            free(next_block);
            merged_count++;
        } else {
            current = current->next;
        }
    }
    printf("Garbage collector merged %d blocks\n", merged_count);
}
void print_memory() 
{
    Block* current = head;
    int idx = 1;
    printf("Memory Blocks:\n");
    while (current) 
    {
        printf(" Block %d: Size = %zu, %s\n",
               idx++, current->size, current->free ? "Free" : "Allocated");
        current = current->next;
    }
    printf("\n");
}
int main() 
{
    size_t sizes[] = {100, 500, 200, 300, 600};
    int n = sizeof(sizes)/sizeof(sizes[0]);
    initialize_memory(sizes, n);
    print_memory();
    Block* a1 = first_fit_alloc(212);
    Block* a2 = best_fit_alloc(417);
    Block* a3 = worst_fit_alloc(100);
    print_memory();
    free_block(a1);
    free_block(a3);
    print_memory();
    garbage_collect();
    print_memory();
    return 0;
}
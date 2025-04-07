#include "vm.h"
#include "vmlib.h"

void *vmalloc(size_t size) {
    if (size == 0) return NULL; // Handle zero-size allocations

    // Align size to a multiple of 16
    size = (size + 15) & ~15;

    struct block_header *current = heapstart;
    struct block_header *best_fit = NULL;

    // Find the best-fit block
    while (current->size_status != VM_ENDMARK) {
        size_t block_size = BLKSZ(current);
        int is_busy = current->size_status & VM_BUSY;

        if (!is_busy && block_size >= size) {
            if (!best_fit || block_size < BLKSZ(best_fit)) {
                best_fit = current;
            }
        }

        current = (struct block_header *)((char *)current + block_size);
    }

    // If no suitable block found, return NULL
    if (!best_fit) return NULL;

    // Split block if necessary
    size_t best_fit_size = BLKSZ(best_fit);
    if (best_fit_size >= size + sizeof(struct block_header) + 16) {
        struct block_header *new_block = (struct block_header *)((char *)best_fit + sizeof(struct block_header) + size);
        new_block->size_status = (best_fit_size - size - sizeof(struct block_header)) | (best_fit->size_status & VM_PREVBUSY);

        best_fit->size_status = size | VM_BUSY | (best_fit->size_status & VM_PREVBUSY);

        struct block_footer *footer = (struct block_footer *)((char *)new_block - sizeof(struct block_footer));
        footer->size = size;
    } else {
        best_fit->size_status |= VM_BUSY;
    }

    return (void *)((char *)best_fit + sizeof(struct block_header));
}
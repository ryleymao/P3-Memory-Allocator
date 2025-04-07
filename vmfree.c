#include "vm.h"
#include "vmlib.h"

/**
 * The vmfree() function frees the memory space pointed to by ptr,
 * which must have been returned by a previous call to vmmalloc().
 * Otherwise, or if free(ptr) has already been called before,
 * undefined behavior occurs.
 * If ptr is NULL, no operation is performed.
 */
void vmfree(void *ptr) {
    if (!ptr) return; // Handle NULL pointers

    struct block_header *block = (struct block_header *)((char *)ptr - sizeof(struct block_header));

    if (!(block->size_status & VM_BUSY)) return; // Already free, do nothing

    block->size_status &= ~VM_BUSY; // Mark the block as free

    // Coalesce with the next block if free
    struct block_header *next_block = (struct block_header *)((char *)block + BLKSZ(block));
    if (!(next_block->size_status & VM_BUSY) && next_block->size_status != VM_ENDMARK) {
        block->size_status += BLKSZ(next_block) + sizeof(struct block_footer);
    }

    // Update the footer of the current block
    struct block_footer *footer = (struct block_footer *)((char *)block + BLKSZ(block) - sizeof(struct block_footer));
    footer->size = BLKSZ(block);
}
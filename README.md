Project 3: Memory Allocator (Malloc)

This project is a custom implementation of a simplified dynamic memory allocator in C, modeled after how malloc and free work in standard C libraries. The goal is to simulate memory allocation and freeing while exploring how real allocators manage heap space, perform coalescing, and avoid fragmentation.

It was developed as part of a systems programming course and focuses on low-level memory concepts, pointer arithmetic, bitwise operations, and writing C code that manipulates memory manually.

Overview
Implement two core functions:

void *vmalloc(size_t size);
This function allocates a block of memory from a fixed-size heap, similar to malloc.

Uses a best-fit allocation policy to minimize fragmentation

Returns a pointer to a 16-byte aligned address

If size <= 0 or no block is large enough, it returns NULL

Ensures all allocations and blocks are aligned to 16 bytes

void vmfree(void* ptr);
This function frees memory previously allocated by vmalloc.

If ptr == NULL, does nothing

If the block is already free, does nothing

Marks the block as free and coalesces with both adjacent free blocks (previous and next), forming one large block

Heap Structure
The allocator manages a heap of fixed size using a linked list of block headers. Each block contains metadata including its status (free or busy), size, and links to neighboring blocks. When blocks are freed, they may be merged (coalesced) with neighbors to reduce fragmentation and make space for larger future allocations.

vminfo() Enhancement
A helper function, vminfo(), traverses the heap and prints all block information (status, offset, size, previous block status). You are required to modify this function to print an additional line at the end:

csharp
Copy
Edit
The largest free block is #x with size y
Where:

x is the block ID (starting from 0) of the largest available block

y is the total size of that block (including its header)

If multiple blocks share the largest size, the one with the smallest ID is chosen

This allows for better debugging and visualization of the heap state.

Core Concepts Practiced
Manual memory management

Block metadata tracking

Heap traversal and visualization

Best-fit allocation strategy

Coalescing to reduce fragmentation

Pointer arithmetic and bitwise flag management

Writing tools to debug and display heap internals

Compilation
Use the provided Makefile to compile the program. Do not modify the Makefile.

go
Copy
Edit
make
The allocator must work on the ieng6 servers using the provided environment. All testing will be performed with the given scripts and test files.

Summary
This project provides practical experience in building a memory allocator from scratch, similar to malloc and free, focusing on correctness, efficiency, and memory reuse. It emphasizes understanding of how memory is managed at a low level and helps reinforce important systems programming concepts.

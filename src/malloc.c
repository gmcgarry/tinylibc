#include <unistd.h>

extern void *__heap_start;
extern void *__heap_end;

#define MAGIC	0xDEAD

struct block {
	int magic;
	int free;
	int size;
};

static void *lastaddr = &__heap_start;

void
free(void *mem)
{
	if (mem == 0) {
		printf("freeing null pointer\n");
		return;
	}
	struct block *block = mem - sizeof(struct block);
	if (block->magic != MAGIC) {
		printf("malloc bad magic 0x%08x\n", block->magic);
		return;
	}
	block->free = 1;
}

void *
malloc(long nbytes)
{
	void *mem = 0;

	nbytes = nbytes + sizeof(struct block);

	void *p = &__heap_start;
	while (p != lastaddr) {
		struct block *block = (struct block *)p;
		if (block->magic != MAGIC) {
			printf("bad magic 0x%04x, malloc corrupt\n", block->magic);
			return NULL;
		}
		if (block->free && block->size >= nbytes) {
			block->free = 0;
			mem = p;
			break;
		}
		p = p + block->size;
	}

	if (!mem) {
		struct block *block = mem = sbrk(nbytes);
		//printf("new block at %u\n", (unsigned int)mem);
		lastaddr += nbytes;
		block->magic = MAGIC;
		block->free = 0;
		block->size = nbytes;
	}

	return mem += sizeof(struct block);
}

#include <stdio.h>

void
__malloc_cleanup()
{
	void *p = &__heap_start;
	while (p != lastaddr) {
		struct block *block = (struct block *)p;
		if (block->magic != MAGIC) {
			printf("bad malloc magic 0x%04x\n", block->magic);
			return;
		}
		if (!block->free)
			printf("WARNING: leaked memory block at %u (%d bytes)\n", (unsigned int)p, (int)block->size);
		p = p + block->size;
	}
}

static void *heaptop = &__heap_start;

int
brk(void *addr)
{
	heaptop = addr;
	return 0;
}

void *
sbrk(intptr_t increment)
{
	void *last = heaptop;
	heaptop += increment;
	return last;
}

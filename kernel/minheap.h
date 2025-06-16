#include "param.h"
#include "spinlock.h"

struct min_heap {
  struct proc* data[NPROC];
  struct spinlock lock;
  int size;
};

void heap_init(struct min_heap *heap);
int heap_insert(struct min_heap *heap, struct proc *p);
struct proc* heap_extract_min(struct min_heap *heap);
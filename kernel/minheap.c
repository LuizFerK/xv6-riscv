#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "minheap.h"
#include "proc.h"

static int parent(int i) { return (i-1)/2; }
static int left(int i) { return 2*i + 1; }
static int right(int i) { return 2*i + 2; }

static void swap(struct proc **a, struct proc **b) {
  struct proc *temp = *a;
  *a = *b;
  *b = temp;
}

void heap_init(struct min_heap *heap) {
  heap->size = 0;
  initlock(&heap->lock, "minheap");
}

int heap_insert(struct min_heap *heap, struct proc *p) {
  acquire(&heap->lock);

  if (heap->size >= NPROC) {
    release(&heap->lock);
    return 0;
  }
  
  heap->data[heap->size] = p;
  int i = heap->size;
  heap->size++;
  
  // Heapify up
  while (i > 0 && heap->data[parent(i)]->pass > heap->data[i]->pass) {
    swap(&heap->data[parent(i)], &heap->data[i]);
    i = parent(i);
  }

  release(&heap->lock);
  return 1;
}

struct proc* heap_extract_min(struct min_heap *heap) {
  acquire(&heap->lock);

  if (heap->size <= 0) {
    release(&heap->lock);
    return 0;
  }
  
  struct proc *root = heap->data[0];
  heap->data[0] = heap->data[heap->size-1];
  heap->size--;
  
  // Heapify down
  int i = 0;
  while (1) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    
    if (l < heap->size && heap->data[l]->pass < heap->data[i]->pass)
      smallest = l;
    if (r < heap->size && heap->data[r]->pass < heap->data[smallest]->pass)
      smallest = r;
    if (smallest == i)
      break;
        
    swap(&heap->data[i], &heap->data[smallest]);
    i = smallest;
  }
  
  release(&heap->lock);
  return root;
}
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

int malloc_count = 0;
int free_count = 0;

//get malloc
void *malloc(size_t size)
{
  static void *(*fptr)(size_t) = NULL;

  /* look up of malloc, only the first time we are here */
 if (fptr == NULL)
 {
    fptr = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
    if (fptr == NULL)
    {
      printf("dlsym: %s\n", dlerror());
      return NULL;
    }
  }

  malloc_count++;
  return (*fptr)(size); // Calling original malloc
}

//get frees
void free(void *fptr)
{
  fptr = dlsym(RTLD_NEXT, "free");
  free_count++;
}

//report
static void report(void) {
    fprintf(stderr,"\nAnalysis finished!\n");
    fprintf(stderr,"Memory allocations: %d\n", malloc_count);
    fprintf(stderr,"Memory free: %d\n", free_count);
    fprintf(stderr,"Total memory leaks found: %d \n", malloc_count - free_count);
}


__attribute__((section(".fini_array"), used)) static typeof(report) *fini_p = report;



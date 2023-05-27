#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char **argv){ 

  char *cvalue = NULL;
  int index;
  int c;

  opterr = 0;


  while ((c = getopt (argc, argv, "ahp:")) != -1)
    switch (c)
      {
      case 'a':
        printf("Author Pamela Salazar Espinoza\n");
        break;
      case 'h':
        printf("Write -a to get author information\n");
        printf("Write -p <PROGRAM>,PROGRAM specifies the path to the program binary that will be analyzed\n");
        break;
      case 'p':
        //printf("Given memory leak to: %s\n", optarg);
        //cvalue = optarg;
        char str1[50] = "LD_PRELOAD=../lib/./libmemcheck.so ";
        strcat(str1, optarg);
        system("gcc -Wall -fPIC -shared -o ../lib/libmemcheck.so ../lib/libmemcheck.c");
        system(str1);
        break;
      case '?':
        if (optopt == 'p')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }


 // printf ("aflag = %d, bflag = %d, cvalue = %s\n",
 //         aflag, bflag, cvalue);

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  return 0;
}


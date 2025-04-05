#include "point_list.h"
#include "clist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(int argc, char* argv[]){

  intrusive_list_t list;
  init_list(&list);

  
  if (strcmp(argv[1], "loadtext") == 0){
    FILE *f_read = fopen(argv[2],"rt");
    int x, y;
    while(fscanf(f_read, "%d %d", &x, &y) > 0){

      add_point(&list, x, y);
    }
    fclose(f_read);
  }
  else if (strcmp(argv[1], "loadbin") == 0){
    FILE *f_read = fopen(argv[2],"rb");
    unsigned char x[3], y[3];
    while(fread(x, 1, sizeof(x), f_read) > 0 && fread(y, 1, sizeof(y), f_read) > 0){
      int x1 = x[0] | (x[1] << 8) | (x[2] << 16);
      int y1 = y[0] | (y[1] << 8) | (y[2] << 16);

      if (x1 > 5000000 || x1 < -5000000){
        x1 = x1 - (int)pow(2,24);
      }
      if (y1 > 5000000 || y1 < -5000000){
        y1 = y1 - (int)pow(2,24);
      }
      add_point(&list, x1, y1);
    }
    fclose(f_read);
  }
  
  if (strcmp(argv[3], "count") == 0){
    count(&list);
    
  }

  else if (strcmp(argv[3], "print") == 0){
    print(&list, argv[4]);

  }

  else if (strcmp(argv[3], "savetext") == 0){
    FILE *f_write = fopen(argv[4], "wt");
    savetext(&list, f_write);
    fclose(f_write);
  }
  else if (strcmp(argv[3], "savebin") == 0){
    FILE *f_write = fopen(argv[4], "wb");
    savebin(&list, f_write);
    fclose(f_write);
  }

  remove_all_points(&list);
  free(list.head);
  return 0;
}

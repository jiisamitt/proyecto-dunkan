#include "block_def.h"

int read_test() {
  char a[] = "/thanos/thanos.gif";
  crFILE *thanos = cr_open(a, 'r');
  if (thanos){
    printf("thanos loaded\n");
  }
  exit(0);
}
int main(int argc, char *argv[])
{
    // Revisar el input
    if (argc != 2)
        {
        printf("Modo de uso: ./crfs simdisk.bin\n");
        return 0;
        }

    cr_mount(argv[1]);
    printf("\n");
    read_test();

}

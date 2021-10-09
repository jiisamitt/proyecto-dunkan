#include "block_def.h"

int main(int argc, char *argv[])
{
    // Revisar el input
    if (argc != 2)
        {
        printf("Modo de uso: ./crfs simdisk.bin\n");
        return 0;
        }
    
    cr_mount(argv[1]);
    cr_ls("/");
    printf("\n");
    cr_mkdir("germy_te_amamos");
    print_binary(5* 2048 / 8, 6*2048 / 8);
    cr_ls("/");
    printf("\n");
    cr_load("test");
    cr_ls("/");
    printf("\n");

    char b[] = "/SSBS.mp3";
    cr_unload(b, "miusik.mp3");    
}

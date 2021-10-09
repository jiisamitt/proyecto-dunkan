#include "block_def.h"

int main(int argc, char *argv[])
{
    // Revisar el input
    if (argc != 2)
        {
        printf("Modo de uso: ./crfs simdisk.bin\n");
        return 0;
        }
    printf("#######################################################################\n");    
    printf("PONIENDO A PRUEBA MOUNT\n");
    cr_mount(argv[1]);
    printf("PRUEBA TERMINADA\n");
    printf("\n");

    printf("#######################################################################\n");    
    printf("PONIENDO A PRUEBA BITMAP\n");
    cr_bitmap();
    printf("PRUEBA TERMINADA\n");
    printf("\n");

    printf("#######################################################################\n");    
    printf("PONIENDO A PRUEBA EXISTS\n");
    char a[] = "/thanos/thanos.gif";
    // char a[] = "/thanos";
    // char a[] = "/wena/mala/thanos/thanos.gif";

    printf("Consulta: %s\n", a);
    int existe = cr_exists(a);
    printf("Existe:   %d\n", existe);
    printf("\n");
    printf("PRUEBA TERMINADA\n");
    printf("\n");

    printf("#######################################################################\n");    
    printf("PONIENDO A PRUEBA WRITE\n");
    printf("ESCRIBIENDO ...\n");
    crFILE* file_desc = (crFILE*) malloc(sizeof(crFILE));
    file_desc->mode = 1; // writting mode
    file_desc->p_pos=0;    // pointer to current pos

    /* 
       OJO al no estar instanciado en el bitmap se puede sobreescribir
       esto debe haber sido instanciado en cr_open junto con el bloque indice
       y el bitmap con este bloque actualizado 
       por lo tanto como hay 65536 bloques asi que pondremos el bloque indice en el ultimo
       para que no hayan sobreescrituras
    */
    // ********************************************************************************************************
    // PROBANDO WRITING CON UN STRING MUY LARGO

    file_desc->p_index= 2048*65528; // pointer to index block [apuntamos a otro bloque libre]   

    FILE* f = fopen("/home/mrf/Downloads/bla.txt", "rb");
    fseek(f, 0, SEEK_END); // Ponemos el puntero al final.
    int size_f = ftell(f); // Retorna la posición del puntero.
    fseek(f, 0, SEEK_SET); // Lo devolvemos al inicio.
    int written = 0;
    unsigned char* buffer = (unsigned char*) malloc(2048*sizeof(unsigned char));
    for (int i = 0; i < (size_f/2048)+1; i++){
        fread(buffer, 1, 2048, f);
        written += cr_write(file_desc, buffer, 2048);    
    }
    fclose(f);   

    // ********************************************************************************************************
    // PONIENDO A PRUEBA WRITING CON UN LIBRO

    // file_desc->p_index= 2048*65530; // pointer to index block
    // // modificar cr_write para que se vea que se usaron bloques de dir. 
    // // indirecto

    // FILE* f = fopen("/home/mrf/Documents/2019-1/SO/Proyecto/P1_Files/android_book.pdf", "rb");
    // fseek(f, 0, SEEK_END); // Ponemos el puntero al final.
    // int size_f = ftell(f); // Retorna la posición del puntero.
    // fseek(f, 0, SEEK_SET); // Lo devolvemos al inicio.
    // int written = 0;
    // unsigned char* buffer = (unsigned char*) malloc(2048*sizeof(unsigned char));
    // for (int i = 0; i < (size_f/2048)+1; i++){
    //     fread(buffer, 1, 2048, f);
    //     written += cr_write(file_desc, buffer, 2048);    
    // }
    // fclose(f);
    // ********************************************************************************************************
    // PONIENDO A PRUEBA WRITING CON tamanho max.

    // file_desc->p_index= 2048*65526; // pointer to index block
    // // modificar cr_write para que se vea que se usaron bloques de dir. 
    // // indirecto

    // FILE* f = fopen("/home/mrf/Downloads/archlinux-2019.05.02-x86_64.iso", "rb");
    // fseek(f, 0, SEEK_END); // Ponemos el puntero al final.
    // int size_f = ftell(f); // Retorna la posición del puntero.
    // fseek(f, 0, SEEK_SET); // Lo devolvemos al inicio.
    // int written = 0;
    // unsigned char* buffer = (unsigned char*) malloc(2048*sizeof(unsigned char));
    // for (int i = 0; i < (size_f/2048)+1; i++){
    //     fread(buffer, 1, 2048, f);
    //     int s;
    //     s = cr_write(file_desc, buffer, 2048);
    //     if (s==0){
    //         break;
    //     }
        
    //     written += s;
    // }
    // fclose(f);
    // ********************************************************************************************************

    printf("se escribieron:   %d Bytes\n\n", written);   

    printf("imprimiendo bloque indice\n");
    print_binary(((file_desc->p_index)-32)/8, ((file_desc->p_index)+150)/8);
    
    printf("\n");
    printf("VIENDO BLOQUES ESCRITOS A TRAVES DEL BITMAP\n");
    cr_bitmap();

    free(file_desc);
    printf("PRUEBA TERMINADA\n");
}

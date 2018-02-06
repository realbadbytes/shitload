#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

#define E_HDR 1

/* switch on/off */
#define DEBUG
/* optional print debug */
#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    printf(fmt, ## args)
#endif

char* read_bin(FILE *fp, char* bin)
{
    long fp_len = 0;
    /* get file length */
    fseek(fp, 0, SEEK_END);
    fp_len = ftell(fp);
    rewind(fp);
    /* alloc heap memory */
    bin = (char *)malloc((fp_len+1)*sizeof(char));
    /* copy bytes */
    fread(bin, fp_len, 1, fp);
    fclose(fp);
    return bin;
}

void print_bytes(char* bin, int section)
{
    switch(section)
    {
        case 1: 
            printf("MAGIC: ");
            for (int i = 0; i < 4; i++)
                printf("%c", bin[i]);
            printf("\n");
            break;
        default:
            printf("shitload\n");
            break;
    }
}

void read_elf64_header(FILE *fp, Elf64_Ehdr *elf_header)
{
    lseek(fp, 0, SEEK_SET);
    read(fp, elf_header, sizeof(Elf64_Ehdr));
}

void print_elf64_header(Elf64_Ehdr *elf_header)
{
    printf("ELF 64\n"); 
}

int main(int argc, char *argv[])
{
    /* ptr to actual bytes of exectable and headers*/
    char* bin;
    Elf64_Ehdr *elf_header;

    /* fopen vars */
    const char* mode = "r";
    FILE *fp;

    /* arg parse */
    if (argc >= 2)
        fp = fopen(argv[1], mode);
    else
        fp = fopen("/home/user/shitload/sample_bins/return_zero", mode);

    /* parse ELF64 Header */
    bin = read_bin(fp, bin);
    read_elf64_header(fp, elf_header);
    print_elf64_header(elf_header);

    return 0;
}

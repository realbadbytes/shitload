#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

char* parse_ehdr(FILE *fp, char* bin)
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

void print_bytes(char* bin, int size)
{
    for (int i = 0; i < size; i++)
        printf("<0x%x>\n", bin[i]);
}

int main(int argc, char *argv[])
{
    char* bin;
    /* ELF64 Header */
    Elf64_Ehdr *elf_header = calloc(0, sizeof *elf_header);

    /* fopen vars */
    const char* mode = "r";
    FILE *fp;

    /* arg parse */
    if (argc >= 2)
        fp = fopen(argv[1], mode);
    else
        fp = fopen("/home/user/shitload/sample_bins/return_zero", mode);

    /* parse ELF64 Header */
    bin = parse_ehdr(fp, bin);
    print_bytes(bin, 4);

    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

#define E_HDR 1

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

Elf64_Ehdr *parse_ehdr(char* bin)
{
    Elf64_Ehdr *temp = malloc(sizeof(Elf64_Ehdr));
    /* e_ident struct*/

    /* magic num 0 */
    temp->e_ident[0] = bin[0];
    /* valid: 0x7f */
    if (temp->e_ident[0] != 0x7f) exit(-1);

    /* magic num 1 */
    temp->e_ident[1] = bin[1];
    /* valid: 'E' */
    if (temp->e_ident[0] != 'E') exit(-1);

    /* magic num 2 */
    temp->e_ident[2] = bin[2];
    /* valid: 'L' */
    if (temp->e_ident[0] != 'L') exit(-1);

    /* magic num 0 */
    temp->e_ident[3] = bin[3];
    /* valid: 'F' */
    if (temp->e_ident[0] != 'F') exit(-1);

    /* class */
    temp->e_ident[4] = bin[4];
    /* valid: 0 ELFCLASSNONE
              1 ELFCLASS32
              2 ELFCLASS64
              3 ELFCLASSNUM */
    if (0 < tmp->e_ident[4] > 3) exit(-1);

    /* data */
    temp->e_ident[5] = bin[5];

    /* version */
    temp->e_ident[6] = bin[6];

    /* OS ABI */
    temp->e_ident[7] = bin[7];

    /* ABI version */
    temp->e_ident[8] = bin[8];

    /* padding */
    int i = 9;
    while (i < 16)
    {
        temp->e_ident[i] = 0;
        i++;
    }

    return temp;
}

int main(int argc, char *argv[])
{
    /* ptr to actual bytes of exectable and headers*/
    char* bin;
    Elf64_Ehdr *ehdr;

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
    print_bytes(bin, E_HDR);
    ehdr = parse_ehdr(bin);

    return 0;
}

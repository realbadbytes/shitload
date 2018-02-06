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

Elf64_Ehdr *parse_ehdr(char* bin)
{
    Elf64_Ehdr *temp = malloc(sizeof(Elf64_Ehdr));
    /* e_ident struct*/

    /* magic num 0 */
    temp->e_ident[0] = bin[0];
    /* valid: 0x7f */
    if (temp->e_ident[0] != 0x7f)
    {
        DEBUG_PRINT(("[-] magic num 0 bad\n"));
        exit(-1);
    }

    /* magic num 1 */
    temp->e_ident[1] = bin[1];
    /* valid: 'E' */
    if (temp->e_ident[1] != 0x45)
    {
        DEBUG_PRINT(("[-] magic num 1 bad: 0x%02x\n", temp->e_ident[1]));
        exit(-1);
    }

    /* magic num 2 */
    temp->e_ident[2] = bin[2];
    /* valid: 'L' */
    if (temp->e_ident[0] != 0x4C)
    {
        DEBUG_PRINT(("[-] magic num 1 bad\n"));
        exit(-1);
    }

    /* magic num 3 */
    temp->e_ident[3] = bin[3];
    /* valid: 'F' */
    if (temp->e_ident[0] != 0x46)
    {
        DEBUG_PRINT(("[-] magic num 1 bad\n"));
        exit(-1);
    }

    /* class */
    temp->e_ident[4] = bin[4];
    /* valid: 0 ELFCLASSNONE
              1 ELFCLASS32
              2 ELFCLASS64
              3 ELFCLASSNUM */
    if (temp->e_ident[4] < 0 || temp->e_ident[4] > 3) exit(-1);
    DEBUG_PRINT(("[+] class %d\n", temp->e_ident[4]));

    /* data */
    temp->e_ident[5] = bin[5];
    /* valid: 0 ELFDATANONE
              1 ELFDATA2LSB
              2 ELFDATA2MSB
              3 ELFDATANUM */
    if (temp->e_ident[5] < 0 || temp->e_ident[5] > 3) exit(-1);

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
    ehdr = parse_ehdr(bin);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int label[20];
int no = 0;

// Check if the current line is a label
int check_label(int k) {
    for (int i = 0; i < no; i++) {
        if (k == label[i]) return 1;
    }
    return 0;
}

int main() {
    FILE *fp1, *fp2;
    char fname[20], op[10], ch;
    char operand1[8], operand2[8], result[8];
    int i = 0, j = 0;

    printf("\nEnter filename of the intermediate code: ");
    scanf("%s", fname);

    fp1 = fopen(fname, "r");
    fp2 = fopen("target.txt", "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    while (fscanf(fp1, "%s", op) != EOF) {
        fprintf(fp2, "\n");
        i++;

        if (check_label(i))
            fprintf(fp2, "label#%d:\n", i);

        if (strcmp(op, "print") == 0) {
            fscanf(fp1, "%s", result);
            fprintf(fp2, "\tOUT %s\n", result);
        }
        else if (strcmp(op, "goto") == 0) {
            fscanf(fp1, "%s %s", operand1, operand2);
            fprintf(fp2, "\tJMP %s, label#%s\n", operand1, operand2);
            label[no++] = atoi(operand2);
        }
        else if (strcmp(op, "[]=") == 0) {
            fscanf(fp1, "%s %s %s", operand1, operand2, result);
            fprintf(fp2, "\tSTORE %s[%s], %s\n", operand1, operand2, result);
        }
        else if (strcmp(op, "uminus") == 0) {
            fscanf(fp1, "%s %s", operand1, result);
            fprintf(fp2, "\tLOAD -%s, R1\n", operand1);
            fprintf(fp2, "\tSTORE R1, %s\n", result);
        }
        else {
            switch (op[0]) {
                case '*':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tLOAD %s, R1\n", operand2);
                    fprintf(fp2, "\tMUL R1, R0\n");
                    fprintf(fp2, "\tSTORE R0, %s\n", result);
                    break;

                case '+':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tLOAD %s, R1\n", operand2);
                    fprintf(fp2, "\tADD R1, R0\n");
                    fprintf(fp2, "\tSTORE R0, %s\n", result);
                    break;

                case '-':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tLOAD %s, R1\n", operand2);
                    fprintf(fp2, "\tSUB R1, R0\n");
                    fprintf(fp2, "\tSTORE R0, %s\n", result);
                    break;

                case '/':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tLOAD %s, R1\n", operand2);
                    fprintf(fp2, "\tDIV R1, R0\n");
                    fprintf(fp2, "\tSTORE R0, %s\n", result);
                    break;

                case '%':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tLOAD %s, R1\n", operand2);
                    fprintf(fp2, "\tMOD R1, R0\n");
                    fprintf(fp2, "\tSTORE R0, %s\n", result);
                    break;

                case '=':
                    fscanf(fp1, "%s %s", operand1, result);
                    fprintf(fp2, "\tSTORE %s, %s\n", operand1, result);
                    break;

                case '>':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tJGT %s, label#%s\n", operand2, result);
                    label[no++] = atoi(result);
                    break;

                case '<':
                    fscanf(fp1, "%s %s %s", operand1, operand2, result);
                    fprintf(fp2, "\tLOAD %s, R0\n", operand1);
                    fprintf(fp2, "\tJLT %s, label#%s\n", operand2, result);
                    label[no++] = atoi(result);
                    break;
            }
        }
    }

    fclose(fp1);
    fclose(fp2);

    // Display output file
    fp2 = fopen("target.txt", "r");
    if (fp2 == NULL) {
        printf("Error opening target.txt\n");
        return 1;
    }

    printf("\nGenerated Target Code:\n");
    while ((ch = fgetc(fp2)) != EOF) {
        putchar(ch);
    }

    fclose(fp2);
    return 0;
}

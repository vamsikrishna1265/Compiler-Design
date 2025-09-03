#include <stdio.h>
#include <string.h>

int main() {
    char gram[50], part1[25], part2[25];
    char modifiedGram[25], newGram[25];
    int i, j = 0, k = 0, l = 0, pos = 0;

    printf("Enter Production (Format: A->abc|abd): ");
    fgets(gram, sizeof(gram), stdin);

    // Remove newline if any
    gram[strcspn(gram, "\n")] = 0;

    // Extract left and right parts
    for (i = 3; gram[i] != '|'; i++, j++)
        part1[j] = gram[i];
    part1[j] = '\0';

    for (j = ++i, i = 0; gram[j] != '\0'; j++, i++)
        part2[i] = gram[j];
    part2[i] = '\0';

    // Find common prefix
    for (i = 0; i < strlen(part1) && i < strlen(part2); i++) {
        if (part1[i] == part2[i]) {
            modifiedGram[k++] = part1[i];
            pos = i + 1;
        } else {
            break;
        }
    }

    // Remaining part after factoring
    modifiedGram[k] = 'X';
    modifiedGram[++k] = '\0';

    // Fill new productions for X
    for (i = pos, j = 0; part1[i] != '\0'; i++, j++)
        newGram[j] = part1[i];
    newGram[j++] = '|';
    for (i = pos; part2[i] != '\0'; i++, j++)
        newGram[j] = part2[i];
    newGram[j] = '\0';

    // Display results
    printf("\nAfter Left Factoring:\n");
    printf("A -> %s\n", modifiedGram);
    printf("X -> %s\n", newGram);

    return 0;
}

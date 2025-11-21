#include <stdio.h>

int main()
{
    int array[] = {1, 2, 3, 4, 5};
    int sum = 0;

    // Calculer la somme des éléments du tableau
    for (int i = 0; i < 5; ++i) { // Correction : i < 5 au lieu de i <= 5
        sum += array[i];
    }

    printf("La somme des éléments du tableau est : %d\n", sum);

    return 0;
}

#include <stdio.h>

// Version récursive corrigée avec condition d'arrêt correcte
unsigned long long fibonacci(unsigned long long n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void)
{
    unsigned long long n = 50; // Valeur de n choisie

    printf("Calcul du nombre de Fibonacci pour n = %llu\n", n);
    printf("Le résultat est : %llu\n", fibonacci(n));

    return 0;
}

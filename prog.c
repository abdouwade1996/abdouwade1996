#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
    sizeof(<donnee>) : retourne la taille en octets d'une donnee
    malloc(<taille_en_octets) : allouer dynamiquement 
    free(donnee_allouee) : libère la mémoire alouée dynamiquement

    calloc(<donnee>, <taille_en_octets>) : alloue et initialise tout a 0

    realloc(<donnee>, <nouvelle_taille>) : réalloue un espace mémoire
*/

int main()
{
    int playerNumber = 0;
    int *list_player = NULL;

    printf("Combien de joueurs ? ");
    scanf("%d", &playerNumber);

    list_player = malloc(sizeof(int)*playerNumber);

    if(list_player == NULL)
        exit(1);
    for(int i = 0; i<playerNumber; i++)
    {
        printf("Player %d -> number %d\n", i, i*5);
        list_player[i] = i*5;
    }
    for(int i=0;i<playerNumber; i++)
    {
        printf("Player[%d] ", list_player[i]);
    }

    free(list_player);

    return 0;
}
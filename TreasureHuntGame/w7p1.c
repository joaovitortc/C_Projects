#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAXPATHLENGTH 70
#define MINPATHLENGTH 10

struct PlayerInfo
{
    int NumLives;
    char symbol;
    int NumTreasures;
    int positions[MAXPATHLENGTH];

};

struct GameInfo
{
    int maxMoves;
    int PathLength;
    int Bombs[MAXPATHLENGTH];
    int Treasures[MAXPATHLENGTH];

};



int main(void)
{
    struct PlayerInfo Player;
    struct GameInfo Game;
    int i;



    printf("================================\n");
    printf("         Treasure Hunt!\n");
    printf("================================\n\n");

    printf("PLAYER Configuration\n");
    printf("--------------------\n");
    printf("Enter a single character to represent the player: ");
    scanf(" %c", &Player.symbol);
    
    do {
        printf("Set the number of lives: ");
        scanf(" %d", &Player.NumLives);

            if (Player.NumLives < 1 || Player.NumLives > 10)
                printf("     Must be between 1 and 10!\n");

    } while (Player.NumLives < 1 || Player.NumLives > 10);
    printf("Player configuration set-up is complete\n\n");

    printf("GAME Configuration\n");
    printf("------------------\n");
    
    do {
        printf("Set the path length (a multiple of 5 between 10-70): ");
        scanf("%d", &Game.PathLength);

        if ((Game.PathLength % 5 != 0) || Game.PathLength < 10 || Game.PathLength > 70)
            printf("     Must be a multiple of 5 and between 10-70!!!\n");

    } while ((Game.PathLength % 5 != 0) || Game.PathLength < 10 || Game.PathLength > 70);

    do {
        printf("Set the limit for number of moves allowed: ");
        scanf("%d", &Game.maxMoves);

        if (Game.maxMoves < 3 || Game.maxMoves > 26)
            printf("    Value must be between 3 and 26\n");

    } while (Game.maxMoves < 3 || Game.maxMoves > 26);
    
    printf("\nBOMB Placement\n");
    printf("--------------\n");
    printf("Enter the bomb positions in sets of 5 where a value\n");
    printf("of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n");
    printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", Game.PathLength);

    for (i = 5; i <= Game.PathLength; i += 5) {
        printf("   Positions [%2d-%2d]: ", i - 4, i);
        scanf(" %d %d %d %d %d", &Game.Bombs[i - 5], &Game.Bombs[i - 4], &Game.Bombs[i - 3], &Game.Bombs[i - 2], &Game.Bombs[i - 1]);
    }
    printf("BOMB placement set\n\n");

    printf("TREASURE Placement\n");
    printf("------------------\n");
    printf("Enter the treasure placements in sets of 5 where a value\n");
    printf("of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n");
    printf("(Example: 1 0 0 1 1) NOTE: there are %d to set!\n", Game.PathLength);

    for (i = 5; i <= Game.PathLength; i += 5) {
        printf("   Positions [%2d-%2d]: ", i - 4, i);
        scanf(" %d %d %d %d %d", &Game.Treasures[i - 5], &Game.Treasures[i - 4], &Game.Treasures[i - 3], &Game.Treasures[i - 2], &Game.Treasures[i - 1]);
    }
    printf("TREASURE placement set\n\n");
    printf("GAME configuration set-up is complete...\n\n");

    printf("------------------------------------\n");
    printf("TREASURE HUNT Configuration Settings\n");
    printf("------------------------------------\n");
    printf("Player:\n");
    printf("   Symbol     : %c\n", Player.symbol);
    printf("   Lives      : %d\n", Player.NumLives);
    printf("   Treasure   : [ready for gameplay]\n");
    printf("   History    : [ready for gameplay]\n");
    printf("\nGame:\n");
    printf("   Path Length: %d\n", Game.PathLength);
    printf("   Bombs      : ");
    for (i = 0; i < Game.PathLength; i++) printf("%d", Game.Bombs[i]);
    printf("\n");
    printf("   Treasure   : ");
    for (i = 0; i < Game.PathLength; i++) printf("%d", Game.Treasures[i]);
    printf("\n\n");

    printf("====================================\n~ Get ready to play TREASURE HUNT! ~\n====================================\n");

    return 0;
}

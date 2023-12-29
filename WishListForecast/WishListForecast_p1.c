#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MIN_NET 500
#define MAX_NET 400000
#define MAX_ITEMS 10

int main(void)
{
    double monthly_net;
    int n_items, item = 1, i;
    double totalCost = 0;
    
    // parallel arrays
    double cost[MAX_ITEMS];
    int priority[MAX_ITEMS];
    char finance[MAX_ITEMS];

    cost[0] = 0;
    priority[0] = 0;
    finance[0] = '\0';



    printf("+--------------------------+\n");
    printf("+   Wish List Forecaster   |\n");
    printf("+--------------------------+\n\n");

    do {
        printf("Enter your monthly NET income: $");
        scanf(" %lf", &monthly_net);

            if (monthly_net < MIN_NET)
                printf("ERROR: You must have a consistent monthly income of at least $500.00\n\n");
            else if (monthly_net > MAX_NET)
                printf("ERROR: Liar! I'll believe you if you enter a value no more than $400000.00\n\n");

    } while (monthly_net < MIN_NET || monthly_net > MAX_NET);

    printf("\n");

    do {
        printf("How many wish list items do you want to forecast?: ");
        scanf(" %d", &n_items);

        if (n_items >= MAX_ITEMS || n_items <= 1)
            printf("ERROR: List is restricted to between 1 and 10 items.\n\n");

    } while (n_items >= MAX_ITEMS || n_items <= 1);

    do {
    printf("\n");
    printf("Item-%d Details:\n", item);

        do {
            printf("   Item cost: $");
            scanf(" %lf", &cost[item]);

            if (cost[item] < 100)
                printf("      ERROR: Cost must be at least $100.00\n");

        } while (cost[item] < 100);

        do {
            printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
            scanf(" %d", &priority[item]);

            if (priority[item] < 1 || priority[item] > 3)
                printf("      ERROR: Value must be between 1 and 3\n");

        } while (priority[item] < 1 || priority[item] > 3);

        do {
            printf("   Does this item have financing options? [y/n]: ");
            scanf(" %c", &finance[item]);

            if (finance[item] != 'y' && finance[item] != 'n')
                printf("      ERROR: Must be a lowercase 'y' or 'n'\n");

        } while (finance[item] != 'y' && finance[item] != 'n');

        item++;
    } while (item <= n_items);

    item = 1; //Resetting the flag "item" to 1 - lets reuse it.
    
    printf("\n");
    printf("Item Priority Financed        Cost\n");
    printf("---- -------- -------- -----------\n");

    do {
        printf("%3d %6d %8c %14.2lf\n", item, priority[item], finance[item], cost[item]);
        ++item;
    } while (item <= n_items);

    printf("---- -------- -------- -----------\n");

    for (i = 0; i <= n_items; i++)
        totalCost += cost[i];

    printf("                      $%11.2lf\n\n", totalCost);

    printf("Best of luck in all your future endeavours!\n");

    return 0;
}
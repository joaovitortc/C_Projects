#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MIN_NET 500
#define MAX_NET 400000
#define MAX_ITEMS 10

int main(void)
{
    int n_items, item = 1, i, selection, filter = 0, years, months;
    double monthly_net, totalCost = 0, amount = 0;  

    //flags
    int yes = 0, selectionValid = 0, FilterValid = 0;
    
    // parallel arrays
    double cost[MAX_ITEMS];
    int priority[MAX_ITEMS];
    char finance[MAX_ITEMS];

    //for constancy sake, setting the first index of the array to 0 is done. There will be no Item-0.
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

    // Part-2

    do {

        //getting a valid selection
        do {
            printf("How do you want to forecast your wish list?\n");
            printf(" 1. All items (no filter)\n");
            printf(" 2. By priority\n");
            printf(" 0. Quit/Exit\n");
            printf("Selection: ");
            scanf(" %d", &selection);
            printf("\n");

            if (selection != 0 && selection != 1 && selection != 2)
                printf("ERROR: Invalid menu selection.\n\n");
            else
                selectionValid = 1;

        } while (selectionValid != 1);

        //getting a valid filter IF selection is 2.
        do {
           
            if (selection == 2) {
                printf("What priority do you want to filter by? [1-3]: ");
                scanf(" %d", &filter);

                if (filter < 1 || filter > 3)
                    printf("INVALID FILTER");
                else
                    FilterValid = 1;
            }
            else
                FilterValid = 1;

        } while (FilterValid != 1);

        // Output for selection 1
        if (selection == 1) {
            printf("====================================================\n");
            printf("Filter:");
            printf("   All items\n");
            printf("Amount:   $");
            printf("%.2lf\n", totalCost);

                years = (int)(totalCost / (monthly_net * 12));
                months = (int)((totalCost / monthly_net) - (years * 12));
                
                if (((int)(totalCost / monthly_net) % 12) > 0.5)
                months += 1;
           
            printf("Forecast:");
            printf(" %d years, %d months\n", years, months);

            for (i = 0; i <= n_items; i++)
                if (finance[i] == 'y')
                    yes = 1;
            if (yes == 1) {
                printf("NOTE: Financing options are available on some items.\n");
                printf("      You can likely reduce the estimated months.\n");
            }
            yes = 0; //resetting flag
            
            printf("====================================================\n\n"); 

        } // output for selection 2
        else if (selection == 2) {
            printf("\n====================================================\n");
            printf("Filter:");
            printf("   by priority (%d)\n", filter);

            for (i = 0; i <= n_items; i++)
                if (priority[i] == filter)
                    amount += cost[i];
            printf("Amount:   $");
            printf("%.2lf\n", amount);

            years = (int)(amount / (monthly_net * 12));
            months = (int)((amount / monthly_net) - (years * 12));
            if (((int)(amount / monthly_net) % 12) > 0.5);
            months += 1;
            printf("Forecast:");
            printf(" %d years, %d months\n", years, months);

            for (i = 0; i <= n_items; i++)
                if (finance[i] == 'y' && priority[i] == filter)
                    yes = 1;
            if (yes == 1) {
                printf("NOTE: Financing options are available on some items.\n");
                printf("      You can likely reduce the estimated months.\n");
            }
            yes = 0; //resetting flag

            printf("====================================================\n\n");
        }
                    
        amount = 0; //resetting variable that is used differently each iteration.

    } while (selection != 0);

    printf("Best of luck in all your future endeavours!\n");

    return 0;
}
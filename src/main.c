# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "portfolio.h"

static void clean_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    Stock *portfolio = NULL;
    int stock_count = 0;
    int capacity = 0;

    short choice;
    do {
        printf("Stock Portfolio Management\n");
        printf("Menu:\n");
        printf("1. Add Stock\n");
        printf("2. Remove Stock\n");
        printf("3. Display Portfolio\n");
        printf("4. Calculate Total Value\n");
        printf("5. Modify stock\n");
        printf("6. Exit\n");
        printf("Enter your choice: \n");
        scanf("%hd", &choice);

        switch (choice) {
            case 1:
                add_stock(&portfolio, &stock_count, &capacity);
                break;
            case 2:
                remove_stock(&portfolio, &stock_count);
                break;
            case 3:
                display_portfolio(portfolio, stock_count);
                break;
            case 4: {
                double total_value = calculate_total_value(portfolio, stock_count);
                printf("Total Portfolio Value: $%.2f\n", total_value);
                break;
            }
            case 5:
                modify_stock(portfolio, stock_count, NULL);
                break;
            case 6:
                free_portfolio(&portfolio);
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                clean_input_buffer();
                break;
        };
    } while (choice != 6);

    free(portfolio);
    portfolio = NULL;

    return 0;
}
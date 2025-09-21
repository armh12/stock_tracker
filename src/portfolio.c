#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>
#include "portfolio.h"  


static int get_stock_index(Stock *portfolio, int count, const char *ticker) {
    for (int i = 0; i < count; i++) {
        if (strcmp(portfolio[i].ticker, ticker) == 0) {
            return i;
        }
    }
    return -1;
}


void add_stock(Stock **portfolio, int *count, int *capacity) {
    int current_count = *count;
    int current_capacity = *capacity;

    if (current_count >= current_capacity) {
        int new_capacity = (current_capacity == 0) ? 1 : current_capacity * 2;
        Stock *new_portfolio_ptr = realloc(*portfolio, sizeof(Stock) * new_capacity);
        if (new_portfolio_ptr == NULL) {
            perror("Failed to reallocate memory");
            return;
        }
        *portfolio = new_portfolio_ptr;
        *capacity = new_capacity; 
    }

    printf("Please enter stock data\n");
    printf("Enter ticker name: \n");
    char ticker[10];
    scanf("%9s", ticker);
    // check if ticker already exist and suggest to make changes in portfolio
    int ticker_index = get_stock_index(*portfolio, *count, ticker);

    if (ticker_index == -1) {
        strcpy((*portfolio)[*count].ticker, ticker);
        printf("Enter quantity of stocks: \n");
        scanf("%i", &(*portfolio)[*count].quantity);
        printf("Enter single price of stock: \n");
        scanf("%lf", &(*portfolio)[*count].price);
        printf("Stock set successfully\n");
        (*count)++;
        return;
    }

    printf("Stock %s is existing in your portfolio, do you want to modify data?\n", ticker);
    printf("1. Modify\n");
    printf("2. Exit\n");
    printf("Enter your choice: \n");

    short choice;
    scanf(" %hd", &choice);
    switch (choice) {
        case 1:
            modify_stock(*portfolio, *count, ticker);
            break;
        case 2:
            return;
    }
}

void modify_stock(Stock *portfolio, int count, const char *ticker_to_change) {
    if (count == 0) {
        printf("Portfolio is empty, nothing to modify.\n");
        return;
    }

    char ticker[10];
    if (!ticker_to_change) {
        printf("Enter ticker to modify: \n");
        scanf("%9s", ticker);
    }
    else {
        strcpy(ticker, ticker_to_change);
    }
    int ticker_index = get_stock_index(portfolio, count, ticker);

    if (ticker_index == -1) {
        printf("Ticker does not exist in portfolio, nothing to modify.\n");
        return;
    }

    short choice;
    do {
        printf("What do you want to change in stock %s?\n", ticker);
        printf("1. Change quantity.\n");
        printf("2. Change price.\n");
        printf("3. Finish changes.\n");
        scanf(" %hd", &choice);

        switch (choice) {
            case 1:
                printf("Enter new quantity: \n");
                scanf("%i", &portfolio[ticker_index].quantity);
                break;
            case 2:
                printf("Enter new price: \n");
                scanf("%lf", &portfolio[ticker_index].price);
                break;
            case 3:
                return;
        } 
    } while (choice != 3);
}


void remove_stock(Stock **portfolio, int *count) {
    int current_count = *count;
    if (current_count == 0) {
        printf("Portfolio ie empty, nothing to remove.\n");
        return;
    }

    printf("Enter the ticker symbol of the stock to remove: \n");
    char ticker[10];
    scanf("%9s", ticker);

    Stock *current_portfolio = *portfolio;
    int found_index = get_stock_index(current_portfolio, current_count, ticker);

    for (int i = found_index; i < current_count - 1; i++) {
        current_portfolio[i] = current_portfolio[i + 1];
    }
    (*count)--;
    printf("Stock %s removed from portfolio.\n", ticker);
    // re-allocate memory
    Stock *new_alloc_ptr = realloc(*portfolio, sizeof(Stock) * *count);
    if (new_alloc_ptr == NULL) {
        printf("Failed to resize the portfolio");
        return;
    } 
    *portfolio = new_alloc_ptr;
}  


void display_portfolio(const Stock *portfolio, int count) {
    printf("--- Your Portfolio (%d stocks) ---\n", count);

    if (count == 0) {
        printf("Portfolio is empty.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Stock %d\n", i + 1);
        printf("\tTicker name - %s\n", portfolio[i].ticker);
        int quantity = portfolio[i].quantity;
        printf("\tStock quantity - %d\n", quantity);
        double single_stock_price = portfolio[i].price;
        printf("\tSingle stock price - %lf\n", single_stock_price);
        printf("\tOverall stocks price - %lf\n", single_stock_price * quantity);
    }
}

void free_portfolio(Stock **portfolio) {
    if (portfolio != NULL && *portfolio != NULL) {
        free(*portfolio);
        *portfolio = NULL;
    }
}


double calculate_total_value(const Stock *portfolio, int count) {
    double total_value = 0.0;
    for (int i = 0; i < count; i++) {
        total_value += portfolio[i].price * portfolio[i].quantity;
    }
    return total_value;
}
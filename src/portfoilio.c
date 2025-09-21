#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>
#include "portfolio.h"  

void add_stock(Stock **portfolio, int *count, int *capacity) {
    int current_count = *count;
    int current_capacity = *capacity;

    if (current_count >= current_capacity) {
        int new_capacity = (current_capacity == 0) ? 1 : current_capacity * 2;
        Stock *new_portfolio_ptr = realloc(*portfolio, sizeof(Stock) * new_capacity);
        *portfolio = new_portfolio_ptr;
        *capacity = new_capacity; 
    }

    Stock *current_portfolio = *portfolio;

    printf("Please enter stock data\n");
    printf("Enter ticker name: \n");
    scanf("%9s", current_portfolio[current_count].ticker);
    printf("Enter quantity of stocks: \n");
    scanf("%i", &current_portfolio[current_count].quantity);
    printf("Enter single price of stock: \n");
    scanf("%lf", &current_portfolio[current_count].price);
    printf("Stock set successfully");
}


void remove_stock(Stock **portfolio, int *count) {
    int current_count = *count;
    if (current_count == 0) {
        printf("Portfolio ie empty, nothing to remove.\n");
        return;
    }

    printf("Enter the ticker symbol of the stock to remove: ");
    char ticker[10];
    scanf("%9s", ticker);

    Stock *current_portfolio = *portfolio;
    int found_index = -1;

    for (int i = 0; i < current_count; i++) {
        if (strcmp(current_portfolio[current_count].ticker, ticker) == 0) {
            found_index = i;
            break;
        }
    }

    for (int i = found_index; i < current_count - 1; i++) {
        current_portfolio[i] = current_portfolio[i + 1];
    }
    (*count)--;
    // re-allocate memory
    Stock *new_alloc_ptr = realloc(*portfolio, sizeof(Stock) * *count);
    *portfolio = new_alloc_ptr;
}  

void display_portfolio(const Stock *portfolio, int count) {
    int portfolio_size = sizeof(*portfolio) / 
    printf("--- Your Portfolio (%d stocks) ---\n", count);

    if (count == 0) {
        printf("Portfolio is empty.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Stock %d\n", i + 1);
        printf("\tTicker name - %s", portfolio[i].ticker);
        int quantity = portfolio[i].quantity;
        printf("\tStock quantity - %d\n", quantity);
        double single_stock_price = portfolio[i].price;
        printf("\tSingle stock price - %lf", single_stock_price);
        printf("\tOverall stocks price - %lf", single_stock_price * quantity);
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
        total_value += portfolio[i].price;
    }
    return total_value;
}
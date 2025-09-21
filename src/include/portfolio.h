# ifndef PORTFOLIO_H
# define PORTFOLIO_H

typedef struct {
    char ticker[10];
    int quantity;
    double price;
} Stock;

void add_stock(Stock **portfolio, int *count, int *capacity);
void remove_stock(Stock **portfolio, int *count);
void modify_stock(Stock *portfolio, int count, const char *ticker_to_change);
void display_portfolio(const Stock *portfolio, int count);
void free_portfolio(Stock **portfolio);
double calculate_total_value(const Stock *portfolio, int count);
# endif
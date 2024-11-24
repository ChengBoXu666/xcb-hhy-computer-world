#include "onecard.h"

Table initial_table(Card *card_fetch, Card *card_discard, Tran trans, Result result, FILE *file) // initial the structure of table's information
{
    Table table;
    table.current = malloc(sizeof(Card));
    if (table.current == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fprintf(file, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    table.attack = 0;
    table.direction = 1;
    table.index1 = trans.t1;
    table.index2 = trans.t2;
    while (1)
    {
        table.current->rank = card_fetch[table.index1].rank;
        table.current->suit = card_fetch[table.index1].suit;
        card_discard[table.index2] = card_fetch[table.index1];
        table.index1++;
        table.index2++;
        if (judge(table.current->rank) == 1)
            break;
    }
    printf("First card: ");
    fprintf(file, "First card: ");
    card_output(table.current->suit, table.current->rank, file);
    printf("\n\n");
    fprintf(file, "\n\n");
    if (result.demo_mode == 0)
        sleep(1);
    return table;
}

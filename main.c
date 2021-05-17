#include <stdio.h>
#include "xsnos.h"

void print_game(struct xsnos *game)
{
    unsigned int i;

    printf("[%c] ", verify_board(game));
    for (i = 0; i < game->size; i++)
        if (game->order[i] > 0)
        {
            printf("%d%c ", game->order[i], game->state[game->order[i] - 1]);
        }
    printf("\n");
    printf("%c %c %c\n"
           "%c %c %c\n"
           "%c %c %c\n", game->state[0], game->state[1], game->state[2],
                         game->state[3], game->state[4], game->state[5],
                         game->state[6], game->state[7], game->state[8]);
    printf("\n");
}

int main(int argc, char** argv)
{
    struct xsnos game;

    xsnos_init(&game);
    explore(&game, 0, &print_game);
    xsnos_clear(&game);

    return 0;
}

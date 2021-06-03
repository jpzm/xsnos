#include <stdio.h>
#include "xsnos.h"

void print_game(struct xsnos *game)
{
    unsigned int i;

    printf("[%c] ", xsnos_verify(game));
    for (i = 0; i < game->size; i++)
        if (game->order[i] < game->size)
        {
            printf("%u%c ", game->order[i], game->state[game->order[i]]);
        }
    printf("\n");
    printf(" %c %c %c\n"
           " %c %c %c\n"
           " %c %c %c\n", game->state[0], game->state[1], game->state[2],
                          game->state[3], game->state[4], game->state[5],
                          game->state[6], game->state[7], game->state[8]);
}

void print_status(struct xsnos *game)
{
    unsigned int i;
    float sum;

    for (i = 0; i < game->size; i++)
    {
        if (game->state[i] == EMPTY)
        {
            if (game->player == CROSS)
                sum = (10 * (float) game->winx[i] - 1000 * (int) game->wino[i]);
            else
                sum = (10 * (float) game->wino[i] - 1000 * (int) game->winx[i]);
            printf("%u [%f]: %u %u %u\n", i, sum,
                                            game->winx[i],
                                            game->wino[i],
                                            game->draw[i]);
        }
    }
}

int main(int argc, char** argv)
{
    struct xsnos game;

    xsnos_init(&game);

    /* TEST AN SPECIFFIC STATE
    unsigned int i;
    char state[] = {'o', '_', 'x',
                    '_', 'x', '_',
                    '_', '_', '_'};
    for (i = 0; i < game.size; i++)
        game.state[i] = state[i];

    game.player = ROUND;
    printf("Best %d.\n", xsnos_explore_move(&game));
    print_status(&game);
    print_game(&game);
    */

    // TEST USING THE MAX NUMBER OF WINS APPROACH
    int best;
    while (xsnos_verify(&game) == EMPTY)
    {
        best = xsnos_minimax_move(&game);
        printf("Best %d%c.\n", best, game.player);
        game.state[best] = game.player;
        print_game(&game);
        game.player = CHANGE_PLAYER(game.player);
    }

    /* TEST MINIMAX ALGORITHM
    unsigned int i;
    char state[] = {'_', '_', '_',
                    '_', '_', '_',
                    '_', '_', '_'};
    for (i = 0; i < game.size; i++)
        game.state[i] = state[i];
    //game.player = ROUND;
    printf("%d\n", xsnos_minimax_move(&game));
    */

    xsnos_clear(&game);

    return 0;
}

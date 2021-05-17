#include "xsnos.h"

void xsnos_init(struct xsnos *game)
{
    unsigned int i;

    game->size = BOARD_SIZE;
    game->order = (unsigned int *) malloc(game->size * sizeof(unsigned int));
    game->state = (char *) malloc(game->size * sizeof(char));

    for (i = 0; i < game->size; i++)
    {
        game->order[i] = 0;
        game->state[i] = EMPTY;
    }

    game->player = CROSS;
}

void xsnos_clear(struct xsnos *game)
{
    free(game->order);
    free(game->state);
}

char verify_board(struct xsnos *game)
{
    char *state = game->state;

    if (state[0] != EMPTY)
    {
        if (state[0] == state[1] && state[1] == state[2])
            return state[0];
        if (state[0] == state[3] && state[3] == state[6])
            return state[0];
    }

    if (state[4] != EMPTY)
    {
        if (state[0] == state[4] && state[4] == state[8])
            return state[0];
        if (state[3] == state[4] && state[4] == state[5])
            return state[3];
        if (state[1] == state[4] && state[4] == state[7])
            return state[1];
        if (state[2] == state[4] && state[4] == state[6])
            return state[2];
    }

    if (state[8] != EMPTY)
    {
        if (state[6] == state[7] && state[7] == state[8])
            return state[6];
        if (state[2] == state[5] && state[5] == state[8])
            return state[2];
    }

    return EMPTY;
}

void explore(struct xsnos *game,
             unsigned int count,
             void (*callback)(struct xsnos *))
{
    unsigned int i;
    char result, draw;

    result = verify_board(game);
    draw = 1;

    if (result == EMPTY)
    {
        for (i = 0; i < BOARD_SIZE; i++)
        {
            if (game->state[i] == EMPTY)
            {
                draw = 0;
                game->state[i] = game->player;
                game->order[count] = i + 1;
                game->player = CHANGE_PLAYER(game->player);
                explore(game, count + 1, callback);
                game->state[i] = EMPTY;
                game->order[count] = 0;
                game->player = CHANGE_PLAYER(game->player);
            }
        }

        if (draw)
        {
            callback(game);
        }
    }
    else
    {
        callback(game);
    }
}


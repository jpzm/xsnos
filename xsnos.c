#include "xsnos.h"

void xsnos_init(struct xsnos *game)
{
    unsigned int i;

    game->size = BOARD_SIZE;
    game->winx = (unsigned int *) malloc(game->size * sizeof(unsigned int));
    game->draw = (unsigned int *) malloc(game->size * sizeof(unsigned int));
    game->wino = (unsigned int *) malloc(game->size * sizeof(unsigned int));
    game->order = (unsigned int *) malloc(game->size * sizeof(unsigned int));
    game->state = (char *) malloc(game->size * sizeof(char));

    for (i = 0; i < game->size; i++)
    {
        game->winx[i] = 0;
        game->draw[i] = 0;
        game->wino[i] = 0;
        game->order[i] = game->size;
        game->state[i] = EMPTY;
    }

    game->player = CROSS;
}

void xsnos_clear(struct xsnos *game)
{
    free(game->winx);
    free(game->draw);
    free(game->wino);
    free(game->order);
    free(game->state);
}

char xsnos_verify(struct xsnos *game)
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

    if (state[0] != EMPTY && state[1] != EMPTY && state[2] != EMPTY &&
        state[3] != EMPTY && state[4] != EMPTY && state[5] != EMPTY &&
        state[6] != EMPTY && state[7] != EMPTY && state[8] != EMPTY)
        return DRAW;

    return EMPTY;
}

void xsnos_explore(struct xsnos *game,
                   unsigned int count,
                   void (*callback)(struct xsnos *))
{
    unsigned int i;
    char result;

    result = xsnos_verify(game);

    if (count == 0)
    {
        for (i = 0; i < game->size; i++)
        {
            game->winx[i] = 0;
            game->draw[i] = 0;
            game->wino[i] = 0;
            game->order[i] = game->size;
        }
    }

    if (result == EMPTY)
    {
        for (i = 0; i < game->size; i++)
        {
            if (game->state[i] == EMPTY)
            {
                game->state[i] = game->player;
                game->order[count] = i;
                game->player = CHANGE_PLAYER(game->player);
                xsnos_explore(game, count + 1, callback);
                game->state[i] = EMPTY;
                game->order[count] = game->size;
                game->player = CHANGE_PLAYER(game->player);
            }
        }
    }
    else
    {
        if (result == CROSS)
            game->winx[game->order[0]]++;
        else if (result == ROUND)
            game->wino[game->order[0]]++;
        else
            game->draw[game->order[0]]++;
        
        if (callback)
            callback(game);
    }
}

int xsnos_minimax(struct xsnos *game, char player)
{
    unsigned int i;
    char result;
    int value, best;

    result = xsnos_verify(game);

    if (result == EMPTY)
    {
        best = (player == game->player) ? -INT_MAX : INT_MAX;

        for (i = 0; i < game->size; i++)
        {
            if (game->state[i] == EMPTY)
            {
                game->state[i] = game->player;
                game->player = CHANGE_PLAYER(game->player);
                value = xsnos_minimax(game, player);
                game->state[i] = EMPTY;
                game->player = CHANGE_PLAYER(game->player);

                if (player == game->player)
                {
                    if (best < value)
                        best = value;
                }
                else
                {
                    if (best > value)
                        best = value;
                }
            }
        }

        return best;
    }
    else
    {
        if (result == player)
            return 1;
        if (result == DRAW)
            return 0;
        return -1;
    }
}

int xsnos_minimax_move(struct xsnos *game)
{
    unsigned int i;
    float best, value;
    int move = -1;

    best = -INT_MAX;
    for (i = 0; i < game->size; i++)
    {
        if (game->state[i] == EMPTY)
        {
            game->state[i] = game->player;
            game->player = CHANGE_PLAYER(game->player);
            value = xsnos_minimax(game, CHANGE_PLAYER(game->player));
            game->state[i] = EMPTY;
            game->player = CHANGE_PLAYER(game->player);

            if (best < value)
            {
                move = i;
                best = value;
            }
        }
    }

    return move;
}

int xsnos_explore_move(struct xsnos *game)
{
    unsigned int i;
    float sum, best = 0.0;
    int move = -1;

    xsnos_explore(game, 0, NULL);

    for (i = 0; i < game->size; i++)
    {
        if (game->state[i] == EMPTY)
        {
            sum = (game->player == CROSS) ? game->winx[i] : game->wino[i];

            if (move == -1 || best < sum)
            {
                move = i;
                best = sum;
            }
        }
    }

    return move;
}

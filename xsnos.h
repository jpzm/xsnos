#ifndef XSNOS_H
#define XSNOS_H

#include <stdlib.h>

#define CROSS 'x'
#define ROUND 'o'
#define EMPTY ' '

#define CHANGE_PLAYER(PLAYER) ((PLAYER == CROSS) ? ROUND : CROSS)

#define BOARD_SIZE (3 * 3)

struct xsnos
{
    unsigned int size, *order;
    char *state;
    char player;
};

/*
 *
 */
void xsnos_init(struct xsnos *);

/*
 *
 */
void xsnos_clear(struct xsnos *);

/*
 *
 */
char verify_board(struct xsnos *);

/*
 *
 */
void explore(struct xsnos *, unsigned int, void (*f)(struct xsnos *));

#endif

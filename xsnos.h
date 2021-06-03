#ifndef XSNOS_H
#define XSNOS_H

#include <stdlib.h>
#include <limits.h>

#define CROSS 'x'
#define ROUND 'o'
#define EMPTY '_'
#define DRAW 'D'

#define CHANGE_PLAYER(PLAYER) ((PLAYER == CROSS) ? ROUND : CROSS)

#define BOARD_SIZE (3 * 3)

struct xsnos
{
    unsigned int size, *order, *winx, *draw, *wino;
    char *state;
    char player;
};

struct xsnos_move
{
    unsigned int index;
    float value;
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
char xsnos_verify(struct xsnos *);

/*
 *
 */
void xsnos_explore(struct xsnos *, unsigned int, void (*f)(struct xsnos *));

/*
 *
 */
int xsnos_minimax(struct xsnos *, char);

/*
 *
 */
int xsnos_explore_move(struct xsnos *);

/*
 *
 */
int xsnos_minimax_move(struct xsnos *);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:20:14 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/31 15:09:31 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	rng_next(t_context *ctx)
{
	long long	tmp;
	int			a;
	int			b;

	a = 1103515245;
	b = 12345;
	tmp = (long long)ctx->rng.seed * a + b;
	if (tmp < INT_MIN || tmp > INT_MAX)
		error_exit("rng_next: seed overflow detected");
	ctx->rng.seed = (int)tmp;
	return (ctx->rng.seed);
}

int	count_enemies(t_context *ctx)
{
	int	y;
	int	x;
	int	cnt;

	y = 0;
	cnt = 0;
	while (y < ctx->map->height)
	{
		x = 0;
		while (x < ctx->map->width)
		{
			if (ctx->map->date[y][x] == 'X')
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

void	fill_enemies(t_context *ctx)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (y < ctx->map->height)
	{
		x = 0;
		while (x < ctx->map->width)
		{
			if (ctx->map->date[y][x] == 'X')
			{
				ctx->enemies[i].x = x;
				ctx->enemies[i].y = y;
				ctx->map->date[y][x] = '0';
				i++;
			}
			x++;
		}
		y++;
	}
}

void	move_one_enemy(t_context *ctx, int idx)
{
	int	r;
	int	dir;
	int	nx;
	int	ny;

	r = rng_next(ctx);
	dir = (r >> 16) & 3;
	nx = ctx->enemies[idx].x + (dir == 0) - (dir == 1);
	ny = ctx->enemies[idx].y + (dir == 2) - (dir == 3);
	if (ctx->map->date[ny][nx] == 'P')
	{
		handle_end(ctx, "textures/game_over.xpm", "Game Over");
		return ;
	}
	else if (ctx->map->date[ny][nx] == '0')
	{
		mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->tx->floor,
			(ctx->enemies[idx].x * ctx->tx->tile_w), (ctx->enemies[idx].y
				* ctx->tx->tile_h));
		ctx->enemies[idx].x = nx;
		ctx->enemies[idx].y = ny;
		mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->tx->enemy, (nx
				* ctx->tx->tile_w), (ny * ctx->tx->tile_h));
	}
}

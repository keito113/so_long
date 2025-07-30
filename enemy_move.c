/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:52:51 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/30 14:20:35 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_enemies(t_context *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->enemy_count)
	{
		mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->tx->enemy,
			(ctx->enemies[i].x * ctx->tx->tile_w), (ctx->enemies[i].y
				* ctx->tx->tile_h));
		i++;
	}
}

void	init_enemies(t_context *ctx)
{
	ctx->enemy_count = count_enemies(ctx);
	ctx->enemies = malloc(sizeof(t_enemy) * ctx->enemy_count);
	if (!ctx->enemies)
		error_exit("Enemy malloc failed");
	fill_enemies(ctx);
	ctx->rng.seed = read_uptime_seconds();
	ctx->last_enemy_move = ctx->rng.seed;
}

int	enemy_loop_hook(void *param)
{
	t_context	*ctx;
	static int	initialized;
	int			now;
	int			i;

	ctx = (t_context *)param;
	if (!initialized)
	{
		init_enemies(ctx);
		draw_enemies(ctx);
		initialized = 1;
	}
	now = read_uptime_seconds();
	if (now - ctx->last_enemy_move >= 1)
	{
		i = 0;
		while (i < ctx->enemy_count)
			move_one_enemy(ctx, i++);
		ctx->last_enemy_move = now;
	}
	return (0);
}

// void	init_enemies(t_context *ctx)
// {
// 	ctx->enemy_count = count_enemies(ctx);
// 	ctx->enemies = malloc(sizeof(t_enemy) * ctx->enemy_count);
// 	if (ctx->enemies)
// 		error_exit("Enemy malloc failed");
// 	fill_enemies(ctx);
// 	ctx->last_enemy_move = read_uptime_seconds();
// 	ctx->rng.seed = ctx->last_enemy_move;
// }

// void	move_enemies(t_context *ctx)
// {
// 	int	i;

// 	i = 0;
// 	while (i < ctx->enemy_count)
// 	{
// 		move_one_enemy(ctx, i);
// 		i++;
// 	}
// }

// int	enemy_loop_hook(void *param)
// {
// 	t_context	*ctx;
// 	int			now;

// 	ctx = (t_context *)param;
// 	now = read_uptime_seconds();
// 	if (now - ctx->last_enemy_move >= 1)
// 	{
// 		move_enemies(ctx);
// 		ctx->last_enemy_move = now;
// 	}
// 	return (0);
// }

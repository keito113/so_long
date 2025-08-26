/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:52:51 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/25 11:43:07 by keitabe          ###   ########.fr       */
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
	struct timeval	tv;

	ctx->enemy_count = count_enemies(ctx);
	if (gettimeofday(&tv, NULL) < 0)
		error_exit("gettimeofday failure");
	ctx->rng.seed = (int)(tv.tv_sec ^ tv.tv_usec);
	ctx->last_enemy_move = tv;
	if (ctx->enemy_count <= 0)
	{
		ctx->enemies = NULL;
		return ;
	}
	ctx->enemies = malloc(sizeof(t_enemy) * ctx->enemy_count);
	if (!ctx->enemies)
		error_exit("Enemy malloc failed");
	fill_enemies(ctx);
}

static void	move_all_enemies(t_context *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->enemy_count)
		move_one_enemy(ctx, i++);
}

int	enemy_loop_hook(void *param)
{
	t_context		*ctx;
	static int		initialized;
	struct timeval	now;
	long			sec_diff;

	ctx = (t_context *)param;
	if (ctx->end.win_ptr)
		return (0);
	if (!initialized)
	{
		init_enemies(ctx);
		draw_enemies(ctx);
		initialized = 1;
	}
	if (gettimeofday(&now, NULL) < 0)
		return (0);
	sec_diff = (long)(now.tv_sec - ctx->last_enemy_move.tv_sec);
	if ((sec_diff > 1) || (sec_diff == 1
			&& now.tv_usec >= ctx->last_enemy_move.tv_usec))
	{
		move_all_enemies(ctx);
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

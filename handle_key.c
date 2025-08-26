/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:01:02 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/25 12:06:52 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_keypress(int keycode, void *param)
{
	t_context	*ctx;

	ctx = param;
	if (ctx->end.win_ptr)
		return (0);
	if (keycode == KEY_ESC)
		cleanup_graphics(ctx);
	else if (keycode == KEY_W)
		move_player(0, -1, ctx);
	else if (keycode == KEY_A)
		move_player(-1, 0, ctx);
	else if (keycode == KEY_S)
		move_player(0, 1, ctx);
	else if (keycode == KEY_D)
		move_player(1, 0, ctx);
	return (0);
}

int	on_destroy(void *param)
{
	cleanup_graphics((t_context *)param);
	return (0);
}

void	handle_events(t_context *ctx)
{
	mlx_hook(ctx->win_ptr, KeyPress, KeyPressMask, on_keypress, ctx);
	mlx_hook(ctx->win_ptr, DestroyNotify, StructureNotifyMask, on_destroy, ctx);
	mlx_loop(ctx->mlx_ptr);
}

int	handle_enemy_collision(int x, int y, t_context *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->enemy_count)
	{
		if (ctx->enemies[i].x == x && ctx->enemies[i].y == y)
		{
			handle_end(ctx, "textures/game_over.xpm", "Game Over");
			return (1);
		}
		i++;
	}
	return (0);
}

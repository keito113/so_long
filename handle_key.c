/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:01:02 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/29 12:57:39 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_graphics(t_context *ctx)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_textures	*tx;

	mlx_ptr = ctx->mlx_ptr;
	win_ptr = ctx->win_ptr;
	tx = ctx->tx;
	mlx_destroy_image(mlx_ptr, tx->floor);
	mlx_destroy_image(mlx_ptr, tx->player);
	mlx_destroy_image(mlx_ptr, tx->exit);
	mlx_destroy_image(mlx_ptr, tx->wall);
	mlx_destroy_image(mlx_ptr, tx->collectible);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	exit(0);
}

int	on_keypress(int keycode, void *param)
{
	t_context	*ctx;

	ctx = param;
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

int	on_destroy(int unused, void *param)
{
	t_context	*ctx;

	(void)unused;
	ctx = (t_context *)param;
	cleanup_graphics(ctx);
	return (0);
}

void	handle_events(t_context *ctx)
{
	mlx_hook(ctx->win_ptr, KeyPress, KeyPressMask, on_keypress, ctx);
	mlx_hook(ctx->win_ptr, DestroyNotify, StructureNotifyMask, on_destroy, ctx);
	mlx_loop(ctx->mlx_ptr);
}

void	handle_enemy_collision(t_context *ctx)
{
	ft_putstr_fd("Game Over!\n", 1);
	cleanup_graphics(ctx);
	exit(0);
}

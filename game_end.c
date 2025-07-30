/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 07:52:18 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/30 13:13:13 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_end_window(void *mlx_ptr, t_gameover *go, const char *path,
		const char *title)
{
	go->img_ptr = mlx_xpm_file_to_image(mlx_ptr, (char *)path, &go->width,
			&go->height);
	if (!go->img_ptr)
		error_exit(path);
	go->win_ptr = mlx_new_window(mlx_ptr, go->width, go->height, (char *)title);
	if (!go->win_ptr)
		error_exit("mlx_new_window failed");
}

static int	expose_hook(void *param)
{
	t_context	*ctx;
	t_gameover	*go;

	ctx = param;
	go = &ctx->gameover;
	mlx_put_image_to_window(ctx->mlx_ptr, go->win_ptr, go->img_ptr, 0, 0);
	return (0);
}

void	handle_end(t_context *ctx, const char *path, const char *title)
{
	t_gameover	*go;

	mlx_destroy_window(ctx->mlx_ptr, ctx->win_ptr);
	go = &ctx->gameover;
	init_end_window(ctx->mlx_ptr, go, path, title);
	mlx_hook(go->win_ptr, 12, 0, expose_hook, ctx);
	go->start_sec = read_uptime_seconds();
	mlx_loop_hook(ctx->mlx_ptr, timeout_hook, ctx);
	mlx_loop(ctx->mlx_ptr);
}

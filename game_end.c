/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 07:52:18 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/29 12:28:42 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_end_window(t_context *ctx, const char *path, const char *title)
{
	t_end	*go;

	go = &ctx->end;
	go->img_ptr = mlx_xpm_file_to_image(ctx->mlx_ptr, (char *)path, &go->width,
			&go->height);
	if (!go->img_ptr)
		fatal(ctx, ERR_IMG_LOAD, path);
	go->win_ptr = mlx_new_window(ctx->mlx_ptr, go->width, go->height,
			(char *)title);
	if (!go->win_ptr)
	{
		mlx_destroy_image(ctx->mlx_ptr, go->img_ptr);
		go->img_ptr = NULL;
		fatal(ctx, ERR_MLX_WIN, "mlx_new_window failed");
	}
}

static int	expose_hook(void *param)
{
	t_context	*ctx;
	t_end		*go;

	ctx = param;
	go = &ctx->end;
	mlx_put_image_to_window(ctx->mlx_ptr, go->win_ptr, go->img_ptr, 0, 0);
	return (0);
}

void	handle_end(t_context *ctx, const char *path, const char *title)
{
	t_end	*go;

	if (ctx->win_ptr)
		mlx_destroy_window(ctx->mlx_ptr, ctx->win_ptr);
	ctx->win_ptr = NULL;
	init_end_window(ctx, path, title);
	go = &ctx->end;
	mlx_hook(go->win_ptr, 12, 0, expose_hook, ctx);
	mlx_hook(go->win_ptr, 17, 0, on_destroy, ctx);
	if (gettimeofday(&go->start_tv, NULL) < 0)
		fatal(ctx, ERR_GENERIC, "gettimeofday failure");
	go->wait_time = 3;
	mlx_loop_hook(ctx->mlx_ptr, timeout_hook, ctx);
}

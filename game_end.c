/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 07:52:18 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/25 11:53:43 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_end_window(void *mlx_ptr, t_end *go, const char *path,
		const char *title)
{
	go->img_ptr = mlx_xpm_file_to_image(mlx_ptr, (char *)path, &go->width,
			&go->height);
	if (!go->img_ptr)
		error_exit(path);
	go->win_ptr = mlx_new_window(mlx_ptr, go->width, go->height, (char *)title);
	if (!go->win_ptr)
	{
		mlx_destroy_image(mlx_ptr, go->img_ptr);
		go->img_ptr = NULL;
		error_exit("mlx_new_window failed");
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

	mlx_destroy_window(ctx->mlx_ptr, ctx->win_ptr);
	ctx->win_ptr = NULL;
	go = &ctx->end;
	init_end_window(ctx->mlx_ptr, go, path, title);
	mlx_hook(go->win_ptr, 12, 0, expose_hook, ctx);
	mlx_hook(go->win_ptr, 17, 0, on_destroy, ctx);
	gettimeofday(&go->start_tv, NULL);
	go->wait_time = 3;
	mlx_loop_hook(ctx->mlx_ptr, timeout_hook, ctx);
}

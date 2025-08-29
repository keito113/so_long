/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_graphics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:49:16 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/29 12:28:50 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	app_destroy(t_context *ctx)
{
	if (!ctx)
		return ;
	destroy_textures(ctx);
	if (ctx->mlx_ptr)
	{
		if (ctx->end.img_ptr)
		{
			mlx_destroy_image(ctx->mlx_ptr, ctx->end.img_ptr);
			ctx->end.img_ptr = NULL;
		}
		if (ctx->end.win_ptr && ctx->end.win_ptr != ctx->win_ptr)
			mlx_destroy_window(ctx->mlx_ptr, ctx->end.win_ptr);
		if (ctx->win_ptr)
			mlx_destroy_window(ctx->mlx_ptr, ctx->win_ptr);
		mlx_destroy_display(ctx->mlx_ptr);
		free(ctx->mlx_ptr);
		ctx->mlx_ptr = NULL;
	}
	ctx->end.win_ptr = NULL;
	ctx->win_ptr = NULL;
	free(ctx->enemies);
	ctx->enemies = NULL;
	free(ctx->tx);
	ctx->tx = NULL;
	free_map(&ctx->map);
}

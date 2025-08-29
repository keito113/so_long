/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:52:39 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/28 12:10:04 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*xpm_or_die(t_context *ctx, const char *path, int *w, int *h)
{
	void	*img;

	img = mlx_xpm_file_to_image(ctx->mlx_ptr, (char *)path, w, h);
	if (!img)
		fatal(ctx, ERR_IMG_LOAD, path);
	return (img);
}

void	load_textures(t_context *ctx)
{
	int	w;
	int	h;

	if (!ctx || !ctx->mlx_ptr || !ctx->tx)
		fatal(ctx, ERR_GENERIC, "load_textures: bad ctx");
	ctx->tx->floor = xpm_or_die(ctx, "textures/floor.xpm", &w, &h);
	ctx->tx->tile_w = w;
	ctx->tx->tile_h = h;
	ctx->tx->player = xpm_or_die(ctx, "textures/player.xpm", &w, &h);
	ctx->tx->wall = xpm_or_die(ctx, "textures/wall.xpm", &w, &h);
	ctx->tx->exit = xpm_or_die(ctx, "textures/exit.xpm", &w, &h);
	ctx->tx->collectible = xpm_or_die(ctx, "textures/collectible.xpm", &w, &h);
	ctx->tx->enemy = xpm_or_die(ctx, "textures/enemy.xpm", &w, &h);
}

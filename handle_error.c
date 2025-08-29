/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:07:40 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/29 12:28:37 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_textures(t_context *ctx)
{
	if (!ctx || !ctx->mlx_ptr || !ctx->tx)
		return ;
	if (ctx->tx->wall)
		mlx_destroy_image(ctx->mlx_ptr, ctx->tx->wall);
	if (ctx->tx->floor)
		mlx_destroy_image(ctx->mlx_ptr, ctx->tx->floor);
	if (ctx->tx->player)
		mlx_destroy_image(ctx->mlx_ptr, ctx->tx->player);
	if (ctx->tx->collectible)
		mlx_destroy_image(ctx->mlx_ptr, ctx->tx->collectible);
	if (ctx->tx->exit)
		mlx_destroy_image(ctx->mlx_ptr, ctx->tx->exit);
	if (ctx->tx->enemy)
		mlx_destroy_image(ctx->mlx_ptr, ctx->tx->enemy);
	ctx->tx->wall = NULL;
	ctx->tx->floor = NULL;
	ctx->tx->player = NULL;
	ctx->tx->collectible = NULL;
	ctx->tx->exit = NULL;
	ctx->tx->enemy = NULL;
}

static const char	*msg_of(t_errc c)
{
	if (c == ERR_ALLOC)
		return ("Memory allocation failed");
	if (c == ERR_SYS_OPEN)
		return ("Cannot open file");
	if (c == ERR_SYS_READ)
		return ("Read failed");
	if (c == ERR_SYS_CLOSE)
		return ("Close failed");
	if (c == ERR_MAP_RECT)
		return ("Map error: not rectangular");
	if (c == ERR_MAP_BORDER)
		return ("Map error: border not closed");
	if (c == ERR_MAP_PEC)
		return ("Map error: P/E/C invalid");
	if (c == ERR_MAP_PATH)
		return ("Map error: path unreachable");
	if (c == ERR_MLX_INIT)
		return ("Failed to init MLX");
	if (c == ERR_MLX_WIN)
		return ("Failed to create window");
	if (c == ERR_IMG_LOAD)
		return ("Failed to load texture");
	return ("Fatal error");
}

void	fatal(t_context *ctx, t_errc code, const char *detail)
{
	const char	*msg = msg_of(code);

	app_destroy(ctx);
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	if (detail)
	{
		write(2, ": ", 2);
		write(2, detail, ft_strlen(detail));
	}
	write(2, "\n", 1);
	exit(1);
}

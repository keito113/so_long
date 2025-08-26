/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_graphics.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:49:16 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/26 12:43:12 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_textures(void *mlx_ptr, t_textures *tx)
{
	if (!tx)
		return ;
	if (tx->floor)
		mlx_destroy_image(mlx_ptr, tx->floor);
	if (tx->player)
		mlx_destroy_image(mlx_ptr, tx->player);
	if (tx->exit)
		mlx_destroy_image(mlx_ptr, tx->exit);
	if (tx->wall)
		mlx_destroy_image(mlx_ptr, tx->wall);
	if (tx->collectible)
		mlx_destroy_image(mlx_ptr, tx->collectible);
	if (tx->enemy)
		mlx_destroy_image(mlx_ptr, tx->enemy);
}

static void	free_map_date(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->date[i]);
		i++;
	}
	free(map->date);
	free(map);
}

void	cleanup_graphics(t_context *ctx)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = ctx->mlx_ptr;
	win_ptr = ctx->win_ptr;
	if (ctx->end.img_ptr || ctx->end.win_ptr)
		cleanup_gameover(mlx_ptr, &ctx->end);
	if (win_ptr)
		mlx_destroy_window(mlx_ptr, win_ptr);
	destroy_textures(mlx_ptr, ctx->tx);
	if (mlx_ptr)
	{
		mlx_destroy_display(mlx_ptr);
		free(mlx_ptr);
	}
	if (ctx->map)
		free_map_date(ctx->map);
	if (ctx->enemies)
		free(ctx->enemies);
	exit(0);
}

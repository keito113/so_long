/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:21:53 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/29 12:28:39 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_graphics(t_context *ctx, int width, int height)
{
	ctx->mlx_ptr = mlx_init();
	if (!ctx->mlx_ptr)
		fatal(ctx, ERR_MLX_INIT, "Mlx initialization failure");
	ctx->win_ptr = mlx_new_window(ctx->mlx_ptr, width, height, "so_long");
	if (!ctx->win_ptr)
		fatal(ctx, ERR_MLX_WIN, "Window creation failure");
}

static void	*get_tex_ptr(char c, t_textures *tx)
{
	if (c == '0')
		return (tx->floor);
	if (c == '1')
		return (tx->wall);
	if (c == 'C')
		return (tx->collectible);
	if (c == 'E')
		return (tx->exit);
	if (c == 'P')
		return (tx->player);
	if (c == 'X')
		return (tx->enemy);
	return (NULL);
}

void	render_map(void *mlx_ptr, void *win_ptr, t_map *map, t_textures *tx)
{
	int	row;
	int	col;
	int	x;
	int	y;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			x = col * tx->tile_w;
			y = row * tx->tile_h;
			mlx_put_image_to_window(mlx_ptr, win_ptr,
				get_tex_ptr(map->date[row][col], tx), x, y);
			col++;
		}
		row++;
	}
}

void	init_player_pos(t_context *ctx)
{
	int	x;
	int	y;

	y = 0;
	while (y < ctx->map->height)
	{
		x = 0;
		while (x < ctx->map->width)
		{
			if (ctx->map->date[y][x] == 'P')
			{
				ctx->player_x = x;
				ctx->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

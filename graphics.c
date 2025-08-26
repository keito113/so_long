/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:21:53 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/26 14:15:12 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_graphics(void **mlx_ptr, void **win_ptr, int width, int height)
{
	*mlx_ptr = mlx_init();
	if (!*mlx_ptr)
		error_exit("Mlx initialization failure");
	*win_ptr = mlx_new_window(*mlx_ptr, width, height, "so_long");
	if (!*win_ptr)
		error_exit("Window creation failure");
}

void	load_textures(void *mlx_ptr, t_textures *tx)
{
	int	w;
	int	h;

	tx->floor = mlx_xpm_file_to_image(mlx_ptr, "textures/floor.xpm", &w, &h);
	if (!tx->floor)
		error_exit("Floor image loading failure");
	tx->tile_w = w;
	tx->tile_h = h;
	tx->player = mlx_xpm_file_to_image(mlx_ptr, "textures/player.xpm", &w, &h);
	if (!tx->player)
		error_exit("Player image loading failure");
	tx->wall = mlx_xpm_file_to_image(mlx_ptr, "textures/wall.xpm", &w, &h);
	if (!tx->wall)
		error_exit("Wall image loading failure");
	tx->exit = mlx_xpm_file_to_image(mlx_ptr, "textures/exit.xpm", &w, &h);
	if (!tx->exit)
		error_exit("Exit image loading failure");
	tx->collectible = mlx_xpm_file_to_image(mlx_ptr, "textures/collectible.xpm",
			&w, &h);
	if (!tx->collectible)
		error_exit("Collectible image loading failure");
	tx->enemy = mlx_xpm_file_to_image(mlx_ptr, "textures/enemy.xpm", &w, &h);
	if (!tx->enemy)
		error_exit("Enemy image loading failure");
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
	error_exit("Invalid map char");
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

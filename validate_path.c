/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:18:22 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/29 09:23:35 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	find_player_position(const t_map *map, int *px, int *py)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->date[y][x] == 'P')
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
	error_exit("Player position not found");
}

static char	**copy_map(char **src, int height, int width)
{
	char	**copy;
	char	*date;
	int		i;
	size_t	ptr_size;
	size_t	buf_size;

	ptr_size = sizeof(char *) * (size_t)height;
	buf_size = (size_t)height * (width + 1);
	copy = malloc(ptr_size + buf_size);
	if (!copy)
		error_exit("Copy map allocation failed");
	date = (char *)(copy + height);
	i = 0;
	while (i < height)
	{
		copy[i] = date + (size_t)i * (width + 1);
		ft_memcpy(copy[i], src[i], width);
		copy[i][width] = '\0';
		i++;
	}
	return (copy);
}

static void	flood_fill(t_scan_map *ctx, int x, int y)
{
	if (x < 0 || x >= ctx->width || y < 0 || y >= ctx->height)
		return ;
	if (ctx->map[y][x] == '1' || ctx->map[y][x] == 'V')
		return ;
	if (ctx->map[y][x] == '0' || ctx->map[y][x] == 'C' || ctx->map[y][x] == 'E'
		|| ctx->map[y][x] == 'P')
		ctx->map[y][x] = 'V';
	flood_fill(ctx, x + 1, y);
	flood_fill(ctx, x - 1, y);
	flood_fill(ctx, x, y + 1);
	flood_fill(ctx, x, y - 1);
}

static void	count_remaining(t_scan_map *ctx, int *c_cnt, int *e_cnt)
{
	int	x;
	int	y;

	*c_cnt = 0;
	*e_cnt = 0;
	y = 0;
	while (y < ctx->height)
	{
		x = 0;
		while (x < ctx->width)
		{
			if (ctx->map[y][x] == 'C')
				(*c_cnt)++;
			if (ctx->map[y][x] == 'E')
				(*e_cnt)++;
			x++;
		}
		y++;
	}
}

void	validate_path(const t_map *map)
{
	int			px;
	int			py;
	int			c_cnt;
	int			e_cnt;
	t_scan_map	ctx;

	ctx.map = copy_map(map->date, map->height, map->width);
	ctx.width = map->width;
	ctx.height = map->height;
	find_player_position(map, &px, &py);
	flood_fill(&ctx, px, py);
	count_remaining(&ctx, &c_cnt, &e_cnt);
	free(ctx.map);
	if (c_cnt > 0 || e_cnt > 0)
		error_exit("No valid path");
}

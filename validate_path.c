/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:18:22 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/29 12:28:14 by keitabe          ###   ########.fr       */
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
	die_map(map, ERR_MAP_PEC, "Player position not found");
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
		fatal(NULL, ERR_ALLOC, "Copy map allocation failed");
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

static void	flood_fill(t_scan_map *ctx, int x, int y, int allow_exit)
{
	char	c;

	if (x < 0 || x >= ctx->width || y < 0 || y >= ctx->height)
		return ;
	c = ctx->map[y][x];
	if (c == 'V' || c == '1' || c == 'X')
		return ;
	if (c == 'E')
	{
		if (!allow_exit)
			return ;
		ctx->map[y][x] = 'V';
	}
	else if (c == '0' || c == 'C' || c == 'P')
		ctx->map[y][x] = 'V';
	else
		return ;
	flood_fill(ctx, x + 1, y, allow_exit);
	flood_fill(ctx, x - 1, y, allow_exit);
	flood_fill(ctx, x, y + 1, allow_exit);
	flood_fill(ctx, x, y - 1, allow_exit);
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

	find_player_position(map, &px, &py);
	ctx.width = map->width;
	ctx.height = map->height;
	ctx.map = copy_map(map->date, map->height, map->width);
	flood_fill(&ctx, px, py, 0);
	count_remaining(&ctx, &c_cnt, &e_cnt);
	free(ctx.map);
	if (c_cnt > 0)
		die_map(map, ERR_MAP_PATH, "No valid path(collectibles unreachable)");
	ctx.map = copy_map(map->date, map->height, map->width);
	flood_fill(&ctx, px, py, 1);
	count_remaining(&ctx, &c_cnt, &e_cnt);
	free(ctx.map);
	if (e_cnt > 0)
		die_map(map, ERR_MAP_PATH, "No valid path (exit unreachable)");
}

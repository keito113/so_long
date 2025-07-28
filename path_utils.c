/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:25:10 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/28 12:03:21 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	find_player_position(t_map *map, int *px, int *py)
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

void	free_map_copy(char **copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

char	**copy_map(const char **src, int height, int width)
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

void	flood_fill(t_scan_map *ctx, int x, int y)
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

void	count_remaining(t_scan_map *ctx, int *c_cnt, int *e_cnt)
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

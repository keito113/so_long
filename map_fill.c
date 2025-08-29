/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:33:33 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/29 12:28:30 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_rows(char **arr, int n)
{
	while (n > 0)
	{
		free(arr[n - 1]);
		n--;
	}
	free(arr);
}

char	**alloc_map(int height, int width)
{
	char	**map;
	int		i;

	if (height <= 0 || width <= 0)
		fatal(NULL, ERR_MAP_RECT, "Invalid map dimensions");
	map = malloc(sizeof(char *) * height);
	if (!map)
		fatal(NULL, ERR_ALLOC, "Memory allocation failed");
	i = 0;
	while (i < height)
	{
		map[i] = malloc(width + 1);
		if (!map[i])
		{
			free_rows(map, i);
			fatal(NULL, ERR_ALLOC, "Memory allocation failed");
		}
		map[i][width] = '\0';
		i++;
	}
	return (map);
}

static ssize_t	fill_loop(int fd, t_map *map)
{
	ssize_t	bytes;
	char	c;
	int		row;
	int		col;

	row = 0;
	col = 0;
	bytes = read(fd, &c, 1);
	while (bytes > 0)
	{
		if (c == '\n')
		{
			row++;
			col = 0;
		}
		else
		{
			if (row >= map->height || col >= map->width)
				fatal_map(&map, ERR_MAP_RECT, "Map dimensions mismatch");
			map->date[row][col] = c;
			col++;
		}
		bytes = read(fd, &c, 1);
	}
	return (bytes);
}

void	fill_map(const char *filename, t_map *map)
{
	int		fd;
	ssize_t	bytes;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		fatal_map(&map, ERR_SYS_OPEN, filename);
	bytes = fill_loop(fd, map);
	if (close(fd) == -1)
		fatal_map(&map, ERR_SYS_CLOSE, filename);
	if (bytes == -1)
		fatal_map(&map, ERR_SYS_READ, filename);
}

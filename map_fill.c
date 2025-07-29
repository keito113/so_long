/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:33:33 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/29 08:20:27 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_map(char **arr, int n)
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
		error_exit("Invalid map dimensions");
	map = malloc(sizeof(char *) * height);
	if (!map)
		error_exit("Memory allocation failed");
	i = 0;
	while (i < height)
	{
		map[i] = malloc(width + 1);
		if (!map[i])
		{
			free_map(map, i);
			error_exit("Memory allocation failed");
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
	while ((bytes = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
		{
			row++;
			col = 0;
		}
		else
		{
			if (row >= map->height || col >= map->width)
				error_exit("Map dimensions mismatch");
			map->date[row][col] = c;
			col++;
		}
	}
	return (bytes);
}

void	fill_map(const char *filename, t_map *map)
{
	int		fd;
	ssize_t	bytes;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("Cannot open file");
	bytes = fill_loop(fd, map);
	close(fd);
	if (bytes == -1)
		error_exit("Read error");
}

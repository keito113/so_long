/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:20:44 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/30 14:54:03 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	validate_chars(const t_map *map)
{
	int		row;
	int		col;
	char	c;

	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			c = map->date[row][col];
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P'
				&& c != 'X')
				error_exit("Map character error");
			col++;
		}
		row++;
	}
}

void	validate_border(const t_map *map)
{
	int	row;
	int	col;

	row = 0;
	col = map->width - 1;
	while (row < map->height)
	{
		if (map->date[row][0] != '1')
			error_exit("Not surrounded by walls");
		if (map->date[row][col] != '1')
			error_exit("Not surrounded by walls");
		row++;
	}
	col = 0;
	row = map->height - 1;
	while (col < map->width)
	{
		if (map->date[0][col] != '1')
			error_exit("Not surrounded by walls");
		if (map->date[row][col] != '1')
			error_exit("Not surrounded by walls");
		col++;
	}
}

static int	element_count(const t_map *map, char c)
{
	int	count;
	int	row;
	int	col;

	count = 0;
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (map->date[row][col] == c)
				count++;
			col++;
		}
		row++;
	}
	return (count);
}

void	validate_elements(const t_map *map)
{
	int	p_count;
	int	e_count;
	int	c_count;

	p_count = element_count(map, 'P');
	e_count = element_count(map, 'E');
	c_count = element_count(map, 'C');
	if (p_count != 1)
		error_exit("Player starting position is incorrect");
	if (e_count != 1)
		error_exit("Map exit is incorrect");
	if (c_count < 1)
		error_exit("Not enough collectibles");
}

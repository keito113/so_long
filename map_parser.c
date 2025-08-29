/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:27:25 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/29 12:28:28 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_filename(const char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext)
		return (0);
	return (ft_strcmp(ext, ".ber") == 0);
}

static void	finalize_line_width(int current_width, int *result_width)
{
	if (*result_width < 0)
		*result_width = current_width;
	else if (current_width != *result_width)
		fatal(NULL, ERR_MAP_RECT, "Map is not rectangular");
}

static ssize_t	process_width_stream(int fd, int *result_width)
{
	char	buf;
	ssize_t	bytes_read;
	int		current_width;

	current_width = 0;
	bytes_read = read(fd, &buf, 1);
	while (bytes_read > 0)
	{
		if (buf == '\n')
		{
			finalize_line_width(current_width, result_width);
			current_width = 0;
		}
		else
			current_width++;
		bytes_read = read(fd, &buf, 1);
	}
	if (bytes_read == -1)
		return (-1);
	if (current_width > 0)
		finalize_line_width(current_width, result_width);
	return (bytes_read);
}

int	check_width(const char *filename, int ex_width)
{
	int		fd;
	int		result_width;
	ssize_t	bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		fatal(NULL, ERR_SYS_OPEN, filename);
	result_width = ex_width;
	bytes_read = process_width_stream(fd, &result_width);
	if (bytes_read == -1)
	{
		(void)close(fd);
		fatal(NULL, ERR_SYS_READ, filename);
	}
	if (close(fd) == -1)
		fatal(NULL, ERR_SYS_CLOSE, filename);
	return (result_width);
}

t_map	*read_map(const char *filename)
{
	t_map	*map;
	int		h;
	int		w;

	if (!check_filename(filename))
		fatal(NULL, ERR_GENERIC, "Invalid file extension");
	h = count_lines(filename);
	w = check_width(filename, -1);
	map = malloc(sizeof(t_map));
	if (!map)
		fatal(NULL, ERR_ALLOC, "Memory allocation failed");
	map->height = h;
	map->width = w;
	map->date = alloc_map(map->height, map->width);
	fill_map(filename, map);
	validate_chars(map);
	validate_border(map);
	validate_elements(map);
	validate_path(map);
	return (map);
}

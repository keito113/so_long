/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:27:25 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/22 09:11:56 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "map_parser.h"

static int	check_filename(const char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext)
		return (0);
	if (ft_strcmp(ext, ".ber") == 0)
		return (1);
	return (0);
}

static void	finalize_line_width(int current_width, int *result_width)
{
	if (*result_width < 0)
		*result_width = current_width;
	else if (current_width != *result_width)
		error_exit("Map is not rectangular");
}

static ssize_t	process_width_stream(int fd, int *result_width)
{
	char	buf;
	ssize_t	bytes_read;
	int		current_width;

	current_width = 0;
	while ((bytes_read = read(fd, &buf, 1)) > 0)
	{
		if (buf == '\n')
		{
			finalize_line_width(current_width, result_width);
			current_width = 0;
		}
		else
			current_width++;
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
		error_exit("Cannot open file");
	result_width = ex_width;
	bytes_read = process_width_stream(fd, &result_width);
	if (bytes_read == -1)
		error_exit("Error reading file");
	close(fd);
	return (result_width);
}

t_map	*read_map(const char *filename)
{
	t_map	*map;

	if (!check_filename(filename))
		error_exit("Invalid file extension");
	map = malloc(sizeof(t_map));
	if (!map)
		error_exit("Memory allocation failed");
	map->height = count_lines(filename);
	map->width = check_width(filename, -1);
	map->date = alloc_map(map->height, map->width);
	fill_map(filename, map);
	validate_chars(map);
	validate_border(map);
	validate_elements(map);
	return (map);
}

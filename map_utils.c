/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:24:47 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/30 15:02:47 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

int	count_lines(const char *filename)
{
	int		lines;
	int		fd;
	char	buf;
	ssize_t	bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("Cannot open file");
	lines = 0;
	bytes_read = read(fd, &buf, 1);
	while (bytes_read > 0)
	{
		if (buf == '\n')
			lines++;
		bytes_read = read(fd, &buf, 1);
	}
	if (bytes_read == -1)
		error_exit("Error reading file");
	close(fd);
	return (lines);
}

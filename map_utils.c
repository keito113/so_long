/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:24:47 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/29 12:28:25 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map **pm)
{
	int	i;

	if (pm == NULL || *pm == NULL)
		return ;
	if ((*pm)->date != NULL)
	{
		i = 0;
		while (i < (*pm)->height && (*pm)->date[i] != NULL)
		{
			free((*pm)->date[i]);
			i++;
		}
		free((*pm)->date);
		(*pm)->date = NULL;
	}
	free(*pm);
	*pm = NULL;
}

void	fatal_map(t_map **pm, t_errc code, const char *detail)
{
	if (pm && *pm)
		free_map(pm);
	fatal(NULL, code, detail);
}

void	die_map(const t_map *map, t_errc code, const char *msg)
{
	t_map	*m;

	m = (t_map *)map;
	fatal_map(&m, code, msg);
}

static ssize_t	count_stream(int fd, int *lines, char *last, int *seen)
{
	char	c;
	ssize_t	br;

	br = read(fd, &c, 1);
	while (br > 0)
	{
		*seen = 1;
		*last = c;
		if (c == '\n')
			(*lines)++;
		br = read(fd, &c, 1);
	}
	return (br);
}

int	count_lines(const char *filename)
{
	int		lines;
	int		fd;
	int		seen;
	char	last;
	ssize_t	br;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		fatal(NULL, ERR_SYS_OPEN, filename);
	lines = 0;
	seen = 0;
	last = '\n';
	br = count_stream(fd, &lines, &last, &seen);
	if (br == -1)
	{
		(void)close(fd);
		fatal(NULL, ERR_SYS_READ, filename);
	}
	if (close(fd) == -1)
		fatal(NULL, ERR_SYS_CLOSE, filename);
	if (seen && last != '\n')
		lines++;
	return (lines);
}

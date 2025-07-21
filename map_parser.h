/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:27:36 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/21 11:01:39 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H

# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	char	**date;
	int		width;
	int		height;
}			t_map;

void		error_exit(const char *msg);
int			count_lines(const char *filename);
char		**alloc_map(int height, int width);
void		fill_map(const char *filename, char **map);

#endif

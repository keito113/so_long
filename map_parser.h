/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:27:36 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/28 12:04:14 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H

# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	char	**date;
	int		width;
	int		height;
}			t_map;

typedef struct s_scan_map
{
	char	**map;
	int		width;
	int		height;
}			t_scan_map;

void		error_exit(const char *msg);
int			check_width(const char *filename, int ex_width);
int			count_lines(const char *filename);
char		**alloc_map(int height, int width);
void		fill_map(const char *filename, t_map *map);
void		validate_chars(const t_map *map);
void		validate_border(const t_map *map);
void		validate_elements(const t_map *map);
t_map		*read_map(const char *filename);
void		find_player_position(t_map *map, int *px, int *py);
void		free_map_copy(char **copy, int height);
char		**copy_map(char **src, int height, int width);
void		flood_fill(t_scan_map *ctx, int x, int y);
void		count_remaining(t_scan_map *ctx, int *c_cnt, int *e_cnt);

#endif

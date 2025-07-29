/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 07:58:52 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/29 12:57:59 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_map
{
	char		**date;
	int			width;
	int			height;
}				t_map;

typedef struct s_scan_map
{
	char		**map;
	int			width;
	int			height;
}				t_scan_map;

typedef struct s_textures
{
	void		*wall;
	void		*floor;
	void		*player;
	void		*collectible;
	void		*exit;
	void		*enemy;
	int			tile_w;
	int			tile_h;
}				t_textures;

typedef struct s_context
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			collectable;
	int			moves;
	int			player_x;
	int			player_y;
	t_map		*map;
	t_textures	*tx;
}				t_context;

void			error_exit(const char *msg);
int				check_width(const char *filename, int ex_width);
int				count_lines(const char *filename);
char			**alloc_map(int height, int width);
void			fill_map(const char *filename, t_map *map);
void			validate_chars(const t_map *map);
void			validate_border(const t_map *map);
void			validate_elements(const t_map *map);
t_map			*read_map(const char *filename);
void			validate_path(const t_map *map);

void			draw_move_count(t_context *ctx);
void			move_player(int dx, int dy, t_context *ctx);

void			init_graphics(void **mlx_ptr, void **win_ptr, int width,
					int height);
void			load_textures(void *mlx_ptr, t_textures *tx);
void			render_map(void *mlx_ptr, void *win_ptr, t_map *map,
					t_textures *tx);
void			cleanup_graphics(t_context *ctx);
int				on_keypress(int keycode, void *param);
int				on_destroy(int unused, void *param);
void			handle_events(t_context *ctx);
void			handle_enemy_collision(t_context *ctx);
void			move_player(int dx, int dy, t_context *ctx);
void			init_player_pos(t_context *ctx);

#endif

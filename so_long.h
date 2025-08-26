/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 07:58:52 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/25 09:45:29 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <mlx.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_rng
{
	int				seed;
}					t_rng;

typedef struct s_map
{
	char			**date;
	int				width;
	int				height;
}					t_map;

typedef struct s_scan_map
{
	char			**map;
	int				width;
	int				height;
}					t_scan_map;

typedef struct s_textures
{
	void			*wall;
	void			*floor;
	void			*player;
	void			*collectible;
	void			*exit;
	void			*enemy;
	int				tile_w;
	int				tile_h;
}					t_textures;

typedef struct s_end
{
	void			*img_ptr;
	int				width;
	int				height;
	void			*win_ptr;
	int				wait_time;
	struct timeval	start_tv;

}					t_end;

typedef struct s_enemy
{
	int				x;
	int				y;
}					t_enemy;

typedef struct s_context
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				collectable;
	int				moves;
	int				player_x;
	int				player_y;
	int				enemy_count;
	struct timeval	last_enemy_move;
	t_enemy			*enemies;
	t_rng			rng;
	t_end			end;
	t_map			*map;
	t_textures		*tx;
}					t_context;

void				error_exit(const char *msg);
int					check_width(const char *filename, int ex_width);
int					count_lines(const char *filename);
char				**alloc_map(int height, int width);
void				fill_map(const char *filename, t_map *map);
void				validate_chars(const t_map *map);
void				validate_border(const t_map *map);
void				validate_elements(const t_map *map);
t_map				*read_map(const char *filename);
void				validate_path(const t_map *map);

void				draw_move_count(t_context *ctx);
void				move_player(int dx, int dy, t_context *ctx);

void				init_graphics(void **mlx_ptr, void **win_ptr, int width,
						int height);
void				load_textures(void *mlx_ptr, t_textures *tx);
void				render_map(void *mlx_ptr, void *win_ptr, t_map *map,
						t_textures *tx);
void				cleanup_graphics(t_context *ctx);
int					on_keypress(int keycode, void *param);
int					on_destroy(void *param);
void				handle_events(t_context *ctx);
int					handle_enemy_collision(int x, int y, t_context *ctx);
void				move_player(int dx, int dy, t_context *ctx);
void				init_player_pos(t_context *ctx);

// gameover
int					timeout_hook(void *param);
void				init_end_window(void *mlx_ptr, t_end *go,
						const char *path, const char *title);
void				render_gameover(void *mlx_ptr, t_end *go);
void				cleanup_gameover(void *mlx_ptr, t_end *go);
void				handle_end(t_context *ctx, const char *path,
						const char *title);

// enemy_move
int					rng_next(t_context *ctx);
int					count_enemies(t_context *ctx);
void				fill_enemies(t_context *ctx);
void				move_one_enemy(t_context *ctx, int idx);
void				draw_enemies(t_context *ctx);
void				init_enemies(t_context *ctx);
int					enemy_loop_hook(void *param);

#endif

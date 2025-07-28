/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:02:05 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/25 11:18:26 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "libft.h"
# include "map_parser.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <mlx.h>
# include <stdlib.h>

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

typedef struct s_textures
{
	void		*wall;
	void		*floor;
	void		*player;
	void		*collectible;
	void		*exit;
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

void			init_graphics(void **mlx_ptr, void **win_ptr, int width,
					int height);
void			load_textures(void *mlx_ptr, t_textures *tx);
void			render_map(void *mlx_ptr, void *win_ptr, t_map *map,
					t_textures *tx);
void			cleanup_graphics(t_context *ctx);
int				on_keypress(int keycode, void *param);
int				on_destroy(int unused, void *param);
void			handle_events(t_context *ctx);
void			move_player(int dx, int dy, t_context *ctx);
void	init_player_pos(t_context *ctx);

#endif

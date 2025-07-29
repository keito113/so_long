/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 07:43:35 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/29 11:20:38 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_collectibles(t_map *map)
{
	int	row;
	int	col;
	int	count;

	row = 0;
	count = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (map->date[row][col] == 'C')
				count++;
			col++;
		}
		row++;
	}
	return (count);
}

int	main(int ac, char *av[])
{
	t_map		*map;
	t_context	ctx;
	t_textures	tx;

	if (ac != 2)
		error_exit("Usage: ./so_long <map.ber>");
	map = read_map(av[1]);
	ctx.map = map;
	ctx.collectable = count_collectibles(map);
	ctx.moves = 0;
	ctx.mlx_ptr = mlx_init();
	if (!ctx.mlx_ptr)
		error_exit("Mlx initialization failure");
	load_textures(ctx.mlx_ptr, &tx);
	ctx.tx = &tx;
	ctx.win_ptr = mlx_new_window(ctx.mlx_ptr, (map->width * tx.tile_w),
			(map->height * tx.tile_h), "so_long");
	if (!ctx.win_ptr)
		error_exit("Window creation failure");
	init_player_pos(&ctx);
	render_map(ctx.mlx_ptr, ctx.win_ptr, map, &tx);
	draw_move_count(&ctx);
	handle_events(&ctx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 07:43:35 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/31 11:39:35 by keitabe          ###   ########.fr       */
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

static void	init_context(int ac, char *av[], t_context *ctx, t_textures *tx)
{
	if (ac != 2)
		error_exit("Usage: ./so_long <map.ber>");
	ctx->map = read_map(av[1]);
	ctx->collectable = count_collectibles(ctx->map);
	*ctx = (t_context){.map = ctx->map, .collectable = ctx->collectable};
	ctx->mlx_ptr = mlx_init();
	if (!ctx->mlx_ptr)
		error_exit("Mlx initialization failure");
	*tx = (t_textures){0};
	load_textures(ctx->mlx_ptr, tx);
	ctx->tx = tx;
	ctx->win_ptr = mlx_new_window(ctx->mlx_ptr, (ctx->map->width * tx->tile_w),
			(ctx->map->height * tx->tile_h), "so_long");
	if (!ctx->win_ptr)
		error_exit("Window creation failure");
	init_player_pos(ctx);
}

int	main(int ac, char *av[])
{
	t_context	ctx;
	t_textures	tx;

	init_context(ac, av, &ctx, &tx);
	render_map(ctx.mlx_ptr, ctx.win_ptr, ctx.map, &tx);
	draw_move_count(&ctx);
	mlx_loop_hook(ctx.mlx_ptr, enemy_loop_hook, &ctx);
	handle_events(&ctx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 07:43:35 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/29 12:28:17 by keitabe          ###   ########.fr       */
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

static void	init_context(int ac, char *av[], t_context *ctx)
{
	int	w;
	int	h;

	if (ac != 2)
		fatal(NULL, ERR_GENERIC, "Usage: ./so_long <map.ber>");
	*ctx = (t_context){0};
	ctx->map = read_map(av[1]);
	ctx->collectable = count_collectibles(ctx->map);
	ctx->mlx_ptr = mlx_init();
	if (!ctx->mlx_ptr)
		fatal(ctx, ERR_MLX_INIT, "mlx_init failed");
	ctx->tx = malloc(sizeof(t_textures));
	if (!ctx->tx)
		fatal(ctx, ERR_ALLOC, "textures alloc failed");
	*ctx->tx = (t_textures){0};
	load_textures(ctx);
	w = ctx->map->width * ctx->tx->tile_w;
	h = ctx->map->height * ctx->tx->tile_h;
	ctx->win_ptr = mlx_new_window(ctx->mlx_ptr, w, h, "so_long");
	if (!ctx->win_ptr)
		fatal(ctx, ERR_MLX_WIN, "Window creation failure");
	init_player_pos(ctx);
}

int	main(int ac, char *av[])
{
	t_context	ctx;

	init_context(ac, av, &ctx);
	render_map(ctx.mlx_ptr, ctx.win_ptr, ctx.map, ctx.tx);
	draw_move_count(&ctx);
	mlx_loop_hook(ctx.mlx_ptr, enemy_loop_hook, &ctx);
	handle_events(&ctx);
	return (0);
}

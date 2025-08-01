/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:23:12 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/30 13:50:20 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_move_count(t_context *ctx)
{
	char	*moves_str;

	moves_str = ft_itoa(ctx->moves);
	if (!moves_str)
		error_exit("itoa failure");
	mlx_string_put(ctx->mlx_ptr, ctx->win_ptr, 10, 10, 0x00FFFFFF, moves_str);
	free(moves_str);
}

static void	apply_move_render(t_context *ctx)
{
	mlx_clear_window(ctx->mlx_ptr, ctx->win_ptr);
	render_map(ctx->mlx_ptr, ctx->win_ptr, ctx->map, ctx->tx);
	draw_move_count(ctx);
	draw_enemies(ctx);
}

static void	apply_move(int new_x, int new_y, t_context *ctx)
{
	if (handle_enemy_collision(new_x, new_y, ctx))
		return ;
	if (ctx->map->date[new_y][new_x] == 'E' && ctx->collectable > 0)
		return ;
	if (ctx->map->date[new_y][new_x] == 'C')
	{
		ctx->collectable--;
		ctx->map->date[new_y][new_x] = '0';
	}
	if (ctx->map->date[new_y][new_x] == 'E' && ctx->collectable == 0)
	{
		mlx_string_put(ctx->mlx_ptr, ctx->win_ptr, ctx->player_x, ctx->player_y,
			0x00FFFFFF, "Have a great camping trip!!");
		handle_end(ctx, "textures/clear.xpm", "Have a great camping trip!!");
	}
	if (ctx->map->date[new_y][new_x] == 'X')
		handle_end(ctx, "textures/game_over.xpm", "Game Over");
	ctx->map->date[ctx->player_y][ctx->player_x] = '0';
	ctx->map->date[new_y][new_x] = 'P';
	ctx->player_x = new_x;
	ctx->player_y = new_y;
	ctx->moves++;
	ft_putnbr_fd(ctx->moves, 1);
	ft_putchar_fd('\n', 1);
	apply_move_render(ctx);
}

void	move_player(int dx, int dy, t_context *ctx)
{
	int	new_x;
	int	new_y;

	new_x = ctx->player_x + dx;
	new_y = ctx->player_y + dy;
	if (new_x < 0 || new_x >= ctx->map->width || new_y < 0
		|| new_y >= ctx->map->height || ctx->map->date[new_y][new_x] == '1')
		return ;
	apply_move(new_x, new_y, ctx);
}

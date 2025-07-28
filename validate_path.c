/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:18:22 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/28 12:19:38 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	validate_path(const t_map *map)
{
	int			px;
	int			py;
	int			c_cnt;
	int			e_cnt;
	t_scan_map	*ctx;

	ctx->map = copy_map(map->date, map->height, map->width);
	ctx->width = map->width;
	ctx->height = map->height;
	find_player_position(map, &px, &py);
	flood_fill(&ctx, px, py);
	count_remaining(ctx, &c_cnt, &e_cnt);
	free_map_copy(ctx->map, ctx->height);
	if (c_cnt > 0 || e_cnt > 0)
		error_exit("No valid path");
}

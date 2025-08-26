/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:18:57 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/26 07:33:38 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_gameover(void *mlx_ptr, t_end *go)
{
	if (go->img_ptr)
	{
		mlx_destroy_image(mlx_ptr, go->img_ptr);
		go->img_ptr = NULL;
	}
	if (go->win_ptr)
	{
		mlx_destroy_window(mlx_ptr, go->win_ptr);
		go->win_ptr = NULL;
	}
}

int	timeout_hook(void *param)
{
	t_context		*ctx;
	t_end			*go;
	struct timeval	now;
	long			sec_diff;

	ctx = (t_context *)param;
	go = &ctx->end;
	if (gettimeofday(&now, NULL) < 0)
		return (0);
	sec_diff = (long)(now.tv_sec - go->start_tv.tv_sec);
	if ((sec_diff > (long)go->wait_time) || (sec_diff == (long)go->wait_time
			&& now.tv_usec >= go->start_tv.tv_usec))
		cleanup_graphics(ctx);
	return (0);
}

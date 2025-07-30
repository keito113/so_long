/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:18:57 by keitabe           #+#    #+#             */
/*   Updated: 2025/07/30 10:50:48 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_gameover(void *mlx_ptr, t_gameover *go)
{
	mlx_destroy_image(mlx_ptr, go->img_ptr);
	mlx_destroy_window(mlx_ptr, go->win_ptr);
}

int	read_uptime_seconds(void)
{
	int		fd;
	ssize_t	n;
	char	buf[32];
	int		sec;
	int		i;

	fd = open("/proc/uptime", O_RDONLY);
	if (fd < 0)
		error_exit("open /proc/uptime failed");
	n = read(fd, buf, sizeof(buf) - 1);
	if (n <= 0)
		error_exit("read /proc/uptime failed");
	buf[n] = '\0';
	sec = 0;
	i = 0;
	while (buf[i] >= '0' && buf[i] <= '9')
	{
		sec = sec * 10 + (buf[i] - '0');
		i++;
	}
	close(fd);
	return (sec);
}

int	timeout_hook(void *param)
{
	t_context	*ctx;
	t_gameover	*go;

	ctx = (t_context *)param;
	go = &ctx->gameover;
	if (read_uptime_seconds() - go->start_sec >= 3)
	{
		cleanup_gameover(ctx->mlx_ptr, go);
		exit(0);
	}
	return (0);
}

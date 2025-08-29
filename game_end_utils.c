/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:18:57 by keitabe           #+#    #+#             */
/*   Updated: 2025/08/29 12:28:44 by keitabe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	timeout_hook(void *param)
{
	t_context		*ctx;
	t_end			*go;
	struct timeval	now;
	long			sec_diff;

	ctx = (t_context *)param;
	go = &ctx->end;
	if (gettimeofday(&now, NULL) < 0)
		fatal(ctx, ERR_GENERIC, "gettimeofday failure");
	sec_diff = (long)(now.tv_sec - go->start_tv.tv_sec);
	if ((sec_diff > (long)go->wait_time) || (sec_diff == (long)go->wait_time
			&& now.tv_usec >= go->start_tv.tv_usec))
	{
		app_destroy(ctx);
		exit(0);
	}
	return (0);
}

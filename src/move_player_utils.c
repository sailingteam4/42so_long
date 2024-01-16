/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:39:05 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/04 16:58:24 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_data *data, int x, int y)
{
	if (data->game->map[y - 1][x] == 0)
		data->game->player.y -= 1;
}

void	move_down(t_data *data, int x, int y)
{
	if (data->game->map[y + 1][x] == 0)
		data->game->player.y += 1;
}

void	move_left(t_data *data, int x, int y)
{
	if (data->game->map[y][x - 1] == 0)
		data->game->player.x -= 1;
}

void	move_right(t_data *data, int x, int y)
{
	if (data->game->map[y][x + 1] == 0)
		data->game->player.x += 1;
}

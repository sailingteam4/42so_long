/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:28:09 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/04 19:54:01 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	had_move(t_data *data, int x, int y)
{
	if (data->game->player.x != x || data->game->player.y != y)
	{
		data->game->player_move++;
		ft_putnbr_fd(data->game->player_move, 1);
		ft_putendl_fd("", 1);
	}
}

static void	collect(t_data *data)
{
	int				k;

	k = 0;
	while (k < data->game->count_coll)
	{
		if (data->game->coll[k].x == data->game->player.x
			&& data->game->coll[k].y == data->game->player.y)
		{
			data->game->coll[k].x = -1;
			data->game->coll[k].y = -1;
			data->game->player_coll++;
		}
		k++;
	}
}

void	move_player(t_data *data)
{
	int				x;
	int				y;

	x = data->game->player.x;
	y = data->game->player.y;
	if (data->game->player_up != 0)
		move_up(data, x, y);
	else if (data->game->player_down != 0)
		move_down(data, x, y);
	else if (data->game->player_left != 0)
		move_left(data, x, y);
	else if (data->game->player_right != 0)
		move_right(data, x, y);
	had_move(data, x, y);
	collect(data);
	put_img_to_window(data);
	if (data->game->exit.x == data->game->player.x
		&& data->game->exit.y == data->game->player.y)
		if (data->game->count_coll == data->game->player_coll)
			data_clear(data, 0, 0);
}

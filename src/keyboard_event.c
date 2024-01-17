/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:25:41 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/17 14:34:38 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		data_clear(data, 0, 0);
	if (keycode == 119)
		data->game->player_up = 1;
	if (keycode == 115)
		data->game->player_down = 1;
	if (keycode == 97)
		data->game->player_left = 1;
	if (keycode == 100)
		data->game->player_right = 1;
	move_player(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->game->player_up = 0;
	if (keycode == 115)
		data->game->player_down = 0;
	if (keycode == 97)
		data->game->player_left = 0;
	if (keycode == 100)
		data->game->player_right = 0;
	move_player(data);
	return (0);
}

int	destroy_hook(t_data *data)
{
	data_clear(data, 0, 0);
	return (0);
}

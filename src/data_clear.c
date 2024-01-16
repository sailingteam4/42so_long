/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:43:05 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/16 12:36:41 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	game_destroy(t_game *game)
{
	int				i;

	if (game != 0)
	{
		if (game->coll != 0)
			free(game->coll);
		if (game->map != 0)
		{
			i = 0;
			while (i < game->height)
				free(game->map[i++]);
			free(game->map);
		}
		free(game);
	}
}

void	data_clear(t_data *data, char *msg, int error)
{
	if (data != 0)
	{
		if (data->ground != 0)
			mlx_destroy_image(data->mlx, data->ground);
		if (data->wall != 0)
			mlx_destroy_image(data->mlx, data->wall);
		if (data->coll != 0)
			mlx_destroy_image(data->mlx, data->coll);
		if (data->exit != 0)
			mlx_destroy_image(data->mlx, data->exit);
		if (data->player != 0)
			mlx_destroy_image(data->mlx, data->player);
		if (data->mlx_img != 0)
			mlx_destroy_image(data->mlx, data->mlx_img);
		if (data->mlx_win != 0 && data->mlx != 0)
		{
			mlx_destroy_window(data->mlx, data->mlx_win);
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
		if (data->game != 0)
			game_destroy(data->game);
		free(data);
	}
	end(msg, error);
}

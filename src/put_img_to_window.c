/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img_to_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 00:00:20 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/04 00:19:40 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_square_to_window(t_data *data, t_img *img, int x, int y)
{
	unsigned int	color;
	int				i;
	int				j;

	j = 0;
	while (j < 40)
	{
		i = 0;
		while (i < 40)
		{
			color = mlx_get_pixel(img, i, j);
			if (color != mlx_rgb_to_int(0, 255, 255, 255))
				mlx_draw_pixel(data->mlx_img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

static void	put_obj_to_window(t_data *data, int i, int j)
{
	int				k;

	if (data->game->exit.x == i && data->game->exit.y == j)
		put_square_to_window(data, data->exit, i * 40, j * 40);
	k = -1;
	while (++k < data->game->count_coll)
		if (data->game->coll[k].x == i && data->game->coll[k].y == j)
			put_square_to_window(data, data->coll, i * 40, j * 40);
	if (data->game->player.x == i && data->game->player.y == j)
		put_square_to_window(data, data->player, i * 40, j * 40);
}

static void	put_map_to_window(t_data *data)
{
	int				i;
	int				j;

	j = 0;
	while (j < data->game->height)
	{
		i = 0;
		while (i < data->game->width)
		{
			if (data->game->map[j][i] == 1)
				put_square_to_window(data, data->wall, i * 40, j * 40);
			else
				put_square_to_window(data, data->ground, i * 40, j * 40);
			put_obj_to_window(data, i, j);
			i++;
		}
		j++;
	}
}

void	put_img_to_window(t_data *data)
{
	put_map_to_window(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->mlx_img, 0, 0);
}

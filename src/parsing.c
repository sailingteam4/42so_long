/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 23:10:51 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/03 23:21:34 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	tab_clear(t_data *data, char *file, int **m, int size)
{
	int				i;

	i = 0;
	while (i < size)
		free(m[i++]);
	free(m);
	data->game->map = 0;
	free(file);
	data_clear(data, "Error in map parsing", errno);
}

static void	get_coord(t_data *data, char *file, int k, int *obj)
{
	if (file[k] == 'P')
	{
		data->game->player.x = k % (data->game->width + 1);
		data->game->player.y = k / (data->game->width + 1);
		file[k] = '0';
	}
	else if (file[k] == 'E')
	{
		data->game->exit.x = k % (data->game->width + 1);
		data->game->exit.y = k / (data->game->width + 1);
		file[k] = '0';
	}
	else if (file[k] == 'C')
	{
		data->game->coll[*obj].x = k % (data->game->width + 1);
		data->game->coll[*obj].y = k / (data->game->width + 1);
		file[k] = '0';
		(*obj)++;
	}
}

void	parse_map(t_data *data, char *file)
{
	int				i;
	int				j;
	int				k;
	int				obj;

	obj = 0;
	k = 0;
	j = -1;
	while (++j < data->game->height)
	{
		data->game->map[j] = (int *)malloc(sizeof(int) * data->game->width);
		if (data->game->map[j] == 0)
			tab_clear(data, file, data->game->map, j);
		i = 0;
		while (i < data->game->width)
		{
			get_coord(data, file, k, &obj);
			data->game->map[j][i++] = file[k++] - 48;
		}
		k++;
	}
}

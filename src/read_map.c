/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:30:35 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/16 12:19:49 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;

	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

static void	calc_width(t_data *data, char *file)
{
	data->game->width = 0;
	while (file[data->game->width] && file[data->game->width] != '\n')
		data->game->width++;
	if (data->game->width == 0 || file[data->game->width] == 0)
	{
		free(file);
		data_clear(data, "map file invalid", 0);
	}
}

static void	calc_height(t_data *data, char *file)
{
	int				i;
	int				j;
	int				file_len;

	data->game->height = 1;
	i = data->game->width + 1;
	file_len = ft_strlen(file);
	while (i < file_len && file[i] != '\0')
	{
		j = 0;
		while (i + j < file_len && file[i + j] != '\0'
			&& file[i + j] != '\n')
			j++;
		if (data->game->width != j)
		{
			free(file);
			data_clear(data, "map format is invalid", 0);
		}
		i += data->game->width + 1;
		data->game->height++;
	}
}

void	read_map(t_data *data, char *file)
{
	calc_width(data, file);
	calc_height(data, file);
	check_map(data, file);
	data->game->coll
		= (t_coord *)malloc(sizeof(t_coord) * data->game->count_coll);
	if (data->game->coll == 0)
	{
		free(file);
		data_clear(data, "Malloc in map parsing", errno);
	}
	data->game->map = (int **)malloc(sizeof(int *) * data->game->height);
	if (data->game->map == 0)
	{
		free(file);
		data_clear(data, "Malloc in map parsing", errno);
	}
	parse_map(data, file);
}

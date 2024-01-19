/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 22:46:45 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/19 15:32:30 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	isvalid(t_data *data, char *file, int i)
{
	if (file[i] == 'P')
		data->game->count_player++;
	else if (file[i] == 'E')
		data->game->count_exit++;
	else if (file[i] == 'C')
		data->game->count_coll++;
	else if (file[i] == '1' || file[i] == '0')
		return ;
	else
	{
		free(file);
		data_clear(data, "map content is invalid", 0);
	}
}

static int	isborder(t_data *data, int i)
{
	if (i < data->game->width
		|| i > (data->game->width + 1) * (data->game->height - 1)
		|| i % (data->game->width + 1) == 0
		|| i % (data->game->width + 1) == data->game->width - 1)
		return (1);
	return (0);
}

static void	dfs(t_game *game, int x, int y, int **visited)
{
	if (x < 0 || y < 0 || x >= game->width || y >= game->height
		|| visited[y][x] || game->map[y][x] == 1)
		return ;
	visited[y][x] = 1;
	dfs(game, x - 1, y, visited);
	dfs(game, x + 1, y, visited);
	dfs(game, x, y - 1, visited);
	dfs(game, x, y + 1, visited);
}

int	check_path(t_game *game)
{
	int	**visited;
	int	i;

	visited = malloc(game->height * sizeof(int *));
	i = 0;
	while (i < game->height)
	{
		visited[i] = calloc(game->width, sizeof(int));
		i++;
	}
	dfs(game, game->player.x, game->player.y, visited);
	i = 0;
	while (i < game->count_coll)
	{
		if (!visited[game->coll[i].y][game->coll[i].x])
		{
			return (free_visited(visited, game->height), 0);
		}
		i++;
	}
	if (!visited[game->exit.y][game->exit.x])
		return (free_visited(visited, game->height), 0);
	return (free_visited(visited, game->height), 1);
}

void	check_map(t_data *data, char *file)
{
	int				i;

	i = -1;
	while (file[++i] != 0)
	{
		if (file[i] == '\n')
			continue ;
		if (isborder(data, i))
		{
			if (file[i] != '1')
			{
				free(file);
				data_clear(data, "map isn't surrounded by walls", 0);
			}
		}
		else
			isvalid(data, file, i);
	}
	if (data->game->count_player != 1
		|| data->game->count_exit != 1
		|| data->game->count_coll < 1)
	{
		free(file);
		data_clear(data, "map configuration is invalid", 0);
	}
}

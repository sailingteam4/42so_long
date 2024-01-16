/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:39:46 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/11 15:43:51 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_data *data, char *filename)
{
	data->game = (t_game *)malloc(sizeof(t_game));
	if (data->game == 0)
		data_clear(data, "Game init malloc", errno);
	data->game->map = 0;
	data->game->coll = 0;
	data->game->count_coll = 0;
	data->game->count_exit = 0;
	data->game->count_player = 0;
	data->game->player_move = 0;
	data->game->player_coll = 0;
	data->game->player_up = 0;
	data->game->player_down = 0;
	data->game->player_left = 0;
	data->game->player_right = 0;
	init_map(data, filename);
}

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == 0)
		data_clear(data, "Can't load mlx", 0);
	data->mlx_win = mlx_new_window(data->mlx, data->game->width * 40,
			data->game->height * 40, "so_long");
	if (data->mlx_win == 0)
		data_clear(data, "Can't create a window", 0);
	data->mlx_img = mlx_new_image(data->mlx, data->game->width * 40,
			data->game->height * 40);
	if (data->mlx_img == 0)
		data_clear(data, "Can't create an image", 0);
}

static void	texture_load(t_data *data, t_img **img, char *path)
{
	int				width;
	int				height;

	*img = mlx_xpm_file_to_image(data->mlx, path, &width, &height);
	if (*img == 0)
		data_clear(0, "Can't load texture", 0);
	(*img)->width = width;
	(*img)->height = height;
}

static void	init_img(t_data *data)
{
	texture_load(data, &data->player, "./ressources/player.xpm");
	texture_load(data, &data->exit, "./ressources/exit.xpm");
	texture_load(data, &data->coll, "./ressources/cone.xpm");
	texture_load(data, &data->wall, "./ressources/wall.xpm");
	texture_load(data, &data->ground, "./ressources/ground.xpm");
}

t_data	*init_data(char *filename)
{
	t_data			*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == 0)
		data_clear(0, "Data malloc creation", errno);
	data->game = 0;
	data->mlx = 0;
	data->mlx_win = 0;
	data->mlx_img = 0;
	data->player = 0;
	data->exit = 0;
	data->coll = 0;
	data->wall = 0;
	data->ground = 0;
	init_game(data, filename);
	init_mlx(data);
	init_img(data);
	return (data);
}

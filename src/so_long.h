/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:15:00 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/17 14:33:11 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "../libft/libft.h"

void			end(char *msg, int error);

typedef struct s_coord
{
	int				x;
	int				y;
}				t_coord;

typedef struct s_game
{
	int				**map;
	int				height;
	int				width;
	t_coord			player;
	int				player_up;
	int				player_down;
	int				player_left;
	int				player_right;
	int				player_move;
	int				player_coll;
	t_coord			exit;
	t_coord			*coll;
	int				count_coll;
	int				count_exit;
	int				count_player;
}				t_game;

typedef struct s_data
{
	void			*mlx;
	void			*mlx_win;
	t_img			*mlx_img;
	t_game			*game;
	t_img			*player;
	t_img			*exit;
	t_img			*coll;
	t_img			*wall;
	t_img			*ground;
}				t_data;

unsigned int	mlx_rgb_to_int(int o, int r, int g, int b);
void			mlx_draw_pixel(t_img *mlx_img, int x, int y, int color);
unsigned int	mlx_get_pixel(t_img *img, int x, int y);

t_data			*init_data(char *filename);
void			free_visited(int **visited, int height);
void			data_clear(t_data *data, char *msg, int error);
void			init_map(t_data *data, char *filename);
void			read_map(t_data *data, char *file);
void			check_map(t_data *data, char *file);
void			parse_map(t_data *data, char *file);
int				check_path(t_game *game);
void			put_img_to_window(t_data *data);
void			move_player(t_data *data);
void			move_up(t_data *data, int x, int y);
void			move_down(t_data *data, int x, int y);
void			move_left(t_data *data, int x, int y);
void			move_right(t_data *data, int x, int y);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				destroy_hook(t_data *data);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:14:04 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/16 14:32:43 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	isber(char *file)
{
	int				len;

	len = ft_strlen(file);
	if (file == 0)
		return (0);
	if (len < 5)
		return (0);
	if (ft_strcmp(file + len - 4, ".ber") != 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data			*data;

	if (ac != 2)
		end("Hold up, invalid number of args", 0);
	if (isber(av[1]) == 0)
		end("Hop Hop Hop invalid file ext (<name>.ber)", 0);
	data = init_data(av[1]);
	put_img_to_window(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx_win, 17, 1L << 17, destroy_hook, data);
	mlx_loop(data->mlx);
	return (0);
}

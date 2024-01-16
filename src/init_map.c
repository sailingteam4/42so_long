/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:04:28 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/16 12:10:10 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*init_file(t_data *data, int fd)
{
	char			*file;

	file = ft_calloc(1, 1);
	if (file == 0)
	{
		close(fd);
		data_clear(data, "Map init calloc", errno);
	}
	return (file);
}

static void	parse_file(t_data *data, char **file, char *buf, int fd)
{
	char			*tmp;

	tmp = ft_strjoin(*file, buf);
	free(*file);
	*file = tmp;
	if (*file == 0)
	{
		close(fd);
		data_clear(data, "Strjoin on map init", errno);
	}
}

static void	read_file(t_data *data, char **file, char *buf, int fd)
{
	int				ret;

	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, buf, 1024);
		if (ret == -1)
		{
			free(*file);
			close(fd);
			data_clear(data, "Read on map init", errno);
		}
		else
		{
			buf[ret] = 0;
			parse_file(data, file, buf, fd);
		}
	}
}

void	init_map(t_data *data, char *filename)
{
	int			fd;
	char		*file;
	char		buf[1024 + 1];
	int			is_path_valid;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		data_clear(data, filename, errno);
	file = init_file(data, fd);
	read_file(data, &file, buf, fd);
	close(fd);
	read_map(data, file);
	free(file);
	is_path_valid = check_path(data->game);
	if (!is_path_valid)
		data_clear(data, "Player can't reach all collectibles and exit", 0);
}

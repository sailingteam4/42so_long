/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontey <nrontey@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:19:09 by nrontey           #+#    #+#             */
/*   Updated: 2024/01/03 12:27:13 by nrontey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	end(char *msg, int error)
{
	if (msg != 0 || error != 0)
		ft_putendl_fd("Error", 0);
	if (msg != 0)
		ft_putstr_fd(msg, 0);
	if (msg != 0 && error != 0)
		ft_putstr_fd(": ", 2);
	if (error != 0)
		ft_putstr_fd(strerror(error), 0);
	if (msg != 0 || error != 0)
	{
		ft_putendl_fd("", 0);
		exit(1);
	}
	exit(0);
}

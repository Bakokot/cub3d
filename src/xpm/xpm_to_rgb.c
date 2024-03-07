/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:45:33 by tbarde-c          #+#    #+#             */
/*   Updated: 2024/03/07 16:28:06 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	xpm_to_rgb(t_cardinal *xpm)
{
	t_color_table	*color_table;
	char			*temp;
	char			*name;

	temp = ft_strdup(xpm->cardinal_str + 3);
	name = ft_strtrim(temp, " \t");
	free(temp);
	//printf("%s\n", name);
	xpm->fd = open(name, O_RDONLY);
	if (xpm->fd == -1)
	{
		close(xpm->fd);
		return (perror(ERR_OPEN), NULL);
	}
	color_table = get_color_table(xpm);
	if (color_table == NULL)
	{
		close(xpm->fd);
		return (false);
	}
	fill_xpm_rgb(xpm, color_table);
	free_color_table(color_table, xpm);
	close(xpm->fd);
	return (true);
}

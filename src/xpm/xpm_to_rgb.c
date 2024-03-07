/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:45:33 by tbarde-c          #+#    #+#             */
/*   Updated: 2024/03/07 14:48:13 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*xpm_to_rgb(t_cardinal *xpm)
{
	t_color_table	*color_table;
	char *name = ft_strtrim(ft_strdup(xpm->cardinal_str + 3), " ");

	xpm->fd = open(name, O_RDONLY);
	if (xpm->fd == -1)
		return (perror(ERR_OPEN), NULL);
	color_table = get_color_table(xpm);
	if (color_table == NULL)
		return (NULL);
	fill_xpm_rgb(xpm, color_table);
	free_color_table(color_table, xpm);
	return (NULL);
}

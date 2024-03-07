/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:49:28 by tbarde-c          #+#    #+#             */
/*   Updated: 2024/03/07 16:28:21 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_color_table	*malloc_color_table(t_color_table *color_table, int nb_of_colors)
{
	int	i;

	color_table = malloc(sizeof(t_color_table) * nb_of_colors);
	i = 0;
	while (i < nb_of_colors)
	{
		color_table[i].red_hex = malloc(sizeof(char) * 3);
		color_table[i].green_hex = malloc(sizeof(char) * 3);
		color_table[i].blue_hex = malloc(sizeof(char) * 3);
		i++;
	}
	return (color_table);
}
/**
 * Treat the case :
 * "[char] c #[six_digit_hex_code]"
*/
static void	copy_with_hashtag(t_color_table *color_table, char *line, int i)
{
	ft_strlcpy(color_table[i].red_hex, line + 6, 3);
	color_table[i].red = ft_atoi_base(color_table[i].red_hex, "0123456789ABCDEF");
	ft_strlcpy(color_table[i].green_hex, line + 8, 3);
	color_table[i].green = ft_atoi_base(color_table[i].green_hex, "0123456789ABCDEF");
	ft_strlcpy(color_table[i].blue_hex, line + 10, 3);
	color_table[i].blue = ft_atoi_base(color_table[i].blue_hex, "0123456789ABCDEF");
}

/*
 *	Treat the case : 
 *	"[char] c gray[two_digit_hex_code]"
*/
static void	copy_gray(t_color_table *color_table, char *line, int i)
{
	ft_strlcpy(color_table[i].red_hex, line + 9, 3);
	color_table[i].red = ft_atoi_base(color_table[i].red_hex, "0123456789ABCDEF");
	ft_strlcpy(color_table[i].green_hex, line + 9, 3);
	color_table[i].green = ft_atoi_base(color_table[i].green_hex, "0123456789ABCDEF");
	ft_strlcpy(color_table[i].blue_hex, line + 9, 3);
	color_table[i].blue = ft_atoi_base(color_table[i].blue_hex, "0123456789ABCDEF");
}

/**
 * An xpm file line looks like that : 
 * "[char] c #[six_digit_hex_code]"
 * OR
 * "[char] c gray[two_digit_hex_code]"
*/
static t_color_table	*fill_color_table(t_cardinal *xpm, t_color_table *color_table)
{
	char	*line;
	int		i;

	color_table = malloc_color_table(color_table, xpm->nb_of_colors);
	i = 0;
	line = get_next_line(xpm->fd);
	while (i < xpm->nb_of_colors)
	{
		if (!line)
			return (ft_printf(2, ERR_XPM_INVALID, xpm->cardinal_str), NULL);
		color_table[i].c = line[1];
		if (ft_strchr(line, '#') != NULL)
			copy_with_hashtag(color_table, line, i);
		else
			copy_gray(color_table, line, i);
		color_table[i].rgb = (color_table[i].red << 16) | (color_table[i].green << 8) | (color_table[i].green);
		free(line);
		line = get_next_line(xpm->fd);
		i++;
	}
	free(line);
	return (color_table);
}

/**
 * Get the color table from the xpm file : 
 * - We associate each char with an rgb code
*/
t_color_table *get_color_table(t_cardinal *xpm)
{
	int					infos;
	t_color_table		*color_table;

	infos = NOT_RECOVERED;
	color_table = NULL;
	while (infos == NOT_RECOVERED)
		infos = get_xpm_infos(xpm);
	if (infos == NO_INFO)
		return (NULL);
	color_table = fill_color_table(xpm, color_table);
	if (color_table == NULL)
		return (NULL);
	return (color_table);
}

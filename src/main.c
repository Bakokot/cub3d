/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:11:40 by tbarde-c          #+#    #+#             */
/*   Updated: 2024/02/09 19:20:23 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	//t_textures	textures;
	int			fd;

	if (input_ok(argc, argv) == false)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, ERR_OPEN, argv[1]), 0);
	(void)fd;
	//get_textures(fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:11:16 by tbarde-c          #+#    #+#             */
/*   Updated: 2024/03/07 14:57:18 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D__H
# define CUB3D__H

#include <math.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>

#include "../libft/inc/libft.h"
#include "../libft/inc/ft_printf.h"
#include "../minilibx-linux/mlx.h"

/**
 * XPM INFOS RECOVERED ?
*/
# define NOT_RECOVERED 0
# define RECOVERED 1
# define NO_INFO 2

/**
 * ERROR MESSAGES
*/
# define INP_USAGE "[usage] : ./cub3d <file.cub>\n"
# define INP_FILENAME "File must be a .cub file\n"

# define ERR_FILEPATH_CONTENT "Error: there is no filepath in '%s'\n"

# define ERR_MAP_CHAR "Error: invalid char '%c' in map\n"
# define ERR_MAP_CLOSED "Error: the map isn't closed\n"
# define ERR_MAP_EMPTY "Error: the map contains empty lines\n"
# define ERR_MAP_NULL "Error: there is no map\n"
# define ERR_MAP_SPAWN_NBR "Error: invalid number of spawns\n"
# define ERR_MAP_SPAWN_LOC "Error: spawn in invalid location\n"

# define ERR_OPEN "Couldn't open data file"

# define ERR_RGB_NBR "Error: RGB code is invalid in '%s'\n"

# define ERR_TEXTURES_NBR "Error: Cub3d couldn't get 6 ligns to read textures\n"
# define ERR_TEXTURES_CONTENT "Error: One of the six first ligns contains an unknown identifier or has a duplicate\n"
# define ERR_TEXTURES_XPM "Error: the file '%s' isn't a .xpm file\n"

# define ERR_XPM_EMPTY "Error: the file '%s' is empty\n"
# define ERR_XPM_INVALID "Error: the file '%s' has invalid info\n"
/**
 * Defines
*/
# define NOTHING 'x'

# define screenwidth 1920
# define screenheight 1080
# define texWidth 64
# define texHeight 64

/**
 * Textures structure
*/
typedef struct s_rgb
{
	char	*rgb_str;
	int		red;
	int		blue;
	int		green;
	int		color;
}	t_rgb;

typedef struct s_cardinal
{
	char	*cardinal_str;
	int		fd;
	int		**rgb;
	int		height;
	int		width;
	int		nb_of_colors;
}	t_cardinal;

typedef struct s_textures
{
	t_cardinal	north;
	t_cardinal	south;
	t_cardinal	east;
	t_cardinal	west;
	t_rgb		floor;
	t_rgb		ceiling;
}	t_textures;

typedef struct s_player
{
	double	dirX;
	double	dirY;
	double	posX;
	double	posY;
	double	planeX;
	double	planeY;
}	t_player;

typedef struct s_ray
{
	int		mapX;			//represents current pos
	int		mapY;			//of ray in the map[][]
	int		side;			//was a NS or a EW wall hit?
	int		stepX;			//left = -1/ right = +1
	int		stepY;
	int		color;
	double	cameraX;		//X-coordinate represents on screen
	double	rayDirY;		//ray = dir of vision + (camera plan * cameraX) --> rotate dir by certain angle
	double	rayDirX;		//Vector direction of
	double	deltaDistX;		//Distance to next border-line
	double	deltaDistY;		//from a border-line
	double	sideDistX;		//Distance to next border-line
	double	sideDistY;		//from current pos
	double	perpWallDist;	//length of ray from camera plane --> not player pos because fisheye effect
}	t_ray;

typedef struct s_map
{
	char		**str;
	char		**str_rectangle;
	int			nbr_column;
	int			nbr_line;
	int			longest_line_index;
	int			minimap;
	t_textures	textures;
}	t_map;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	t_image		img;
}	t_mlx;

typedef struct s_data
{
	int			textures[8][texWidth * texHeight];
	t_mlx		mlx;
	t_map		map;
	t_ray		ray;
	t_player	player;
}	t_data;

typedef struct	s_color_table
{
	char	c;
	int		rgb;
	char	*red_hex;
	char	*green_hex;
	char	*blue_hex;
	int		red;
	int		green;
	int		blue;
}	t_color_table;

/********************************************************
					Debug
*********************************************************/
void			print_textures_str(t_textures textures);
void			print_rgbs(t_textures textures);
void			print_map(t_map map, t_player player);
void			print_xpm_infos(t_cardinal xpm);
void			print_color_table(t_color_table table);
void			print_xpm_rgb(t_cardinal *xpm);

/********************************************************
					String Manipulation
*********************************************************/
bool			ft_isspace(char c);
bool			line_empty(char *line);
void			remove_backslash_n(char **str);
bool			ft_strstr_last(char *str, char *to_find);
int				countchar(char *str, char c);
int				ft_atoi_base(char *str, char *base);
char		*ft_strtrim_ending(char const *s1, char const *set);

/********************************************************
					Cleaning
*********************************************************/
void			free_textures(t_textures *textures);
void			free_split(char **rgb);
void			free_map(t_map *map);
bool			finish_reading_file(int fd);
void			free_xpm_rgb(t_textures *textures);
void			free_color_table(t_color_table *table, t_cardinal *xpm);
void			free_xpm_rgb(t_textures *textures);

/********************************************************
					Input checking
*********************************************************/
bool	input_ok(int argc, char **argv, int *fd);

/********************************************************
					Parsing
*********************************************************/

char			*skip_empty_lines(int fd);

//	--- Textures ---
bool	get_textures(int fd, t_textures *textures);
bool	fill_textures(t_textures *textures, char **textures_info);
bool	check_textures(t_textures *textures);
bool	check_filepath(t_cardinal *cardinal);
bool	check_rgb(t_rgb *texture);
bool	is_cardinal(char *str, char *cardinal);
bool	is_north(char *str);
bool	is_south(char *str);
bool	is_east(char *str);
bool	is_west(char *str);
bool	is_floor(char *str);
bool	is_ceiling(char *str);

//	---	Map	---
bool	get_map(int fd, t_map *map);
bool	check_map(t_map *map, t_player *player);
bool	check_map_char(t_map *map, t_player *player);
bool	is_player(char c);
void	make_map_rectangular(t_map *map);
bool	check_map_closed(t_map *map, char **map_rectangle);

/********************************************************
  					XPM
*********************************************************/
int    			rgb_to_int(char *str);
int				get_xpm_infos(t_cardinal *xpm);
bool			xpm_to_rgb(t_cardinal *xpm);
t_color_table	*get_color_table(t_cardinal *xpm);
void			fill_xpm_rgb(t_cardinal *xpm, t_color_table *table);

/********************************************************
					MLX
*********************************************************/
bool	init_mlx(t_data *data);
int		key_input(int key, t_data *data);
void	raycasting(t_data *data);
void	trace(t_image img, int x1, int y1, int x2, int y2, int color);
int		my_mlx_pixel_put(t_image img, int x, int y, int color);
void	free_mlx(t_mlx mlx);
void	minimap(t_data *data);

#endif

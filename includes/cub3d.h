/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:30:03 by zouddach          #+#    #+#             */
/*   Updated: 2024/09/17 00:37:21 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/mlx.h"
# include "../gnl/get_next_line_bonus.h"
# include "../libft/libft.h"
#include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_point
{
	int x;
	int y;
}				t_point;

typedef struct s_ray
{
	double	angle;
	double	dist;
	int		hit;
	int		wallHitX;
	int		wallHitY;
	int		wallContent;
}				t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}				t_mlx;

typedef struct s_map
{
	int 	fd;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*C;
	char	*F;
	int		rows;
	int		cols;
}				t_map;

typedef struct s_player
{
	t_point	pos;
	double	dir;
	double	fov;
}				t_player;

typedef struct s_game
{
	t_mlx		mlx;
	t_data		img;
	t_player	player;
	t_map		map;
	t_map		check_map;
}				t_game;

#endif
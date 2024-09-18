/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:30:03 by zouddach          #+#    #+#             */
/*   Updated: 2024/09/18 02:36:12 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../gnl/get_next_line_bonus.h"
# include "/usr/local/include/mlx.h"
#include "../libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

# define ESCAPE_BUTTON 53
# define W_BUTTON 13
# define A_BUTTON 0
# define S_BUTTON 1
# define D_BUTTON 2
# define UP_BUTTON 126
# define DOWN_BUTTON 125
# define LEFT_BUTTON 123
# define RIGHT_BUTTON 124
# define QUIT_BUTTON 12

typedef struct s_point {
  int x;
  int y;
} t_point;

typedef struct s_ray {
  double angle;
  double dist;
  int hit;
  int wallHitX;
  int wallHitY;
  int wallContent;
} t_ray;

typedef struct s_data {
  int width;
  int height;
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
} t_data;

typedef struct s_mlx {
  void *mlx;
  void *win;
} t_mlx;

typedef struct s_map {
  int fd;
  char **map;
  char *no;
  char *so;
  char *we;
  char *ea;
  char *C;
  char *F;
  int rows;
  int maxCols;
} t_map;

typedef struct s_player {
  t_point pos;
  double dir;
  double fov;
} t_player;

typedef struct s_texture {
  t_data no;
  t_data so;
  t_data we;
  t_data ea;
} t_texture;

typedef struct s_setting {
  int width;
  int height;
  char *title;
  long player_speed;
  t_mlx mlx;
} t_setting;

typedef struct s_game {
  t_mlx mlx;
  t_texture walls;
  t_player player;
  t_map map;
  t_map check_map;
  t_setting setting;
} t_game;

int count_char(char *str, char c);
char *ft_replace(char *str, char c, char *news);
int dump_spaces(char **line);
int ft_line_value(char *line, char **value);
int check_map(t_game *game);
void ft_cut_char(char *str, char c);

#endif
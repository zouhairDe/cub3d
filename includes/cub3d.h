/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:30:03 by zouddach          #+#    #+#             */
/*   Updated: 2024/09/21 21:32:13 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../gnl/get_next_line_bonus.h"
# include "mlx.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024
# define MINIMAP_WIDTH 250
# define MINIMAP_HEIGHT 250
# define SCALE 10
# define MINIMAP_SCALE 20
# define RAY_STEP 0.1
# define NUM_RAYS WINDOW_WIDTH

typedef struct s_point {
  int x;
  int y;
} t_point;

typedef struct s_ray {
  double x;
  double y;
  double dir;
  double angle;
  double dist;
  int hit;
  int wallHitX;
  int wallHitY;
  int wallContent;
  double wallStripHeight;
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
  t_data data;
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
  double x;
  double y;
  double dir;
  double fov;
  double moveSpeed;
  double rotSpeed;
} t_player;

typedef struct s_texture {
  t_data no;
  t_data so;
  t_data we;
  t_data ea;
  unsigned int ceilling;
  unsigned int floor;
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
int	simulate(t_game *game);
void printGame(t_game game);
unsigned int rgb_to_hex(int r, int g, int b);
int twoDArrSize(char **arr);
double normalizeAngle(double angle);
void	drawWalls(t_game *game, t_ray *ray);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	cast_ray(t_game *game);

#endif
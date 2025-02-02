/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:30:03 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/02 06:40:20 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../../gnl/get_next_line_bonus.h"
# include "../../mlx/mlx.h"
# include "../../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>

#define DEG_TO_RAD(angle) ((double)(angle) * M_PI / 180.0)
#define RAD_TO_DEG(angle) ((double)(angle) *  180.0 / M_PI)

# define ESCAPE_BUTTON 53
# define W_BUTTON 13
# define A_BUTTON 0
# define S_BUTTON 1
# define D_BUTTON 2
# define H_BUTTON 4
# define UP_BUTTON 126
# define ON_MOUSEMOVE 6
# define DOWN_BUTTON 125
# define LEFT_BUTTON 123
# define RIGHT_BUTTON 124
# define QUIT_BUTTON 12

# define FOV DEG_TO_RAD(60)

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024
# define MINIMAP_SCALE 32
# define MINIMAP_WIDTH  (MINIMAP_SCALE*8)
# define MINIMAP_HEIGHT (MINIMAP_SCALE*8)
# define RAY_STEP 0.1
# define NUM_RAYS WINDOW_WIDTH
# define WALL_SIZE 64
# define center_x (MINIMAP_WIDTH / 2)
# define center_y (MINIMAP_HEIGHT / 2)
#define win_center_x (WINDOW_WIDTH / 2)
#define win_center_y (WINDOW_HEIGHT / 2)


// USED FOR WALL FACE RENDERING.
# define N 0
# define E 1
# define S 2
# define W 3

typedef struct s_point {
  double x;
  double y;
} t_point;

typedef struct s_intPoint {
  int x;
  int y;
} t_intPoint;

typedef struct s_dda
{
    t_point hp;
    t_point vp;
    double	hdist;
    double	vdist;
    double  initial_x;
    double  initial_y;
}t_dda;

typedef struct s_ray {
  t_point origin;
  t_point Dir;
  double angle;
  double dist;
  t_point wallHit;
  int wallContent;
  double wallStripHeight;
  bool is_facing_down;
  bool is_facing_up;
  bool is_facing_right;
  bool is_facing_left;
  bool	vertical_hit;
  int	face; // which face the ray hit NSEW
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
  char *wt;
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
  t_data wt;
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

typedef struct s_crosshair
{
	int	size;
	int	thickness;
}	t_crosshair;

typedef struct s_gc
{
	void	*ptr;
	struct s_gc	*next;
}	t_gc;

typedef struct s_game {
	t_mlx			mlx;
	t_texture		walls;
	t_player		player;
	t_map			map;
	t_map			check_map;
	t_setting		setting;
	t_point			dir_end;
	t_crosshair		crosshair;
	t_data			minimap; //rem
	bool			mouse;
	int				mouseX;
	int				mouseY;
	int				frame;
	t_gc			*gc;
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
int two_d_arr_size(char **arr);
double normalizeAngle(double angle);
void	drawWalls(t_game *game, t_ray *ray);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    draw_rays(t_game *game);
void	init_ray(t_ray *ray, double angle);
int handlePress(int keycode, void *param);
int handleRelease(int keycode, void *param);
int handle_mouse(int x, int y, void *param);
int check_map_border(t_map *map);
int quite(t_game *game);
void	*g_malloc(t_game *game, size_t size);
void	free_all(t_gc *gc);
void	free_ptr(t_game *game, void *ptr);

// added
void 	drawAngleInMap(t_game *game);
void	drawFovInMap(t_game *game);
void	castRays(t_game *game);
double distance(double x1, double y1, double x2, double y2);

#endif

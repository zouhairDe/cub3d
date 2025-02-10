/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:30:03 by zouddach          #+#    #+#             */
/*   Updated: 2025/02/10 02:50:29 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../gnl/get_next_line_bonus.h"
# include "../../libft/libft.h"
# include "../../mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

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

# define FOV 1.0471975511965977461542144610932

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024
# define MINIMAP_WIDTH 250
# define MINIMAP_HEIGHT 250
# define MINIMAP_SCALE 32
# define RAY_STEP 0.1
# define NUM_RAYS 1280
# define WALL_SIZE 64

# define DOOR_CLOSED 2
# define DOOR_OPEN 3
# define CENTER_X 125
# define CENTER_Y 128
# define WIN_CENTER_X 640
# define WIN_CENTER_Y 512

// USED FOR WALL FACE RENDERING.
# define N 0
# define E 1
# define S 2
# define W 3

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_intPoint
{
	int				x;
	int				y;
}					t_intPoint;

typedef struct s_dda
{
	t_point			hp;
	t_point			vp;
	double			hdist;
	double			vdist;
	double			initial_x;
	double			initial_y;
	bool			vwall;
	bool			hwall;
}					t_dda;

typedef struct s_ray
{
	t_point			origin;
	double			angle;
	double			dist;
	t_point			wall_hit;
	int				wall_content;
	double			wall_strip_height;
	bool			facing_down;
	bool			facing_up;
	bool			facing_right;
	bool			facing_left;
	bool			vertical_hit;
	int				face;
}					t_ray;

typedef struct s_minimap
{
	int				pixel_x;
	int				pixel_y;
	int				tx;
	int				ty;
	unsigned int	color;
	int				col;
	int				screen_x;
	int				screen_y;
	double			rotation_angle;
}				t_minimap;

typedef struct s_drawing_data
{
	double	angle_diff;
	double	perp_dist;
	double	projection_plan_dist;
	int		strip_height;
	int		start;
	int		end;
	int		tx;
	int		y;
	int		dft;
	int		ty;
}			t_drawing_data;

typedef struct s_data
{
	int				width;
	int				height;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_data			data;
}					t_mlx;

typedef struct s_map
{
	int				fd;
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*wt;
	char			*ceiling;
	char			*floor;
	int				rows;
	int				max_cols;
}					t_map;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir;
	double			fov;
	double			moving_speed;
	double			rotation_speed;
}					t_player;

typedef struct s_texture
{
	t_data			no;
	t_data			so;
	t_data			we;
	t_data			ea;
	t_data			wt;
	t_data			closed_door;
	unsigned int	ceilling;
	unsigned int	floor;
}					t_texture;

typedef struct s_setting
{
	int				width;
	int				height;
	char			*title;
	long			player_speed;
	t_mlx			mlx;
}					t_setting;

typedef struct s_crosshair
{
	int				size;
	int				thickness;
}					t_crosshair;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}					t_gc;

typedef struct s_game
{
	t_mlx			mlx;
	t_texture		walls;
	t_player		player;
	t_map			map;
	t_map			check_map;
	t_setting		setting;
	t_point			dir_end;
	t_crosshair		crosshair;
	t_data			minimap;
	bool			mouse;
	int				mouse_x;
	int				mouse_y;
	int				sprites_index;
	void			*sprites_image;
	t_gc			*gc;
}					t_game;

int					init_map(t_game *game, char **line);
int					ft_parse_map(t_game *game);
int					ft_path(char *path, t_game *game);
int					manage_line_logic(char *line, t_game *game);
int					start_map_allocation(t_game *game, char **line);
int					set_textures(t_game *game);
int					set_textures2(t_game *game);
int					not_surrounded(t_map *map);
int					ft_find(char *str, char c);
int					set_mlx(t_game *game);
int					convert_to_hex(t_game *game);
int					validate_elements(t_game *game);
int					check_chars(t_map *map);
int					count_char(char *str, char c);
int					dump_spaces(char **line);
int					ft_line_value(char *line, char **value);
int					check_map(t_game *game);
int					simulate(t_game *game);
int					two_d_arr_size(char **arr);
int					handle_press(int keycode, void *param);
int					handle_release(int keycode, void *param);
int					handle_mouse(int x, int y, void *param);
int					check_map_border(t_map *map);
int					quit(t_game *game);
int					is_wall(t_game *game, double pX, double pY);
int					validate_elements(t_game *game);
int					set_player(t_game *game);
int					set_textures(t_game *game);
int					copy_map(t_game *game);

bool				check_wall_collision(t_game *game, int keycode);
bool				check_up_collision(t_game *game, int *new_x, int *new_y);
bool				check_right_collision(t_game *game, int *newX, int *newY);
bool				check_left_collision(t_game *game, int *newX, int *newY);
bool				check_down_collision(t_game *game, int *newX, int *newY);
bool				check_collor_values(char **side, int *r, int *g, int *b);

unsigned int		rgb_to_hex(int r, int g, int b);

double				normalize_angle(double angle);
double				distance(double x1, double y1, double x2, double y2);
double				deg_to_rad(double angle);
double				rad_to_deg(double angle);

char				*equalize_map_row(const char *row, int max_length);
char				**equalize_map(char **map, int row_count);
char				*ft_replace(char *str, char c, char *news);

void				init_game(t_game *game);
void				draw_rotated_map(t_game *game);
void				center_player_in_map(t_game *game);
void				clear_minimap(t_game *game);
void				put_player(t_game *game, int i);
void				free_2d_arr(char **arr);
void				floodfill(t_map *map, int x, int y);
void				ft_cut_char(char *str, char c);
void				get_sprites(t_game *game, char *f, bool onRelease);
void				sprites(t_game *game, bool onRelease);
void				init_sprites(char **f1, char **f2, char **f3, char **f4);
int					handle_press2(t_game *game, int keycode);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				init_ray(t_ray *ray, double angle);
void				*g_malloc(t_game *game, size_t size);
void				free_all(t_gc *gc);
void				free_ptr(t_game *game, void *ptr);
void				draw_angle_in_map(t_game *game);
void				draw_fov_in_map(t_game *game);
void				cast_rays(t_game *game);
void				dda(t_game *game, t_ray *ray);
void				get_vertical_info(t_game *game, t_ray *ray, t_dda *info);
void				get_horizontal_info(t_game *game, t_ray *ray, t_dda *info);
void				info_init(t_dda *info);
void				collor_floor(t_game *game);
void				collor_ceilling(t_game *game);
int					door(t_game *game, double pX, double pY);
void				draw_line(t_game *game, int x1, int x2, t_intPoint end);
int					handle_mouse_checks(t_game *game, int map_x, int map_y);
void				free_game(t_game *game);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_painter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:01:12 by zouddach          #+#    #+#             */
/*   Updated: 2024/11/19 10:33:28 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void draw_line(t_game *game, t_point start, t_point end, int color)
{
    int dx = abs((int)end.x - (int)start.x);
    int dy = abs((int)end.y - (int)start.y);
    int sx = start.x < end.x ? 1 : -1;
    int sy = start.y < end.y ? 1 : -1;
    int err = dx - dy;
    
    t_point current = start;

    while ((int)current.x != (int)end.x || (int)current.y != (int)end.y)
    {
        if (current.x >= 0 && current.x < MINIMAP_WIDTH && 
            current.y >= 0 && current.y < MINIMAP_HEIGHT)
            my_mlx_pixel_put(&game->mlx.data, current.x, current.y, color);
        
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            current.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            current.y += sy;
        }
    }
}

void draw_direction_vector(t_game *game)
{
    int directionVectorLength = 40;
    t_point start = {MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2};
    t_point end = {
        start.x + directionVectorLength * cos(game->player.dir),
        start.y + directionVectorLength * sin(game->player.dir)
    };
    
    draw_line(game, start, end, 0x00FF0000);
    
    game->dir_end.x = end.x;
    game->dir_end.y = end.y;
}

void draw_plane(t_game *game)
{
    int planeVectorLength = 40;
    double planeDir = game->player.dir + M_PI / 2;
    
    t_point plane_left = { game->dir_end.x + planeVectorLength * cos(planeDir),
        game->dir_end.y + planeVectorLength * sin(planeDir)
    };
    
    t_point plane_right = {
        game->dir_end.x - planeVectorLength * cos(planeDir),
        game->dir_end.y - planeVectorLength * sin(planeDir)
    };
    
    // Draw both sides of the plane vector in blue
    draw_line(game, game->dir_end, plane_left, 0x0000FF00);
    draw_line(game, game->dir_end, plane_right, 0x0000FF00);
}

void cast_single_ray(t_game *game, double ray_angle, int ray_num)
{
    t_point ray_dir = {
        cos(ray_angle),
        sin(ray_angle)
    };
    
    t_point player_pos = {
        MINIMAP_WIDTH / 2,
        MINIMAP_HEIGHT / 2
    };
    
    // Length of ray from current position to next x or y-side
    t_point delta_dist = {
        fabs(1.0 / ray_dir.x),
        fabs(1.0 / ray_dir.y)
    };
    
    // Starting grid position
    int map_x = (int)game->player.x;
    int map_y = (int)game->player.y;
    
    // Length of ray from current position to next x or y-side
    t_point side_dist;
    
    // Direction to step in x or y-direction (either +1 or -1)
    int step_x;
    int step_y;
    
    // Calculate step and initial side_dist
    if (ray_dir.x < 0)
    {
        step_x = -1;
        side_dist.x = (player_pos.x - map_x) * delta_dist.x;
    }
    else
    {
        step_x = 1;
        side_dist.x = (map_x + 1.0 - player_pos.x) * delta_dist.x;
    }
    if (ray_dir.y < 0)
    {
        step_y = -1;
        side_dist.y = (player_pos.y - map_y) * delta_dist.y;
    }
    else
    {
        step_y = 1;
        side_dist.y = (map_y + 1.0 - player_pos.y) * delta_dist.y;
    }
    
    // Perform DDA
    int hit = 0;
    int side; // 0 for x-side, 1 for y-side
    double max_distance = 100.0; // Maximum ray distance
    t_point current = player_pos;
    
    while (!hit && (fabs(current.x - player_pos.x) < max_distance))
    {
        // Jump to next map square
        if (side_dist.x < side_dist.y)
        {
            side_dist.x += delta_dist.x;
            map_x += step_x;
            current.x = map_x;
            current.y = player_pos.y + (map_x - player_pos.x) * ray_dir.y / ray_dir.x;
            side = 0;
        }
        else
        {
            side_dist.y += delta_dist.y;
            map_y += step_y;
            current.y = map_y;
            current.x = player_pos.x + (map_y - player_pos.y) * ray_dir.x / ray_dir.y;
            side = 1;
        }
        
        if (map_x < 0 || map_y < 0 || map_x >= game->map.maxCols || map_y >= game->map.rows)
            hit = 1;
        else if (game->map.map[map_x][map_y] == '1')
            hit = 1;
    }
    
    // Draw the ray
    int color = side ? 0x0000FF : 0xFF0000; // Different colors for x and y sides
    draw_line(game, player_pos, current, color);
}

void cast_and_draw_rays(t_game *game)
{
    int num_rays = 60; // Number of rays to cast
    double fov =  FOV * M_PI / 180; // Field of view (90 degrees)
    
    // Starting angle (player direction - FOV/2)
    double start_angle = -(game->player.dir - fov / 2);
    
    double angle_step = fov / (num_rays - 1);
    
    // Cast rays
    for (int i = 0; i < num_rays; i++)
    {
        double current_angle = start_angle + i * angle_step;
        cast_single_ray(game, current_angle, i);
    }
}

void draw_rays(t_game *game)
{
    draw_direction_vector(game);
    draw_plane(game);
    cast_and_draw_rays(game);
}
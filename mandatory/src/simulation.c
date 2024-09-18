/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2024/09/18 07:27:27 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

#include "../../includes/cub3d.h"

#define SCALE 20
#define RAY_STEP 0.1

double normalizeAngle(double angle)
{
    angle = remainder(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return angle;
}

t_ray castRay(t_game *game, double angle)
{
    t_ray ray;
    
    ray.dir = normalizeAngle(angle);
    ray.dist = 0;
    ray.hit = 0;
    while (!ray.hit)
    {
        ray.dist += RAY_STEP;
        ray.x = game->player.x + cos(ray.dir) * ray.dist;
        ray.y = game->player.y + sin(ray.dir) * ray.dist;
        int mapX = (int)ray.x;
        int mapY = (int)ray.y;
        if (mapX < 0 || mapY < 0 || mapX >= game->map.maxCols || mapY >= game->map.rows || game->map.map[mapY][mapX] == '1')
            ray.hit = 1;
    }
    return ray;
}

void drawRay(t_game *game, t_ray ray)
{
    int j;
    int screenX, screenY;
    
    for (j = 0; j < ray.dist * SCALE; j++)
    {
        screenX = (int)((game->player.x + cos(ray.dir) * j / SCALE) * SCALE);
        screenY = (int)((game->player.y + sin(ray.dir) * j / SCALE) * SCALE);
        if (screenX >= 0 && screenX < WINDOW_WIDTH && screenY >= 0 && screenY < WINDOW_HEIGHT)
        {
            mlx_pixel_put(game->mlx.mlx, game->mlx.win, screenX, screenY, 0X00FF0000);
        }
    }
}

int simulate(t_game *game)
{   
    int i;
    double rayAngle;
    
    mlx_clear_window(game->mlx.mlx, game->mlx.win);
    
    for (i = 0; i < WINDOW_WIDTH; i++)
    {
        rayAngle = game->player.dir - game->player.fov / 2 + (i * game->player.fov / WINDOW_WIDTH);
        t_ray ray = castRay(game, rayAngle);
        drawRay(game, ray);
    }
    
    mlx_do_sync(game->mlx.mlx);
    return 0;
}

int key_hook(int keycode, t_game *game)
{
    double moveSpeed = 0.1;
    double rotSpeed = 0.1;

    if (keycode == 65361) // Left arrow
        game->player.dir -= rotSpeed;
    else if (keycode == 65363) // Right arrow
        game->player.dir += rotSpeed;
    else if (keycode == 65362) // Up arrow
    {
        game->player.x += cos(game->player.dir) * moveSpeed;
        game->player.y += sin(game->player.dir) * moveSpeed;
    }
    else if (keycode == 65364) // Down arrow
    {
        game->player.x -= cos(game->player.dir) * moveSpeed;
        game->player.y -= sin(game->player.dir) * moveSpeed;
    }
    
    game->player.dir = normalizeAngle(game->player.dir);
    simulate(game);  // Redraw after movement
    return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2024/09/18 12:35:34 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

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

void collorCeilling(t_game *game)
{
	int i;
	int j;
	bool	toggle = false;
	
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT / 2)
		{
			mlx_pixel_put(game->mlx.mlx, game->mlx.win, i, j, game->walls.ceilling);
			j++;
		}
		i++;
	}
}

void collorFloor(t_game *game)
{
	int i;
	int j;
	
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = WINDOW_HEIGHT / 2;
		while (j < WINDOW_HEIGHT)
		{
			mlx_pixel_put(game->mlx.mlx, game->mlx.win, i, j, game->walls.floor);
			j++;
		}
		i++;
	}
}

void drawMiniMapBorders(t_game *game)
{
	int i;
	int j;
	
	i = 0;
	while (i < MINIMAP_WIDTH)
	{
		j = 0;
		while (j < MINIMAP_HEIGHT)
		{
			if (i == 0 || j == 0 || i == MINIMAP_WIDTH - 1 || j == MINIMAP_HEIGHT - 1)
			{
				mlx_pixel_put(game->mlx.mlx, game->mlx.win, i, j, 0X00FFFFFF);
				mlx_pixel_put(game->mlx.mlx, game->mlx.win, i + 1, j + 1, 0X00FFFFFF);
				mlx_pixel_put(game->mlx.mlx, game->mlx.win, i + 2, j + 2, 0X00FFFFFF);
			}
			else
				mlx_pixel_put(game->mlx.mlx, game->mlx.win, i, j, 0X00000000);
			j++;
		}
		i++;
	}
}

// Setting scale factor
// Calculate player's position on minimap
// Draw player as a small square
// void drawPlayerOnMiniMap(t_game *game)
// {
//     int x, y;
//     int playerSize = 4;
//     float scale;
	
// 	scale = (float)MINIMAP_WIDTH / game->map.maxCols;
// 	x = game->player.x * scale;
// 	y = game->player.y * scale;
// 	for (int dy = 0; dy < playerSize; dy++)
// 	{
// 		for (int dx = 0; dx < playerSize; dx++)
// 		{
// 			int drawX = x + dx;
// 			int drawY = y + dy;
// 			if (drawX >= 0 && drawX < MINIMAP_WIDTH && drawY >= 0 && drawY < MINIMAP_HEIGHT)
// 			{
// 				mlx_pixel_put(game->mlx.mlx, game->mlx.win, drawX, drawY, 0X00FF0000);
// 			}
// 		}
// 	}
// }

// void drawWallsOnMiniMap(t_game *game)
// {
//     int i, j;
//     float scale;
    
//     scale = (float)MINIMAP_WIDTH / game->map.maxCols;
//     for (i = 0; i < game->map.rows; i++)
//     {
//         for (j = 0; j < game->map.maxCols; j++)
//         {
//             if (j < ft_strlen(game->map.map[i]) && game->map.map[i][j] == '1')
//             {
//                 int x = j * scale;
//                 int y = i * scale;
//                 for (int dy = 0; dy < scale; dy++)
//                 {
//                     for (int dx = 0; dx < scale; dx++)
//                     {
//                         int drawX = x + dx;
//                         int drawY = y + dy;
//                         if (drawX >= 0 && drawX < MINIMAP_WIDTH && drawY >= 0 && drawY < MINIMAP_HEIGHT)
//                         {
//                             mlx_pixel_put(game->mlx.mlx, game->mlx.win, drawX, drawY, 0X00FFFFFF);
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// void drawMiniMap(t_game *game)
// {
//     drawMiniMapBorders(game);
//     drawWallsOnMiniMap(game);
//     drawPlayerOnMiniMap(game);
// }

void	CenterPlayerInMiniMap(t_game *game)
{
	int x;
	int y;
	int playerSize = 4;
	float scale;
	
	scale = (float)MINIMAP_WIDTH / game->map.maxCols;
	x = game->player.x * scale;
	y = game->player.y * scale;
	for (int dy = 0; dy < playerSize; dy++)
	{
		for (int dx = 0; dx < playerSize; dx++)
		{
			int drawX = x + dx;
			int drawY = y + dy;
			if (drawX >= 0 && drawX < MINIMAP_WIDTH && drawY >= 0 && drawY < MINIMAP_HEIGHT)
			{
				mlx_pixel_put(game->mlx.mlx, game->mlx.win, drawX, drawY, 0X00FF0000);
			}
		}
	}
}

int simulate(t_game *game)
{   
    int i;
    double rayAngle;
    
    mlx_clear_window(game->mlx.mlx, game->mlx.win);
	
	collorCeilling(game);
	collorFloor(game);
	drawMiniMapBorders(game);
	// drawMiniMap(game);
	CenterPlayerInMiniMap(game);
    
    // for (i = 0; i < WINDOW_WIDTH; i++)
    // {
    //     rayAngle = game->player.dir - game->player.fov / 2 + (i * game->player.fov / WINDOW_WIDTH);
    //     t_ray ray = castRay(game, rayAngle);
    //     drawRay(game, ray);
    // }
    
    mlx_do_sync(game->mlx.mlx);
    return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:49:38 by zouddach          #+#    #+#             */
/*   Updated: 2024/09/21 21:34:30 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double normalizeAngle(double angle)
{
    angle = remainder(angle, 2 * M_PI);
    if (angle < 0)
        angle = (2 * M_PI) + angle;
    return angle;
}

void collorCeilling(t_game *game)
{
	int i;
	int j;
	bool	toggle = false;

	i = 0;
	while (i++ < WINDOW_WIDTH)
	{
		j = 0;
		while (j++ < WINDOW_HEIGHT / 2)
		{
			if (i < MINIMAP_HEIGHT && j < MINIMAP_HEIGHT)
				continue ;
			else
				my_mlx_pixel_put(&game->mlx.data, i, j, game->walls.ceilling);
		}
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
			my_mlx_pixel_put(&game->mlx.data, i, j, game->walls.floor);
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
				my_mlx_pixel_put(&game->mlx.data, i, j, 0X00FFFFFF);
				my_mlx_pixel_put(&game->mlx.data, i + 1, j + 1, 0X00FFFFFF);
				my_mlx_pixel_put(&game->mlx.data, i + 2, j + 2, 0X00FFFFFF);
			}
			j++;
		}
		i++;
	}
}

void rotatePoint(double *x, double *y, double angle) {
    double oldX = *x;
    double oldY = *y;
    *x = oldX * cos(angle) - oldY * sin(angle);
    *y = oldX * sin(angle) + oldY * cos(angle);
}

void drawRotatedMap(t_game *game)
{
    t_point P = {game->player.y, game->player.x};
    int centerX = MINIMAP_WIDTH / 2;
    int centerY = MINIMAP_HEIGHT / 2;
    double rotationAngle = game->player.dir;

    for (int i = 0; i < game->map.rows; i++)
    {
        for (int j = 0; j < ft_strlen(game->map.map[i]); j++)
        {
            double mapX = (j - P.x) * MINIMAP_SCALE;
            double mapY = (i - P.y) * MINIMAP_SCALE;
            rotatePoint(&mapX, &mapY, -rotationAngle);
            int screenX = centerX + (int)mapX;
            int screenY = centerY + (int)mapY;

            if (screenX < 0 || screenY < 0 || screenX >= MINIMAP_WIDTH || screenY >= MINIMAP_HEIGHT)
                continue;

            if (game->map.map[i][j] == '1')
            {
                for (int x = 0; x < MINIMAP_SCALE; x++)
                {
                    for (int y = 0; y < MINIMAP_SCALE; y++)
                    {
                        int pixelX = screenX + x;
                        int pixelY = screenY + y;
                        if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
                            my_mlx_pixel_put(&game->mlx.data, pixelX, pixelY, 0X00FFFFFF);
                    }
                }
            }
        }
    }
}

void centerPlayerInMap(t_game *game)
{
    int centerX = MINIMAP_WIDTH / 2;
    int centerY = MINIMAP_HEIGHT / 2;
    int height = 2 * 4;
    int halfBase = 3;

    for (int i = -halfBase; i <= halfBase; i++)
    {
        for (int j = 0; j < height; j++)
        {
            double x = i;
            double y = j;
            rotatePoint(&x, &y, game->player.dir);
            int drawX = centerX + (int)x;
            int drawY = centerY + (int)y;
            if (drawX >= 0 && drawX < MINIMAP_WIDTH && drawY >= 0 && drawY < MINIMAP_HEIGHT)
                my_mlx_pixel_put(&game->mlx.data, drawX, drawY, 0X00FF0000);
        }
    }
}

void drawMap(t_game *game)
{
	drawMiniMapBorders(game);
	drawRotatedMap(game);
	centerPlayerInMap(game);
}

void clean_window(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(data, i, j, 0);
			j++;
		}
		i++;
	}
}
void draw_rayOnMinimap(t_game *game, double rayX, double rayY)
{
    int i;
    int j;
    int pixelX;
    int pixelY;

    // Scale the ray coordinates based on minimap scaling
    pixelX = (int)(rayX * MINIMAP_SCALE);
    pixelY = (int)(rayY * MINIMAP_SCALE);

    // Draw a single pixel representing the ray step
    if (pixelX >= 0 && pixelX < MINIMAP_WIDTH && pixelY >= 0 && pixelY < MINIMAP_HEIGHT)
    {
        for (i = 0; i < MINIMAP_SCALE; i++)
        {
            for (j = 0; j < MINIMAP_SCALE; j++)
            {
                my_mlx_pixel_put(&game->mlx.data, pixelX + i, pixelY + j, 0x00FF0000); // Draw the ray in red
            }
        }
    }
}


void cast_minimap_rays(t_game *game)
{
    t_ray ray;
    init_ray(&ray, game);

    for (int i = 0; i < MINIMAP_WIDTH; i++) // Cast rays across the minimap
    {
        double cameraX = 2 * i / (double)MINIMAP_WIDTH - 1; // Calculate camera plane position
        ray.Dir.x = game->player.dir + game->player.fov * cameraX; // Adjust the ray's direction with FOV
        ray.Dir.y = game->player.dir + game->player.fov * cameraX;

        // DDA initialization
        int mapX = (int)game->player.x;
        int mapY = (int)game->player.y;

        // Length of ray from one x or y-side to the next x or y-side
        double deltaDistX = fabs(1 / ray.Dir.x);
        double deltaDistY = fabs(1 / ray.Dir.y);

        // Calculate step and initial sideDist
        int stepX, stepY;
        double sideDistX, sideDistY;

        if (ray.Dir.x < 0)
        {
            stepX = -1;
            sideDistX = (game->player.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
        }

        if (ray.Dir.y < 0)
        {
            stepY = -1;
            sideDistY = (game->player.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
        }

        // Perform DDA
        int hit = 0;
        int side;
        while (!hit)
        {
            // Jump to next map square, either in x-direction or y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // Check if ray has hit a wall
			printf("mapX = %d, mapY = %d\n", mapX, mapY);
			if (mapX < 0 || mapY < 0 || mapX >= game->map.rows || mapY >= ft_strlen(game->map.map[mapY]))
				hit = 1;
			else if (game->map.map[mapY][mapX] == '1')
				hit = 1;
        }

        // Draw the ray on the minimap
        draw_rayOnMinimap(game, mapX, mapY);
    }
}


int simulate(t_game *game)
{
	int i;
	double rayAngle;

	mlx_clear_window(game->mlx.mlx, game->mlx.win);
	clean_window(&game->mlx.data);

	collorCeilling(game);
	collorFloor(game);
	drawMap(game);
	cast_minimap_rays(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.data.img, 0, 0);
	return 0;
}

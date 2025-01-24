/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 04:48:13 by zouddach          #+#    #+#             */
/*   Updated: 2025/01/24 14:07:14 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d_bonus.h"

int	copy_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	game->check_map.map = malloc(sizeof(char *) * game->map.rows);
	if (!game->check_map.map)
		return (1);
	while (i < game->map.rows)
	{
		game->check_map.map[i] = ft_strdup(game->map.map[i]);
		i++;
	}
	game->check_map.rows = game->map.rows;
	game->check_map.maxCols = game->map.maxCols;
	return (0);
}

int	ft_find(char *str, char c)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

int	setPlayer(t_game *game)
{
	int i;
	bool posSet;
	
	i = 0;
	posSet = false;
	while (i < game->check_map.rows)
	{
		if (ft_find(game->check_map.map[i], 'N') != -1 ||
			ft_find(game->check_map.map[i], 'S') != -1 ||
			ft_find(game->check_map.map[i], 'E') != -1 ||
			ft_find(game->check_map.map[i], 'W') != -1)
		{
			if (posSet == true)
				return (printf("Error\nMultiple player starting positions\n"));
			game->player.x = i + 0.5;
			if (ft_find(game->check_map.map[i], 'S') != -1)
				(game->player.dir = 270, game->player.y = ft_find(game->check_map.map[i], 'S') + 0.5);
			else if (ft_find(game->check_map.map[i], 'E') != -1)
				(game->player.dir = 180, game->player.y = ft_find(game->check_map.map[i], 'E') + 0.5);
			else if (ft_find(game->check_map.map[i], 'W') != -1)
				(game->player.dir = 90, game->player.y = ft_find(game->check_map.map[i], 'W') + 0.5);
			else
				(game->player.dir = 0, game->player.y = ft_find(game->check_map.map[i], 'N') + 0.5);
			posSet = true;
		}
		i++;
	}
	game->player.dir = normalizeAngle(game->player.dir); // added this so that the angle is normalized even if no key is pressed
	// printf("Player position: %f, %f\n", game->player.x, game->player.y);
	if (!posSet)
		return (printf("Error\nNo player starting position\n"));
	return (0);
}

void	floodfill(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->rows || y >= ft_strlen(map->map[x]))
		return ;
	if (map->map[x] == NULL)
		return ;
	if (map->map[x][y] == '1' || map->map[x][y] == '*')
		return ;
	map->map[x][y] = '*';
	floodfill(map, x + 1, y);
	floodfill(map, x - 1, y);
	floodfill(map, x, y + 1);
	floodfill(map, x, y - 1);
}

int	check_chars(t_map *map)
{
	int i;
	int j;
	
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0' &&
				map->map[i][j] != '2' && map->map[i][j] != 'N' &&
				map->map[i][j] != 'S' && map->map[i][j] != 'E' &&
				map->map[i][j] != 'W' && map->map[i][j] != '\n' &&
				map->map[i][j] != ' ' && map->map[i][j] != 'D')
				return (printf("Error\nInvalid character in map %s\nat %d --> %c\n", map->map[i], j, map->map[i][j]));
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_ignore_space(char *str)
{
	int i;
	
	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	notSurrounded(t_map *map)
{
	int i;
	int j;
	
	i = 0;
	if (ft_strchr(map->map[0], '*') || ft_strchr(map->map[map->rows - 1], '*'))
		return (printf("Error\nMap not surrounded by walls\n"));
	while (i < map->rows)
	{
		if ((map->map[i][ft_strlen(map->map[i]) - 1] == '*') ||
			(map->map[i][ft_ignore_space(map->map[i])] == '*'))
			return (printf("Error\nMap not surrounded by walls\n"));
		i++;
	}
	return (0);
}

int	setTextures(t_game *game)
{
	printf("Loading textures\n");
	game->map.no[ft_strlen(game->map.no) - 1] = 0;
	game->map.so[ft_strlen(game->map.so) - 1] = 0;
	game->map.we[ft_strlen(game->map.we) - 1] = 0;
	game->map.ea[ft_strlen(game->map.ea) - 1] = 0;
	printf("North texture: %s\n", game->map.no);
	printf("West texture: %s\n", game->map.we);
	printf("South texture: %s\n", game->map.so);
	printf("East texture: %s\n", game->map.ea);//ila kano khawyin l path khas error 9bl mmatwsl hna
	game->walls.no.img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.no, &game->walls.no.width, &game->walls.no.height);
	if (!game->walls.no.img)
		return (printf("Error\nCouldn't load NO texture\n"));
	game->walls.no.addr = mlx_get_data_addr(game->walls.no.img, &game->walls.no.bits_per_pixel,
		&game->walls.no.line_length, &game->walls.no.endian);

	game->walls.wt.img = mlx_xpm_file_to_image(game->mlx.mlx, "./textures/WallTop.xpm", &game->walls.wt.width, &game->walls.wt.height);
	if (!game->walls.wt.img)
		return (printf("Error\nCouldn't load WT texture\n"));
	game->walls.wt.addr = mlx_get_data_addr(game->walls.wt.img, &game->walls.wt.bits_per_pixel, &game->walls.wt.line_length, &game->walls.wt.endian);
	
	game->walls.so.img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.so, &game->walls.so.width, &game->walls.so.height);
	if (!game->walls.so.img)
		return (printf("Error\nCouldn't load SO texture\n"));
	game->walls.so.addr = mlx_get_data_addr(game->walls.so.img, &game->walls.so.bits_per_pixel, &game->walls.so.line_length, &game->walls.so.endian);
	
	game->walls.we.img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.we, &game->walls.we.width, &game->walls.we.height);
	if (!game->walls.we.img)
		return (printf("Error\nCouldn't load WE texture\n"));
	game->walls.we.addr = mlx_get_data_addr(game->walls.we.img, &game->walls.we.bits_per_pixel, &game->walls.we.line_length, &game->walls.we.endian);
	
	game->walls.ea.img = mlx_xpm_file_to_image(game->mlx.mlx, game->map.ea, &game->walls.ea.width, &game->walls.ea.height);
	if (!game->walls.ea.img)
		return (printf("Error\nCouldn't load EA texture\n"));
	game->walls.ea.addr = mlx_get_data_addr(game->walls.ea.img, &game->walls.ea.bits_per_pixel, &game->walls.ea.line_length, &game->walls.ea.endian);
	
	game->walls.CDoor.img = mlx_xpm_file_to_image(game->mlx.mlx, "./texture_stock/xpm/oxidized_copper_bulb_powered.xpm", &game->walls.CDoor.width, &game->walls.CDoor.height);
	if (!game->walls.CDoor.img)
		return (printf("Error\nCouldn't load CDoor texture\n"));
	return (0);
}

int quite(t_game *game)
{
	int i;
	
	i = 0;
	printf("Exiting\n");
	// printGame(*game);
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	while (i < game->check_map.rows)
	{
		free(game->check_map.map[i]);
		i++;
	}
	free(game->check_map.map);
	free(game->map.no);
	free(game->map.so);
	free(game->map.we);
	free(game->map.ea);
	free(game->mlx.mlx);
	exit(0);
	return (0);
}

bool	checkWallCollision(t_game *game, int keycode)
{
	int newX;
	int newY;
	double distance;

	//make it stop 0.3 before touching wall
	if (keycode == W_BUTTON)
	{
		newX = game->player.x + game->player.moveSpeed * sin(game->player.dir);
		newY = game->player.y + game->player.moveSpeed * cos(game->player.dir);
		// distance = distance(game->player.x, game->player.y, newX, newY);
	}
	else if (keycode == S_BUTTON)
	{
		newX = game->player.x - game->player.moveSpeed * sin(game->player.dir);
		newY = game->player.y - game->player.moveSpeed * cos(game->player.dir);
	}
	else if (keycode == A_BUTTON)
	{
		newX = game->player.x - game->player.moveSpeed * cos(game->player.dir);
		newY = game->player.y + game->player.moveSpeed * sin(game->player.dir);
	}
	else if (keycode == D_BUTTON)
	{
		newX = game->player.x + game->player.moveSpeed * cos(game->player.dir);
		newY = game->player.y - game->player.moveSpeed * sin(game->player.dir);
	}
	
	if (newX < 0 || newY < 0 || newX >= game->map.rows
		|| newY >= ft_strlen(game->map.map[(int)newX]))
		return (false);
	
	if (game->map.map[(int)newX][(int)newY] == '1' || game->map.map[(int)newX][(int)newY] == 'D')
		return (false);
	return (true);
}

int handlePress(int keycode, void *param)
{
	// printf("keycode: %d\n", keycode);
    t_game *game = (t_game *)param;

    if (keycode == 53)
        return (quite(param));
	if (keycode == H_BUTTON)
	{
		if (game->mouse)
			mlx_mouse_hide(), game->mouse = !game->mouse;
		else
			mlx_mouse_show(), game->mouse = !game->mouse;
	}
	else if (keycode == LEFT_BUTTON)
		game->player.dir -= game->player.rotSpeed;
	else if (keycode == RIGHT_BUTTON)
		game->player.dir += game->player.rotSpeed;
	else if (keycode == W_BUTTON && checkWallCollision(game, W_BUTTON)){
		game->player.x += game->player.moveSpeed * sin(game->player.dir);
		game->player.y += game->player.moveSpeed * cos(game->player.dir);
	}
	else if (keycode == S_BUTTON && checkWallCollision(game, S_BUTTON)){
		game->player.x -= game->player.moveSpeed * sin(game->player.dir);
		game->player.y -= game->player.moveSpeed * cos(game->player.dir);
	}
	else if (keycode == A_BUTTON && checkWallCollision(game, A_BUTTON)){
		game->player.x -= game->player.moveSpeed * cos(game->player.dir);
		game->player.y += game->player.moveSpeed * sin(game->player.dir);
	}
	else if (keycode == D_BUTTON && checkWallCollision(game, D_BUTTON)){
		game->player.x += game->player.moveSpeed * cos(game->player.dir);
		game->player.y -= game->player.moveSpeed * sin(game->player.dir);
	}
	game->player.dir = normalizeAngle(game->player.dir);
	simulate(game);
	return 0;
}

int handleRelease(int keycode, void *param)
{
	t_game *game = (t_game *)param;
	return 0;
}


int handle_mouse(int x, int y, void *param)
{
    t_game	*game;
    int		diff_x;
    static int last_x;

	game = (t_game *)param;
	last_x = WINDOW_WIDTH / 2;
	diff_x = x - last_x;
	if (game->mouse)
		return (0);
    if (diff_x != 0)
    {
        game->player.dir += (diff_x * 0.001);
        game->player.dir = normalizeAngle(game->player.dir);
        last_x = x;
    }
    mlx_mouse_move(game->mlx.win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    return (0);
}

int setMLX(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		return (printf("Error\nCouldn't initialize mlx\n"));
	game->mlx.win = mlx_new_window(game->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game->mlx.win)
		return (printf("Error\nCouldn't create window\n"));
	game->mlx.data.img = mlx_new_image(game->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->mlx.data.img)//shit is so fkng t9il
		return (printf("Error\nCouldn't create image\n"));
	game->mlx.data.addr = mlx_get_data_addr(game->mlx.data.img, &game->mlx.data.bits_per_pixel, &game->mlx.data.line_length, &game->mlx.data.endian);
	if (!game->mlx.data.addr)
		return (printf("Error\nCouldn't create image\n"));
	return (0);
}

int	convertToHex(t_game *game)
{
	char	**floor;
	char	**ceilling;

	floor = ft_split(game->map.F, ',');
	if (!floor)
		return (1);
	ceilling = ft_split(game->map.C, ',');
	if (!ceilling)
		return (1);//free floor...
	if (twoDArrSize(floor) != 3 || twoDArrSize(ceilling) != 3)
		return (printf("Error\nInvalid color format\n"));
	game->walls.floor = rgb_to_hex(ft_atoi(floor[0]), ft_atoi(floor[1]), ft_atoi(floor[2]));
	game->walls.ceilling = rgb_to_hex(ft_atoi(ceilling[0]), ft_atoi(ceilling[1]), ft_atoi(ceilling[2]));
	return (0);
}

char *equalize_map_row(const char *row, int max_length)
{
    char *new_row = calloc(max_length + 1, sizeof(char));
    if (!new_row)
        return NULL;
    
    int i = 0;
    while (row[i] && i < max_length)
    {
        if (row[i] != ' ' && row[i] != '\t')
            new_row[i] = row[i];
        else
            new_row[i] = '0';
        i++;
    }
    while (i < max_length)
    {
        new_row[i] = '0';
        i++;
    }
    new_row[i] = '\0';
    
    return new_row;
}

char **equalize_map(char **map, int row_count)
{
	char **new_map;
    if (!map || row_count <= 0)
        return NULL;
    
    int max_length = 0;
    for (int i = 0; i < row_count; i++)
    {
        int len = strlen(map[i]);
        if (len > max_length)
            max_length = len;
    }
    new_map = malloc((row_count + 1) * sizeof(char *));
    if (!new_map)
        return NULL;
    
    for (int i = 0; i < row_count; i++)
    {
        new_map[i] = equalize_map_row(map[i], max_length);
        if (!new_map[i])
        {
            for (int j = 0; j < i; j++)
                free(new_map[j]);
            free(new_map);
            return NULL;
        }
    }
    new_map[row_count] = NULL;
    
    return new_map;
}

int check_map(t_game *game)//gotta check for leaks when exiting with errors...
{
	if (copy_map(game))
		return (1);
	game->map.map = equalize_map(game->map.map, game->map.rows);
	if (!game->map.map)
		return (1);
	if (check_chars(&game->check_map))
		return (1);
	if (setPlayer(game))
		return (1);
	printf("mid from check map\n");
	floodfill(&game->check_map, 5, 13);
	if (notSurrounded(&game->check_map))
		return (1);
	if (convertToHex(game))
		return (1);
	if (setMLX(game))
		return (1);
	//if (game->map.no == NULL || game->map.so == NULL || game->map.we == NULL || game->map.ea == NULL)
	//	return (printf("Error\nMissing texture path\n"));
	printf("pre set texture\n");
	if (setTextures(game))
		return (1);
	
	printf("done with check map\n");
		
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-lah <mait-lah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:29:47 by zouddach          #+#    #+#             */
/*   Updated: 2025/01/29 19:41:40 by mait-lah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int start_map_allocation(t_game *game, char **line) {
	char **tmp;
	int i;
	
	if (game->map.map == NULL) {
	  game->map.map = malloc(sizeof(char *));
	  if (!game->map.map)
		return (1);
	  game->map.map[0] = ft_strdup(*line);
	  game->map.rows++;
	  game->map.map[0] = ft_replace(game->map.map[0], '\t', "    ");
		if (!game->map.map[0])
			return (1);
		ft_cut_char(game->map.map[0], '\n');
	  return (0);
	}
	i = 0;
	tmp = game->map.map;
	game->map.map = malloc(sizeof(char *) * (game->map.rows + 1));
	if (!game->map.map)
	  return (1);
	while (i < game->map.rows) {
	  game->map.map[i] = tmp[i];
	  i++;
	}
	game->map.map[i] = ft_strdup(*line);
	game->map.rows++;
	if (game->map.maxCols < (int)ft_strlen(*line))
	  game->map.maxCols = ft_strlen(*line) - 1;
	game->map.map[i] = ft_replace(game->map.map[i], '\t', "    ");
	if (!game->map.map[i])
	  return (1);
	ft_cut_char(game->map.map[i], '\n');
	free(tmp);
	return (0);
}


int manage_line_logic(char *line, t_game *game) {
  char *tmp;

  tmp = line;
  dump_spaces(&line);
  if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "NO\t", 3))
	return (ft_line_value(line, &game->map.no));
  else if (!ft_strncmp(line, "SO ", 3) || !ft_strncmp(line, "SO\t", 3))
	return (ft_line_value(line, &game->map.so));
  else if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "WE\t", 3))
	return (ft_line_value(line, &game->map.we));
  else if (!ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "EA\t", 3))
	return (ft_line_value(line, &game->map.ea));
  else if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "C\t", 2))
	return (ft_line_value(line, &game->map.C));
  else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "F\t", 2))
	return (ft_line_value(line, &game->map.F));
  else if (ft_strchr(line, '1') || ft_strchr(line, '0'))
	return (start_map_allocation(game, &tmp));
  return (0);
}

int ft_parse_map(t_game *game) {
  char *line;
  char *tmp;
(void)tmp;
  while ((line = get_next_line(game->map.fd)) != NULL) {
	if (manage_line_logic(line, game))
	  return (free(line), 1);
	free(line);
  }
  return (0);
}

int ft_path(char *path, t_game *game) {
  int dot;

  dot = path - ft_strrchr(path, '.');
  if (dot == 0 || !ft_strncmp(&path[dot], ".cub", 4))
	return (printf("Error\nInvalid file extension\n"));
  game->map.fd = open(path, O_RDONLY);
  if (game->map.fd == -1)
	return (printf("Error\nFile not found\n"));
  return (0);
}

void init_game(t_game *game) {
  game->map.fd = 0;
  game->map.no = NULL;
  game->map.so = NULL;
  game->map.we = NULL;
  game->map.ea = NULL;
  game->map.wt = NULL;
  game->map.C = NULL;
  game->map.F = NULL;
  game->map.map = NULL;
  game->map.rows = 0;
  game->map.maxCols = 0;
  game->check_map.fd = 0;
  game->check_map.no = NULL;
  game->check_map.so = NULL;
  game->check_map.we = NULL;
  game->check_map.ea = NULL;
//  game->check_map.wt = NULL; ??? 
  game->check_map.C = NULL;
  game->check_map.F = NULL;
  game->check_map.map = NULL;
  game->check_map.rows = 0;
  game->check_map.maxCols = 0;
  game->player.x = 0.0;
  game->player.y = 0.0;
  game->player.dir = 0;
  game->player.fov = 0;
  game->player.moveSpeed = 0.1;
  game->player.rotSpeed = 0.1;
  game->mlx.mlx = NULL;
  game->mlx.win = NULL;
  game->setting.width = 0;
  game->setting.height = 0;
  game->setting.title = NULL;
  game->setting.player_speed = 1;
  game->setting.mlx.mlx = NULL;
  game->setting.mlx.win = NULL;
  game->mouse = false;
  game->mouseX = WINDOW_WIDTH / 2;
  game->mouseY = WINDOW_HEIGHT / 2;
  game->crosshair.size = 4;
  game->crosshair.thickness = 2;  
  game->frame = 0;
}


void printGame(t_game game) {
	struct stat st = {0};
	if (stat("logs", &st) == -1) {
		mkdir("logs", 0700);
	}
	
	FILE *f = fopen("logs/gameData.log", "a");
	if (!f) {
		perror("Error opening log file");
		return;
	}
	fprintf(f, "____________________ Game Data ------------------\n");
	fprintf(f, "Current Game State\n");
	fprintf(f, "Map:\n");
	for (int i = 0; i < game.map.rows; i++)
		fprintf(f, "%s\n", game.map.map[i]);
	fprintf(f, "\nMap settings:\n");
	(game.mouse) ? fprintf(f, "Mouse: true\n") : fprintf(f, "Mouse: false\n");
	fprintf(f, "Player speed: %ld\n", game.setting.player_speed);
	fprintf(f, "Player move speed: %f\n", game.player.moveSpeed);
	fprintf(f, "Player rotation speed: %f\n", game.player.rotSpeed);
	fprintf(f, "Window width: %d\n", game.setting.width);
	fprintf(f, "Window height: %d\n", game.setting.height);
	fprintf(f, "Title: %s\n", game.setting.title);
	fprintf(f, "Textures:\n");
	(game.walls.no.addr) ? fprintf(f, "NO: %s", game.map.no) : fprintf(f, "NO: NULL\n");
	(game.walls.so.addr) ? fprintf(f, "SO: %s", game.map.so) : fprintf(f, "SO: NULL\n");
	(game.walls.we.addr) ? fprintf(f, "WE: %s", game.map.we) : fprintf(f, "WE: NULL\n");
	(game.walls.ea.addr) ? fprintf(f, "EA: %s", game.map.ea) : fprintf(f, "EA: NULL\n");
	fprintf(f, "Colors:\n");
	(game.walls.ceilling) ? fprintf(f, "Ceilling: %d\n", game.walls.ceilling) : fprintf(f, "Ceilling: NULL\n");
	(game.walls.floor) ? fprintf(f, "Floor: %d\n", game.walls.floor) : fprintf(f, "Floor: NULL\n");
	fprintf(f, "Player pos: %f %f\n", game.player.x, game.player.y);
	fprintf(f, "Player dir: %f\n", game.player.dir);
	fprintf(f, "Player fov: %f\n", game.player.fov);
}

int init(char *path, t_game *game) {
  printf("in init \n");
  init_game(game);
  if (ft_path(path, game))
	return (1);
	printf("1\n");
  if (ft_parse_map(game))
	return (1);
  printf("2 \n");
  if (check_map(game))
	return (1);
  printf("done initing\n");
  return (0);
}

void fff() { system("leaks cub3d"); }

void free_game(t_game *game) {
  free(game->map.no);
  free(game->map.so);
  free(game->map.we);
  free(game->map.ea);
  free(game->map.C);
  free(game->map.F);
  for (int i = 0; i < game->map.rows; i++)
	free(game->map.map[i]);
  free(game->map.map);
  close(game->map.fd);
}

int main(int ac, char **av) {
  //   atexit(fff);
  t_game game;

  printf("\n"); // remove later.
  if (ac != 2)
	return (printf("Error\nInvalid number of arguments\n"));
  if (init(av[1], &game))
	return (printf("Error\nParsing error\n"));

	mlx_hook(game.mlx.win, 2, 0L, handlePress, &game);
	mlx_hook(game.mlx.win, 3, 0L, handleRelease, &game);
	mlx_hook(game.mlx.win, 17, 0, quite, &game);
	mlx_loop_hook(game.mlx.mlx, simulate, &game);
	mlx_hook(game.mlx.win, ON_MOUSEMOVE, 0, handle_mouse, &game);
	// mlx_mouse_hook(game->mlx.win, handle_mouse, (void *)game);//hadi mni n9ado doors ndiroha t7l b left click
	mlx_loop(game.mlx.mlx);

  free_game(&game);
  return (0);
}
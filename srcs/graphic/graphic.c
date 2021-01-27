/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 20.05/01/24 14:08:32 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/27 16:01:56 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"
#include <errno.h>
#include <math.h>

void	ft_clear_memory(t_game *game)
{
	ft_free_scene(game->scene);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

static	void	ft_handle_keys(t_game *game)
{
	double	posy;
	double	posx;
	double	dirx;
	double	diry;

	posy = game->posy;
	posx = game->posx;
	dirx = game->dirx;
	diry = game->diry;
	if (game->w)
	{
		if (game->scene->map[(int)posy][(int)(posx + dirx * (0.05 * 2))] != '1')
			game->posx += dirx * 0.05;
		if (game->scene->map[(int)(posy + diry * 0.05)][(int)posx] != '1')
			game->posy += diry * 0.05;
	}
	else if (game->s)
	{
		if (game->scene->map[(int)posy][(int)(posx - dirx * (0.05 * 2))] != '1')
			game->posx -= dirx * 0.05;
		if (game->scene->map[(int)(posy - diry * 0.05)][(int)posx] != '1')
			game->posy -= diry * 0.05;
	}
	if (game->d)
	{
		if (game->scene->map[(int)posy][(int)(posx + diry * (0.05 * 2))] != '1')
			game->posx += diry * 0.05;
		if (game->scene->map[(int)(posy - dirx * (0.05 * 2))][(int)posx] != '1')
			game->posy -= dirx * 0.05;
	}
	else if (game->a)
	{
		if (game->scene->map[(int)posy][(int)(posx - diry * (0.05 * 2))] != '1')
			game->posx -= diry * 0.05;
		if (game->scene->map[(int)(posy + dirx * (0.05 * 2))][(int)posx] != '1')
			game->posy += dirx * 0.05;
	}
}

static	int	ft_nextframe(t_game *game)
{
	t_frame frame;

	ft_handle_keys(game);
	frame = ft_render_frame(game);
    mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	mlx_destroy_image(game->mlx, frame.img);
	return (0);
}

t_game	ft_init_game(t_scene *scene)
{
	t_game	game;

	game.posx = scene->player.x;
	game.posy = scene->player.y;
	game.mlx = NULL;
	game.win = NULL;
	game.dirx = -1;
	game.diry = 0;
	game.planex = 0;
	game.planey = 0.66;
	game.w = false;
	game.a = false;
	game.s = false;
	game.d = false;
	return (game);
}

void	ft_graphic_handle(t_scene *scene)
{
	t_game	game;

	game = ft_init_game(scene);
	game.mlx = mlx_init();
	if (!game.mlx)
		ft_exit_str("Failed to connect to X server", scene, 5);
	game.win = mlx_new_window(game.mlx, scene->x_scr,
			scene->y_scr, "Cub3d");
	if (!game.win)
	{
		mlx_destroy_display(game.mlx);
		free(game.mlx);
		ft_exit_str("Failed to create the window", scene, 6);
	}
	game.scene = scene;
	mlx_hook(game.win, 33, 0, ft_event_exit, &game);
	mlx_hook(game.win, 2, 1L, ft_event_key, &game);
	mlx_hook(game.win, 3, 1L<<1, ft_event_key_release, &game);
    mlx_loop_hook(game.mlx, ft_nextframe, &game);
	mlx_loop(game.mlx);
}

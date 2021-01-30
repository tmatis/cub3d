/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:59:14 by tmatis            #+#    #+#             */
/*   Updated: 2021/01/29 21:01:44 by tmatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

static	void	ft_render_line(t_frame frame, int x, int y, int color)
{
	int	i;

	i = 0;
	while (i < x)
		ft_frame_pixel(frame, i++, y, color);
}

void	ft_render_cf(t_game *game)
{
	int color_c;
	int color_f;
	int	y;

	color_c = ft_trgb(0, game->scene->c.r, game->scene->c.g, game->scene->c.b);
	color_f = ft_trgb(0, game->scene->f.r, game->scene->f.g, game->scene->f.b);
	y = 0;
	while (y < (game->scene->y_scr / 2))
		ft_render_line(game->frame, game->scene->x_scr, y++, color_c);
	while (y < game->scene->y_scr)
		ft_render_line(game->frame, game->scene->x_scr, y++, color_f);
}

void	ft_render_frame(t_game *game)
{
	ft_render_cf(game);
	ft_render_raycast(game);
}

t_frame	ft_init_frame(t_game *game)
{
	t_frame	frame;

	frame.img = mlx_new_image(game->mlx, game->scene->x_scr,
			game->scene->y_scr);
	if (!frame.img)
	{
		ft_log_error("Unable to create frame");
		ft_clear_memory(game);
	}
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel,
			&frame.line_length, &frame.endian);
	return (frame);
}



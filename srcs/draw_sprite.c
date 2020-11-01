/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:32:49 by viroques          #+#    #+#             */
/*   Updated: 2020/10/31 20:20:49 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void			ft_sort_sprite(t_mlx *mlx, t_player *player)
{
	int			distance[mlx->count_sprite];
	int			i;
	int			tmp;
	t_sprite	tmp_sprite;

	tmp = 0;
	i = -1;
	while (++i < mlx->count_sprite)
		distance[i] = (player->pos_x - mlx->sprite[i].x) * (player->pos_x -
		mlx->sprite[i].x) + (player->pos_y - mlx->sprite[i].y)
		* (player->pos_y - mlx->sprite[i].y);
	i = -1;
	while (++i < mlx->count_sprite - 1)
	{
		if (distance[i] < distance[i + 1])
		{
			tmp = distance[i];
			distance[i] = distance[i + 1];
			distance[i + 1] = tmp;
			tmp_sprite = mlx->sprite[i];
			mlx->sprite[i] = mlx->sprite[i + 1];
			mlx->sprite[i + 1] = tmp_sprite;
			i = 0;
		}
	}
}

static void			info_sprite_2(t_mlx *mlx, t_info_s *info)
{
	if (info->draw_start_y < 0)
		info->draw_start_y = 0;
	info->draw_end_y = info->sprite_height / 2
	+ mlx->win_height / 2 + info->v_move_screen;
	if (info->draw_end_y >= mlx->win_height)
		info->draw_end_y = mlx->win_height - 1;
	info->sprite_width = abs((int)(mlx->win_height / (info->transform_y)));
	info->draw_start_x = -info->sprite_width / 2 + info->sprite_screen_x;
	if (info->draw_start_x < 0)
		info->draw_start_x = 0;
	info->draw_end_x = info->sprite_width / 2 + info->sprite_screen_x;
	if (info->draw_end_x >= mlx->win_width)
		info->draw_end_x = mlx->win_width - 1;
}

static void			info_sprite(t_mlx *mlx, t_player *p, t_info_s *info, int i)
{
	info->sprite_x = mlx->sprite[i].x - p->pos_x;
	info->sprite_y = mlx->sprite[i].y - p->pos_y;
	info->inv_det = 1.0 / (p->plan_x * p->dir_y - p->dir_x * p->plan_y);
	info->transform_x = info->inv_det *
	(p->dir_y * info->sprite_x - p->dir_x * info->sprite_y);
	info->transform_y = info->inv_det *
	(-p->plan_y * info->sprite_x + p->plan_x * info->sprite_y);
	info->text_width = mlx->texture[4]->width;
	info->text_height = mlx->texture[4]->height;
	info->v_move_screen = (int)(info->text_height / info->transform_y);
	info->sprite_screen_x = (int)(mlx->win_width / 2 *
	(1 + info->transform_x / info->transform_y));
	info->sprite_height = abs((int)(mlx->win_height / (info->transform_y)));
	info->draw_start_y = -info->sprite_height / 2 +
	mlx->win_height / 2 + info->v_move_screen;
	info_sprite_2(mlx, info);
}

static void			screen_sprite(t_mlx *mlx, t_info_s *info, int y, int stripe)
{
	int d;
	int tex_y;
	int color;

	d = (y - info->v_move_screen) * 256 - mlx->win_height
	* 128 + info->sprite_height * 128;
	tex_y = ((d * info->text_height) / info->sprite_height) / 256;
	color = mlx->texture[4]->data[info->text_width * tex_y + info->tex_x];
	if ((color & 0xffffff) != 0)
		mlx->img.data[y * mlx->win_width + stripe - 1] = color;
}

void				ft_draw_sprite(t_mlx *mlx, t_player *player)
{
	int			i;
	int			stripe;
	int			y;
	t_info_s	info;

	i = -1;
	ft_sort_sprite(mlx, player);
	while (++i < mlx->count_sprite)
	{
		info_sprite(mlx, player, &info, i);
		stripe = info.draw_start_x - 1;
		while (++stripe < info.draw_end_x)
		{
			info.tex_x = (int)(256 * (stripe - (-info.sprite_width / 2 +
			info.sprite_screen_x)) * info.text_width / info.sprite_width) / 256;
			if (info.transform_y > 0 && stripe > 0 && stripe < mlx->win_width
			&& info.transform_y < mlx->buff[stripe])
			{
				y = info.draw_start_y - 1;
				while (++y < info.draw_end_y)
					screen_sprite(mlx, &info, y, stripe);
			}
		}
	}
}

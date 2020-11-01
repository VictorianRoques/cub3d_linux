/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:33:30 by viroques          #+#    #+#             */
/*   Updated: 2020/11/01 18:19:40 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		ft_calcul_wall(t_vecteur *vec, int x, t_mlx *mlx)
{
	int line_height;
	int draw_start;
	int draw_end;

	line_height = (int)(mlx->win_height / vec->perp_wall_dist);
	mlx->vec.line_height = line_height;
	draw_start = -line_height / 2 + mlx->win_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + mlx->win_height / 2;
	if (draw_end >= mlx->win_height || draw_end < 0)
		draw_end = mlx->win_height - 1;
	draw_wall_text(x, draw_start, draw_end, mlx);
}

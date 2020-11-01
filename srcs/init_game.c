/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:33:05 by viroques          #+#    #+#             */
/*   Updated: 2020/10/31 20:47:15 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_malloc_text(t_mlx *mlx)
{
	int i;

	i = 0;
	if (!(mlx->texture = malloc(sizeof(t_img *) * 5)))
		return (error("Malloc texture failed\n", -1));
	while (i < 5)
	{
		if (!(mlx->texture[i] = malloc(sizeof(t_img))))
		{
			while (i >= 0)
			{
				free(mlx->texture[i]);
				i--;
			}
			return (error("Malloc texture failed\n", -1));
		}
		ft_bzero(mlx->texture[i], sizeof(t_img));
		i++;
	}
	mlx->tmp_free.tmp_texture = mlx->texture;
	return (0);
}

int		ft_init(t_mlx *mlx)
{
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->player.move_speed = 0.025;
	mlx->player.rotate_speed = 0.025;
	if (!(mlx->mlx_ptr = mlx_init()))
		return (error("mlx init failed\n", -1));
	return (1);
}

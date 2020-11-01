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

int		ft_init(t_mlx *mlx)
{
	ft_bzero(mlx, sizeof(t_mlx));
	if (!(mlx->mlx_ptr = mlx_init()))
		return (error("mlx init failed\n", -1));
	mlx->player.move_speed = 0.025;
	mlx->player.rotate_speed = 0.025;
	return (1);
}

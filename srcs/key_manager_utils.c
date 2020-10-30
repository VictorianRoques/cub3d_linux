/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:33:09 by viroques          #+#    #+#             */
/*   Updated: 2020/10/30 21:33:10 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					key_press(int keycode, t_mlx *mlx)
{
	if (keycode > 65363)
		return (0);
	mlx->keyboard[keycode] = 1;
	return (0);
}
int					key_release(int keycode, t_mlx *mlx)
{
	if (keycode > 65363)
		return (0);
	mlx->keyboard[keycode] = 0;
	return (0);
}
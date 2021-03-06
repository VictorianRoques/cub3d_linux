/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:33:12 by viroques          #+#    #+#             */
/*   Updated: 2020/10/31 20:55:25 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	void		move_manager_right_left(t_mlx *mlx)
{
	if (mlx->keyboard[KEY_A])
	{
		if (mlx->map.world_map[(int)(mlx->player.pos_x - mlx->player.plan_x
		* mlx->player.move_speed)][(int)mlx->player.pos_y] != 1)
			mlx->player.pos_x -= mlx->player.plan_x * mlx->player.move_speed;
		if (mlx->map.world_map[(int)mlx->player.pos_x][(int)(mlx->player.pos_y
		- mlx->player.plan_y * mlx->player.move_speed)] != 1)
			mlx->player.pos_y -= mlx->player.plan_y * mlx->player.move_speed;
	}
	if (mlx->keyboard[KEY_D])
	{
		if (mlx->map.world_map[(int)(mlx->player.pos_x + mlx->player.plan_x *
		mlx->player.move_speed)][(int)mlx->player.pos_y] != 1)
			mlx->player.pos_x += mlx->player.plan_x * mlx->player.move_speed;
		if (mlx->map.world_map[(int)mlx->player.pos_x][(int)(mlx->player.pos_y
		+ mlx->player.plan_y * mlx->player.move_speed)] != 1)
			mlx->player.pos_y += mlx->player.plan_y * mlx->player.move_speed;
	}
}

static	void		move_manager_up_down(t_mlx *mlx)
{
	if (mlx->keyboard[KEY_W])
	{
		if (mlx->map.world_map[(int)(mlx->player.pos_x + mlx->player.dir_x
		* mlx->player.move_speed)][(int)mlx->player.pos_y] != 1)
			mlx->player.pos_x += mlx->player.dir_x * mlx->player.move_speed;
		if (mlx->map.world_map[(int)(mlx->player.pos_x)][(int)(mlx->player.pos_y
		+ mlx->player.dir_y * mlx->player.move_speed)] != 1)
			mlx->player.pos_y += mlx->player.dir_y * mlx->player.move_speed;
	}
	if (mlx->keyboard[KEY_S])
	{
		if (mlx->map.world_map[(int)(mlx->player.pos_x - mlx->player.dir_x
		* mlx->player.move_speed)][(int)(mlx->player.pos_y)] != 1)
			mlx->player.pos_x -= mlx->player.dir_x * mlx->player.move_speed;
		if (mlx->map.world_map[(int)(mlx->player.pos_x)][(int)(mlx->player.pos_y
		- mlx->player.dir_y * mlx->player.move_speed)] != 1)
			mlx->player.pos_y -= mlx->player.dir_y * mlx->player.move_speed;
	}
}

static void			rotate_left(t_mlx *mlx)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = mlx->player.dir_x;
	old_plane_x = mlx->player.plan_x;
	mlx->player.dir_x = mlx->player.dir_x * cos(mlx->player.rotate_speed)
	- mlx->player.dir_y * sin(mlx->player.rotate_speed);
	mlx->player.dir_y = old_dir_x * sin(mlx->player.rotate_speed)
	+ mlx->player.dir_y * cos(mlx->player.rotate_speed);
	mlx->player.plan_x = mlx->player.plan_x * cos(mlx->player.rotate_speed)
	- mlx->player.plan_y * sin(mlx->player.rotate_speed);
	mlx->player.plan_y = old_plane_x * sin(mlx->player.rotate_speed)
	+ mlx->player.plan_y * cos(mlx->player.rotate_speed);
}

static	void		rotate_manager(t_mlx *mlx)
{
	double old_dir_x;
	double old_plane_x;

	if (mlx->keyboard[KEY_RIGHT])
	{
		old_dir_x = mlx->player.dir_x;
		old_plane_x = mlx->player.plan_x;
		mlx->player.dir_x = mlx->player.dir_x * cos(-mlx->player.rotate_speed)
		- mlx->player.dir_y * sin(-mlx->player.rotate_speed);
		mlx->player.dir_y = old_dir_x * sin(-mlx->player.rotate_speed)
		+ mlx->player.dir_y * cos(-mlx->player.rotate_speed);
		mlx->player.plan_x = mlx->player.plan_x * cos(-mlx->player.rotate_speed)
		- mlx->player.plan_y * sin(-mlx->player.rotate_speed);
		mlx->player.plan_y = old_plane_x * sin(-mlx->player.rotate_speed)
		+ mlx->player.plan_y * cos(-mlx->player.rotate_speed);
	}
	if (mlx->keyboard[KEY_LEFT])
		rotate_left(mlx);
}

int					ft_keyboard_manager(t_mlx *mlx)
{
	move_manager_right_left(mlx);
	move_manager_up_down(mlx);
	rotate_manager(mlx);
	ft_raycasting(mlx, &mlx->vec, &mlx->player);
	if (mlx->keyboard[KEY_ESC])
		return (exit_game(mlx));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:33:36 by viroques          #+#    #+#             */
/*   Updated: 2020/11/01 18:22:36 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void		fill_theader_bmp(t_mlx *mlx, t_bmp_header *theader)
{
	theader->type = 0x4d42;
	theader->offset = 0x36;
	theader->dib_header_size = 0x28;
	theader->width_px = mlx->win_width;
	theader->height_px = mlx->win_height;
	theader->num_planes = 0x01;
	theader->bits_per_pixel = 0x20;
}

static void		write_header_bmp(t_bmp_header *theader, int fd)
{
	write(fd, &(theader->type), 2);
	write(fd, &(theader->size), 4);
	write(fd, &(theader->reserved1), 2);
	write(fd, &(theader->reserved2), 2);
	write(fd, &(theader->offset), 4);
	write(fd, &(theader->dib_header_size), 4);
	write(fd, &(theader->width_px), 4);
	write(fd, &(theader->height_px), 4);
	write(fd, &(theader->num_planes), 2);
	write(fd, &(theader->bits_per_pixel), 2);
	write(fd, &(theader->compression), 4);
	write(fd, &(theader->image_size_bytes), 4);
	write(fd, &(theader->x_resolution_ppm), 4);
	write(fd, &(theader->y_resolution_ppm), 4);
	write(fd, &(theader->num_colors), 4);
	write(fd, &(theader->important_colors), 4);
}

static int		write_bmp_file(t_mlx *mlx)
{
	int				fd;
	int				size;
	t_bmp_header	theader;

	ft_bzero(&theader, sizeof(t_bmp_header));
	fill_theader_bmp(mlx, &theader);
	size = mlx->win_height * mlx->win_width;
	fd = open("screenshot.bmp", O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0666);
	write_header_bmp(&theader, fd);
	while (size)
	{
		size -= mlx->win_width;
		write(fd, &mlx->img.data[size], mlx->win_width * 4);
	}
	close(fd);
	return (0);
}

int				screenshot(t_mlx *mlx, char *argv)
{
	if (ft_init(mlx) < 0)
		exit(0);
	if (parsing_map(mlx, argv) < 0)
		return (exit_game_err(mlx));
	mlx->save = 1;
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->win_width,
	mlx->win_height);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
	&mlx->img.size_l, &mlx->img.endian);
	ft_raycasting(mlx, &mlx->vec, &mlx->player);
	write_bmp_file(mlx);
	free_map_world_and_text(mlx);
	return (0);
}

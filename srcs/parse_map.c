/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:33:27 by viroques          #+#    #+#             */
/*   Updated: 2020/11/01 18:00:11 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char		*read_file(char *stock, char *path)
{
	int		ret;
	int		fd;
	char	*tmp;
	char	buff[4096];

	if (!(stock = malloc(sizeof(char))))
		return (error_char("Malloc failed in read file\n", NULL));
	stock[0] = '\0';
	if ((fd = open(path, __O_DIRECTORY) != -1))
		return (error_char("file .cub is a directory\n", NULL));
	if ((fd = open(path, O_RDONLY)) < 0)
		return (error_char("Invalid path can't read the file\n", NULL));
	while ((ret = read(fd, buff, 4096)))
	{
		buff[ret] = '\0';
		tmp = stock;
		if (!(stock = ft_strjoin(tmp, buff)))
		{
			free(tmp);
			return (error_char("Malloc failed strjoin in read_file\n", NULL));
		}
		free(tmp);
	}
	close(fd);
	return (stock);
}

int				parsing_map(t_mlx *mlx, char *path)
{
	char *stock;

	if (ft_strncmp(".cub", path + ft_strlen(path) - 4, 4))
		return (error("Format file must be end by .cub\n", -1));
	stock = NULL;
	if (!(stock = read_file(stock, path)))
		return (-1);
	if (!(mlx->file = ft_split(stock, '\n')))
		return (error_custom("Maloc failed in ft_read_map", -1, stock));
	if (!(mlx->file_n = ft_split_sep(stock, '\n')))
	{
		free(stock);
		return (error_free("Maloc failed in ft_read_map", -1, mlx->file));
	}
	free(stock);
	if (parse_header_map(mlx, mlx->file, mlx->file_n) < 0)
	{
		ft_free_tab(mlx->file_n);
		ft_free_tab(mlx->file);
		return (-1);
	}
	ft_free_tab(mlx->file);
	ft_free_tab(mlx->file_n);
	return (0);
}

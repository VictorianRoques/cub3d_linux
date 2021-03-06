/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 21:32:56 by viroques          #+#    #+#             */
/*   Updated: 2020/10/31 20:48:12 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int			error(char *msg, int ret)
{
	write(2, "Error\n", 7);
	write(2, msg, ft_strlen(msg));
	return (ret);
}

char		*error_char(char *msg, char *err)
{
	write(2, "Error\n", 7);
	write(2, msg, ft_strlen(msg));
	return (err);
}

int			error_free(char *msg, int ret, char **tab)
{
	ft_free_tab(tab);
	write(2, "Error\n", 7);
	write(2, msg, ft_strlen(msg));
	return (ret);
}

int			error_custom(char *msg, int ret, char *stock)
{
	free(stock);
	write(2, "Error\n", 7);
	write(2, msg, ft_strlen(msg));
	return (ret);
}

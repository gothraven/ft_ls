/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:00:55 by szaghban          #+#    #+#             */
/*   Updated: 2018/11/01 15:31:34 by szaghban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_print_void(int k)
{
	while (--k >= 0)
		write(1, " ", 1);
}

void	display2(char *name)
{
	write(1, name, ft_strlen(name));
	write(1, ":\n", 2);
}

void	display(char *name, t_bool ld, char *path, t_place *max)
{
	struct stat		flst;
	char			*mem;
	char			*link;

	if (ld == TRUE)
	{
		long_display(name, path, max);
		write(1, " ", 1);
		write(1, name, ft_strlen(name));
		mem = ft_str_dupncat(path, name);
		lstat(mem, &flst);
		if (S_ISLNK(flst.st_mode) == 1)
		{
			if ((link = malloc(sizeof(char) * 1024)) == NULL)
				exit(0);
			link[readlink(mem, link, 1023)] = '\0';
			write(1, " -> ", 4);
			write(1, link, ft_strlen(link));
			free(link);
		}
		free(mem);
	}
	else
		write(1, name, ft_strlen(name));
	write(1, "\n", 1);
}

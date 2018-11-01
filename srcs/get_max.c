/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:01:18 by szaghban          #+#    #+#             */
/*   Updated: 2018/11/01 17:50:57 by szaghban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		check_file(char *file, t_bool m, t_place *max)
{
	struct stat		flst;
	struct group	*grp;
	struct passwd	*pwd;
	int				mem;

	lstat(file, &flst);
	if ((mem = ft_strlen(ft_itoa(flst.st_nlink))) > max->links)
		max->links = mem;
	if ((pwd = getpwuid(flst.st_uid)) != NULL)
		if ((mem = ft_strlen(pwd->pw_name)) > max->u_id)
			max->u_id = mem;
	if ((grp = getgrgid(flst.st_gid)) != NULL)
		if ((mem = ft_strlen(grp->gr_name)) > max->g_id)
			max->g_id = mem;
	if (S_ISCHR(flst.st_mode) || S_ISBLK(flst.st_mode))
	{
		if ((mem = (ft_strlen(ft_itoa((flst.st_rdev >> 24) & 0xff)) +
				ft_strlen(ft_itoa(flst.st_rdev & 0xffffff)) + 5)) > max->size)
			max->size = mem;
	}
	else if ((mem = ft_strlen(ft_itoa(flst.st_size))) > max->size)
		max->size = mem;
	if (S_ISREG(flst.st_mode) == 1 || S_ISLNK(flst.st_mode) == 1)
		max->blocks = max->blocks + flst.st_blocks;
	(m == TRUE) ? free(file) : 0;
}

static void	print_blocks(char *yay)
{
	write(1, "total ", 6);
	write(1, yay, ft_strlen(yay));
	write(1, "\n", 1);
	free(yay);
}

t_place		*get_max(t_fnode *node, char *path, t_bool l)
{
	t_place	*max;
	t_fnode	*loop;

	if (l == FALSE)
		return (NULL);
	if ((max = malloc(sizeof(*max))) == NULL)
		exit(0);
	max->links = 0;
	max->u_id = 4;
	max->g_id = 4;
	max->size = 0;
	max->blocks = 0;
	loop = node;
	while (loop)
	{
		if (path != NULL)
			check_file(ft_str_dupncat(path, loop->name), TRUE, max);
		else
			check_file(loop->name, FALSE, max);
		loop = loop->next;
	}
	if (loop != node)
		print_blocks(ft_itoa(max->blocks));
	return (max);
}

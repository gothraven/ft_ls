/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lst_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:00:31 by szaghban          #+#    #+#             */
/*   Updated: 2018/11/01 15:31:16 by szaghban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_fnode	*lst_delone(t_flist *dir_list, t_fnode *loop)
{
	t_fnode *clean;

	if (loop == dir_list->first)
	{
		dir_list->first = dir_list->first->next;
		free(loop->name);
		free(loop);
		loop = dir_list->first;
	}
	else
	{
		clean = dir_list->first;
		while (clean->next != loop)
			clean = clean->next;
		clean->next = clean->next->next;
		free(loop->name);
		free(loop);
		loop = clean->next;
	}
	return (loop);
}

static t_place	*for_ld(t_flist *dir_list)
{
	t_place		*max;
	t_fnode		*loop;
	struct stat loop_stat;

	max = malloc(sizeof(*max));
	if (max == NULL)
		exit(0);
	max->links = 0;
	max->u_id = 4;
	max->g_id = 4;
	max->size = 0;
	max->blocks = 0;
	loop = dir_list->first;
	while (loop != NULL)
	{
		lstat(loop->name, &loop_stat);
		if (!(S_ISDIR(loop_stat.st_mode)))
			check_file(loop->name, FALSE, max);
		loop = loop->next;
	}
	return (max);
}

void			clean_lst_files(t_flist *dir_list, t_options *ls_options)
{
	t_fnode		*loop;
	t_place		*max;
	struct stat loop_stat;

	if (ls_options->long_display == TRUE)
		max = for_ld(dir_list);
	loop = dir_list->first;
	while (loop != NULL)
	{
		lstat(loop->name, &loop_stat);
		if (!(S_ISDIR(loop_stat.st_mode)) || (S_ISLNK(loop_stat.st_mode) &&
					ls_options->long_display == TRUE &&
					*(ft_strrchr(loop->name, '/') + 1) != '\0'))
		{
			display(loop->name, ls_options->long_display, NULL, max);
			loop = lst_delone(dir_list, loop);
		}
		else
			loop = loop->next;
	}
	if (ls_options->long_display == TRUE)
		free(max);
}

void			element_exist(t_flist *dir_list, t_options *ls_options)
{
	struct stat	name_stat;
	t_fnode		*loop;

	loop = dir_list->first;
	while (loop != NULL)
	{
		if (stat(loop->name, &name_stat) != 0)
		{
			write(2, "ls: ", 4);
			write(2, loop->name, ft_strlen(loop->name));
			write(2, ": No such file or directory\n", 28);
			loop = lst_delone(dir_list, loop);
			ls_options->error = TRUE;
		}
		else
			loop = loop->next;
	}
}

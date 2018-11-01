/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_simulator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:01:45 by szaghban          #+#    #+#             */
/*   Updated: 2018/11/01 15:35:44 by szaghban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_flist	*display_cont(t_fnode *node, t_options *ls_options, char *path)
{
	char		*new_name;
	t_place		*max;
	t_flist		*new_dir_list;
	struct stat	fill_stat;

	if (ls_options->recursive == TRUE)
		new_dir_list = ft_list_set();
	max = get_max(node, path, ls_options->long_display);
	while (node != NULL)
	{
		new_name = NULL;
		if (ls_options->recursive == TRUE && ft_strcmp(node->name, ".") != 0 &&
				ft_strcmp(node->name, "..") != 0)
			if ((new_name = ft_str_dupncat(path, node->name)) != NULL &&
				lstat(new_name, &fill_stat) == 0 && S_ISDIR(fill_stat.st_mode))
				add_node(new_dir_list->first, new_name);
		free(new_name);
		display(node->name, ls_options->long_display, path, max);
		node = del_node(node);
	}
	if (ls_options->recursive == FALSE)
		return (NULL);
	free(max);
	new_dir_list->first = del_node(new_dir_list->first);
	return (new_dir_list);
}

static t_fnode	*fill_content(char *path, t_fnode *node, t_options *ls_options)
{
	DIR				*to_read;
	struct dirent	*to_stock;

	if ((to_read = opendir(path)) == NULL)
	{
		write(2, "ls: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": Permission denied\n", 20);
		ls_options->error = TRUE;
	}
	else
	{
		while ((to_stock = readdir(to_read)) != NULL)
			if (to_stock->d_name[0] != '.' || ls_options->hidden_files == TRUE)
				add_node(node, to_stock->d_name);
		closedir(to_read);
	}
	node = del_node(node);
	return (node);
}

void			ls_simulator(t_flist *dir_list, t_options *ls_options)
{
	t_flist	*content;
	t_flist	*new_dir_list;
	t_fnode	*loop;

	loop = dir_list->first;
	while (loop != NULL)
	{
		if (dir_list->first->next != NULL)
			display2(loop->name);
		content = ft_list_set();
		content->first = fill_content(loop->name, content->first, ls_options);
		list_sort(content, ls_options, loop->name);
		new_dir_list = display_cont(content->first, ls_options, loop->name);
		if (new_dir_list != NULL && new_dir_list->first != NULL)
		{
			write(1, "\n", 1);
			list_sort(new_dir_list, ls_options, NULL);
			if (new_dir_list->first->next == NULL)
				display2(new_dir_list->first->name);
			ls_simulator(new_dir_list, ls_options);
		}
		if ((loop = loop->next) != NULL)
			write(1, "\n", 1);
	}
}

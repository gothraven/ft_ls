/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:01:26 by szaghban          #+#    #+#             */
/*   Updated: 2018/11/01 15:33:31 by szaghban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	timecmp(char *browse, char *mem, char *path)
{
	char		*browse2;
	char		*mem2;
	struct stat	browse_stat;
	struct stat	mem_stat;

	if (path != NULL)
	{
		browse2 = ft_str_dupncat(path, browse);
		lstat(browse2, &browse_stat);
		free(browse2);
		mem2 = ft_str_dupncat(path, mem);
		lstat(mem2, &mem_stat);
		free(mem2);
	}
	else
	{
		lstat(browse, &browse_stat);
		lstat(mem, &mem_stat);
	}
	if (browse_stat.st_mtime < mem_stat.st_mtime)
		return (1);
	if (browse_stat.st_mtime > mem_stat.st_mtime)
		return (-1);
	return (0);
}

static void	time_sort(t_fnode *first_node, char *path, t_bool r)
{
	t_fnode *sort;
	t_fnode *browse;
	t_fnode *mem;
	char	*tmp;
	int		res;

	sort = first_node;
	while (sort != NULL)
	{
		browse = sort;
		mem = sort;
		while ((browse = browse->next) != NULL)
		{
			if ((res = timecmp(browse->name, mem->name, path)) == 0)
				res = ft_strcmp(browse->name, mem->name);
			if ((res < 0 && r == FALSE) || (res > 0 && r == TRUE))
				mem = browse;
		}
		if (mem != sort && ((tmp = sort->name) != NULL))
		{
			sort->name = mem->name;
			mem->name = tmp;
		}
		sort = sort->next;
	}
}

static void	name_sort(t_fnode *first_node, t_bool r)
{
	t_fnode	*sort;
	t_fnode	*browse;
	t_fnode	*mem;
	char	*tmp;

	sort = first_node;
	while (sort != NULL)
	{
		browse = sort;
		mem = sort;
		while ((browse = browse->next) != NULL)
			if ((ft_strcmp(browse->name, mem->name) < 0 && r == FALSE) ||
					(ft_strcmp(browse->name, mem->name) > 0 && r == TRUE))
				mem = browse;
		if (sort != mem)
		{
			tmp = sort->name;
			sort->name = mem->name;
			mem->name = tmp;
		}
		sort = sort->next;
	}
}

void		list_sort(t_flist *first_node, t_options *ls_options, char *path)
{
	if (first_node == NULL || first_node->first == NULL)
		return ;
	if (ls_options->time_order == TRUE)
		time_sort(first_node->first, path, ls_options->reverse_order);
	else
		name_sort(first_node->first, ls_options->reverse_order);
}

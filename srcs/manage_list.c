/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:01:57 by szaghban          #+#    #+#             */
/*   Updated: 2018/11/01 15:40:30 by szaghban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_options	*ft_options_set(void)
{
	t_options	*ls_options;

	ls_options = malloc(sizeof(*ls_options));
	if (ls_options == NULL)
		exit(0);
	ls_options->long_display = FALSE;
	ls_options->recursive = FALSE;
	ls_options->hidden_files = FALSE;
	ls_options->reverse_order = FALSE;
	ls_options->time_order = FALSE;
	ls_options->error = FALSE;
	return (ls_options);
}

t_flist		*ft_list_set(void)
{
	t_flist	*dir_list;
	t_fnode *set;

	if ((dir_list = malloc(sizeof(*dir_list))) == NULL)
		exit(0);
	if ((set = malloc(sizeof(*set))) == NULL)
		exit(0);
	if ((set->name = ft_strdup(".")) == NULL)
		exit(0);
	set->next = NULL;
	dir_list->first = set;
	return (dir_list);
}

void		add_node(t_fnode *chain_fill, char *argv)
{
	t_fnode *set;
	t_fnode	*end;

	if ((set = malloc(sizeof(*set))) == NULL)
		exit(0);
	set->next = NULL;
	if ((set->name = ft_strdup(argv)) == NULL)
		exit(0);
	end = chain_fill;
	while (end->next != NULL)
		end = end->next;
	end->next = set;
}

t_fnode		*del_node(t_fnode *chain_del)
{
	t_fnode *mem;

	mem = chain_del->next;
	free(chain_del->name);
	free(chain_del);
	return (mem);
}

char		*ft_str_dupncat(char *name1, char *name2)
{
	char	*mem;
	size_t	size;

	size = ft_strlen(name1) + ft_strlen(name2) + 2;
	if ((mem = malloc(sizeof(char) * (size))) == NULL)
		exit(0);
	if (name1 != NULL)
	{
		ft_strcpy(mem, name1);
		ft_strcat(mem, "/");
		ft_strcat(mem, name2);
	}
	else
		ft_strcpy(mem, name2);
	return (mem);
}

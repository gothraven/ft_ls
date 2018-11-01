/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:00:02 by szaghban          #+#    #+#             */
/*   Updated: 2018/11/01 15:29:36 by szaghban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	check_options(t_options *ls_options, char *argv)
{
	if (*(argv + 1) == '-' && *(argv + 2) == '\0')
		return (1);
	while (*(++argv) != '\0')
	{
		if (*(argv) == 'l')
			ls_options->long_display = TRUE;
		if (*(argv) == 'R')
			ls_options->recursive = TRUE;
		if (*(argv) == 'a')
			ls_options->hidden_files = TRUE;
		if (*(argv) == 'r')
			ls_options->reverse_order = TRUE;
		if (*(argv) == 't')
			ls_options->time_order = TRUE;
		if (*(argv) != 'l' && *(argv) != 'R' && *(argv) != 'a' &&
				*(argv) != 'r' && *(argv) != 't')
		{
			write(2, "ls: illegal option -- ", 22);
			write(2, argv, 1);
			write(2, "\nusage: ls [-Ralrt] [file ...]\n", 32);
			exit(1);
		}
	}
	return (0);
}

int			check_arg(t_options *ls_options, t_flist *dir_list, char **argv)
{
	int		loop;
	int		ac;
	t_fnode	*chain_fill;

	loop = 0;
	chain_fill = dir_list->first;
	while (argv[loop] && argv[loop][0] == '-' &&
			check_options(ls_options, argv[loop]) == 0)
		loop++;
	if (argv[loop] && ft_strcmp(argv[loop], "--") == 0)
		loop++;
	ac = loop;
	while (argv[loop])
	{
		if (ft_strlen(argv[loop]) == 0)
		{
			write(2, "ls: fts_open: No such file or directory\n", 40);
			exit(1);
		}
		add_node(chain_fill, argv[loop]);
		loop++;
	}
	if (dir_list->first->next != NULL)
		dir_list->first = del_node(dir_list->first);
	return (loop - ac);
}

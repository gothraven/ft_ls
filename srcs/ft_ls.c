/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:01:07 by szaghban          #+#    #+#             */
/*   Updated: 2018/11/01 15:31:57 by szaghban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	main(int argc, char **argv)
{
	t_options	*ls_options;
	t_flist		*dir_list;
	int			ac;

	ls_options = NULL;
	ls_options = ft_options_set();
	dir_list = NULL;
	dir_list = ft_list_set();
	if (argc > 1)
	{
		ac = check_arg(ls_options, dir_list, argv + 1);
		list_sort(dir_list, ls_options, NULL);
		element_exist(dir_list, ls_options);
		clean_lst_files(dir_list, ls_options);
		if (ac > 1 && dir_list && dir_list->first)
		{
			write(1, "\n", 1);
			if (dir_list->first->next == NULL)
				display2(dir_list->first->name);
		}
	}
	ls_simulator(dir_list, ls_options);
	return (ls_options->error);
}

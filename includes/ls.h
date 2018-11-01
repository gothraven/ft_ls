/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:02:05 by szaghban          #+#    #+#             */
/*   Updated: 2018/11/01 15:47:37 by szaghban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# define TRUE 1
# define FALSE 0

# define MINOR(x) ((x) & 0xffffff)
# define MAJOR(x) (((x) >> 24) & 0xff)

typedef int			t_bool;

typedef	struct		s_fnode
{
	char			*name;
	struct s_fnode	*next;
}					t_fnode;

typedef struct		s_place
{
	int				links;
	int				u_id;
	int				g_id;
	int				size;
	int				blocks;
}					t_place;

typedef struct		s_flist
{
	t_fnode			*first;
}					t_flist;

typedef struct		s_options
{
	t_bool			long_display;
	t_bool			recursive;
	t_bool			hidden_files;
	t_bool			reverse_order;
	t_bool			time_order;
	t_bool			error;
}					t_options;

t_options			*ft_options_set(void);
t_flist				*ft_list_set(void);
int					check_arg(t_options *ls_options, t_flist *dir_list, char **argv);
void				list_sort(t_flist *dir_list, t_options *ls_options, char *path);
void				element_exist(t_flist *dir_list, t_options *ls_options);
void				ls_simulator(t_flist *dir_list, t_options *ls_options);
void				clean_lst_files(t_flist *dir_list, t_options *ls_options);
void				display(char *name, t_bool l, char *path, t_place *max);
void				long_display(char *file, char *path, t_place *max);
void				display2(char *name);
void				ls_simulator(t_flist *dir_list, t_options *ls_options);
void				add_node(t_fnode *chain_fill, char *argv);
t_fnode				*del_node(t_fnode *chain_del);
char				*ft_str_dupncat(char *name1, char *name2);
t_place				*get_max(t_fnode *node, char *path, t_bool l);
void				check_file(char *file, t_bool m, t_place *max);
void				ft_print_void(int k);

#endif

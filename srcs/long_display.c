/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szaghban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:01:35 by szaghban          #+#    #+#             */
/*   Updated: 2018/11/01 15:33:48 by szaghban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	long_display4(struct stat flst, t_place *max)
{
	char	*mem;

	if (S_ISCHR(flst.st_mode) || S_ISBLK(flst.st_mode))
	{
		mem = ft_itoa(MAJOR(flst.st_rdev));
		ft_print_void(max->size - ft_strlen(mem) - 4);
		write(1, mem, ft_strlen(mem));
		free(mem);
		write(1, ",", 1);
		mem = ft_itoa(MINOR(flst.st_rdev));
		ft_print_void(max->size - ft_strlen(mem) - 5);
		write(1, mem, ft_strlen(mem));
		free(mem);
	}
	else
	{
		mem = ft_itoa(flst.st_size);
		ft_print_void(max->size - ft_strlen(mem) + 2);
		write(1, mem, ft_strlen(mem));
		free(mem);
	}
	ft_print_void(1);
}

static void	long_display3_5(struct stat flst, t_place *max)
{
	char			*mem;
	struct group	*grp;

	write(1, "  ", 2);
	if ((grp = getgrgid(flst.st_gid)) != NULL)
	{
		write(1, grp->gr_name, ft_strlen(grp->gr_name));
		ft_print_void(max->g_id - ft_strlen(grp->gr_name));
	}
	else
	{
		mem = ft_itoa(flst.st_gid);
		write(1, mem, ft_strlen(mem));
		ft_print_void(max->g_id - ft_strlen(mem));
		free(mem);
	}
}

static void	long_display3(struct stat flst, t_place *max)
{
	char			*mem;
	struct passwd	*pwd;

	mem = ft_itoa(flst.st_nlink);
	ft_print_void(max->links - ft_strlen(mem) + 1);
	write(1, mem, ft_strlen(mem));
	free(mem);
	write(1, " ", 1);
	if ((pwd = getpwuid(flst.st_uid)) != NULL)
		write(1, pwd->pw_name, ft_strlen(pwd->pw_name));
	ft_print_void((pwd != NULL) ? max->u_id - ft_strlen(pwd->pw_name) : 0);
	if (pwd == NULL)
	{
		mem = ft_itoa(flst.st_uid);
		write(1, mem, ft_strlen(mem));
		ft_print_void(max->u_id - ft_strlen(mem));
		free(mem);
	}
	long_display3_5(flst, max);
}

static void	long_display2(struct stat flst)
{
	if (S_ISDIR(flst.st_mode))
		write(1, "d", 1);
	else if (S_ISCHR(flst.st_mode))
		write(1, "c", 1);
	else if (S_ISBLK(flst.st_mode))
		write(1, "b", 1);
	else if (S_ISFIFO(flst.st_mode))
		write(1, "p", 1);
	else if (S_ISLNK(flst.st_mode))
		write(1, "l", 1);
	else
		write(1, (S_ISSOCK(flst.st_mode)) ? "s" : "-", 1);
	write(1, (flst.st_mode & S_IRUSR) ? "r" : "-", 1);
	write(1, (flst.st_mode & S_IWUSR) ? "w" : "-", 1);
	if (flst.st_mode & S_ISUID)
		write(1, (flst.st_mode & S_IXUSR) ? "s" : "S", 1);
	else
		write(1, (flst.st_mode & S_IXUSR) ? "x" : "-", 1);
	write(1, (flst.st_mode & S_IRGRP) ? "r" : "-", 1);
	write(1, (flst.st_mode & S_IWGRP) ? "w" : "-", 1);
	if (flst.st_mode & S_ISGID)
		write(1, (flst.st_mode & S_IXGRP) ? "s" : "S", 1);
	else
		write(1, (flst.st_mode & S_IXGRP) ? "x" : "-", 1);
	write(1, (flst.st_mode & S_IROTH) ? "r" : "-", 1);
}

void		long_display(char *file, char *path, t_place *max)
{
	struct stat		flst;
	char			*mem;
	time_t			now;

	mem = ft_str_dupncat(path, file);
	lstat(mem, &flst);
	long_display2(flst);
	write(1, (flst.st_mode & S_IWOTH) ? "w" : "-", 1);
	if (flst.st_mode & S_ISVTX)
		write(1, (flst.st_mode & S_IXOTH) ? "t" : "T", 1);
	else
		write(1, (flst.st_mode & S_IXOTH) ? "x" : "-", 1);
	write(1, (listxattr(mem, NULL, 0, XATTR_NOFOLLOW) > 0) ? "@" : " ", 1);
	free(mem);
	long_display3(flst, max);
	long_display4(flst, max);
	now = time(0);
	if ((now - 6 * 30.5 * 24 * 60 * 60) > flst.st_mtime || now < flst.st_mtime)
	{
		write(1, (ctime(&flst.st_mtime) + 4), 6);
		ft_print_void(2);
		write(1, (ctime(&flst.st_mtime) + 20), 4);
	}
	else
		write(1, (ctime(&flst.st_mtime) + 4), 12);
}

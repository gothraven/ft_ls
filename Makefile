# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: szaghban <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/01 14:59:31 by szaghban          #+#    #+#              #
#    Updated: 2018/11/01 15:46:45 by szaghban         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = gcc
CFLAGS = -g3 -fsanitize=address -Wall -Werror -Wextra
LIBFTL = -L./libft -lft
MLXL = -L./minilibx_macos -lmlx

SRCS = $(addprefix $(SRCDIR), $(SRCFILES))
OBJS = $(addprefix $(OBJDIR), $(SRCFILES:.c=.o))

OBJDIR = ./objs/
SRCDIR = ./srcs/
INCDIR = ./includes/

SRCFILES =	check_arg.c clean_lst_files.c display.c \
			ft_ls.c get_max.c list_sort.c \
			long_display.c ls_simulator.c manage_list.c

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFTL) -o $(NAME)

clean:
	make -C ./libft clean
	rm -fr $(OBJDIR)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all

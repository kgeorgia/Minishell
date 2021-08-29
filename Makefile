# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgeorgia <kgeorgia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/17 16:07:07 by kgeorgia          #+#    #+#              #
#    Updated: 2021/08/29 19:08:50 by kgeorgia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			minishell

CC =			gcc

FLAGS =			-Wall -Wextra -Werror -g

RM =			rm -rf

DIR_HEADERS =	./includes/

DIR_LIBFT	=	./libft/

DIR_SRCS =		./srcs/

DIR_OBJS =		./objs/

LIBFT	=		./libft/libft.a

SRC =			main.c\
		parser/parser.c			parser/parser_utils.c		parser/replace_env.c\
		executor/executor.c		executor/check_cmd.c		executor/builtins.c\
		executor/exec_utils.c	executor/exec_utils_2.c		executor/redirect.c


SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

OBJS =			$(SRCS:.c=.o)

OBJS_2 =		$(subst $(DIR_SRCS), $(DIR_OBJS), $(SRCS:.c=.o))

all:			$(NAME)

$(NAME) :		$(OBJS_2)
				@make -C $(DIR_LIBFT)
				@gcc $(FLAGS) -I $(DIR_SRCS) -I $(DIR_LIBFT) $(OBJS_2) $(LIBFT) readline/libhistory.a readline/libreadline.a -ltermcap -o $(NAME)
				@echo "Compiled "$(NAME)" successfully!"

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				@gcc $(FLAGS) -I $(DIR_SRCS) -I $(DIR_LIBFT) -c $< -o $@
				@echo "Compiled "$<" successfully!"

norme:
				norminette $(DIR_SRCS)
				norminette $(DIR_HEADERS)

clean:
				$(RM) $(OBJS_2)
				make -C ./libft/ clean

fclean:			clean
				make -C ./libft/ fclean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all, clean, fclean, re, bonus
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efumiko <efumiko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/30 23:45:09 by ddraco            #+#    #+#              #
#    Updated: 2020/12/31 00:39:51 by efumiko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c parser/cmd.c parser/parser.c \
parser/pipes.c parser/redirects.c parser/redirects_work.c parser/semicolon.c \
parser/redirects_struct.c parser/workers.c utils/array_utils.c utils/array_utils2.c \
utils/array_utils3.c utils/error_message.c utils/error_message2.c \
get_next_line/get_next_line.c commands/unset.c \
commands/pwd.c commands/ft_command.c commands/export.c \
commands/exit.c commands/env.c commands/echo.c commands/cd.c

OBJ = $(SRC:.c=.o)

HEADER = minishell.h

FLAGS = -Wall -Werror -Wextra -I./includes

all: $(NAME)

$(NAME):$(OBJ)
	$(MAKE) bonus -C libft
	cp libft/libft.a .
	cc -o $(NAME) $(FLAGS) $(OBJ) -L. -lft

clean:
	rm -rf $(OBJ)
	$(MAKE) clean -C libft

fclean: clean
	rm -rf libft.a
	rm -rf $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: all clean fclean re run
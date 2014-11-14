# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 13:05:11 by jaguillo          #+#    #+#              #
#    Updated: 2014/11/12 14:09:32 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

H_DIR = h/
C_DIR = src/
O_DIR = o/
LIBFT = libft/

C_FILES = $(shell ls -1t $(C_DIR) | grep ".c")

O_FILES = $(addprefix $(O_DIR),$(C_FILES:.c=.o))

all: $(NAME)

$(NAME): libft $(O_FILES)
	@gcc -O2 -o $@ $(O_FILES) -I$(LIBFT) -L$(LIBFT) -lft && echo "\033[0;32m$@			\033[1;30m<<--\033[0;0m" || echo "\033[0;31m$@\033[0;0m"

libft:
	@(make -C $(LIBFT) || (echo "\033[0;31m$@\033[0;0m" && exit 1)) | grep -v "Nothing to be done" || echo "" > /dev/null

$(O_DIR)%.o: $(C_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@gcc -Wall -Wextra -Werror -O2 -I$(H_DIR) -I$(LIBFT) -L$(LIBFT) -lft -o $@ -c $< && echo "\033[0;0m$<		\033[1;30m-->>	\033[0;32m$@\033[0;0m" || (echo "\033[0;0m$<		\033[1;30m-->>	\033[0;31m$@\033[0;0m" && exit 1)

clean:
	@rm $(O_FILES) 2> /dev/null || echo "" > /dev/null
	@rmdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@make -C $(LIBFT) clean

fclean: clean
	@rm $(NAME) 2> /dev/null || echo "" > /dev/null
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all libft clean fclean re

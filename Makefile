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

FLAGS = -Wall -Wextra -Werror -O2
DEBUG = 0

C_FILES = $(shell ls -1 $(C_DIR) | grep "\.c")

O_FILES = $(addprefix $(O_DIR),$(C_FILES:.c=.o))

all:
	@(if [ "$(DEBUG)" -eq "1" ]; then make -C $(LIBFT) debug; else make -C $(LIBFT); fi || (echo "\033[0;31m$(LIBFT)\033[0;0m" && exit 1)) | grep -v "Nothing to be done" || echo "" > /dev/null
	@make -j3 $(NAME)

$(NAME): $(O_FILES)
	@gcc $(FLAGS) -o $@ $(O_FILES) -I$(LIBFT) -L$(LIBFT) -lft && printf "\033[0;32m%-24s\033[1;30m<<--\033[0;0m\n" "$@" || printf "\033[0;31m%-24s\033[1;30m<<--\033[0;0m\n" "$@"

$(O_DIR)%.o: $(C_DIR)%.c
	@mkdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@printf "\033[1;30m"
	@gcc $(FLAGS) -I$(H_DIR) -I$(LIBFT) -L$(LIBFT) -lft -o $@ -c $< && printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;32m$@\033[0;0m\n" "$<" || (printf "\033[0;0m%-24s\033[1;30m-->>	\033[0;31m$@\033[0;0m\n" "$<" && exit 1)

debug: _debug all

clean:
	@rm $(O_FILES) 2> /dev/null || echo "" > /dev/null
	@rmdir $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@make -C $(LIBFT) clean

fclean: clean
	@make -C $(LIBFT) fclean
	@rm $(NAME) 2> /dev/null || echo "" > /dev/null

update: fclean
	@git subtree pull --prefix=libft --squash ../libft master -m "Update libft"

re: fclean all

rebug: fclean debug

_debug:
	$(eval FLAGS = -Wall -Wextra -g)
	$(eval DEBUG = 1)

.PHONY: all debug clean fclean update re rebug _debug

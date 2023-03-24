# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucas-ma <jferreir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 15:07:52 by jferreir          #+#    #+#              #
#    Updated: 2023/01/31 09:59:11 by jferreir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################ PROGRAM ################

NAME	    =    so_long

################ TERMINAL ###############

RMV        =        rm -f
MKD        =        mkdir
PRT        =        printf
MKE        =        make
CPY        =        cp

################# COLORS ################

--GRN    =        \033[32m
--RED    =        \033[31m
--WHT    =        \033[39m

################# DIRS ##################

_SRC    =        src/
_OBJ 	=		 obj/
_LIB    =        libs/
_MLX    =        ./mlx/
_BIN    =        ./

############### COMPILER ################

CC      =        cc
CFLAGS      =        -Wall -Werror -Wextra -g -fsanitize=address
#valgrind --leak-check=full --show-leak-kinds=all ./so_long
SRCS    =		$(_SRC)so_long_main.c \
				$(_SRC)check_map.c
OBJS    =        $(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS))
DEPS    =        ./libs/libft.a ./mlx/libmlx.a
LIBS    =        -lft

################ RULES ##################

all: deps $(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(MKD) -p $(@D)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(DEPS) $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) -L $(_LIB) $(LIBS)

################ DEPS ###################

./libs/libft.a:
	$(MKE) -C libft/

./mlx/libmlx.a:
	$(MKE) -C mlx/

############## STRUCTURE ################

$(_BIN):
	$(MKD) $(_BIN)libs/libft.a

clean:
	$(RMV) -r $(_OBJ)

fclean: clean
	$(RMV) -r $(NAME)
	$(RMV) -r $(_LIB)libft.a
	$(RMV) -r $(_MLX)libmlx.a

re: fclean all

rebonus: fclean bonus

.PHONY: all deps clean fclean re

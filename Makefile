# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/30 09:59:24 by fbarrett          #+#    #+#              #
#    Updated: 2024/03/07 14:24:00 by fbarrett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d

O_DIRECT	=	./bin/

SRC_DIRECT	=	src/

MY_LIBRARY	=	./libft/

MLX_LIBRARY	=	./MLX42/

MY_FILES	=	main.c check_map.c render_minimap.c error_msg.c check_textures.c render.c render2.c cube_utils.c parsing_map.c check_FC.c key_hooks.c minimap.c

MY_SOURCES	=	$(addprefix $(SRC_DIRECT), $(MY_FILES))

BONUS_SOURCES	=

MY_OBJECTS	=	$(addprefix $(O_DIRECT), $(MY_SOURCES:src/%.c=%.o))

CC		=	gcc

LIBFLAGS	= -L$(MY_LIBRARY) -lft -I.

#MLX flags en_dehors de 42
#MLXLIBFLAGS	=	-L./MLX42/build/ -lmlx42 -lglfw -L"$(HOMEBREW_PREFIX)/opt/glfw/lib" -I. -framework Cocoa -framework OpenGL -framework IOKit

MLXLIBFLAGS	=	-L./MLX42/build/ -lmlx42 -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib" -I. -framework Cocoa -framework OpenGL -framework IOKit

CCFLAGS		=	-Wall -Wextra -Werror

DEBUG_FLAGS	=	-g -fsanitize=address

all:		$(NAME)

$(NAME):	$(MLX_LIBRARY) $(O_DIRECT) $(MY_OBJECTS) $(MY_LIBRARY)
	@make -C $(MY_LIBRARY)
	@cmake -S ./MLX42 -B ./MLX42/build
	@make -C ./MLX42/build -j4
	$(CC) $(CCFLAGS) -o $(NAME) $(MY_OBJECTS) $(LIBFLAGS) $(MLXLIBFLAGS)

debug:		$(MLX_LIBRARY) $(O_DIRECT) $(MY_OBJECTS) $(MY_LIBRARY)
	@make -C $(MY_LIBRARY)
	@cmake -S ./MLX42 -B ./MLX42/build
	@make -C ./MLX42/build -j4
	$(CC) $(CCFLAGS) $(DEBUG_FLAGS) -o $(NAME) $(MY_OBJECTS) $(LIBFLAGS) $(MLXLIBFLAGS)

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f $(O_DIRECT)*.o
	
fclean:		clean
	rm -f $(NAME)
	rm -rf $(O_DIRECT)
	rm -rf $(MLX_LIBRARY)

$(MLX_LIBRARY):
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_LIBRARY)

$(O_DIRECT)%.o:	src/%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

$(O_DIRECT):
	mkdir -p -m 777 $(O_DIRECT)

re:		fclean $(NAME)

.PHONY:	all clean fclean re test debug

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/30 09:59:24 by fbarrett          #+#    #+#              #
#    Updated: 2024/02/29 11:14:31 by fbarrett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

MY_SOURCES	=	get_next_line.c ft_isdigit.c ft_putendl_fd.c ft_strlen.c ft_isprint.c \
	ft_putstr_fd.c ft_strmapi.c ft_itoa.c ft_split.c ft_strncmp.c ft_atoi.c ft_memchr.c\
	ft_strchr.c ft_strnstr.c ft_bzero.c ft_memcmp.c ft_strdup.c ft_strrchr.c\
	ft_putnbr_fd.c ft_calloc.c ft_memcpy.c ft_striteri.c ft_strtrim.c ft_isalnum.c\
	ft_memmove.c ft_isalpha.c ft_memset.c ft_strjoin.c\
	ft_substr.c ft_isascii.c ft_putchar_fd.c ft_strlcat.c ft_tolower.c ft_toupper.c \
	ft_strlcpy.c ft_putnbrbase_fd.c base_type_check.c array_int_func.c ft_lstnew.c \
	ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

MY_OBJECTS	=	$(MY_SOURCES:%.c=%.o)

CC	=	gcc

LIBFLAGS = -L. -lft -I.

CCFLAGS	=	-Wall -Wextra -Werror -g

all:	$(NAME)

$(NAME): $(MY_OBJECTS)
	ar rcs libft.a $(MY_OBJECTS)

test:	$(NAME) libft.h
	$(CC) $(CCFLAGS) $(LIBFLAGS) main.c -o test

%.o:%.c libft.h
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean:	clean
	rm -f $(NAME) test a.out

re:	fclean $(NAME)

.PHONY:	clean all fclean re test

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 23:07:08 by zouddach          #+#    #+#              #
#    Updated: 2024/08/08 19:37:56 by zouddach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRC = ft_isdigit.c	ft_memset.c	ft_strlcpy.c ft_substr.c \
		ft_atoi.c ft_isprint.c ft_split.c ft_strlen.c ft_tolower.c \
		ft_bzero.c ft_itoa.c ft_strchr.c ft_strmapi.c ft_toupper.c \
		ft_calloc.c ft_memchr.c ft_strdup.c ft_strncmp.c ft_strtrim.c \
		ft_isalnum.c ft_memcmp.c ft_striteri.c ft_strnstr.c ft_putchar_fd.c \
		ft_isalpha.c ft_memcpy.c ft_strjoin.c ft_strrchr.c ft_putendl_fd.c \
		ft_isascii.c ft_memmove.c ft_strlcat.c ft_putstr_fd.c ft_putnbr_fd.c \

BSRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c \

OBG = $(SRC:.c=.o)
BOBG = $(BSRC:.c=.o)
RM = /bin/rm -f

GREEN = \033[0;32m
RED = \033[0;31m
DEFAULT = \033[0m
BLUE = \033[0;34m
BOLD = \033[1m

all: $(NAME)

%.o: %.c libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBG)
	@ar rcs $(NAME) $(OBG)
	@ranlib $(NAME)

clean:
	@$(RM) $(OBG) $(BOBG)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
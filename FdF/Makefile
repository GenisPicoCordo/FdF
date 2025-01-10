# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/20 13:26:08 by gpico-co          #+#    #+#              #
#    Updated: 2025/01/10 10:30:00 by gpico-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := fdf
CC := cc
CFLAGS := -Wall -Werror -Wextra -Wunreachable-code -Ofast
RM := rm -f

# Directorios de librerías y includes
LIBFTDIR := libft
LIBFT := $(LIBFTDIR)/libft.a
PRINTFDIR := libft/ft_printf
PRINTF := $(PRINTFDIR)/libftprintf.a
MLX42DIR := MLX42
MLX42BUILD := $(MLX42DIR)/build
INCLUDES := -I includes -I $(MLX42DIR)/include -I $(LIBFTDIR) -I $(PRINTFDIR)

SRC := src/main.c \
			src/draw_utils.c \
			src/projection.c \
			src/map_utils.c \
			src/utils.c \
			src/draw.c


OBJS := $(SRC:.c=.o)

LIBS := $(MLX42BUILD)/libmlx42.a $(LIBFT) $(PRINTF) -ldl -lglfw -pthread -lm

# Variables para simplificar compilación
MAKE_LIBFT := $(MAKE) -C $(LIBFTDIR)
MAKE_PRINTF := $(MAKE) -C $(PRINTFDIR)

all: makelibft makeprintf libmlx $(NAME)

makelibft:
	$(MAKE_LIBFT)

makeprintf:
	$(MAKE_PRINTF)

libmlx:
	@cmake $(MLX42DIR) -B $(MLX42BUILD) && make -C $(MLX42BUILD) -j4
	@echo "MLX42 compilado."	

%.o: %.c Makefile includes/fdf.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compilando: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "Enlazado final: $(NAME) creado."

clean:
	$(RM) -f $(OBJS)
	$(RM) -r $(MLX42BUILD)
	@$(MAKE_LIBFT) clean
	@$(MAKE_PRINTF) clean
	@echo "Objetos y compilados intermedios eliminados."

fclean: clean
	$(RM) $(NAME)
	@$(MAKE_LIBFT) fclean
	@$(MAKE_PRINTF) fclean
	@echo "Ejecutables eliminados."

re: fclean all
	
.PHONY: all clean fclean re libmlx libft


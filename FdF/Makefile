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
CFLAGS := -Wall -Werror -Wextra -Wunreachable-code -Ofast -g 
RM := rm -f

LIBFTDIR := libft
LIBFT := $(LIBFTDIR)/libft.a
PRINTFDIR := libft/ft_printf
PRINTF := $(PRINTFDIR)/libftprintf.a
MLX42DIR := MLX42
MLX42BUILD := $(MLX42DIR)/build
INCLUDES := -I includes -I $(MLX42DIR)/include -I $(LIBFTDIR) -I $(PRINTFDIR)

SRC := src/main.c \
			src/main_utils.c \
			src/render.c \
			src/grid.c \
			src/grid_utils1.c \
			src/grid_utils2.c \
			src/input_reader.c \
			src/input_reader1.c \
			src/graphics.c \
			src/hooks.c \
			src/error_handling.c \
			src/colours.c \
			src/draw_utils.c 
			
OBJS := $(SRC:.c=.o)

LIBS := $(MLX42BUILD)/libmlx42.a $(LIBFT) $(PRINTF) -ldl -lglfw -pthread -lm

all: makelibft makeprintf libmlx $(NAME)

makelibft:
	make -C $(LIBFTDIR)

makeprintf:
	make -C $(PRINTFDIR)

libmlx:
	@cmake -DDEBUG=1 $(MLX42DIR) -B $(MLX42BUILD) && make -C $(MLX42BUILD) -j4
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
	make clean -C $(LIBFTDIR)
	make clean -C $(PRINTFDIR)
	@echo "Objetos y compilados intermedios eliminados."

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)
	make fclean -C $(PRINTFDIR)
	@echo "Ejecutables eliminados."

re: fclean all
	
.PHONY: all clean fclean re libmlx libft

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: r <r@student.42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 11:52:50 by lsohler           #+#    #+#              #
#    Updated: 2023/06/18 17:09:13 by r                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# PROJET #
NAME = shallow

# HEADER #
INCLUDES = includes/
HEADER_SRCS = shallow.h
HEADER = $(addprefix $(INCLUDES), $(HEADER_SRCS))

# SOURCES #
SRCS = main.c mlx.c key.c circle.c ft_itoa.c
# GNL_FUNC = 
# GNL_DIR = gnl/
# GNL_SRCS = $(addprefix $(GNL_DIR), $(GNL_FUNC))
# GNL_OBJS = $(GNL_SRCS:.c=.o)
# LIBFT_DIR = libft/
# LIBFT_FUNC = 
# LIBFT_SRCS = $(addprefix $(LIBFT_DIR), $(LIBFT_FUNC))
OBJS = $(SRCS:.c=.o)
# LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

# MLX #

MLX_DIR = minilibx_macos/
#MLX = -I minilibx_macos -g -L minilibx_macos -l mlx -framework OpenGL -framework AppKit
MLX =  -L$(MLX_DIR) -l mlx -framework OpenGl -framework AppKit

# UTILS #
CC = gcc
# CFLAGS = -Wall -Werror -Wextra
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3 -g
RM = rm -rf

# COLORS #
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m

# COMMANDS #
%.o: %.c
				@$(CC) $(FLAGS) -I $(INCLUDES) -I $(MLX_DIR) -c $< -o $@


$(NAME): $(OBJS) $(LIBFT_OBJS) $(GNL_OBJS)
				@$(CC) $(FLAGS) -I $(INCLUDES) $(MLX) $(OBJS)  -o $(NAME)
				@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"


all: $(NAME)

clean:
				@$(RM) $(OBJS)
				@$(RM) $(LIBFT_OBJS)
				@$(RM) $(GNL_OBJS)
				@echo "$(YELLOW)object files cleaned!$(DEFAULT)"

fclean: clean
				@$(RM) $(NAME)
				@echo "$(RED)$(NAME) cleaned!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re
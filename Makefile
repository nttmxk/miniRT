CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

NAME = miniRT
SRCS =	main.c \
		trace/ft_sphere.c \
		trace/ft_plane.c \
		trace/ft_cylinder.c \
		trace/phong_lighting.c \
		utils/op_vector.c \
		utils/op_vector2.c \
		utils/op_vector3.c \
		utils/ft_constructor.c \
		utils/init.c \
		utils/utils.c \
		get_next_line/get_next_line.c \
        get_next_line/get_next_line_utils.c \
		parser/ft_atoi.c \
		parser/ft_split.c \
		parser/parse_objs.c \
		parser/parse_scenes.c \
		parser/parser.c \
		parser/putters.c \
		parser/reallocs.c \
		parser/validator1.c \
		parser/validator2.c

OBJS = $(SRCS:%.c=%.o)

INCLUDES = -I./includes

%.o: %.c
		$(CC) $(CFLAGS) $(FLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(MLXFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: fclean all clean re

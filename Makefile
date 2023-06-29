#SETUP
NAME		=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
FSAN		=	-fsanitize=address -g
RM			=	rm -rf

#FILES, DIRECTORIES AND PATHS
HEADER_F	=	minishell.h
HEADER_DIR	=	headers/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_F))
FUNCS_F		=	ft_calloc.c ft_split.c ft_strarr_cpy.c \
				ft_strarr_free.c ft_strdup.c ft_strjoin.c \
				ft_strlen.c ft_strncmp.c get_next_line.c \
				ft_strchr.c ft_atoi.c ft_itoa.c ft_isalnum.c \
				ft_itoa_2.c
FUNCS_DIR	=	functions/
FUNCS		=	$(addprefix $(FUNCS_DIR), $(FUNCS_F))
SOURCE_F	=	main.c parsing.c minishell_split_utils.c \
				minishell_split.c command_handling.c \
				pipes.c parsing_utils.c utils.c \
				redirect.c command_handling_utils.c \
				signals.c builtins_2.c builtins.c \
				builtins_utils.c utils_2.c parsing_utils_2.c \
				builtins_utils_2.c redirect_2.c \
				command_handling_utils_2.c \
				builtins_utils_3.c
SOURCE_DIR	=	sources/
SOURCE		=	$(addprefix $(SOURCE_DIR), $(SOURCE_F))

#OBJECTS
OBJS_S		=	$(SOURCE:.c=.o)
OBJS_F		=	$(FUNCS:.c=.o)

#COMMANDS
%.o: %.c
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJS_S) $(OBJS_F)
				@$(CC) $(FLAGS) $(FSAN) $(OBJS_S) $(OBJS_F) -lreadline -o $(NAME)
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

all:			$(NAME)

clean:
				@$(RM) $(OBJS_S) $(OBJS_F)
				@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(RED)object files and executable deleted!$(DEFAULT)"

re:				fclean all

.PHONY:		all clean fclean re

#COLORS
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
DEFAULT	=	\033[0m
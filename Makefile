NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a

INCLUDE = ./include/minishell.h

BUILTINS = cd echo env exit export pwd unset cd_utils export_utils

ENV = env get_env sort_env shlvl env_tools

EXEC = bin builtin exec heredoc

MAIN = minishell redir signal

PARSING = parser tokens expander lexer

TOOLS = fd free token type expander parsing heredoc_utils

SRC = $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	  $(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make bonus -C libft/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -L$(shell brew --prefix readline)/lib -lreadline
	@echo "\n\033[0;42mDone !"

%.o:%.c $(INCLUDE)
	@printf "\x1b[35mGenerating minishell objects... %-10.10s\r" $@
	@$(CC) $(CFLAGS) -c -I$(shell brew --prefix readline)/include $< -o $@

clean:
	@echo "\x1b[41m\nObjects has been deleted\033[0;37m"
	@make clean -C libft/
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft/
	@rm -rf $(OBJ)
	@rm -rf $(NAME)

re: fclean all

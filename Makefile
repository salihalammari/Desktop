NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -I header/ -I libft/

LDFLAGS="-L/goinfre/sghajdao/homebrew/opt/readline/lib"

CPPFLAGS="-I/goinfre/sghajdao/homebrew/opt/readline/include"

LIBFT = libft/libft.a

HEADER = minishell.h

BUILTINS = cd echo env exit export pwd unset

ENV = env get_env sort_env shlvl env_tools

EXEC = bin builtin exec

MAIN = minishell redir signal

PARSING = parser tokens expander lexer

TOOLS = fd free token type expander parsing

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
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LIBFT) $(LDFLAGS) -lreadline
	@echo "\n\033[0mDone !"

%.o: %.c HEADER
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\033[0;31m\nDeleting objects..."
	@make clean -C libft/
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft/
	@rm -rf $(OBJ)
	@rm -rf $(NAME)

re: fclean all

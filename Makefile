NAME	=	minishell
CC		=	cc
CFLAGS	=	-Werror -Wextra -Wall
LIBFT	=	libft/libft.a
LDFLAGS= -L/goinfre/slammari/homebrew/opt/readline/lib
CPPFLAGS= -I/goinfre/slammari/homebrew/opt/readline/include

SRCS	=	sources/parsing/builtins/builtins.c sources/parsing/syntax/check_quotes.c sources/parsing/spliter/find_env.c \
	sources/parsing/builtins/ft_cd.c sources/parsing/builtins/ft_echo.c sources/parsing/builtins/ft_env.c \
	sources/parsing/builtins/ft_exit.c sources/parsing/builtins/ft_export_utils.c sources/parsing/builtins/ft_export.c \
	sources/parsing/builtins/ft_pwd.c sources/parsing/builtins/ft_unset.c sources/parsing/spliter/init_path.c \
	sources/main.c sources/execution/redirection/redir_in.c sources/execution/redirection/redir_out.c \
	sources/execution/runing/run_pipe_aux.c sources/execution/runing/run_pipe.c sources/signal.c \
	sources/parsing/spliter/split_cmd.c sources/parsing/syntax/token_utils.c sources/parsing/syntax/token.c \
	sources/parsing/syntax/take_off_quotes.c sources/parsing/expander/expander.c sources/parsing/syntax/malloc_check.c \
	sources/parsing/builtins/ft_cd_utils.c sources/parsing/builtins/ft_echo_utils.c sources/parsing/builtins/ft_env_utils.c \
	sources/parsing/builtins/ft_exit_utils.c sources/parsing/builtins/ft_export_utils2.c \
	sources/parsing/builtins/ft_export_utils3.c sources/execution/redirection/redir_in_utils.c \
	sources/execution/runing/run_pipe_utils.c sources/execution/runing/run_pipe_utils2.c \
	sources/parsing/syntax/token_utils2.c sources/parsing/syntax/token_utils3.c \
	sources/parsing/spliter/split_cmd_utils.c sources/parsing/spliter/split_cmd_utils2.c \
	sources/prompt.c sources/parsing/syntax/check_syntax.c sources/parsing/expander/expander_utils.c \
	sources/parsing/builtins/ft_export_utils4.c sources/parsing/spliter/utils_fun.c

OBJS	=	$(SRCS:.c=.o)

$(NAME): $(OBJS)
	@echo "\033[0;32m\n\nCompiling minishell..."
	@$(MAKE) -s bonus -C ./libft
	@$(CC) $(CFLAGS) $(LIBFT) $(LDFLAGS) -lreadline $^ -o $(NAME)
	@$(MAKE) -s clean -C ./libft
	@printf "\n\033[0;32m ───────────── Done ──────────── \033[0m\n\n"

%.o: %.c minishell.h
	@printf "\033[0;33mGenerating minishell objects... %-10.10s\r" $@
	@$(CC) $(CFLAGS) -c $(CPPFLAGS) $< -o $@
	@printf "\033[1;36m Compiling \033[0m $< \033[1;36m√\033[0m\n"

all: $(NAME)

clean:
	@$(MAKE) -s clean -C ./libft
	@rm -rf $(OBJS)

fclean: clean
	@$(MAKE) -s fclean -C ./libft
	@rm -rf $(NAME)

re: fclean all

NAME	=	minishell
CC		=	cc
CFLAGS	=	-Werror -Wextra -Wall
LIBFT	=	libft/libft.a
LDFLAGS = -L/goinfre/slammari/homebrew/opt/readline/lib
CPPFLAGS = -I/goinfre/slammari/homebrew/opt/readline/include

SRCS	=	sources/builtins.c sources/check_quotes.c sources/find_env.c \
	sources/ft_cd.c sources/ft_echo.c sources/ft_env.c \
	sources/ft_exit.c sources/ft_export_utils.c sources/ft_export.c \
	sources/ft_pwd.c sources/ft_unset.c sources/init_path.c \
	sources/main.c sources/redir_in.c sources/redir_out.c \
	sources/run_pipe_aux.c sources/run_pipe.c sources/signal.c \
	sources/split_cmd.c sources/token_utils.c sources/token.c \
	sources/take_off_quotes.c sources/expander.c sources/malloc_check.c \
	sources/ft_cd_utils.c sources/ft_echo_utils.c sources/ft_env_utils.c \
	sources/ft_exit_utils.c sources/ft_export_utils2.c \
	sources/ft_export_utils3.c sources/redir_in_utils.c \
	sources/run_pipe_utils.c sources/run_pipe_utils2.c \
	sources/token_utils2.c sources/token_utils3.c \
	sources/split_cmd_utils.c sources/split_cmd_utils2.c \
	sources/prompt.c sources/check_syntax.c sources/expander_utils.c
	sources/utils_fun.c

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

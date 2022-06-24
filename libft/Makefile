NAME := libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

SRC := ft_strjoin.c \
	ft_atoi.c ft_memchr.c ft_strlcat.c \
	ft_bzero.c ft_memcmp.c ft_strlcpy.c \
	ft_calloc.c ft_memcpy.c ft_strlen.c \
	ft_isalnum.c ft_memmove.c ft_strmapi.c \
	ft_isalpha.c ft_memset.c ft_strncmp.c \
	ft_isascii.c ft_putchar_fd.c ft_strnstr.c \
	ft_isdigit.c ft_putendl_fd.c ft_strrchr.c \
	ft_isprint.c ft_putnbr_fd.c ft_strtrim.c \
	ft_itoa.c ft_putstr_fd.c ft_substr.c \
	ft_split.c ft_tolower.c \
	ft_strchr.c ft_toupper.c \
	ft_strdup.c \
	ft_striteri.c

SRCB := $(SRC) ft_lstnew.c ft_lstadd_front.c\
	ft_lstsize.c ft_lstlast.c\
	ft_lstadd_back.c ft_lstdelone.c \
	ft_lstclear.c ft_lstiter.c

OBJECTS := $(SRC:.c=.o)

OBJECTSB := $(SRCB:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "\033[0;32m\n\nCompiling libft..."
	@$(AR) ${NAME} $?

bonus: $(OBJECTSB)
	@$(AR) $(NAME) $?

%.o: %.c libft.h
	@printf "\033[0;33mGenerating libft objects... %-10.10s\r" $@
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTSB) $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

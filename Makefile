# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 14:13:11 by nfoughal          #+#    #+#              #
#    Updated: 2023/04/03 17:49:58 by nfoughal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = CC
CFLAGS = -Wall -Wextra -Werror

SRC  =  main.c parsing.c utils.c minishell.c env_variable.c mshell_support.c parsing_support.c \
		main_parsing.c utils1.c utils2.c free.c free2.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

${NAME} : ${OBJ}
	${MAKE} -C ./libft bonus
	${CC} ${CFLAGS} ${OBJ} -lreadline ./libft/libft.a -o ${NAME}

%.o:%.c minishell.h
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	@rm -f $(OBJ)
	${MAKE} clean -C ./libft

fclean: clean
	@rm -f $(NAME)
	${MAKE} fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
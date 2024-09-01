# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 14:13:11 by nfoughal          #+#    #+#              #
#    Updated: 2023/04/16 22:18:44 by moouaamm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = CC
CFLAGS = -Wall -Wextra -Werror -I/Users/moouaamm/.brew/opt/readline/include

SRC  =  main.c parsing.c utils.c minishell.c env_variable.c mshell_support.c parsing_support.c \
		main_parsing.c utils1.c utils2.c utils3.c free.c free2.c mshell_supp2.c replace_env.c error_check.c \
		cmds.c execution.c in_out.c sig_handle.c cmds2.c cmds3.c cmds4.c cmds5.c execution2.c execution3.c \
		utils4.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

${NAME} : ${OBJ}
	${MAKE} -C ./libft bonus
	${CC} ${CFLAGS} ${OBJ} -lreadline -L/Users/moouaamm/.brew/opt/readline/lib ./libft/libft.a -o ${NAME}

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
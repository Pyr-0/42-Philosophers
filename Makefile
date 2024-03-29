# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 16:08:58 by mrojas-e          #+#    #+#              #
#    Updated: 2022/03/08 19:33:43 by mrojas-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo
CC			=	gcc
CC_FLAGS	=	-Wall -Werror -Wextra -pthread -g
RM			=	rm -rf
DIR_HEADERS =	./includes/
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./obj/
SRC			=	sophos_main.c utilitas.c initium.c veritas.c ft_atoi.c fork_mechanics.c
SRCS		=	$(SRC)
OBJS 		=	$(SRCS:%.c=$(DIR_OBJS)%.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				@tput setaf 05 && printf "Sources Succesfully Compiled!\n"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) $(OBJS) -o $(NAME)
				@tput setaf 013 && printf "$(NAME) created.\n"

$(OBJS):		$(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
#				@tput setaf 207 && printf "\nCompiling sources\n$<"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@
$(DIR_OBJS):
				@mkdir $@

clean:
				@$(RM) $(DIR_OBJS)
				@tput setaf 117 && printf "\nobject files  deleted.\n"
				
fclean:			clean
				@$(RM) $(NAME)
				@tput setaf 117 && printf "FULL CLEAN COMPLETED.\n"

re:				fclean all

.PHONY:			all clean fclean re norm

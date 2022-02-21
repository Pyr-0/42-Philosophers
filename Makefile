# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 16:08:58 by mrojas-e          #+#    #+#              #
#    Updated: 2022/02/21 18:33:58 by mrojas-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo
CC			=	gcc
CC_FLAGS	=	-Wall -Wextra -Werror
RM			=	rm -rf
DIR_HEADERS =	./includes/
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./obj/
SRC			=	sophos.c utilitas.c initium.c
SRCS		=	$(SRC)
OBJS 		=	$(SRCS:%.c=$(DIR_OBJS)%.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				@tput setaf 207 && printf " object files compiled.\n"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) $(OBJS) -o $(NAME)
				@tput setaf 013 && printf "$(NAME) created.\n"

$(OBJS):		$(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				@tput setaf 207 && printf "Compiling sources $<"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@
$(DIR_OBJS):
				@mkdir $@

clean:
				@$(RM) $(DIR_OBJS)
				@tput setaf 117 && printf "object files  deleted.\n"
				
fclean:			clean
				@$(RM) $(NAME)
				@tput setaf 117 && printf "FULL CLEAN COMPLETED.\n"

re:				fclean all

.PHONY:			all clean fclean re norm

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jebitrus <jebitrus@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 23:42:12 by jebitrus          #+#    #+#              #
#    Updated: 2024/07/16 23:42:55 by jebitrus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -pthread

SRCS	= 	philo.c input_check.c \
			print_error.c struct.c \
			fixing.c mtx_actions.c \
			dining.c \
			utils.c routine.c eat_schedule.c\
			monitor.c \

RM		= rm -rf

INCLUDE	= libphilo.h

OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $^
	@echo "...Linking objs."

%.o : %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "...Compiling $(notdir $<)."

clean :
	@$(RM) $(OBJS)
	@echo "...Removing objs."

fclean : clean
	@$(RM) $(NAME)
	@echo "...Removing binary."

re : fclean all

.PHONY : all clean fclean re debug

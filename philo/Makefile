# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/03 21:32:49 by vfurmane          #+#    #+#              #
#    Updated: 2021/10/20 13:48:29 by vfurmane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
SRCS		= $(addprefix srcs/, check_args.c death_checker.c main.c philo_actions.c put.c setup.c simulation.c state_changes.c teardown.c time.c \
			  $(addprefix argparse/, argparse.c argparse_manager.c) \
			  $(addprefix utils/, ft_atoi.c ft_isdigit.c ft_is_positive_int.c ft_strlen.c))
OBJS		= $(SRCS:.c=.o)
INCL		= $(addprefix -I , includes)
CC			= clang
CFLAGS		= -Wall -Wextra -Werror
LIBS		= -pthread
RM			= rm -f

%.o:		%.c
			$(CC) $(CFLAGS) -c $< $(INCL) -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(LIBS) $^ -o $(NAME)

bonus:		all

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 12:42:57 by smagdela          #+#    #+#              #
#    Updated: 2021/12/02 16:35:53 by smagdela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
#	VARIABLES	#
#################

NAME	=	minitalk
CLIENT	=	client
SERVER	=	server

LIBSD	=	libs/
LIBFTD	=	${addprefix ${LIBSD},libft/}
LIBPRINTFD	=	${addprefix ${LIBSD},ft_printf/}
INCD	=	includes/
SRCD	=	sources/
OBJD	=	objects/
BONUSD	=	bonus/
BONUSSD	=	${BONUSD}sources/
BONUSOD	=	${BONUSD}objects/

LIBFT	:=	${addprefix ${LIBFTD},libft.a}
FTPRINTF:=	${addprefix ${LIBPRINTFD},libftprintf.a}
LIBS	:=	${LIBFT} ${FTPRINTF}
SRCS	=	server.c client.c ft_utils.c
BONUS 	=	server_bonus.c client_bonus.c ft_utils_bonus.c ft_utils_2_bonus.c
OBJS	:=	${addprefix ${OBJD},${SRCS:.c=.o}}
SRCS	:=	${addprefix ${SRCD},${SRCS}}
BONUSO	:=	${addprefix ${BONUSOD},${BONUS:.c=.o}}
BONUS	:=	${addprefix ${BONUSSD},${BONUS}}

CC	=	clang
CFLAGS	=	-Wall -Wextra -Werror
LIBSMK	=	make -C

##################
#	FANCY STUFF	 #
##################

GREEN	=	\033[0;32m
RED		=	\033[1;31m
NC		=	\033[0m

WHALE	=	"\n${GREEN}       ::: \n     ___:____     |^\/^| \n   ,'        '.    \  / \n   |  O        \___/  | \n ~^~^~^~^~^~^~^~^~^~^~^~^~\n \n Compilation Successful!	${NC}\n"
NUKE	=	"\n${RED}     _.-^^---....,,--       \n _--                  --_  \n<                        >)\n|                         | \n \._                   _./  \n    '''--. . , ; .--'''       \n          | |   |             \n       .-=||  | |=-.   \n       '-=£€%&%€£=-'   \n          | ;  :|     \n _____.,-£%&€@%£&£~,._____${NC}\n\n"

#############
#	RULES	#
#############

all:	${NAME}

${NAME}:	${LIBS} ${OBJS}
	${CC} ${CFLAGS} ${filter-out ${OBJD}${SERVER}.o,${OBJS}} ${LIBS} -o ${CLIENT}
	${CC} ${CFLAGS} ${filter-out ${OBJD}${CLIENT}.o,${OBJS}} ${LIBS} -o ${SERVER}
	@echo ${WHALE}

${OBJD}%.o:	${SRCD}%.c
	mkdir -p ${OBJD}
	${CC} ${CFLAGS} -c -o $@ -I${INCD} -I${LIBFTD} -I${LIBPRINTFD} $<

${LIBS}:
	${LIBSMK} ${LIBFTD} bonus
	${LIBSMK} ${LIBPRINTFD} bonus

bonus: ${LIBS} ${OBJS} ${BONUSO}
	${CC} ${CFLAGS} ${filter-out ${BONUSOD}${SERVER}_bonus.o,${BONUSO}} ${LIBS} -o ${CLIENT}_bonus
	${CC} ${CFLAGS} ${filter-out ${BONUSOD}${CLIENT}_bonus.o,${BONUSO}} ${LIBS} -o ${SERVER}_bonus
	@echo ${WHALE}

${BONUSOD}%.o:	${BONUSSD}%.c
	mkdir -p ${BONUSOD}
	${CC} ${CFLAGS} -c -o $@ -I${INCD} -I${LIBFTD} -I${LIBPRINTFD} $<

clean:
	-rm -rf ${OBJD} ${BONUSOD}
	${LIBSMK} ${LIBFTD} clean
	${LIBSMK} ${LIBPRINTFD} clean

fclean:	clean
	-rm ${CLIENT} ${SERVER} ${CLIENT}_bonus ${SERVER}_bonus
	${LIBSMK} ${LIBFTD} fclean
	${LIBSMK} ${LIBPRINTFD} fclean
	@echo ${NUKE}

re:		fclean all

.PHONY : re all bonus clean fclean

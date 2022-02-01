# -*-🦕-*- Make Philosophers -*-🦕-*- 

NAME	= philosphers

# -*- Definitions of variables -*-

SRCS_DIR	= srcs
SRCS		= ${addprefix ${SRCS_DIR}/,${SRCS_FIND}}
SRCS_FIND	= ${shell find . -type f \( -wholename "./srcs/*.c" -not -wholename "./ft_*bonus.c" -not -wholename "./libft/ft_*.c" \) | cut -d'/' -f3-}
SRCS_BONUS	= ${addprefix ${SRCS_DIR}/,${SRCS_BFIND}}
SRCS_BFIND	= ${shell find . -type f \( -wholename "./srcs/*.c" -not -wholename "./libft/ft_*.c" \) | cut -d'/' -f3-}

OBJS_DIR	= objs
OBJS		= ${addprefix ${OBJS_DIR}/,${SRCS_FIND:.c=.o}}
OBJS_BONUS	= ${addprefix ${OBJS_DIR}/,${SRCS_BFIND:.c=.o}}

INCLUDES	= -Iincludes

CC			= gcc
RM			= rm -f
MAKE		= make
CFLAGS 		= -Wall -Wextra -Werror -fsanitize=address -g

# Colors

GRAY		= \e[1;30m
GREEN 		= \e[1;32m
DARK_GREEN	= \e[0;32m
YELLOW		= \e[1;33m
BLUE		= \e[1;34m
PURPLE		= \e[1;35m
CYAN		= \e[1;36m
WHITE		= \e[1;37m
NORMAL		= \e[0;37m
END			= \e[0m

# -*- The Rules -*-

#	Implicit rules

# Create and compile objects files in a dedicated folder
${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c 
			@mkdir -p objs
			@${CC} ${CFLAGS} ${INCLUDES} -O3 -c $< -o $@

#	Active rules

all:		${NAME} test

# Make libft + compile pipex
${NAME}:	${OBJS}
			@printf "\n"
			@$(CC) ${CFLAGS} ${INCLUDES} ${OBJS} -o $(NAME)
			@printf "	${WHITE}[${GREEN} Success. Compiled philosophers.${WHITE}]\
			${END} \n\n"

test:		${NAME}
			@printf "\n	📚 [${PURPLE}INSTRUCTIONS${END}] 📚\n"
			@printf "\n🦕🍭	${YELLOW}To use philosophers${END}\n"
			@printf "	./philosophers ${GRAY}??${END}"
			@printf "\n\n"

bonus:		${NAME} 

#	Cleaning rules

clean:
			@${RM} ${OBJS} ${OBJS_BONUS}
			@rm -rf objs
			@printf "\n	${WHITE}[${BLUE} Cleaned philosophers object files ${WHITE}]\
			${END}\n"

fclean:		clean
			@${RM} ${NAME}
			@printf "	${WHITE}[${BLUE} Cleaned philosophers output files ${WHITE}]\
			${END}\n\n"

re:			fclean all

.PHONY:		all clean fclean re



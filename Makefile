# -*-🦕-*- Make Minishell -*-🦕-*- 

NAME	= minishell

# -*- Definitions of variables -*-

SRCS_DIR	= srcs
SRCS		= $(wildcard $(SRCS_DIR)/*.c)

OBJS_DIR	= objs
OBJS		= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

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
			@${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

#	Active rules

all:		${NAME} test

# Make libft + compile minishell
${NAME}:	${OBJS}
			@printf "\n"
			@$(CC) ${CFLAGS} ${INCLUDES} ${OBJS} -o $(NAME)
			@printf "	${WHITE}[${GREEN} Success. Compiled minishell.${WHITE}]\
			${END} \n\n"

test:		${NAME}
			@printf "\n	📚 [${PURPLE}INSTRUCTIONS${END}] 📚\n"
			@printf "\n🦕🍭	${YELLOW}To use minishell${END}\n"
			@printf "	./minishell ??"
			@printf "\n\n"

bonus:		${NAME} 

#	Cleaning rules

clean:
			@${RM} ${OBJS} ${OBJS_BONUS}
			@rm -rf objs
			@printf "\n	${WHITE}[${BLUE} Cleaned minishell object files ${WHITE}]\
			${END}\n"

fclean:		clean
			@${RM} ${NAME}
			@printf "	${WHITE}[${BLUE} Cleaned minishell output files ${WHITE}]\
			${END}\n\n"

re:			fclean all

.PHONY:		all clean fclean re


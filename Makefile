# -*-🥥-*- Make Minishell -*-🥥-*- 
#							by the Cocoshells 🥥

NAME	= minishell

# -*- Definitions of variables -*-

SRCS_DIR		= srcs
SRCS			:= $(shell find $(SRCS_DIR) -name *.c)

OBJS_DIR		= objs
OBJS			:= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

OBJS_SUB_DIR	:= $(shell find $(SRCS_DIR) -mindepth 1 -type d)
OBJS_SUB_DIR	:= $(OBJS_SUB_DIR:$(SRCS_DIR)/%=$(OBJS_DIR)/%)

LIBFT_DIR		= 42_00_libft

INCLUDES		= -Iincludes
LIBRARIES		= -L${LIBFT_DIR} -lft -lreadline

CC				= gcc
RM				= rm -f
MAKE			= make
CFLAGS 			= -Wall -Wextra -Werror

# Colors

GRAY			= \e[1;30m
GREEN 			= \e[1;32m
DARK_GREEN		= \e[0;32m
YELLOW			= \e[1;33m
BLUE			= \e[1;34m
PURPLE			= \e[1;35m
CYAN			= \e[1;36m
WHITE			= \e[1;37m
NORMAL			= \e[0;37m
END				= \e[0m

# -*- The Rules -*-

#	Implicit rules

# Create and compile objects files in a dedicated folder
$(OBJS_DIR)/%.o: ${SRCS_DIR}/%.c
			@mkdir -p ${OBJS_DIR}
			@mkdir -p $(OBJS_SUB_DIR)
			@${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

#	Active rules

all:			${NAME} instructions

# Make libft + compile minishell
${NAME}:		${OBJS}
			@printf "\n"
			@${MAKE} bonus -C ${LIBFT_DIR}
			@$(CC) ${CFLAGS} ${INCLUDES} ${LIBRARIES} ${OBJS} -o $(NAME)
			@printf "	${WHITE}[${GREEN} Success. Compiled minishell.${WHITE}]\
			${END} \n\n"

instructions:	${NAME}
			@printf "\n	📚 [${PURPLE}INSTRUCTIONS${END}] 📚\n"
			@printf "\n🥥🌴	${YELLOW}To use minishell${END}\n"
			@printf "	./minishell or ./minishell <file>"
			@printf "\n\n"

test:			${NAME}
			@bash tester/cocoshell_tester.sh		

bonus:			${NAME} 

#	Cleaning rules

clean:
			@${MAKE} clean -C ${LIBFT_DIR}
			@${RM} ${OBJS} ${OBJS_BONUS}
			@rm -rf objs
			@printf "\n	${WHITE}[${BLUE} Cleaned minishell object files ${WHITE}]\
			${END}\n"

fclean:			clean
			@${MAKE} fclean_no_clean -C ${LIBFT_DIR}
			@${RM} ${NAME}
			@printf "	${WHITE}[${BLUE} Cleaned minishell output files ${WHITE}]\
			${END}\n\n"

re:				fclean all

debug:			INCLUDES += -DDEBUG_MODE
debug:			CFLAGS = -Wall -Wextra -g -fsanitize=address
debug:			clean
debug:			all

.PHONY:			all clean fclean re debug


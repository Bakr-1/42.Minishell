# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalseri <aalseri@student.42Abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 21:10:12 by aalseri           #+#    #+#              #
#    Updated: 2023/02/21 13:37:29 by aalseri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

DIR_SRCS	= srcs
DIR_OBJS	= objs
SUBDIRS		= main parsing/parse parsing/token execution/exec execution/builtin execution/here_doc utils/signals utils/utils_more utils/err

SRCS_MAIN	= minishell

SRCS_PARSE	=  parse  parse_args  parse_pipes_1 parse_pipes_2

SRCS_TOKEN	= token token_string token_utils

SRCS_EXEC	= execution single_cmd single_cmd_red exec_pipe_red \
				multi_pipes utils_exec_1 \
				utils_pipe_red_1 utils_pipes_1 \
				utils_pipes_3 utils_single_cmd_1

SRCS_HD		= here_doc here_doc_utils

SRCS_SIG	= sig

SRCS_BIN	= builtin_cd exec_builtin builtin_echo \
				builtin_export builtin_exit builtin_unset utils_exit \
				utils_export_1 utils_export_2
				

SRCS_UTILS	= utils_1 utils_2 utils_3 utils_4

SRCS_ERR	= err err_1 err_2


SRCS = $(addsuffix .c, $(addprefix srcs/main/, $(SRCS_MAIN))) \
	$(addsuffix .c, $(addprefix srcs/parsing/parse/, $(SRCS_PARSE))) \
	$(addsuffix .c, $(addprefix srcs/parsing/token/, $(SRCS_TOKEN))) \
	$(addsuffix .c, $(addprefix srcs/execution/exec/, $(SRCS_EXEC))) \
	$(addsuffix .c, $(addprefix srcs/execution/builtin/, $(SRCS_BIN))) \
	$(addsuffix .c, $(addprefix srcs/execution/here_doc/, $(SRCS_HD))) \
	$(addsuffix .c, $(addprefix srcs/utils/signals/, $(SRCS_SIG))) \
	$(addsuffix .c, $(addprefix srcs/utils/utils_more/, $(SRCS_UTILS))) \
	$(addsuffix .c, $(addprefix srcs/utils/err/, $(SRCS_ERR)))

SRCS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_SRCS)/, $(dir)))
OBJS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_OBJS)/, $(dir)))
OBJS		= $(subst $(DIR_SRCS), $(DIR_OBJS), $(SRCS:.c=.o))

INCLUDES = -I ./includes
LIBFT = libft/libft.a
ECHO =	echo

CC = gcc

ifeq ($(shell uname -p), i386)
	RL_MAC		= -L /usr/local/Cellar/readline/8.1/lib -I /usr/local/Cellar/readline/8.1/include
	RL_INC_MAC = -I /usr/local/Cellar/readline/8.1/include
else
	RL_MAC		= -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
	RL_INC_MAC = -I /opt/homebrew/opt/readline/include
endif
CFLAGS =  -Wall -Wextra -Werror -g

E0M			=	 "\e[0m"

$(DIR_OBJS)/%.o :	$(DIR_SRCS)/%.c
			@printf "${BIPurple}🏗️ Generating minishell objects... %-33.33s\r"$(E0M) $@
			@mkdir -p $(DIR_OBJS) $(OBJS_DIRS)
			@$(CC) $(CFLAGS) $(RL_INC_MAC) $(INCLUDES) -c $< -o $@

sanitize = #-fsanitize=address

all: ${NAME}

${NAME} : ${LIBFT} ${OBJS}
	@${CC} ${CFLAGS} ${sanitize} ${OBJS} ${INCLUDES} ${LIBFT} -o ${NAME} $(RL_MAC) -lreadline
	@printf "${BIGreen}Run ./minishell${Color_Off}\n"

# slow-load: shrek.txt
# 	@echo "${Green}"
# 	@awk '{print; fflush(); system("sleep 0.1")}' $<
${LIBFT}:
	@${MAKE} --no-print-directory -C libft

clean:
	@${MAKE} --no-print-directory -i clean -C libft
	@echo "${BIRed}Minishell Cleaned!${Color_Off}"
	@rm -rf ${DIR_OBJS}

fclean: clean
	@${MAKE} --no-print-directory -i fclean -C libft
	@rm -rf ${NAME}

re: fclean all

r:
	@${MAKE} re --no-print-directory -i
	@./${NAME}

.PHONY: all clean fclean re

git:
	git add -A
	git commit
	git push

test:
	@$(ECHO) "▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"
	@$(ECHO) "▒▒▄▄▄▒▒▒█▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▄▄▄▒▒▒█▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▄▄▄▒▒▒█▒▒▒▒▄▒▒▒▒▒▒▒▒"
	@$(ECHO) "▒█▀█▀█▒█▀█▒▒█▀█▒▄███▄▒▒█▀█▀█▒█▀█▒▒█▀█▒▄███▄▒▒█▀█▀█▒█▀█▒▒█▀█▒▄███▄▒"
	@$(ECHO) "░█▀█▀█░█▀██░█▀█░█▄█▄█░░█▀█▀█░█▀██░█▀█░█▄█▄█░░█▀█▀█░█▀██░█▀█░█▄█▄█░"
	@$(ECHO) "░█▀█▀█░█▀████▀█░█▄█▄█░░█▀█▀█░█▀████▀█░█▄█▄█░░█▀█▀█░█▀████▀█░█▄█▄█░"
	@$(ECHO) "████████▀█████████████████████▀█████████████████████▀█████████████"

test2:
	@printf "$(IRed)"
	@printf "\n%b"
	@$(ECHO) '  *         )       )             )   (         )         (      (     '
	@$(ECHO) '(  `     ( /(    ( /(          ( /(   )\ )   ( /(         )\ )   )\ )  '
	@$(ECHO) ')\))(    )\())   )\())  (      )\()) (()/(   )\())  (    (()/(  (()/(  '
	@$(ECHO) '((_)()\  ((_)\   ((_)\   )\    ((_)\   /(_)) ((_)\   )\    /(_))  /(_)) '
	@$(ECHO) '(_()((_)   ((_)   _((_) ((_)  __ ((_) (_))    _((_) ((_)  (_))   (_))   '
	@$(ECHO) '|  \/  |  / _ \  | \| | | __| \ \ / / / __|  | || | | __| | |    | |    '
	@$(ECHO) '| |\/| | | (_) | | .` | | _|   \ V /  \__ \  | __ | | _|  | |__  | |__  '
	@$(ECHO) '|_|  |_|  \___/  |_|\_| |___|   |_|   |___/  |_||_| |___| |____| |____| '


# **************************************************************************** #
# 									VALGRIND								   #
le: ${NAME}
	make re && ./leak.sh
l: ${NAME}
	make && ./leak.sh

leaks_fd:
	make re && make clean && valgrind --track-fds=yes  ./minishell
# --suppressions=supress_readline \
# --log-file=valgrind-out.txt 
leaks:
	make re && make clean \
	&& valgrind --leak-check=full \
	--track-origins=yes \
	--show-leak-kinds=all --suppressions=.ignore_readline.txt --log-file=valgrind-out.txt \
	./minishell
# **************************************************************************** #





# Reset
Color_Off=\033[0m       # Text Reset

# Regular Colors
Black=\033[0;30m        # Black
Red=\033[0;31m         # Red
Green=\033[0;32m        # Green
Yellow=\033[0;33m       # Yellow
Blue=\033[0;34m         # Blue
Purple=\033[0;35m       # Purple
Cyan=\033[0;36m         # Cyan
White=\033[0;37m        # White

# Bold
BBlack=\033[1;30m       # Black
BRed=\033[1;31m         # Red
BGreen=\033[1;32m       # Green
BYellow=\033[1;33m      # Yellow
BBlue=\033[1;34m        # Blue
BPurple=\033[1;35m      # Purple
BCyan=\033[1;36m        # Cyan
BWhite=\033[1;37m       # White

# Background
On_Black=\033[40m       # Black
On_Red=\033[41m         # Red
On_Green=\033[42m      # Green
On_Yellow=\033[43m      # Yellow
On_Blue=\033[44m        # Blue
On_Purple=\033[45m      # Purple
On_Cyan=\033[46m        # Cyan
On_White=\033[47m       # White

# High Intensty
IBlack=\033[0;90m       # Black
IRed=\033[0;91m         # Red
IGreen=\033[0;92m       # Green
IYellow=\033[0;93m      # Yellow
IBlue=\033[0;94m        # Blue
IPurple=\033[0;95m      # Purple
ICyan=\033[0;96m        # Cyan
IWhite=\033[0;97m       # White

# Bold High Intensty
BIBlack=\033[1;90m      # Black
BIRed=\033[1;91m        # Red
BIGreen=\033[1;92m      # Green
BIYellow=\033[1;93m     # Yellow
BIBlue=\033[1;94m       # Blue
BIPurple=\033[1;95m     # Purple
BICyan=\033[1;96m       # Cyan
BIWhite=\033[1;97m      # White

# High Intensty backgrounds
On_IBlack=\033[0;100m   # Black
On_IRed=\033[0;101m     # Red
On_IGreen=\033[0;102m   # Green
On_IYellow=\033[0;103m  # Yellow
On_IBlue=\033[0;104m    # Blue
On_IPurple=\033[10;95m  # Purple
On_ICyan=\033[0;106m    # Cyan
On_IWhite=\033[0;107m   # White
LIGHT_BLUE  = \033[1;36m
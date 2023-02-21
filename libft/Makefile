# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalseri <aalseri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/24 21:10:12 by aalseri           #+#    #+#              #
#    Updated: 2023/01/08 17:23:44 by aalseri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

DIR_SRCS	= srcs
DIR_OBJS	= objs
SUBDIRS		= is to mem str put lst int memory ft_printf gnl ft_fprintf

S_PRINTF	= ft_printf ft_fprintf ft_fputhexa
S_GNL		= get_next_line get_next_line_utils
S_IS		= ft_isalnum ft_isalpha ft_isascii ft_isdigit \
				ft_isprint ft_isspace ft_isdigitneg

S_INT		= ft_atoi ft_itoa ft_atoiof
S_LST		= ft_lstadd_back ft_lstadd_front ft_lstclear \
				ft_lstdelone ft_lstiter ft_lstlast \
				ft_lstmap ft_lstnew ft_lstsize
S_MEM		= ft_memchr ft_memcmp ft_memcpy \
				ft_memmove ft_memset
S_MEMORY	= ft_calloc ft_free ft_bzero
S_PUT		= ft_putchar_fd ft_putendl_fd ft_putnbr_fd \
				ft_putstr_fd
S_STR		= ft_split ft_strcat ft_strchr \
				ft_strcpy ft_strdup ft_strjoin \
				ft_strlcat ft_strlcpy ft_strlen \
				ft_strmapi ft_strncmp ft_strnstr \
				ft_strrchr ft_strtrim ft_substr ft_swap
S_TO		= ft_tolower ft_toupper


SRCS = $(addsuffix .c, $(addprefix srcs/ft_printf/, $(S_PRINTF))) \
		$(addsuffix .c, $(addprefix srcs/gnl/, $(S_GNL))) \
		$(addsuffix .c, $(addprefix srcs/is/, $(S_IS))) \
		$(addsuffix .c, $(addprefix srcs/int/, $(S_INT))) \
		$(addsuffix .c, $(addprefix srcs/lst/, $(S_LST))) \
		$(addsuffix .c, $(addprefix srcs/mem/, $(S_MEM))) \
		$(addsuffix .c, $(addprefix srcs/memory/, $(S_MEMORY))) \
		$(addsuffix .c, $(addprefix srcs/put/, $(S_PUT))) \
		$(addsuffix .c, $(addprefix srcs/str/, $(S_STR))) \
		$(addsuffix .c, $(addprefix srcs/to/, $(S_TO)))



SRCS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_SRCS)/, $(dir)))
OBJS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_OBJS)/, $(dir)))
OBJS		= $(subst $(DIR_SRCS), $(DIR_OBJS), $(SRCS:.c=.o))

INCLUDES	= -I includes

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

RM		= /bin/rm -f

$(DIR_OBJS)/%.o :	$(DIR_SRCS)/%.c
			@printf "${BIPurple}🏗️ Generating libft objects... %-33.33s\r${Color_Off}" $@
			@mkdir -p $(DIR_OBJS) $(OBJS_DIRS)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: ${NAME}

$(NAME):	$(OBJS)
			@ar -rcs $(NAME) $(OBJS)
			@ranlib $(NAME)
			@printf "\n${BIGreen}LIBFT is ready${Color_Off}\n"
			@sleep 1

clean:
			@echo "${BIRed}Libft Cleaned!${Color_Off}"
			@$(RM) $(OBJS)
			@$(RM) -r $(DIR_OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

norme:
			norminette

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

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 10:03:25 by lomartin          #+#    #+#              #
#    Updated: 2026/01/05 09:26:19 by lomartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS += -Wall -Wextra -Werror
DFLAGS += -g3 -DBUILD_DEBUG=1
LIBFT = libft/libft.a
LIBFT_DEBUG = libft/libft_DEBUG.a
LIB_FLAGS = -lreadline

NAME = minishell
D_NAME = minishell_debug

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDES_DIR = -Iincludes -Ilibft/includes

FILES = main\
		readline\
		builtin/cd\
		builtin/echo\
		builtin/env\
		builtin/exit\
		builtin/export\
		builtin/pwd\
		builtin/set_var\
		builtin/subshell\
		builtin/unset\
		parsing/envp\
		parsing/token_word_parsing_compound\
		parsing/token_word_parsing\
		parsing/token_word_name\
		parsing/token_operator_parsing\
		parsing/token_operator_parsing_2\
		parsing/token_parser_errors\
		parsing/token_parser\
		parsing/token_free\
		parsing/token_validity_checker\
		parsing/token_validity\
		parsing/token_parsing_utils\
		parsing/token_build_subshells\
		parsing/command_builder\
		parsing/command_utils\
		parsing/command_visualizer\
		parsing/command_visualizer_2\
		execution/commands\
		execution/conditions\
		execution/exec\
		execution/parsing\
		execution/parsing_args\
		execution/parsing_utils\
		execution/readdir\
		execution/redirects\
		execution/redirects_utils\
		execution/wildcard\
		execution/wildcards_utils\
		utils/error\
		utils/utils\
		utils/exec_utils\
		utils/dict_utils\
		utils/gc_debug



SRCS = $(addprefix $(SRC_DIR),  $(addsuffix .c, $(FILES)))

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))
DEP = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(FILES)))

D_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix _DEBUG.o, $(FILES)))
D_DEP = $(addprefix $(OBJ_DIR), $(addsuffix _DEBUG.d, $(FILES)))

DEPFLAGS = -MMD

.PHONY: clean fclean all libft re debug libft-rebuild libft-debug-rebuild

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIB_FLAGS) -o $(NAME)

$(D_NAME): $(LIBFT_DEBUG) $(MLX) $(D_OBJ)
	$(CC) $(DFLAGS) $(D_OBJ) $(LIBFT_DEBUG) $(LIB_FLAGS) -o $(D_NAME)

debug: $(D_NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES_DIR) -c $< -o $@

$(OBJ_DIR)%_DEBUG.o: $(SRC_DIR)%.c | obj
	$(CC) $(DFLAGS) $(DEPFLAGS) $(INCLUDES_DIR) -c $< -o $@


$(LIBFT): libft-rebuild
	@true

libft-rebuild:
	make -C libft all

$(LIBFT_DEBUG): libft-debug-rebuild
	@true

libft-debug-rebuild:
	make -C libft debug


obj:
	mkdir -p $@

clean:
	rm -f $(OBJ) $(D_OBJ) $(DEP) $(D_DEP)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(D_NAME)
	make -C libft fclean

re: fclean all

-include $(DEP) $(D_DEP)

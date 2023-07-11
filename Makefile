# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akouame <akouame@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 19:49:34 by hkaddour          #+#    #+#              #
#    Updated: 2022/11/04 11:59:32 by akouame          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
HEADER = include/minishell.h
FLAGS = -Wextra -Wall -Werror
LIB = libft/libft.a
READLINE = $(shell brew --prefix  readline)
SRC = $(addprefix src/, shell/main.c shell/init.c shell/signals.c shell/shell_utils.c \
			free/free_collector.c error/error_handling.c \
			tokenizer/lexer/lexer_pt1.c tokenizer/lexer/lexer_pt2.c \
			tokenizer/tokenizer.c tokenizer/tokenizer_helper.c \
			tokenizer/token_identifier/token_identifier1.c \
			tokenizer/token_identifier/token_identifier2.c \
			tokenizer/expand_allocate.c tokenizer/expand_count.c \
			tokenizer/join_token/join_token.c tokenizer/token_identifier/token_identifier3.c \
			tokenizer/token_identifier/token_identifier_utils.c \
			tokenizer/join_token/join_token_helper.c \
			tokenizer/expand_utils.c \
			parser/parser.c parser/parser_helper.c parser/parser_utils.c \
			parser/heredoc/heredoc.c \
			execution/execution.c execution/pipeline.c execution/pipeline_helper.c \
			execution/redirection.c execution/run_one_cmd.c execution/exec_utils.c \
			builtin_cmd/builtin_cmd.c builtin_cmd/builtin_utils.c builtin_cmd/cd/cd.c \
			builtin_cmd/cd/cd_everywhere.c builtin_cmd/cd/cd_utils.c \
			builtin_cmd/cd/cd_everywhere_helper.c builtin_cmd/cd/cd_swaping_oldpwd_pwd.c \
			builtin_cmd/echo.c builtin_cmd/env/env.c builtin_cmd/env/env_utils.c \
			builtin_cmd/env/get_env.c builtin_cmd/exit/exit.c builtin_cmd/exit/exit_utils.c \
			builtin_cmd/export/export.c builtin_cmd/export/export_helper.c \
			builtin_cmd/export/export_utils.c builtin_cmd/pwd.c builtin_cmd/unset.c)

OBJS = $(SRC:.c=.o)

all: $(NAME)
	
$(NAME): $(LIB) $(OBJS)
	@$(CC) $(OBJS) $(LIB) -o $(NAME) -L $(READLINE)/lib -lreadline

%.o: %.c $(HEADER)
	@/bin/echo -n "."
	@$(CC) -I $(READLINE)/include $(FLAGS) -c $< -o $@ -I $(HEADER)

$(LIB):
	@make -C ./libft

clean:
	@make fclean -C ./libft
	@rm -rf $(OBJS)
	
fclean:
	@make fclean -C ./libft
	@rm -rf $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re

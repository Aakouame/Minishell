# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akouame <akouame@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 19:49:34 by hkaddour          #+#    #+#              #
#    Updated: 2022/10/29 16:23:35 by hkaddour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
HEADER = include/minishell.h
FLAGS = -g
LIB = libft/libft.a
OFILE = ofiles
READLINE = $(shell brew --prefix  readline)
SRC = $(addprefix src/, shell/main.c shell/init.c shell/signals.c shell/shell_utils.c \
			free/free_collector.c error/error_handling.c \
			tokenizer/lexer/lexer_pt1.c tokenizer/lexer/lexer_pt2.c \
			tokenizer/tokenizer.c tokenizer/tokenizer_helper.c \
			tokenizer/token_identifier/token_identifier1.c \
			tokenizer/token_identifier/token_identifier2.c \
			tokenizer/expand_allocate.c tokenizer/expand_count.c \
			tokenizer/join_token/join_token.c \
			parser/parser.c parser/parser_helper.c parser/parser_utils.c \
			parser/heredoc/heredoc.c parser/heredoc/heredoc_utils.c \
			parser/heredoc/len_hrdoc_data.c \
			execution/execution.c execution/pipeline.c execution/pipeline_helper.c \
			execution/redirection.c execution/run_one_cmd.c execution/exec_utils.c \
			builtin_cmd/builtin_cmd.c builtin_cmd/builtin_utils.c builtin_cmd/cd/cd.c \
			builtin_cmd/cd/cd_everywhere.c \
			builtin_cmd/cd/cd_everywhere_helper.c builtin_cmd/cd/cd_swaping_oldpwd_pwd.c \
			builtin_cmd/echo.c builtin_cmd/env/env.c builtin_cmd/env/env_utils.c \
			builtin_cmd/env/get_env.c builtin_cmd/exit/exit.c builtin_cmd/exit/exit_utils.c \
			builtin_cmd/export/export.c builtin_cmd/export/export_helper.c \
			builtin_cmd/export/export_utils.c builtin_cmd/pwd.c builtin_cmd/unset.c)









# SRC = src/shell/main.c \
# 			src/shell/init.c \
# 			src/shell/prompt.c \
# 			src/shell/signals.c \
# 			src/shell/shell_utils.c \
# 			src/tokenizer/tokenizer.c \
# 			src/tokenizer/tokenizer_helper.c \
# 			src/tokenizer/alloc_token/allocate_token_helper.c \
# 			src/tokenizer/alloc_token/allocate_tokens.c \
# 			src/tokenizer/alloc_token/allocate_tokens_dolla.c \
# 			src/tokenizer/alloc_token/allocate_tokens_dolla_begin.c \
# 			src/tokenizer/count_len_alloc/count_len_dolla.c \
# 			src/tokenizer/count_len_alloc/count_len_dolla_begin.c \
# 			src/tokenizer/count_len_alloc/count_value_len.c \
# 			src/tokenizer/count_len_alloc/count_value_len_helper.c \
# 			src/tokenizer/lexer/lexer_pt1.c \
# 			src/tokenizer/lexer/lexer_pt1_helper.c \
# 			src/tokenizer/lexer/lexer_pt2.c \
# 			src/tokenizer/token_identifier/token_identifier1.c \
# 			src/tokenizer/token_identifier/token_identifier2.c \
# 			src/tokenizer/token_identifier/token_identifier_helper.c \
# 			src/parser/heredoc/heredoc.c \
# 			src/parser/heredoc/heredoc_utils.c \
# 			src/parser/heredoc/len_hrdoc_data.c \
# 			src/parser/parser.c \
# 			src/parser/parser_helper.c \
# 			src/parser/parser_utils.c \
# 			src/execution/execution.c \
# 			src/execution/pipeline.c \
# 			src/execution/pipeline_helper.c \
# 			src/execution/redirection.c \
# 			src/execution/run_one_cmd.c \
# 			src/execution/exec_utils.c \
# 			src/builtin_cmd/builtin_cmd.c \
# 			src/builtin_cmd/cd/cd.c \
# 			src/builtin_cmd/cd/cd_everywhere.c \
# 			src/builtin_cmd/cd/cd_everywhere_helper.c \
# 			src/builtin_cmd/cd/cd_swaping_oldpwd_pwd.c \
# 			src/builtin_cmd/echo.c \
# 			src/builtin_cmd/env/env.c \
# 			src/builtin_cmd/env/env_utils.c \
# 			src/builtin_cmd/env/get_env.c \
# 			src/builtin_cmd/exit/exit.c \
# 			src/builtin_cmd/exit/exit_utils.c \
# 			src/builtin_cmd/export/export.c \
# 			src/builtin_cmd/export/export_helper.c \
# 			src/builtin_cmd/export/export_utils.c \
# 			src/builtin_cmd/pwd.c \
# 			src/builtin_cmd/unset.c \
# 			src/free/free_collector.c \
# 			src/error/error_handling.c \
# 			src/builtin_cmd/builtin_utils.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(OBJS) $(LIB) -o $(NAME) -L $(READLINE)/lib -lreadline

%.o: %.c $(HEADER)
	$(CC) -I $(READLINE)/include $(FLAGS) -c $< -o $@ -I $(HEADER)

$(LIB):
	make -C ./libft

clean:
	@make fclean -C ./libft
	@rm -rf $(OFILE)

fclean:
	@make fclean -C ./libft
	@rm -rf $(NAME) $(OBJS) *.dSYM

re: fclean all

.PHONY: all clean fclean re

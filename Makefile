.PHONY:     			all $(NAME) mkbuild lib clean fclean re sanitize

NAME					= minishell

BUILD_DIR				= build/
	
HEADER_DIR				= header/
HEADER_FILE				= minishell.h

DIR						= src/
SRC			 			= main.c init.c \
						  parsing/parsing.c \
						  exec/signal_handler/signal_handler.c \
						  exec/builtins/echo.c exec/builtins/cd.c exec/builtins/pwd.c exec/builtins/export.c \
						  exec/builtins/unset.c exec/builtins/env.c exec/builtins/exit.c \
						  exec/utils/chained_list.c exec/utils/utils.c exec/utils/setup_cmd.c \
						  exec/exec_functions/exec_hub.c exec/exec_functions/exec_setup_struct.c \
						  exec/exec_functions/exec_setup_files.c exec/exec_functions/exec_dup_manager.c \
						  exec/exec_functions/exec_path_utils.c exec/exec_functions/exec_get_path.c \
						  exec/exec_functions/exec_execution.c exec/exec_functions/exec_execution_utils.c \
						  exec/heredoc/heredoc.c exec/heredoc/heredoc_utils.c \
						  exec/exec_functions/exec_quit_utils.c \
						  exec/free_functions/free_utils.c \
						  parsing/input_operator_error.c \
						  parsing/pipe_error.c \
						  parsing/split_line.c \
						  parsing/get_all_cmd/get_cmd.c \
						  parsing/get_all_cmd/get_file.c \
						  parsing/get_all_cmd/get_flag.c \
						  parsing/get_all_cmd/get_content.c \
						  parsing/get_all_cmd/get_utils.c \
						  parsing/list_utils.c \
						  parsing/convert_3d_array.c \
						  parsing/free_utils_parsing.c \
						  parsing/global_variable/global_variable.c \
						  parsing/global_variable/global_variable_nbr_char.c \
						  parsing/global_variable/global_variable_utils.c \
						  parsing/global_variable/global_variable_special_case.c \
						  parsing/split_skip_quote.c \
							
OBJECTS			    	= $(SRC:%.c=$(BUILD_DIR)%.o)
	
LIBFT					= libft.a
LIB_DIR					= libft/

	
GCC						= gcc
CFLAGS					= -Wall -Wextra -Werror -g3 
LDLIBS					= -lreadline
SANITIZE				= $(CFLAGS) -fsanitize=address

RM 						= rm -rf

$(BUILD_DIR)%.o:		$(DIR)%.c $(HEADER_DIR)/$(HEADER_FILE) Makefile
						@mkdir -p $(@D)
						$(GCC) $(CFLAGS) -I$(HEADER_DIR) -I$(LIB_DIR) -c $< -o $@

all: 					mkbuild lib $(HEADER_DIR) $(NAME) 
						
mkbuild:
						@mkdir -p build
						
$(NAME): 				$(OBJECTS) $(LIB_DIR)$(LIBFT)
						$(GCC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT) $(LDLIBS)

sanitize :				$(OBJECTS) $(LIB_DIR)$(LIBFT)
						$(GCC) $(SANITIZE) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT)

lib:
						@make -C $(LIB_DIR)
					
clean:					
						@${RM} $(OBJECTS)
						@make clean -C $(LIB_DIR)
						@${RM} $(BUILD_DIR)

fclean:					clean
						@${RM} ${NAME}
						@make fclean -C $(LIB_DIR)

re:						fclean all
						$(MAKE) all

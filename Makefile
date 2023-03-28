.PHONY:     			all $(NAME) mkbuild lib clean fclean re sanitize

NAME					= minishell

BUILD_DIR				= build/
	
HEADER_DIR				= header/
HEADER_FILE				= minishell.h

DIR						= src/
SRC			 			= main.c init.c \
						  parsing/parsing.c \
						  exec/redirect/redirect.c \
						  exec/signal_handler/signal_handler.c \
						  exec/builtins/echo.c exec/builtins/cd.c exec/builtins/pwd.c exec/builtins/export.c \
						  exec/builtins/unset.c exec/builtins/env.c exec/builtins/exit.c \
						  exec/pipe/dup_manager.c exec/pipe/execution.c exec/pipe/get_exec_done.c \
						  exec/pipe/get_exec_done_utils.c exec/pipe/get_path.c exec/pipe/heredoc.c \
						  exec/pipe/quit_utils.c exec/pipe/utils.c exec/exec_functions/exec_pipe.c \
						  exec/utils/chained_list.c \
						  exec/exec_functions/exec_hub.c exec/exec_functions/exec_single_cmd.c \
						  exec/free_functions/free_utils.c \
						  parsing/input_operator_error.c \
						  parsing/split_line.c \
						  parsing/get_cmd.c \
						  parsing/get_file.c \
						  parsing/get_flag.c \
						  parsing/get_content.c \
						  parsing/get_utils.c \
						  parsing/list_utils.c \
						  parsing/convert_3d_array.c \
						  parsing/free_utils.c \
						  parsing/global_variable/global_variable.c \
						  parsing/global_variable/global_variable_nbr_char.c \
						  parsing/global_variable/global_variable_utils.c \
							
OBJECTS			    	= $(SRC:%.c=$(BUILD_DIR)%.o)
	
LIBFT					= libft.a
LIB_DIR					= libft/

	
GCC						= gcc
CFLAGS					= -Wall -Wextra -g3 
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

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/14 10:00:31 by tmatis            #+#    #+#              #
#    Updated: 2024/08/06 14:58:36 by brahimb          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME	= minishell
CC 		= clang -g3
CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -MMD -MF $(@:.o=.d)
AUTHOR	= ksainte_bbouaiss
DATE	= 31/05/2024

NOVISU 	= 1

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

FILE_EXTENSION	= .c

SRCS_PATH		= ./src

INCLUDE_PATH	= ./include

SRCS			= command_line_interface/CommandLineInterface.c \
					command_line_interface/CommandLineInterface_utils.c \
					command_line_interface/Printing_utilshelper.c \
					command_line_interface/Printing_utils.c \
					command_line_interface/Free_utils.c \
					command_line_interface/input_tokenizer.c \
					command_line_interface/input_tokenizer_helper.c \
					command_line_interface/handle_quotes.c \
					command_line_interface/input_tokenizer_token_type.c \
					command_parser/TreeParser.c \
					command_parser/TreeParserUtils.c \
					command_parser/TreeParserArgUtils.c \
					command_parser/TreeParserCmdUtils.c \
					environment_variable_manager/EnvironmentVariableManager.c  \
					environment_variable_manager/EnvironmentVariableManagerHelper.c \
					environment_variable_manager/EnvironmentVariableManagerSpecial.c \
					environment_variable_manager/Expander.c \
					environment_variable_manager/ExpanderHelper.c \
					executor/builtins/echo.c \
					executor/builtins/cd.c executor/builtins/cdhelper.c \
					executor/builtins/pwd.c \
					executor/builtins/export.c \
					executor/builtins/unset.c \
					executor/builtins/env.c \
					executor/builtins/exit.c \
					executor/Executor.c \
					executor/Execute_in_parent.c\
					executor/Execute_path_in_childs.c \
					executor/Execute_builtins_in_childs.c \
					executor/Find_childs_path.c \
					executor/Redirect_builtins_to_parent.c \
					executor/Redirect_to_childs.c \
					executor/Execution_utils.c \
					pipe_handler/PipeHandler.c \
					pipe_handler/Heredoc.c \
					signal_handler/SignalHandler.c \
					redirection_handler/RedirectionHandler.c \
					redirection_handler/RedirectionHandlerHelper.c
					
MAIN			= main.c

LIBFT 			= libft/libft.a

UNAME_S 		:= $(shell uname -s)

################################################################################
#                                  Makefile  objs                              #
################################################################################

SHELL := /bin/bash


OBJS				= $(addprefix objs/, ${SRCS:$(FILE_EXTENSION)=.o})
OBJ_MAIN			= $(addprefix objs/, ${MAIN:$(FILE_EXTENSION)=.o})
DEPS				= $(addprefix objs/, ${SRCS:$(FILE_EXTENSION)=.d})
DEPS_MAIN			= $(addprefix objs/, ${MAIN:$(FILE_EXTENSION)=.d})

################################################################################
#                                 Makefile logic                               #
################################################################################

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

COM_STRING   = "compiling"

# Set paths based on the operating system
ifeq ($(UNAME_S), Darwin)
    # macOS
    ifeq ($(shell test -d /Users/$(USER)/.brew && echo yes), yes)
        # User-specific Homebrew path
        READLINE_INCLUDE := /Users/$(USER)/.brew/opt/readline/include
        READLINE_LIB := /Users/$(USER)/.brew/opt/readline/lib
    else
        # Default Homebrew path
        READLINE_INCLUDE := /opt/homebrew/opt/readline/include
        READLINE_LIB := /opt/homebrew/opt/readline/lib
    endif
else
    # Add other OS-specific paths if needed
        READLINE_INCLUDE := /opt/homebrew/opt/readline/include
        READLINE_LIB := /opt/homebrew/opt/readline/lib
endif

HASH	= 

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Darwin) 
	RUN_CMD = script -q $@.log $1 > /dev/null; \
				RESULT=$$?
else ifeq ($(detected_OS),Linux)
	RUN_CMD = script -q -e -c "$(1)" $@.log > /dev/null; \
				RESULT=$$?; \
				sed -i '1d' $@.log; \
				sed -i "$$(($$(wc -l < $@.log)-1)),\$$d" $@.log
else
	RUN_CMD = $(1) 2> $@.log; \
				RESULT=$$?
endif

ifeq ($(shell git rev-parse HEAD &>/dev/null; echo $$?),0)
	AUTHOR	:= $(shell git log --format='%aN' | sort -u | awk '{printf "%s, ", $$0}' | rev | cut -c 3- | rev)
	DATE	:= $(shell git log -1 --date=format:"%Y/%m/%d %T" --format="%ad")
	HASH	:= $(shell git rev-parse --short HEAD)
endif

define run_and_test
printf "%b%-46b" "$(COM_COLOR)$(COM_STRING) " "$(OBJ_COLOR)$(@F)$(NO_COLOR)"; \
$(RUN_CMD); \
if [ $$RESULT -ne 0 ]; then \
	printf "%b\n" "$(ERROR_COLOR)[✖]$(NO_COLOR)"; \
	rm -rf .files_changed; \
	if [ $(NOVISU) -eq 0 ]; then \
		echo; \
	fi; \
elif [ -s $@.log ]; then \
	printf "%b\n" "$(WARN_COLOR)[⚠]$(NO_COLOR)"; \
else  \
	printf "%b\n" "$(OK_COLOR)[✓]$(NO_COLOR)"; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

define save_files_changed
	FILE_CPP=`echo $(SRCS) $(MAIN)`; \
	FILE_OBJ=`find objs -type f -name '*.o' 2>/dev/null | sed 's/objs\///'`; \
	TO_COMPILE=`echo $$FILE_CPP | wc -w`; \
	for FILE in $$FILE_CPP; do \
		for OBJ in $$FILE_OBJ; do \
			if [ $${FILE%$(FILE_EXTENSION)} = $${OBJ%.o} ]; then \
				if [ $(SRCS_PATH)/$$FILE -ot objs/$$OBJ ]; then \
					FILE_DEP=`echo objs/$$OBJ | sed 's/\.o/\.d/'`; \
					HEAD_FILES=`< $$FILE_DEP xargs | grep -oh "\w*.h\w*"`; \
					RECOMPILE=0; \
					for HEAD in $$HEAD_FILES; do \
						if [ $(SRCS_PATH)/$$HEAD -nt objs/$$OBJ ]; then \
							RECOMPILE=1; \
							break; \
						fi; \
					done; \
					if [ $$RECOMPILE -eq 0 ]; then \
						((TO_COMPILE=$$TO_COMPILE-1)); \
					fi;\
				fi; \
			fi; \
		done; \
	done; \
	echo 0/$$TO_COMPILE > .files_changed
endef

define draw_bar
	FILE_TOTAL=`bash -c 'cat .files_changed | cut -d"/" -f2'`; \
	FILE_DONE=`bash -c 'cat .files_changed | cut -d"/" -f1'`; \
	if [ $$FILE_TOTAL -eq 0 ]; then \
		FILE_TOTAL=1; \
		FILE_DONE=1; \
	fi; \
	RES=`echo "scale=2; $$FILE_DONE/$$FILE_TOTAL*48" | bc`; \
	RES=`echo $${RES%%.*}`; \
	printf "$(OBJ_COLOR)[$(NO_COLOR)"; \
	i=0; \
	while [ $$i -lt 48 ]; do \
		if [ $$i -lt $$RES ]; then \
			printf "$(OK_COLOR)█$(NO_COLOR)"; \
		else \
			printf "$(COM_COLOR)▒$(NO_COLOR)"; \
		fi; \
		((i=$$i+1)); \
	done; \
	printf "$(OBJ_COLOR)]$(NO_COLOR)"; \
	printf " ($(COM_COLOR)$$FILE_DONE$(NO_COLOR)/$(COM_COLOR)$$FILE_TOTAL$(NO_COLOR))"; \
	printf " "; \
	((FILE_DONE=$$FILE_DONE+1)); \
	echo $$FILE_DONE/$$FILE_TOTAL > .files_changed;
endef

define display_progress_bar
	if [ $(NOVISU) -eq 0 ]; then \
		line=`bash -c 'oldstty=$$(stty -g); stty raw -echo min 0; tput u7 > /dev/tty; IFS=";" read -r -d R -a pos; stty $$oldstty; row=$$(($${pos[0]:2} - 1)); echo $$row'`; \
		max_line=`tput lines`; \
		((max_line=$$max_line-2));\
		new_line=0; \
		tput sc; \
		i=0; \
		while [ $$i -lt 60 ]; do \
			printf " "; \
			((i=$$i+1)); \
		done; \
		tput rc; \
		if [ $$line -gt $$max_line ]; then \
			new_line=1; \
			echo ; \
		else \
			((line=$$line+1));\
		fi; \
		tput sc; \
		tput cup $$line; \
		$(draw_bar) \
		if [ $$new_line -eq 1 ]; then \
			((line=$$line-1));\
			tput cup $$line; \
		else \
			tput rc; \
		fi; \
	fi
endef

################################################################################
#                                 Makefile rules                             #
################################################################################

all: header setup $(NAME)
	@rm -rf .files_changed

header:
	@printf "%b" "$(OK_COLOR)"
	@echo "        ___  _____ ___  ___      _        "
	@echo "       /   |/ __  \|  \/  |     | |       "
	@echo "      / /| |\`' / /'| .  . | __ _| | _____ "
	@echo "     / /_| |  / /  | |\/| |/ _\` | |/ / _ \\"
	@echo "     \___  |./ /___| |  | | (_| |   <  __/"
	@echo "         |_/\_____/\_|  |_/\__,_|_|\_\___| v2"
	@echo
ifneq ($(HASH),)
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)@$(HASH)\n"
else
	@printf "%b" "$(OBJ_COLOR)Name:	$(WARN_COLOR)$(NAME)\n"
endif
	@printf "%b" "$(OBJ_COLOR)Author:	$(WARN_COLOR)$(AUTHOR)\n"
	@printf "%b" "$(OBJ_COLOR)Date: 	$(WARN_COLOR)$(DATE)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)CC: 	$(WARN_COLOR)$(CC)\n\033[m"
	@printf "%b" "$(OBJ_COLOR)Flags: 	$(WARN_COLOR)$(CFLAGS)\n\033[m"
	@echo


-include $(DEPS) $(DEPS_MAIN)

$(NAME):	$(LIBFT) ${OBJS} ${OBJ_MAIN}
			@$(call display_progress_bar)
			@$(call run_and_test,$(CC) $(CFLAGS) $(DFLAGS) -I$(READLINE_INCLUDE) -L$(READLINE_LIB) -lreadline -L./include/libft -I$(INCLUDE_PATH) -o $@ ${OBJS} ${OBJ_MAIN} -lft)

# @$(call run_and_test,$(CC) $(CFLAGS) $(DFLAGS) -I/opt/homebrew/opt/readline/include -L/opt/homebrew/opt/readline/lib -lreadline -L./include/libft -I$(INCLUDE_PATH) -o $@ ${OBJS} ${OBJ_MAIN} -lft)
# @$(call run_and_test,$(CC) $(CFLAGS) $(DFLAGS) -I$(READLINE_INCLUDE) -L$(READLINE_LIB) -lreadline -L./include/libft -I$(INCLUDE_PATH) -o $@ ${OBJS} ${OBJ_MAIN} -lft)
#@$(call run_and_test,$(CC) $(CFLAGS) $(DFLAGS) -I/Users/ksainte/.brew/opt/readline/include -L/Users/ksainte/.brew/opt/readline/lib -lreadline -L./include/libft -I$(INCLUDE_PATH) -o $@ ${OBJS} ${OBJ_MAIN} -lft)

setup:
	@$(call save_files_changed)

objs/%.o: 	$(SRCS_PATH)/%$(FILE_EXTENSION)
			@mkdir -p $(dir $@)
			@$(call display_progress_bar)
			@$(call run_and_test,$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I$(INCLUDE_PATH))

$(LIBFT):	
			@echo checking libft...
			@make -sC ./include/libft libft.a

clean:		header
			@rm -rf objs objs_tests
			@make -sC ./include/libft clean
			@printf "%-53b%b" "$(COM_COLOR)clean:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

fclean:		header clean
			@rm -rf $(NAME)
			@make -sC ./include/libft fclean
			@printf "%-53b%b" "$(COM_COLOR)fclean:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

re:			fclean all

.PHONY:		all clean fclean re header libft

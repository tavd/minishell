# ------------------------------ configurable -----------------------------------
# -MMD generates makefile dependencies that tell make which source file depend
#  on what headers. These get generated at the same time when the source files are compiled
DEP_FLAGS = -MMD -MP
CFLAGS = -Wall -Wextra -Werror
CC = cc
INCLUDE_PATHS = ./include

# (not used by gcc)
BUILD_PATH = ./build

# [c] do not warn about creation of file
# [r] eplace existing or insert new file(s) into the archive
# [U] set time stamps needed for replacement using make's archive(member) function
ARFLAGS = rcU
NAME := libft.a

LIBFT_MODULES ?= bool string stdio stdlib
# use 'export' in other makefile to set this. or use flag: -e SUB_MODULES="list of sub modules here ..."
# This can be used to change the module make will compile when recursively calling this Makefile.

# ---------------------------------- Files --------------------------------------
BOOL_SRC := \
    ft_isalnum.c \
    ft_isalpha.c \
    ft_isdigit.c \
    ft_isprint.c \
    ft_isascii.c \
    ft_is_int.c \
    ft_isdecimal.c \

BOOL_SRC := $(addprefix bool/, $(BOOL_SRC))
BOOL_OBJ := $(patsubst %.c, $(BUILD_PATH)/%.o, $(BOOL_SRC))

CTYPE_SRC := \
    ft_tolower.c \
    ft_toupper.c \

CTYPE_SRC := $(addprefix ctype/, $(CTYPE_SRC))
CTYPE_OBJ := $(patsubst %.c, $(BUILD_PATH)/%.o, $(CTYPE_SRC))

STRING_SRC := \
    ft_strlen.c \
    ft_strrchr.c \
    ft_strchr.c \
    ft_strlcat.c \
    ft_strlcpy.c \
    ft_strncmp.c \
    ft_strnstr.c \
    ft_strdup.c \
    ft_substr.c \
    ft_strjoin.c \
    ft_strtrim.c \
    ft_striteri.c \
    ft_strmapi.c \
    ft_memset.c \
    ft_bzero.c \
    ft_memcpy.c \
    ft_memcmp.c \
    ft_memmove.c \
    ft_memchr.c \

STRING_SRC := $(addprefix string/, $(STRING_SRC))
STRING_OBJ := $(patsubst %.c, $(BUILD_PATH)/%.o, $(STRING_SRC))

STDLIB_SRC := \
    ft_atoi.c \
    ft_itoa.c \
    ft_calloc.c \
    ft_atof.c \
    ft_split.c \

STDLIB_SRC := $(addprefix stdlib/, $(STDLIB_SRC))
STDLIB_OBJ := $(patsubst %.c, $(BUILD_PATH)/%.o, $(STDLIB_SRC))

MORE_STUFF = \
    ft_split.c \

LST_SRC := \
    ft_lstnew.c \
    ft_lstadd_front.c \
    ft_lstlast.c \
    ft_lstsize.c \
    ft_lstadd_back.c \
    ft_lstdelone.c \
    ft_lstclear.c \
    ft_lstiter.c \
    ft_lstmap.c \

LST_SRC := $(addprefix lst/, $(LST_SRC))
LST_OBJ := $(patsubst %.c, $(BUILD_PATH)/%.o, $(LST_SRC))

PRINTF_SRC  := \
    char_specifiers.c \
    int_specifiers.c \
    ft_printf.c \

PRINTF_SRC := $(addprefix ft_printf/, $(PRINTF_SRC))
PRINTF_OBJ := $(patsubst %.c, $(BUILD_PATH)/%.o, $(PRINTF_SRC))

STDIO_SRC := \
    ft_putchar_fd.c \
    ft_putendl_fd.c \
    ft_putstr_fd.c \
    ft_putnbr_fd.c \
    ft_putnbr_base.c \

STDIO_SRC := $(addprefix stdio/, $(STDIO_SRC))
STDIO_OBJ := $(patsubst %.c, $(BUILD_PATH)/%.o, $(STDIO_SRC))

# -------------------------------------------------------------------------
INCLUDE_FLAGS = $(addprefix -I, $(INCLUDE_PATHS))
CFLAGS += $(INCLUDE_FLAGS)

# This does NOT create, but lists the names of the dependency files which 'Make' uses to know
# when an obj dpending on a header needs to be rebuild, when that header file has changed.
ALL_OBJ_VARS := $(filter %_OBJ, $(.VARIABLES))
ALL_DEPS := $(patsubst %.o, %.d, $(foreach var, $(ALL_OBJ_VARS), $($(var))))
# -------------------------------------------------------------------------

all: $(LIBFT_MODULES)

# NOTE: on error delete the archive file ?
$(NAME):
	$(AR) $(ARFLAGS) $(NAME)

$(BUILD_PATH)/%.o: %.c
	@echo -n $(GREEN)
	@mkdir -p $(dir $@)
	$(CC) $(DEP_FLAGS) $(CFLAGS) -c $< -o $@
	@echo -n $(CYAN)

bool: $(BOOL_OBJ) $(NAME)($(BOOL_OBJ))
	@echo $(YELLOW)bool.h module done. $(GREEN)

ctype: bool $(CTYPE_OBJ) $(NAME)($(CTYPE_OBJ))
	@echo $(YELLOW)ctype.h module done. $(GREEN)

string: $(STRING_OBJ) $(NAME)($(STRING_OBJ))
	@echo $(YELLOW)string.h module done. $(GREEN)

printf: bool $(PRINTF_OBJ) $(NAME)($(PRINTF_OBJ))
	@echo $(YELLOW)ft_printf.h module done. $(GREEN)

stdio: printf $(STDIO_OBJ) $(NAME)($(STDIO_OBJ))
	@echo $(YELLOW)stdio.h module done. $(GREEN)

# TODO: add more subdivisions to stdlib
stdlib: bool $(STDLIB_OBJ) $(NAME)($(STDLIB_OBJ))
	@echo $(YELLOW)stdlib.h module done. $(GREEN)

lst: $(LST_OBJ) $(NAME)($(LST_OBJ))
	@echo $(YELLOW)lst.h module done. $(GREEN)

clean:
	@echo -n $(RED)
	rm -rf $(BUILD_PATH)
	@echo -n $(RESET)

fclean: clean
	@echo -n $(RED)
	rm -f $(NAME)
	@echo -n $(RESET)

re: fclean all

-include $(ALL_DEPS)

.PHONY:	clean fclean re all $(LIBFT_MODULES) string

.NOTPARALLEL: all

# --------------------------------- COLORS --------------------------------------
RED := $(shell tput -T xterm setaf 1)
GREEN := $(shell tput -T xterm setaf 2)
YELLOW := $(shell tput -T xterm setaf 3)
BLUE := $(shell tput -T xterm setaf 4)
PURPLE := $(shell tput -T xterm setaf 5)
CYAN := $(shell tput -T xterm setaf 6)
WHITE := $(shell tput -T xterm setaf 7)
RESET := $(shell tput -T xterm setaf 7)
# TODO: Reset doesn't work
#RESET := $(shell tput -T xterm setaf sgr0)

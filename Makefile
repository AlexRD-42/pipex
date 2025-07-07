# Configuration ------------------------------- #
NAME = pipex
BUILD_PATH = build
INC_PATH = includes
OBJ_PATH = $(BUILD_PATH)/obj
BIN = $(BUILD_PATH)/$(NAME)
VPATH = sources sources/utils

# Files --------------------------------------- #
LIBS =
SRCS = exec.c mem_copy.c
OBJS = $(addprefix $(OBJ_PATH)/, $(SRCS:.c=.o))

# Flags --------------------------------------- #
CC = clang
CFLAGS = -Wall -Wextra $(addprefix -I,$(INC_PATH)) -flto -fstrict-aliasing
LFLAGS =
DEBUG = -g -Wpedantic -Wcast-qual -Wfloat-equal -Wswitch-default -Wsign-conversion
SANITIZERS = -fsanitize=address,undefined,leak -fno-omit-frame-pointer
FAST = -march=native -O3 -ffast-math

# Pattern Rule -------------------------------- #
$(OBJ_PATH)/%.o: %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

# Linking Rule -------------------------------- #
$(BIN): $(OBJS) | $(BUILD_PATH)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) $(LFLAGS)

# Directory Rule ------------------------------ #
$(OBJ_PATH):
	@mkdir -p $@
$(BUILD_PATH):
	@mkdir -p $@

# Phonies ------------------------------------- #
all: $(BIN)

debug: CFLAGS += $(DEBUG)
debug: clean $(BIN)

fast: CFLAGS += $(FAST)
fast: clean $(BIN)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(BIN)

re: fclean all

.PHONY: all clean fclean re fast debug

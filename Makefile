SRC = $(addprefix $(SRC_DIR)/, check.c main.c gen_fa.c errors.c helper.c cJSON.c pdfgen.c)

SRC_DIR := srcs
OBJ_DIR := objs
INC_DIR := includes
LIB_DIR := ./lib
BIN_DIR := .

TARGET := pdf_gen
EXE := $(BIN_DIR)/$(TARGET)
OBJS := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC := gcc
CFLAGS := -Wall -Werror -Wextra

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -L$(LIB_DIR) -lft $? $(CFLAGS) -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I $(INC_DIR) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all

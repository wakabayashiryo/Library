#
#  File-Name: Makefile
#
#  Created on: 2016/9/10
#  Author: Wakabayashi Ryo
#
#	File-History:
# 	>date Detail
#	>2016/9/10 generate this file 
#

#target name
TARGET := project

#command of compile and compile options , remove 
CC = gcc	
OPTIMIZE := -O0
CFLAGS := -c -g $(OPTIMIZE) -std=c99 -MMD -MP -Wall -Wextra -Winit-self
LDFLAG := -Wl,-Map=Debug/$(TARGET).map
LIB := -lm
RM = rm -f -r 

#directory macros
SRCDIR := Src
INCDIR := Inc
LIBDIR := lib
LIBSRC := $(shell find $(LIBDIR) -name Src)
OBJ := Debug
BIN := Bin


SRCF := $(wildcard $(SRCDIR)/*.c)
LIBSRCF := $(foreach dir,$(LIBSRC),$(wildcard $(dir)/*.c))
OBJF := $(addprefix $(OBJ)/,$(notdir $(SRCF:%.c=%.o)))\
	 $(addprefix $(OBJ)/,$(notdir $(LIBSRCF:%.c=%.o)))
#directory of headerfiles macros
INCLUDE :=  -I Inc \
		$(addprefix -I ,$(shell find lib -name Inc))

#dependency file
DEPF := $(OBJF:%.o=%.d)

VPATH := $(LIBSRC) $(SRCDIR) 

.PHONY: all clean

all: $(BIN)/$(TARGET)

#generate binary-file
$(BIN)/$(TARGET): $(OBJF)
	-@mkdir -p $(BIN)
	$(CC) $(LDFLAG) -o $@ $^ $(LIB)

#sources are generated to objectfile in Subdirectry 
$(OBJ)/%.o: %.c
	-@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $< $(LIB)

-include $(DEPF) #-includeは.PHONYとallの間に入れないように

#delete object binary directries
clean: 
	$(RM) $(OBJ) $(BIN) 

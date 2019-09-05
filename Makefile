LEM-IN = lem-in

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

SRCDIR = srcs
OBJDIR = obj

SRC-LEM-DIR = lem-in/
LEM-FILES = main	tools	bfs	\
	patch	rooms	rooms1	ants	
LEM-OBJ = $(addprefix $(OBJDIR)/$(SRC-LEM-DIR),$(addsuffix .o,$(LEM-FILES)))

LIBFT = ./libft/libftprintf.a 
INCDIR = -I ./includes
LIBLINK = -L ./libft -lftprintf
LIBINC = -I ./libft/includes

all: $(LIBFT) $(LEM-IN)

$(LIBFT):
	@make -C ./libft

$(OBJDIR):
	@echo "Creating object files directories..."
	@mkdir $(OBJDIR)
	@mkdir $(OBJDIR)/$(SRC-LEM-DIR)
	@echo "Directories are created!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(FLAGS) $(INCDIR) $(LIBINC) -c $< -o $@

$(LEM-IN): $(LEM-OBJ)
	@echo "Compiling Lem-in..."
	@$(CC) $(LIBLINK) -o $(LEM-IN) $(LEM-OBJ) 
	@echo "Lem-in is compiled!"

libclean:
	@make clean -C ./libft

clean: libclean
	@echo "Deleting Lem-in object files..."
	@rm -rf $(OBJDIR)
	@echo "Lem-in object files are deleted!"

fclean: clean
	@echo "Deleting executables..."
	@rm -rf $(LEM-IN)
	@echo "Executables are deleted!"
	@make fclean -C ./libft
	@echo "Everything is cleaned!"

re: fclean
	@$(MAKE) all

test-bigs:
	./generator --big-superposition > test1; ./lem-in < test1

test-big:
	./generator --big > test1; ./lem-in < test1	

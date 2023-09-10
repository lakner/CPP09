NAME	= RPN
SRCS	= main.cpp PmergeMe.cpp
HEADERS	= PmergeMe.hpp

ODIR	= obj
OBJS	= $(addprefix $(ODIR)/, $(SRCS:.cpp=.o))

CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98
SANFLAGS = -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

print-%: 
	@echo $* = $($*)
			
all: $(NAME)

$(ODIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(ODIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all


.SUFFIXES = 

NAME = ft_containers

VECTOR = ft_vector

MAP = ft_map

STACK = ft_stack

HEADERS = avl.hpp is_integral.hpp iterators.hpp lexicographical_compare.hpp \
			map.hpp pair.hpp stack.hpp vector.hpp

SRC = main.cpp vector.cpp map.cpp stack.cpp

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME) $(VECTOR) $(MAP) $(STACK)

$(NAME) : main.o
	c++ $(FLAGS) $^ -o $@

$(VECTOR) : vector.o
	c++ $(FLAGS) $^ -o $@

$(STACK) : stack.o
	c++ $(FLAGS) $^ -o $@

$(MAP) : map.o
	c++ $(FLAGS) $^ -o $@

%.o : %.cpp $(HEADERS)
	c++ $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME) $(VECTOR) $(MAP) $(STACK)

re : fclean all

.PHONY : all clean fclean re
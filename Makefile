NAME = ft_containers

VECTOR = ft_vector std_vector

MAP = ft_map std_map

STACK = ft_stack std_stack

HEADERS = avl.hpp is_integral.hpp iterators.hpp lexicographical_compare.hpp \
			map.hpp pair.hpp stack.hpp vector.hpp

SRC = main.cpp ft_vector.cpp ft_map.cpp ft_stack.cpp \
		std_vector.cpp std_map.cpp std_stack.cpp

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME) $(VECTOR) $(MAP) $(STACK)

$(NAME) : main.o
	c++ $(FLAGS) $^ -o $@

$(VECTOR) : ft_vector.o  std_vector.o
	c++ $(FLAGS) ft_vector.o -o ft_vector
	c++ $(FLAGS) std_vector.o -o std_vector

$(STACK) : ft_stack.o std_stack.o
	c++ $(FLAGS) ft_stack.o -o ft_stack
	c++ $(FLAGS) std_stack.o -o std_stack

$(MAP) : ft_map.o std_map.o
	c++ $(FLAGS) ft_map.o -o ft_map
	c++ $(FLAGS) std_map.o -o std_map

%.o : %.cpp $(HEADERS)
	c++ $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME) $(VECTOR) $(MAP) $(STACK)

re : fclean all

.PHONY : all clean fclean re
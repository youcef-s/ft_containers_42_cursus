NAME = containers

FT_CONT = ft_containers

STD_CONT = std_containers

HEADERS = avl.hpp is_integral.hpp iterators.hpp lexicographical_compare.hpp \
			map.hpp pair.hpp stack.hpp vector.hpp

SRC = main.cpp ft_containers.cpp std_containers.cpp

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME) $(FT_CONT) $(STD_CONT)

$(NAME) : main.o
	c++ $(FLAGS) $^ -o $@

$(FT_CONT) : ft_containers.o
	c++ $(FLAGS) $^ -o $@

$(STD_CONT) : std_containers.o
	c++ $(FLAGS) $^ -o $@

%.o : %.cpp $(HEADERS)
	c++ $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME) $(FT_CONT) $(STD_CONT)

re : fclean all

.PHONY : all clean fclean re
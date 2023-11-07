#include <iostream>
#include <vector>

template <typename T>
void move_vectors(T& two, T& one) {
	two = std::move(one);
}
template <typename T>
void print(const T& vector) {
	if (vector.data() != nullptr) {
		for (int i = 0; i < vector.size(); ++i) {
			std::cout << vector[i] + ' ';
		}
		std::cout << std::endl << "Размер: " << vector.size();
		std::cout << std::endl << "Адрес: " << vector.data() << std::endl;
	}
	else {
		std::cout << "Вектора не существует!" << std::endl;
	}
}


int main() {
	setlocale(LC_ALL, "rus");
	std::vector <std::string> one = { "test_string_1", "test_string_2"};
	std::vector <std::string> two = {"test1", "test2", "test3"};
	print(one);
	print(two);
	move_vectors(two, one);
	print(one);
	print(two);
	return 0;
}
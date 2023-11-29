#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class func {
	std::vector<int> sum;
	std::vector<int> big_int;
public:
	func(std::vector<int> big) : big_int (big) {}
	void operator() (int n) {
		std::vector<int> v;
		while ((n / 10) != 0) {
			n /= 10;
			v.push_back(0);
		}
		int cash = 0;
		int temp;
		for (int i = 0; i < big_int.size(); ++i) {
			temp = big_int[i] * n + cash;
			cash = temp / 10;
			v.push_back(temp % 10);
		}
		if (cash > 0) {
			v.push_back(cash);
		}
		int size = sum.size();
		int size2 = v.size();
		int cash2 = 0;
		int j = 0;
		for (int i = 0; i < size || j < size2; ++i, ++j) {
			int temp;
			if (i < size && j < size2) {
				temp = sum[i] + v[j] + cash2;
				sum[i] = temp % 10;
				cash2 = temp / 10;
			}
			else if (i >= size) {
				temp = v[j] + cash2;
				sum.push_back(temp % 10);
				cash2 = temp / 10;
			}
			
			}
		if (cash2 > 0) {
			sum.push_back(cash2);
		}
	}
	std::vector<int> get_v() {
		return sum;
	}
	

};

class big_number {
	std::vector<int> big_int;
	void mirror(std::vector<int>& a) {
		std::vector<int> b;
		size_t size = a.size() - 1;
		for (int i = size; i >= 0; --i) {
			b.push_back (a[i]);
		}
		a = move(b);
	}
	bool mul(int m) {
		if ((m / 10) != 0) {
			return 1;
		}
		else {
			return  0;
		}
	}

	std::vector<int> decr(int m) {
		int n = m / 10;
		int i = 0;
		std::vector<int> v;
		while (m != 0) {
			v.push_back(m % 10 * static_cast<int>(pow(10, i)));
			m /= 10;
			++i;
		}
		return v;
	}
public:
	friend class func;
	big_number() {};
	big_number(const std::vector<int>& v) {

		big_int = v;
	}
	big_number(const big_number& c) {
		big_int.clear();
		for (int n : c.big_int) {
			big_int.push_back(n);
		}
	}
	big_number(big_number&& c) noexcept {
		big_int = move(c.big_int);
	}
	big_number& operator= (std::vector<int> v) {
		big_int = move(v);
		return *this;
	}
	big_number& operator= (const big_number& c) {
		if (&c != this) {
			big_int.clear();
			for (int n : c.big_int) {
				big_int.push_back(n);
			}
		}
		return *this;
	}
	big_number& operator= (big_number&& c) noexcept {
		if (&c != this) {
			big_int = move(c.big_int);
			}
		return *this;
	}

	big_number& operator+ (big_number& c) {
		size_t size, size2;
		int cash = 0;
		int iterator = 0;
		mirror(big_int);
		mirror(c.big_int);
		size = big_int.size();
		size2 = c.big_int.size();
		if (size >= size2) {
			for (int i = 0; i < size2; ++i) {
				int temp = 0;
				temp = big_int[i] + c.big_int[i] + cash;
				big_int[i] = temp % 10;
				cash = temp / 10;
				++iterator;
			}
			for (int i = iterator; i < size; ++i) {
				int temp = big_int[i] + cash;
				big_int[i] = temp % 10;
				cash = temp / 10;
			}
			if(cash > 0){
				big_int.push_back(cash);
			}
			
		}
			else {
				for (int i = 0; i < size2; ++i) {
					int temp = 0;
					if (i < size) {
						temp = big_int[i] + c.big_int[i] + cash;
						big_int[i] = temp % 10;
						cash = temp / 10;
					}
					else {
						temp = c.big_int[i] + cash;
						big_int.push_back(temp % 10);
						cash = temp / 10;
					}
				}
				if (cash > 0) {
					big_int.push_back(cash);
				}
			}
		mirror(big_int);
		mirror(c.big_int);
		return *this;
	}
	big_number& operator* (int m) {
		int cash = 0;
		func funct(big_int);
		mirror(big_int);
		if (mul(m)) {
			std::vector<int> v = decr(m);
			auto func = std::for_each(v.begin(), v.end(), funct);
			big_int = func.get_v();
		}
		else {
			for (int i = 0; i < big_int.size(); ++i) {
				int temp = 0;
				temp = big_int[i] * m + cash;
				big_int[i] = temp % 10;
				cash = temp / 10;
			}
			if (cash >= 10) {
				big_int.push_back(cash % 10);
				big_int.push_back(cash / 10);
			}
			else if (cash > 0 && cash < 10) {
				big_int.push_back(cash);
			}
		}
		mirror(big_int);
		return *this;
	}
	friend big_number& operator* (int m, big_number& c);

	void print() {
		for (int n : big_int) {
			std::cout << n << ' ';
		}
		std::cout << std::endl;
	}
	
};


bool mul(int m) {
	if ((m / 10) != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

std::vector<int> decr(int m) {
	int n = m / 10;
	int i = 0;
	std::vector<int> v;
	while (m != 0) {
		v.push_back(m % 10 * static_cast<int>(pow(10, i)));
		m /= 10;
		++i;
	}
	return v;
}

void mirror(std::vector<int>& a) {
	std::vector<int> b;
	size_t size = a.size() - 1;
	for (int i = size; i >= 0; --i) {
		b.push_back (a[i]);
	}
	a = move(b);
}

big_number& operator* (int m, big_number& c) {
	int cash = 0;
	mirror(c.big_int);
	if (mul(m)) {
		std::vector<int> v = decr(m);
		func funct(c.big_int);
		auto func = for_each(v.begin(), v.end(), funct);
		c.big_int = func.get_v();
	}
	else {
		for (int i = 0; i < c.big_int.size(); ++i) {
			int temp = 0;
			temp = c.big_int[i] * m + cash;
			c.big_int[i] = temp % 10;
			cash = temp / 10;
		}
		if (cash > 0) {
			c.big_int.push_back(cash);
		}
	}
	mirror(c.big_int);
	return c;
}


std::vector<int> big_integer(std::string s) {
	std::vector<int> big_int;
	for (char n : s) {
		big_int.push_back(atoi(&n));
	}
	return big_int;
}


int main() {
	big_number number1 = big_integer("923421123131129");
	big_number number2 = big_integer("49283479283423948");
	number1.print();
	number2.print();
	big_number number3;
	//number3 = number1;
	//number3.print();
	//number1.print();
	//number3 = number1 + number2;
	//number3.print();
	//number3 = number1 * 3;
	//number3 = 120 * number1;
	number3.print();

	return 0;
}
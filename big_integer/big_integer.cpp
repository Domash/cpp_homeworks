#include "big_integer.hpp"

typedef std::vector <int>::size_type vec_type;

big_integer::big_integer() {
	data.push_back(0);
}

big_integer::big_integer(long long val) {
	if(val < 0) {
		val *= -1;
		sign = true;
	}
	do {
		data.push_back(val % 10);
		val /= 10;
	} while(val);
}

big_integer::big_integer(big_integer const &other) {
	sign = other.sign;
	data = other.data;
}

big_integer::big_integer(std::string const &str){
	this -> data.clear();
	bool negate = (str[0] == '-');
	for(auto &it : str) {
		if(is_digit(it)) {
			this -> data.push_back(it);
		}
	}
	sign = negate;
	std::reverse(this -> data.begin(), this -> data.end());
}

//operators ****************************************************************************

bool operator == (big_integer const &a, big_integer const &b) {
	if(a.sign != b.sign) {
		return false;
	}

	if(a.data.size() != b.data.size()) {
		return false;
	}

	auto len = a.data.size();
	for(auto i = 0; i < len; ++i) {
		if(a.data[i] != b.data[i]) {
			return false;
		}
	}
	return true;
}

bool operator != (big_integer const &a, big_integer const &b) {
	return !(a == b);
}

bool operator > (big_integer const &a, big_integer const &b) {

	bool flag = false;

	if(a.sign < b.sign) {
		return true;
	} else if(a.sign > b.sign) {
		return false;
	} else if(a.sign) {
		flag = true;
	}

	auto len_a = a.data.size();
	auto len_b = b.data.size();
	
	if(len_a != len_b) {
		return (len_a > len_b) ^ flag;
	}

	for(int i = (int)len_a - 1; i >= 0; --i) {
		if(a.data[i] != b.data[i]) {
			return (a.data[i] > b.data[i]) ^ flag;
		}
	}
	return false ^ flag;
}

bool operator < (big_integer const &a, big_integer const &b) {
	return (b > a);
}

bool operator >= (big_integer const &a, big_integer const &b) {
	if(a == b) return true;
	return a > b;

}

bool operator <= (big_integer const &a, big_integer const &b) {
	if(a == b) return true;
	return a < b;
}

big_integer operator + (big_integer const &a, big_integer const &b) {
	if(a.sign == b.sign) {
		big_integer result;
		result.sign = a.sign;
		auto len = std::max(a.data.size(), b.data.size()) + 1;
		result.data.resize(len, 0);

		int curr_val = 0;
		for(auto i = 0; i < len; ++i) {
			if(i < a.data.size()) curr_val += a.data[i];
			if(i < b.data.size()) curr_val += b.data[i];
			result.data[i] = (curr_val % big_integer::base);
			curr_val /= big_integer::base;
		}
		result.shrink_zeroes();
		return result;
	}

	big_integer t = b;
	t.sign ^= true;
	return a - t;
}

big_integer operator - (big_integer const &a, big_integer const &b) {
	big_integer result;
	if(a.sign == b.sign) {
		if(a.abs() >= b.abs()) {
			result = a;
			auto curr_val = 0;
			for(auto i = 0; i < b.data.size() || curr_val; ++i) {
				result.data[i] -= curr_val + (i < b.data.size() ? b.data[i] : 0);
				curr_val = result.data[i] < 0;
				if(curr_val) result.data[i] += big_integer::base;

			}
			result.shrink_zeroes();
			return result;
		}
		result = b - a;
		result.sign ^= true;
		return result;
	}
	result = b;
	result.sign ^= true;
	return a + result;
}

big_integer operator * (big_integer const &a, big_integer const &b) {
	big_integer result;
	result.sign = a.sign ^ b.sign;
	auto len = a.data.size() + b.data.size() + 1;
	result.data.resize(len, 0);

	for(auto i = 0; i < a.data.size(); ++i) {
		for(auto j = 0; j < b.data.size(); ++j) {
			int curr_pos = j + i;
			int curr_mul = a.data[i] * b.data[j];

			while(curr_mul) {
				result.data[curr_pos] += curr_mul % big_integer::base;
				curr_mul /= big_integer::base;
				curr_pos++;
			}
		}
	}

	int cnt = 0;
	for(auto i = 0; i < result.data.size(); ++i) {
		cnt += result.data[i];
		result.data[i] = cnt % big_integer::base;
		cnt /= big_integer::base;
	}
	result.shrink_zeroes();

	return result;
}

big_integer operator / (big_integer const &a, big_integer const &b) {

}

big_integer operator % (big_integer const &a, big_integer const &b) {
	
}

big_integer &big_integer::operator = (big_integer const &val) {
	this -> sign = val.sign;
	this -> data = val.data;
	return *this;
}

big_integer &big_integer::operator += (big_integer const &val) {
	*this = *this + val;
	return *this;
}

big_integer &big_integer::operator -= (big_integer const &val) {
	*this = *this - val;
	return *this;
}

big_integer &big_integer::operator *= (big_integer const &val) {
	*this = *this * val;
	return *this;
}

//operators ****************************************************************************

std::string to_string(big_integer const &val) {
	if(val.is_zero()) {
		return "0";
	}

	std::string result = "";
	for(const auto &it: val.data) {
		result += static_cast<char>(it) + '0';
	}
	if(val.sign) {
		result += "-";
	}

	std::reverse(result.begin(), result.end());

	return result;
}

bool big_integer::is_zero() const {
	return (data.size() == 1 && data[0] == 0);
} 

void big_integer::shrink_zeroes() {
	while(data.size() && !data.back()) {
		data.pop_back();
	}
	if(!data.size()) {
		data.push_back(0);
		sign = false;
	}
}

bool big_integer::is_digit(char val) const {
	return (val >= '0' && val <= '9');
}

big_integer big_integer::abs() const {
	big_integer result = *this;
	result.sign = false;
	return result;
}

int big_integer::get_digit(size_t index) const {
	if(index < this -> data.size()) {
		return this -> data[index];
	} 
	return 0;
}


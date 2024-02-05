#include <iostream>

namespace dv {
	template<typename tp>
	class vector {
		tp* data;
		size_t size;

	public:

		//Default constructor
		vector() : data(nullptr), size(0) {}

		//Constructor to fill size with written value
		explicit vector(size_t _size, tp value) : size(_size) {
			data = new tp[size];

			for (size_t i = 0; i < size; i++)
				data[i] = value;
		}

		//Constructor to fill size with nulls 
		explicit vector(size_t _size) : size(_size) {
			data = new tp[size];

			for (size_t i = 0; i < size; i++)
				data[i] = 0;
		}

		//Copy constructor
		vector(const vector& other) : data(nullptr), size(0) { //explicit do not match
			makeCopy(other);
		}

		//Destructor
		~vector() {
			delete[] data;
		}

		tp& operator[](int index) {
			return indexFind(index);
		}
		const tp& operator[](int index) const {
			return indexFind(index);
		}

		vector& operator=(const vector& other) {
			delete[] data;
			makeCopy(other);
			return *this;
		}

		//Summary with another vector
		vector operator+(const vector& other) {
			vector temp = *this;

			if (temp.size <= other.size)
				for (size_t i = 0; i < temp.size; i++)
					temp.data[i] += other.data[i];

			else for (size_t i = 0; i < other.size; i++)
				temp.data[i] += other.data[i];

			return temp;
		}

		template<size_t N> //to give size of array
		//Summary with array of the same type
		vector<tp> operator+(const tp(&arr)[N]) {
			vector temp = *this;

			if (temp.size < N) {
				resize(N);
				for (size_t i = 0; i < N; i++)
					temp.data[i] += arr[i];
			}
			else for (size_t i = 0; i < N; i++)
				temp.data[i] += +arr[i];

			return temp;
		}

		template<size_t N> //to give size of array
		vector<tp>& operator=(const tp(&arr)[N]) {
			size_t arrSize = N;

			if (size >= arrSize) {
				for (size_t i = 0; i < arrSize; i++)
					data[i] = arr[i];
			}
			else {
				resize(arrSize);
				for (size_t i = 0; i < arrSize; i++)
					data[i] = arr[i];
			}

			return *this;
		}

		//Equal operator
		friend bool operator==(const vector& first, const vector& second) {
			return isEqual(first, second);
		}
		//No-equal operator
		friend bool operator!=(const vector& first, const vector& second) {
			return !isEqual(first, second);
		}

		//overloaded << to show all vector (equals show_all)
		friend std::ostream& operator<<(std::ostream& os, const vector& vec) {
			for (size_t i = 0; i < vec.size; i++)
				os << vec.data[i] << " ";

			return os;
		}

		//overloaded >> to set an element to the end of the vector (push_back)
		friend std::istream& operator>>(std::istream& is, vector& vec) {

			tp value;
			is >> value;
	
			vec.push_back(value);
			return is;
		}

		void show_all() {
			for (size_t i = 0; i < size; i++)
				std::cout << data[i] << " ";
			std::cout << '\n';
		}

		//set an element to the end of array by array's resizing
		void push_back(tp element) {
			resize(size + 1);
			data[size - 1] = element;
		}

		//push one element to any place
		void push_at(size_t position, tp element) {
			size_t targetPos = position - 1;
			vector temp = *this;
			delete[] data;

			size = size + 1;
			data = new tp[size];
			for (size_t i = 0; i < size; i++) {
				if (i < targetPos)
					data[i] = temp.data[i];
				else if (i == targetPos)
					data[i] = element;
				else data[i] = temp.data[i - 1];
			}
		}

		//push array of elements to any place
		template<size_t N>
		void push_at(size_t position, const tp(&arr)[N]) {
			size_t targetPos = position - 1;
			int elementsPushed = 0;

			vector temp = *this;
			delete[] data;

			size = size + N;
			data = new tp[size];
			for (size_t i = 0; i < size; i++) {
				if (i < targetPos)
					data[i] = temp.data[i];
				else if (i >= targetPos && elementsPushed < N)
					data[i] = arr[elementsPushed++];
				else data[i] = temp.data[i - N];
			}
		}

		//remove an element from the end of array by array's resizing
		void pop_back() {
			resize(size - 1);
		}

		//remove an element from any place
		void deleteAt(size_t position) {
			
			size_t targetPos = position - 1;
			if (targetPos >= size) {
				std::cerr << "Error. Delete position is out of bounds\n";
				return;
			}

			vector temp = *this;

			delete[] data;
			data = new tp[size - 1];

			for (size_t i = 0; i < targetPos; i++)
				data[i] = temp.data[i];

			for (size_t i = targetPos + 1; i < size; i++)
				data[i - 1] = temp.data[i];

			--size;
		}

		// delete an array of elements from the start position to the end position (not indeces in function args)
		void deleteUntil(size_t start, size_t end) {
			size_t startIndex = start - 1;
			size_t endIndex = end - 1;
			
			//Start must be from an element previous to the last, and the end 
			if (startIndex > size - 2 || endIndex >= size) {
				std::cerr << "Error. Positions is incorrect. Try to decrease start or end position\n";
				return;
			}

			size_t deleteSize = endIndex - startIndex + 1;
			vector temp = *this;
			
			delete[] data;
			data = new tp[size - deleteSize];

			for (size_t i = 0; i < startIndex; i++)
				data[i] = temp.data[i];

			for (size_t i = endIndex + 1; i < size; i++)
				data[i - deleteSize] = temp.data[i];
			
			size -= deleteSize;
		}

		//get size
		size_t getSize() const {
			return size;
		}
		//get data
		tp* getData() {
			return data;
		}
		//get data if const
		const tp* getData() const {
			return data;
		}

	private:
		//for []
		tp& indexFind(int index) {
			if (index < 0 || index >(size - 1)) {
				std::cerr << "Index is outside of bounds. Returned index 0\n";
				return data[0];
			}
			return data[index];
		}

		//for copy constructor and =
		void makeCopy(const vector& other) {
			size = other.size;
			data = new tp[size];

			for (size_t i = 0; i < size; i++)
				data[i] = other.data[i];
		}

		//Recreate array with new size. If size less then before it returns array with fit elements; if bigger then new elemenets return as 0
		void resize(size_t newSize) {
			vector temp = *this;
			delete[] data;
			data = new tp[newSize];

			for (int i = 0; i < newSize; i++) {
				if (i < temp.size)
					data[i] = temp.data[i];
				else data[i] = 0;
			}
			size = newSize;
		}

		//function to check equality
		friend bool isEqual(const vector& v1, const vector& v2) {
			if (v1.size != v2.size)
				return false;
			else for (size_t i = 0; i < v1.size; i++)
					if (v1.data[i] != v2.data[i])
						return false;
			return true;
		}

	};
}

void PreviousTest() {
	int a[] = { 1, 2, 4 };
	dv::vector<int> _vec(5, 0);
	_vec = a;
	_vec.show_all();

	dv::vector<float> first(3);
	float first_values[] = { 12.5, 13.0, 14.0 };
	first = first_values;
	first.show_all();

	dv::vector<float> second(3);
	float second_values[] = { 0, 5.2, 8.0 };
	second = second_values;
	second.show_all();

	dv::vector<float> summary(3, 0);
	dv::vector<float> sum;
	summary = first + second;
	summary.show_all();

	summary.push_back(3.2);
	sum = summary + second;
	sum.show_all();
	sum.push_at(3, 12.5);
	sum.show_all();

	float abab[] = { 0, 3, 0 };
	sum.push_at(4, abab);
	sum.show_all();


	first = summary;
	std::cout << (first == summary) << std::endl;
	std::cout << (first == second) << std::endl;
	std::cout << (first != second) << std::endl;
}

int main() {
	
	//PreviousTest();

	int a[] = { 1, 2, 4 };
	dv::vector<int> _vec(5, 2);
	_vec = a;
	_vec.show_all();

	_vec.deleteAt(3);
	_vec.show_all();

	_vec.deleteUntil(1, 3);
	std::cout << _vec << std::endl;
	std::cout << _vec.getSize() << std::endl;

	return 0;
}

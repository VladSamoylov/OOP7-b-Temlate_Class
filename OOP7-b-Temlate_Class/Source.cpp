#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

template <class T>
class RealNumber {
private:
	T* mas;
	int n;
public:
	RealNumber();
	RealNumber(const int&);
	RealNumber(const RealNumber&);
	void Generate();
	RealNumber operator=(const RealNumber&);
	RealNumber operator+(const RealNumber&);
	RealNumber operator-(const RealNumber&);
	double operator*(const RealNumber&);
	RealNumber operator<<(int);
	template <class U> friend RealNumber<U> operator>>(RealNumber<U>&, int);
	double operator[](const int&);
	void Show();
	~RealNumber();
};

/**
 * @brief Конструктор класу RealNumber за замовченням
*/
template<class T>
RealNumber<T>::RealNumber() {

	this->mas = nullptr;
	this->n = 0;
}

/**
 * @brief Параметричний конструктор класу RealNumber
 * @param n Кількість чисел дійсного типу в масиві
*/
template<class T>
RealNumber<T>::RealNumber(const int& n) {

	string type = typeid(T).name();
	this->n = n;
	this->mas = new T[this->n];
	for (int i = 0; i < this->n; i++) {
		if (type == "float" || type == "double") {
			this->mas[i] = static_cast<float>((rand() % 20) - 10) + static_cast<float>((rand() % 9) / 10.0) + static_cast<float>((rand() % 9) / 100.0);
		}
		else if (type == "bool") {
			this->mas[i] = rand() % 2;
		}
		else this->mas[i] = (rand() % 21) - 10;
	}
}

/**
 * @brief Конструктор копіювання класу RealNumber
 * @param rn Об'єкт для копіювання
*/
template <class T>
RealNumber<T>::RealNumber(const RealNumber& rn) {

	this->n = rn.n;
	this->mas = new T[this->n];
	for (int i = 0; i < rn.n; i++) {
		this->mas[i] = rn.mas[i];
	}
}

/**
 * @brief Метод, який генерує новий масив дійсного типу
*/
template <class T>
void RealNumber<T>::Generate() {
	
	string type = typeid(T).name();
	if (this->mas != nullptr) delete[] this->mas;
	this->n = (rand() % 10) + 1;
	this->mas = new T[this->n];
	for (int i = 0; i < this->n; i++) {
		if (type == "float" || type == "double") {
			this->mas[i] = static_cast<float>((rand() % 20) - 10) + static_cast<float>((rand() % 9) / 10.0) + static_cast<float>((rand() % 9) / 100.0);
		}
		else if (type == "bool") {
			this->mas[i] = rand() % 2;
		}
		else this->mas[i] = (rand() % 21) - 10;
	}
}

/**
 * @brief Метод, який відображає зміст масиву
*/
template <typename T>
void RealNumber<T>::Show() {

	cout << "{";
	for (int i = 0; i < this->n; i++) {
		cout << setw(6) << right << this->mas[i];
	}
	cout << " }" << endl;
}

/**
 * @brief Деструктор
*/
template<class T>
RealNumber<T>::~RealNumber() {

	delete[] this->mas;
}

/**
 * @brief Перевантаження бінарного оператору =
 * @param rn Об'єкт правого аргументу
 * @return Повернення поточного об'єкту
*/
template <class T>
RealNumber<T> RealNumber<T>::operator=(const RealNumber& rn) {

	if (this->n != rn.n) {
		if (this->mas != nullptr) delete[] this->mas;
		this->n = rn.n;
		this->mas = new T[this->n];
	}
	for (int i = 0; i < rn.n; i++) {
		this->mas[i] = rn.mas[i];
	}
	return *this;
}

/**
 * @brief Перевантаження бінарного оператору +
 * @param rn Об'єкт правого аргументу
 * @return Повернення тимчасового об'єкту
*/
template <class T>
RealNumber<T> RealNumber<T>::operator+(const RealNumber<T>& rn) {

	if (this->n > rn.n) {
		RealNumber<T> tmp(*this);
		for (int i = 0; i < rn.n; i++) {
			tmp.mas[i] += rn.mas[i];
		}
		return tmp;
	}
	else if (this->n < rn.n) {
		RealNumber<T> tmp(rn);
		for (int i = 0; i < this->n; i++) {
			tmp.mas[i] += this->mas[i];
		}
		return tmp;
	}
	else {
		RealNumber<T> tmp(this->n);
		for (int i = 0; i < tmp.n; i++) {
			tmp.mas[i] = this->mas[i] + rn.mas[i];
		}
		return tmp;
	}
}

/**
 * @brief Перевантаження бінарного оператору -
 * @param rn Об'єкт правого аргументу
 * @return Повернення тимчасового об'єкту
*/
template <class T>
RealNumber<T> RealNumber<T>::operator-(const RealNumber& rn) {

	if (this->n > rn.n) {
		RealNumber<T> tmp(*this);
		for (int i = 0; i < rn.n; i++) {
			tmp.mas[i] -= rn.mas[i];
		}
		return tmp;
	}
	else if (this->n < rn.n) {
		RealNumber<T> tmp(rn);
		for (int i = 0; i < this->n; i++) {
			tmp.mas[i] = this->mas[i] - tmp.mas[i];
		}
		for (int j = this->n; j < rn.n; j++) {
			tmp.mas[j] = 0 - tmp.mas[j];
		}
		return tmp;
	}
	else {
		RealNumber<T> tmp(this->n);
		for (int i = 0; i < tmp.n; i++) {
			tmp.mas[i] = this->mas[i] - rn.mas[i];
		}
		return tmp;
	}
}

/**
 * @brief Перевантаження бінарного оператору *
 * @param rn Об'єкт правого аргументу
 * @return Результату скалярного множення двох об'єктів
*/
template <class T>
double RealNumber<T>::operator*(const RealNumber& rn) {

	double scalar_product = 0.0;
	if (this->n > rn.n) {
		for (int i = 0; i < rn.n; i++) {
			scalar_product += this->mas[i] * rn.mas[i];
		}
	}
	else if (this->n < rn.n) {
		for (int i = 0; i < this->n; i++) {
			scalar_product += this->mas[i] * rn.mas[i];
		}
	}
	else {
		for (int i = 0; i < this->n; i++) {
			scalar_product += this->mas[i] * rn.mas[i];
		}
	}

	return scalar_product;
}

/**
 * @brief Перевантаження оператору =
 * @param index Елемент для отримання за індексом
 * @return Значення елементу за індексом
*/
template <class T>
double RealNumber<T>::operator[](const int& index) {

	if (index < 0 || index >= this->n) {
		cerr << "Current index don't find !" << endl;
		cout << "Return the element of maximum masive index [" << this->n - 1 << "] = ";
		return this->mas[this->n - 1];
	}
	else return this->mas[index];
}

/**
 * @brief Перевантаження оператору <<
 * @param notused Не використовується
 * @return Повернення поточного об'єкту
*/
template <class T>
RealNumber<T> RealNumber<T>::operator<<(int notused) {

	if (this->mas == nullptr) return *this;
	T tmp = this->mas[0];
	for (int i = 0; i < this->n - 1; i++) {
		this->mas[i] = this->mas[i + 1];
	}
	this->mas[this->n - 1] = tmp;

	return *this;
}
/**
 * @brief Дружня функція, яка перевантажує оператор >>
 * @param rn Об'єкт лівого аргументу
 * @param notused Не використовується
 * @return Повернення об'єкту
*/
template <class U>
RealNumber<U> operator>>(RealNumber<U>& rn, int notused) {

	if (rn.mas == nullptr) return rn;
	U tmp = rn.mas[rn.n - 1];
	for (int i = rn.n - 1; i > 0; i--) {
		rn.mas[i] = rn.mas[i - 1];
	}
	rn.mas[0] = tmp;

	return rn;
}

/**
 * @brief Функція, яка перевіряє правильність введення даних користувачем
 * @param x Данні для перевірки
*/
template <class T> 
void CheckData(T& x) {

	cin.ignore(666, '\n');
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(666, '\n');
		    cerr << "You enter wrong data! Please enter correct int data: \n";
			cin >> x;
			cin.ignore(666, '\n');
		}
		else break;
	}
}

int main() {

	srand(static_cast<unsigned int>(time(nullptr)));
	int work = 1;

	RealNumber<int> rn1(2);
	RealNumber<float> rn2(5), rn6(2);
	RealNumber<bool> rn3(5), rn4(7), rn5;

	while (work != 0) {
		cout << "rn1: "; rn1.Show();
		cout << "rn2: "; rn2.Show();
		cout << "rn3: "; rn3.Show();
		cout << "rn4: "; rn4.Show();
		cout << "rn5: "; rn5.Show();
		cout << setw(80) << setfill('-') << " " << setfill(' ') << endl;
		cout << setw(20) << left << "rn2<<: "; rn2 << 1; rn2.Show();
		cout << setw(20) << left << "rn2>>: "; rn2 >> 1; rn2.Show();
		cout << setw(20) << left << "rn1 + rn1: "; (rn1 + rn1).Show(); 
		cout << setw(20) << left << "rn5 = rn4 - rn5: "; rn5 = rn4 - rn3; rn5.Show();
		cout << setw(20) << left << "Scalar product (rn2 * rn6): " << rn2 * rn6 << endl;
		cout << setw(20) << left << "Get 4 element of rn1[4]: " << rn1[4] << endl;

		if (work != 0) {
			cout << "\nRetry? 1 - yes / 0 - no" << endl;
			cin >> work;
			CheckData(work);
			rn1.Generate();
			rn2.Generate();
			rn3.Generate();
			rn4.Generate();
			rn6.Generate();
		}cout << endl;
	}

	return 0;
}
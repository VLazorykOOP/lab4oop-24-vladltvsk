/*#include <iostream>

class VectorInt {
private:
    int* data;
    int size;
    int codeError;
    static int count; // Змінна для підрахунку числа об'єктів даного типу

public:
    // Конструктори

    VectorInt() : data(new int[1]), size(1), codeError(0) {
        count++; // Збільшуємо лічильник об'єктів
        data[0] = 0;
    }

    VectorInt(int n) : size(n), codeError(0) {
        if (n <= 0) {
            codeError = 1; // Код помилки для невірного розміру вектора
            return;
        }
        data = new int[n];
        count++; // Збільшуємо лічильник об'єктів
        for (int i = 0; i < n; ++i) {
            data[i] = 0;
        }
    }

    VectorInt(int n, int value) : size(n), codeError(0) {
        if (n <= 0) {
            codeError = 1; // Код помилки для невірного розміру вектора
            return;
        }
        data = new int[n];
        count++; // Збільшуємо лічильник об'єктів
        for (int i = 0; i < n; ++i) {
            data[i] = value;
        }
    }

    // Операції
 // Передсуфіксний інкремент (++v1)
    VectorInt& operator++() {
        for (int i = 0; i < size; ++i) {
            ++data[i];
        }
        return *this;
    }

    // Постфіксний інкремент (v1++)
    VectorInt operator++(int) {
        VectorInt temp(*this);
        ++(*this);
        return temp;
    }

    // Логічне заперечення (!v1)
    bool operator!() const {
        return size == 0;
    }

    // Побітове заперечення (~v1)
    VectorInt operator~() const {
        VectorInt result(*this);
        for (int i = 0; i < size; ++i) {
            result.data[i] = ~result.data[i];
        }
        return result;
    }

    // Арифметичне заперечення (-v2)
    VectorInt operator-() const {
        VectorInt result(*this);
        for (int i = 0; i < size; ++i) {
            result.data[i] = -result.data[i];
        }
        return result;
    }

    // Присвоєння (=)
    VectorInt& operator=(const VectorInt& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            codeError = other.codeError;
            data = new int[size];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Додавання векторів (+=)
    VectorInt& operator+=(const VectorInt& other) {
        if (size != other.size) {
            codeError = 2; // Код помилки для різних розмірів векторів
            return *this;
        }
        for (int i = 0; i < size; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    // Віднімання векторів (-=)
    VectorInt& operator-=(const VectorInt& other) {
        if (size != other.size) {
            codeError = 2; // Код помилки для різних розмірів векторів
            return *this;
        }
        for (int i = 0; i < size; ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    // Множення вектора на скаляр (*=)
    VectorInt& operator*=(int scalar) {
        for (int i = 0; i < size; ++i) {
            data[i] *= scalar;
        }
        return *this;
    }

    // Ділення вектора на скаляр (/=)
    VectorInt& operator/=(int scalar) {
        if (scalar == 0) {
            codeError = 3; // Код помилки для ділення на нуль
            return *this;
        }
        for (int i = 0; i < size; ++i) {
            data[i] /= scalar;
        }
        return *this;
    }

    // Остача від ділення вектора на скаляр (%=)
    VectorInt& operator%=(int scalar) {
        if (scalar == 0) {
            codeError = 3; // Код помилки для ділення на нуль
            return *this;
        }
        for (int i = 0; i < size; ++i) {
            data[i] %= scalar;
        }
        return *this;
    }

    // Побітове додавання векторів (|=)
    VectorInt& operator|=(const VectorInt& other) {
        if (size != other.size) {
            codeError = 2; // Код помилки для різних розмірів векторів
            return *this;
        }
        for (int i = 0; i < size; ++i) {
            data[i] |= other.data[i];
        }
        return *this;
    }

    // Побітове додавання за модулем 2 векторів (^=)
    VectorInt& operator^=(const VectorInt& other) {
        if (size != other.size) {
            codeError = 2; // Код помилки для різних розмірів векторів
            return *this;
        }
        for (int i = 0; i < size; ++i) {
            data[i] ^= other.data[i];
        }
        return *this;
    }

    // Побітове по-елементне множення векторів (&=)
    VectorInt& operator&=(const VectorInt& other) {
        if (size != other.size) {
            codeError = 2; // Код помилки для різних розмірів векторів
            return *this;
        }
        for (int i = 0; i < size; ++i) {
            data[i] &= other.data[i];
        }
        return *this;
    }

    // Дружня функція для виведення вектора у потік
    friend std::ostream& operator<<(std::ostream& out, const VectorInt& vec) {
        out << "[";
        for (int i = 0; i < vec.size; ++i) {
            out << vec.data[i];
            if (i != vec.size - 1) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }

    // Метод для отримання елементу вектора за індексом
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 4; // Код помилки для невірного індексу
            return data[size - 1]; // Повертаємо останній елемент у випадку помилки
        }
        return data[index];
    }

    // Метод для отримання коду помилки
    int getCodeError() const {
        return codeError;
    }

    // Деструктор

    ~VectorInt() {
        delete[] data;
        count--; // Зменшуємо лічильник об'єктів
    }

    // Метод для отримання кількості об'єктів даного типу
    static int getCount() {
        return count;
    }
};

// Ініціалізація статичної змінної класу
int VectorInt::count = 0;

int main() {
     VectorInt v1(5, 1); // Вектор {1, 1, 1, 1, 1}
    VectorInt v2(5, 2); // Вектор {2, 2, 2, 2, 2}

    // Перший вираз
    VectorInt v3 = v1 += v2;    // Операція додавання
    v3 *= 3;                   // Операція множення на скаляр
    v3 -= v1;                   // Операція віднімання
    v3 /= 2;                   // Операція ділення на скаляр
    VectorInt v4 = v3 |= v2;    // Операція побітового додавання

    std::cout << "Expression 1 result: " << v4 << std::endl;

    // Другий вираз
    VectorInt v5 = v1 *=2;    // Операція множення
    v5 += v2;                   // Операція додавання
    v5 ^= 2;                    // Операція побітового додавання за модулем 2
    v5 %= 3;                    // Операція остачі від ділення на скаляр
    v5++;                      // Операція постфіксного інкременту

    std::cout << "Expression 2 result: " << v5 << std::endl;

    return 0;
}*/


#include <iostream>
#include <unordered_map>
#include <string>

class Inventory {
private:
    std::unordered_map<std::string, int> inventoryMap;
    int codeError; // Змінна для коду помилки

public:
    // Конструктор
    Inventory() : codeError(0) {}

    // Функція створення набору асоціативних сутностей
    void createInventory(const std::string names[], const int numbers[], int size) {
        for (int i = 0; i < size; ++i) {
            inventoryMap[names[i]] = numbers[i];
        }
    }

    // Перевантаження оператора індексації []
    int& operator[](const std::string& itemName) {
        if (inventoryMap.find(itemName) == inventoryMap.end()) {
            codeError = 1; // Код помилки для відсутності елемента в асоціативному масиві
            return codeError;
        }
        return inventoryMap[itemName];
    }

    // Перевантаження оператора виклику функції ()
    int& operator()(const std::string& itemName) {
        return inventoryMap[itemName];
    }

    // Функція для отримання коду помилки
    int getCodeError() const {
        return codeError;
    }

    // Перевантаження дружньої операції виведення
    friend std::ostream& operator<<(std::ostream& out, const Inventory& inv) {
        for (const auto& item : inv.inventoryMap) {
            out << "Item: " << item.first << ", Inventory Number: " << item.second << std::endl;
        }
        return out;
    }

    // Перевантаження дружньої операції введення
    friend std::istream& operator>>(std::istream& in, Inventory& inv) {
        std::string name;
        int number;
        std::cout << "Enter item name and inventory number (separated by space, type 'exit' to stop):" << std::endl;
        while (true) {
            in >> name;
            if (name == "exit") {
                break;
            }
            in >> number;
            inv.inventoryMap[name] = number;
        }
        return in;
    }
};

int main() {
    // Приклад використання
    std::string names[] = {"Chair", "Desk", "Bookshelf"};
    int numbers[] = {101, 102, 103};
    Inventory inventory;
    inventory.createInventory(names, numbers, 3);

    std::cout << "Initial Inventory:" << std::endl;
    std::cout << inventory << std::endl;

    // Доступ до елементів за допомогою оператора індексації []
    std::cout << "Inventory number of Chair: " << inventory["Chair"] << std::endl;
    std::cout << "Inventory number of Bookshelf: " << inventory["Bookshelf"] << std::endl; 

    // Доступ до елементів за допомогою оператора виклику функції ()
    std::cout << "Inventory number of Desk: " << inventory("Desk") << std::endl;

    return 0;
}

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>
#include <fstream>

// Структура для хранения информации о книге
struct Book {
    std::string author; 
    std::string title;  
    int year;           
    int copies;         
};

// Функция для сравнения книг по году издания
bool compareByYear(const Book& a, const Book& b) {
    return a.year < b.year;
}

// Класс для управления библиотекой книг
class Library {
private:
    std::multimap<std::string, Book> books;

public:
    // Метод для добавления книги в библиотеку
    void addBook(const Book& book) {
        books.insert({ book.author, book });
    }

    // Метод для удаления книги из библиотеки
    void removeBook(const std::string& author, const std::string& title) {
        // Поиск диапазона книг одного автора
        auto range = books.equal_range(author);
        // Поиск нужной книги по названию
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second.title == title) {
                books.erase(it);
                break;
            }
        }
    }

    // Метод для вывода всех книг, отсортированных по авторам
    void printBooksByAuthor() const {
        for (const auto& pair : books) {
            const Book& book = pair.second;
            std::cout << "Автор: " << book.author << ", Название: " << book.title
                << ", Год издания: " << book.year << ", Количество: " << book.copies << '\n';
        }
    }

    // Метод для вывода всех книг, отсортированных по годам
    void printBooksByYear() const {
        std::vector<Book> sortedBooks;
        for (const auto& pair : books) {
            sortedBooks.push_back(pair.second);
        }
        std::sort(sortedBooks.begin(), sortedBooks.end(), compareByYear);
        for (const auto& book : sortedBooks) {
            std::cout << "Автор: " << book.author << ", Название: " << book.title
                << ", Год издания: " << book.year << ", Количество: " << book.copies << '\n';
        }
    }

    // Метод для сохранения всех книг в файл, отсортированных по авторам
    void saveBooksByAuthorToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& pair : books) {
                const Book& book = pair.second;
                outFile << "Автор: " << book.author << ", Название: " << book.title
                    << ", Год издания: " << book.year << ", Количество: " << book.copies << '\n';
            }
            outFile.close();
        }
        else {
            std::cerr << "Невозможно открыть файл для записи\n";
        }
    }

    // Метод для сохранения всех книг в файл, отсортированных по годам
    void saveBooksByYearToFile(const std::string& filename) const {
        std::vector<Book> sortedBooks;
        for (const auto& pair : books) {
            sortedBooks.push_back(pair.second);
        }
        std::sort(sortedBooks.begin(), sortedBooks.end(), compareByYear);

        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& book : sortedBooks) {
                outFile << "Автор: " << book.author << ", Название: " << book.title
                    << ", Год издания: " << book.year << ", Количество: " << book.copies << '\n';
            }
            outFile.close();
        }
        else {
            std::cerr << "Невозможно открыть файл для записи\n";
        }
    }
};

// Функция для вывода меню на экран
void printMenu() {
    std::cout << "Меню:\n";
    std::cout << "1. Добавить книгу\n";
    std::cout << "2. Удалить книгу\n";
    std::cout << "3. Показать все книги (по авторам)\n";
    std::cout << "4. Показать все книги (по годам)\n";
    std::cout << "5. Сохранить все книги (по авторам) в файл\n";
    std::cout << "6. Сохранить все книги (по годам) в файл\n";
    std::cout << "7. Выйти\n";
    std::cout << "Выберите опцию: ";
}

int main() {
    // Установка кодировки консоли на Windows для корректного отображения русских символов
    (system("chcp 1251"));
    setlocale(LC_ALL, "RU");

    Library library; // Создание объекта библиотеки
    int choice;      // Переменная для хранения выбора пользователя

    do {
        printMenu(); 
        std::cin >> choice; // Считывание выбора пользователя
        std::cin.ignore(); // Игнорировать оставшийся символ новой строки

        if (choice == 1) {
            // Добавление новой книги
            Book book;
            std::cout << "Введите автора: ";
            std::getline(std::cin, book.author);
            std::cout << "Введите название: ";
            std::getline(std::cin, book.title);
            std::cout << "Введите год издания: ";
            std::cin >> book.year;
            std::cout << "Введите количество экземпляров: ";
            std::cin >> book.copies;
            std::cin.ignore(); // Игнорировать оставшийся символ новой строки
            library.addBook(book);
        }
        else if (choice == 2) {
            // Удаление книги
            std::string author, title;
            std::cout << "Введите автора: ";
            std::getline(std::cin, author);
            std::cout << "Введите название: ";
            std::getline(std::cin, title);
            library.removeBook(author, title);
        }
        else if (choice == 3) {
            // Показать все книги (по авторам)
            library.printBooksByAuthor();
        }
        else if (choice == 4) {
            // Показать все книги (по годам)
            library.printBooksByYear();
        }
        else if (choice == 5) {
            // Сохранить все книги (по авторам) в файл
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::getline(std::cin, filename);
            library.saveBooksByAuthorToFile(filename);
        }
        else if (choice == 6) {
            // Сохранить все книги (по годам) в файл
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::getline(std::cin, filename);
            library.saveBooksByYearToFile(filename);
        }
    } while (choice != 7); // Цикл продолжается, пока пользователь не выберет выход (опция 7)

    return 0;
}

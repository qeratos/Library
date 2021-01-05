//
// Created by younDev on 05.12.2020.
//
#include "database.h"
#include "logic.h"
#include <Windows.h>
using namespace std;



void print_available_books(const vector<book>& books) {
    vector<book> available_books;
    for (book b : books) {
        if (b.count > 0) {
            available_books.push_back(b);
        }
    }
    cout << "Список доступных книг: " << endl;
    if (available_books.empty()) {
        cout << "Ничего не найдено" << endl;
    }
    else {
        print_books(available_books);
    }
}



void return_book(vector<book>& books, vector<user>& users) {
    int user_id;
    while (true) {
        cout << "Введите id читателя: " << endl;
        string s;
        cin >> s;
        if (!is_integer(s)) {
            cout << "Введите корректное число!" << endl;
            continue;
        }
        user_id = stoi(s);
        if (user_id <= 0 || user_id > users.size()) {
            cout << "Введите корректное число!" << endl;
            continue;
        }
        break;
    }

    user_id--;
    if (users[user_id].taked_books.empty()) {
        cout << "У читателя нет книги" << endl;
    }
    else {
        cout << "Выберите id книги:" << endl;
        for (int id : users[user_id].taked_books) {
            cout << id << " ";
        }
        cout << endl;
        int book_id;
        while (true) {
            cout << "Введите id книги: " << endl;
            string s;
            cin >> s;
            if (!is_integer(s)) {
                cout << "Введите корректное число!" << endl;
                continue;
            }
            book_id = stoi(s);
            auto it = find(users[user_id].taked_books.begin(), users[user_id].taked_books.end(), book_id);
            if (it == users[user_id].taked_books.end()) {
                cout << "Введите корректное число!" << endl;
                continue;
            }
            users[user_id].taked_books.erase(it);
            books[book_id - 1].count++;
            break;
        }
    }
}

void loadusers(const string& filename, vector<user>& users) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        return;
    }

    while (!fin.eof()) {
        string temp;
        user new_user;
        fin >> temp;
        if (!fin.eof()) break;
        fin >> new_user.id;
        fin >> temp >> new_user.name;
        fin >> temp >> new_user.last_name;
        fin >> temp >> new_user.tel_number;
        int count;
        fin >> temp >> count;
        fin >> temp;
        for (int i = 0; i < count; i++) {
            int id;
            fin >> id;
            new_user.taked_books.push_back(id);
        }
        users.push_back(new_user);
    }

    fin.close();
}

void display() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 6);
    cout << "-------------------------------------\n"
         << "||          Library v1.0           ||\n"
         << "-------------------------------------\n";
    SetConsoleTextAttribute(console, 7);
    cout << "|1|   Вывести все доступные книги  ||\n"
         << "-------------------------------------\n"
         << "|2|     Вывести всех читателей     ||\n"
         << "-------------------------------------\n"
         << "|3|          Поиск книги           ||\n"
         << "-------------------------------------\n"
         << "|4|         Поиск читателя         ||\n"
         << "-------------------------------------\n"
         << "|5|  Добавить книгу в библиотеку   ||\n"
         << "-------------------------------------\n"
         << "|6| Добавить читателя в библиотеку ||\n"
         << "-------------------------------------\n"
         << "|7|     Выдать книгу читателю      ||\n"
         << "-------------------------------------\n"
         << "|8|    Вернуть книгу в библиотеку  ||\n"
         << "-------------------------------------\n"
         << "|9| просмотр взятых книг читателем ||\n"
         << "-------------------------------------\n"
         << "||     Для выхода выберите - 10    ||\n"
         << "-------------------------------------" << endl;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    vector<user> users;
    vector<book> books;
    string usersfilename = "users.txt";
    string booksfilename = "books.txt";
    loadusers(usersfilename, users);
    loadbooks(booksfilename, books);
    while (true) {
        display();
        int type;
        while (true) {
            cout << "Выберите пункт меню: ";
            string s;
            cin >> s;
            if (!is_integer(s)) {
                cout << "Введите корректное число!" << endl;
                continue;
            }
            type = stoi(s);
            if (type <= 0 || type > 10) {
                cout << "Введите корректное число!" << endl;
                continue;
            }
            break;
        }

        switch (type) {
            case 1:
                print_available_books(books);
                break;
            case 2:
                print_users(users);
                break;
            case 3:
                find_book(books);
                break;
            case 4:
                find_user(users);
                break;
            case 5:
                add_book(books);
                break;
            case 6:
                add_user(users);
                break;
            case 7:
                give_book(books, users);
                break;
            case 8:
                return_book(books, users);
                break;
            case 9:
                taked_books(books, users);
                break;
            case 10:
                saveusers(usersfilename, users);
                savebooks(booksfilename, books);
                exit(0);
        }

        cout << "Нажмите любую кнопку..." << endl;
        char c = getchar();
        if (c == '\n') c = getchar();
        system("cls");
    }
}
//
// Created by younDev on 05.12.2020.
//
#pragma once
#ifndef LIBRARY_LOGIC_H
#define LIBRARY_LOGIC_H


#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cassert>
#include <string>
#include <clocale>

using namespace std;

void print_books(const vector<book>& books) {
    for (book b : books) {
        cout << b << endl;
    }
}

void print_users(const vector<user>& users) {
    for (user u : users) {
        cout << u << endl;
    }
}

void find_book(const vector<book>& books, const string& title) {
    vector<book> finded_books;
    for (book b : books) {
        if (b.title.find(title) != string::npos) {
            finded_books.push_back(b);
        }
    }
    cout << "Найденные книги:" << endl;
    if (finded_books.empty()) {
        cout << "Ничего не найдено" << endl;
    }
    else {
        print_books(finded_books);
    }
}


void find_book(const vector<book>& books) {
    string title;
    cout << "Введите название: ";
    cin >> title;
    find_book(books, title);
}


void find_user(const vector<user>& users, const string& name) {
    vector<user> finded_users;
    for (user u : users) {
        if (u.name.find(name) != string::npos) {
            finded_users.push_back(u);
        }
    }
    cout << "Найденные читатели:" << endl;
    if (finded_users.empty()) {
        cout << "Ничего не найдено" << endl;
    }
    else {
        print_users(finded_users);
    }
}


void find_user(const vector<user>& users) {
    string name;
    cout << "Введите имя: ";
    cin >> name;
    find_user(users, name);
}


void add_book(vector<book>& books) {
    book new_book;
    cin >> new_book;
    books.push_back(new_book);
    books.back().id = books.size();
}


void add_user(vector<user>& users) {
    user new_user;
    cin >> new_user;
    users.push_back(new_user);
    users.back().id = users.size();
}

void give_book(vector<book>& books, vector<user>& users) {
    int book_id;
    while (true) {
        cout << "Введите номер книги: " << endl;
        string s;
        cin >> s;
        if (!is_integer(s)) {
            cout << "Введите корректное число!" << endl;
            continue;
        }
        book_id = stoi(s);
        if (book_id <= 0 || book_id > books.size()) {
            cout << "Введите корректное число!" << endl;
            continue;
        }
        if (books[book_id - 1].count == 0) {
            cout << "Этой книги в библиотеке больше не осталось" << endl;
            return;
        }
        break;
    }

    int user_id;
    while (true) {
        cout << "Введите номер читателя: " << endl;
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
    auto it = find(users[user_id].taked_books.begin(), users[user_id].taked_books.end(), book_id);
    if (it == users[user_id].taked_books.end()) {
        users[user_id].taked_books.push_back(book_id);
        books[book_id - 1].count--;
    }
    else {
        cout << "У читателя уже есть эта книга" << endl;
    }
}

void taked_books(vector<book>& books, vector<user>& users) {
    int user_id;
    while (true) {
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

    vector<book> taked;
    for (int id : users[user_id - 1].taked_books) {
        taked.push_back(books[id - 1]);
    }
    cout << "Взятые книги: " << endl;
    print_books(taked);
}

#endif //LIBRARY_LOGIC_H

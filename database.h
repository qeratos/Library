//
// Created by younDev on 05.12.2020.
//

#ifndef LIBRARY_DATABASE_H
#define LIBRARY_DATABASE_H


#pragma once
#ifndef database
#define database

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cassert>
#include <string>
#include <clocale>

using namespace std;

bool is_integer(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

struct book {

    int id;
    string title;
    string author;
    int year;
    int count;

    book() {}

    book(const string& title, const string& author, const int& year, const int& count) :
            title(title), author(author), year(year), count(count) {}

    book(const book& b) : id(b.id), title(b.title), author(b.author), year(b.year), count(b.count) {}

    friend istream& operator >> (istream& in, book& b) {
        cout << "Введите название: ";
        char c;
        do {
            c = getchar();
        } while (c == ' ' || c == '\n');
        while (true) {
            b.title += c;
            c = getchar();
            if (c == '\n') break;
        }
        cout << "Введите автора: ";
        do {
            c = getchar();
        } while (c == ' ' || c == '\n');
        while (true) {
            b.author += c;
            c = getchar();
            if (c == '\n') break;
        }
        while (true) {
            cout << "Введите год выпуска: ";
            string s;
            in >> s;
            if (!is_integer(s)) {
                cout << "Введите корректное число!" << endl;
                continue;
            }
            b.year = stoi(s);
            break;
        }

        while (true) {
            cout << "Введите количество копий книги в библиотеке: ";
            string s;
            in >> s;
            if (!is_integer(s)) {
                cout << "Введите корректное число!" << endl;
                continue;
            }
            b.count = stoi(s);
            break;
        }
        return in;
    }


    friend string to_string(const book& b) {
        string text;
        text += "ID: " + to_string(b.id) + "\n";
        text += "Title: " + b.title + "\n";
        text += "Author: " + b.author + "\n";
        text += "Year: " + to_string(b.year) + "\n";
        text += "Count: " + to_string(b.count) + "\n";
        return text;
    }

    friend ostream& operator << (ostream& os, const book& b) {
        os << to_string(b);
        return os;
    }

};

struct user {

    int id;
    string name;
    string last_name;
    string tel_number;
    vector<int> taked_books;

    user() {}

    user(const string& name, const string& last_name, const string& tel_number, const vector<int>& taked_books = vector<int>{}) :
            name(name), last_name(last_name), tel_number(tel_number), taked_books(taked_books) {}

    user(const user& u) : id(u.id), name(u.name), last_name(u.last_name), tel_number(u.tel_number), taked_books(u.taked_books) {}

    friend istream& operator >> (istream& in, user& u) {
        cout << "Введите имя: ";
        char c;
        do {
            c = getchar();
        } while (c == ' ' || c == '\n');

        while (true) {
            u.name += c;
            c = getchar();
            if (c == '\n') break;
        }
        cout << "Введите фамилию: ";
        do {
            c = getchar();
        } while (c == ' ' || c == '\n');
        while (true) {
            u.last_name += c;
            c = getchar();
            if (c == '\n') break;
        }
        cout << "Введите номер телефона: ";
        in >> u.tel_number;
        return in;
    }

    friend string to_string(const user& u) {
        string text;
        text += "ID: " + to_string(u.id) + "\n";
        text += "Name: " + u.name + "\n";
        text += "LastName: " + u.last_name + "\n";
        text += "TelNumber: " + u.tel_number + "\n";
        text += "TakedBooksCount: " + to_string((int)u.taked_books.size()) + "\n";
        text += "TakedBooks: ";
        for (int id : u.taked_books) {
            text += to_string(id) + " ";
        }
        return text;
    }

    friend ostream& operator << (ostream& os, const user& u) {
        os << to_string(u);
        return os;
    }

};



void saveusers(const string& filename, vector<user>& users) {
    ofstream fout(filename);
    for (user u : users) {
        fout << u << endl;
    }
}


void savebooks(const string& filename, vector<book>& books) {
    ofstream fout(filename);
    for (book b : books) {
        fout << b << endl;
    }
}

void loadbooks(const string& filename, vector<book>& books) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        return;
    }

    while (!fin.eof()) {
        string temp;
        book new_book;
        fin >> temp;
        if (fin.eof()) break;
        fin >> new_book.id;
        fin >> temp >> new_book.title;
        fin >> temp >> new_book.author;
        fin >> temp >> new_book.year;
        fin >> temp >> new_book.count;
        books.push_back(new_book);
    }

    fin.close();
}


#endif // database



#endif //LIBRARY_DATABASE_H

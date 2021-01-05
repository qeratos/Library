//
// Created by younDev on 05.12.2020.
//

#ifndef LIBRARY_LOGIC_H
#define LIBRARY_LOGIC_H

#pragma once
#ifndef logic
#define logic

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
    cout << "Íàéäåííûå êíèãè:" << endl;
    if (finded_books.empty()) {
        cout << "Íè÷åãî íå íàéäåíî" << endl;
    }
    else {
        print_books(finded_books);
    }
}


void find_book(const vector<book>& books) {
    string title;
    cout << "Ââåäèòå íàçâàíèå: ";
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
    cout << "Íàéäåííûå ÷èòàòåëè:" << endl;
    if (finded_users.empty()) {
        cout << "Íè÷åãî íå íàéäåíî" << endl;
    }
    else {
        print_users(finded_users);
    }
}


void find_user(const vector<user>& users) {
    string name;
    cout << "Ââåäèòå èìÿ: ";
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
        cout << "Ââåäèòå id êíèãè: " << endl;
        string s;
        cin >> s;
        if (!is_integer(s)) {
            cout << "Ââåäèòå êîððåêòíîå ÷èñëî!" << endl;
            continue;
        }
        book_id = stoi(s);
        if (book_id <= 0 || book_id > books.size()) {
            cout << "Ââåäèòå êîððåêòíîå ÷èñëî!" << endl;
            continue;
        }
        if (books[book_id - 1].count == 0) {
            cout << "Ýòîé êíèãè â áèáëèîòåêå áîëüøå íå îñòàëàñü" << endl;
            return;
        }
        break;
    }

    int user_id;
    while (true) {
        cout << "Ââåäèòå id ÷èòàòåëÿ: " << endl;
        string s;
        cin >> s;
        if (!is_integer(s)) {
            cout << "Ââåäèòå êîððåêòíîå ÷èñëî!" << endl;
            continue;
        }
        user_id = stoi(s);
        if (user_id <= 0 || user_id > users.size()) {
            cout << "Ââåäèòå êîððåêòíîå ÷èñëî!" << endl;
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
        cout << "Ó ÷èòàòåëÿ óæå åñòü ýòà êíèãà" << endl;
    }
}

void taked_books(vector<book>& books, vector<user>& users) {
    int user_id;
    while (true) {
        string s;
        cin >> s;
        if (!is_integer(s)) {
            cout << "Ââåäèòå êîððåêòíîå ÷èñëî!" << endl;
            continue;
        }
        user_id = stoi(s);
        if (user_id <= 0 || user_id > users.size()) {
            cout << "Ââåäèòå êîððåêòíîå ÷èñëî!" << endl;
            continue;
        }
        break;
    }

    vector<book> taked;
    for (int id : users[user_id - 1].taked_books) {
        taked.push_back(books[id - 1]);
    }
    cout << "Âçÿòûå êíèãè: " << endl;
    print_books(taked);
}


#endif

#endif //LIBRARY_LOGIC_H

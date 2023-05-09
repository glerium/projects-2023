#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <cctype>
#include <algorithm>
#include <unistd.h>

#define DATABASE "data.csv"
namespace fs = std::filesystem;

class Person {
public:
    int id;
    std::string name;
    std::string phone;
    char gender;    // M: male, F: female
    std::string address;
    int age;
    bool operator<(const Person& rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Person& d);
int read_data(fs::path file, std::vector<Person>& ret, bool& error);
int write_data(fs::path file, const std::vector<Person>& data, bool& error);

void input(std::string& ret, const std::string& label="", bool newline=false);
void input(int& ret, const std::string& label="", bool newline=false);
void input(char& ret, const std::string& label="", bool newline=false);
void input(Person& ret, const std::string& label="", bool newline=false);
bool input_confirm(const std::string& text);

void show_menu();

#endif
#ifndef CONTACT_H
#define CONTACT_H

// 导入项目中使用的头文件
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

// 条目数据定义
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

int read_data(fs::path file, std::vector<Person>& ret, bool& error);            // 从文件中读取数据至内存
int write_data(fs::path file, const std::vector<Person>& data, bool& error);    // 将内存中的数据保存至文件，覆盖原有内容

void input(std::string& ret, const std::string& label="", bool newline=false);  // 从标准输入流读取一个字符串
void input(int& ret, const std::string& label="", bool newline=false);          // 从标准输入流读取一个整数
void input(char& ret, const std::string& label="", bool newline=false);         // 从标准输入流读取一个char
void input(Person& ret, const std::string& label="", bool newline=false);       // 从标准输入流读取一个Person对象
bool input_confirm(const std::string& text);                        // 用于执行重要操作前的确认，要求用户输入指定字符串以继续
std::ostream& operator<<(std::ostream& os, const Person& d);        // 将Person对象输出至ostream

void show_menu();       // 显示操作表单

#endif
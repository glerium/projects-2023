#include "contact.h"

int read_data(fs::path file, std::vector<Person>& ret, bool& error) {
    std::ifstream ff(file);
    std::stringstream ss, ss2;
    int cnt = 0;
    error = false;
    try {
        while(!ff.eof()) {
            ss.clear();
            ss2.clear();
            Person tmp;
            std::string line;
            std::string s;
            std::getline(ff, line);
            if(line.size()==0) break;
            ss << line;
            
            std::getline(ss, s, ',');
            ss2 << s;
            ss2 >> tmp.id;
            if(ss.fail()) throw 1;

            std::getline(ss, tmp.name, ',');
            std::getline(ss, tmp.phone, ',');

            std::getline(ss, s, ',');
            if(std::toupper(s[0])!='F'&&std::toupper(s[0])!='M') throw 1;
            else tmp.gender = s[0];
            if(ss.fail()) throw 1;

            std::getline(ss, tmp.address, ',');
            ss >> tmp.age;
            if(ss.fail()) throw 1;

            ret.push_back(tmp);
            cnt++;
        }
    } catch(...) {
        error = true;
    }
    return cnt;
}

int write_data(fs::path file, const std::vector<Person>& data, bool& error) {
    error = false;
    std::ofstream ff(file, std::ios::out);
    std::stringstream ss;
    std::string s;
    int cnt = 0;
    try {
        for(auto i : data) {
            ss << i.id << ',' << i.name << ',' << i.phone << ',' << char(i.gender) << ',' << i.address << ',' << i.age << std::endl;
            getline(ss, s);
            ff << s << std::endl;
            cnt++;
        }
    } catch(...) {
        error = true;
    }
    return cnt;
}

bool isnum(const std::string& data) {
    if(data.size() >= 10) return false;
    for(auto i : data) if(!isdigit(i)) return false;
    return true;
}

void input(std::string& ret, const std::string& label, bool newline) {
    ret = "";
    std::cout << label;
    if(newline) std::cout << std::endl;
    while(!ret.size()) std::getline(std::cin, ret);
}

void input(int& ret, const std::string& label, bool newline) {
    std::cout << label;
    if(newline) std::cout << std::endl;
    std::string s;
    std::stringstream ss;
    while(!s.size()) std::getline(std::cin, s);
    while(!isnum(s)) {
        std::cout << "Invalid integer!" << std::endl;
        std::getline(std::cin, s);
    }
    ss << s;
    ss >> ret;
}

void input(char& ret, const std::string& label, bool newline) {
    std::cout << label;
    if(newline) std::cout << std::endl;
    std::string s;
    while(!s.size()) std::cin >> s;
    ret = s[0];
}

void input(Person& ret, const std::string& label, bool newline) {
    input(ret.name, "Name: ");
    input(ret.phone, "Phone number: ");
    input(ret.gender, "Gender(M/F): ");
    while (toupper(ret.gender)!='M' && toupper(ret.gender)!='F')
        input(ret.gender, "Invalid gender!", true);
    input(ret.address, "Address: ");
    input(ret.age, "Age: ");
}

bool input_confirm(const std::string& text) {
    std::cout << "Are you sure? Enter \"" << text << "\" to continue." << std::endl;
    std::string str;
    std::getline(std::cin, str);
    if(str == text) return true;
    else return false;
}
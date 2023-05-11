#include "contact.h"

/*  read_data：从指定文件中读取所有数据进入Person对象
    输入参数：fs::path file：要读取的文件名
             vector<Person>& ret：存储数据的vector对象
             bool& error：用于返回值，存放是否在读取过程中发生错误
    返回值：一个int，表示实际读取到内存的数据条数
*/
int read_data(fs::path file, std::vector<Person>& ret, bool& error) {
    std::ifstream ff(file);
    std::stringstream ss;       // 处理文件中的一整行
    std::stringstream ss2;      // 用于处理单独的int
    int cnt = 0;                // 已读入的数据计数
    error = false;              // 初始化时认为还没有发生错误
    try {
        while(!ff.eof()) {
            ss.clear();
            ss2.clear();

            Person tmp;         // 当前处理的一条Person数据
            std::string line;   // 文件中的一行
            std::string s;      // 处理int对象时使用的临时变量
            std::getline(ff, line);
            if(line.size()==0) break;
            ss << line;
            
            std::getline(ss, s, ',');
            ss2 << s;
            ss2 >> tmp.id;
            if(ss.fail()) throw 1;      // 如果对应位不是int则抛出错误

            std::getline(ss, tmp.name, ',');
            std::getline(ss, tmp.phone, ',');

            std::getline(ss, s, ',');
            if(std::toupper(s[0])!='F'&&std::toupper(s[0])!='M') throw 1;   // 性别位不是F或M则抛出错误
            else tmp.gender = s[0];
            if(ss.fail()) throw 1;

            std::getline(ss, tmp.address, ',');
            ss >> tmp.age;
            if(ss.fail()) throw 1;

            ret.push_back(tmp);
            cnt++;      // 更新数据计数
        }
    } catch(...) {
        error = true;
    }
    return cnt;
}

/*  write_data：将内存中的数据写入文件，覆盖原文件
    输入参数：fs::path file：文件路径
             const vector<Person>& data：要写入的数据
             bool& error：用于返回值，表示是否发生错误
    返回值：int，表示实际写入的数据条数

*/
int write_data(fs::path file, const std::vector<Person>& data, bool& error) {
    error = false;
    std::ofstream ff(file, std::ios::out);
    std::stringstream ss;
    std::string s;      // 用于转换数据类型
    int cnt = 0;        // 写入数据计数置零
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

/*  isnum：辅助函数，用于判断字符串中是否全为数字字符，且位数不大于10
    输入参数：const string& data：要判断的字符串
    返回值：bool，是否满足前述要求
*/
bool isnum(const std::string& data) {
    if(data.size() >= 10) return false;
    for(auto i : data) if(!isdigit(i)) return false;
    return true;
}

/*  input系列重载函数：向标准输出流显示一段文字，然后读取一个指定类型的对象
    TODO: 用template重写函数
    输入参数：ret：引用，用于装载用户的输入值
             const string& label：要向用户显示的文字，默认为空字符串，即不显示任何文字
             bool newline：显示文字后是否换行，默认为false
    返回值：无
*/
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
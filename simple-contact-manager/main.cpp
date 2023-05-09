#include "contact.h"
using namespace std;
int main(){
    fs::path p;
    p = fs::path(DATABASE);
    std::vector<Person> data;
    int choice = 0;
    int idx = 1;
    while(true) {
        show_menu();
        input(choice, "Choose one: ", false);
        bool err;
        char chr;
        int ret;
        int it;
        std::string str;
        Person tmp;
        vector<Person>::iterator x;
        while(choice < 0 || choice > 9) input(choice, "Invalid option! ", true);
        switch(choice) {
            case 1:
                input(chr, "Do you wish to save?(Y/N) ");
                if(toupper(chr) == 'Y') {
                    ret = write_data(p, data, err);
                    if(err) std::cerr << "Error occurred while writing " << p.filename() << "." << endl;
                    std::cout << "Wrote " << ret << " row" << (ret>1 ? "s." : ".") << std::endl;
                } else {
                    std::cout << "Abort." << std::endl;
                }
                break;

            case 2:
                input(chr, "Do you wish to load? This will clear all unsaved data!(Y/N) ");
                if(toupper(chr) == 'Y') {
                    data.clear();
                    if(fs::is_regular_file(p)) {
                        string s;
                        bool err;
                        ret = read_data(p, data, err);
                        if(err) std::cerr << "Error occurred while reading " << p.filename() << "." << endl;
                        std::cout << "Read " << ret << " row" << (ret>1 ? "s." : ".") << std::endl;
                        // for(auto i : data) std::cout << i <<std::endl;
                        // write_data(p, data, err);
                        for(auto i : data) idx = max(idx, i.id);
                    } else {
                        std::cerr << "File " << p.filename() << " not found." << std::endl;
                    }
                } else {
                    std::cout << "Abort." << std::endl;
                }
                break;

            case 3:
                input(tmp);
                tmp.id = ++idx;
                data.push_back(tmp);
                break;

            case 4:
                input(str);
                for(auto i : data) {
                    if(i.name == str) 
                        std::cout << i << std::endl;
                }
                break;

            case 5:
                input(it, "Enter ID: ");
                x = data.end();
                for(auto i = data.begin(); i != data.end(); i++) {
                    if(i -> id == it) {
                        x = i;
                        break;
                    }
                }
                if(x == data.end()) std::cerr << "ID not found!" << endl;
                else {
                    try {
                        data.erase(x);
                        std::cout << "Erased 1 row." << endl;
                    } catch(...) {
                        std::cerr << "Error occorred! " << endl;
                    }
                }
                break;

            case 6:
                input(it, "Enter ID: ");
                x = data.end();
                for(auto i = data.begin(); i != data.end(); i++) {
                    if(i -> id == it) {
                        x = i;
                        break;
                    }
                }
                if(x == data.end()) std::cerr << "ID not found!" << endl;
                else {
                    try {
                        input(tmp, "Enter new data.", true);
                        *x = tmp;
                        std::cout << "1 row modified." << endl;
                    } catch(...) {
                        std::cerr << "Error occurred!" << endl;
                    }
                }
                break;

            case 7:
                for(auto i : data)
                    std::cout << i << std::endl;
                break;

            case 8:
                if(input_confirm("Yes, I wish to clear all data.")) {
                    data.clear();
                    std::cout << "All data cleared." << std::endl;
                } else {
                    std::cout << "Abort." << std::endl;
                }
                break;

            case 9:
                std::sort(data.begin(), data.end());
                std::cout << "Sorted." << std::endl;
                break;

            case 0:
                goto end;

            default:
                ;
        }
        usleep(500000);
        cin.clear();
        cin.ignore();
    }
end:
    return 0;
}
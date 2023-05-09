#include "contact.h"

std::ostream& operator<<(std::ostream& os, const Person& d){
    os<<d.id<<' '<<d.name<<' '<<d.phone<<' '<<d.gender<<' '<<d.address<<' '<<d.age;
    return os;
}

bool Person::operator<(const Person& rhs) const {
    if(rhs.name != name) return name < rhs.name;
    else return id < rhs.id;
}

void show_menu() {
    std::cout << 
        "1. Save to file\n"
        "2. Load from file\n"
        "3. Add\n"
        "4. Search by name\n"
        "5. Delete\n"
        "6. Modify\n"
        "7. List all\n"
        "8. Clear all\n"
        "9. Sort by name\n"
        "0. Exit\n";
}
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <fstream>
#include <vector>
#include <clocale>

const char *const FILE_PATH = "data.txt";

struct Shoes {

    std::string vendorCode;
    std::string name;
    long long price;
    std::string producer;
    int sizeS;
    int amount;

    friend bool operator == (const Shoes& left, const Shoes& right) {
        if(left.vendorCode != right.vendorCode) return false;
        if(left.name != right.name) return false;
        if(left.price != right.price) return false;
        if(left.producer != right.producer) return false;
        if(left.sizeS != right.sizeS) return false;
        return true;
    }

    bool operator < (const Shoes& other) {
        if(vendorCode != other.vendorCode) return vendorCode < other.vendorCode;
        if(name != other.name) return name < other.name;
        if(price != other.price) return price < other.price;
        if(producer != other.producer) return  producer < other.producer;
        return sizeS < other.sizeS;
    }

    bool operator < (const Shoes& other) const {
        if(vendorCode != other.vendorCode) return vendorCode < other.vendorCode;
        if(name != other.name) return name < other.name;
        if(price != other.price) return price < other.price;
        if(producer != other.producer) return  producer < other.producer;
        return sizeS < other.sizeS;
    }

    friend std::istream& operator >> (std::istream& is, Shoes& shoes) {
        is >> shoes.vendorCode
           >> shoes.name
           >> shoes.price
           >> shoes.producer
           >> shoes.sizeS
           >> shoes.amount;
        return is;
    }

    friend std::ostream& operator << (std::ostream& os, const Shoes& shoes) {
        os << shoes.vendorCode << "\n"
           << shoes.name       << "\n"
           << shoes.price      << "\n"
           << shoes.producer   << "\n"
           << shoes.sizeS      << "\n"
           << shoes.amount     << "\n";
        return os;
    }

};

std::vector<Shoes> database;

bool ReadShoes(Shoes& shoes) {

    std::cout << "Input vendor code: ";
    std::cin >> shoes.vendorCode;

    bool ok = false;

    if (shoes.vendorCode[0] == 'M') {
        ok = true;
    }

    if (shoes.vendorCode[0] == 'W') {
        ok = true;
    }

    if(shoes.vendorCode[0] == 'C') {
        ok = true;
    }

    if(!ok) {
        std::cout << "Vendor code must start with: [M(Men),W(Women),C(Child)]\n\n";
        return false;
    }


    std::cout << "Input name: ";
    std::cin >> shoes.name;

    std::cout << "Input price: ";
    std::cin >> shoes.price;

    std::cout << "Input producer: ";
    std::cin >> shoes.producer;

    std::cout << "Input size: ";
    std::cin >> shoes.sizeS;

    std::cout << "Input amount: ";
    std::cin >> shoes.amount;

    return true;

}

void AddShoes() {

    Shoes shoes;

    bool ok = ReadShoes(shoes);

    if(ok) {
        database.insert(std::upper_bound(database.begin(), database.end(), shoes), shoes);
    }

}

void DeleteShoes() {

    std::cout << "\n1. Delete by index\n"
              << "2. Delete by shoes\n";

    std::string commandStr;
    std::cin >> commandStr;

    std::stringstream is(commandStr);

    int commandType = 0;

    if((is >> commandType).fail()) {
        std::cout << "\nBad integer number, try again!\n\n";
        return;
    }

    if(commandType == 1) {

        std::string strIndex;
        int index = 0;

        std::cout << "Input index: ";

        std::cin >> strIndex;
        is.clear();
        is.str(strIndex);

        if((is >> index).fail()) {
            std::cout << "\nBad integer number, try again!\n\n";
            return;
        }

        if(index <= 0 || index > database.size()) {
            std::cout << "\nIndex out of range, try again!\n\n";
            return;
        }

        database.erase(database.begin() + index - 1);

        return;

    }

    if(commandType == 2) {

        Shoes shoes;
        bool ok = ReadShoes(shoes);

        if(ok) {

            std::vector<Shoes>::iterator iterator = std::find(database.begin(), database.end(), shoes);
            if(iterator != database.end()) {
                database.erase(iterator);
            }

        }

        return;

    }

    std::cout << "\nInvalid index, try again!\n";

}

void FindByVendorCodeAndSize() {

    std::string vendorCode;
    std::string sizeStr;
    int sizeS = 0;

    std::cout << "\nInput shoes vendor code: ";
    std::cin >> vendorCode;

    std::cout << "Input shoes size: ";
    std::cin >> sizeStr;

    std::stringstream is(sizeStr);

    if((is >> sizeS).fail()) {
        std::cout << "\nBad integer number, try again\n\n";
        return;
    }

    std::cout << "\n";

    int counter = 0;

    for(size_t i = 0; i < database.size(); ++i) {
        if(database[i].vendorCode == vendorCode && database[i].sizeS == sizeS) {
            counter++;
            std::cout << "Shoes = {"
                      << database[i].vendorCode << ", "
                      << database[i].name       << ", "
                      << database[i].price      << ", "
                      << database[i].producer   << ", "
                      << database[i].sizeS      << ", "
                      << database[i].amount     << "}\n";
        }
    }

    if(!counter) {
        std::cout << "No matches shoes, try again!\n";
    }

    std::cout << "\n";

}

void PrintAllShoes() {

    std::cout << "\nNumber of shoes = " << database.size() << ":\n";
    for(size_t i = 0; i < database.size(); ++i) {
        std::cout << "Shoes[" << i + 1 << "] = {";
        std::cout << database[i].vendorCode << ", "
                  << database[i].name       << ", "
                  << database[i].price      << ", "
                  << database[i].producer   << ", "
                  << database[i].sizeS      << ", "
                  << database[i].amount     << "}\n";
    }

    std::cout << "\n";

}

void ReadDataFromFile() {

    database.clear();

    std::ifstream in(FILE_PATH);

    if(!in.is_open()) {
        std::cerr << "Can't open file [data.txt]\n";
        return;
    }

    size_t shoes_size;
    in >> shoes_size;

    for(size_t i = 0; i < shoes_size; ++i) {
        Shoes shoes;
        in >> shoes;
        database.push_back(shoes);
    }

}

void SaveDataToFile() {

    std::ofstream out(FILE_PATH);

    if(!out.is_open()) {
        std::cout << "Can't open file [data.txt]\n";
        return;
    }

    out << database.size() << "\n";
    for(size_t i = 0; i < database.size(); ++i) {
        out << database[i].vendorCode << "\n"
            << database[i].name       << "\n"
            << database[i].price      << "\n"
            << database[i].producer   << "\n"
            << database[i].sizeS      << "\n"
            << database[i].amount     << "\n";
    }

    out.close();

}

void PrintErrorMessage() {
    std::cout << "\nWrong command number, try again!\n\n";
}

void PrintExitMessage() {
    std::cout << "\nGood buy!\n";
}

int main() {

    ReadDataFromFile();

    bool status = true;

    while(status) {

        std::cout << "Menu:\n"
                  << "1. Add new shoes\n"
                  << "2. Delete shoes\n"
                  << "3. Find by vendor code & size\n"
                  << "4. Show info about all shoes\n"
                  << "5. Exit\n";

        int type;
        std::cin >> type;

        switch(type) {

            case 1: {
                AddShoes();
                break;
            }
            case 2: {
                DeleteShoes();
                break;
            }
            case 3: {
                FindByVendorCodeAndSize();
                break;
            }
            case 4: {
                PrintAllShoes();
                break;
            }
            case 5: {
                status = false;
                PrintExitMessage();
                break;
            }
            default: {
                PrintErrorMessage();
            }

        }

    }

    SaveDataToFile();

    return 0;
}

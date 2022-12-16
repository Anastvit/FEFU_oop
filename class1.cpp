#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Store
{
protected:
    std::string name;
    bool hasSocialMedia;
    unsigned customerCount;

public:
    Store(std::string name, bool hasSocialMedia)
    {
        this->customerCount = 0;
        this->name = name;
        this->hasSocialMedia = hasSocialMedia;
    }

    void Open()
    {
        srand(time(0));
        if (hasSocialMedia)
            customerCount += (50 + rand() % 51);
        else
            customerCount += (1 + rand() % 50);
    }

    void ShowStats()
    {
        std::cout << "Name: " << name << "\nCustomer Count: " << customerCount << "\nSocial Media: " << ((hasSocialMedia) ? "Yes" : "No");
    }

    friend bool operator==(const Store& a, const Store& b);
    friend bool operator!=(const Store& a, const Store& b);
    friend bool operator>(const Store& a, const Store& b);
    friend bool operator<(const Store& a, const Store& b);
    friend bool operator>=(const Store& a, const Store& b);
    friend bool operator<=(const Store& a, const Store& b);
};

bool operator==(const Store& a, const Store& b)
{
    return a.customerCount == b.customerCount;
}

bool operator!=(const Store& a, const Store& b)
{
    return a.customerCount != b.customerCount;
}

bool operator>(const Store& a, const Store& b)
{
    return a.customerCount > b.customerCount;
}

bool operator<(const Store& a, const Store& b)
{
    return a.customerCount < b.customerCount;
}

bool operator>=(const Store& a, const Store& b)
{
    return a.customerCount >= b.customerCount;
}

bool operator<=(const Store& a, const Store& b)
{
    return a.customerCount <= b.customerCount;
}

class BookStore : public Store
{
private:
    unsigned soldBookCount;

public:
    BookStore(std::string name, bool hasSocialMedia) : Store(name, hasSocialMedia)
    {
        soldBookCount = 0;
    }

    void Open()
    {
        Store::Open();
        srand(time(0));
        soldBookCount += (1 + rand() % 50);
    }

    void ShowStats()
    {
        std::cout << "Name: " << name << "\nCustomer Count: " << customerCount << "\nSold Book Count: " << soldBookCount << "\nSocial Media: " << ((hasSocialMedia) ? "Yes" : "No");
    }
};

int main()
{
    Store store("Just a store", false);
    store.Open();
    store.Open();
    store.ShowStats();
    std::cout << "\n\n";

    BookStore book("ChitayGorod", true);
    book.ShowStats();
    std::cout << "\n\n";
    book.Open();
    book.ShowStats();
    std::cout << "\n\n";

    std::cout << (book > store);
}

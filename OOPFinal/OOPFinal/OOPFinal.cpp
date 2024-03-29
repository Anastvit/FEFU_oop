﻿#include <iostream>
#include <string>
#include <random>
#include <ranges>
#include "customcontainer.h"

//В этой версии проекта я применяю singletone, iterator, лямбда-функцию, std::ranges, переопределение операторов, паттерн проектирования "Абстрактная фабрика";

int getRandomInt()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1023); // [1, 100]
    return dist6(rng);
}

class Store
{
protected:
    std::string name;
    bool hasSocialMedia;
    unsigned customerCount;

public:
    Store() {}
    Store(std::string name, bool hasSocialMedia)
    {
        this->customerCount = 0;
        this->name = name;
        this->hasSocialMedia = hasSocialMedia;
    }

    void ListItems(const std::vector<std::string>& items)
    {
        std::cout << "Items in store:\n";
        std::ranges::for_each(items, [](const std::string& item) {
            std::cout << "- " << item << "\n";
            });
    }

    virtual void Open()
    {
        if (hasSocialMedia)
            this->customerCount += (50 + getRandomInt() % 51);
        else
            this->customerCount += (1 + getRandomInt() % 50);
    }

    virtual void ShowStats()
    {
        std::cout << "Name: " << name << "\nCustomer Count: " << customerCount << "\nSocial Media: " << ((hasSocialMedia) ? "Yes" : "No");
    }

    std::string getName() { return name; }

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
        this->soldBookCount += (1 + getRandomInt() % 50);
    }

    void ShowStats()
    {
        Store::ShowStats();
        std::cout << "\nSold Book Count: " << soldBookCount;
    }
};

class ElectronicsStore : public Store
{
private:
    unsigned soldItemCount;
    bool hasOnlineStore;

public:
    ElectronicsStore(std::string name, bool hasSocialMedia, bool hasOnlineStore) : Store(name, hasSocialMedia)
    {
        soldItemCount = 0;
        this->hasOnlineStore = hasOnlineStore;
    }

    void Open()
    {
        Store::Open();
        soldItemCount += (1 + getRandomInt() % 50);
        if (hasOnlineStore)
            this->customerCount += (50 + getRandomInt() % 51);
        else
            this->customerCount += (1 + getRandomInt() % 50);
    }

    void ShowStats()
    {
        Store::ShowStats();
        std::cout << "\nSold Item Count: " << soldItemCount << "\nOnline Store: " << ((hasOnlineStore) ? "Yes" : "No");;
    }
};

class AbstractStoreFactory
{
public:
    virtual Store* createStore(std::string name, bool hasSocialMedia) = 0;
};

class BookStoreFactory : public AbstractStoreFactory
{
public:
    Store* createStore(std::string name, bool hasSocialMedia)
    {
        return new BookStore(name, hasSocialMedia);
    }
};

class ElectronicsStoreFactory : public AbstractStoreFactory
{
public:
    Store* createStore(std::string name, bool hasSocialMedia)
    {
        return new ElectronicsStore(name, hasSocialMedia, true);
    }
};

class VladivostokCity
{
    using StoreContainer = Container<Store, 100>;
private:
    static VladivostokCity* p_instance;
    StoreContainer stores;
    VladivostokCity() {}
    VladivostokCity(const VladivostokCity&);
    VladivostokCity& operator=(VladivostokCity&);
public:
    static VladivostokCity& getInstance() {
        if (!p_instance)
            p_instance = new VladivostokCity();
        return *p_instance;
    }

    void showAllStores()
    {
        StoreContainer::Iterator beg = stores.begin();
        StoreContainer::Iterator end = stores.end();
        while (beg != end)
        {
            std::cout << beg->getName() << "\n";
            beg++;
        }
    }

    void registerStore(Store& store)
    {
        stores.add(store);
    }
};
VladivostokCity* VladivostokCity::p_instance = 0;

int main()
{
    setlocale(LC_ALL, "Russian");
    ElectronicsStoreFactory electronicsFactory;
    Store* electronicsStore = electronicsFactory.createStore("DNS", true);
    VladivostokCity::getInstance().registerStore(*electronicsStore);
    electronicsStore->Open();
    electronicsStore->ShowStats();
    std::cout << "\n";
    std::vector<std::string> electronicsItems = { "TV", "Cameras", "Headphones" };
    electronicsStore->ListItems(electronicsItems);
    std::cout << "\n";


    BookStoreFactory bookStoreFactory;
    Store* bookStore = bookStoreFactory.createStore("Labyrynth", true);
    VladivostokCity::getInstance().registerStore(*bookStore);
    bookStore->Open();
    bookStore->ShowStats();
    std::cout << "\n";
    std::vector<std::string> bookStoreItems = { "Novels", "Manga", "Comics" };
    bookStore->ListItems(bookStoreItems);
    std::cout << "\n";

    return 0;
}
#include <iostream>
#include <string>
#include <ctime>

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
        srand(time(0));
        soldBookCount += (1 + rand() % 50);
    }

    void ShowStats()
    {
        std::cout << "Name: " << name << "\nCustomer Count: " << customerCount << "\nSold Book Count: " << soldBookCount << "\nSocial Media: " << ((hasSocialMedia) ? "Yes" : "No");
    }
};

class Stores
{
public:
    struct Iterator
    {
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Store;
        using pointer = Store*;
        using reference = Store&;

        Iterator(Stores::Iterator& o) : m_ptr(o.m_ptr) {}
        Iterator(Stores::Iterator&& o) noexcept : m_ptr(std::move(o.m_ptr))
        {
            o.m_ptr = nullptr;
        }
        Iterator(pointer ptr) : m_ptr(ptr) {}
        ~Iterator() {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        Iterator& operator--() { m_ptr--; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
        friend bool operator< (const Iterator& a, const Iterator& b) { return a.m_ptr < b.m_ptr; };
        friend bool operator> (const Iterator& a, const Iterator& b) { return a.m_ptr > b.m_ptr; };
        friend bool operator>= (const Iterator& a, const Iterator& b) { return (a.m_ptr > b.m_ptr) || (a.m_ptr == b.m_ptr); };
        friend bool operator<= (const Iterator& a, const Iterator& b) { return (a.m_ptr < b.m_ptr) || (a.m_ptr == b.m_ptr); };

        Iterator& operator+(int n)
        {
            m_ptr = m_ptr + n;
            return *this;
        }
        Iterator& operator-(int n)
        {
            m_ptr = m_ptr - n;
            return *this;
        }
        Iterator& operator+=(int n)
        {
            m_ptr = m_ptr + n;
            return *this;
        }
        Iterator& operator-=(int n)
        {
            m_ptr = m_ptr - n;
            return *this;
        }


        // copy assignment
        Iterator& operator=(const Stores::Iterator& other)
        {
            // Guard self assignment
            if (this == &other)
                return *this;

            *m_ptr = *other;
            return *this;
        }

        // move assignment
        Iterator& operator=(Iterator&& other) noexcept
        {
            // Guard self assignment
            if (this == &other)
                return *this;

            m_ptr = std::move(other.m_ptr);
            other.m_ptr = nullptr;

            return *this;
        }

        void swap(Iterator& other) {
            std::swap(*m_ptr, *other);
        }

    private:
        pointer m_ptr;
    };

    Stores() { currIndex = 0; }
    Iterator begin() { return Iterator(&m_data[0]); }
    Iterator end() { return Iterator(&m_data[currIndex]); }
    void add(Store& store)
    {
        m_data[currIndex] = store;
        currIndex++;
    }

private:
    Store m_data[200];
    int currIndex;
};

class VladivostokCity
{
private:
    static VladivostokCity* p_instance;
    Stores stores;
    VladivostokCity() {
        stores = Stores();
    }
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
        Stores::Iterator beg = stores.begin();
        Stores::Iterator end = stores.end();
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

    Store store("Реми", false);
    VladivostokCity::getInstance().registerStore(store);
    store.Open();
    store.Open();
    store.ShowStats();
    std::cout << "\n\n";

    Store mall("Море", false);
    VladivostokCity::getInstance().registerStore(mall);

    BookStore book("Читай-город", true);
    VladivostokCity::getInstance().registerStore(book);
    book.ShowStats();
    std::cout << "\n\n";
    book.Open();
    book.ShowStats();
    std::cout << "\n\n";

    BookStore labyrinth("Лабиринт", true);
    VladivostokCity::getInstance().registerStore(labyrinth);

    std::cout << (book > store) << "\n\nAll stores in VDK:\n";
    VladivostokCity::getInstance().showAllStores();
}

#include <iostream>
#include <fstream>
#include <string>

struct scan_info
{
    std::string model; // наименование модели
    int price; // цена
    double x_size; // горизонтальный размер области сканирования
    double y_size; // вертикальный размер области сканирования
    int optr; // оптическое разрешение
    int grey; // число градаций серого
};

void writeToFile(scan_info& info)
{
    std::ifstream fin("C:\\Users\\MiBook\\Desktop\\lab3\\scan_info.txt", std::ios::in);
    if (fin.is_open())
    {
        fin.seekg(0, std::ios::end);
        int bytes = fin.tellg();
        int count = 0;
        fin.seekg(0, std::ios::beg);
        fin.read((char*)&count, sizeof(int));
        char* readBytes = new char[bytes - 4];
        fin.read(readBytes, bytes - 4);
        fin.close();

        std::ofstream fout("C:\\Users\\MiBook\\Desktop\\lab3\\scan_info.txt", std::ios::out | std::ios::binary);
        count++;
        fout.write((char*)&count, sizeof(int));
        fout.write((char*)&info.price, sizeof(int));
        fout.write((char*)&info.x_size, sizeof(double));
        fout.write((char*)&info.y_size, sizeof(double));
        fout.write((char*)&info.optr, sizeof(int));
        fout.write((char*)&info.grey, sizeof(int));
        fout.write(info.model.c_str(), info.model.size() + 1);
        fout.write(readBytes, bytes - 4);
        fout.close();
        delete[] readBytes;
    }
    else
    {
        std::ofstream fout("C:\\Users\\MiBook\\Desktop\\lab3\\scan_info.txt", std::ios::out | std::ios::binary);
        int count = 1;
        fout.write((char*)&count, sizeof(int));
        fout.write((char*)&info.price, sizeof(int));
        fout.write((char*)&info.x_size, sizeof(double));
        fout.write((char*)&info.y_size, sizeof(double));
        fout.write((char*)&info.optr, sizeof(int));
        fout.write((char*)&info.grey, sizeof(int));
        fout.write(info.model.c_str(), info.model.size() + 1);
        fout.close();
    }
}

void dialog()
{
    scan_info scan;
    std::cout << "Enter Model: ";
    std::getline(std::cin, scan.model);
    std::cout << "Enter Info (price, x_size, y_size, optr, grey): ";
    if ((std::cin >> scan.price >> scan.x_size >> scan.y_size >> scan.optr >> scan.grey))
        writeToFile(scan);
    else
        std::cout << "Incorrect input!" << std::endl;
}


int main()
{
    dialog();

    return 0;
}

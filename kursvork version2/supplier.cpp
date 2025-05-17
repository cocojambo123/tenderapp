#pragma once
#include "supplier.h"

void showAllSuppliers(const std::vector<Supplier>& suppliers) {
    if (suppliers.empty()) {
        std::cout << "Список поставщиков пуст.\n";
        return;
    }

    std::cout << "\n--- Список поставщиков ---\n";
    std::cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
    std::cout << "| № | Поставщик        | Товар               | Кол-во          |   Цена за еденицу   |   Общая цена   | Доставка (дн)  |\n";
    std::cout << "+----------------------------------------------------------------------------------------------------------------------+\n";

    for (int i = 0; i < suppliers.size(); ++i) {
        std::cout << "| " << std::setw(1) << i + 1 << " "
            << "| " << std::setw(17) << std::left << suppliers[i].name
            << "| " << std::setw(20) << std::left << suppliers[i].product
            << "| " << std::setw(15) << std::right << suppliers[i].quantity
            << " | " << std::setw(19) << std::fixed << std::setprecision(2) << suppliers[i].pricePerUnit
            << " | " << std::setw(14) << std::fixed << std::setprecision(2) << suppliers[i].totalPrice
            << " | " << std::setw(14) << suppliers[i].delivery_days << " |" << std::endl;
    }

    std::cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
}

void addSupplier(std::vector<Supplier>& suppliers, const std::string& filename) {
    Supplier new_supplier;

    

    safeStringInput(new_supplier.name, "Введите название поставщика: ");

    safeStringInput(new_supplier.product, "Введите наименование товара: ");

    intInput(new_supplier.quantity, "Введите количество товара: ", 0, 9999999999);

    intInput(new_supplier.pricePerUnit, "Введите цену за еденицу: ", 0, 9999999999);


    new_supplier.totalPrice = new_supplier.quantity * new_supplier.pricePerUnit;

    intInput(new_supplier.delivery_days, "Введите срок поставки (в днях): ", 0, 9999999999);

    suppliers.push_back(new_supplier);

    std::ofstream fout(filename, std::ios::app);
    if (fout.is_open()) {
        fout << new_supplier.name << ";"
            << new_supplier.product << ";"
            << new_supplier.quantity << ";"
            << new_supplier.pricePerUnit << ";"
            << new_supplier.totalPrice << ";"
            << new_supplier.delivery_days << "\n";
        fout.close();
        std::cout << "Поставщик добавлен и сохранён в файл.\n";
    }
    else {
        std::cout << "Ошибка записи в файл.\n";
    }
}

void readSuppliersFromFile(std::vector<Supplier>& suppliers, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "Не удалось открыть файл: " << filename << "\n";
        return;
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        Supplier s;
        std::string quantityStr, pricePerUnitStr, totalPriceStr, daysStr;

        std::getline(iss, s.name, ';');
        std::getline(iss, s.product, ';');
        std::getline(iss, quantityStr, ';');
        std::getline(iss, pricePerUnitStr, ';');
        std::getline(iss, totalPriceStr, ';');
        std::getline(iss, daysStr, ';');

        try {
            s.quantity = std::stoi(quantityStr);
            s.pricePerUnit = std::stod(pricePerUnitStr);
            s.totalPrice = std::stoi(totalPriceStr);
            s.delivery_days = std::stoi(daysStr);
            suppliers.push_back(s);
        }
        catch (...) {
            std::cout << "Ошибка при разборе строки: " << line << "\n";
        }
    }

    fin.close();
}

void writeSuppliersToFile(const std::vector<Supplier>& suppliers, const std::string& filename) {
    std::ofstream fout(filename);
    for (const auto& s : suppliers) {
        fout << s.name << ";"
            << s.product << ";"
            << s.quantity << ";"
            << s.pricePerUnit << ";"
            << s.totalPrice << ";"
            << s.delivery_days << "\n";
    }
    fout.close();
}

void deleteSupplier(std::vector<Supplier>& suppliers, const std::string& filename) {
    if (suppliers.empty()) {
        std::cout << "Список поставщиков пуст.\n";
        return;
    }

    showAllSuppliers(suppliers);
    int index;
    std::cout << "Введите номер поставщика для удаления: ";
    std::cin >> index;

    if (index < 1 || index > suppliers.size()) {
        std::cout << "Неверный номер.\n";
        return;
    }

    std::string name = suppliers[index - 1].name;
    suppliers.erase(suppliers.begin() + (index - 1));
    writeSuppliersToFile(suppliers, filename);
    std::cout << "Поставщик '" << name << "' успешно удалён.\n";
}

void editSupplier(std::vector<Supplier>& suppliers, const std::string& filename) {
    if (suppliers.empty()) {
        std::cout << "Список поставщиков пуст.\n";
        return;
    }

    showAllSuppliers(suppliers);
    int index;
    intInput(index, "Введите номер поставщика для редактирования: ", 1, suppliers.size());

    Supplier& s = suppliers[index - 1];
    

    safeStringInput(s.name, "Новое название поставщика (было: " + s.name + "): ");
    safeStringInput(s.product, "Новый товар (было: " + s.product + "): ");

    intInput(s.quantity, "Новое количество (было: " + std::to_string(s.quantity) + "): ", 0, 999999);
    intInput(reinterpret_cast<int&>(s.pricePerUnit), "Новая цена за единицу (было: " + std::to_string(s.pricePerUnit) + "): ", 0, 999999);

    s.totalPrice = s.quantity * s.pricePerUnit;
    std::cout << "Новая общая цена: " << s.totalPrice << "\n";

    intInput(s.delivery_days, "Новый срок поставки (было: " + std::to_string(s.delivery_days) + "): ", 0, 365);

    writeSuppliersToFile(suppliers, filename);
    std::cout << "Поставщик успешно обновлён.\n";
}

void searchSuppliers(const std::vector<Supplier>& suppliers) {
    if (suppliers.empty()) {
        std::cout << "Список поставщиков пуст.\n";
        return;
    }

    std::cout << "\n1. Поиск по названию поставщика";
    std::cout << "\n2.Поиск по названию товара";
    std::cout << "\n3.Поиск по сроку доставки";
    std::cout << " \nВыберите параметр : ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    bool found = false;

    if (choice == 1) {
        std::string keyword;
        std::cout << "Введите часть названия поставщика: ";
        std::getline(std::cin, keyword);

        for (const auto& s : suppliers) {
            if (s.name.find(keyword) != std::string::npos) {
                std::cout << s.name << " | " << s.product << " | " << s.delivery_days << " дн.\n";
                found = true;
            }
        }
    }
    else if (choice == 2) {
        std::string product;
        std::cout << "Введите наименование товара: ";
        std::getline(std::cin, product);

        for (const auto& s : suppliers) {
            if (s.product.find(product) != std::string::npos) {
                std::cout << s.name << " | " << s.product << " | " << s.delivery_days << " дн.\n";
                found = true;
            }
        }
    }
    else if (choice == 3) {
        int maxDays;
        std::cout << "Введите максимальное количество дней доставки: ";
        std::cin >> maxDays;

        for (const auto& s : suppliers) {
            if (s.delivery_days <= maxDays) {
                std::cout << s.name << " | " << s.product << " | " << s.delivery_days << " дн.\n";
                found = true;
            }
        }
    }

    if (!found) std::cout << "Совпадений не найдено.\n";
}

void sortSuppliers(std::vector<Supplier>& suppliers) {
    if (suppliers.empty()) {
        std::cout << "Список поставщиков пуст.\n";
        return;
    }
    std::cout << "\nСортировать:";
    std::cout << "\n1.По названию поставщика";
    std::cout << "\n2.По назаванию компьютера";
    std::cout << "\n3.По сроку доставки";
    std::cout << "\n4.По цене за еденицу";
    std::cout << "\n5.По общей цене";
    std::cout << "\nВыберите параметр : ";
    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        std::sort(suppliers.begin(), suppliers.end(), [](const Supplier& a, const Supplier& b) {
            return a.name < b.name;
            });
        break;
    case 2:
        std::sort(suppliers.begin(), suppliers.end(), [](const Supplier& a, const Supplier& b) {
            return a.product < b.product;
            });
        break;
    case 3:
        std::sort(suppliers.begin(), suppliers.end(), [](const Supplier& a, const Supplier& b) {
            return a.delivery_days < b.delivery_days;
            });
        break;
    case 4:
        std::sort(suppliers.begin(), suppliers.end(), [](const Supplier& a, const Supplier& b) {
            return a.pricePerUnit < b.pricePerUnit;
            });
        break;
    case 5:
        std::sort(suppliers.begin(), suppliers.end(), [](const Supplier& a, const Supplier& b) {
            return a.totalPrice < b.totalPrice;
            });
        break;
    default:
        std::cout << "Неверный выбор.\n";
        return;
    }

    std::cout << "\nОтсортированный список:\n";
    showAllSuppliers(suppliers);
}

void findFastestSupplier(const std::vector<Supplier>& suppliers) {
    if (suppliers.empty()) {
        std::cout << "Список поставщиков пуст.\n";
        return;
    }

    const Supplier* fastest = &suppliers[0];
    for (const auto& s : suppliers) {
        if (s.delivery_days < fastest->delivery_days) {
            fastest = &s;
        }
    }

    std::cout << "\n--- Поставщик с минимальным сроком поставки ---\n";
    std::cout << "Название: " << fastest->name << "\n";
    std::cout << "Товар: " << fastest->product << "\n";
    std::cout << "Количество: " << fastest->quantity << "\n";
    std::cout << "Цена за еденицу: " << fastest->pricePerUnit << "\n";
    std::cout << "Общая цена: " << fastest->totalPrice << "\n";
    std::cout << "Срок поставки: " << fastest->delivery_days << " дн.\n";
}
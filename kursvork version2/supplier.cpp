#pragma once
#include "supplier.h"

void showAllSuppliers(const std::vector<Supplier>& suppliers) {
    if (suppliers.empty()) {
        std::cout << "������ ����������� ����.\n";
        return;
    }

    std::cout << "\n--- ������ ����������� ---\n";
    std::cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
    std::cout << "| � | ���������        | �����               | ���-��          |   ���� �� �������   |   ����� ����   | �������� (��)  |\n";
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

    

    safeStringInput(new_supplier.name, "������� �������� ����������: ");

    safeStringInput(new_supplier.product, "������� ������������ ������: ");

    intInput(new_supplier.quantity, "������� ���������� ������: ", 0, 9999999999);

    intInput(new_supplier.pricePerUnit, "������� ���� �� �������: ", 0, 9999999999);


    new_supplier.totalPrice = new_supplier.quantity * new_supplier.pricePerUnit;

    intInput(new_supplier.delivery_days, "������� ���� �������� (� ����): ", 0, 9999999999);

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
        std::cout << "��������� �������� � ������� � ����.\n";
    }
    else {
        std::cout << "������ ������ � ����.\n";
    }
}

void readSuppliersFromFile(std::vector<Supplier>& suppliers, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cout << "�� ������� ������� ����: " << filename << "\n";
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
            std::cout << "������ ��� ������� ������: " << line << "\n";
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
        std::cout << "������ ����������� ����.\n";
        return;
    }

    showAllSuppliers(suppliers);
    int index;
    std::cout << "������� ����� ���������� ��� ��������: ";
    std::cin >> index;

    if (index < 1 || index > suppliers.size()) {
        std::cout << "�������� �����.\n";
        return;
    }

    std::string name = suppliers[index - 1].name;
    suppliers.erase(suppliers.begin() + (index - 1));
    writeSuppliersToFile(suppliers, filename);
    std::cout << "��������� '" << name << "' ������� �����.\n";
}

void editSupplier(std::vector<Supplier>& suppliers, const std::string& filename) {
    if (suppliers.empty()) {
        std::cout << "������ ����������� ����.\n";
        return;
    }

    showAllSuppliers(suppliers);
    int index;
    intInput(index, "������� ����� ���������� ��� ��������������: ", 1, suppliers.size());

    Supplier& s = suppliers[index - 1];
    

    safeStringInput(s.name, "����� �������� ���������� (����: " + s.name + "): ");
    safeStringInput(s.product, "����� ����� (����: " + s.product + "): ");

    intInput(s.quantity, "����� ���������� (����: " + std::to_string(s.quantity) + "): ", 0, 999999);
    intInput(reinterpret_cast<int&>(s.pricePerUnit), "����� ���� �� ������� (����: " + std::to_string(s.pricePerUnit) + "): ", 0, 999999);

    s.totalPrice = s.quantity * s.pricePerUnit;
    std::cout << "����� ����� ����: " << s.totalPrice << "\n";

    intInput(s.delivery_days, "����� ���� �������� (����: " + std::to_string(s.delivery_days) + "): ", 0, 365);

    writeSuppliersToFile(suppliers, filename);
    std::cout << "��������� ������� �������.\n";
}

void searchSuppliers(const std::vector<Supplier>& suppliers) {
    if (suppliers.empty()) {
        std::cout << "������ ����������� ����.\n";
        return;
    }

    std::cout << "\n1. ����� �� �������� ����������";
    std::cout << "\n2.����� �� �������� ������";
    std::cout << "\n3.����� �� ����� ��������";
    std::cout << " \n�������� �������� : ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    bool found = false;

    if (choice == 1) {
        std::string keyword;
        std::cout << "������� ����� �������� ����������: ";
        std::getline(std::cin, keyword);

        for (const auto& s : suppliers) {
            if (s.name.find(keyword) != std::string::npos) {
                std::cout << s.name << " | " << s.product << " | " << s.delivery_days << " ��.\n";
                found = true;
            }
        }
    }
    else if (choice == 2) {
        std::string product;
        std::cout << "������� ������������ ������: ";
        std::getline(std::cin, product);

        for (const auto& s : suppliers) {
            if (s.product.find(product) != std::string::npos) {
                std::cout << s.name << " | " << s.product << " | " << s.delivery_days << " ��.\n";
                found = true;
            }
        }
    }
    else if (choice == 3) {
        int maxDays;
        std::cout << "������� ������������ ���������� ���� ��������: ";
        std::cin >> maxDays;

        for (const auto& s : suppliers) {
            if (s.delivery_days <= maxDays) {
                std::cout << s.name << " | " << s.product << " | " << s.delivery_days << " ��.\n";
                found = true;
            }
        }
    }

    if (!found) std::cout << "���������� �� �������.\n";
}

void sortSuppliers(std::vector<Supplier>& suppliers) {
    if (suppliers.empty()) {
        std::cout << "������ ����������� ����.\n";
        return;
    }
    std::cout << "\n�����������:";
    std::cout << "\n1.�� �������� ����������";
    std::cout << "\n2.�� ��������� ����������";
    std::cout << "\n3.�� ����� ��������";
    std::cout << "\n4.�� ���� �� �������";
    std::cout << "\n5.�� ����� ����";
    std::cout << "\n�������� �������� : ";
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
        std::cout << "�������� �����.\n";
        return;
    }

    std::cout << "\n��������������� ������:\n";
    showAllSuppliers(suppliers);
}

void findFastestSupplier(const std::vector<Supplier>& suppliers) {
    if (suppliers.empty()) {
        std::cout << "������ ����������� ����.\n";
        return;
    }

    const Supplier* fastest = &suppliers[0];
    for (const auto& s : suppliers) {
        if (s.delivery_days < fastest->delivery_days) {
            fastest = &s;
        }
    }

    std::cout << "\n--- ��������� � ����������� ������ �������� ---\n";
    std::cout << "��������: " << fastest->name << "\n";
    std::cout << "�����: " << fastest->product << "\n";
    std::cout << "����������: " << fastest->quantity << "\n";
    std::cout << "���� �� �������: " << fastest->pricePerUnit << "\n";
    std::cout << "����� ����: " << fastest->totalPrice << "\n";
    std::cout << "���� ��������: " << fastest->delivery_days << " ��.\n";
}
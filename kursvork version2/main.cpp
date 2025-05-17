// auth_system.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h> 
#include <iomanip>
#include "account.h"
#include "auth.h"
#include "file_constants.h"
#include "io_utils.h"
#include "supplier.h"

void userManagmentMenu(std::vector<Account>& accounts) {
    
    bool flag = true;
    while (flag) {
        int choice;
        std::cout << "\n---------Управление пользователями------------------\n";
        std::cout << "1. Подтверждение пользователей\n";
        std::cout << "2. Просмотр учетных записей\n";
        std::cout << "3. Удаление пользователей\n";
        std::cout << "4. Добавление новой учетной записи\n";
        std::cout << "0. Выход\n";
        intInput(choice, "\nВыберите пункт: ", 0, 4);
        switch (choice) {
        case 1:
            confirmationAccounts(accounts, ACCOUNTS_FILE);
            break;
        case 2:
            showAllAccounts(accounts);
            break;
        case 3:
            deleteAccount(accounts);
            break;
        case 4:
            addAccount(accounts);
            break;
        case 0:
            flag = false;
            break;
        default: {
            break;
        }
        }
    }
}

void tenderEditingMode(std::vector<Supplier>& suppliers) {
    bool flag = true;
    while (flag) {
        int choice;
        std::cout << "\n---------Режим редактирования заявок------------------\n";
        std::cout << "1. Добавить новую заявку\n";
        std::cout << "2. Удалить заявку поставщика\n";
        std::cout << "3. Редактировать заявку поставщика\n";
        std::cout << "0. Выход\n";
        intInput(choice, "\nВыберите пункт: ", 0, 3);
        switch (choice) {
        case 1:
            addSupplier(suppliers, SUPPLIERS_FILE);
            break;
        case 2:
            deleteSupplier(suppliers, SUPPLIERS_FILE);
            break;
        case 3:
            editSupplier(suppliers, SUPPLIERS_FILE);
            break;
        case 0:
            flag = false;
            break;
        default: {
            break;
        }
        }
    }
}

void tenderProcessingMode(std::vector<Supplier>& suppliers) {
    bool flag = true;
    while (flag) {
        int choice;
        std::cout << "\n---------Режим обработки заявок------------------\n";
        std::cout << "1. Просмотреть все заявки\n";
        std::cout << "2. Поиск\n";
        std::cout << "3. Сортировка\n";
        std::cout << "4. Результат тендера\n";
        std::cout << "0. Выход\n";
        intInput(choice, "\nВыберите пункт: ", 0, 4);
        switch (choice) {
        case 1:
            showAllSuppliers(suppliers);
            break;
        case 2:
            searchSuppliers(suppliers);
            break;
        case 3:
            sortSuppliers(suppliers);
            break;
        case 4:
            findFastestSupplier(suppliers);
            break;
        case 0:
            flag = false;
            break;
        default: {
            break;
        }
        }
    }
}

void workWithTenderMenu(std::vector<Supplier>& suppliers) {
    bool flag = true;
    while (flag) {
        int choice;
        std::cout << "\n---------Работа с тендером------------------\n";
        std::cout << "1. Режим редактирования\n";
        std::cout << "2. Режим обработки\n";
        std::cout << "0. Выход\n";
        intInput(choice, "\nВыберите пункт: ", 0, 2);
        switch (choice) {
        case 1:
            tenderEditingMode(suppliers);
            break;
        case 2:
            tenderProcessingMode(suppliers);
            break;
        case 0:
            flag = false;
            break;
        default:
            break;
        }
    }
}

void adminMenu(std::vector<Account>& accounts) {
    std::vector<Supplier> suppliers;
    readSuppliersFromFile(suppliers, SUPPLIERS_FILE);


    bool flag = true;
    while (flag) {
        int choice;
        std::cout << "\n----------------- МЕНЮ АДМИНИСТРАТОРА ---------------------------------------\n";
        std::cout << "1. Работа с тендером\n";
        std::cout << "2. Управление пользователями\n";
        std::cout << "0. Выход\n";
        intInput(choice, "\nВыберите пункт: ", 0, 2);
        switch (choice) {
        case 1:
            workWithTenderMenu(suppliers);
            break;
        case 2:
            userManagmentMenu(accounts);
            break;
        case 0:
            flag = false;
            break;
        default: {
            break;
        }
        }
    }
}

void userMenu(std::vector<Account>& accounts) {
    std::vector<Supplier> suppliers;
    readSuppliersFromFile(suppliers, SUPPLIERS_FILE);


    bool flag = true;
    while (flag) {
        int choice;
        std::cout << "\n--- МЕНЮ ПОЛЬЗОВАТЕЛЯ ---\n";
        std::cout << "1. Просмотреть все заявки\n";
        std::cout << "2. Найти поставщика с минимальным сроком поставки\n";
        std::cout << "3. Поиск\n";
        std::cout << "4. Сортировка\n";
        std::cout << "0. Выход\n";
        intInput(choice, "\nВыберите пункт: ", 0, 4);
        switch (choice) {
        case 1:
            showAllSuppliers(suppliers);
            break;
        case 2:
            findFastestSupplier(suppliers);
            break;
        case 3:
            searchSuppliers(suppliers);
            break;
        case 4:
            sortSuppliers(suppliers);
            break;
        case 0:
            std::cout << "Выход из пользовательского меню.\n";
            flag = false;
            break;
        default:
            std::cout << "Неверный выбор.\n";
            break;
        }
    }
}

void loginAccount(std::vector<Account>& accounts) {
    std::string login, password;
    withoutSpacesInput(login, "\nВведите логин - ");

    std::cout << "\nВведите пароль - ";
    password = inputPasswordMasked();

    int role = authorize(accounts, login, password);
    if (role == 1) {
        adminMenu(accounts);
    }
    else if (role == 0) {
        userMenu(accounts);
    }
}

int main() {
    createAdminIfFileNotExist();
    setlocale(LC_ALL, "rus");
    createAdminIfFileNotExist();
    std::vector<Account> accounts;
    readAccountsFromFile(accounts);


    bool programFlag = true;
    while (programFlag) {

        int choice;
        std::cout << "----------------------------- МЕНЮ -------------------------------------------\n";
        std::cout << "\n1. Вход";
        std::cout << "\n2. Регистрация";
        std::cout << "\n0. Выход.\n";
        intInput(choice, "\nВыберите действие : ", 0, 2);

        switch (choice) {
        case 1:
            loginAccount(accounts);
            break;
        case 2:
            registerAccount(accounts);

            break;
        case 0:
            programFlag = false;
        default:
            break;
        }
    }
    return 0;
}
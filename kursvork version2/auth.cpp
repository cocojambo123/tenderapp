#pragma once
#include "auth.h"
#include "io_utils.h"

void createAdminIfFileNotExist() {
    std::ifstream file(ACCOUNTS_FILE);
    if (!file.good()) {
        std::ofstream fout(ACCOUNTS_FILE);
        fout << "admin;admin123;1;1\n";
        fout.close();
    }
}
std::string inputPasswordMasked() {
    std::string pass;
    char ch;
    while ((ch = _getch()) != '\r') { // до Enter
        if (ch == '\b' && !pass.empty()) {
            std::cout << "\b \b";
            pass.pop_back();
        }
        else if (isprint(ch)) {
            pass += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return pass;
}
int authorize(const std::vector<Account>& accounts, const std::string& login, const std::string& password) {
    for (const auto& acc : accounts) {
        if (acc.login == login && acc.password == password) {
            if (acc.access == 1) return acc.role;
            else {
                std::cout << "Учетная запись не подтверждена.\n";
                return -1;
            }
        }
    }
    std::cout << "Неверный логин или пароль.\n";
    return -1;
}
void registerAccount(std::vector<Account>& accounts) {
    Account newAcc;
    withoutSpacesInput(newAcc.login, "Введите новый логин: ");

    for (const auto& acc : accounts) {
        if (acc.login == newAcc.login) {
            std::cout << "Логин уже существует.\n";
            return;
        }
    }

    std::cout << "Введите пароль: ";
    newAcc.password = inputPasswordMasked();
    newAcc.role = 0;
    newAcc.access = 0;

    writeAccountToFile(newAcc);
    std::cout << "Регистрация завершена. Ожидайте подтверждения администратора.\n";
}

void addAccount(std::vector<Account>& accounts) {
    Account newAcc;
    withoutSpacesInput(newAcc.login, "Введите новый логин: ");

    for (const auto& acc : accounts) {
        if (acc.login == newAcc.login) {
            std::cout << "Логин уже существует.\n";
            return;
        }
    }

    std::cout << "Введите пароль: ";
    newAcc.password = inputPasswordMasked();
    intInput(newAcc.role, "Введите роль (1-администратор, 0-пользователь): ", 0, 1);
    intInput(newAcc.access, "Подтвердить аккаунт (1-да, 0-нет): ", 0, 1);

    writeAccountToFile(newAcc);
    std::cout << "Добавление аккаунта завершено.\n";
}
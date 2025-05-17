#include "account.h"
void readAccountsFromFile(std::vector<Account>& accounts) {
    std::ifstream file(ACCOUNTS_FILE);
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        Account acc;
        std::string roleStr, accessStr;
        std::getline(iss, acc.login, ';');
        std::getline(iss, acc.password, ';');
        std::getline(iss, roleStr, ';');
        std::getline(iss, accessStr, ';');
        acc.role = std::stoi(roleStr);
        acc.access = std::stoi(accessStr);
        accounts.push_back(acc);
    }
    file.close();
}
void writeAccountToFile(const Account& acc) {
    std::ofstream file(ACCOUNTS_FILE, std::ios::app);
    file << acc.login << ';' << acc.password << ';' << acc.role << ';' << acc.access << '\n';
    file.close();
}
void writeAllAccountsToFile(const std::vector<Account>& accounts) {
    std::ofstream file(ACCOUNTS_FILE, std::ios::trunc); // очищаем файл
    for (const auto& acc : accounts) {
        file << acc.login << ';' << acc.password << ';' << acc.role << ';' << acc.access << '\n';
    }
    file.close();
}
void deleteAccount(std::vector<Account>& accounts) {
    std::cout << "\n--------------- Удаление аккаунтов ---------------\n";
    if (accounts.empty()) {
        std::cout << "Список учетных записей пуст.\n";
        return;
    }

    showAllAccounts(accounts);
    int index;
    std::cout << "Введите номер аккаунта для удаления: ";
    std::cin >> index;

    if (index < 1 || index > accounts.size()) {
        std::cout << "Неверный номер.\n";
        return;
    }

    if (accounts[index - 1].role == 1) {
        std::cout << "\nНельзя удалять администраторов!!!\n";
        return;
    }

    std::string name = accounts[index - 1].login;
    accounts.erase(accounts.begin() + (index - 1));
    writeAllAccountsToFile(accounts);
    std::cout << "Учетная запись '" << name << "' успешно удалена.\n";
}
void confirmationAccounts(std::vector<Account>& accounts, const std::string& filename) {
    bool anyPending = false;
    for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i].access == 0) {
            std::cout << i + 1 << ". Логин: " << accounts[i].login << " (ожидает подтверждения)\n";
            anyPending = true;
        }
    }

    if (!anyPending) {
        std::cout << "Нет неподтвержденных пользователей.\n";
        return;
    }

    std::cout << "Введите номер пользователя для подтверждения или 0 для выхода: ";
    int index;
    std::cin >> index;

    if (index > 0 && index <= accounts.size()) {
        if (accounts[index - 1].access == 0) {
            accounts[index - 1].access = 1;
            std::ofstream fout(filename);
            for (const auto& acc : accounts) {
                fout << acc.login << ";" << acc.password << ";" << acc.role << ";" << acc.access << "\n";
            }
            fout.close();
            std::cout << "Пользователь подтвержден.\n";
        }
        else {
            std::cout << "Этот пользователь уже подтвержден.\n";
        }
    }
}
void showAllAccounts(const std::vector<Account>& accounts) {
    if (accounts.empty()) {
        std::cout << "Список учетных записей пуст.\n";
        return;
    }

    std::cout << "\n--- Список всех учетных записей ---\n";
    std::cout << std::left
        << std::setw(5) << "№"
        << std::setw(20) << "Логин"
        << std::setw(20) << "Пароль"
        << std::setw(15) << "Роль"
        << std::setw(15) << "Статус" << "\n";
    std::cout << std::string(75, '-') << "\n";

    for (int i = 0; i < accounts.size(); ++i) {
        std::string roleStr = accounts[i].role == 1 ? "Админ" : "Пользователь";
        std::string accessStr = accounts[i].access == 1 ? "Подтвержден" : "Ожидает";

        std::cout << std::setw(5) << i + 1
            << std::setw(20) << accounts[i].login
            << std::setw(20) << accounts[i].password
            << std::setw(15) << roleStr
            << std::setw(15) << accessStr << "\n";
    }

    std::cout << std::string(75, '-') << "\n";
}

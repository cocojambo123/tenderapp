#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h> 
#include <iomanip>
#include "file_constants.h"
struct Account {
    std::string login;
    std::string password;
    int role;
    int access;
};
void readAccountsFromFile(std::vector<Account>& accounts);
void writeAccountToFile(const Account& acc);
void writeAllAccountsToFile(const std::vector<Account>& accounts);
//bool deleteAccountByLogin(const std::string& loginToDelete);
void deleteAccount(std::vector<Account>& accounts);
void confirmationAccounts(std::vector<Account>& accounts, const std::string& filename);
void showAllAccounts(const std::vector<Account>& accounts);
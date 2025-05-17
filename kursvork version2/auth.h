#pragma once
#include "account.h";
#include "io_utils.h";
#include "file_constants.h"

void createAdminIfFileNotExist();
std::string inputPasswordMasked();
int authorize(const std::vector<Account>& accounts, const std::string& login, const std::string& password);
void registerAccount(std::vector<Account>& accounts);
void addAccount(std::vector<Account>& accounts);
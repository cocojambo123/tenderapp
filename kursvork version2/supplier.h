#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h> 
#include <iomanip>
#include "file_constants.h"
#include "io_utils.h"
#include <algorithm>
#include <cctype>
struct Supplier {
    std::string name;
    std::string product;
    int quantity;
    int pricePerUnit;
    int totalPrice;
    int delivery_days;
};

void showAllSuppliers(const std::vector<Supplier>& suppliers);
void addSupplier(std::vector<Supplier>& suppliers, const std::string& filename);
void readSuppliersFromFile(std::vector<Supplier>& suppliers, const std::string& filename);
void writeSuppliersToFile(const std::vector<Supplier>& suppliers, const std::string& filename);
void deleteSupplier(std::vector<Supplier>& suppliers, const std::string& filename);
void editSupplier(std::vector<Supplier>& suppliers, const std::string& filename);
void searchSuppliers(const std::vector<Supplier>& suppliers);
void sortSuppliers(std::vector<Supplier>& suppliers);
void findFastestSupplier(const std::vector<Supplier>& suppliers);
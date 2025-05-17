#include "io_utils.h"

void intInput(int& data, const std::string message, int start, int end) {
    while (true) {
        std::cout << message;
        std::cin >> data;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������: ������� ����� �����.\n";
        }
        else if (std::cin.peek() != '\n') {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������: ���� ������ ��������� ������ ���� ����� ��� �������� ��� ��������.\n";
        }
        else if (data < start || data > end) {
            std::cout << "������: ����� ������ ���� � ��������� �� " << start << " �� " << end << ".\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}


void safeStringInput(std::string& input, const std::string& message) {
    bool flag = true;
    while (flag) {
        std::cout << message;
        std::getline(std::cin, input);

        bool valid = !input.empty() && input.find_first_not_of(" \t") != std::string::npos;
        if (!valid) {
            std::cout << "���� �� ����� ���� ������. ��������� ����.\n";
        }
        else {
            flag = false;
        }
    }
}

void withoutSpacesInput(std::string& password, std::string message) {
    bool flag = true;
    while (flag) {
        std::cout << message;
        std::cin >> password;

        if (std::cin.peek() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n+------------------------------------------------------+";
            std::cout << "\n|  ������������ ����! ����� ������ ���� ��� ��������  |\n";
            std::cout << "+------------------------------------------------------+\n";
        }
        else {
            flag = false;
        }
    }
}
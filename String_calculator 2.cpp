#include "functions.hpp"

int main()
{
    setlocale(0, "Russian");
    std::string infix = "";
    std::vector<std::string> rpn;
    std::string temp = "";
    float x;
    for (;;) {
        std::cout << "Введите ваш пример: ";
        std::getline(std::cin, infix);
        if (infix.empty()) {
            break;
        }
        if (std::count(infix.begin(), infix.end(), 'x') > 0) {
            std::cout << "В ваше примере вы указали переменную x. Укажите чему равен x: ";
            std::getline(std::cin, temp);
        }
        if (temp != "") {
            x = std::stof(temp);
        }
        else {
            x = 0;
        }
        try {
            transform_infix(infix);
            rpn = into_RPN(infix);
            std::cout << "Результат: " << calculate_rpn(rpn, x) << std::endl << std::endl;
        }
        catch (const char* error_message) {
            std::cout << error_message << std::endl;
        }
    }
    return 0;
}
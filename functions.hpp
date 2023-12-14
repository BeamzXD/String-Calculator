#include "include_functions.hpp"

std::string delete_space(const std::string& infix) {  //Удаляет лишние пробелы из строки
    std::string ans = "";
    for (auto& el : infix) {
        if (el != ' ') {
            ans += el;
        }
    }
    return ans;
}

void transform_infix(std::string& infix) {    //Превращает минусы, означающие отрицательные значения, а не вычитание в функцию
    infix = delete_space(infix);
    std::string operators = "+-*/^nsgp";
    if (infix[0] == '-') {
        infix[0] = 'm';
    }
    char temp = ' ';
    if ((infix[0] != '(') && (infix[0] != ')')) {
        temp = infix[0];
    }
    for (int i = 1; i < infix.size(); ++i) {
        if (temp != ' ') {
            if ((infix[i] == '-') && (std::find(operators.begin(), operators.end(), temp) != operators.end())) {
                infix[i] = 'm';
            }
            if ((infix[i] != '(') && (infix[i] != ')')) {
                temp = infix[i];
            }
        }
        else {
            if (infix[i] == '-') {
                infix[i] = 'm';
            }
            if ((infix[i] != '(') && (infix[i] != ')')) {
                temp = infix[i];
            }
        }
    }
}

float math_one(const float& x, const std::string& operator_) {  //Функция выполняющая функцию над аргументом
    std::map<std::string, int> ops = { {"m", 1}, {"sin", 2}, {"cos", 3}, {"tg", 4}, {"tg", 5}, {"exp", 6} };
    int var = ops[operator_];
    switch (var) {
    case 1:
        return (x * (-1));
    case 2:
        return sin(x);
    case 3:
        return cos(x);
    case 4:
        return tan(x);
    case 5:
        return 1 / tan(x);
    case 6:
        return exp(x);
    }
}

float math_two(const float& x, const float& y, const std::string& operator_) {  //Функция выполняющая опреации с операндами
    std::map<std::string, int> ops = { {"+", 1}, {"-", 2}, {"*", 3}, {"/", 4}, {"^", 5} };
    int var = ops[operator_];
    switch (var) {
    case 1:
        return x + y;
    case 3:
        return x * y;
    case 4:
        if (!y) {
            throw "Деление на ноль. Пожалуйста, попробуйте снова";
        }
        return x / y;
    case 2:
        return x - y;
    case 5:
        return pow(x, y);
    }
}

std::vector<std::string> into_RPN(const std::string& infix) { //Функция для переводa инфиксной нотации в обратную польскую (постфиксную)
    
    std::string alph = "qwertyuiopasdfghjklzxcvbnm";
    std::vector<std::string> functions = { "sin", "cos", "tg", "ctg", "exp" };
    std::vector<std::string> constants = { "pi", "e", "x" };
    std::vector<std::string> minus = { "m" };
    std::vector<std::string> nums = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "." };
    std::stack<std::string> operator_stack;
    std::map<std::string, int> operators = { {"+", 2}, {"-", 2}, {"*", 1}, {"/", 1}, {"^", 0}, {"m", -1} };
    std::vector<std::string> rpn;
    for (int i = 0; i < infix.size(); ++i) {
        if (std::find(minus.begin(), minus.end(), infix.substr(i, 1)) != minus.end()) {
            operator_stack.push(infix.substr(i, 1));
        }
        else if (operators.count(infix.substr(i, 1))) {
            while ((operator_stack.size()) && (operator_stack.top() != "(") &&
                (operators[infix.substr(i, 1)] >= operators[operator_stack.top()])) {
                rpn.push_back(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.push(infix.substr(i, 1));
        }
        else if (infix[i] == '(') {
            operator_stack.push(infix.substr(i, 1));
        }
        else if (infix[i] == ')') {
            if (operator_stack.size() == 0) {
                throw "Последовательность скобок во введенном выражении неверна. Пожалуйста, попробуйте снова";
            }
            while (operator_stack.top() != "(") {
                rpn.push_back(operator_stack.top());
                operator_stack.pop();
                if (operator_stack.size() == 0) {
                    throw "Последовательность скобок во введенном выражении неверна. Пожалуйста, попробуйте снова";
                }
            }
            operator_stack.pop();
            if (operator_stack.size()) {
                if (std::find(minus.begin(), minus.end(), operator_stack.top()) != minus.end()) {
                    rpn.push_back(operator_stack.top());
                    operator_stack.pop();
                }

            }
        }
        else if (std::find(nums.begin(), nums.end(), infix.substr(i, 1)) != nums.end()) {
            std::string temp = "";
            temp += infix.substr(i, 1);
            while (std::find(nums.begin(), nums.end(), infix.substr(i + 1, 1)) != nums.end()) {
                ++i;
                temp += infix.substr(i, 1);
            }
            rpn.push_back(temp);
        }
        else if (alph.find(infix.substr(i, 1)) != std::string::npos) {
            std::string temp = "";
            temp += infix.substr(i, 1);
            while (alph.find(infix.substr(i + 1, 1)) != std::string::npos) {
                ++i;
                temp += infix.substr(i, 1);
                if (i > infix.size() - 1) {
                    break;
                }
            }
            if ((std::find(constants.cbegin(), constants.cend(), temp)) != constants.end()) {
                rpn.push_back(temp);
            }
            else if ((std::find(functions.cbegin(), functions.cend(), temp)) != functions.end()) {
                operator_stack.push(temp);
            }
            else {
                throw "У вас есть входное постоянное значение или функция, которую этот калькулятор не поддерживает. Пожалуйста, попробуйте снова";
            }
        }
    }
    while (operator_stack.size()) {
        if (operator_stack.top() == "(") {
            throw "Последовательность скобок во введенном выражении неверна. Пожалуйста, попробуйте снова";
        }
        rpn.push_back(operator_stack.top());
        operator_stack.pop();
    }
    return rpn;
}

float calculate_rpn(const std::vector<std::string>& rpn, const float& x) {   //Функция подсчёта
    std::vector<float> operand_stack;
    std::map<std::string, int> operators_count = { {"+", 2}, {"-", 2}, {"*", 2}, {"/", 2}, {"^", 2},  {"m", 1}, {"sin", 1}, {"cos", 1}, {"tg", 1}, {"ctg", 1}, {"exp", 1} };
    std::vector<float> temp;
    for (int i = 0; i < rpn.size(); ++i) {
        if (!operators_count.count(rpn[i])) {
            if (rpn[i] == "pi") {
                operand_stack.push_back(M_PI);
            }
            else if (rpn[i] == "e") {
                operand_stack.push_back(M_E);
            }
            else if (rpn[i] == "x") {
                operand_stack.push_back(x);
            }
            else {
                operand_stack.push_back((std::stof(rpn[i])));
            }
        }
        else {
            if ((operators_count[rpn[i]] > operand_stack.size())) {
                throw "В вашем выражении допущена ошибка. Пожалуйста, попробуйте снова";
            }
            for (int j = operators_count[rpn[i]] - 1; j > -1; --j) {
                temp.push_back(operand_stack[operand_stack.size() - 1 - j]);
            }
            for (int j = operators_count[rpn[i]] - 1; j > -1; --j) {
                operand_stack.pop_back();
            }
            if (operators_count[rpn[i]] == 2) {
                operand_stack.push_back(math_two(temp[0], temp[1], rpn[i]));
            }
            else {
                operand_stack.push_back(math_one(temp[0], rpn[i]));
            }
            temp.clear();
        }
    }
    return operand_stack.back();
}
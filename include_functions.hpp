#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

std::string delete_space(const std::string& infix);
void transform_infix(std::string& infix);
float math_one(const float& x, const std::string& operator_);
float math_two(const float& x, const float& y, const std::string& operator_);

std::vector<std::string> into_RPN(const std::string& infix);

float calculate_rpn(const std::vector<std::string>& rpn, const float& x);


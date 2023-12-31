/*
 * @Author: Tairan Gao
 * @Date:   2023-12-30 20:05:51
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-12-30 20:09:12
 */
#include <iostream>
#include <string>

int main() {



    std::cout << char('a' & '_') << '\n';
    std::cout << char('A' | ' ') << '\n';
    std::cout << char('a' ^ ' ') << '\n';
    std::cout << char('A' ^ ' ') << '\n';

    return 0;
}
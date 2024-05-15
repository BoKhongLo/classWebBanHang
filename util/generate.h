#ifndef GENERATE_H
#define GENERATE_H
#include <iostream>
#include <string>
#include <random>

using namespace std;

// Hàm tạo chuỗi ngẫu nhiên có độ dài khoảng 10 ký tự
string generateRandomString(string smth) {
    const int length = 10;
    string randomString;

    // Sử dụng smth làm lõi (seed) cho thiết lập ngẫu nhiên
    mt19937 gen(smth.length());
    uniform_int_distribution<> dis('a', 'z'); // Số ngẫu nhiên trong khoảng ASCII của các ký tự chữ cái thường

    // Tạo chuỗi ngẫu nhiên
    for (int i = 0; i < length; ++i) {
        randomString += static_cast<char>(dis(gen));
    }

    return randomString;
}

#endif
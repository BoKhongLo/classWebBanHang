#ifndef ENCODE_H
#define ENCODE_H

#include <iostream>
#include <string>

using namespace std;

// Hàm mã hóa chuỗi sử dụng Caesar cipher với một khoảng dịch trượt
string caesarCipherEncrypt(const string &input, int shift = 3) {
    string encrypted = input;
    // Duyệt qua từng ký tự trong chuỗi đầu vào
    for (char &ch : encrypted) {
        // Kiểm tra xem ký tự có phải là chữ cái không
        if (isalpha(ch)) {
            // Xác định khoảng dịch chuyển cho ký tự chữ cái (0-25)
            int offset = isupper(ch) ? 'A' : 'a';
            // Mã hóa ký tự bằng cách dịch chuyển
            ch = static_cast<char>((ch - offset + shift) % 26 + offset);
        }
    }
    return encrypted;
}

// Hàm giải mã chuỗi sử dụng Caesar cipher với một khoảng dịch trượt
string caesarCipherDecrypt(const string &input, int shift = 3) {
    // Để giải mã, chỉ cần sử dụng dịch chuyển âm của hàm mã hóa
    return caesarCipherEncrypt(input, -shift);
}
#endif
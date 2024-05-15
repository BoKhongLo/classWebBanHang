#ifndef AUTH_H
#define AUTH_H
#include "util/find.h"
#include "dto.h"
#include "user.h"
#include <bits/stdc++.h>
using namespace std;
class User;
class Auth
{
public:
    static bool validateUser(string userID)
    {
        if (getValueFromFile("data/user.txt", userID, 11,0) == "1")
        {
            return true;
        }
        return true;
    }

    static otp_token sendOTP(string id)
    {
        string otp = generateRandomString(id);
        string refreshToken = generateRandomString(id + "refresh_token");
        string accessToken = generateRandomString(id + "access_token");
        WriteFile("data/otp.txt", id, otp, refreshToken, accessToken);
        otp_token out{otp, refreshToken};
        return out;
    }
    static bool VerifyOtp(string n_otp, string id)
    {
        string otp_correct = getValueFromFile("data/otp.txt", id, 1,0);
        if (otp_correct == n_otp)
        {
            return true;
        }
        return false;
    }

    static void signUp(User &user, dangkyDto dto)
    {
        if (containsStringAtPosition("data/user.txt", dto.email, 4))
        {
            cout << "user already exited" << endl;
        }
        else
        {
            user.setUsername(dto.name);
            user.setAddress(dto.address);
            user.setPhoneNumber(dto.phoneNumber);
            user.setEmail(dto.email);
            user.setGender(dto.gender);
            user.genHash(dto.password);
            user.generateIdAuto(dto.name + dto.password);
            otp_token otp_token_out = Auth::sendOTP(user.getUserId());
            user.genRoomIdAuto(user.getUserId());
            cout << "YOUR'S OTP CODE: " << otp_token_out.otp << endl;
            string input_otp_code;
            cout << "Enter your otp code" << endl;
            cout << "> ";
            cin >> input_otp_code;
            if (VerifyOtp(input_otp_code, user.getUserId()))
            {
                user.setRefreshToken(otp_token_out.refresh_token);
                user.setIsAuthenticated(true);
                cout << "Sign Up Success" << endl;
                user.save();
            }
            else
            {
                cout << "Check your Otp code please!" << endl;
            }
        }
    }
    static void login(dangNhapDto dto)
    {
        string file = "data/user.txt";
        if (containsStringAtPosition(file, dto.email, 4) and containsStringAtPosition(file, caesarCipherEncrypt(dto.password), 2))
        {
            cout << "Login Success" << endl;
        }
        else
        {
            cout << "Login Failure" << endl;
        }
    }
};
#endif
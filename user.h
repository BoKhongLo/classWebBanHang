#include <cart.h>
#include <bits/stdc++.h>
#include <ctime>
#include <vector>

using namespace std;

class User
{
private:
    string idUser;
    bool isDisplay;
    string hash;
    string refresh_token;
    vector<string> role;
    int memberExp;
    tm updateAt;
    tm createdAt;
    string cartId;
    string roomId;
    string idCart;
    string memberLevel;
    
    string generateIdUser(){
        return "";
    }
    string getUpdateTime(){
        return "";
    }
    



public:
    string username;
    string email;
    string phoneNumber;
    string imgDisplay;
    tm birthday;
    string address;
    string gender;

    // User(string username, string email, string phoneNumber, string imgDisplay, string address, string gender;) {
    //     this->username = username;
    //     this->email = email;
    //     this->phoneNumber = phoneNumber;
    //     this->imgDisplay = imgDisplay;
    //     this->address = address;
    //     this->gender = gender;
    //     this->idUser = 0;
    // }
    User() {}
}
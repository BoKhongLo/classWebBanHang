#include <product.h>
#include <bits/stdc++.h>
#include <ctime>

using namespace std;

class IRoomchat{
private:
    string id, userId;
    bool isDisplay, isBlock;
    vector<string> memberRoomchat;
    vector<IMessages> messages;
    time_t updateAt, createdAt;
};
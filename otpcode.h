#include <bits/stdc++.h>
#include <ctime>

using namespace std;

class IOtp{
private:
    string id, email, otpCode, type;
    bool value, isDisplay;
    time_t updateAt, createdAt;
};
#include <user.h>
#include <bits/stdc++.h>
#include <ctime>

using namespace std;

class ICartItem {
private:
    string productId;
    int quantity;
public:
    
};

class ICart {
private:
    string id, userId;  
    vector<ICartItem> items;
    double totalPrice, totalItemCount;
    IDeliveryInfo shippingAddress;
    time_t updateAt, createdAt;
};


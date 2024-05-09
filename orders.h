#include <user.h>
#include <product.h>
#include <bits/stdc++.h>
#include <ctime>

using namespace std;

class IOrder{
private:
    string id, userId, status, notes;
    bool isDisplay;
    double totalAmount;
    vector<IProduct> listProducts;
    IDeliveryInfo deliveryInfo;
    time_t updateAt, createdAt;
};

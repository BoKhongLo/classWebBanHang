#ifndef PRODUCT_H
#define PRODUCT_H

#include <bits/stdc++.h>
#include <ctime>
#include <iostream>
using namespace std;

class Product
{
private:
    string productId;
    int quantity, heart;
    double price;
    string productName;
    bool isDisplay, sales;
    double cost;
    string productType;
    string color;
    string size;
    int buyCount;
    string detail;
    string description;

public:
    Product()
    {
        this->productId = "product 0";
        this->quantity = 1;
        this->price = 1;
    }
    Product(string id, int quantity, double price)
    {
        this->productId = id;
        this->quantity = quantity;
        this->price = price;
    };

    bool operator==(const Product &other) const
    {
        return (productId == other.productId &&
                quantity == other.quantity &&
                price == other.price);
    }
    void setProductId(const string &id) { productId = "Product_"+ generateRandomString(id+"product"); }
    void setProductIdDump(const string &id) { productId = id;}
    void setQuantity(int q) { quantity = q; }
    void setHeart(int h) { heart = h; }
    void setPrice(double p) { price = p; }
    void setProductName(const string &name) { productName = name; }
    void setIsDisplay(bool display) { isDisplay = display; }
    void setSales(bool s) { sales = s; }
    void setCost(double c) { cost = c; }
    void setProductType(const string &type) { productType = type; }
    void setColor(const string &c) { color = c; }
    void setSize(const string &s) { size = s; }
    void setBuyCount(int count) { buyCount = count; }
    void setDetail(const string &d) { detail = d; }
    void setDescription(const string &desc) { description = desc; }

    string getProductId() const { return productId; }
    int getQuantity() const { return quantity; }
    int getHeart() const { return heart; }
    double getPrice() const { return price; }
    string getProductName() const { return productName; }
    bool getIsDisplay() const { return isDisplay; }
    bool getSales() const { return sales; }
    double getCost() const { return cost; }
    string getProductType() const { return productType; }
    string getColor() const { return color; }
    string getSize() const { return size; }
    int getBuyCount() const { return buyCount; }
    string getDetail() const { return detail; }
    string getDescription() const { return description; }
    friend ostream &operator<<(ostream &os, const Product &item)
    {
        os << "Product ID: " << item.productId << ", Quantity: " << item.quantity << ", Price: " << item.price;
        return os;
    }
    void save()
    {
        WriteFile("data/product.txt", this->productId,this->productName, this->price, this->quantity, this->productType, this->size, this->color, this->detail);
    }
};

#endif
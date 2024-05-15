#ifndef CART_H
#define CART_H
#include "util/find.h"
#include "util/generate.h"
#include "product.h"
#include <bits/stdc++.h>
#include <ctime>
#include <iostream>
using namespace std;
class Cart
{
private:
    string idCart, userId;
    vector<Product> items;
    double totalPrice, totalItemCount;
    time_t updateAt, createdAt;

public:
    Cart(string userID)
    {
        this->idCart = "Card_"+ generateRandomString(this->userId + "cart");
        this->userId = userID;
        this->totalPrice = calculateItemCount() || 0;
        this->totalItemCount = calculateItemCount() || 0;
    }
    Cart() : idCart(""), userId(""), items(), totalPrice(0.0), totalItemCount(0.0) {}
    // Getter for idCart
    string getIdCart() const
    {
        return idCart;
    }

    // Setter for idCart
    void setIdCart(const string &idCart)
    {
        this->idCart = idCart;
    }

    // Getter for userId
    string getUserIdCart() const
    {
        return userId;
    }

    // Setter for userId
    void setUserIdCart(const string &userId)
    {
        this->userId = userId;
    }

    // Setter for items
    void setItems(const vector<Product> &items)
    {
        this->items = items;
    }

    // Getter for totalPrice
    double getTotalPrice() const
    {
        return totalPrice;
    }

    // Setter for totalPrice
    void setTotalPrice(double totalPrice)
    {
        this->totalPrice = totalPrice;
    }

    // Getter for totalItemCount
    double getTotalItemCount() const
    {
        return totalItemCount;
    }

    // Setter for totalItemCount
    void setTotalItemCount(double totalItemCount)
    {
        this->totalItemCount = totalItemCount;
    }
    double calculatePrice()
    {
        double sum = 0.0;
        for (Product item : this->items)
        {
            sum += item.getPrice(); // Lấy giá của mỗi sản phẩm và cộng vào tổng
        }
        return sum;
    }
    double calculateItemCount()
    {
        return this->items.size();
    }
    void showItems()
    {
        for (Product item : this->items)
        {
            cout << item << endl;
        }
    }

    void updateCart(string choice, string idProduct, int quantity)
    {
        bool found = false;

        // Duyệt qua từng Product trong vector items
        for (auto &item : items)
        {
            if (item.getProductId() == idProduct) // Kiểm tra xem item có mã sản phẩm idProduct không
            {
                found = true;
                if (choice == "remove")
                {
                    // Xóa item nếu quantity cần xóa lớn hơn hoặc bằng số lượng hiện có
                    if (quantity >= item.getQuantity())
                    {
                        items.erase(remove(items.begin(), items.end(), item), items.end());
                    }
                    else
                    {
                        // Giảm số lượng của item nếu quantity < số lượng hiện có
                        item.setQuantity(item.getQuantity() - quantity);
                    }

                    // Cập nhật lại tổng số tiền và tổng số lượng
                    totalPrice -= item.getPrice() * quantity;
                    totalItemCount -= quantity;
                }
                else if (choice == "add")
                {
                    // Tăng số lượng của item
                    item.setQuantity(item.getQuantity() + quantity);
                    // Cập nhật lại tổng số tiền và tổng số lượng
                    totalPrice += item.getPrice() * quantity;
                    totalItemCount += quantity;
                }
                break; // Kết thúc vòng lặp sau khi xử lý item
            }
        }
        if (!found && choice == "add")
        {
            // Nếu không tìm thấy item có mã sản phẩm idProduct và choice là "add"
            // Thêm mới một Product vào vector items
            Product newItem(idProduct, quantity, 0); // Tạo mới Product với giá 0
            items.push_back(newItem);
            // Cập nhật lại tổng số tiền và tổng số lượng
            totalPrice += newItem.getPrice() * quantity;
            totalItemCount += quantity;
        }
    }
    void save()
    {
        string item_in_cart;
        for(Product item : this->items){
            item_in_cart += item.getProductId() += ',';
        }
        WriteFile("data/cart.txt", this->idCart, this->userId, item_in_cart, this->totalPrice, this->totalItemCount);
    }
    friend ostream &operator<<(ostream &os, const Cart &cart)
    {
        os << "Cart ID: " << cart.idCart << ", User ID: " << cart.userId << endl;
        os << "Items in Cart:" << endl;
        for (const Product &item : cart.items)
        {
            os << item << endl; // Utilize operator<< of Product
        }
        os << "Total Price: " << cart.totalPrice << endl;
        os << "Total Item Count: " << cart.totalItemCount << endl;
        return os;
    }
};
#endif
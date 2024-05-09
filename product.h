#include <auth.h>
#include <cart.h>
#include <bits/stdc++.h>
#include <ctime>

using namespace std;

class IMessages{
private:
    string id, typeMegs, userId, roomId, title, content;
    vector<string> urlFile;
    double star;
    time_t updateAt, createdAt;
};

class ISales{
private:
    bool isSales;
    double percents;
    time_t end;
};
struct addProductdto{
    string productName, productType, description, userID;
    double cost, price, stockQuantity;
};
struct removeProductdto{
    string productId;
};

class ListProduct{
private:
    vector<IProduct> data;
public:
    // thêm sản phẩm vào giỏ hàng
    IProduct addProduct (addProductdto dto, Auth auth){
        string userId;
        if(auth.validateUser(userId)){
            IProduct new_product;
            data.push_back(new_product);
            return new_product;
        }
        return NULL;
    }
    //xóa sản phẩm
    bool removeProduct(removeProductdto dto, Auth auth){
        string userId;
        if(auth.validateUser(userId)){
            IProduct product;
            data.remove(product);
            return true;
        }
        return false;
    }

};

class IProduct{
private:
    string id, productName, description, productType, detail;
    bool isDisplay;
    double cost, price, stockQuantity, buyCount, rating;
    vector<string> imgDisplay, pattern;
    vector<IMessages> commentsList;
    ISales sales;
    time_t updateAt, createdAt;
public:
    IProduct() : id(""), productName(""), description(""), productType(""), detail(""), isDisplay(false),
    cost(0.0), price(0.0), stockQuantity(0.0), buyCount(0.0), rating(0.0), imgDisplay(vector<string>()), sales(ISales()), updateAt(0), createdAt(0){}

    //lấy thông tin sản phẩm
    IProduct getInfo(string productId){
        IProduct productInfo;
        if(productId == id){
            productInfo.id = id;
            productInfo.productName = productName;
            productInfo.description = description;
            return productInfo;
        }
        return NULL;
    }
};


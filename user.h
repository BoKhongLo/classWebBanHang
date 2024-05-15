#ifndef USER_H
#define USER_H

#include "dto.h"
#include "cart.h"
#include <bits/stdc++.h>
#include <ctime>
#include <fstream>
#include "util/generate.h"
#include "util/encode.h"
using namespace std;
class Cart;
class DeliveryInfo
{
private:
  string name, phoneNumber, address;

public:
  DeliveryInfo(string name = "", string phoneNumber = "", string address = "")
      : name(name), phoneNumber(phoneNumber), address(address) {}
  bool operator==(const DeliveryInfo &other) const
  {
    return (name == other.name && phoneNumber == other.phoneNumber && address == other.address);
  }
  string toString() const
  {
    ostringstream oss;
    oss << name << "#" << phoneNumber << "#" << address;
    return oss.str();
  }
  friend ostream &operator<<(ostream &os, const DeliveryInfo &deliveryInfo)
  {
    os << '{' << endl;
    os << "   " << "Delivery Information for: " << deliveryInfo.name << endl;
    os << "   " << "phoneNumber: " << deliveryInfo.phoneNumber << endl;
    os << "   " << "address: " << deliveryInfo.address << endl;
    os << '}';
    return os;
  }
};

class User
{
private:
  string userId, username, firstName, lastName,
      hash, refresh_token, email, address, gender,
      memberLevel, roomId;

  bool isDisplay, isAuthenticated;

  string phonenumber[5];
  string role[2] = {"user"};

  DeliveryInfo deliveryInfoList;

  time_t updateAt, createdAt;
  Cart myCart;

public:
  User() : userId(""), username(""),
           refresh_token(""), email(""), address(""), gender(""), hash(""),
           memberLevel(""), isAuthenticated(false), updateAt(0), createdAt(0)
  {
    myCart.setIdCart("Card_" + generateRandomString(this->userId + "cart"));
    myCart.setUserIdCart(this->userId);
    myCart.setTotalItemCount(0);
    myCart.setTotalPrice(0);
    myCart.save();
  }
  void setUsername(const string &value) { this->username = value; }
  void setRefreshToken(const string &value) { this->refresh_token = value; }
  void setEmail(const string &value) { this->email = value; }
  void setAddress(const string &value) { this->address = value; }
  void setGender(const string &value) { this->gender = value; }
  void setMemberLevel(const string &value) { this->memberLevel = value; }
  void setRoomId(const string &value) { this->roomId = value; }
  void setIdCart(const string &value) { this->myCart.setIdCart(value); }
  void setIsDisplay(bool value) { this->isDisplay = value; }
  void setIsAuthenticated(bool value) { this->isAuthenticated = value; }
  // ================================ SET RÔN =================================================================
  void setRole(const string &value)
  {
    append(this->role, 2, value);
  }
  // ================================ SET RÔN =================================================================
  void setPhoneNumber(const string &value)
  {
    append(this->phonenumber, 5, value);
  }
  void setDeliveryInfo(DeliveryInfo delivery)
  {
    this->deliveryInfoList = delivery;
  }

  // Getters
  string getUserId() const { return userId; }
  string getUsername() const { return username; }
  string getFirstName() const { return firstName; }
  string getLastName() const { return lastName; }
  string getHash() const { return hash; }
  string getRefreshToken() const { return refresh_token; }
  string getEmail() const { return email; }
  string getAddress() const { return address; }
  string getGender() const { return gender; }
  string getMemberLevel() const { return memberLevel; }
  string getRoomId() const { return roomId; }
  string getIdCart() const { return myCart.getIdCart(); }
  bool getIsDisplay() const { return isDisplay; }
  bool getIsAuthenticated() const { return isAuthenticated; }

  void showMyCart()
  {
    cout << "====== Your's Cart ======" << endl;
    cout << "Cart ID: ";
    cout << "User ID: " << getValueFromFile("data/cart.txt", getIdCart(), 1, 1) << endl;
    cout << "items: " << endl;
    myCart.showItems();
  }

  void generateIdAuto(string name)
  {
    this->userId = "User_" + generateRandomString(name);
  }
  string genId(string name)
  {
    return "User_" + generateRandomString(name);
  }
  void genHash(string pass)
  {
    this->hash = caesarCipherEncrypt(pass);
  }
  void genRoomIdAuto(string id)
  {
    this->roomId = "room" + generateRandomString(id);
  }
  // void editProfileService(editProfileDto dto)
  // {
  //   setUsername(dto.name);
  //   setAddress(dto.address);
  //   setEmail(dto.email);
  //   setPhoneNumber(dto.phoneNumber);
  //   setDeliveryInfo(dto.deliveryInfo);
  // }

  void addHeartProductService(int heart, const string &productId)
  {
    // Kiểm tra giá trị heart phải từ 1 đến 5
    if (heart < 1 || heart > 5)
    {
      cerr << "Heart value must be between 1 and 5." << endl;
      return;
    }

    // Đọc nội dung file data.txt
    ifstream inFile("data/review.txt");
    if (!inFile)
    {
      cerr << "Failed to open file for reading." << endl;
      return;
    }

    vector<string> lines;
    string line;
    bool found = false;
    bool exactMatch = false;

    while (getline(inFile, line))
    {
      istringstream iss(line);
      string pid, uid;
      int h;

      // Định dạng ban đầu của dòng là 'productId#userId#heart'
      size_t firstHash = line.find('#');
      size_t lastHash = line.rfind('#');

      if (firstHash != string::npos && lastHash != string::npos && firstHash != lastHash)
      {
        pid = line.substr(0, firstHash);
        uid = line.substr(firstHash + 1, lastHash - firstHash - 1);
        h = stoi(line.substr(lastHash + 1));

        if (pid == productId && uid == userId)
        {
          if (h == heart)
          {
            exactMatch = true;
          }
          else
          {
            line = productId + "#" + userId + "#" + to_string(heart);
          }
          found = true;
        }
      }
      lines.push_back(line);
    }

    inFile.close();

    if (exactMatch)
    {
      cout << "Exact match found. No changes made." << endl;
      return;
    }

    if (!found)
    {
      lines.push_back(productId + "#" + userId + "#" + to_string(heart));
    }

    // Ghi lại nội dung file data.txt
    ofstream outFile("data/review.txt");
    if (!outFile)
    {
      cerr << "Failed to open file for writing." << endl;
      return;
    }

    for (const auto &l : lines)
    {
      outFile << l << endl;
    }

    outFile.close();

    cout << "Updated rating: " << productId << "#" << userId << "#" << heart << endl;
  }

  void removeHeartProductService(const string &productId)
  {
    ifstream inFile("data/review.txt");
    if (!inFile)
    {
      cerr << "Failed to open file." << endl;
      return;
    }
    vector<string> lines;
    string line;
    bool found = false;

    while (getline(inFile, line))
    {
      istringstream iss(line);
      string existingProductId, existingUserId, existingHeart;
      if (getline(iss, existingProductId, '#') &&
          getline(iss, existingUserId, '#') &&
          getline(iss, existingHeart))
      {
        if (existingProductId == productId)
        {
          found = true;
          continue;
        }
      }
      lines.push_back(line);
    }
    inFile.close();
    if (!found)
    {
      cout << "No rating found for product: " << productId << endl;
      return;
    }
    ofstream outFile("data/review.txt");
    if (!outFile)
    {
      cerr << "Failed to open file for writing." << endl;
      return;
    }
    for (const string &updatedLine : lines)
    {
      outFile << updatedLine << endl;
    }
    outFile.close();
    cout << "Removed all ratings for product: " << productId << endl;
  }
  void save() const
  {
    // Convert all data to a string
    ostringstream oss;
    oss << this->userId << "#" << this->username << "#" << this->hash
        << "#" << refresh_token << "#"
        << email << "#" << address << "#" << gender << "#" << memberLevel << "#"
        << roomId << "#" << this->myCart.getIdCart() << "#" << isDisplay << "#"
        << isAuthenticated << '#' << toString(role, 2) << "#" << toString(phonenumber, 5);

    oss << "#" << updateAt << "#" << createdAt;
    string newData = oss.str();
    // Open file in read mode to check for duplicates
    ifstream infile("data/user.txt");
    if (!infile.is_open())
    {
      throw runtime_error("Unable to open file for reading");
    }

    string line;
    bool isDuplicate = false;
    while (getline(infile, line))
    {
      if (line == newData)
      {
        isDuplicate = true;
        break;
      }
    }
    infile.close();

    // Only write to file if the data is not a duplicate
    if (!isDuplicate)
    {
      ofstream file("data/user.txt", ios::app);
      if (!file.is_open())
      {
        throw runtime_error("Unable to open file for writing");
      }

      file << newData << endl;
      file.close();
    }
  }

  void showProduct()
  {
    cout << "========================================================================= CAC SAN PHAM HIEN CO =========================================================================" << endl;
    string filename = "data/product.txt";
    vector<string> columnNames = {"idProduct", "ten san pham", "gia (VND)", "so luong con lai", "Kieu", "size", "color", "brand"};
    printFormattedTable(filename, columnNames);
  }
  void updateCart(string choice, string idProduct, int quantity)
  {
    myCart.updateCart(choice, idProduct, quantity);
    myCart.save();
  }
  static void editProduct(editproductDto dto)
  {
    Product newProduct;
    newProduct.setProductId(dto.userId);
    newProduct.setProductName(dto.nameProduct);
    newProduct.setPrice(dto.price);
    newProduct.setQuantity(dto.quantity);
    newProduct.setSize(dto.size);
    newProduct.setColor(dto.color);
    newProduct.setDetail(dto.detail);
    newProduct.setProductType(dto.style);
    newProduct.save();
  }
  static void addProduct(addProductDto dto)
  {
    Product newProduct;
    newProduct.setProductId(dto.userId);
    newProduct.setProductName(dto.nameProduct);
    newProduct.setPrice(dto.price);
    newProduct.setQuantity(dto.quantity);
    newProduct.setSize(dto.size);
    newProduct.setColor(dto.color);
    newProduct.setDetail(dto.detail);
    newProduct.setProductType(dto.style);
    newProduct.save();
  }
  static void deleteProduct(const deleteproductDto& dto) {
    std::ifstream inFile("data/product.txt");
    std::vector<std::string> lines; // Dùng vector để lưu trữ các dòng từ tệp

    if (!inFile) {
        std::cerr << "Không thể mở tệp product.txt để đọc.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        // Tìm dòng chứa productName cần xóa
        if (line.find(dto.productID) != std::string::npos) {
            continue; // Bỏ qua dòng chứa productName cần xóa
        }
        lines.push_back(line); // Lưu trữ các dòng không bị xóa vào vector
    }

    inFile.close();

    std::ofstream outFile("data/product.txt");
    if (!outFile) {
        std::cerr << "Không thể mở tệp product.txt để ghi.\n";
        return;
    }

    for (const std::string& l : lines) {
        outFile << l << std::endl; // Ghi lại các dòng không bị xóa vào tệp mới
    }

    outFile.close();
}
  void createOrder() {}
  void deleteOrder() {}
};

#endif
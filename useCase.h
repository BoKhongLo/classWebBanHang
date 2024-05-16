#ifndef USECASE_H
#define USECASE_H
#include "cart.h"
#include "product.h"
#include "user.h"

#include "auth.h"
#include <iostream>
using namespace std;
void dangky(User &user, dangkyDto ttuser1)
{
  Auth::signUp(user, ttuser1);
}
void dangnhap(dangNhapDto dto)
{
  Auth::login(dto);
}
void themSanPham(addProductDto dto)
{
  if (Auth::validateUser(dto.userId))
  {
    User::addProduct(dto);
    cout << "Product saved" << endl;
  }
  else
  {
    cout << " Failed, you are not allowed" << endl;
  };
}

void suaSanPham(editproductDto dto)
{
  if (Auth::validateUser(dto.userId))
  {
    User::editProduct(dto);
    cout << "Edit Product saved" << endl;
  }
  else
  {
    cout << " Failed, you are not allowed" << endl;
  };
}

void xoaSanPham(deleteproductDto dto)
{
  if (Auth::validateUser(dto.userId))
  {
    User::deleteProduct(dto);
    cout << "delete Product saved" << endl;
  }
  else
  {
    cout << " Failed, you are not allowed" << endl;
  };
}

void taoOrder(User user)
{
  string in;
  int in_quantity;
  string size;
  string color;

  string listId;
  int quantity;
  int price;

  while (true)
  {
    user.showOrder();
    user.showMyCart();
    cout << "Nhan done de hoan thanh don hang" << endl;
    cout << "nhap id cua san pham ban muon cho vao don hang: ";
    cin >> in;

    if (in == "done")
    {
      user.showOrder();
      break;
    }
    cout << "Nhap so luong: ";
    cin >> in_quantity;
    cout << "nhap size: ";
    cin >> size;
    cout << "nhap mau: ";
    cin >> color;

    quantity += in_quantity;
    listId += in;
    price += stoi(getValueFromFile("data/product.txt", in, 2, 0));
    user.showOrder();
    product_quantity_sumPrice kv{
        listId,
        quantity,
        price,
        size,
        color};
    user.createOrder(kv, user.getUserId());
    system("cls");
  }
}
void showNguoiDung(User &user)
{
  if (Auth::validateUser(user.getUserId()))
  {
    cout << "========================================================================= CAC NGUOI DUNG HIEN CO =========================================================================" << endl;
    std::vector<int> selectedColumns = {1, 4, 6, 7, 9, 12, 13}; // Lựa chọn các cột mà người dùng muốn in ra
    vector<string> columnNames = {"Id user", "Username", "EMAIL", "GENDER", "LEVEL", "CARD_ID", "role", "phone"};
    printSelectedColumns("data/user.txt", columnNames, selectedColumns);
  }
  else
  {
    cout << "you are not allowed" << endl;
  }
}

void setRolebyId(User user,const string id,string role){
  if (Auth::validateUser(user.getUserId())){
  replaceValueInFile("data/user.txt",id,12,role);
    cout << "set role successfully" << endl;
  }else{
    cout << "you are not allowed" << endl;
  }
}
#endif
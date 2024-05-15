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

void xoaSanPham(deleteproductDto dto){
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

#endif
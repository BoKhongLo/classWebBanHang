#ifndef DTO_H
#define DTO_H
#include "user.h"
#include <bits/stdc++.h>
using namespace std;

struct dangkyDto
{
  string name;
  string phoneNumber;
  string gender;
  string email;
  string address;
  string password;
};

struct otp_token
{
  string otp;
  string refresh_token;
};
struct dangNhapDto
{
  string email;
  string password;

};
struct addProductDto{
  string userId;
  string nameProduct;
  double price;
  int quantity;
  string style;
  string size;
  string color;
  string detail;
};

struct editproductDto{
  string userId;
  string productID;
  string nameProduct;
  double price;
  int quantity;
  string style;
  string size;
  string color;
  string detail;
};

struct deleteproductDto{
  string userId;
  string productID;
};
#endif
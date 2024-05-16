#include "cart.h"
#include "product.h"
#include "user.h"
#include "useCase.h"
#include "auth.h"
#include <iostream>
#include <cstdlib> // for system()

using namespace std;

int main()
{
    system("cls");
    User user1;
    dangkyDto ttuser1{
        "nguoi1",
        "0376585282",
        "nam",
        "user@gmail.com",
        "So nha 15, Ngo 250 Kim Giang, Dai Kim Hoang Mai Ha Noi",
        "abc123"};
    dangNhapDto user1_dangNhap{
        "user@gmail.com",
        "abc123"};
    addProductDto addDTO{
        user1.getUserId(),
        "Quan Bo Adidos",
        100000,
        1000,
        "Ong suong",
        "S M L XL XXL",
        "Xanh Do Tim Den",
        "Quan xin"};
    editproductDto editDTO{
        user1.getUserId(),
        "Product_bfuilzslzi",
        "Quan Bo Adidos",
        100000,
        1000,
        "Ong suong",
        "S M L XL XXL",
        "Xanh Do Tim Den",
        "Quan xin"};
    deleteproductDto delDTO{
        user1.getUserId(),
        "Product_bfuilzslzi"};
    // ===================== AUTH ========================
    // dangky(user1, ttuser1);
    // dangnhap(user1_dangNhap);

    // //===================== tra cú=====================
    // // user1.showProduct();

    // // // ===================== quản lý giỏ hàng ========================
    // user1.updateCart("add", "product1", 10);
    // // user1.showMyCart();
    // user1.updateCart("add", "product2", 10);
    // // user1.showMyCart();

    // ===================== quản lý SẢN PHẨM ========================
    // cout << " them san pham moi" <<endl;
    // themSanPham(addDTO);
    // user1.showProduct();

    // cout << " sua san pham theo id" <<endl;
    // suaSanPham(editDTO);
    // user1.showProduct();

    // cout << " xoa san pham theo id" <<endl;
    // xoaSanPham(delDTO);
    // user1.showProduct();

    // ===================== quản lý ĐƠN HÀNG ========================
    // taoOrder(user1);
    // user1.showOrder();
    // ===================== quản lý NGƯỜI DÙNG (ADMIN) ========================
    // showNguoiDung(user1);
    // setRolebyId(user1,"User_opsvpwowlq", "admin,user");
    return 0;
}
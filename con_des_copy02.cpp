#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;


class Product {

public:
    char *name;
    char *icon;
    double price;
public:
    //构造函数，默认有一个无参构造函数，重写了之后默认构造函数就失效
    Product(char *name,char *icon,double price){
        int len=strlen(name);
        //此处申请内存加1,有一个\0的结束符
        this->name=(char*)malloc(len+1);
        strcpy(this->name,name);
        this->icon=icon;
        this->price=price;

    }

    //默认拷贝构造函数不会拷贝动态内存空间，浅拷贝
//    Product(const Product &p){
//        this->name=p.name;
//        this->icon=p.icon;
//        this->price=p.price;
//
//    }

    Product(const Product &p){
        // 如果在构造函数中申请了动态内存，重写拷贝构造函数也需要申请一个动态内存空间
        // 不然回收动态内存空间的时候会报错
        int len=strlen(p.name);
        this->name=(char *)malloc(len+1);
        strcpy(this->name,p.name);
        cout<<"copy"<<endl;
        this->icon=p.icon;
        this->price=p.price;

    }

    void print(){
        cout<<"name="<<this->name<<",icon="<<this->icon<<",price="<<this->price<<endl;

    }

    //析构函数
    //在对象生命周期结束之前调用，最后执行的函数
    ~Product(){
        cout<<"析构函数"<<endl;
        //释放this->name的动态内存空间
        free(this->name);
    }

};

//int main(){
//
//
//    Product p("宝马","三角状",300000);
//    p.print();
//    //拷贝构造
//    Product p1(p);
//
//    p1.print();
//
//    printf("p的name:%#x,p1的name:%#x\n",p.name,p1.name);
//
//    strcpy(p.name,"xx");
//
//    p1.print();
//    p.print();
//    return 0;
//}

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
    //���캯����Ĭ����һ���޲ι��캯������д��֮��Ĭ�Ϲ��캯����ʧЧ
    Product(char *name,char *icon,double price){
        int len=strlen(name);
        //�˴������ڴ��1,��һ��\0�Ľ�����
        this->name=(char*)malloc(len+1);
        strcpy(this->name,name);
        this->icon=icon;
        this->price=price;

    }

    //Ĭ�Ͽ������캯�����´����̬�ڴ�ռ䣬ǳ����
//    Product(const Product &p){
//        this->name=p.name;
//        this->icon=p.icon;
//        this->price=p.price;
//
//    }

    Product(const Product &p){
        // ����ڹ��캯���������˶�̬�ڴ棬��д�������캯��Ҳ��Ҫ����һ����̬�ڴ�ռ�
        // ��Ȼ���ն�̬�ڴ�ռ��ʱ��ᱨ��
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

    //��������
    //�ڶ����������ڽ���֮ǰ���ã����ִ�еĺ���
    ~Product(){
        cout<<"��������"<<endl;
        //�ͷ�this->name�Ķ�̬�ڴ�ռ�
        free(this->name);
    }

};

//int main(){
//
//
//    Product p("����","����״",300000);
//    p.print();
//    //��������
//    Product p1(p);
//
//    p1.print();
//
//    printf("p��name:%#x,p1��name:%#x\n",p.name,p1.name);
//
//    strcpy(p.name,"xx");
//
//    p1.print();
//    p.print();
//    return 0;
//}

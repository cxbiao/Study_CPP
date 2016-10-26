#include <iostream>
#include <stdio.h>
using namespace std;


//C++的类成员默认私有
namespace CPP_CLASS {

    class Animal{
    private:
        char *name;
        int age;
    public:
        void setName(char *name){
            this->name=name;
        }
        void setAge(int age){
            this->age=age;
        }

        void showInfo(){

            cout<<"姓名: "<<this->name<<" 年龄: "<<this->age<<endl;
        }

    };

}

//C++中的结构体可以定义函数，成员可以有权限修饰符，默认是公有public
//struct不能继承
namespace CPP_STRUCT {

    struct Person{

    private:
        char *name;
        int age;
    public:
        void setName(char *name){
            this->name=name;
        }
        void setAge(int age){
            this->age=age;
        }

        void showPersonInfo(){

            cout<<"姓名: "<<this->name<<" 年龄: "<<this->age<<endl;
        }


    };


}


namespace CPP_QUOTE {

    class Quote {

    public:
        int x=10;

        //引用只作为变量的别名，没有单独的内存空间
        void swip(int &a,int &b){
            int c=0;
            c=a;
            a=b;
            b=c;
        }

        //指针交换
        void swip_p(int *a,int *b){
            int c=0;
            c=*a;
            *a=*b;
            *b=c;

        }


    };

}

using namespace CPP_CLASS;
using namespace CPP_STRUCT;
using namespace CPP_QUOTE;

void useCppClass(){

    Animal animal;
    animal.setName("dog");
    animal.setAge(2);
    animal.showInfo();
}


void useCppStruct(){

    Person p;
    p.setName("zero");
    p.setAge(20);
    p.showPersonInfo();
}


void useCppQuote(){

    Quote q;
    //q1是q的别名
    Quote &q1=q;
    q1.x=100;
    printf("q的内存地址:%#x,q1的内存地址:%#x\n",&q,&q1);
    cout<<"q=="<<q.x<<endl;
    int x=20,y=40;
    q1.swip(x,y);
    cout<<"q swipe x="<<x<<" y= "<<y<<endl;

    //指针交换
    q1.swip_p(&x,&y);
    cout<<"指针值交换:   x="<<x<<"  y=  "<<y<<endl;

}
//int main(){
//
//    useCppClass();
//    useCppStruct();
//    useCppQuote();
//    return 0;
//}

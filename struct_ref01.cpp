#include <iostream>
#include <stdio.h>
using namespace std;


//C++�����ԱĬ��˽��
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

            cout<<"����: "<<this->name<<" ����: "<<this->age<<endl;
        }

    };

}

//C++�еĽṹ����Զ��庯������Ա������Ȩ�����η���Ĭ���ǹ���public
//struct���ܼ̳�
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

            cout<<"����: "<<this->name<<" ����: "<<this->age<<endl;
        }


    };


}


namespace CPP_QUOTE {

    class Quote {

    public:
        int x=10;

        //����ֻ��Ϊ�����ı�����û�е������ڴ�ռ�
        void swip(int &a,int &b){
            int c=0;
            c=a;
            a=b;
            b=c;
        }

        //ָ�뽻��
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
    //q1��q�ı���
    Quote &q1=q;
    q1.x=100;
    printf("q���ڴ��ַ:%#x,q1���ڴ��ַ:%#x\n",&q,&q1);
    cout<<"q=="<<q.x<<endl;
    int x=20,y=40;
    q1.swip(x,y);
    cout<<"q swipe x="<<x<<" y= "<<y<<endl;

    //ָ�뽻��
    q1.swip_p(&x,&y);
    cout<<"ָ��ֵ����:   x="<<x<<"  y=  "<<y<<endl;

}
//int main(){
//
//    useCppClass();
//    useCppStruct();
//    useCppQuote();
//    return 0;
//}

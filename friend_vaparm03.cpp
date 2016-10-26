#include <iostream>
#include <stdarg.h>
using namespace std;


class Song {

private:
    char *name;
public:
    Song(char *name){
        this->name=name;
        cout<<"Song的构造函数"<<endl;
    }
    char* getName(){
        return this->name;
    }
    ~Song(){

        cout<<"Song的析构函数"<<endl;
    }

};


class Music {

private:
    char *musicName;
    Song s;
public:
    // 如果类中存在对象字段，而这个对象需要传入构造函数参数，则需要在当前类构造函数)后面：进行赋值初始化
    Music(char* musicName,char* songName):s(songName){
        this->musicName=musicName;
        cout<<"Music的构造函数"<<endl;
    }

    void printInfo(){

        cout<<"歌曲: "<<this->musicName<<endl;
        cout<<"歌手: "<<this->s.getName()<<endl;
    }
    ~Music(){

         cout<<"Music的析构函数"<<endl;
    }


};

class Flower {


protected:
    int id;
    char *name;
public:
    Flower(int id,char *name){

        this->id=id;
        this->name=name;
    }

    void printInfo(){

        cout<<"id= "<<this->id<<"   name="<<this->name<<endl;
    }


};

class Rose:public Flower {

public:
    Rose(int id,char *name):Flower(id,name){

    }
    void printInfo(){

        cout<<"id= "<<this->id<<"   name="<<name<<"--"<<endl;
    }


};


//使用new创建对象
void useNewKeyCreateObject(){

    Music *m=new Music("决口不提","李明");
    m->printInfo();
    delete m;

}

void useInherit(){

    Rose r(1,"rose");
    r.printInfo();

}


//继承的二义性
class A {

public:
    char *name;

};

class A1:virtual public A{

};

class A2:virtual public A{

};

class B:public A1,public A2{

};


void useTwoInherit(){
    B b;
    b.name="zero";
    //指定父类显示调用
    b.A1::name="zero";
    b.A2::name="zero";


}



//友元函数可以访问一个类的任何字段和函数
class FriendFunction {


//创建一个友元函数,用来访问私有字段，需要在外部实现函数
friend void accessFriendFunctionField(FriendFunction *p,int id,char *name);
//友元类 ， 友元类可以访问此类任意字段和函数
friend class FriendClass;

// 类私有字段 , 私有字段，常规访问需要创建public get的访问函数 , 不能进行直接访问
private:
    int id;
    char *name;
public:
    FriendFunction(int id,char *name){
        this->id=id;
        this->name=name;

    }
     void printfInfo() {
        cout << "id = " << this->id << "   name = " << this->name << endl;
    }


};

 //作为类的友元类,可以修改类中任意字段也函数
class FriendClass{

private:
    FriendFunction *f;
public:
    FriendClass(FriendFunction *f){
        this->f=f;
    }
    void accessFriendField(){

        f->id=100;
        f->name="友元类修改";
    }

};

//友元函数
void accessFriendFunctionField(FriendFunction *p,int id,char *name){
    p->id=id;
    p->name=name;

}

//友元函数使用
void useFriendFunction(){

    FriendFunction *f=new FriendFunction(1,"找不到你的方向");
    f->printfInfo();

    accessFriendFunctionField(f,3,"我是你娘");
    f->printfInfo();


    //java中的Class对象，可以访问任意对象的任意字段，本质是Class类每个类的友元类
    FriendClass fc(f);
    fc.accessFriendField();
    f->printfInfo();

}


//可变参数
class VariableParameter {

public:
    void varParams(int i,...){
        //可变参数列表
        va_list ap_list;
        //从...之前的第一个参数开始，后面就是可变参数
        va_start(ap_list,i);
        //得到可变参数，参数1为可变参数列表，参数2为参数类型
        int age=va_arg(ap_list,int);
        double weight=va_arg(ap_list,double);
        char *registry=va_arg(ap_list,char*);
        va_end(ap_list);

         cout << "编号: " << i << " 年龄： " << age << " 体重： " << weight << "  籍贯： " << registry << endl;
    }

};

//使用可变参数
/**
C++的可变参数，必须含有一个固定参数，可变参数类型不固定，
可以是任意数据类型，通过va_arg()函数指定数据类型 。

*/
void useVarParams(){
    VariableParameter v;
    v.varParams(1,20,132.36,"广州");
}
int main(){

    useNewKeyCreateObject();
    useInherit();
    useTwoInherit();
    useFriendFunction();
    useVarParams();
    return 0;
}

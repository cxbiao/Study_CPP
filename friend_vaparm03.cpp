#include <iostream>
#include <stdarg.h>
using namespace std;


class Song {

private:
    char *name;
public:
    Song(char *name){
        this->name=name;
        cout<<"Song�Ĺ��캯��"<<endl;
    }
    char* getName(){
        return this->name;
    }
    ~Song(){

        cout<<"Song����������"<<endl;
    }

};


class Music {

private:
    char *musicName;
    Song s;
public:
    // ������д��ڶ����ֶΣ������������Ҫ���빹�캯������������Ҫ�ڵ�ǰ�๹�캯��)���棺���и�ֵ��ʼ��
    Music(char* musicName,char* songName):s(songName){
        this->musicName=musicName;
        cout<<"Music�Ĺ��캯��"<<endl;
    }

    void printInfo(){

        cout<<"����: "<<this->musicName<<endl;
        cout<<"����: "<<this->s.getName()<<endl;
    }
    ~Music(){

         cout<<"Music����������"<<endl;
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


//ʹ��new��������
void useNewKeyCreateObject(){

    Music *m=new Music("���ڲ���","����");
    m->printInfo();
    delete m;

}

void useInherit(){

    Rose r(1,"rose");
    r.printInfo();

}


//�̳еĶ�����
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
    //ָ��������ʾ����
    b.A1::name="zero";
    b.A2::name="zero";


}



//��Ԫ�������Է���һ������κ��ֶκͺ���
class FriendFunction {


//����һ����Ԫ����,��������˽���ֶΣ���Ҫ���ⲿʵ�ֺ���
friend void accessFriendFunctionField(FriendFunction *p,int id,char *name);
//��Ԫ�� �� ��Ԫ����Է��ʴ��������ֶκͺ���
friend class FriendClass;

// ��˽���ֶ� , ˽���ֶΣ����������Ҫ����public get�ķ��ʺ��� , ���ܽ���ֱ�ӷ���
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

 //��Ϊ�����Ԫ��,�����޸����������ֶ�Ҳ����
class FriendClass{

private:
    FriendFunction *f;
public:
    FriendClass(FriendFunction *f){
        this->f=f;
    }
    void accessFriendField(){

        f->id=100;
        f->name="��Ԫ���޸�";
    }

};

//��Ԫ����
void accessFriendFunctionField(FriendFunction *p,int id,char *name){
    p->id=id;
    p->name=name;

}

//��Ԫ����ʹ��
void useFriendFunction(){

    FriendFunction *f=new FriendFunction(1,"�Ҳ�����ķ���");
    f->printfInfo();

    accessFriendFunctionField(f,3,"��������");
    f->printfInfo();


    //java�е�Class���󣬿��Է����������������ֶΣ�������Class��ÿ�������Ԫ��
    FriendClass fc(f);
    fc.accessFriendField();
    f->printfInfo();

}


//�ɱ����
class VariableParameter {

public:
    void varParams(int i,...){
        //�ɱ�����б�
        va_list ap_list;
        //��...֮ǰ�ĵ�һ��������ʼ��������ǿɱ����
        va_start(ap_list,i);
        //�õ��ɱ����������1Ϊ�ɱ�����б�����2Ϊ��������
        int age=va_arg(ap_list,int);
        double weight=va_arg(ap_list,double);
        char *registry=va_arg(ap_list,char*);
        va_end(ap_list);

         cout << "���: " << i << " ���䣺 " << age << " ���أ� " << weight << "  ���᣺ " << registry << endl;
    }

};

//ʹ�ÿɱ����
/**
C++�Ŀɱ���������뺬��һ���̶��������ɱ�������Ͳ��̶���
�����������������ͣ�ͨ��va_arg()����ָ���������� ��

*/
void useVarParams(){
    VariableParameter v;
    v.varParams(1,20,132.36,"����");
}
int main(){

    useNewKeyCreateObject();
    useInherit();
    useTwoInherit();
    useFriendFunction();
    useVarParams();
    return 0;
}

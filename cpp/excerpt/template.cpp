#include <iostream>
#include <vector>

using namespace std;

// 模版：模板是泛型编程的基础，泛型编程即以一种独立于任何特定类型的方式编写代码。
// 关键点：采用占位符T，在函数或者类中用T声明的类型，则在使用该函数或者类的时候，T可以改为对应的具体的类型.



//######################## 模版函数:对传入的参数和返回的参数做泛型处理 ##############################
template <typename T>
T maxp(T a, T b)
{
    return a>b ? a : b;
}

//######################## 模版类:在类名后面加上<T>是表示要先实例化一个对应T类型的对象 ##############################
template <class T>
class Stack  //这里竟然又不在类名后加<T>：类声明
{
    private:
        vector<T> elems;

    public:
        void push(T elem);
        T get();
        
};
template <class T>
void Stack<T>::push(T elem)
{
   elems.push_back(elem); 
}
template <class T>
T Stack<T>::get()
{
    return elems.back();
}

int main()
{

    int p = maxp(10, 12);
    cout << "max is :" << p << endl;

    Stack<int> st;   //需要先实例化成对应类型的对象.
    st.push(10);
    int pp = st.get();
    cout << "Stack elem: " << pp << endl; 
}

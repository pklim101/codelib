## C++

## 一、简介.
- (1) 特点
1. 静态类型:在编译时执行类型检查，而不是在运行时执行类型检查.
2. 编译式；
3. 大小写敏感；
4. 不规则；
5. 支持过程化编程；
6. 支持面向对象编程；
7. 支持泛型编程。
8. 被认为是一种中级语言，它综合了高级语言和低级语言的特点；
9. 最初命名为带类的C，后来更名为C++；
10. C++是C的一个超集，实际上，任何合法的C程序都是合法的C++程序.
11. C++程序可以定义为对象的集合，这些对象通过调用彼此的方法进行交互.

- (2) 面向对象
1. C++完全支持面向对象的程序设计；
2. 面向对象开发四大特性：封装、抽象、继承、多态.

- (3) 标准库
1. 核心语言：变量、常量、数据类型等;
2. C++标准库：提供了大量函数;
3. 标准模版库(STL),提供了大量的方法，用于操作数据结构等.

- (4) ANSI标准

- (5) 如何学C++
1. 理解概念；

- (6) 应用
1. 编写设备驱动程序;
2. 要求实时性的直接操作硬件的软件；

## 二、环境
1. 软件：
- 文本编辑器：源代码，后缀名为：.cpp  .cp  .c；
- C++编译器；将源代码转为机器语言，编译成最终可执行的程序. GNU - C/C++.

2. 安装GNU的C/C++编译器.
- 检查是否已经安装了GCC：
```bash
g++ -v
```

- g++是将gcc的默认语言设为C++的一个特殊版本，链接时它自动使用C++标准库而不是C标准库.

3. 源代码
```cpp
#include <iostream>
using namespace std;
int main()
{
    cout << "Hello,world!" << endl;
    return 0;
}
```

4. 编译:
```bash
g++ start.cpp
g++ start.cpp -o start
```

- 多个C++代码文件的编译方式：
```bash
g++ start1.cpp cpp start2.cpp -o start
```

5. 执行
```bash
./a.out
```
6. g++常用命令选项
- -std=c++1 ： 指定使用C++11来编译main.cpp文件;
- -Wall ： 生成所有警告信息.

## 三、基本语法
1. 面向对象
- 对象：具有状态+行为；
- 类：对象的抽象;
- 方法：即行为;
- 即时变量：对象的状态是由即时变量的值差un关键的.

2. typedef声明
- typedef int feet; //给int取一个别名为feet

3. 变量初始化：正确地初始化变量是一个良好的编程习惯，否则有时候程序可能会产生意想不到的结果。
- 当局部变量被定义时，系统不会对其初始化，您必须自行对其初始化。
- 定义全局变量时，系统会自动初始化为各类型对应的值。

4. 常量(也叫字面量)
- (1)整数常量:
- 0x:十六进制；0:八进制；十进制:不带前缀；
- 整数常量后缀U:无符号整型；L:长整型；(大小写均可;UL组合顺序任意)

- (2)浮点常量:
- 指数用e或E表示；

- (3)布尔常量:【不应该把true的值看成是1，把false的值看成是0】
- true
- false

- (4)字符常量:字符常量是括在单引号中.
- 以L开头(如L‘'x')，表示宽字符常量；存储在wchar_t类型中；
- 普通(如'x')，表示窄字符常量，存储在char类型中;
- 字符常量可以的值有:普通('x')、转义('\t')、通用字符('\u02C0')。

- (5)字符串常量:字符串常量是括在双引号中.

- 定义常量的方式：将常量定义为大写形式是一个很好的编程习惯.
- <1>使用#define预处理器；#define WIDTH 5
- <2>使用const关键字: const int WIDTH = 5;

5. 修饰符类型：
- signed
- unsigned
- long
- short

- 注意：速记符号
- unsigned short、unsigned long中，int是隐含的； unsigned x等同于unsigned int x;

- 类型限定符
- const:const类型的对象在程序执行期间不能被改变；
- volatile:volatile告诉编译器，变量的值可能以程序未明确指定的方式被改变；
- restrict:由restrict修饰的指针，访问它所指向的对象.

6. 存储类：定义程序中变量/函数的范围(可见性)和声明周期.
- auto(C++11中不再是存储类说明符)：根据表达式自动推断被声明的变量的类型；
- register(C++11已弃用)：存储在寄存器中的局部变量；如计数器；
- static：
- extern：多个文件共享相同的全局变量和函数；
- mutable
- thread_local(C++11)：生命周期仅在其线程上.

7. 运算符
- 常用：加减乘除...
- 杂项：sizeof()；三元运算?:；逗号运算符；成员运算符->；强制转换运算符(int)a；指针运算符&和*.

8. 函数
```cpp
//函数声明
int max(int, int);
//函数定义
int max(int num1, int num2) 
{
   // 局部变量声明
   int result;
 
   if (num1 > num2)
      result = num1;
   else
      result = num2;
 
   return result; 
}
```

- Lambda：
- [capture](parameters)->return-type{body}

9. 数组：存储一个固定大小、相同类型元素的顺序集合。
- 声明数组：double balance[3];
- 数组初始化：balance = {3.1,2.1,5.1};

10. 字符串
- C风格字符串：本质上是使用null字符'\0'终止的一维字符数组.
- C++引入的string类类型：#include <string>

11. 指针
- 1.简化编程任务；2.动态内存分配.

12. 引用：引用变量是一个已存在变量的别名.
- 对引用的理解：试想变量名称是变量附属在内存位置中的标签，您可以把引用当成是变量附属在内存位置中的第二个标签。因此，您可以通过原始变量名称或引用来访问变量的内容。
- 用法： 
```cpp
int& r = i;  //r是一个初始化为i的整型引用; 引用必须在创建时被初始化.
cout << r << endl;
```
- 引用的作用：
- (1)函数参数列表
- (2)函数返回值

13. 日期 & 时间
- C++继承了C语言用于日期和时间操作的结构和函数.
- #include <ctime>
- 四种类型：clock_t、time_t、size_t、tm
- tm结构类型:
```cpp
struct tm {
  int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
  int tm_min;   // 分，范围从 0 到 59
  int tm_hour;  // 小时，范围从 0 到 23
  int tm_mday;  // 一月中的第几天，范围从 1 到 31
  int tm_mon;   // 月，范围从 0 到 11
  int tm_year;  // 自 1900 年起的年数
  int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
  int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
  int tm_isdst; // 夏令时
}

```
- tm结构最常用
```cpp

#include <iostream>
#include <ctime>
 
using namespace std;
 
int main( )
{
   // 基于当前系统的当前日期/时间
   time_t now = time(0);
 
   cout << "1970 到目前经过秒数:" << now << endl;
 
   tm *ltm = localtime(&now);
 
   // 输出 tm 结构的各个组成部分
   cout << "年: "<< 1900 + ltm->tm_year << endl;
   cout << "月: "<< 1 + ltm->tm_mon<< endl;
   cout << "日: "<<  ltm->tm_mday << endl;
   cout << "时间: "<< ltm->tm_hour << ":";
   cout << ltm->tm_min << ":";
   cout << ltm->tm_sec << endl;
}
```

14. 基本输入输出
- C++中的I/O发生的流中，流是字节序列.
- 输入操作：字节流从设备(如键盘、磁盘驱动器、网络连接等)流向内存；
- 输出操作：字节流从内存流向设备(如显示屏、打印机、磁盘驱动器、网络连接等).
- 重要的IO库：
- (1) <iostream>：cin、cout、cerr、clog
- (2) <iomanip>：参数化流操作.
- (3) <fstream>：文件操作.

- 对cout的理解：预定义的对象 cout 是 iostream 类的一个实例。cout 对象"连接"到标准输出设备，通常是显示屏。cout 是与流插入运算符 << 结合使用的. 如：cout << "Value of str is : " << "HHH" << endl;
- 用cerr流来显示错误信息，而其它日志消息则使用clog流来输出是良好的编程习惯(因为cerr无缓冲，错误能立即显示出来)

15. 结构struct
```cpp
//声明一个结构类型为Books，变量为book.
struct Books 
{
   char  title[50];
   char  author[50];
   char  subject[100];
   int   book_id;
} book; 

//成员访问运算符(.)

//指向结构的指针
struct Books *sp;//定义指向结构的指针
sp = &book1;     //将结构变量的地址赋值给结构指针变量
book1->book_id;  //用结构指针访问结构成员.
```
- typedef关键字
```cpp
typedef struct Books
{
   char  title[50];
   char  author[50];
   char  subject[100];
   int   book_id;
}Books;
Books Book1, Book2;
```


## 四、面向对象
1. 类中的数据和方法是类的成员.
2. 定义一个类，本质上是定义了一个数据类型的蓝图.
3. 类的定义和声明
```cpp
//类的定义

class Box
{
    public:
        double length;
        double width;
        double height;
    
        Box(); //构造函数：构造函数的名称与类的名称完全相同，并且不会返回任何类型，也不会返回void.    
        ~Box(); //这是析构函数声明：析构函数的名称与类的名称完全相同，只是加了前缀~；它不会返回任何值，也不能带任何参数.

        double getVolume(void)
        {
            return length * width * height;
        }
};
Box::box(double len)
{
    count << "Object is being created, length = "<< len << endl;
    length = len;
}
Box::~Box(void)
{
    cout << "Object is being deleted" << endl;
}
double Box::getVolume(void)  //域区分符(::)，志明一个函数或数据属于哪个类;前面没类名，表示全局数据或全局函数(即非成员函数)
{
    return length * width * height;
}
//声明类的对象，就像声明基本类型的变量一样.
Box Box1;          // 声明 Box1，类型为 Box
Box Box2;          // 声明 Box2，类型为 Box
//访问数据成员 ：成员访问符(.)
Box1.height = 5.0;
cout << Box1.height << endl;
```

4. 继承：可以派生自多个基类
- 形式：class derived-class: access-specifier base-class
- 派生类不会继承的情况：
- (1)基类的构造函数、析构函数、拷贝构造函数；
- (2)基类的重载运算符;
- (3)基类的友元函数.

- 多继承
```cpp
class <派生类名>:<继承方式1><基类名1>,<继承方式2><基类名2>,…
{
<派生类类体>
};
```

5. 重载
- 概念：在同一作用域内，声明几个功能类似的同名函数，但这些同名函数的形式参数(参数的个数、类型、顺序)必须不同.
- 分类:函数重载、运算符重载(operator+)

6. 多态
- 概念：调用成员函数时，会根据调用函数的对象的类型来执行不同的函数. 
- 静态链接(早绑定)：调用的是基类的函数；
- 动态链接(后期绑定)：在基类的函数前加virtual声明；根据所调用的对象类型来选择调用的函数.
- 纯虚函数:virtual int area() = 0;(= 0 告诉编译器，函数没有主体)；可能想要在基类中定义虚函数，以便在派生类中重新定义该函数更好地适用于对象.


7. 数据抽象
- 数据抽象是一种依赖于接口和实现分离的编程设计技术. 是把实现细节和相关数据分离开的概念.
- public/protect提供对外接口，private提供具体底层实现.

8. 数据封装
- 数据封装是一种把数据和操作数据的函数捆绑在一起的机制
- 数据抽象是一种仅向用户暴露接口而把具体的实现细节隐藏起来的机制

9. 接口
- 概念：接口描述了类的行为和功能，而不需要完成类的特定实现.
- 如果类中至少有一个函数被声明为纯虚函数，则这个类就是抽象类。纯虚函数是通过在声明中使用 "= 0" 来指定的.
- 抽象类不能用于实例化对象，只能作为接口使用.
- 如果一个抽象类的子类需要被实例化，则必须实现每个虚函数.
- 为什么要有抽象类：为了给其他类提供一个可以继承的适当的基类，比如多态的应用.


五、高级应用
1. 文件和流
- ofstream,ifstream,fstream
- seekg(n,ios::cur),seekp(n,ios::cur) //ios::beg(默认)、ios::cur、ios::end

2. 异常处理
- throw、try、catch

3. 动态内存
- C++中的内存分为两部分：
- (1)栈：在函数内部声明的所有变量都将占用栈内存；
- (2)堆：在程序运行时可用于动态分配的内存.
- 分配和释放内存：
```cpp
#include <iostream>
using namespace std;
 
int main ()
{
   double* pvalue  = NULL; // 初始化为 null 的指针
   pvalue  = new double;   // 为变量请求内存
 
   *pvalue = 29494.99;     // 在分配的地址存储值
   cout << "Value of pvalue : " << *pvalue << endl;
 
   delete pvalue;         // 释放内存
 
   return 0;
}
```
4. 命名空间：即定义了上下文。本质上，命名空间就是定义一个范围.
```cpp
#include <iostream>
using namespace std;
 
namespace first_space{  //用namespace定义命名空间
   void func(){
      cout << "Inside first_space" << endl;
   }
}

using namespace first_space;

int main ()
{
 
   // 调用命名空间中的函数
   first_space::func();
    func(); //如果使用using namespace指令，在调用函数时可省略'first_space::'部分.
   return 0;
}
```

5. 模版：模版是泛型编程的基础.模版是创建泛型类或函数的蓝图或公式.

6. 预处理器
- 预处理器是一些指令，在编译之前完成的预处理；
- 所有的预处理器指令都是以#开头；
- 预处理器不是C++语句，所以不以分号结尾；
- 预处理指令有：#include、#define、#if、#else、#line等.
- #和##.
- 预定义宏：__LINE__、__FILE__、__DATE__、__TIME__

7. 信号处理：信号是由操作系统传给进程的中断，会提早终止一个程序.
- 捕获信号：void(*signal (int sig, void (*func)(int)))(int); 
- 生成信号：int raise (signal sig);

8. 多线程
- 区别：
    >>基于进程的多任务处理是程序的并发执行。
    >>基于线程的多任务处理是同一程序的片段的并发执行。
- 创建线程：pthread_create (thread, attr, start_routine, arg)
- 终止线程：pthread_exit (status) //如果通过该函数退出线程，则会等待所有线程退出后，main()才会结束.
- 连接线程：pthread_join (threadid, status) 
- 分离线程：pthread_detach (threadid)

- 使用-lpthread库编译：$ g++ test.cpp -lpthread -o test.o

9. web编程

## 五、资源库
1. STL：实现多重常用算法和数据结构.
- STL核心三组件：容器、算法、迭代器.

2. 标准库
- 标准库可分为两部分：
- (1)标准函数库：继承自C语言；
- (2)面向对象类库：类及其相关函数的集合.



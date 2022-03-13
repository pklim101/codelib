/*************************************************************************
    > File Name: 1.cpp
    > Author: tony
    > Mail: tony@z.com 
    > Created Time: 2019年05月20日 星期一 19时47分05秒
 ************************************************************************/
#include<iostream>
#include<time.h>
#include<unistd.h>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include <memory>
#include <chrono>
#include<stdint.h>
#include<algorithm>
#include<cmath>
#include<assert.h>
#include<unordered_map>
#include<thread>
#include<pthread.h>
#include<unordered_map>
#include<functional>
#include<limits>
#include<random>
#include<numeric>
#include<iomanip>
#include<typeinfo>
#include<string>
#include<cstring>
#include<fstream>
#include<iterator> //std::ostream_iterator
#include<iostream> //std::out
//#include<boost>
using namespace std;

void say(std::pair<const int32_t, int32_t>& m){
  cout<<m.first<<endl;
}

void say2(const int32_t &t){
  cout << t << endl;
}

void say3(std::map<int32_t,int32_t>::iterator x){
  cout << x->first <<endl;
}

void func(int32_t& a){
  cout << a << endl;
  a = 20;
  cout << a << endl;
}

void printStr(string& str) { //参数加const即可
  cout << str << endl;
}

void printInt(int& num) { //参数加const即可
  cout << num << endl;
}


class Test{
public:
  int hello(){
    cout << "hello,world!" <<endl;
  }
};

void vectorElementObjCall() {
  std::vector<Test> t;
  t[10].hello();
}

const char* xx(){
	const char* c;
	string s="1234";
	c = s.c_str(); 
	s = "fuck";
  cout << s.data() << endl;
	return c;
}

string str = "`hello word$,end!~@";
void replaceAllChar(string &str) {
  static std::set<char> key_board_char = {'`','~','!','@','#','$','%','^','&','*'};
  string::iterator iter;
  for(iter=str.begin(); iter!=str.end(); iter++){
    if(key_board_char.find(*iter)!=key_board_char.end()){
      str.erase(iter);
			iter--;
    }
  }
}

void noLockAtomic() {
	int count = 3;
	int ret = 0;
	ret = __sync_fetch_and_add(&count, 1);
  cout << count <<":" << ret << endl;
	ret = __sync_add_and_fetch(&count, 1);
  cout << count <<":" << ret << endl;
}

//解引用理解:https://www.cnblogs.com/junyidcf/archive/2011/02/24/1963769.html
//一句话理解：解引用是通过*p直接去访问指针指向的值,而不必经由地址去访问值.
//*p++：++优先级高于*;
void constTestInt() {
  const int a = 5;
  int* p;
  p = const_cast<int*>(&a);
  (*p)++;
  cout << a << endl;  //5
  cout << *p << endl; //6 原理貌似是*p就是一个映射到变量a分标量
}

void constTestArr() {
  const int a[] = {4,5,6};
  int* p;
  p = const_cast<int*>(a);
  *p++;
  cout << a[0] << endl;
  cout << *p << endl;
}

class InnerClass {
  public:
    int itype;
    void seeOut(){
    }
};
class OutClass {
  public:
  int otype;
  InnerClass ic; 
  void seeInt(){
    cout << "int:" << ic.itype << endl;
  }
};

struct Person{
  int32_t age;
  string name;
};

struct PersonHash {
	std::size_t operator()(const Person& p) const { //对‘(const PersonHash) (const Person&)’的调用没有匹配
		return std::hash<int32_t>()(p.age) + std::hash<string>()(p.name);
	}
};

struct PersonEqual {
	bool operator()(const Person& p1, const Person& p2) const {
		if(p1.age	== p2.age && p1.name == p2.name) {
			return true;
		}
		return false;
	}
};


typedef std::unordered_map<Person,int32_t,PersonHash, PersonEqual> Stu;
//typedef std::unordered_map<uint32_t,std::unordered_map<int32_t, KeywordSwapImage>> KSIMapDict;

typedef std::unordered_map<string, double> umap;

void unordered_map_test(){
  Person per;
  per.age = 10;
  per.name = "Tom";
  Stu* stu = new Stu;
  stu->insert(std::pair<Person, int32_t>(per, 123));
  Person per2;
  per2.age = 10;
  per2.name = "Tom";
  auto iter = stu->find(per2);
  if (iter != stu->end()) {
    cout << iter->first.age << iter->first.name << endl;
    cout << iter->second << endl;
  } else {
    cout << "Nof Found!" << endl;
  }
}
// unordered_map_test(); 输出:10Tom

struct Functional_obj {
  int age;
  string name;
  int operator()(int a) {
    return a;
  }
};
/**
  Functional_obj fobj;
  auto xx = fobj(20); //fobj是一个对象，用起来的语法像函数：传参.
*/
int32_t g_var = 0;
int32_t& refer(int32_t a){
  g_var = a;
  return g_var;
}
/**
  refer(10) = 20;
  cout << g_var << endl; //输出20

*/

int32_t hash_test(){
  std::hash<string> H;
  auto hs = H("hello");
  cout << hs << endl;
  return hs;
}

int32_t random_test(int32_t lower, int32_t upper) {
  uniform_int_distribution<int> distribution(lower,upper);
	random_device rd;
  default_random_engine generator(rd());
  return distribution(generator);
}
//auto dic = std::bind(random_test, 1, 6); dic();  使用bind参数的方式实现便捷的多次调用

int32_t random_device_test(){
	random_device rd; //声明一个random_device类型的变量rd
	return rd();   //operator() 返回生成的随机数
}

void getline_test(){
	std::string str;	
	getline(std::cin, str); //从标准输入获取数据并放入str中.
	cout << str << endl;
}

struct ACCU{
  int32_t operator()(int32_t sum, int32_t a){
    sum += a; 
    return sum;
  }
};
int32_t accu(int32_t sum, int32_t a){
  sum += a;
  return sum;
}
void numeric_test(){
  std::vector<int32_t> vec = {1,2,3,4,5};
  int32_t ret = accumulate(vec.begin(), vec.end(), 0);	
  cout << ret << endl;
  int32_t ret2 = accumulate(vec.begin(), vec.end(), 0, ACCU()); //ACCU()：用类名()的方式声明这是一个临时变量，为ACCU类对象.
  cout << ret2 << endl;
  int32_t ret3 = accumulate(vec.begin(), vec.end(), 0, accu); //accu是函数指针。因为函数名本身就是指针，指向了函数代码，函数的地址是函数的首地址，正如不带下标的数组名表示的是数组的首地址一样.
  cout << ret3 << endl;
}

void iomanip_test(){
    cout << std::setw(10) << "hello" << endl; //设置stream的filed宽，也就是加上"hello"后整个的宽，不够用空格填充.
}

void char_test(char* c){
  cout << c << endl;
}
/** 可重入函数: 可重入是指被多个任务同时调用，但是数据不会出现问题。
  recommin(); // 输出:10
  recommin(); // 输出:20
  //因为函数内有局部静态变量，函数是有状态的，多个任务调用数据会出异常.
*/
void recommin(){
  static int sum = 0;
  sum += 10;
  cout << "sum = " << sum << endl;
}

struct Leak{
  string name;
  int32_t age;
  int64_t sign;
};
void mem_leak(){
  while(true) {
    Leak tmp;
    tmp.name = "ccu是函数指针。因为函数名本身就是指针，指向了函数代码，函数的地址是函数的首地址，正如不带下标的数组名表示的是数组的首地址一样";
    Leak* leak = &tmp;

    //cout << "create Leak...size:" << sizeof(leak) << endl;
  }
}

/** 对象类型转换
  Type_cast tc;
  tc.a = 10;
  cout << int(tc) << endl;

*/
class Type_cast{
public:
  int a;
  operator int() { //不写成int operator int()是因为返回类型int被省略了
    return a;
  }
};

//void test_fun_void() const {  //非成员函数‘void test_fun_void()’不能拥有 cv 限定符
//
//}


/**
class PPP{
public:
  PPP(){
    cout << "ppp" << endl;
  }
};
class AAA{
public:
  AAA(){
    cout << "base" << endl;
  }
};

class BBB : public AAA {
public:
  BBB(){
    cout << "derive" << endl;
  }
private:
  PPP ppp;  //non-static成员变量会调用PPP的构造函数
  static PPP ps;//static成员变量不会调用PPP的构造函数
};
//BBB bbb; //父类AAA的构造函数也会被调用.
*/

/*
  AAA *bptr = new BBB;
  bptr->foo();
  delete bptr;
class AAA{
public:
  AAA(){
    cout << "base construct" << endl;
  }
  virtual void foo(){
    cout << "base foo()" << endl;
  }
  virtual ~AAA(){ //如果不是virtual析构函数，则经由base class指针删除的时候，不会析构derive对象。
    cout << "base virtual destroy." << endl;
  }
};

class BBB : public AAA {
public:
  BBB(){
    cout << "derive construct" << endl;
  }
  void foo(){
    cout << "derive foo()" << endl;
  }
  //如果不定义derive析构函数，则调用的是derive默认生成的析构函数,并不是从父类继承过来的析构函数,因为构造函数和析构函数不能被继承.
  ~BBB(){
    cout << "derive virtual destroy." << endl;
  }
};
*/

//溢出转换
void overflow_int(){
  uint64_t ppp = -9180528710595341107;
  cout << ppp << endl;
}

void boost_lambda(){
 // using namespace boost::lambda;
 // vector<int> vec = {1,2,3,5,9};
 // for_each(vec.begin(),vec.end(),std::cout<<_1*10<<"\n"<<endl);
}

//default_AAA da(3) : 对重载的‘default_AAA(int)’的调用有歧义
class default_AAA{
public:
  default_AAA(int a, int b=10){
    cout << a << "===" << b << endl;
  }
  default_AAA(int a){
    cout << a << "===" << endl;
  }
};

/*非成员函数解决类型隐式转换问题 
  SHAA saa(10);
  SHAA sab(20);
  SHAA res = saa * 2;
  SHAA res2 = 3*saa;
  SHAA res3 = 3*2;
  cout << res.count;
  cout << res2.count;
  cout << res3.count;
*/
class SHAA{
public:
  SHAA(int num){
    count = num;
  }
  int count;
  void foo(){
    cout << "foo" << endl;
  }
};

const SHAA operator*(const SHAA& lhs, const SHAA& rhs) {
  return lhs.count * rhs.count;
}
/* dynamic向下转换，可将base class pointor转换为derive class pointer,然后调用derive class的方法
  PPP* p = new PPP;
  QQQ* q = dynamic_cast<QQQ*>(p);
  q->foo();

class PPP{
  virtual void ttt(){
  }
};
class QQQ: public PPP{
public:
  void foo(){
    cout<< "xxxxx\n";
  }
};
*/
/* 不会继承重载函数
class AA {
public:
  void foo(){
    cout<< "aa-foo" << endl;
  }
  void foo(int){
    cout<< "aa-foo-reload" << endl;
  }
};
class BB :public AA{
public:
  using AA::foo; //让AA内名为foo的所有东西在BB内都可见.
  void foo(){
    cout<< "bb-foo" << endl;
  }
};
  BB b;
  b.foo(3);//错误：对‘BB::foo(int)’的调用没有匹配的函数
*/
/* private继承与访问权限
class AA {
public:
  void foo(){
    cout<< "aa-foo" << endl;
  }
};
class BB :private AA{
public:
  void foo(){
    AA::foo(); //虽然是private继承，但是依然可以访问父类的public和protected成员.是因为继承后才将子类的相应成员改为private的.
  }
};
  BB b;
  b.foo();
*/

/* typeid(类型名/变量/表达式) ：获取"类型名/变量/表达式"的类型
int a = 10;
string b = "hello";
const type_info &tinfo = typeid(a);
const type_info &tinfo2 = typeid(b);
cout << tinfo.name() << "," << tinfo.hash_code() << endl; //i,6253375586064260614
cout << tinfo2.name() << "," << tinfo2.hash_code() << endl; //Ss,3343276721546589767
*/

/**模版参数竟然还可以是确定的类型；
  //come from TMP:template metaprogramming
template<unsigned t>
struct STU{
  int arr[t];
};
  STU<2> stu; //同时模版参数竟然还可以指定参数的值
  stu.arr[0] = 10; 
  stu.arr[1] = 20; 
  for (int i=0; i<2; i++) {
    cout << stu.arr[i] << endl;
  }
*/
/*
  char astr[] = {'h','e','l','l','o'};
  cout << strlen(astr)<<endl; //不要下面for循环，这里输出的是6，要的时候输出的是5
  for(int i = 0; i<strlen(astr); i++){
    cout << "i:"<< i << astr[i]<<endl;
  }
*/
/*
  char* str = "hello"; //警告：不建议使用从字符串常量到‘char*’的转换 ,所以前面要加const限定
  char astr[] = "hello";
*/

class B{
public:
  virtual void foo() const {
    cout << "foo const"<< endl;
  }
};
class D : public B{
public:
  virtual void foo() {
    cout << "foo "<< endl;
  }
};

//read string from a file.
void readStringFromFile(){
  ifstream numfile("num.txt");
  int n;
  char astr[100];
  string str;
  while(numfile.getline(astr,5)) {
    cout << astr << endl;
  }
}


/*
//std::chrono
void chrono_test(){
  using namespace std::chrono;
  //=============duration
  //duration:用count representation 和 period presion表示一个时间跨度span，比如100秒
  std::chrono::duration<int> pp(100);
  cout << pp.count() << endl;

  //=============time_point
  //独立使用time_point:表示一个具体的时间specific time，如：birthday
  //用duration来表示time_point
  time_point<system_clock,duration<int>> tp(duration<int>(1));
  //用系统时钟来初始化时间
  system_clock::time_point tp2 (tp);
  cout << tp2.time_since_epoch().count() << endl;
  //换成time_t表示
  time_t tt = system_clock::to_time_t(tp2);
  cout << ctime(&tt) << endl;
  
  //=============clock
  //provice access to the current time_point
  system_clock::time_point now = system_clock::now();
  time_t tt2 = system_clock::to_time_t(now);
  cout << ctime(&tt2) << endl;

  duration<int,std::ratio<60*60*24>> oneday; //设置一个1天的时间跨度 [std::ratio给chrono用]
  system_clock::time_point tomorrow = now+oneday; //这里怎么可以是time_point和duration相加呢？难道是重载了?
  time_t tt3 = system_clock::to_time_t(tomorrow);
  cout << ctime(&tt3) << endl;

  auto tp = std::chrono::high_resolution_clock::now();
  std::cout << tp.time_since_epoch().count() << std::endl;

  auto tp2 = std::chrono::system_clock::now();
  std::cout << tp2.time_since_epoch().count() << std::endl;

  auto tp3 = std::chrono::steady_clock::now();
  std::cout << tp3.time_since_epoch().count() << std::endl;
}
*/
/* 结构体指针成员赋值出现段错误
struct SS {
  string result;
};
string str = "hello";
//SS *s;  //因为这里只是声明，还没分配内存
SS *s = new SS;
s->result = "hello";
*/

/*
int foo(void* __restrict args) {
  int* aa = (int*)args; //这里需要加(int*)强转下，否则void*不知道是什么类型. 错误：从类型‘void* __restrict__’到类型‘int*’的转换无效 [-fpermissive]
  *aa = 20; //需要在aa前加*，否则 错误：从类型‘int’到类型‘int*’的转换无效.
}
  int tt = 10;
  foo(&tt);
*/

/*独占指针std::unique_ptr
class Unique{
public: //错误：‘int Unique::age’是私有的
  int age;
};
int foo(Unique* uq) {
  std:unique_ptr<Unique> uuu(uq);
  uq->age = 20; //就算这里设置了值，在该函数外这也访问不到，因为出了该函数后，uq对象呗unique_ptr析构了.
}
Unique *uq = new Unique();
foo(uq);
cout << "==================" << uq->age <<endl;
//delete uq; //前面用了unique_ptr独占指针释放uq对象后，这里再删除，则会出错：double free.
*/

/* enum类型调用到底要不要加enum类型名？ 好像加不加都可以，但是在protobuf里好像又不能加
namespace testenum {
struct Tea {
  enum SEX {
    UNKNOW = 0,
    FEMALE = 1,
    MALE = 2,
  };
  std::string name;
};
}
cout << "==================" << testenum::Tea::SEX::MALE <<endl; //访问路径竟然还可以加枚举类型SEX。
*/
/* 宏定义中用decltype()
#define A(x) std::vector<decltype(x)>
  int32_t a = 10;
  A(a) pp;
  pp.push_back(20);
  for (auto i : pp) {
    cout << i << endl;
  }
*/

/*
  std::map<int, std::string> mm;
  mm.emplace(10,"tom");
  mm.emplace(10,"anmi"); //如果key相同，则插入失败
  for (auto iter = mm.begin(); iter != mm.end(); ++iter) {
    cout << iter->first << "=====" << iter->second << endl; 
  }
*/
  int foo(void* __restrict args) {
    int* aa = (int*)args; //这里需要加(int*)强转下，否则void*不知道是什么类型. 错误：从类型‘void* __restrict__’到类型‘int*’的转换无效 [-fpermissive]
    *aa = 20; //需要在aa前加*，否则 错误：从类型‘int’到类型‘int*’的转换无效.
  }

int main(){
  int tt = 10;
  foo(&tt);
  cout << tt < endl;

  //throw std::invalid_argument((str.c_str()));
  char data[] = "dc";
  cout << data << endl;

  cout << time(NULL) << endl;

#if 0


  cout << "=================="<<endl;
  


  typedef std::chrono::duration<int, std::ratio<3600,1>> xx;
  typedef std::chrono::duration<int, std::ratio<60,1>> zz;
  zz zza(60);
  int32_t pacing;
  cout << pacing << endl;
  cout << "=================="<<endl;

  map<int32_t, int32_t> mm;
  mm.insert(make_pair<int32_t,int32_t>(10,2));
  for(map<int32_t, int32_t>::iterator iter=mm.begin(); iter!=mm.end(); ++iter) {
    //cout << iter->first << endl;
    say(*iter);
    //say2((iter->first));

  }
  map<int32_t,int32_t> aa({{50,3},{60,5}});
  for(map<int32_t,int32_t>::iterator xiter=aa.begin();xiter!=aa.end();++xiter){
    say3(xiter);
  }
  /**
  std::shared_ptr<map<int32_t, int32_t>> tt = make_shared<map<int32_t,int32_t>>(mm);
	for(map<int32_t, int32_t>::iterator iter = mm.begin(); iter != mm.end(); ++iter){
		cout << iter->first;
		cout << iter->second;
	}

  */
  string ppa = "abc";
  const char* abc = string(ppa).c_str();
  cout << abc << endl;
  string str;
  stringstream ss;
  ss << "world";
  ss >> str;
  cout << str << endl;
  cout << sizeof(int32_t)<< endl;
  const char* sc = "hello";
  vector<int32_t> v = {1,3,8,9};
  int* pp = v.data();
  cout << "pp:" << (pp+8) << endl;
  string pxx = string((const char*)(v.data()), v.size()*sizeof(int32_t));
  cout << "=:"<< pxx << endl;

  time_t cur;
  cur = time(NULL);
  cout << cur << endl;

  std:string p = "he";
  uint64_t b;
  cout <<sizeof(b)<< endl;
  cout << p.length() << endl;
  int a = 123456/1000;
  cout << a << endl;
  return 0;
#endif
}


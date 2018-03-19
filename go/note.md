# gostudy
===
`go` study note!

### come in

## performance
- simple,fast,safe
- concurrency,intreasting,open
- memory management,array safe,compile fastly

## usage
- web server
- storage cluster
- center server
- high performance distribution - concurrency 
- game server


## INSTALL
1. down go1.4.linux-amd64.tar.gz
2. tar -C /usr/local -xzf go1.4.linux-amd64.tar.gz
3. vim .bash_profile
- export PATH=$PATH:/usr/local/go/bin
4. source .bash_profile

## compile tools
- Sublime Text
- GoSublime
- vim

## hello world
```go
package main  //包声明。表示是一个可独立执行的程序，每个Go应用程序都包含一个main包.

import "fmt"  //引入包。 告诉Go编译器这个程序需要使用fmt包(的函数或其它元素)

func main() {  //程序开始执行的函数. main函数是每一个可执行程序所必须包含的，一般是启动后第一个执行的函数(如果有init()函数则会先执行该函数)
　　//println("hello word!")
    fmt.Println("hello word!")  //在最后自动加换行符\n
    fmt.Print("hello word!\n")  //等效与fmt.Println()
}
```
- compile and execute
```shell
$ go build
$ ./hello
hello!
```
## GC
- 1.0版本的GC问题在遇到内存中有大量数据需要回收的时候，会引起服务停顿甚至数秒，相当于服务中断状态，问题很严重，所以需要考虑到不要让内存中有大量数据.
- 1.5版本解决了GC问题。

### language fundation structure 
- 包声明
- 引入包
- 函数
- 变量
- 语句 & 表达式
- 注释


###  常用
1. 注释
- //
- /*    */
2. 首字母大小写
- 首字母大写：标识符在外部包可用(必须先包含包含标识符的这个包)，类似public;
- 首字母小写：对包外不可见，类似protected.
3. 每行代表一个语句结束；多个语句写在同一行则可认为加分号分隔;
4. 变量声明必须用空格隔开：  var age int;


### grammer
## 一、数据类型
1. 用于声明函数和变量
2. 数据类型的出现是为了把数据分成所需内存大小不同的数据，编程的时候需要用大数据的时候才需要申请大内存，就可以充分利用内存。
3. bool: true/false.
4. string: UTF-8.
5. 派生类型：指针(pointer)、数组、结构化(struct)、Channel、切片、接口(interface)、Map.
6. go 1.9版本对于数字类型，无需定义int及float32、float64，系统会自动识别。 

## 二、变量
1. 格式： var identifier type  
- var name string = "Tom"
- c := 10 注意 :=左侧的变量不应该是已经声明过的，否则会导致编译错误.只能在函数体中出现.
```go
// 这种因式分解关键字的写法一般用于声明全局变量
var (
    vname1 v_type1
    vname2 v_type2
)

```
2. :=赋值操作
- `可省略类型和var,类型由编译器自动推断。`
- `这是使用变量的首选形式，但是它只能被用在函数体内，而不可以用于全局变量的声明与赋值。使用操作符 := 可以高效地创建一个新的变量，称之为初始化声明。`

3. 变量不仅要初始化，而且还要被使用.否则编译不通过.
- `但是全局变量允许声明但不使用`.

4. 交换变量的值： a, b = b, a

5. 空白标识符_(只写变量)用于抛弃值， 如：_, b = 5, 7

6. 值引用
- 取内存地址  &i
- 指针


## 三、常量
1. 格式：const identifier [type] = value  //类型可以省略.
2. 枚举常量
```go
const (
    Unknown = 0
    Female = 1
    Male = 2
)
```

3.iota：特殊常量，可以认为是一个可以被编译器修改的常量.可用作枚举.


## 四、运算符
1. `异或：q和q相反则为真.即两个对应的位相异则为1.`

2. & , *
- & ：  &a; 将给出变量的实际地址.
- * ：  *a; 是一个指针变量.

## 五、函数
1. 返回单个值
```go
/* 函数返回两个数的最大值 */
func max(num1, num2 int) int {   //格式：func function_name( [parameter list] ) [return_types]    .     return_types 不是必须的.
   /* 声明局部变量 */
   var result int

   if (num1 > num2) {
      result = num1
   } else {
      result = num2
   }
   return result 
}
```

2. 返回多个值.
```go
package main

import "fmt"

func swap(x, y string) (string, string) {
   return y, x
}

func main() {
   a, b := swap("Mahesh", "Kumar")
   fmt.Println(a, b)
}
```

3. 函数参数
- 值传递
- 引用传递

4. 函数用法
- 函数作为变量的值.
- 闭包：闭包是匿名函数，可在动态编程中使用.
```go
//该函数的目的是在闭包中递增i变量.
func getSequence() func() int {  //`这里的func() int和return的匿名函数返回值+类型【func() int】要保持一致`
   i:=0
   return func() int {           //`返回的是一个函数： func() int`
      i+=1
     return i  
   }
}
```
- 方法：方法就是一个包含了接受者的函数，接受者可以是命名类型或者结构体类型的一个值或者是一个指针。
```go
//下面定义一个结构体类型和该类型的一个方法：
package main

import (
   "fmt"  
)

/* 定义结构体 */
type Circle struct {
  radius float64
}

func main() {
  var c1 Circle
  c1.radius = 10.00
  fmt.Println("Area of Circle(c1) = ", c1.getArea())
}

//该 method 属于 Circle 类型对象中的方法
func (c Circle) getArea() float64 {   //重点：这里相当于把getArea()方法看作是c这个结构体的方法.
  //c.radius 即为 Circle 类型对象中的属性
  return 3.14 * c.radius * c.radius
}
```

## 六、数组
1. 数组是具有相同唯一类型的一组已编号且长度固定的数据项序列.

2. 数组声明：数组声明需要指定元素类型及元素个数. var balance [10] float32

3.初始化数组：var balance = [5]float32{1000.0, 2.0, 3.4, 7.0, 50.0}

## 七、指针
1. 指针声明：var fp *float32   //* 号用于指定变量是作为一个指针

2. 指针使用流程
```go
package main

import "fmt"

func main() {
    var a int= 20   /* 声明实际变量 */

    //1.定义指针变量。
    var ip *int        /* 声明指针变量 */

    //2.为指针变量赋值。
    ip = &a  /* 指针变量的存储地址 */

    fmt.Printf("a 变量的地址是: %x\n", &a  )

    /* 指针变量的存储地址 */
    fmt.Printf("ip 变量储存的指针地址: %x\n", ip )

    //3.访问指针变量中指向地址的值。
    /* 使用指针访问值 */
    fmt.Printf("*ip 变量的值: %d\n", *ip )
}
```
3. 空指针
- 当一个指针被定义后没有分配到任何变量时，它的值为 nil。

## 八、结构体
1. 结构体是由一系列具有相同类型或不同类型的数据构成的数据集合.
```go
type Books struct {
   title string
   author string
   subject string
   book_id int
}
```
2. 结构体访问.
- 访问结构体成员，需要使用点号 (.) 操作符，格式为："结构体.成员名".

## 九、切片(Slice)
1. 概念：对数组的抽象；动态数组； 长度不固定； 可追加元素.

2. 定义切片
- var identifier []type //切片不需要说明长度.
- var slice1 []type = make([]type, len)  简写：slice1 := make([]type, len)
- make([]T, length, capacity) //指定容量，capacity可选. //这里 len 是数组的长度并且也是切片的初始长度.

3. append() 和 copy() 函数.

九、范围(Range)
1. 概念：range 关键字用于for循环中迭代数组(array)、切片(slice)、通道(channel)或集合(map)的元素。在数组和切片中它返回元素的索引值，在集合中返回 key-value 对的 key 值.

```go
nums := []int{2, 3, 4}
for i, num := range nums {
    if num == 3 {
        fmt.Println("index:", i)
    }
}
```
十、集合(Map)
1. 概念：无序；键值对. 通过key来快速检索数据.可迭代. 使用hash实现.

2. 定义：
- /* 声明变量，默认 map 是 nil */
- var map_variable map[key_data_type]value_data_type

- /* 使用 make 函数 */
- map_variable := make(map[key_data_type]value_data_type) 

3. delete(mapname, key)：删除集合的元素.

十一、递归函数
1. 递归，就是在运行的过程中调用自己。 

2. 语法
```go
func recursion() {
   recursion() /* 函数调用自身 */
}

func main() {
   recursion()
}
```
- 注意：在使用递归时，开发者需要设置退出条件，否则递归将陷入无限循环中。

十二、类型转换
1. 概念：将一种数据类型的变量转换为另外一种类型的变量.
```go
var sum int = 17
float32(sum)
```

十三、接口 - truct + 方法 =>实现对象.
1. 概念：接口是把所有的具有共性的方法定义在一起，任何其他类型只要实现了这些方法就是实现了这个接口.

2. 定义
```go
package main

import (
    "fmt"
)
/* 定义接口 */
type Phone interface {
    call()
}

/* 定义结构体 */
type NokiaPhone struct {
    var name string
}

/* 实现接口方法 */
func (nokiaPhone NokiaPhone) call() {
    fmt.Println("I am Nokia, I can call you!")
}

type IPhone struct {
}

func (iPhone IPhone) call() {
    fmt.Println("I am iPhone, I can call you!")
}

func main() {
    var phone Phone

    phone = new(NokiaPhone)
    phone.call()

    phone = new(IPhone)
    phone.call()

}
```

十四、错误处理
1. error类型是一个接口类型.
```go
type error interface {
    Error() string
}
```

十五、开发工具
1. LiteIDE
2. Eclipse + goclipse + gocode(gocode插件，用于go的代码补全提示)








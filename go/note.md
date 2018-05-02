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
### 格式
- 格式： func (p mytype) funcname(q int) (r,s int) { return 0,0 }
1. 保留字func 用于定义一个函数；
2. (p mytype) ： 函数可以`定义用于特定的类型`，这类函数更加通俗的称呼是method。这部分称作receiver， 而它是可选的；
3. funcname是你函数的名字；
4. int 类型的变量q 是输入参数。参数用pass-by-value 方式传递，意味着它们会被复制；
5. 变量r 和s 是这个函数的named return parameters。在Go 的函数中可以返回多个值。如果想要返回无命名的参数，只需要提供类型：(int, int)。如果只有一个返回值，可以省略圆括号。如果函数是一个子过程，并且没有任
何返回值，也可以省略这些内容；
6. 这是函数体，注意return 是一个语句，所以包裹参数的括号是可选的。

### 详解函数
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

5. 定义函数退出前执行的函数
例如在打开文件的时候，每一次返回都需要关闭文件描述符，这样会有大量代码重复，在go中，可以定义函数退出前执行的函数。
```
func test(a int) (sum int){
    defer print("test done")
    if a<0{
        return -1
    }else{
        return 1
    }
}
```
这样无论a是大于还是小于0，都会输出文字。

6. 可变参数
类似于Python的*args
```
func test(args ...int) (int) {
    for i, v := range args {  //i为key，num为value；如果省略i，则num为value.最好的办法是，如果不要key，则用_占位.
        print(i, v, "\n")
    }
    return 1
}
func main() {
    test(1, 2, 3, 4, 5)
}
```

7. 快速定义函数
类似于Python的lambda
```
add_one := func(i int) int {
    return 1 + i
}
print(add_one(2))
```

8.函数作为参数
```
func test(i int, fun func(int) int) (int) {
    i++
    return fun(i)
}
func main() {
    add_one := func(i int) int {
        return 1 + i
    }
    print(test(2,add_one))
}
```

## 预定义函数
- len 和cap 可用于不同的类型，len 用于返回字符串、slice 和数组的长度。参阅”array、slices和map”。
- new 用于各种类型的内存分配。参阅”用new 分配内存”。
- make 用于内建类型（map、slice 和channel）的内存分配。参阅”用make 分配内存”。
- copy 用于复制slice。append 用于追加slice。。
- panic 和recover 用于异常处理机制。参阅”恐慌（Panic）和恢复（Recover）” 。
- print 和println 是底层打印函数，可以在不引入fmt 包的情况下使用。它们主要用于调
试。
- complex、real和imag 全部用于处理复数。

## 六、数组
1. 数组是具有相同唯一类型的一组已编号且长度固定的数据项序列.

2. 数组声明：数组声明需要指定元素类型及元素个数. var balance [10] float32

3. 初始化数组：var balance = [5]float32{1000.0, 2.0, 3.4, 7.0, 50.0}

4. 声明byte类型的字节数组：var result []byte

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

### 数组和切片注意事项：
- 当传递一个array给函数的时候，函数得到的是一个array的副本，即传值。
- slice和array类似，不同的是slice是array的一个指针，所以修改slice，是会影响array的，而且传递一个slice给函数的时候，传递的是指针，所以是传址。
- append用户向切片中添加元素，返回新的切片，新的切片的内存地址可能和之前的不一样。


## 十、范围(Range)
1. 概念：range 关键字用于for循环中迭代数组(array)、切片(slice)、通道(channel)或集合(map)的元素。在数组和切片中它返回元素的索引值，在集合中返回 key-value 对的 key 值.

```go
nums := []int{2, 3, 4}
for i, num := range nums {
    if num == 3 {
        fmt.Println("index:", i)
    }
}
```
## 十一、集合(Map)
1. 概念：无序；键值对. 通过key来快速检索数据.可迭代. 使用hash实现.

2. 定义：
- /* 声明变量，默认 map 是 nil */
- var map_variable map[key_data_type]value_data_type `【但是这样声明后，依然需要map_variable = make(map[key_data_type]value_data_type这样创建map】`

- /* 使用 make 函数 */
- map_variable := make(map[key_data_type]value_data_type) 

3. delete(mapname, key)：删除集合的元素.

## 十二、递归函数
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

## 十三、类型转换
1. 概念：将一种数据类型的变量转换为另外一种类型的变量.
```go
var sum int = 17
float32(sum)
```

## 十四、接口 - truct + 方法 =>实现对象.
1. 概念：接口是把所有的具有共性的方法定义在一起，任何其他类型只要实现了这些方法就是实现了这个接口.
-- `通俗理解：1. 把struct的声明当作类，故有p := new(结构体类型)； 2. 把struct里的变量看作成员变量； 3. 声明一个匿名函数，参数传入struct的类型名，同时加上方法名【该方法名即为该new的对象的方法】.`

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

## 十五、错误处理
1. error类型是一个接口类型.
```go
type error interface {
    Error() string
}
```

## 十六、开发工具
1. LiteIDE
2. Eclipse + goclipse + gocode(gocode插件，用于go的代码补全提示)

## 十七、恐慌和恢复
- go中没有异常的处理，只有恐慌和恢复
```
func thrownPanic(fun func() int) (b bool) {
    defer func() {
        if r := recover(); r != nil {
            b = true
        }
    }()
    fun()
    return
}
func main() {
    add_one := func() int {
        a := []int{1, 2, 3}
        print(a[0])
        return 1
    }
    print(thrownPanic(add_one))
}
```
在thrownPanic中，会调用fun，然后在函数结束前执行defer的函数，如果fun中产生了异常，r会为非nil，这样返回true，否则返回false
这样外层的函数就能知道调用fun是否产生了异常。

    "runtime/debug"
    "reflect"
    "fmt"
)
func test_func(){
    defer func(){
        if err:=recover();err!=nil{
            fmt.Println("Panic ",err,reflect.TypeOf(err))
            debug.PrintStack()
        }
    }()
    list:=[]int{1}
    println(list[1])
}
func main(){
    test_func()

程序在执行println(list[1])的时候，会产生恐慌，也就是异常，但是程序不会立刻退出，还会执行defer的函数，这时，`通过revocer函数，可以catch住这个异常，然后把异常信息打印出来，这样程序可以继续正常运行，其实跟try catch差不多`。


## 时间time
- 获取时间戳用time.Now().Unix()
- 格式化时间用t.Format
- 解析时间用time.Parse
> 模版2006-01-02格式，这些数字都是有特殊函义的，不是随便指定的数字，见下面列表：
> 月份 1,01,Jan,January  
> 日　 2,02,_2    
> 时　 3,03,15,PM,pm,AM,am  
> 分　 4,04  
> 秒　 5,05  
> 年　 06,2006  
> 周几 Mon,Monday                                                                                                                                                                                                    
> 时区时差表示 -07,-0700,Z0700,Z07:00,-07:00,MST  
> 时区字母缩写 MST  
```go
import (
    "fmt"
    "time"
)
func main() {
    //获取时间戳
    timestamp := time.Now().Unix()
    fmt.Println(timestamp)  //当前10位时间戳

    //格式化为字符串,tm为Time类型
    tm := time.Unix(timestamp, 0)  //原型：func Unix(sec int64, nsec int64) Time                                                    

    fmt.Println(tm.Format("2006-01-02 03:04:05 PM"))  //"2006-01-02 03:04:05 PM"是格式模版
    fmt.Println(tm.Format("02/01/2006 15:04:05 PM"))

    //从字符串转为时间戳，第一个参数是格式，第二个是要转换的时间字符串
    tm2, _ := time.Parse("01/02/2006", "02/08/2015")
    fmt.Println(tm2.Unix())
/**
输出结果：
1423361979
2015-02-08 10:19:39 AM
08/02/2015 10:19:39 AM
1423353600
}
*/
```

## HTTP GET/POST请求
- GET请求
- get请求可以直接http.Get方法，非常简单。
```go
func httpGet() {
    resp, err := http.Get("http://www.xxx.com/demo/accept.php?id=1")
    if err != nil {
        // handle error
    }
 
    defer resp.Body.Close()
    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        // handle error
    }
 
    fmt.Println(string(body))
}
```
- post请求
1. 一种是使用http.Post方式
- Tips：使用这个方法的话，第二个参数要设置成”application/x-www-form-urlencoded”，否则post参数无法传递。
```go
func httpPost() {
    resp, err := http.Post("http://www.xxx.com/demo/accept.php",
        "application/x-www-form-urlencoded",
        strings.NewReader("name=cjb"))
    if err != nil {
        fmt.Println(err)
    }
 
    defer resp.Body.Close()
    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        // handle error
    }
 
    fmt.Println(string(body))
}
```
2. 一种是使用http.PostForm方法
```php
func httpPostForm() {
    resp, err := http.PostForm("http://www.xxx.com/demo/accept.php",
        url.Values{"key": {"Value"}, "id": {"123"}})
 
    if err != nil {
        // handle error
    }
 
    defer resp.Body.Close()
    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        // handle error
    }
 
    fmt.Println(string(body))
 
}

- 复杂请求
- 有时需要在请求的时候设置头参数、cookie之类的数据，就可以使用http.Do方法。
- 同上面的post请求，必须要设定Content-Type为application/x-www-form-urlencoded，post参数才可正常传递。
```go
func httpDo() {
    client := &http.Client{}
 
    req, err := http.NewRequest("POST", "http://www.xxx.com/demo/accept.php", strings.NewReader("name=cjb"))
    if err != nil {
        // handle error
    }
 
    req.Header.Set("Content-Type", "application/x-www-form-urlencoded")
    req.Header.Set("Cookie", "name=anny")
 
    resp, err := client.Do(req)
 
    defer resp.Body.Close()
 
    body, err := ioutil.ReadAll(resp.Body)
    if err != nil {
        // handle error
    }
 
    fmt.Println(string(body))
}
```
- head请求
- 可以直接使用http client的head方法。

## 文件读写
1. os.OpenFile与fp.WriteString写字符串.
```go
filename:="xxx.txt"
str:="hello world!"
fp, err := os.OpenFile(filename, os.O_RDWR | os.O_CREATE | os.O_APPEND, 0x644)
if err != nil {
    panic(err)
}
defer fp.Close()
wint, err := fp.WriteString(str)
if err != nil {
    panic(err)
}
fmt.Printf("%d\n", wint)
_, err = fp.Seek(0, 0)
if err != nil {
    panic(err)
}
bs := make([]byte, 100)
rint, err := fp.Read(bs)
if err != nil {
    panic(err)
}
fmt.Printf("%d, %s\n", rint, bs)
```

## JSON
```go
package main
import (
    "encoding/json"
    "fmt"
    "os"
    "reflect"
)
type Response1 struct {
    Page   int
    Fruits []string
}
type Response2 struct {
    Page   int      `json:"page"`
    Fruits []string `json:"fruits"`
}

func main() {
    //encoding basic data types to JSON strings。
    /**
    :!go run a.go
    []uint8
    [116 114 117 101]

    []uint8
    1

    []uint8
    3.12
    [51 46 49 50]

    []uint8
    "hello"
    [34 104 101 108 108 111 34]
    */
    bolB, _ := json.Marshal(true)
    fmt.Println(reflect.TypeOf(bolB))
    fmt.Println(bolB)

    intB, _ := json.Marshal(1)
    fmt.Println(reflect.TypeOf(intB))
    fmt.Println(string(intB))

    fltB, _ := json.Marshal(3.12)
    fmt.Println(reflect.TypeOf(fltB))
    fmt.Println(string(fltB))
    fmt.Println(fltB)

    strB, _ := json.Marshal("hello")
    fmt.Println(reflect.TypeOf(strB))
    fmt.Println(string(strB))
    fmt.Println(strB)
    
    //encoding slices and maps to JSON arrays and objects.
    /** slice
    []uint8
    ["apple","orange"]
    [91 34 97 112 112 108 101 34 44 34 111 114 97 110 103 101 34 93] 
    */  
    slcD := []string{"apple", "orange"}
    slcB, _ := json.Marshal(slcD)
    fmt.Println(reflect.TypeOf(slcB))
    fmt.Println(string(slcB))
    fmt.Println(slcB)
    /** map 
    []uint8
    {"apple":5,"orange":6}
    [123 34 97 112 112 108 101 34 58 53 44 34 111 114 97 110 103 101 34 58 54 125]
    */  
    mapD := map[string]int{"apple": 5, "orange": 6}
    mapB, _ := json.Marshal(mapD)
    fmt.Println(reflect.TypeOf(mapB))
    fmt.Println(string(mapB))
    fmt.Println(mapB)

    //encoding automatically your custom data types.
    //{"Page":1,"Fruits":["apple","orange"]}
    res1D := &Response1{
        Page:   1,  
        Fruits: []string{"apple", "orange"},
    }   
    res1B, _ := json.Marshal(res1D)
    fmt.Println(string(res1B))
    //use tags on struct field declarations to customize the encoded JSON key names.
    //{"page":1,"fruits":["apple","orange"]}     [add tags to keys]
    res2D := &Response2{
        Page:   1,  
        Fruits: []string{"apple", "orange"},
    }   
    res2B, _ := json.Marshal(res2D)
    fmt.Println(string(res2B))

    fmt.Println("DECODING JSON")
    /***************************DECODING JSON**************************/
    /** 
    1. provide a variable where the JSON package can put the decoded data.
    2. map[string]interface()/ will hold/ a map of/ strings to arbitray data types.
    */  
    var dat map[string]interface{}
    fmt.Println(reflect.TypeOf(dat)) //map[string]interface {}

    byt := []byte(`{"num":6.13,"strs":["apple","orange"]}`)
    //check for associated errors
    /** 
    map[num:6.13 strs:[a b]] 
    map[string]interface {}
    
    */  
    if err := json.Unmarshal(byt, &dat); err != nil {
        panic(err)
    }   
    fmt.Println(dat)                 //map[num:6.13 strs:[a b]] 
    fmt.Println(reflect.TypeOf(dat)) //map[string]interface {}

    // situation1: none-nested.  get value to get directly.
    num := dat["num"].(float64)
    fmt.Println(num)                 //6.13
    fmt.Println(reflect.TypeOf(num)) //float64
    // situation2: nested.  requires a series of casts.
    strs := dat["strs"].([]interface{})
    str1 := strs[0].(string)
    fmt.Println(reflect.TypeOf(dat["strs"])) //[]interface {}
    fmt.Println(reflect.TypeOf(strs))        //[]interface {}
    fmt.Println(reflect.TypeOf(str1))        //string
    fmt.Println(str1)

    // decode JSON into custom data types.
    str := `{"page": 1, "fruits": ["apple", "peach"]}`
    res := Response2{}
    json.Unmarshal([]byte(str), &res)
    fmt.Println(res)           //{1 [apple peach]}
    fmt.Println(res.Page)      //1 
    fmt.Println(res.Fruits[0]) //apple

    /** 
    Except used bytes and strings as imtermediates between the data and JSON represation on standard out above.
    We can also stream JSON encoding to os.Writer like os.Stdout or HTTP response bodies.
    */  
    enc := json.NewEncoder(os.Stdout)
    d := map[string]int{"apple": 5, "orange": 7}
    enc.Encode(d) //{"apple":5,"orange":7}
```

## Scala基于Java，调用了大量的Java库。
## Scala与Java的最大区别：Scala语句末尾的分号是可选的。
## 理解：可以认为Scala程序是对象的集合，通过调用彼此的方法来实现消息的传递。

## 部署
-- 下载unix版本的二进制版 -- 解压 -- 设置环境变量：  
```scala
SCALA_HOME=/home/sofia/scala-2.12.3
export SCALA_HOME
PATH=$PATH:$SCALA_HOME/bin
export PATH
export CLASSPATH=$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar:/home/codelib
```

## scala执行方式
- 交互式界面  
命令行输入scala-回车

- 脚本形式  
1. 编译成字节码：scalac HelloWorld.scala
2. 执行字节码文件： scala HelloWorld
- 问题：  
No such file or class on classpath: HelloWorld”  
解决方法：  
    设置环境变量：export CLASSPATH=$CLASSPATH:/home/codelib:/home/sofia/scala-2.12.3/lib/scala-library.jar  //这个目录为生成字节码class文件的目录,此时可以执行scala Helloworld. 后面加上lib/scala-library.jar，便可让java来执行scala字节码程序.

## Scala基本语法
- 区分大小写.
- 类名第一个字母要大写。
- 方法名称第一个字母用小写。
- 程序文件名称应该与对象名称完全匹配。如果文件名和对象名称不匹配，程序无法编译。
- def main(args:Array[String]) - Scala程序从main()方法开始执行，这是所有Scala程序的入口。
- 注释：同java一样，// 和 /**/
- 定义包：
```scala
//方法一：
package com.xx
class HelloWorld
//方法二：
package com.xx{
    class HelloWorld
}
```
- 引用包： 
```scala
import java.awt.Color
import java.awt._ //引入包内所有成员
```
- 以scala开头的包，在使用时都是省去scala的：因为默认情况下，Scala总会引入java.lang._、scala._、Predef._。

## 数据类型
- 注意：scala的数据类型都是对象，没有像java中的原生类型。在scala中是可以对数字等基础类型调用方法。
- Byte：8位有符号整数，-128到127
- Char：16位无符号Unicode字符 U+0000到U+FFFF
- Boolean：true/false
- Unit：表示无值，等同void。Unit只有一个实例值，写成()。
- Null：null或空引用.
- Nothing：Nothing类型在Scala的类层级的最低端，它是任何其它类型的子类型。
- Any：是所有其他类的超类.
- AnyRef：是所有引用类(reference class)的基类.

## 字面量
- 浮点型：后缀不加f/F则默认为Double类型，加了表示float类型.
- 字符类型用单引号. val a="aaa'\n'"
- 多行字符串表示方法：三个双引号来表示分隔符 """..."""
- 0 到 255 间的 Unicode 字符可以用一个八进制转义序列来表示，即反斜线‟\‟后跟 最多三个八进制。

## 函数
- Scala 函数名可以有以下特殊字符：+, ++, ~, &,-, -- , \, /, : 等。
- 函数声明:
```scala
def functionName ([参数1:类型,参数2:类型,...]) : [return type] = {}
//如果你不写等于号和方法主体，那么方法会被隐式声明为"抽象(abstract)"，包含它的类型于是也是一个抽象类型。
//如果没有返回值，那么returntype可声明为Unit，类似java的void。
```
- 函数调用方法：  
1. 直接调用函数名;
2. 点号调用(同java)。
- Scala也是一种函数式语言，所以函数是 Scala 语言的核心。

## 数组
- 存储固定大小、类型相同的元素.
- 数组声明：
```scala
var z:Array[String] = new Array[String](3)
//或
var z = new Array[String](3)
//或
var z = Array("Robin","Amy","Linda")
```
- 数组访问或者赋值：z(0)="robin"
- 数组遍历:
```
var z = Array("Robin","Amy","Linda")
for(x <- z){
    println(x)
}
length = z.length
var total = 0.0
for(i <- 0 to (length-1)){  //类似foreach的感觉
    total += z(i)
}
- 合并数组：concat(arr1, arr2, ...)
- 创建区间数组: var z = range(10, 20, 2) //最后一个参数为步长，默认为1

## 集合Collection
- List:类似于数组，元素类型都相同,元素和重复。列表是不可变的，值一旦被定义了就不能改变，且列表具有递归结构(链表结构)  
val site: List[String] = List("Runoob", "Google", "Baidu")
- Set：没有重复的元素。分为可变和不可变集合，默认是不可变集合如果你想使用可变集合，需要引用 scala.collection.mutable.Set 包。  
val set = Set(1,2,3)
- Map（映射）：是一种可迭代的键值对结构，键是唯一的，Map也叫哈希表。氛围可变/不可变，默认为不可变.import scala.collection.mutable.Map
```scala
// 空哈希表，键为字符串，值为整型
var A:Map[Char,Int] = Map()

// Map 键值对演示
val colors = Map("red" -> "#FF0000", "azure" -> "#F0FFFF")
```
- 元组：与列表一样，元组也是不可变的，但元组可以包含不同类型的元素。  
```scala
val t = (1, 3.14, "Fred")  
println(t._1) //访问元组第一个元素
t.productIterator.foreach{ i =>println("Value = " + i )} //用Tuple.productIterator() 方法来迭代输出元组的所有元素
```
- Option（选项）：表示一个值是可选的
- Iterator（迭代器）：它不是一个集合，它是一种访问集合的方法。
```scala
/**
调用 it.next() 会返回迭代器的下一个元素，并且更新迭代器的状态。
调用 it.hasNext() 用于检测集合中是否还有元素。
让迭代器 it 逐个返回所有元素最简单的方法是使用 while 循环
迭代器it方法:max,min,size,length
*/
val it = Iterator("Baidu", "Google", "Runoob", "Taobao")
while (it.hasNext){
 println(it.next())
}
```

## 类和对象
- 类是抽象的，不占用内存，而对象是具体的，占用存储空间。
- 和java一样，用new实例化一个对象，用extends继承一个对象。【scala只能继承一个父类】
- 继承注意：
```scala
1、重写一个非抽象方法必须使用override修饰符。
2、只有主构造函数才可以往基类的构造函数里写参数。
3、在子类中重写超类的抽象方法时，你不需要使用override关键字。
```
- scala单例：虽然scala没有static，但是提供了关键字object。
- 伴生类和伴生对象：在同一个源文件里定义的同名的类和object声明的对象.

## 模式匹配
- scala的模式匹配同java的switch.
```scala
object Test {
   def main(args: Array[String]) {
      println(matchTest(3))

   }
   def matchTest(x: Int): String = x match {
      case 1 => "one"
      case 2 => "two"
      case _ => "many"
   }
}
```
## 样例类
- 使用关键字case声明的类：case classes。
- 样例类是一种特殊的类，经过优化以用于模式匹配.
```
case class Person(name: String, age: Int)
val alice = new Person("Alice", 25)
```

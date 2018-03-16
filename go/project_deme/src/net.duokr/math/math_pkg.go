package math

//Go规定了只有首字母大写的函数才能从包导出使用。

func Add(a, b int) int {
    return a + b
}

func Subtract(a, b int) int {
    return a - b
}

func Divide(a, b int) int {
    if b == 0 {
        panic("Can be not divided by zero!")
    }
    return a / b
}

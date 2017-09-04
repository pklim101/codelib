package main

import "fmt"



func main(){
    var balance [3] float32

    balance[0] = 20.1
    balance[1] = 16.9
    balance[2] = 12.0

    for i,x:=range balance {
        fmt.Printf("第%d位x的值 = %.2f\n", i,x);
    }


    var numbers = [5]int{1,2,3,5,9}
    for i,x:= range numbers {
        fmt.Printf("%d x = %d\n", i,x)    
    }

    //多维数组
    a := [5][2]int {
        {1,2},    
        {3,2},    
        {2,2},    
        {1,7},    
        {3,2},    
    }
    //i,j必须声明，不能直接用
    for i := 0; i<5; i++ { 
        for j :=0; j <2; j++ {
            fmt.Printf("a[%d][%d] = %d\n", i,j,a[i][j])    
        }    
    }

    //如果你想向函数传递数组参数，你需要在函数定义时，声明形参为数组
    var t = []int{1,2,3,5,9}
    var avg float32
    avg = getAverage(t, 5)
    fmt.Printf("avg = %f", avg)
}
//用func声明.
func getAverage(arr []int, size int) float32 {//这个{不能作为新行放到行首
    var i,sum int
    var avg float32
    
    for i =0; i < size; i++{
        sum += arr[i]    
    }     

    avg = float32(sum / size) //整型相除得到浮点，则需要强制转换为浮点类型float32()

    return avg
}

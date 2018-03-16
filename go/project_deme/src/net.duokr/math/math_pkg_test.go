package math

/** Test Case
1. 规定：Go会把以_test.go结尾的文件当作是测试文件.

2. 测试怎么写:当然是用assert来判断程序的运行结果是否和预期的相同了.

3. 运行测试用例：将路径切换到测试文件所在目录，运行go test命令，go会自动测试所有的测试用例.

4. 测试用例的特点是以函数名以Test开始，而且具有唯一参数t *testing.T.

*/

import (
    "testing"
)

func TestAdd(t *testing.T) {

    var a = 100
    var b = 200

    var val = Add(a, b)

    if val != a+b {
        t.Error("Test Case [", "TestAdd", "] Failed!")
    }

}

func TestSubtract(t *testing.T) {
    var a = 100
    var b = 200

    var val = Subtract(a, b)

    if val != a-b {
        t.Error("Test Case [", "TestSubtract", "] Failed!")
    }
}

func TestDivide(t *testing.T) {
    var a = 100
    var b = 200

    var val = Divide(a, b)

    if val != a/b {
        t.Error("Test Case [", "TestDivide", "] Failed!")
    }
}


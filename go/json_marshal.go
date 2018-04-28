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
}

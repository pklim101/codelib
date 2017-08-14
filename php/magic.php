<?php
/**
#######################################
# 魔术方法 :: 重点在于触发条件.
#######################################
isset(): 判断一个变量或者一个对象的公有成员是否设置【私有成员无法判断】.
__isset(): 在类里面重写该方法，则可以在类外面调用isset()判断类的私有成员是否设置.  

unset():删除一个变量或者一个对象的公有成员【私有成员无法删除】.
__unset(): 在类中重写该方法，则可以在类外面调用unset()删除类的私有成员.
*/

class A{
    public $name;
    public $age;

    public function __construct(){
       $this->name = "Json"; 
    }
    
    /**
    触发条件：当调用不存在或不可访问的类属性时.
     */
    public function __isset($nm){ 
        echo "当在类外部使用isset()函数测定私有成员$nm时，自动调用<br>"; 
        return isset($this->$nm); 
    } 

    /**
    触发条件：当调用不存在或不可访问的类属性时.
     */
    public function __unset($nm){ 
        echo "当在类外部使用unset()函数来删除私有成员时自动调用的<br>"; 
        unset($this->$nm); 
    } 

    /**
    触发条件：echo $new A();
    */
    public function __toString(){
        return "必须返回一个字符串.\n"; 
    }

    /**
    触发条件：当调用不存在的类时.
    @params$className String 被调用的类名.
     */
    public function __autoload($className){
        $file = "/data/".$className."class.php";
        if(is_file($file)){
            include_once($file);
        }
    }
    
    
    /**
    触发条件：当调用var_export(该类)
    */
    public function __set_state(){
        $t = new A();
        $t->name = "Amy";// 这里这样设置无效.
        //$this->name = "Amy";
        return $t; 
    }

    /**
    触发条件：当调用的类方法不存在时触发.
    @params $name String class method name.
    @params $params Array parameters.from the second parameter to the end are method parameters in a array.
    */
    public function __call($name, $params){
        echo "this is a called class method non-existent.\n";
        print_r($params);
    }

    /**
    触发条件：unserialize
     @params无参数
     @return array  必须返回一个包含若干类属性的数组.
    */
    public function __sleep(){
        return array('name');
    }

    /**
    触发条件：类被反序列化时serialize
     @params 无参数
     */
    public function __wakeup(){
        $this->name = "new name for wakeup.\n";
    }

    /**
    触发条件：对象被克隆时被调用.
     */
    public function __clone(){
        $this->name = "这是克隆时被重置的name值.\n";
    }

    
}

$p = new A();
echo $p;

var_export($p);

$p->calltest(111,222,333);


$p1 = clone $p; //深拷贝
$p2 = $p;    //浅拷贝
var_dump($p,$p1,$p2);

var_dump($s = serialize($p));

var_dump(unserialize($s));


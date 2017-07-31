<?php
#####################
# trait：解决php单继承问题，实现多继承.
# Notic: trait类不能实例化.
#####################

trait Hello{
    public function sayHello(){
        echo "Hello ";    
    }    
}


trait World{
    public function sayWorld(){
        echo "World";    
    }    
}

class Exclamation{
    #此处插入Hello,World两个trait类.
    use Hello,World;
    public function sayExclamation(){
        echo "!";    
    }    
}

$p = new Exclamation();
$p->sayHello();
$p->sayWorld();
$p->sayExclamation();

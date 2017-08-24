### 一、创建数据库webpy和表entries.
```SQL
create database `webpy`;

CREATE TABLE entries (  
    id INT AUTO_INCREMENT,  
    title TEXT,  
    content TEXT,  
    posted_on DATETIME,  
    primary key (id)  
); 
```

### 二、在主目录webpy里创建blog.py.

### 三、在主目录webpy里创建model.py.

### 四、在模板目录templates依次创建：base.html、edit.html、index.html、new.html、view.html.

### 五、进入主目录在命令行下运行：python blog.py，将启动web服务，在浏览器输入：http://localhost:8080/ 


### 注意：
- 运行python blog.py的时候，可能会报错：ImportError: No module named MySQLdb.
- 原因：没有安装MySQL-python模块.
- 解决：pip install MySQL-python安装一直失败，提示mysql_config not fund.
- 1. ln -s ln -s /usr/local/mysql/bin/mysql_config /usr/local/bin/mysql_config;
- 2. 直接下载MySQL-python-1.2.5.zip,然后修改site.cfg里的mysql_config配置；
- 3. python setup.py install.   

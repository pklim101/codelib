### 项目结构组织、部署、测试用例
1. 项目结构组织
```
.
├── bin   //执行build.sh后生成
│   └── main
├── note_project_demo.md
├── pkg   //执行build.sh后生成
│   └── linux_amd64
│       └── net.duokr
│           └── math.a
└── src
    ├── main
    │   ├── build.sh
    │   ├── main
    │   └── main.go
    └── net.duokr
        └── math
            ├── math_pkg.go
            └── math_pkg_test.go

```

2. 部署 - 编译安装
- 需要切换到build.sh所在目录后执行该脚本.

3. 测试用例
- ~/codelib/go/project_deme/src/net.duokr/math/math_pkg_test.go

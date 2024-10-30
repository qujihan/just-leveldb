# LSMTree之leveldb
## 前置条件
- ninja
- make
- clang/clang++(or gcc/g++)

# 运行
```bash
# 会在 bin/ 目录下生成可执行文件
# 运行数据会存放在 leveldb_data 中
git submodule update --init --recursive
make
```

# 使用自己的 fork 自 google/leveldb 的 leveldb 源码
```bash
# 先clone本仓库
cd just-leveldb
git submodule deinit -f leveldb; git rm leveldb
git submodule add https://github.com/your_github_domain/leveldb.git leveldb
git submodule update --init --recursive
```
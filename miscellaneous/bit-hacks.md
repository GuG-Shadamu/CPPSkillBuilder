# Some interesting Bit Hacks


### 1. 利用或操作 `|` 和空格将英文字符转换为小写

```cpp
char('a' | ' ') // is 'a'
char('A' | ' ') // is 'a'
```

### 2. 利用与操作 `&` 和下划线将英文字符转换为大写

```cpp
char('b' & '_') // is 'B'
char('B' & '_') // is 'B'
```


### 3. 利用异或操作 `^` 和空格进行英文字符大小写互换

```cpp
char('c' ^ ' ') // is 'C'
char('C' ^ ' ') // is 'c'
```

### 4. 不用临时变量交换两个数

```cpp
int a = 1;
int b = 2;

a ^= b;
b ^= a;
a ^= b;

// now a = 2, b=1
```


### 5. 判断两个数是否异号

```cpp
int x = -1, y = 2;
bool f = ((x ^ y) < 0); // true

int x = 3, y = 2;
bool f = ((x ^ y) < 0); // false
```
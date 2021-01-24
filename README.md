## Gray Code and Set using Hashtable

[toc]

<div style="page-break-after: always;"></div>

### Introduction

In this task we will use C++ to implement Gray code generation and Set container based on HashTable.

The first section will describe a generic binary data container and give a Gray code implementation based on it. 

The second section will describe the collection and its associated operations.

### Gray code

#### Summary

Gray codes are used in some basic applications of signal transmission: in some cases it is unreliable to use traditional binary data transmission, for example:

>We need to transfer the data "8" to the target after coding it - it has a binary code of 1000 and assume the current register storage is "7" - the corresponding code is 0111, during this conversion process, the possible register states are:
>
>```
>{ 0110, 0101, 0100, 0011, 0010, 0001, 0000 }
>```
>
>This encoding has a large margin of error when approaching digital transformations, and Gray Code solves this problem.

Gray Code is also known as "Least Difference Code" because the binary digits of two adjacent numbers differ by only one digit.

Because the mapping from Binary codes set to Gray codes set is **Injection**, which means: assume <!-- $n$ --> <img src="https://render.githubusercontent.com/render/math?math=n"> bits Binary codes set is <!-- $X$ --> <img src="https://render.githubusercontent.com/render/math?math=X">, corresponding Gray codes set is <!-- $Y$ --> <img src="https://render.githubusercontent.com/render/math?math=Y">, the conversion function from binary to Gray codes is <!-- $f: X \to Y$ --> <img src="https://render.githubusercontent.com/render/math?math=f%3A%20X%20%5Cto%20Y">, so we got:
<!-- $$
\forall x \in X ,\; \exist f(x) = y \in Y\\
\forall x, x' \in X ,\; f(x) = f(x') \Rightarrow x = x'
$$ --> 

<div align="center"><img src="https://render.githubusercontent.com/render/math?math=%5Cforall%20x%20%5Cin%20X%20%2C%5C%3B%20%5Cexist%20f(x)%20%3D%20y%20%5Cin%20Y%5C%5C%0A%5Cforall%20x%2C%20x'%20%5Cin%20X%20%2C%5C%3B%20f(x)%20%3D%20f(x')%20%5CRightarrow%20x%20%3D%20x'"></div>
So the total number of <!-- $n$ --> <img src="https://render.githubusercontent.com/render/math?math=n"> bits of the Gray code is <!-- $2^n$ --> <img src="https://render.githubusercontent.com/render/math?math=2%5En">, which equal to <!-- $n$ --> <img src="https://render.githubusercontent.com/render/math?math=n"> bits of Binary codes.

#### Construction

We will give three ways of generating <!-- $n$ --> <img src="https://render.githubusercontent.com/render/math?math=n"> bits Gray codes and explain the principles behind them.

##### Manual calculation

Starting with the binary number <!-- $0$ --> <img src="https://render.githubusercontent.com/render/math?math=0">, repeat <!-- $2^n - 1$ --> <img src="https://render.githubusercontent.com/render/math?math=2%5En%20-%201"> times to construct all the Gray codes of the <!-- $n$ --> <img src="https://render.githubusercontent.com/render/math?math=n"> bit, following the pattern below:

- Change the value of the rightmost bit
- Changes the left bit of the first bit from the right that is <!-- $1$ --> <img src="https://render.githubusercontent.com/render/math?math=1">

This method is more complex and we usually use the following two methods for construction.

##### Recursive construction

According to the above construction of the Gray code, it is easy to see that the Gray code has a certain symmetrical structure, take <!-- $3$ --> <img src="https://render.githubusercontent.com/render/math?math=3"> bits Gray Code for example:
<!-- $$
0 \; 00 \\
0 \; 01 \\
0 \; 11 \\
0 \; 10 \\ 
--- \\
1 \; 10 \\
1 \; 11 \\
1 \; 01 \\
1 \; 00
$$ --> 

<div align="center"><img src="https://render.githubusercontent.com/render/math?math=0%20%5C%3B%2000%20%5C%5C%0A0%20%5C%3B%2001%20%5C%5C%0A0%20%5C%3B%2011%20%5C%5C%0A0%20%5C%3B%2010%20%5C%5C%20%0A---%20%5C%5C%0A1%20%5C%3B%2010%20%5C%5C%0A1%20%5C%3B%2011%20%5C%5C%0A1%20%5C%3B%2001%20%5C%5C%0A1%20%5C%3B%2000"></div>
A more visual explanation:

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/c/c1/Binary-reflected_Gray_code_construction.svg/500px-Binary-reflected_Gray_code_construction.svg.png)

Except of the highest bit <!-- $0,1$ --> <img src="https://render.githubusercontent.com/render/math?math=0%2C1">, the next two bits which above and below the dividing line are symmetrical, which means: 

Every <!-- $n$ --> <img src="https://render.githubusercontent.com/render/math?math=n"> bits Gray Code can be constructed by <!-- $n-1$ --> <img src="https://render.githubusercontent.com/render/math?math=n-1"> bit Gray Code.

It can be operated as an Recusive program, fake-code below:

```python
GrayCode(power: int) -> List[String, 2 ** power]:
  
  # Termination conditions
  if (n == 1) return ["0", "1"]

  codes = List[String, 2 ** power]
  before: List[String, 2 ** (power - 1)] = GrayCode(n - 1)
  for code in before:
    codes.append("1" + code)
    
  for code in before[::-1]:
    codes.append("0" + code)
    
  return codes
```

##### Calculate construction

We can construct Gray codes from decimal numbers with the following function:

```c++
unsigned int g(unsigned int) { return n^(n >> 1); }
```

And we could prove that in the Gray Code sequence generated according to the above function, the binary bits of two adjacent Gray codes have only one bit difference.

Considering about the diffrence between <!-- $n$ --> <img src="https://render.githubusercontent.com/render/math?math=n"> and <!-- $n + 1$ --> <img src="https://render.githubusercontent.com/render/math?math=n%20%2B%201">. Add up <!-- $1$ --> <img src="https://render.githubusercontent.com/render/math?math=1"> to <!-- $n$ --> <img src="https://render.githubusercontent.com/render/math?math=n"> equaivalent to changing all the consecutive <!-- $1$ --> <img src="https://render.githubusercontent.com/render/math?math=1"> bits into <!-- $0$ --> <img src="https://render.githubusercontent.com/render/math?math=0">, which is inverting. Then change the lowest bit from <!-- $0$ --> <img src="https://render.githubusercontent.com/render/math?math=0"> to <!-- $1$ --> <img src="https://render.githubusercontent.com/render/math?math=1">:
<!-- $$
\begin{aligned}
(n)_2 &= \dots 0 \overbrace{11\cdots 11}^{k \text{ times}} \\
(n + 1)_2 &= \dots 1 \underbrace{00 \cdots 00}_{k \text{ times}}
\end{aligned}
$$ --> 

<div align="center"><img src="https://render.githubusercontent.com/render/math?math=%5Cbegin%7Baligned%7D%0A(n)_2%20%26%3D%20%5Cdots%200%20%5Coverbrace%7B11%5Ccdots%2011%7D%5E%7Bk%20%5Ctext%7B%20times%7D%7D%20%5C%5C%0A(n%20%2B%201)_2%20%26%3D%20%5Cdots%201%20%5Cunderbrace%7B00%20%5Ccdots%2000%7D_%7Bk%20%5Ctext%7B%20times%7D%7D%0A%5Cend%7Baligned%7D"></div>
So when we calculaing <!-- $g(n)$ --> <img src="https://render.githubusercontent.com/render/math?math=g(n)"> and <!-- $g(n + 1)$ --> <img src="https://render.githubusercontent.com/render/math?math=g(n%20%2B%201)">, the last <!-- $k$ --> <img src="https://render.githubusercontent.com/render/math?math=k"> bits will be:
<!-- $$
\underbrace{100 \cdots 00}_{k \text{ times}}
$$ --> 

<div align="center"><img src="https://render.githubusercontent.com/render/math?math=%5Cunderbrace%7B100%20%5Ccdots%2000%7D_%7Bk%20%5Ctext%7B%20times%7D%7D"></div>
and the <!-- $k + 1$ --> <img src="https://render.githubusercontent.com/render/math?math=k%20%2B%201"> bits is different. Because <!-- $n$ --> <img src="https://render.githubusercontent.com/render/math?math=n"> and <!-- $n+1$ --> <img src="https://render.githubusercontent.com/render/math?math=n%2B1"> are the same except for the last <!-- $k+1$ --> <img src="https://render.githubusercontent.com/render/math?math=k%2B1"> bits, therefore, the <!-- $k+1$ --> <img src="https://render.githubusercontent.com/render/math?math=k%2B1"> bit is either XORed by <!-- $1$ --> <img src="https://render.githubusercontent.com/render/math?math=1"> at the same time, or XORed by <!-- $0$ --> <img src="https://render.githubusercontent.com/render/math?math=0"> at the same time. In both cases, the <!-- $k+1$ --> <img src="https://render.githubusercontent.com/render/math?math=k%2B1"> bit is different. The binary bits except the last <!-- $k+1$ --> <img src="https://render.githubusercontent.com/render/math?math=k%2B1"> bits are also subjected to the same XOR operation, and the result is the same.

### Binary encoding container

We use bytes as the smallest container storage unit, which corresponds to `unsigned char` in the C++ type system. Since the smallest unit of operation in c++ is byte, we need to use bit operators to operate on different bits.

#### Container

We use an `unsigned char` array to store bit information. 

Its length is uniform on each platform - `1 byte`. And when we need to set a bit, we find the specified byte variable through the index of the operation firstly. Then perform bit manipulation, which is write down below.

#### Bit write operation

To write a bit, we need to judge in two situations:

- Write a `1` bit

    Assume we need to set a specific bit to `1`, it can be performed by `OR` operation before raw bits with bits `0000...1...0`, which position of `1` is index we need to set. 

- Write a `0` bit

    To write `0` to bits, we could using `AND` bits operation between raw bits and bits set `1111...0...1`, which position of `0` is index we need to set.

#### Bit read operation

When we need to read a specified bit, we can use the `AND` bit operator to perform operations between the original bit string and 0000...1...0, then shift the obtained value to the right and the bit to the right The number is defined by the index of the number of digits read.
The Boolean type conversion of the value obtained in this way is the result we need.

#### Gray code

The Binary class defined in this way can be used directly as the Gray Code class. In order to add the function of generating Gray codes from decimal numbers, we use class inheritance and add the `import` method:

```c++
class Gray: public Binary {
public:
    using Binary::Binary;

public:
    template <typename VT>
    void import(VT value) {
        this->decimal<VT>(value ^ (value >> 1));
    }
};
```

### Set

> In mathematics, a set is a well-defined collection of distinct objects, considered as an object in its own right.The arrangement of the objects in the set does not matter. A set may be denoted by placing its objects between a pair of curly braces.

Typically, the same element can only appear once in the same set. In contrast, the notion of Multiple sets can be used if multiple occurrences of the same element in a set required.

#### Binary operations among sets

Given two sets <!-- $A$ --> <img src="https://render.githubusercontent.com/render/math?math=A"> and <!-- $B$ --> <img src="https://render.githubusercontent.com/render/math?math=B">, define the operation between them:

- Union
    <!-- $$
    A \cup B = \{x | x \in A \or x \in B \}
    $$ --> 

    <div align="center"><img src="https://render.githubusercontent.com/render/math?math=A%20%5Ccup%20B%20%3D%20%5C%7Bx%20%7C%20x%20%5Cin%20A%20%5Cor%20x%20%5Cin%20B%20%5C%7D"></div>

- Intersection
    <!-- $$
    A \cap B = \{x | x \in A \and x \in B \}
    $$ --> 

    <div align="center"><img src="https://render.githubusercontent.com/render/math?math=A%20%5Ccap%20B%20%3D%20%5C%7Bx%20%7C%20x%20%5Cin%20A%20%5Cand%20x%20%5Cin%20B%20%5C%7D"></div>

- Complement, assume <!-- $U$ --> <img src="https://render.githubusercontent.com/render/math?math=U"> is universal set
    <!-- $$
    \bar{A} = \{ x | x \notin A \}
    $$ --> 

    <div align="center"><img src="https://render.githubusercontent.com/render/math?math=%5Cbar%7BA%7D%20%3D%20%5C%7B%20x%20%7C%20x%20%5Cnotin%20A%20%5C%7D"></div>

- Difference
    <!-- $$
    A - B = \{ x | x \in A \and x \notin B \}
    $$ --> 

    <div align="center"><img src="https://render.githubusercontent.com/render/math?math=A%20-%20B%20%3D%20%5C%7B%20x%20%7C%20x%20%5Cin%20A%20%5Cand%20x%20%5Cnotin%20B%20%5C%7D"></div>

- Symmetric Difference
    <!-- $$
    A \Delta B = (A - B) \cup (B - A)
    $$ --> 

    <div align="center"><img src="https://render.githubusercontent.com/render/math?math=A%20%5CDelta%20B%20%3D%20(A%20-%20B)%20%5Ccup%20(B%20-%20A)"></div>

### Hash Table

#### Summary

The data structure of Set is implememted using a **Hash Table**. Inside the hash table, a Vector based on a linked list is used as a slot to store data to resolve conflicts.

Hash table is used in situations where it is necessary to quickly determine whether a given element exists in the data container. In some cases, it can be modified to implement a Ditionary.

We refer to the data stored in the hash table as **element**.

The basic idea of hash table is as follows:

0. Allocate for a certain space in advance and number different positions in the space
1. Use a function to calculate a hash value for a given element
2. Using the calculated hash value as the location, store the given element in the corresponding location
3. When we need to judge whether an element is in the hash table, perform the hash function on it, and check whether the element exists at the obtained position.

Here is an exaple of Hash table using given key for calculation of hash value, which is like Dictionary:

![Dict](https://upload.wikimedia.org/wikipedia/commons/thumb/7/7d/Hash_table_3_1_1_0_1_0_0_SP.svg/630px-Hash_table_3_1_1_0_1_0_0_SP.svg.png)

Before using the hash table, we need to provide an estimate of the size of the hash table: when the size of the hash table is too small and the amount of data used is large, it will cause a lot of conflicts, which will cause performance degradation. 

The set here can implement multiple sets and normal sets at the same time.

For a Gray code with <!-- $n$ --> <img src="https://render.githubusercontent.com/render/math?math=n"> bits, the size of the global set <!-- $S$ --> <img src="https://render.githubusercontent.com/render/math?math=S"> can be easily calculated using the following formula:
<!-- $$
S = 2^n
$$ --> 

<div align="center"><img src="https://render.githubusercontent.com/render/math?math=S%20%3D%202%5En"></div>
Using C++ template-based programming, we can specify different hash functions for different types. 

##### Vector

We use linked list to implement Vector as a data container. The linked list here refers to a singly linked list-that is, each node only stores the pointer and data of the next node.

Simple of Linked list here:

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/6d/Singly-linked-list.svg/816px-Singly-linked-list.svg.png" alt="Vector" style="zoom:50%;" />

The reason for using linked lists is that we cannot determine how many items need to be stored in each slot. Querying nodes in the linked list needs to start from the beginning, traversing the value of each node for comparison. Although the data is obviously too concentrated, it will cause a significant drop in performance.

Our implementation of `Node` is as follows:

```c++
template <typename T>
class Node {
public:
    T* _data;
    Node* _next;

public:
    Node() = delete;
    explicit Node(const T& value) {
        this->_data = new T(value);
        this->_next = nullptr;
    }
    bool isend() const { return (this->_next == nullptr); }
    const T& value() { return *this->_data; }
    ~Node() { free(this->_data); }
};
```

Based on this we can implement a linked list:

```c++
template <typename T>
class Vector {
private:
    size_t _size;
    Node<T>* _header;

public:
    Vector(): _size(0), _header(nullptr) {}
    size_t count() const { return this->_size; }
    const T& get(size_t index);
    bool empty() const;
    bool exist(const T& value) const;
    void remove(const T& value);
    T& index(size_t index);
    T pop(size_t index);
}
```

The time complexity table of the methods:

| Method   | Complexity |
| -------- | ---------- |
| `count`  | <!-- $O(1)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(1)">     |
| `get`    | <!-- $O(n)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(n)">     |
| `empty`  | <!-- $O(1)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(1)">     |
| `exist`  | <!-- $O(n)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(n)">     |
| `remove` | <!-- $O(n)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(n)">     |
| `index`  | <!-- $O(n)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(n)">     |
| `pop`    | <!-- $O(n)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(n)">     |

#### Hash Function

According to the above description, it can be found that the hash function will greatly affect the performance of the hash table:

- If the value of the function is too concentrated, it will increase conflicts and cause performance degradation
- If the function is too complex, it will increase the time of each element operation

And since our task is to store the Gray code in the set, according to the description above, there is a one-to-one correspondence between binary and decimal, we can directly use the gray code corresponding to the decimal value as the hash value:

```c++
template <>
unsigned int hash<Gray>(size_t maxsize, const Gray& bin) {
    return bin.decimal() % maxsize;
}
```

Here, the function template specialization is used to define the gray code type hash function, and in order to ensure that the hash value does not exceed the maximum range of the hash table, the first parameter of the hash function specifies the capacity of the hash table, use `%` modulates the calculated value.

##### Collision

It can be seen that when two elements have the same hash value, a collision will occur. At this time, we can use a linked list to store the colliding elements in order:

![Collision](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/Hash_table_5_0_1_1_1_1_1_LL.svg/900px-Hash_table_5_0_1_1_1_1_1_LL.svg.png)

We call the linked list corresponding to each address a slot.

#### Traversal

When we need to traverse the elements in the hash table, we use an iterator type instance to save the current traversed slot index; at the same time, because each slot may have more than one element, we need another member to save the current slot internal index:

```c++
class Iterator {
    private:
        Vector<T>** _slots;
        size_t _current;
        size_t _index;
        size_t _size;
        ...
}
```

In the process of traversal, the internal member variables are updated, and the pointed slot can be changed.

At the same time, you can add `begin`, `end` methods to the collection to support the range-based for loop in the C++14 standard.

#### Implementation and performance analysis

In implementation, before adding an element, we can selectively check whether the current collection has this element in method `add`:

- Check to ensure that all elements in the table are not the same - *Set*
- You can store multiple identical elements in the same table without checking - *Multiple Set*

```c++
template <typename T>
unsigned int hash(size_t, const T&);

template <typename T>
class Set {
private:
    size_t _size;
    Vector<T>** _slots;
    size_t _count;
    bool _unique;

public:
    size_t count() const;
    void add(const T& value);
    void remove(const T& value);
    bool in(const T& value) const;
}
```

The time complexity table of the methods:

| Method   | Average | Worst Case |
| -------- | ------- | ---------- |
| `count`  | <!-- $O(1)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(1)">  | <!-- $O(1)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(1)">     |
| `add`    | <!-- $O(1)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(1)">  | <!-- $O(n)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(n)">     |
| `in`     | <!-- $O(1)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(1)">  | <!-- $O(n)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(n)">     |
| `remove` | <!-- $O(1)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(1)">  | <!-- $O(n)$ --> <img src="https://render.githubusercontent.com/render/math?math=O(n)">     |

*If here any problems with LaTex rendering, please download README.raw.md for viewing!*
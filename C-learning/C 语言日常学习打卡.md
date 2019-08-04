# 　　　　　　　C 语言日常学习打卡

### Day 1

- 代码1(有关于数组字符串和字符)：

  > ```c
  > #include <stdio.h>
  > 
  > int main()
  > {
  >     char ch1[] = {'a','b','c','\0'}; //要标记反斜杠\0来表示结束输出字符串
  >     char ch2[] = "Hello world!";
  >     char ch3[] = "Yesterday......!";
  >     int arr1[100] = {0}; //所有的数据初始化为零
  >     char str[100]; //定义了一个字符串数组
  >     scanf("%s",str);
  > 
  >     printf("Str is %s", str);//以空格分割数据
  >     printf("%s\n", ch1);
  >     printf("--------\n");
  >     printf("%s\n", ch2);
  >     printf("%s\n", ch3);
  > 
  >     return 0;
  > }
  > 
  > ```

- 代码２(实现追加字符串)

  > ```c
  > #include<stdio.h>
  > 
  > int main()
  > {
  >  char str1[] = "123456";
  >  char str2[] = "abcdef";
  >  char dst[100];
  > 
  >  int i = 0;
  >  while(str1[i] != 0)
  >  {
  >      dst[i] = str1[i];
  >      i++;
  >  }
  > 
  >  int j = 0;
  >  while(str2[j] != 0)
  >  {
  >      dst[i+j] =str2[j];
  >      j++;
  >  }
  > 
  >  dst[i+j] = 0;//字符串的结尾符
  > 
  >  printf("Merge of string:%s",dst);
  > 
  >  return 0;
  > }
  > 
  > ```
  >

### Day 2

- 代码１(const 修饰的问题)

  >```c
  >	int a = 100;
  >	int b = 200;
  >
  >//指向常量的指针
  >	//修饰*，指针指向内存区域不能修改，指针指向可以变
  >	const int *p1 = &a; //等价于int const *p1 = &a;
  >	//*p1 = 111; //err
  >	p1 = &b; //ok
  >
  >//指针常量
  >	//修饰p1，指针指向不能变，指针指向的内存可以修改
  >	int * const p2 = &a;
  >	//p2 = &b; //err
  >	*p2 = 222; //ok
  >```
  >
  >
  >
  >
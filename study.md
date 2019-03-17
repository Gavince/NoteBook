## c语言上机算法

**主要学习链接**

[算法100例](https://blog.csdn.net/zili_mu/article/details/82931147)

[复试上机](https://blog.csdn.net/zzzzlei123123123/article/details/79598774)

[Markdown 学习](https://www.jianshu.com/p/q81RER)

### 多么美丽的长颈鹿

![](/home/gavin/Deeplearning/darknet/data/giraffe.jpg)					

### (1)冒泡排序

```c
#include <stdio.h>

#include <malloc.h>

void Bubble_sort(int*, int);

int main()
{
    int* arr;
    int len, i;

​```c
printf("Len is :");
scanf("%d", &len);

*arr = (int*)malloc(sizeof(int)*len);
printf("Please enter arrry(sort)!\n");
for(i=0; i<len; i++)
{
    printf("Num:");
    scanf("%d",arr+i);
}

Bubble_sort(arr, len);

printf("After sort:");
for (i = 0; i<len; i++)
{
    printf("%d\t",*(arr+i));
}

return 0;
​```

}
void Bubble_sort(int* Arr, int len)//从小到大排序
{
    int i, j;
    int temp;

​```c
for(i=0; i<len-1; i++)
    for(j=0; j< len-i-1; j++)
    {
        if(*(Arr+j)>*(Arr+j+1))
        {
            temp = *(Arr+j);
            *(Arr+j) = *(Arr+j+1);
            *(Arr+j+1) = temp;
        }
    }
​```

}
```

### (2)字符串空格消除

```c
#include <stdio.h>

void Remove_black(char*);

int main()
{
    char ch[] = "He ll o  w    or ld !";

​```c
Remove_black(ch);

return 0;
​```

}
void Remove_black(char* str)
{
    char ch1[110] = {0};
    int i = 0;
    int j = 0;

​```c
while(str[j] != '\0')
{

    if(str[j] != ' ')
    {
        ch1[i] = str[j];
        i++;
    }
    j++;
}
printf("%s", ch1);
​```

}
```

### (3)字符串按照序列排序

```c
include <stdio.h>

int main()
{
    char a[] = "baidu";
    char b[] = "ali";
    char c[] = "jd";
    char* temp;
    int i, j;
    char* str[] = {a, b, c};//char* 的字符指针

​```c
//冒泡排序
for (i = 0;i<3-1; i++)
    for (j = 0;j<3-i-1;j++)
    {
        if(str[j][0]>str[j+1][0])
        {
            temp = str[j];
            str[j] = str[j+1];
            str[j+1] = temp;
        }
    }
printf("NO1 = %s, NO2 = %s, NO3 = %s",str[0],str[1],str[2]);

return 0;
​```

}
```

### (4)动态数组的使用

```c
#include <stdio.h>

#include <malloc.h>

void Bubble_sort(int*, int);

int main()
{
    int* arr;
    int len, i;

printf("Len is :");
scanf("%d", &len);

arr = (int*)malloc(sizeof(int)*len);
printf("Please enter arrry(sort)!\n");
for(i=0; i<len; i++)
{
    printf("Num:");
    scanf("%d",arr+i);
}

Bubble_sort(arr, len);

printf("After sort:");
for (i = 0; i<len; i++)
{
    printf("%d\t",*(arr+i));
}

return 0;
}
void Bubble_sort(int* Arr, int len)//从小到大排序
{
    int i, j;
    int temp;
    
	for(i=0; i<len-1; i++)
    	for(j=0; j< len-i-1; j++)
   		 {
       		 if(*(Arr+j)>*(Arr+j+1))
        	{
            temp = *(Arr+j);
            *(Arr+j) = *(Arr+j+1);
            *(Arr+j+1) = temp;
       		}
    	 }
}
```

### (5)斐波那契数列

```c
#include<stdio.h>
void Fibonacci(int );

int main()
{
    int n;
    printf("Please enter a num:");
    scanf("%d", &n);
    Fibonacci(n);
    return 0;
}

void Fibonacci(int n)
{
    int f1 = 1;
    int f2 = 1;
    int i;
    int f3;

​```c
if(n == 1 || n == 2)
{
    f3 = 1;
}
else
{
    for(i = 2; i<n; i++)
    {
        f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
    }
}
printf("F3 = %d\n",f3);
​```

}
```

### (6)统计各个字母的多少

```c
＃include<stdio.h>

int main()
{
    char c;
    int space = 0, num = 0, vacuble = 0, other = 0;

​```c
//统计里面的数字，字母，空格的数量
while((c = getchar()) != '\n')//getchar 一次只是得到一个字符，并没有真正得到整个字符串
{
    
    if((c >= 'a' && c <= 'z' ) || (c >= 'A' && c <= 'Z'))
    {
        vacuble++;
    }
    else if(c == ' ')
    {
        space++;
    }
    else if(c >= '0'&& c <= '9')
    {
        num++;
    }
    else
    {
        other++;
    }
}

printf("vacuble = %d,sapce = %d, num = %d\n", vacuble, space, num);

return 0;
​```

}
```

### (7)素数的判断

```C
#include<stdio.h>

void Is_Primes(int);
int main()
{
    int n;

​```c
printf("Please enter a num:");
scanf("%d", &n);
Is_Primes(n);

return 0;
​```

}
void Is_Primes(int n)
{
    int i;
    int flag = 0;

​```c
for(i = 1; i<=n; i++)
{
    if(n%i == 0)
    {
        flag++;
    }
}
printf("flag = %d",flag);
if(flag == 2 || flag == 1)
{
    printf("Is primes!");
}
else
{
    printf("No primes!");
}
​```

}
```

### (8)水仙花数的计算（100~999）

```C
#include<stdio.h>

int main()
{
    /*输出100~999所有的水仙花数*/
    int i;

​    int a, b, c;

​```T
for (i = 100; i<1000; i++)
{
    a = i/100;//百位
    b = i%100/10;//十位
    c = i%10;//个位
    if(i == a*a*a + b*b*b + c*c*c)
    {
        printf("Flower:%d\n", i);
    }
}

return 0;
}
```



![美好的生活](/home/gavin/Downloads/timg.jpeg)



### (9)排序后去除重复项目

>**算法描述**：实现对数列的排序后，消除重复项数

```c
/*
    20190317 星期天　多云
*/
# include <stdio.h>
# include <malloc.h>

void Sort(int*, int len);//排序
void Remove(int*,int len);//去除重复项
void Show(int*, int len);//显示数列

int main()
{
    int *p;
    int len, i;

    printf("len is :");
    scanf("%d", &len);
    p = (int*)malloc(sizeof(int)*len);//申请一个动态数组

    printf("Please enter a num:\n");
    for(i = 0; i<len; i++)
    {
        printf("Num :");
        scanf("%d", p+i);
    }
    Sort(p, len);//排序算法
    printf("Before array is:");
    Show(p, len);//排序后的显示数列
    Remove(p, len);
    free(p);

    return 0;
}

void Sort(int* q, int len)
{
    int i, j;
    int temp;

    for(i = 0; i<len-1; i++)
        for(j = 0; j<len-i-1; j++)
        {
            if(*(q+j)>*(q+j+1))
            {
                temp = *(q+j);
                *(q+j) = *(q+j+1);
                *(q+j+1) = temp;
            }
        }
}

void Remove(int* q, int len)
{
    int i;
    int index = 0;
    int *temp;

    temp = (int*)malloc(sizeof(int)*len);
    for(i = 0; i<len; i++)
    {
        if(*(q+i) != *(q+i+1))//消除重复的项数
        {
            *(temp+index) = *(q+i);
            index++;
        }
    }

    printf("\nAfter remove:");
    for (i = 0; i<index; i++)
    {
        printf("%d\t",*(temp+i));
    }
    free(temp);
}

void Show(int *q, int len)
{
    int i;

    for (i = 0; i<len; i++)
    {
        printf("%d\t",*(q+i));
    }
}

```

### (10)递归算法

>**算法描述**：实现一个n的阶乘,算法的实现图例如下：
>
>![](/home/gavin/NoteBook/n!.jpg)

```c
#include<stdio.h>

int Factorial(int);//递归实现

int main()
{
    int n;
    int num;

    printf("Please enter n:");
    scanf("%d", &n);
    num = Factorial(n);

    printf("%d! = %d", n, num);

    return 0;
}

int Factorial(int n)
{
    if(n == 0) return 1;

    if(n > 0)
       return
        n*Factorial(n-1);
}
```






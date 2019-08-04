####  2019.4.3 晴天　图书馆

1. **类的基本操作**

   ```python
   class Car:
       """
       描述车的一些基本特性
       """
       count = 0#定义一个类属性,来记录现在已经创建了多少台车
   
       def __init__(self, brand, perference, mode):
           """
   
           :param brand:品牌
           :param perference:性能
           :param mode: 生产地
           """
           self.brand = brand
           self.perference = perference
           self.mode = mode
           Car.count += 1 #类属性的写法格式，能够被多个实例化的对象所共享
   
       def describe(self):
           """
           描述车的信息
           :return:
           """
           print("%s的性能：%s,生产地：%s"%(self.brand, self.perference, self.mode))
   
   
   class Truck(Car):
       """
       大卡车类
       """
       def __init__(self, brand, perference, mode, load):
           """
   
           :param brand:
           :param perference:
           :param mode:
           :param load:
           """
           super().__init__(brand, perference, mode)
           self.load = load
   
       def cost(self):
           """
   
           :return:
           """
           print("大卡车真的好")
   
       def describe(self):
           """
           重写父类的方法,子类的实例化对象会调用其方法,忽略父类的方法
           :return:
           """
           print("%s的性能：%s，生产地:%s,载重量:%s"%(self.brand, self.perference, self.mode, self.load))
   
   
   car1 = Truck("大众", "良好", "中国", "10kg")
   car1.describe()
   car2 = Truck("奥迪", "优秀", "美国", "100kg")
   car2.describe()
   print(car2.__module__)
   print("总共有多少台车：%d"%(Car.count))
   ```

2. **私有属性的私有方法（伪）**

   ```python
   #私有属性和方法是不希望被外部访问的的内容
   class Woman:
       """
       女人
       """
       def __init__(self, name):
   
           self.name = name
           self.__age = 18 # 加上两个下划线　表示一个私有属性
                           # 不能被外部调用　只能在内部调用
   
       def __secret(self):# 加上两个下划线　表示一个私有方法
   
           print("%s的年龄是%d" % (self.name, self.__age))
   
   
   xm = Woman("xiaomei")
   xm .name
   xm._Woman__secret()
   """
   总结：
   单个下划线＋类名＋私有属性和方法,可以直接访问私有(也即在python不存在正真的私有)
   可以再具有私有属性的中调用一个实例方法调用私有属性，然后进行访问
   """
   ```

3. **类属性和类方法**

   ```python
   class Tool(object):
   
       count = 0 #一个类属性
   
       @classmethod  #类方法需要用(修饰器)标识符标明方法
       def show_tool_count(cls):
   
           print("工具的对象的数量 %d" % cls.count)
   
       #如果不访问类属性/实例属性
       @staticmethod
       def method():
   
           print("静态方法！")
   
       def __init__(self, name):
   
           self.name = name
           Tool.count += 1
   
   
   #调用类方法
   Tool.method() #通过类名 调用静态方法 - 不需要创建对象
   tool1 = Tool("斧头")
   tool1.show_tool_count()
   
   tool1.count += 10 #外部创建了一个实例属性
   print(tool1.count)#实例属性
   del tool1.count
   
   Tool.count += 10
   print(Tool.count)#类属性
   print(tool1.count)
   Tool.show_tool_count()
   """
   小结：
   二：方法
   
   　　1：实例方法：
   
   　　　　def fun_name(self,...):
   
   　　　　　　pass
   
   　　　　外部用实例调用
   
   　　2：静态方法：@staticmethod            
   
   　　　　　　不能访问实例属性！！！   参数不能传入self！！！
   
   　　　　　　与类相关但是不依赖类与实例的方法！！
   
   　　3:类方法：@classmethod
   
   　　　　　　不能访问实例属性！！！   参数必须传入cls！！！
   
   　　　　　　必须传入cls参数（即代表了此类对象-----区别------self代表实例对象），并且用此来调用类属性：cls.类属性名
   
   　　*静态方法与类方法都可以通过类或者实例来调用。其两个的特点都是不能够调用实例属性
   
   """
   ```

4. **类属性**

   ```python
   class Tool(object):
   
       count = 0 #一个类属性
   
       def __init__(self, name):
   
           self.name = name
           Tool.count += 1 #只能这样写
   
   
   tool1 = Tool("斧头")
   tool2 = Tool("榔头")
   tool3 = Tool("起子")
   
   tool3.count = 99 #添加一个count实例属性,不是一个个类属性
   print("对象的总数：%d" % tool3.count)
   print(Tool.count) #可以使用类名.类属性的名称
   
   print("工具对象的总数%d" % Tool.count)
   
   
   """
   小结：
   实例属性属于各个实例所有,互不干扰；
   类属性属于类所有，所有实例共享一个属性；
   不要对实例属性和类属性使用相同的名字,否则将产生难以发现的错误
   """
   ```

   
# Ubuntu18.04安装caffe＋cuda+cudnn+anaconda+OpenCv3.4.1

#### [主要链接](https://blog.csdn.net/CAU_Ayao/article/details/80578600)

#### [cuda简介](https://www.jianshu.com/p/34a504af8d51)

基本软件的链接

1. [搜狗输入法](https://blog.csdn.net/fx_yzjy101/article/details/80243710)
2. [Markdown下载](https://www.typora.io/#linux)
3. [Ubuntu换源](https://blog.csdn.net/zgljl2012/article/details/79065174/)
4. [codeblocks的安装](https://blog.csdn.net/qq_35976351/article/details/82801356)
5. [Opencv的下载地址](https://opencv.org/releases.html)　[安装opencv](https://blog.csdn.net/ZT0518/article/details/82817086)
6. [Deepin Screenshot](https://blog.csdn.net/qq_32767041/article/details/84205219)
7. [网易云音乐](https://blog.csdn.net/Handoking/article/details/81026651)

### 安装出现的问题

1. gcc降版本问题

   > 解决方法：[链接](https://blog.csdn.net/weixin_40920290/article/details/80462734)

2. sudo make runtest -j4 编译出现问题

   > ![](/home/gavin/Desktop/DeepinScreenshot_select-area_20190319075420.png)

   > 解决方案1:[链接](https://blog.csdn.net/yh1226/article/details/85695562)
   >
   > 解决方案2:[链接](https://blog.csdn.net/fanglrui/article/details/79391406)

3. sudo make runtest -j4 编译出现问题

   >![](/home/gavin/Desktop/DeepinScreenshot_select-area_20190319080849.png)

   > **解决方案1**:[链接](https://blog.csdn.net/lily1234567/article/details/83109733)
   >
   > **修改后**:　sudo cp -s /home/gavin/anaconda3/pkgs/hdf5-1.10.2-hba1933b_1/lib/libhdf5_hl.so.100  /usr/lib/libhdf5_hl.so.100

4. sudo make runtest -j4 编译出现问题

   > ![](/home/gavin/Desktop/DeepinScreenshot_select-area_20190319083905.png)

   > **解决方案１:**[链接](https://blog.csdn.net/weili_/article/details/82051126)

5. import caffe 出现问题

   > ![](/home/gavin/Desktop/DeepinScreenshot_select-area_20190319095438.png)

   >**解决方案：**[链接](https://blog.csdn.net/striker_v/article/details/51596628)

6. import caffe 出现问题

   > ![](/home/gavin/Desktop/DeepinScreenshot_select-area_20190319100242.png)

   > **解决方案**：

7. import caffe

   >![](/home/gavin/Desktop/DeepinScreenshot_select-area_20190319111258.png)

   >**解决方案：**

8. 显存问题

   >![](/home/gavin/Desktop/DeepinScreenshot_select-area_20190319112722.png)

   > **解决方案：**[链接](https://blog.csdn.net/dongfang1984/article/details/53259297)

- 测试网络

  [链接](https://www.cnblogs.com/is-Tina/p/7747844.html)

  > ![截图](/home/gavin/Desktop/DeepinScreenshot_select-area_20190319120714.png)

- 附录(常见问题网上解决方案)

  > [链接１](https://blog.csdn.net/m0_37407756/article/details/70789271)
  >
  > [链接２](https://blog.csdn.net/CAU_Ayao/article/details/80582900)


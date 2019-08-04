# Caffe 学习

1. 打印模型图片(需要指定到所选模型的目录下面)

```caffe
python ~/Machine/caffe/python/draw_net.py lenet.prototxt lenet.png --rankdir=BT
```

2. > 2>&1 | tee a.log 重定向　[链接](https://blog.csdn.net/HMH2_YY/article/details/78439095)

3. python版本问题(主要是在plot_training_log.py.example)

   > ![图片](/home/gavin/NoteBook/pictures/DeepinScreenshot_select-area_20190321171932.png)

   >解决方案：[链接](https://blog.csdn.net/betty13006159467/article/details/88665054)

4. caffe log文件的生成

   > [链接](https://blog.csdn.net/HMH2_YY/article/details/78439095)

5. caffe 打印图表

   > ![](/home/gavin/NoteBook/pictures/DeepinScreenshot_gnome-terminal-server_20190322210856.png)


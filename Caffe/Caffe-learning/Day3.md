1. **Caffe 目录结构**

   ```txt
   .
   ├── build -> .build_release //编译好的结果存放处， 子目录结构与主目录结构类似
   ├── cmake
   │   ├── External
   │   ├── Modules
   │   └── Templates
   ├── data	//用于存放原始数据及数据获取脚本
   │   ├── cifar10
   │   ├── ilsvrc12
   │   └── mnist
   ├── distribute	//编译后生成发布包的位置，用于迁移
   │   ├── bin
   │   └── lib
   ├── docker	//方便迁移，使用了Docker
   │   ├── cpu
   │   └── gpu
   ├── docs
   │   ├── images
   │   ├── _layouts
   │   ├── stylesheets
   │   └── tutorial
   │       ├── fig
   │       └── layers
   ├── examples	//用来存放caffe的简单例程
   │   ├── cifar10
   │   ├── cpp_classification
   │   ├── feature_extraction
   │   ├── finetune_flickr_style
   │   ├── finetune_pascal_detection
   │   ├── hdf5_classification
   │   ├── imagenet
   │   ├── images
   │   ├── mnist
   │   │   ├── lenet
   │   │   ├── mnist_test_lmdb
   │   │   └── mnist_train_lmdb
   │   ├── net_surgery
   │   ├── pycaffe
   │   │   └── layers
   │   ├── siamese
   │   └── web_demo
   │       └── templates
   ├── include	//Caffe头文件集中存放的位置
   │   └── caffe
   │       ├── layers
   │       ├── test
   │       └── util
   ├── matlab
   │   ├── +caffe
   │   │   ├── imagenet
   │   │   ├── private
   │   │   └── +test
   │   ├── demo
   │   └── hdf5creation
   ├── models	//存放实例模型
   │   ├── bvlc_alexnet
   │   ├── bvlc_googlenet
   │   ├── bvlc_reference_caffenet
   │   ├── bvlc_reference_rcnn_ilsvrc13
   │   └── finetune_flickr_style
   ├── python	// 用于Python Wrapper
   │   └── caffe
   │       ├── imagenet
   │       ├── proto
   │       ├── __pycache__
   │       └── test
   ├── scripts	//存放脚本
   │   └── travis
   ├── src 	//Caffe 源码
   │   ├── caffe
   │   │   ├── layers //各个层实现的过程
   │   │   ├── proto 	//proto描述文件， 学习数据结构先从这里开始
   │   │   ├── solvers
   │   │   ├── test
   │   │   │   └── test_data
   │   │   └── util
   │   └── gtest
   └── tools	//常用的工具源码
       └── extra
   
   78 directories
   ```

   
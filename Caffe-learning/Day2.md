# Day2（LeNet模型的）

1. **lenet 模型的解析**

   ```protobuf
   name: "LeNet"        	// 网络的名称
   layer {				//定义一个层
     name: "mnist"		//层名
     type: "Data"		   // 层的类型为数据层
     top: "data"			//层的输出blob有两个：data和label
     top: "label"			
     include {			
       phase: TRAIN		//只在训练期间有效
     }
     transform_param {
       scale: 0.00390625		//数据变换使用的数据缩放因子
     }
     data_param {			// 数据层参数
       source: "examples/mnist/mnist_train_lmdb"	//LMDB的路径（数据装换后的位置）
       batch_size: 64			//批量数目，一次只读取64张照片
       backend: LMDB			//数据格式为LMDB
     }
   }
   layer {
     name: "mnist"
     type: "Data"
     top: "data"
     top: "label"
     include {
       phase: TEST    			//**只在分类阶段有效** 
     }
     transform_param {
       scale: 0.00390625
     }
     data_param {
       source: "examples/mnist/mnist_test_lmdb"
       batch_size: 100
       backend: LMDB
     }
   }
   layer {  					//定义一个卷积层
     name: "conv1"
     type: "Convolution"
     bottom: "data"
     top: "conv1"
     param {
       lr_mult: 1		//权值学习速率倍乘因子，1倍表示保持与全局参数一致
     }
     param {
       lr_mult: 2		//bias 学习速率倍乘因子，是全局参数的两倍
     }
     convolution_param { 		//卷积计算参数
       num_output: 20
       kernel_size: 5
       stride: 1
       weight_filler {			//权值使用Xavier填充器
         type: "xavier"
       }
       bias_filler {
         type: "constant"		//bias 使用常数填充器，默认为0
       }
     }
   }
   layer {					//定义新的下采样层pool1，输入conv1，输出blob为pool1
     name: "pool1"
     type: "Pooling"
     bottom: "conv1"
     top: "pool1"
     pooling_param {
       pool: MAX
       kernel_size: 2
       stride: 2
     }
   }
   layer {
     name: "conv2"
     type: "Convolution"
     bottom: "pool1"
     top: "conv2"
     param {
       lr_mult: 1
     }
     param {
       lr_mult: 2
     }
     convolution_param {
       num_output: 50
       kernel_size: 5
       stride: 1
       weight_filler {
         type: "xavier"
       }
       bias_filler {
         type: "constant"
       }
     }
   }
   layer {
     name: "pool2"
     type: "Pooling"
     bottom: "conv2"
     top: "pool2"
     pooling_param {
       pool: MAX
       kernel_size: 2
       stride: 2
     }
   }
   layer {   // 定义一个全连接层 输入：pool2 输出：ip1 
     name: "ip1"
     type: "InnerProduct"
     bottom: "pool2"
     top: "ip1"
     param {
       lr_mult: 1
     }
     param {
       lr_mult: 2
     }
     inner_product_param { //全连接层参数
       num_output: 500  //该层输出元素个数为500
       weight_filler {
         type: "xavier"
       }
       bias_filler {
         type: "constant"
       }
     }
   }
   layer {				//新的非线性层，用Relu方法
     name: "relu1"
     type: "ReLU"
     bottom: "ip1"
     top: "ip1"
   }
   layer {   // 全连接层
     name: "ip2"
     type: "InnerProduct"
     bottom: "ip1"
     top: "ip2"
     param {
       lr_mult: 1
     }
     param {
       lr_mult: 2
     }
     inner_product_param {
       num_output: 10
       weight_filler {
         type: "xavier"
       }
       bias_filler {
         type: "constant"
       }
     }
   }
   layer {
     name: "accuracy"
     type: "Accuracy"
     bottom: "ip2"
     bottom: "label"
     top: "accuracy"
     include {
       phase: TEST
     }
   }
   layer {
     name: "loss"
     type: "SoftmaxWithLoss"
     bottom: "ip2"
     bottom: "label"
     top: "loss"
   }
   ```

   2.   **LeNet 网络**

   ![lenet模型图](/home/gavin/NoteBook/pictures/lenet.png)

   3. **参数**

      ```protobuf
      # The train/test net protocol buffer definition
      net: "examples/mnist/lenet_train_test.prototxt"
      # test_iter specifies how many forward passes the test should carry out.
      # In the case of MNIST, we have test batch size 100 and 100 test iterations,
      # covering the full 10,000 testing images.
      test_iter: 100
      # Carry out testing every 500 training iterations.
      test_interval: 500
      # The base learning rate, momentum and the weight decay of the network.
      base_lr: 0.01
      momentum: 0.9
      weight_decay: 0.0005
      # The learning rate policy
      lr_policy: "inv"
      gamma: 0.0001
      power: 0.75
      # Display every 100 iterations
      display: 100
      # The maximum number of iterations
      max_iter: 10000
      # snapshot intermediate results
      snapshot: 5000
      snapshot_prefix: "examples/mnist/lenet"
      # solver mode: CPU or GPU
      solver_mode: GPU
      ```

      4. **log**

         ```log
         I0321 17:36:53.040315 14186 upgrade_proto.cpp:1113] snapshot_prefix was a directory and is replaced to examples/mnist/lenet/lenet_solver
         I0321 17:36:53.040676 14186 caffe.cpp:204] Using GPUs 0
         I0321 17:36:53.054731 14186 caffe.cpp:209] GPU 0: GeForce GTX 950M
         I0321 17:36:53.292666 14186 solver.cpp:45] Initializing solver from parameters: 
         test_iter: 100
         test_interval: 500
         base_lr: 0.01
         display: 100
         max_iter: 10000
         lr_policy: "inv"
         gamma: 0.0001
         power: 0.75
         momentum: 0.9
         weight_decay: 0.0005
         snapshot: 5000
         snapshot_prefix: "examples/mnist/lenet/lenet_solver"
         solver_mode: GPU
         device_id: 0
         net: "examples/mnist/lenet_train_test.prototxt"
         train_state {
           level: 0
           stage: ""
         }
         I0321 17:36:53.292860 14186 solver.cpp:102] Creating training net from net file: examples/mnist/lenet_train_test.prototxt
         I0321 17:36:53.293077 14186 net.cpp:296] The NetState phase (0) differed from the phase (1) specified by a rule in layer mnist
         I0321 17:36:53.293099 14186 net.cpp:296] The NetState phase (0) differed from the phase (1) specified by a rule in layer accuracy
         I0321 17:36:53.293166 14186 net.cpp:53] Initializing net from parameters: 
         name: "LeNet"
         state {
           phase: TRAIN
           level: 0
           stage: ""
         }
         layer {
           name: "mnist"
           type: "Data"
           top: "data"
           top: "label"
           include {
             phase: TRAIN
           }
           transform_param {
             scale: 0.00390625
           }
           data_param {
             source: "examples/mnist/mnist_train_lmdb"
             batch_size: 64
             backend: LMDB
           }
         }
         layer {
           name: "conv1"
           type: "Convolution"
           bottom: "data"
           top: "conv1"
           param {
             lr_mult: 1
           }
           param {
             lr_mult: 2
           }
           convolution_param {
             num_output: 20
             kernel_size: 5
             stride: 1
             weight_filler {
               type: "xavier"
             }
             bias_filler {
               type: "constant"
             }
           }
         }
         layer {
           name: "pool1"
           type: "Pooling"
           bottom: "conv1"
           top: "pool1"
           pooling_param {
             pool: MAX
             kernel_size: 2
             stride: 2
           }
         }
         layer {
           name: "conv2"
           type: "Convolution"
           bottom: "pool1"
           top: "conv2"
           param {
             lr_mult: 1
           }
           param {
             lr_mult: 2
           }
           convolution_param {
             num_output: 50
             kernel_size: 5
             stride: 1
             weight_filler {
               type: "xavier"
             }
             bias_filler {
               type: "constant"
             }
           }
         }
         layer {
           name: "pool2"
           type: "Pooling"
           bottom: "conv2"
           top: "pool2"
           pooling_param {
             pool: MAX
             kernel_size: 2
             stride: 2
           }
         }
         layer {
           name: "ip1"
           type: "InnerProduct"
           bottom: "pool2"
           top: "ip1"
           param {
             lr_mult: 1
           }
           param {
             lr_mult: 2
           }
           inner_product_param {
             num_output: 500
             weight_filler {
               type: "xavier"
             }
             bias_filler {
               type: "constant"
             }
           }
         }
         layer {
           name: "relu1"
           type: "ReLU"
           bottom: "ip1"
           top: "ip1"
         }
         layer {
           name: "ip2"
           type: "InnerProduct"
           bottom: "ip1"
           top: "ip2"
           param {
             lr_mult: 1
           }
           param {
             lr_mult: 2
           }
           inner_product_param {
             num_output: 10
             weight_filler {
               type: "xavier"
             }
             bias_filler {
               type: "constant"
             }
           }
         }
         layer {
           name: "loss"
           type: "SoftmaxWithLoss"
           bottom: "ip2"
           bottom: "label"
           top: "loss"
         }
         I0321 17:36:53.293229 14186 layer_factory.hpp:77] Creating layer mnist
         I0321 17:36:53.293315 14186 db_lmdb.cpp:35] Opened lmdb examples/mnist/mnist_train_lmdb
         I0321 17:36:53.293344 14186 net.cpp:86] Creating Layer mnist
         I0321 17:36:53.293352 14186 net.cpp:382] mnist -> data
         I0321 17:36:53.293373 14186 net.cpp:382] mnist -> label
         I0321 17:36:53.293941 14186 data_layer.cpp:45] output data size: 64,1,28,28
         I0321 17:36:53.294965 14186 net.cpp:124] Setting up mnist
         I0321 17:36:53.294983 14186 net.cpp:131] Top shape: 64 1 28 28 (50176)
         I0321 17:36:53.294988 14186 net.cpp:131] Top shape: 64 (64)
         I0321 17:36:53.294992 14186 net.cpp:139] Memory required for data: 200960
         I0321 17:36:53.295001 14186 layer_factory.hpp:77] Creating layer conv1
         I0321 17:36:53.295074 14186 net.cpp:86] Creating Layer conv1
         I0321 17:36:53.295081 14186 net.cpp:408] conv1 <- data
         I0321 17:36:53.295112 14186 net.cpp:382] conv1 -> conv1
         I0321 17:36:53.815847 14186 net.cpp:124] Setting up conv1
         I0321 17:36:53.815884 14186 net.cpp:131] Top shape: 64 20 24 24 (737280)
         I0321 17:36:53.815889 14186 net.cpp:139] Memory required for data: 3150080
         I0321 17:36:53.815912 14186 layer_factory.hpp:77] Creating layer pool1
         I0321 17:36:53.815958 14186 net.cpp:86] Creating Layer pool1
         I0321 17:36:53.815990 14186 net.cpp:408] pool1 <- conv1
         I0321 17:36:53.816015 14186 net.cpp:382] pool1 -> pool1
         I0321 17:36:53.816102 14186 net.cpp:124] Setting up pool1
         I0321 17:36:53.816121 14186 net.cpp:131] Top shape: 64 20 12 12 (184320)
         I0321 17:36:53.816124 14186 net.cpp:139] Memory required for data: 3887360
         I0321 17:36:53.816126 14186 layer_factory.hpp:77] Creating layer conv2
         I0321 17:36:53.816138 14186 net.cpp:86] Creating Layer conv2
         I0321 17:36:53.816143 14186 net.cpp:408] conv2 <- pool1
         I0321 17:36:53.816149 14186 net.cpp:382] conv2 -> conv2
         I0321 17:36:53.818715 14186 net.cpp:124] Setting up conv2
         I0321 17:36:53.818733 14186 net.cpp:131] Top shape: 64 50 8 8 (204800)
         I0321 17:36:53.818737 14186 net.cpp:139] Memory required for data: 4706560
         I0321 17:36:53.818747 14186 layer_factory.hpp:77] Creating layer pool2
         I0321 17:36:53.818755 14186 net.cpp:86] Creating Layer pool2
         I0321 17:36:53.818760 14186 net.cpp:408] pool2 <- conv2
         I0321 17:36:53.818769 14186 net.cpp:382] pool2 -> pool2
         I0321 17:36:53.818830 14186 net.cpp:124] Setting up pool2
         I0321 17:36:53.818836 14186 net.cpp:131] Top shape: 64 50 4 4 (51200)
         I0321 17:36:53.818850 14186 net.cpp:139] Memory required for data: 4911360
         I0321 17:36:53.818852 14186 layer_factory.hpp:77] Creating layer ip1
         I0321 17:36:53.818859 14186 net.cpp:86] Creating Layer ip1
         I0321 17:36:53.818862 14186 net.cpp:408] ip1 <- pool2
         I0321 17:36:53.818868 14186 net.cpp:382] ip1 -> ip1
         I0321 17:36:53.821492 14186 net.cpp:124] Setting up ip1
         I0321 17:36:53.821509 14186 net.cpp:131] Top shape: 64 500 (32000)
         I0321 17:36:53.821511 14186 net.cpp:139] Memory required for data: 5039360
         I0321 17:36:53.821523 14186 layer_factory.hpp:77] Creating layer relu1
         I0321 17:36:53.821532 14186 net.cpp:86] Creating Layer relu1
         I0321 17:36:53.821537 14186 net.cpp:408] relu1 <- ip1
         I0321 17:36:53.821544 14186 net.cpp:369] relu1 -> ip1 (in-place)
         I0321 17:36:53.822340 14186 net.cpp:124] Setting up relu1
         I0321 17:36:53.822362 14186 net.cpp:131] Top shape: 64 500 (32000)
         I0321 17:36:53.822365 14186 net.cpp:139] Memory required for data: 5167360
         I0321 17:36:53.822367 14186 layer_factory.hpp:77] Creating layer ip2
         I0321 17:36:53.822377 14186 net.cpp:86] Creating Layer ip2
         I0321 17:36:53.822381 14186 net.cpp:408] ip2 <- ip1
         I0321 17:36:53.822387 14186 net.cpp:382] ip2 -> ip2
         I0321 17:36:53.822999 14186 net.cpp:124] Setting up ip2
         I0321 17:36:53.823019 14186 net.cpp:131] Top shape: 64 10 (640)
         I0321 17:36:53.823022 14186 net.cpp:139] Memory required for data: 5169920
         I0321 17:36:53.823029 14186 layer_factory.hpp:77] Creating layer loss
         I0321 17:36:53.823037 14186 net.cpp:86] Creating Layer loss
         I0321 17:36:53.823040 14186 net.cpp:408] loss <- ip2
         I0321 17:36:53.823046 14186 net.cpp:408] loss <- label
         I0321 17:36:53.823053 14186 net.cpp:382] loss -> loss
         I0321 17:36:53.823066 14186 layer_factory.hpp:77] Creating layer loss
         I0321 17:36:53.823896 14186 net.cpp:124] Setting up loss
         I0321 17:36:53.823916 14186 net.cpp:131] Top shape: (1)
         I0321 17:36:53.823918 14186 net.cpp:134]     with loss weight 1
         I0321 17:36:53.823937 14186 net.cpp:139] Memory required for data: 5169924
         I0321 17:36:53.823941 14186 net.cpp:200] loss needs backward computation.
         I0321 17:36:53.823952 14186 net.cpp:200] ip2 needs backward computation.
         I0321 17:36:53.823956 14186 net.cpp:200] relu1 needs backward computation.
         I0321 17:36:53.823961 14186 net.cpp:200] ip1 needs backward computation.
         I0321 17:36:53.823964 14186 net.cpp:200] pool2 needs backward computation.
         I0321 17:36:53.823968 14186 net.cpp:200] conv2 needs backward computation.
         I0321 17:36:53.823972 14186 net.cpp:200] pool1 needs backward computation.
         I0321 17:36:53.823977 14186 net.cpp:200] conv1 needs backward computation.
         I0321 17:36:53.823982 14186 net.cpp:202] mnist does not need backward computation.
         I0321 17:36:53.823985 14186 net.cpp:244] This network produces output loss
         I0321 17:36:53.823998 14186 net.cpp:257] Network initialization done.
         I0321 17:36:53.824156 14186 solver.cpp:190] Creating test net (#0) specified by net file: examples/mnist/lenet_train_test.prototxt
         I0321 17:36:53.824199 14186 net.cpp:296] The NetState phase (1) differed from the phase (0) specified by a rule in layer mnist
         I0321 17:36:53.824270 14186 net.cpp:53] Initializing net from parameters: 
         name: "LeNet"
         state {
           phase: TEST
         }
         layer {
           name: "mnist"
           type: "Data"
           top: "data"
           top: "label"
           include {
             phase: TEST
           }
           transform_param {
             scale: 0.00390625
           }
           data_param {
             source: "examples/mnist/mnist_test_lmdb"
             batch_size: 100
             backend: LMDB
           }
         }
         layer {
           name: "conv1"
           type: "Convolution"
           bottom: "data"
           top: "conv1"
           param {
             lr_mult: 1
           }
           param {
             lr_mult: 2
           }
           convolution_param {
             num_output: 20
             kernel_size: 5
             stride: 1
             weight_filler {
               type: "xavier"
             }
             bias_filler {
               type: "constant"
             }
           }
         }
         layer {
           name: "pool1"
           type: "Pooling"
           bottom: "conv1"
           top: "pool1"
           pooling_param {
             pool: MAX
             kernel_size: 2
             stride: 2
           }
         }
         layer {
           name: "conv2"
           type: "Convolution"
           bottom: "pool1"
           top: "conv2"
           param {
             lr_mult: 1
           }
           param {
             lr_mult: 2
           }
           convolution_param {
             num_output: 50
             kernel_size: 5
             stride: 1
             weight_filler {
               type: "xavier"
             }
             bias_filler {
               type: "constant"
             }
           }
         }
         layer {
           name: "pool2"
           type: "Pooling"
           bottom: "conv2"
           top: "pool2"
           pooling_param {
             pool: MAX
             kernel_size: 2
             stride: 2
           }
         }
         layer {
           name: "ip1"
           type: "InnerProduct"
           bottom: "pool2"
           top: "ip1"
           param {
             lr_mult: 1
           }
           param {
             lr_mult: 2
           }
           inner_product_param {
             num_output: 500
             weight_filler {
               type: "xavier"
             }
             bias_filler {
               type: "constant"
             }
           }
         }
         layer {
           name: "relu1"
           type: "ReLU"
           bottom: "ip1"
           top: "ip1"
         }
         layer {
           name: "ip2"
           type: "InnerProduct"
           bottom: "ip1"
           top: "ip2"
           param {
             lr_mult: 1
           }
           param {
             lr_mult: 2
           }
           inner_product_param {
             num_output: 10
             weight_filler {
               type: "xavier"
             }
             bias_filler {
               type: "constant"
             }
           }
         }
         layer {
           name: "accuracy"
           type: "Accuracy"
           bottom: "ip2"
           bottom: "label"
           top: "accuracy"
           include {
             phase: TEST
           }
         }
         layer {
           name: "loss"
           type: "SoftmaxWithLoss"
           bottom: "ip2"
           bottom: "label"
           top: "loss"
         }
         I0321 17:36:53.824347 14186 layer_factory.hpp:77] Creating layer mnist
         I0321 17:36:53.824411 14186 db_lmdb.cpp:35] Opened lmdb examples/mnist/mnist_test_lmdb
         I0321 17:36:53.824426 14186 net.cpp:86] Creating Layer mnist
         I0321 17:36:53.824439 14186 net.cpp:382] mnist -> data
         I0321 17:36:53.824450 14186 net.cpp:382] mnist -> label
         I0321 17:36:53.824574 14186 data_layer.cpp:45] output data size: 100,1,28,28
         I0321 17:36:53.826339 14186 net.cpp:124] Setting up mnist
         I0321 17:36:53.826364 14186 net.cpp:131] Top shape: 100 1 28 28 (78400)
         I0321 17:36:53.826370 14186 net.cpp:131] Top shape: 100 (100)
         I0321 17:36:53.826372 14186 net.cpp:139] Memory required for data: 314000
         I0321 17:36:53.826378 14186 layer_factory.hpp:77] Creating layer label_mnist_1_split
         I0321 17:36:53.826393 14186 net.cpp:86] Creating Layer label_mnist_1_split
         I0321 17:36:53.826398 14186 net.cpp:408] label_mnist_1_split <- label
         I0321 17:36:53.826407 14186 net.cpp:382] label_mnist_1_split -> label_mnist_1_split_0
         I0321 17:36:53.826418 14186 net.cpp:382] label_mnist_1_split -> label_mnist_1_split_1
         I0321 17:36:53.826524 14186 net.cpp:124] Setting up label_mnist_1_split
         I0321 17:36:53.826550 14186 net.cpp:131] Top shape: 100 (100)
         I0321 17:36:53.826565 14186 net.cpp:131] Top shape: 100 (100)
         I0321 17:36:53.826578 14186 net.cpp:139] Memory required for data: 314800
         I0321 17:36:53.826591 14186 layer_factory.hpp:77] Creating layer conv1
         I0321 17:36:53.826618 14186 net.cpp:86] Creating Layer conv1
         I0321 17:36:53.826625 14186 net.cpp:408] conv1 <- data
         I0321 17:36:53.826634 14186 net.cpp:382] conv1 -> conv1
         I0321 17:36:53.830312 14186 net.cpp:124] Setting up conv1
         I0321 17:36:53.830333 14186 net.cpp:131] Top shape: 100 20 24 24 (1152000)
         I0321 17:36:53.830338 14186 net.cpp:139] Memory required for data: 4922800
         I0321 17:36:53.830377 14186 layer_factory.hpp:77] Creating layer pool1
         I0321 17:36:53.830392 14186 net.cpp:86] Creating Layer pool1
         I0321 17:36:53.830399 14186 net.cpp:408] pool1 <- conv1
         I0321 17:36:53.830410 14186 net.cpp:382] pool1 -> pool1
         I0321 17:36:53.830468 14186 net.cpp:124] Setting up pool1
         I0321 17:36:53.830477 14186 net.cpp:131] Top shape: 100 20 12 12 (288000)
         I0321 17:36:53.830480 14186 net.cpp:139] Memory required for data: 6074800
         I0321 17:36:53.830483 14186 layer_factory.hpp:77] Creating layer conv2
         I0321 17:36:53.830500 14186 net.cpp:86] Creating Layer conv2
         I0321 17:36:53.830507 14186 net.cpp:408] conv2 <- pool1
         I0321 17:36:53.830513 14186 net.cpp:382] conv2 -> conv2
         I0321 17:36:53.833215 14186 net.cpp:124] Setting up conv2
         I0321 17:36:53.833231 14186 net.cpp:131] Top shape: 100 50 8 8 (320000)
         I0321 17:36:53.833235 14186 net.cpp:139] Memory required for data: 7354800
         I0321 17:36:53.833245 14186 layer_factory.hpp:77] Creating layer pool2
         I0321 17:36:53.833256 14186 net.cpp:86] Creating Layer pool2
         I0321 17:36:53.833262 14186 net.cpp:408] pool2 <- conv2
         I0321 17:36:53.833271 14186 net.cpp:382] pool2 -> pool2
         I0321 17:36:53.833334 14186 net.cpp:124] Setting up pool2
         I0321 17:36:53.833341 14186 net.cpp:131] Top shape: 100 50 4 4 (80000)
         I0321 17:36:53.833354 14186 net.cpp:139] Memory required for data: 7674800
         I0321 17:36:53.833356 14186 layer_factory.hpp:77] Creating layer ip1
         I0321 17:36:53.833364 14186 net.cpp:86] Creating Layer ip1
         I0321 17:36:53.833369 14186 net.cpp:408] ip1 <- pool2
         I0321 17:36:53.833377 14186 net.cpp:382] ip1 -> ip1
         I0321 17:36:53.835999 14186 net.cpp:124] Setting up ip1
         I0321 17:36:53.836012 14186 net.cpp:131] Top shape: 100 500 (50000)
         I0321 17:36:53.836015 14186 net.cpp:139] Memory required for data: 7874800
         I0321 17:36:53.836026 14186 layer_factory.hpp:77] Creating layer relu1
         I0321 17:36:53.836035 14186 net.cpp:86] Creating Layer relu1
         I0321 17:36:53.836040 14186 net.cpp:408] relu1 <- ip1
         I0321 17:36:53.836046 14186 net.cpp:369] relu1 -> ip1 (in-place)
         I0321 17:36:53.836855 14186 net.cpp:124] Setting up relu1
         I0321 17:36:53.836876 14186 net.cpp:131] Top shape: 100 500 (50000)
         I0321 17:36:53.836879 14186 net.cpp:139] Memory required for data: 8074800
         I0321 17:36:53.836882 14186 layer_factory.hpp:77] Creating layer ip2
         I0321 17:36:53.836894 14186 net.cpp:86] Creating Layer ip2
         I0321 17:36:53.836899 14186 net.cpp:408] ip2 <- ip1
         I0321 17:36:53.836906 14186 net.cpp:382] ip2 -> ip2
         I0321 17:36:53.837052 14186 net.cpp:124] Setting up ip2
         I0321 17:36:53.837059 14186 net.cpp:131] Top shape: 100 10 (1000)
         I0321 17:36:53.837061 14186 net.cpp:139] Memory required for data: 8078800
         I0321 17:36:53.837069 14186 layer_factory.hpp:77] Creating layer ip2_ip2_0_split
         I0321 17:36:53.837079 14186 net.cpp:86] Creating Layer ip2_ip2_0_split
         I0321 17:36:53.837082 14186 net.cpp:408] ip2_ip2_0_split <- ip2
         I0321 17:36:53.837088 14186 net.cpp:382] ip2_ip2_0_split -> ip2_ip2_0_split_0
         I0321 17:36:53.837095 14186 net.cpp:382] ip2_ip2_0_split -> ip2_ip2_0_split_1
         I0321 17:36:53.837134 14186 net.cpp:124] Setting up ip2_ip2_0_split
         I0321 17:36:53.837141 14186 net.cpp:131] Top shape: 100 10 (1000)
         I0321 17:36:53.837143 14186 net.cpp:131] Top shape: 100 10 (1000)
         I0321 17:36:53.837146 14186 net.cpp:139] Memory required for data: 8086800
         I0321 17:36:53.837150 14186 layer_factory.hpp:77] Creating layer accuracy
         I0321 17:36:53.837160 14186 net.cpp:86] Creating Layer accuracy
         I0321 17:36:53.837167 14186 net.cpp:408] accuracy <- ip2_ip2_0_split_0
         I0321 17:36:53.837172 14186 net.cpp:408] accuracy <- label_mnist_1_split_0
         I0321 17:36:53.837178 14186 net.cpp:382] accuracy -> accuracy
         I0321 17:36:53.837188 14186 net.cpp:124] Setting up accuracy
         I0321 17:36:53.837196 14186 net.cpp:131] Top shape: (1)
         I0321 17:36:53.837200 14186 net.cpp:139] Memory required for data: 8086804
         I0321 17:36:53.837203 14186 layer_factory.hpp:77] Creating layer loss
         I0321 17:36:53.837213 14186 net.cpp:86] Creating Layer loss
         I0321 17:36:53.837218 14186 net.cpp:408] loss <- ip2_ip2_0_split_1
         I0321 17:36:53.837240 14186 net.cpp:408] loss <- label_mnist_1_split_1
         I0321 17:36:53.837249 14186 net.cpp:382] loss -> loss
         I0321 17:36:53.837258 14186 layer_factory.hpp:77] Creating layer loss
         I0321 17:36:53.838076 14186 net.cpp:124] Setting up loss
         I0321 17:36:53.838086 14186 net.cpp:131] Top shape: (1)
         I0321 17:36:53.838088 14186 net.cpp:134]     with loss weight 1
         I0321 17:36:53.838104 14186 net.cpp:139] Memory required for data: 8086808
         I0321 17:36:53.838109 14186 net.cpp:200] loss needs backward computation.
         I0321 17:36:53.838114 14186 net.cpp:202] accuracy does not need backward computation.
         I0321 17:36:53.838119 14186 net.cpp:200] ip2_ip2_0_split needs backward computation.
         I0321 17:36:53.838124 14186 net.cpp:200] ip2 needs backward computation.
         I0321 17:36:53.838127 14186 net.cpp:200] relu1 needs backward computation.
         I0321 17:36:53.838131 14186 net.cpp:200] ip1 needs backward computation.
         I0321 17:36:53.838135 14186 net.cpp:200] pool2 needs backward computation.
         I0321 17:36:53.838140 14186 net.cpp:200] conv2 needs backward computation.
         I0321 17:36:53.838145 14186 net.cpp:200] pool1 needs backward computation.
         I0321 17:36:53.838150 14186 net.cpp:200] conv1 needs backward computation.
         I0321 17:36:53.838155 14186 net.cpp:202] label_mnist_1_split does not need backward computation.
         I0321 17:36:53.838160 14186 net.cpp:202] mnist does not need backward computation.
         I0321 17:36:53.838163 14186 net.cpp:244] This network produces output accuracy
         I0321 17:36:53.838168 14186 net.cpp:244] This network produces output loss
         I0321 17:36:53.838181 14186 net.cpp:257] Network initialization done.
         I0321 17:36:53.838232 14186 solver.cpp:57] Solver scaffolding done.
         I0321 17:36:53.838543 14186 caffe.cpp:239] Starting Optimization
         I0321 17:36:53.838549 14186 solver.cpp:289] Solving LeNet
         I0321 17:36:53.838552 14186 solver.cpp:290] Learning Rate Policy: inv
         I0321 17:36:53.840003 14186 solver.cpp:347] Iteration 0, Testing net (#0)
         I0321 17:36:54.054323 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:36:54.062096 14186 solver.cpp:414]     Test net output #0: accuracy = 0.1078
         I0321 17:36:54.062131 14186 solver.cpp:414]     Test net output #1: loss = 2.32374 (* 1 = 2.32374 loss)
         I0321 17:36:54.069643 14186 solver.cpp:239] Iteration 0 (-2.32449e-30 iter/s, 0.231025s/100 iters), loss = 2.28711
         I0321 17:36:54.069710 14186 solver.cpp:258]     Train net output #0: loss = 2.28711 (* 1 = 2.28711 loss)
         I0321 17:36:54.069738 14186 sgd_solver.cpp:112] Iteration 0, lr = 0.01
         I0321 17:36:54.764420 14186 solver.cpp:239] Iteration 100 (144.056 iter/s, 0.694174s/100 iters), loss = 0.231436
         I0321 17:36:54.764458 14186 solver.cpp:258]     Train net output #0: loss = 0.231436 (* 1 = 0.231436 loss)
         I0321 17:36:54.764469 14186 sgd_solver.cpp:112] Iteration 100, lr = 0.00992565
         I0321 17:36:55.450439 14186 solver.cpp:239] Iteration 200 (145.781 iter/s, 0.685959s/100 iters), loss = 0.148665
         I0321 17:36:55.450472 14186 solver.cpp:258]     Train net output #0: loss = 0.148665 (* 1 = 0.148665 loss)
         I0321 17:36:55.450479 14186 sgd_solver.cpp:112] Iteration 200, lr = 0.00985258
         I0321 17:36:56.137159 14186 solver.cpp:239] Iteration 300 (145.633 iter/s, 0.68666s/100 iters), loss = 0.165326
         I0321 17:36:56.137194 14186 solver.cpp:258]     Train net output #0: loss = 0.165326 (* 1 = 0.165326 loss)
         I0321 17:36:56.137200 14186 sgd_solver.cpp:112] Iteration 300, lr = 0.00978075
         I0321 17:36:56.826916 14186 solver.cpp:239] Iteration 400 (144.992 iter/s, 0.689692s/100 iters), loss = 0.0595556
         I0321 17:36:56.826946 14186 solver.cpp:258]     Train net output #0: loss = 0.0595556 (* 1 = 0.0595556 loss)
         I0321 17:36:56.826952 14186 sgd_solver.cpp:112] Iteration 400, lr = 0.00971013
         I0321 17:36:57.506897 14186 solver.cpp:347] Iteration 500, Testing net (#0)
         I0321 17:36:57.717358 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:36:57.724813 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9719
         I0321 17:36:57.724846 14186 solver.cpp:414]     Test net output #1: loss = 0.0840058 (* 1 = 0.0840058 loss)
         I0321 17:36:57.731014 14186 solver.cpp:239] Iteration 500 (110.615 iter/s, 0.904033s/100 iters), loss = 0.107035
         I0321 17:36:57.731070 14186 solver.cpp:258]     Train net output #0: loss = 0.107035 (* 1 = 0.107035 loss)
         I0321 17:36:57.731082 14186 sgd_solver.cpp:112] Iteration 500, lr = 0.00964069
         I0321 17:36:58.421355 14186 solver.cpp:239] Iteration 600 (144.873 iter/s, 0.69026s/100 iters), loss = 0.106062
         I0321 17:36:58.421388 14186 solver.cpp:258]     Train net output #0: loss = 0.106062 (* 1 = 0.106062 loss)
         I0321 17:36:58.421396 14186 sgd_solver.cpp:112] Iteration 600, lr = 0.0095724
         I0321 17:36:59.112923 14186 solver.cpp:239] Iteration 700 (144.612 iter/s, 0.691507s/100 iters), loss = 0.112926
         I0321 17:36:59.112964 14186 solver.cpp:258]     Train net output #0: loss = 0.112926 (* 1 = 0.112926 loss)
         I0321 17:36:59.112977 14186 sgd_solver.cpp:112] Iteration 700, lr = 0.00950522
         I0321 17:36:59.799790 14186 solver.cpp:239] Iteration 800 (145.603 iter/s, 0.686801s/100 iters), loss = 0.184272
         I0321 17:36:59.799826 14186 solver.cpp:258]     Train net output #0: loss = 0.184272 (* 1 = 0.184272 loss)
         I0321 17:36:59.799834 14186 sgd_solver.cpp:112] Iteration 800, lr = 0.00943913
         I0321 17:37:00.494211 14186 solver.cpp:239] Iteration 900 (144.017 iter/s, 0.69436s/100 iters), loss = 0.163555
         I0321 17:37:00.494251 14186 solver.cpp:258]     Train net output #0: loss = 0.163555 (* 1 = 0.163555 loss)
         I0321 17:37:00.494262 14186 sgd_solver.cpp:112] Iteration 900, lr = 0.00937411
         I0321 17:37:00.726097 14193 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:01.180172 14186 solver.cpp:347] Iteration 1000, Testing net (#0)
         I0321 17:37:01.388419 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:01.396993 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9814
         I0321 17:37:01.397032 14186 solver.cpp:414]     Test net output #1: loss = 0.0547186 (* 1 = 0.0547186 loss)
         I0321 17:37:01.404949 14186 solver.cpp:239] Iteration 1000 (109.809 iter/s, 0.910669s/100 iters), loss = 0.100698
         I0321 17:37:01.405001 14186 solver.cpp:258]     Train net output #0: loss = 0.100698 (* 1 = 0.100698 loss)
         I0321 17:37:01.405009 14186 sgd_solver.cpp:112] Iteration 1000, lr = 0.00931012
         I0321 17:37:02.092242 14186 solver.cpp:239] Iteration 1100 (145.514 iter/s, 0.687221s/100 iters), loss = 0.00583671
         I0321 17:37:02.092284 14186 solver.cpp:258]     Train net output #0: loss = 0.00583661 (* 1 = 0.00583661 loss)
         I0321 17:37:02.092293 14186 sgd_solver.cpp:112] Iteration 1100, lr = 0.00924715
         I0321 17:37:02.778784 14186 solver.cpp:239] Iteration 1200 (145.672 iter/s, 0.686472s/100 iters), loss = 0.0143196
         I0321 17:37:02.778827 14186 solver.cpp:258]     Train net output #0: loss = 0.0143195 (* 1 = 0.0143195 loss)
         I0321 17:37:02.778838 14186 sgd_solver.cpp:112] Iteration 1200, lr = 0.00918515
         I0321 17:37:03.466939 14186 solver.cpp:239] Iteration 1300 (145.33 iter/s, 0.688089s/100 iters), loss = 0.0185389
         I0321 17:37:03.466979 14186 solver.cpp:258]     Train net output #0: loss = 0.0185388 (* 1 = 0.0185388 loss)
         I0321 17:37:03.466986 14186 sgd_solver.cpp:112] Iteration 1300, lr = 0.00912412
         I0321 17:37:04.157732 14186 solver.cpp:239] Iteration 1400 (144.775 iter/s, 0.690729s/100 iters), loss = 0.00702524
         I0321 17:37:04.157770 14186 solver.cpp:258]     Train net output #0: loss = 0.00702518 (* 1 = 0.00702518 loss)
         I0321 17:37:04.157778 14186 sgd_solver.cpp:112] Iteration 1400, lr = 0.00906403
         I0321 17:37:04.838759 14186 solver.cpp:347] Iteration 1500, Testing net (#0)
         I0321 17:37:05.046963 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:05.053436 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9852
         I0321 17:37:05.053472 14186 solver.cpp:414]     Test net output #1: loss = 0.0474708 (* 1 = 0.0474708 loss)
         I0321 17:37:05.059765 14186 solver.cpp:239] Iteration 1500 (110.87 iter/s, 0.901956s/100 iters), loss = 0.0843106
         I0321 17:37:05.059823 14186 solver.cpp:258]     Train net output #0: loss = 0.0843105 (* 1 = 0.0843105 loss)
         I0321 17:37:05.059835 14186 sgd_solver.cpp:112] Iteration 1500, lr = 0.00900485
         I0321 17:37:05.749503 14186 solver.cpp:239] Iteration 1600 (145.008 iter/s, 0.689616s/100 iters), loss = 0.0763663
         I0321 17:37:05.749545 14186 solver.cpp:258]     Train net output #0: loss = 0.0763662 (* 1 = 0.0763662 loss)
         I0321 17:37:05.749557 14186 sgd_solver.cpp:112] Iteration 1600, lr = 0.00894657
         I0321 17:37:06.440747 14186 solver.cpp:239] Iteration 1700 (144.681 iter/s, 0.691177s/100 iters), loss = 0.0152583
         I0321 17:37:06.440785 14186 solver.cpp:258]     Train net output #0: loss = 0.0152582 (* 1 = 0.0152582 loss)
         I0321 17:37:06.440793 14186 sgd_solver.cpp:112] Iteration 1700, lr = 0.00888916
         I0321 17:37:07.133358 14186 solver.cpp:239] Iteration 1800 (144.395 iter/s, 0.692546s/100 iters), loss = 0.0289478
         I0321 17:37:07.133390 14186 solver.cpp:258]     Train net output #0: loss = 0.0289477 (* 1 = 0.0289477 loss)
         I0321 17:37:07.133399 14186 sgd_solver.cpp:112] Iteration 1800, lr = 0.0088326
         I0321 17:37:07.617445 14193 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:07.828814 14186 solver.cpp:239] Iteration 1900 (143.803 iter/s, 0.695395s/100 iters), loss = 0.107276
         I0321 17:37:07.828852 14186 solver.cpp:258]     Train net output #0: loss = 0.107276 (* 1 = 0.107276 loss)
         I0321 17:37:07.828861 14186 sgd_solver.cpp:112] Iteration 1900, lr = 0.00877687
         I0321 17:37:08.512044 14186 solver.cpp:347] Iteration 2000, Testing net (#0)
         I0321 17:37:08.719350 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:08.727061 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9859
         I0321 17:37:08.727092 14186 solver.cpp:414]     Test net output #1: loss = 0.0415617 (* 1 = 0.0415617 loss)
         I0321 17:37:08.733372 14186 solver.cpp:239] Iteration 2000 (110.561 iter/s, 0.904479s/100 iters), loss = 0.0149348
         I0321 17:37:08.733422 14186 solver.cpp:258]     Train net output #0: loss = 0.0149347 (* 1 = 0.0149347 loss)
         I0321 17:37:08.733438 14186 sgd_solver.cpp:112] Iteration 2000, lr = 0.00872196
         I0321 17:37:09.422060 14186 solver.cpp:239] Iteration 2100 (145.219 iter/s, 0.688615s/100 iters), loss = 0.0270313
         I0321 17:37:09.422101 14186 solver.cpp:258]     Train net output #0: loss = 0.0270312 (* 1 = 0.0270312 loss)
         I0321 17:37:09.422111 14186 sgd_solver.cpp:112] Iteration 2100, lr = 0.00866784
         I0321 17:37:10.113766 14186 solver.cpp:239] Iteration 2200 (144.584 iter/s, 0.691642s/100 iters), loss = 0.0221009
         I0321 17:37:10.113811 14186 solver.cpp:258]     Train net output #0: loss = 0.0221009 (* 1 = 0.0221009 loss)
         I0321 17:37:10.113823 14186 sgd_solver.cpp:112] Iteration 2200, lr = 0.0086145
         I0321 17:37:10.804498 14186 solver.cpp:239] Iteration 2300 (144.788 iter/s, 0.690666s/100 iters), loss = 0.128096
         I0321 17:37:10.804535 14186 solver.cpp:258]     Train net output #0: loss = 0.128096 (* 1 = 0.128096 loss)
         I0321 17:37:10.804546 14186 sgd_solver.cpp:112] Iteration 2300, lr = 0.00856192
         I0321 17:37:11.494989 14186 solver.cpp:239] Iteration 2400 (144.837 iter/s, 0.690432s/100 iters), loss = 0.0119442
         I0321 17:37:11.495023 14186 solver.cpp:258]     Train net output #0: loss = 0.0119442 (* 1 = 0.0119442 loss)
         I0321 17:37:11.495029 14186 sgd_solver.cpp:112] Iteration 2400, lr = 0.00851008
         I0321 17:37:12.176226 14186 solver.cpp:347] Iteration 2500, Testing net (#0)
         I0321 17:37:12.385469 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:12.392807 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9834
         I0321 17:37:12.392838 14186 solver.cpp:414]     Test net output #1: loss = 0.0529501 (* 1 = 0.0529501 loss)
         I0321 17:37:12.399106 14186 solver.cpp:239] Iteration 2500 (110.613 iter/s, 0.904051s/100 iters), loss = 0.0199883
         I0321 17:37:12.399147 14186 solver.cpp:258]     Train net output #0: loss = 0.0199883 (* 1 = 0.0199883 loss)
         I0321 17:37:12.399154 14186 sgd_solver.cpp:112] Iteration 2500, lr = 0.00845897
         I0321 17:37:13.092748 14186 solver.cpp:239] Iteration 2600 (144.18 iter/s, 0.693575s/100 iters), loss = 0.0462023
         I0321 17:37:13.092788 14186 solver.cpp:258]     Train net output #0: loss = 0.0462023 (* 1 = 0.0462023 loss)
         I0321 17:37:13.092797 14186 sgd_solver.cpp:112] Iteration 2600, lr = 0.00840857
         I0321 17:37:13.780076 14186 solver.cpp:239] Iteration 2700 (145.505 iter/s, 0.687261s/100 iters), loss = 0.0361092
         I0321 17:37:13.780118 14186 solver.cpp:258]     Train net output #0: loss = 0.0361092 (* 1 = 0.0361092 loss)
         I0321 17:37:13.780127 14186 sgd_solver.cpp:112] Iteration 2700, lr = 0.00835886
         I0321 17:37:14.465260 14186 solver.cpp:239] Iteration 2800 (145.961 iter/s, 0.685117s/100 iters), loss = 0.0011111
         I0321 17:37:14.465297 14186 solver.cpp:258]     Train net output #0: loss = 0.0011111 (* 1 = 0.0011111 loss)
         I0321 17:37:14.465306 14186 sgd_solver.cpp:112] Iteration 2800, lr = 0.00830984
         I0321 17:37:14.527343 14193 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:15.165187 14186 solver.cpp:239] Iteration 2900 (142.885 iter/s, 0.699865s/100 iters), loss = 0.0179292
         I0321 17:37:15.165225 14186 solver.cpp:258]     Train net output #0: loss = 0.0179292 (* 1 = 0.0179292 loss)
         I0321 17:37:15.165230 14186 sgd_solver.cpp:112] Iteration 2900, lr = 0.00826148
         I0321 17:37:15.845149 14186 solver.cpp:347] Iteration 3000, Testing net (#0)
         I0321 17:37:16.051123 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:16.058786 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9885
         I0321 17:37:16.058814 14186 solver.cpp:414]     Test net output #1: loss = 0.0371024 (* 1 = 0.0371024 loss)
         I0321 17:37:16.065467 14186 solver.cpp:239] Iteration 3000 (111.087 iter/s, 0.900197s/100 iters), loss = 0.0090931
         I0321 17:37:16.065518 14186 solver.cpp:258]     Train net output #0: loss = 0.00909309 (* 1 = 0.00909309 loss)
         I0321 17:37:16.065531 14186 sgd_solver.cpp:112] Iteration 3000, lr = 0.00821377
         I0321 17:37:16.754936 14186 solver.cpp:239] Iteration 3100 (145.156 iter/s, 0.688912s/100 iters), loss = 0.0147705
         I0321 17:37:16.754969 14186 solver.cpp:258]     Train net output #0: loss = 0.0147705 (* 1 = 0.0147705 loss)
         I0321 17:37:16.754976 14186 sgd_solver.cpp:112] Iteration 3100, lr = 0.0081667
         I0321 17:37:17.442896 14186 solver.cpp:239] Iteration 3200 (145.369 iter/s, 0.687903s/100 iters), loss = 0.0055816
         I0321 17:37:17.442939 14186 solver.cpp:258]     Train net output #0: loss = 0.00558156 (* 1 = 0.00558156 loss)
         I0321 17:37:17.442946 14186 sgd_solver.cpp:112] Iteration 3200, lr = 0.00812025
         I0321 17:37:18.126127 14186 solver.cpp:239] Iteration 3300 (146.378 iter/s, 0.683163s/100 iters), loss = 0.022177
         I0321 17:37:18.126160 14186 solver.cpp:258]     Train net output #0: loss = 0.0221769 (* 1 = 0.0221769 loss)
         I0321 17:37:18.126168 14186 sgd_solver.cpp:112] Iteration 3300, lr = 0.00807442
         I0321 17:37:18.817870 14186 solver.cpp:239] Iteration 3400 (144.575 iter/s, 0.691684s/100 iters), loss = 0.00694077
         I0321 17:37:18.817906 14186 solver.cpp:258]     Train net output #0: loss = 0.00694074 (* 1 = 0.00694074 loss)
         I0321 17:37:18.817926 14186 sgd_solver.cpp:112] Iteration 3400, lr = 0.00802918
         I0321 17:37:19.493414 14186 solver.cpp:347] Iteration 3500, Testing net (#0)
         I0321 17:37:19.704710 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:19.712149 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9856
         I0321 17:37:19.712180 14186 solver.cpp:414]     Test net output #1: loss = 0.0459739 (* 1 = 0.0459739 loss)
         I0321 17:37:19.718447 14186 solver.cpp:239] Iteration 3500 (111.048 iter/s, 0.900511s/100 iters), loss = 0.00498116
         I0321 17:37:19.718490 14186 solver.cpp:258]     Train net output #0: loss = 0.00498111 (* 1 = 0.00498111 loss)
         I0321 17:37:19.718498 14186 sgd_solver.cpp:112] Iteration 3500, lr = 0.00798454
         I0321 17:37:20.411341 14186 solver.cpp:239] Iteration 3600 (144.337 iter/s, 0.692825s/100 iters), loss = 0.0285249
         I0321 17:37:20.411378 14186 solver.cpp:258]     Train net output #0: loss = 0.0285248 (* 1 = 0.0285248 loss)
         I0321 17:37:20.411386 14186 sgd_solver.cpp:112] Iteration 3600, lr = 0.00794046
         I0321 17:37:21.100358 14186 solver.cpp:239] Iteration 3700 (145.147 iter/s, 0.688957s/100 iters), loss = 0.0176604
         I0321 17:37:21.100400 14186 solver.cpp:258]     Train net output #0: loss = 0.0176603 (* 1 = 0.0176603 loss)
         I0321 17:37:21.100446 14186 sgd_solver.cpp:112] Iteration 3700, lr = 0.00789695
         I0321 17:37:21.412600 14193 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:21.790105 14186 solver.cpp:239] Iteration 3800 (144.995 iter/s, 0.68968s/100 iters), loss = 0.0131787
         I0321 17:37:21.790143 14186 solver.cpp:258]     Train net output #0: loss = 0.0131786 (* 1 = 0.0131786 loss)
         I0321 17:37:21.790150 14186 sgd_solver.cpp:112] Iteration 3800, lr = 0.007854
         I0321 17:37:22.473935 14186 solver.cpp:239] Iteration 3900 (146.249 iter/s, 0.683768s/100 iters), loss = 0.0386029
         I0321 17:37:22.473969 14186 solver.cpp:258]     Train net output #0: loss = 0.0386029 (* 1 = 0.0386029 loss)
         I0321 17:37:22.473978 14186 sgd_solver.cpp:112] Iteration 3900, lr = 0.00781158
         I0321 17:37:23.155109 14186 solver.cpp:347] Iteration 4000, Testing net (#0)
         I0321 17:37:23.363662 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:23.371101 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9899
         I0321 17:37:23.371134 14186 solver.cpp:414]     Test net output #1: loss = 0.0303656 (* 1 = 0.0303656 loss)
         I0321 17:37:23.377439 14186 solver.cpp:239] Iteration 4000 (110.688 iter/s, 0.90344s/100 iters), loss = 0.0135227
         I0321 17:37:23.377485 14186 solver.cpp:258]     Train net output #0: loss = 0.0135226 (* 1 = 0.0135226 loss)
         I0321 17:37:23.377494 14186 sgd_solver.cpp:112] Iteration 4000, lr = 0.0077697
         I0321 17:37:24.067708 14186 solver.cpp:239] Iteration 4100 (144.907 iter/s, 0.690097s/100 iters), loss = 0.0179965
         I0321 17:37:24.067744 14186 solver.cpp:258]     Train net output #0: loss = 0.0179964 (* 1 = 0.0179964 loss)
         I0321 17:37:24.067754 14186 sgd_solver.cpp:112] Iteration 4100, lr = 0.00772833
         I0321 17:37:24.757782 14186 solver.cpp:239] Iteration 4200 (144.925 iter/s, 0.690013s/100 iters), loss = 0.0112684
         I0321 17:37:24.757817 14186 solver.cpp:258]     Train net output #0: loss = 0.0112683 (* 1 = 0.0112683 loss)
         I0321 17:37:24.757822 14186 sgd_solver.cpp:112] Iteration 4200, lr = 0.00768748
         I0321 17:37:25.453296 14186 solver.cpp:239] Iteration 4300 (143.792 iter/s, 0.69545s/100 iters), loss = 0.0331706
         I0321 17:37:25.453346 14186 solver.cpp:258]     Train net output #0: loss = 0.0331705 (* 1 = 0.0331705 loss)
         I0321 17:37:25.453359 14186 sgd_solver.cpp:112] Iteration 4300, lr = 0.00764712
         I0321 17:37:26.144446 14186 solver.cpp:239] Iteration 4400 (144.701 iter/s, 0.691082s/100 iters), loss = 0.0132631
         I0321 17:37:26.144507 14186 solver.cpp:258]     Train net output #0: loss = 0.013263 (* 1 = 0.013263 loss)
         I0321 17:37:26.144526 14186 sgd_solver.cpp:112] Iteration 4400, lr = 0.00760726
         I0321 17:37:26.822340 14186 solver.cpp:347] Iteration 4500, Testing net (#0)
         I0321 17:37:27.032770 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:27.040190 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9879
         I0321 17:37:27.040213 14186 solver.cpp:414]     Test net output #1: loss = 0.036961 (* 1 = 0.036961 loss)
         I0321 17:37:27.046785 14186 solver.cpp:239] Iteration 4500 (110.835 iter/s, 0.902244s/100 iters), loss = 0.00506846
         I0321 17:37:27.046835 14186 solver.cpp:258]     Train net output #0: loss = 0.00506836 (* 1 = 0.00506836 loss)
         I0321 17:37:27.046844 14186 sgd_solver.cpp:112] Iteration 4500, lr = 0.00756788
         I0321 17:37:27.735915 14186 solver.cpp:239] Iteration 4600 (145.228 iter/s, 0.688572s/100 iters), loss = 0.0130338
         I0321 17:37:27.735962 14186 solver.cpp:258]     Train net output #0: loss = 0.0130337 (* 1 = 0.0130337 loss)
         I0321 17:37:27.735975 14186 sgd_solver.cpp:112] Iteration 4600, lr = 0.00752897
         I0321 17:37:28.306006 14193 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:28.424226 14186 solver.cpp:239] Iteration 4700 (145.298 iter/s, 0.688242s/100 iters), loss = 0.00983115
         I0321 17:37:28.424265 14186 solver.cpp:258]     Train net output #0: loss = 0.00983103 (* 1 = 0.00983103 loss)
         I0321 17:37:28.424275 14186 sgd_solver.cpp:112] Iteration 4700, lr = 0.00749052
         I0321 17:37:29.109009 14186 solver.cpp:239] Iteration 4800 (146.045 iter/s, 0.68472s/100 iters), loss = 0.0189935
         I0321 17:37:29.109046 14186 solver.cpp:258]     Train net output #0: loss = 0.0189934 (* 1 = 0.0189934 loss)
         I0321 17:37:29.109053 14186 sgd_solver.cpp:112] Iteration 4800, lr = 0.00745253
         I0321 17:37:29.796532 14186 solver.cpp:239] Iteration 4900 (145.463 iter/s, 0.687461s/100 iters), loss = 0.00938823
         I0321 17:37:29.796571 14186 solver.cpp:258]     Train net output #0: loss = 0.00938809 (* 1 = 0.00938809 loss)
         I0321 17:37:29.796578 14186 sgd_solver.cpp:112] Iteration 4900, lr = 0.00741498
         I0321 17:37:30.475172 14186 solver.cpp:464] Snapshotting to binary proto file examples/mnist/lenet/lenet_solver_iter_5000.caffemodel
         I0321 17:37:30.489665 14186 sgd_solver.cpp:284] Snapshotting solver state to binary proto file examples/mnist/lenet/lenet_solver_iter_5000.solverstate
         I0321 17:37:30.492760 14186 solver.cpp:347] Iteration 5000, Testing net (#0)
         I0321 17:37:30.697100 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:30.704600 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9898
         I0321 17:37:30.704633 14186 solver.cpp:414]     Test net output #1: loss = 0.0305021 (* 1 = 0.0305021 loss)
         I0321 17:37:30.711011 14186 solver.cpp:239] Iteration 5000 (109.36 iter/s, 0.914411s/100 iters), loss = 0.03099
         I0321 17:37:30.711053 14186 solver.cpp:258]     Train net output #0: loss = 0.0309899 (* 1 = 0.0309899 loss)
         I0321 17:37:30.711062 14186 sgd_solver.cpp:112] Iteration 5000, lr = 0.00737788
         I0321 17:37:31.392047 14186 solver.cpp:239] Iteration 5100 (146.85 iter/s, 0.680969s/100 iters), loss = 0.0172542
         I0321 17:37:31.392083 14186 solver.cpp:258]     Train net output #0: loss = 0.0172541 (* 1 = 0.0172541 loss)
         I0321 17:37:31.392102 14186 sgd_solver.cpp:112] Iteration 5100, lr = 0.0073412
         I0321 17:37:32.082185 14186 solver.cpp:239] Iteration 5200 (144.911 iter/s, 0.690076s/100 iters), loss = 0.00745322
         I0321 17:37:32.082221 14186 solver.cpp:258]     Train net output #0: loss = 0.00745309 (* 1 = 0.00745309 loss)
         I0321 17:37:32.082228 14186 sgd_solver.cpp:112] Iteration 5200, lr = 0.00730495
         I0321 17:37:32.766340 14186 solver.cpp:239] Iteration 5300 (146.179 iter/s, 0.684094s/100 iters), loss = 0.00153736
         I0321 17:37:32.766376 14186 solver.cpp:258]     Train net output #0: loss = 0.00153722 (* 1 = 0.00153722 loss)
         I0321 17:37:32.766382 14186 sgd_solver.cpp:112] Iteration 5300, lr = 0.00726911
         I0321 17:37:33.451647 14186 solver.cpp:239] Iteration 5400 (145.943 iter/s, 0.685201s/100 iters), loss = 0.00904315
         I0321 17:37:33.451685 14186 solver.cpp:258]     Train net output #0: loss = 0.00904301 (* 1 = 0.00904301 loss)
         I0321 17:37:33.451694 14186 sgd_solver.cpp:112] Iteration 5400, lr = 0.00723368
         I0321 17:37:34.128152 14186 solver.cpp:347] Iteration 5500, Testing net (#0)
         I0321 17:37:34.336278 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:34.343739 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9901
         I0321 17:37:34.343771 14186 solver.cpp:414]     Test net output #1: loss = 0.0296925 (* 1 = 0.0296925 loss)
         I0321 17:37:34.350088 14186 solver.cpp:239] Iteration 5500 (111.312 iter/s, 0.898373s/100 iters), loss = 0.00818316
         I0321 17:37:34.350129 14186 solver.cpp:258]     Train net output #0: loss = 0.00818303 (* 1 = 0.00818303 loss)
         I0321 17:37:34.350137 14186 sgd_solver.cpp:112] Iteration 5500, lr = 0.00719865
         I0321 17:37:35.054950 14186 solver.cpp:239] Iteration 5600 (141.887 iter/s, 0.704787s/100 iters), loss = 0.00114008
         I0321 17:37:35.055006 14186 solver.cpp:258]     Train net output #0: loss = 0.00113995 (* 1 = 0.00113995 loss)
         I0321 17:37:35.055021 14186 sgd_solver.cpp:112] Iteration 5600, lr = 0.00716402
         I0321 17:37:35.201992 14193 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:35.753119 14186 solver.cpp:239] Iteration 5700 (143.247 iter/s, 0.698094s/100 iters), loss = 0.00443383
         I0321 17:37:35.753155 14186 solver.cpp:258]     Train net output #0: loss = 0.00443369 (* 1 = 0.00443369 loss)
         I0321 17:37:35.753161 14186 sgd_solver.cpp:112] Iteration 5700, lr = 0.00712977
         I0321 17:37:36.441409 14186 solver.cpp:239] Iteration 5800 (145.301 iter/s, 0.688228s/100 iters), loss = 0.0297283
         I0321 17:37:36.441447 14186 solver.cpp:258]     Train net output #0: loss = 0.0297282 (* 1 = 0.0297282 loss)
         I0321 17:37:36.441452 14186 sgd_solver.cpp:112] Iteration 5800, lr = 0.0070959
         I0321 17:37:37.133239 14186 solver.cpp:239] Iteration 5900 (144.557 iter/s, 0.691768s/100 iters), loss = 0.00837125
         I0321 17:37:37.133280 14186 solver.cpp:258]     Train net output #0: loss = 0.0083711 (* 1 = 0.0083711 loss)
         I0321 17:37:37.133287 14186 sgd_solver.cpp:112] Iteration 5900, lr = 0.0070624
         I0321 17:37:37.813768 14186 solver.cpp:347] Iteration 6000, Testing net (#0)
         I0321 17:37:38.022833 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:38.030100 14186 solver.cpp:414]     Test net output #0: accuracy = 0.99
         I0321 17:37:38.030128 14186 solver.cpp:414]     Test net output #1: loss = 0.0290969 (* 1 = 0.0290969 loss)
         I0321 17:37:38.036778 14186 solver.cpp:239] Iteration 6000 (110.686 iter/s, 0.90346s/100 iters), loss = 0.00392532
         I0321 17:37:38.036835 14186 solver.cpp:258]     Train net output #0: loss = 0.00392517 (* 1 = 0.00392517 loss)
         I0321 17:37:38.036846 14186 sgd_solver.cpp:112] Iteration 6000, lr = 0.00702927
         I0321 17:37:38.726523 14186 solver.cpp:239] Iteration 6100 (145.099 iter/s, 0.689184s/100 iters), loss = 0.00112453
         I0321 17:37:38.726563 14186 solver.cpp:258]     Train net output #0: loss = 0.00112438 (* 1 = 0.00112438 loss)
         I0321 17:37:38.726572 14186 sgd_solver.cpp:112] Iteration 6100, lr = 0.0069965
         I0321 17:37:39.416851 14186 solver.cpp:239] Iteration 6200 (144.872 iter/s, 0.690263s/100 iters), loss = 0.00724698
         I0321 17:37:39.416895 14186 solver.cpp:258]     Train net output #0: loss = 0.00724682 (* 1 = 0.00724682 loss)
         I0321 17:37:39.416908 14186 sgd_solver.cpp:112] Iteration 6200, lr = 0.00696408
         I0321 17:37:40.111409 14186 solver.cpp:239] Iteration 6300 (143.99 iter/s, 0.694492s/100 iters), loss = 0.00985702
         I0321 17:37:40.111450 14186 solver.cpp:258]     Train net output #0: loss = 0.00985688 (* 1 = 0.00985688 loss)
         I0321 17:37:40.111460 14186 sgd_solver.cpp:112] Iteration 6300, lr = 0.00693201
         I0321 17:37:40.805438 14186 solver.cpp:239] Iteration 6400 (144.099 iter/s, 0.693968s/100 iters), loss = 0.00413558
         I0321 17:37:40.805472 14186 solver.cpp:258]     Train net output #0: loss = 0.00413544 (* 1 = 0.00413544 loss)
         I0321 17:37:40.805480 14186 sgd_solver.cpp:112] Iteration 6400, lr = 0.00690029
         I0321 17:37:41.483916 14186 solver.cpp:347] Iteration 6500, Testing net (#0)
         I0321 17:37:41.695384 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:41.703146 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9901
         I0321 17:37:41.703172 14186 solver.cpp:414]     Test net output #1: loss = 0.0308437 (* 1 = 0.0308437 loss)
         I0321 17:37:41.709345 14186 solver.cpp:239] Iteration 6500 (110.639 iter/s, 0.903842s/100 iters), loss = 0.0098571
         I0321 17:37:41.709389 14186 solver.cpp:258]     Train net output #0: loss = 0.00985698 (* 1 = 0.00985698 loss)
         I0321 17:37:41.709399 14186 sgd_solver.cpp:112] Iteration 6500, lr = 0.0068689
         I0321 17:37:42.115360 14193 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:42.405858 14186 solver.cpp:239] Iteration 6600 (143.585 iter/s, 0.696453s/100 iters), loss = 0.0167376
         I0321 17:37:42.405901 14186 solver.cpp:258]     Train net output #0: loss = 0.0167375 (* 1 = 0.0167375 loss)
         I0321 17:37:42.405913 14186 sgd_solver.cpp:112] Iteration 6600, lr = 0.00683784
         I0321 17:37:43.094805 14186 solver.cpp:239] Iteration 6700 (145.163 iter/s, 0.688883s/100 iters), loss = 0.0093986
         I0321 17:37:43.094843 14186 solver.cpp:258]     Train net output #0: loss = 0.00939846 (* 1 = 0.00939846 loss)
         I0321 17:37:43.094851 14186 sgd_solver.cpp:112] Iteration 6700, lr = 0.00680711
         I0321 17:37:43.785157 14186 solver.cpp:239] Iteration 6800 (144.866 iter/s, 0.690291s/100 iters), loss = 0.00308178
         I0321 17:37:43.785192 14186 solver.cpp:258]     Train net output #0: loss = 0.00308163 (* 1 = 0.00308163 loss)
         I0321 17:37:43.785198 14186 sgd_solver.cpp:112] Iteration 6800, lr = 0.0067767
         I0321 17:37:44.470257 14186 solver.cpp:239] Iteration 6900 (145.977 iter/s, 0.685037s/100 iters), loss = 0.00469418
         I0321 17:37:44.470293 14186 solver.cpp:258]     Train net output #0: loss = 0.00469404 (* 1 = 0.00469404 loss)
         I0321 17:37:44.470300 14186 sgd_solver.cpp:112] Iteration 6900, lr = 0.0067466
         I0321 17:37:45.151285 14186 solver.cpp:347] Iteration 7000, Testing net (#0)
         I0321 17:37:45.360307 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:45.367748 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9907
         I0321 17:37:45.367780 14186 solver.cpp:414]     Test net output #1: loss = 0.0279737 (* 1 = 0.0279737 loss)
         I0321 17:37:45.374174 14186 solver.cpp:239] Iteration 7000 (110.644 iter/s, 0.903801s/100 iters), loss = 0.00740426
         I0321 17:37:45.374217 14186 solver.cpp:258]     Train net output #0: loss = 0.00740411 (* 1 = 0.00740411 loss)
         I0321 17:37:45.374258 14186 sgd_solver.cpp:112] Iteration 7000, lr = 0.00671681
         I0321 17:37:46.060153 14186 solver.cpp:239] Iteration 7100 (145.791 iter/s, 0.685912s/100 iters), loss = 0.0113288
         I0321 17:37:46.060191 14186 solver.cpp:258]     Train net output #0: loss = 0.0113286 (* 1 = 0.0113286 loss)
         I0321 17:37:46.060199 14186 sgd_solver.cpp:112] Iteration 7100, lr = 0.00668733
         I0321 17:37:46.750802 14186 solver.cpp:239] Iteration 7200 (144.805 iter/s, 0.690586s/100 iters), loss = 0.00669761
         I0321 17:37:46.750836 14186 solver.cpp:258]     Train net output #0: loss = 0.00669746 (* 1 = 0.00669746 loss)
         I0321 17:37:46.750844 14186 sgd_solver.cpp:112] Iteration 7200, lr = 0.00665815
         I0321 17:37:47.432025 14186 solver.cpp:239] Iteration 7300 (146.808 iter/s, 0.681163s/100 iters), loss = 0.0240019
         I0321 17:37:47.432062 14186 solver.cpp:258]     Train net output #0: loss = 0.0240017 (* 1 = 0.0240017 loss)
         I0321 17:37:47.432070 14186 sgd_solver.cpp:112] Iteration 7300, lr = 0.00662927
         I0321 17:37:48.116753 14186 solver.cpp:239] Iteration 7400 (146.056 iter/s, 0.684669s/100 iters), loss = 0.00575735
         I0321 17:37:48.116788 14186 solver.cpp:258]     Train net output #0: loss = 0.00575719 (* 1 = 0.00575719 loss)
         I0321 17:37:48.116796 14186 sgd_solver.cpp:112] Iteration 7400, lr = 0.00660067
         I0321 17:37:48.769345 14193 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:48.791462 14186 solver.cpp:347] Iteration 7500, Testing net (#0)
         I0321 17:37:48.998901 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:49.006486 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9902
         I0321 17:37:49.006511 14186 solver.cpp:414]     Test net output #1: loss = 0.0299996 (* 1 = 0.0299996 loss)
         I0321 17:37:49.012643 14186 solver.cpp:239] Iteration 7500 (111.629 iter/s, 0.895821s/100 iters), loss = 0.00147341
         I0321 17:37:49.012686 14186 solver.cpp:258]     Train net output #0: loss = 0.00147325 (* 1 = 0.00147325 loss)
         I0321 17:37:49.012697 14186 sgd_solver.cpp:112] Iteration 7500, lr = 0.00657236
         I0321 17:37:49.700821 14186 solver.cpp:239] Iteration 7600 (145.325 iter/s, 0.688114s/100 iters), loss = 0.00700269
         I0321 17:37:49.700860 14186 solver.cpp:258]     Train net output #0: loss = 0.00700252 (* 1 = 0.00700252 loss)
         I0321 17:37:49.700870 14186 sgd_solver.cpp:112] Iteration 7600, lr = 0.00654433
         I0321 17:37:50.387862 14186 solver.cpp:239] Iteration 7700 (145.564 iter/s, 0.686981s/100 iters), loss = 0.0210292
         I0321 17:37:50.387902 14186 solver.cpp:258]     Train net output #0: loss = 0.021029 (* 1 = 0.021029 loss)
         I0321 17:37:50.387912 14186 sgd_solver.cpp:112] Iteration 7700, lr = 0.00651658
         I0321 17:37:51.077646 14186 solver.cpp:239] Iteration 7800 (144.986 iter/s, 0.689721s/100 iters), loss = 0.0016399
         I0321 17:37:51.077684 14186 solver.cpp:258]     Train net output #0: loss = 0.00163972 (* 1 = 0.00163972 loss)
         I0321 17:37:51.077692 14186 sgd_solver.cpp:112] Iteration 7800, lr = 0.00648911
         I0321 17:37:51.770789 14186 solver.cpp:239] Iteration 7900 (144.283 iter/s, 0.693081s/100 iters), loss = 0.00302445
         I0321 17:37:51.770843 14186 solver.cpp:258]     Train net output #0: loss = 0.00302427 (* 1 = 0.00302427 loss)
         I0321 17:37:51.770848 14186 sgd_solver.cpp:112] Iteration 7900, lr = 0.0064619
         I0321 17:37:52.447950 14186 solver.cpp:347] Iteration 8000, Testing net (#0)
         I0321 17:37:52.654633 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:52.662154 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9909
         I0321 17:37:52.662186 14186 solver.cpp:414]     Test net output #1: loss = 0.027501 (* 1 = 0.027501 loss)
         I0321 17:37:52.668864 14186 solver.cpp:239] Iteration 8000 (111.36 iter/s, 0.89799s/100 iters), loss = 0.00563864
         I0321 17:37:52.668929 14186 solver.cpp:258]     Train net output #0: loss = 0.00563846 (* 1 = 0.00563846 loss)
         I0321 17:37:52.668949 14186 sgd_solver.cpp:112] Iteration 8000, lr = 0.00643496
         I0321 17:37:53.357664 14186 solver.cpp:239] Iteration 8100 (145.311 iter/s, 0.688177s/100 iters), loss = 0.0242891
         I0321 17:37:53.357866 14186 solver.cpp:258]     Train net output #0: loss = 0.0242889 (* 1 = 0.0242889 loss)
         I0321 17:37:53.357879 14186 sgd_solver.cpp:112] Iteration 8100, lr = 0.00640827
         I0321 17:37:54.043135 14186 solver.cpp:239] Iteration 8200 (145.931 iter/s, 0.685255s/100 iters), loss = 0.0096888
         I0321 17:37:54.043171 14186 solver.cpp:258]     Train net output #0: loss = 0.00968862 (* 1 = 0.00968862 loss)
         I0321 17:37:54.043180 14186 sgd_solver.cpp:112] Iteration 8200, lr = 0.00638185
         I0321 17:37:54.728236 14186 solver.cpp:239] Iteration 8300 (145.977 iter/s, 0.685041s/100 iters), loss = 0.0331769
         I0321 17:37:54.728269 14186 solver.cpp:258]     Train net output #0: loss = 0.0331767 (* 1 = 0.0331767 loss)
         I0321 17:37:54.728276 14186 sgd_solver.cpp:112] Iteration 8300, lr = 0.00635567
         I0321 17:37:55.412156 14186 solver.cpp:239] Iteration 8400 (146.228 iter/s, 0.683862s/100 iters), loss = 0.00846423
         I0321 17:37:55.412191 14186 solver.cpp:258]     Train net output #0: loss = 0.00846406 (* 1 = 0.00846406 loss)
         I0321 17:37:55.412197 14186 sgd_solver.cpp:112] Iteration 8400, lr = 0.00632975
         I0321 17:37:55.643337 14193 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:56.093567 14186 solver.cpp:347] Iteration 8500, Testing net (#0)
         I0321 17:37:56.303144 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:56.310853 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9913
         I0321 17:37:56.310885 14186 solver.cpp:414]     Test net output #1: loss = 0.0277699 (* 1 = 0.0277699 loss)
         I0321 17:37:56.316977 14186 solver.cpp:239] Iteration 8500 (110.528 iter/s, 0.904752s/100 iters), loss = 0.00609586
         I0321 17:37:56.317023 14186 solver.cpp:258]     Train net output #0: loss = 0.0060957 (* 1 = 0.0060957 loss)
         I0321 17:37:56.317034 14186 sgd_solver.cpp:112] Iteration 8500, lr = 0.00630407
         I0321 17:37:57.006495 14186 solver.cpp:239] Iteration 8600 (145.042 iter/s, 0.689453s/100 iters), loss = 0.000714005
         I0321 17:37:57.006530 14186 solver.cpp:258]     Train net output #0: loss = 0.000713841 (* 1 = 0.000713841 loss)
         I0321 17:37:57.006536 14186 sgd_solver.cpp:112] Iteration 8600, lr = 0.00627864
         I0321 17:37:57.700429 14186 solver.cpp:239] Iteration 8700 (144.118 iter/s, 0.693876s/100 iters), loss = 0.00310442
         I0321 17:37:57.700489 14186 solver.cpp:258]     Train net output #0: loss = 0.00310426 (* 1 = 0.00310426 loss)
         I0321 17:37:57.700513 14186 sgd_solver.cpp:112] Iteration 8700, lr = 0.00625344
         I0321 17:37:58.388308 14186 solver.cpp:239] Iteration 8800 (145.391 iter/s, 0.687801s/100 iters), loss = 0.00164098
         I0321 17:37:58.388341 14186 solver.cpp:258]     Train net output #0: loss = 0.00164082 (* 1 = 0.00164082 loss)
         I0321 17:37:58.388360 14186 sgd_solver.cpp:112] Iteration 8800, lr = 0.00622847
         I0321 17:37:59.075045 14186 solver.cpp:239] Iteration 8900 (145.628 iter/s, 0.686681s/100 iters), loss = 0.000501583
         I0321 17:37:59.075081 14186 solver.cpp:258]     Train net output #0: loss = 0.000501429 (* 1 = 0.000501429 loss)
         I0321 17:37:59.075093 14186 sgd_solver.cpp:112] Iteration 8900, lr = 0.00620374
         I0321 17:37:59.751264 14186 solver.cpp:347] Iteration 9000, Testing net (#0)
         I0321 17:37:59.959125 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:37:59.966624 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9904
         I0321 17:37:59.966657 14186 solver.cpp:414]     Test net output #1: loss = 0.028375 (* 1 = 0.028375 loss)
         I0321 17:37:59.972826 14186 solver.cpp:239] Iteration 9000 (111.394 iter/s, 0.897715s/100 iters), loss = 0.0118657
         I0321 17:37:59.972857 14186 solver.cpp:258]     Train net output #0: loss = 0.0118655 (* 1 = 0.0118655 loss)
         I0321 17:37:59.972868 14186 sgd_solver.cpp:112] Iteration 9000, lr = 0.00617924
         I0321 17:38:00.662742 14186 solver.cpp:239] Iteration 9100 (144.957 iter/s, 0.689861s/100 iters), loss = 0.00553683
         I0321 17:38:00.662780 14186 solver.cpp:258]     Train net output #0: loss = 0.00553668 (* 1 = 0.00553668 loss)
         I0321 17:38:00.662787 14186 sgd_solver.cpp:112] Iteration 9100, lr = 0.00615496
         I0321 17:38:01.352582 14186 solver.cpp:239] Iteration 9200 (144.974 iter/s, 0.689781s/100 iters), loss = 0.00221661
         I0321 17:38:01.352661 14186 solver.cpp:258]     Train net output #0: loss = 0.00221647 (* 1 = 0.00221647 loss)
         I0321 17:38:01.352672 14186 sgd_solver.cpp:112] Iteration 9200, lr = 0.0061309
         I0321 17:38:02.042515 14186 solver.cpp:239] Iteration 9300 (144.963 iter/s, 0.689831s/100 iters), loss = 0.0056283
         I0321 17:38:02.042553 14186 solver.cpp:258]     Train net output #0: loss = 0.00562816 (* 1 = 0.00562816 loss)
         I0321 17:38:02.042560 14186 sgd_solver.cpp:112] Iteration 9300, lr = 0.00610706
         I0321 17:38:02.528177 14193 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:38:02.740190 14186 solver.cpp:239] Iteration 9400 (143.346 iter/s, 0.697614s/100 iters), loss = 0.0257568
         I0321 17:38:02.740226 14186 solver.cpp:258]     Train net output #0: loss = 0.0257567 (* 1 = 0.0257567 loss)
         I0321 17:38:02.740233 14186 sgd_solver.cpp:112] Iteration 9400, lr = 0.00608343
         I0321 17:38:03.417956 14186 solver.cpp:347] Iteration 9500, Testing net (#0)
         I0321 17:38:03.626682 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:38:03.633486 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9893
         I0321 17:38:03.633510 14186 solver.cpp:414]     Test net output #1: loss = 0.0324677 (* 1 = 0.0324677 loss)
         I0321 17:38:03.639657 14186 solver.cpp:239] Iteration 9500 (111.186 iter/s, 0.899397s/100 iters), loss = 0.00432486
         I0321 17:38:03.639703 14186 solver.cpp:258]     Train net output #0: loss = 0.00432473 (* 1 = 0.00432473 loss)
         I0321 17:38:03.639714 14186 sgd_solver.cpp:112] Iteration 9500, lr = 0.00606002
         I0321 17:38:04.328503 14186 solver.cpp:239] Iteration 9600 (145.253 iter/s, 0.688453s/100 iters), loss = 0.00447488
         I0321 17:38:04.328546 14186 solver.cpp:258]     Train net output #0: loss = 0.00447475 (* 1 = 0.00447475 loss)
         I0321 17:38:04.328553 14186 sgd_solver.cpp:112] Iteration 9600, lr = 0.00603682
         I0321 17:38:05.018791 14186 solver.cpp:239] Iteration 9700 (144.881 iter/s, 0.690221s/100 iters), loss = 0.00456662
         I0321 17:38:05.018831 14186 solver.cpp:258]     Train net output #0: loss = 0.0045665 (* 1 = 0.0045665 loss)
         I0321 17:38:05.018842 14186 sgd_solver.cpp:112] Iteration 9700, lr = 0.00601382
         I0321 17:38:05.706287 14186 solver.cpp:239] Iteration 9800 (145.468 iter/s, 0.687435s/100 iters), loss = 0.0136388
         I0321 17:38:05.706321 14186 solver.cpp:258]     Train net output #0: loss = 0.0136387 (* 1 = 0.0136387 loss)
         I0321 17:38:05.706328 14186 sgd_solver.cpp:112] Iteration 9800, lr = 0.00599102
         I0321 17:38:06.400578 14186 solver.cpp:239] Iteration 9900 (144.044 iter/s, 0.694231s/100 iters), loss = 0.00445842
         I0321 17:38:06.400617 14186 solver.cpp:258]     Train net output #0: loss = 0.00445829 (* 1 = 0.00445829 loss)
         I0321 17:38:06.400624 14186 sgd_solver.cpp:112] Iteration 9900, lr = 0.00596843
         I0321 17:38:07.069780 14186 solver.cpp:464] Snapshotting to binary proto file examples/mnist/lenet/lenet_solver_iter_10000.caffemodel
         I0321 17:38:07.083510 14186 sgd_solver.cpp:284] Snapshotting solver state to binary proto file examples/mnist/lenet/lenet_solver_iter_10000.solverstate
         I0321 17:38:07.089138 14186 solver.cpp:327] Iteration 10000, loss = 0.00239114
         I0321 17:38:07.089169 14186 solver.cpp:347] Iteration 10000, Testing net (#0)
         I0321 17:38:07.294113 14194 data_layer.cpp:73] Restarting data prefetching from start.
         I0321 17:38:07.301775 14186 solver.cpp:414]     Test net output #0: accuracy = 0.9908
         I0321 17:38:07.301798 14186 solver.cpp:414]     Test net output #1: loss = 0.0284383 (* 1 = 0.0284383 loss)
         I0321 17:38:07.301802 14186 solver.cpp:332] Optimization Done.
         I0321 17:38:07.301805 14186 caffe.cpp:250] Optimization Done.
         ```

         

         

   
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 29 20:36:19 2019

@author: gavin

Describe: 读入读出图片的操作
"""

import cv2
#import numpy as np

cv2.namedWindow("image", cv2.WINDOW_NORMAL)#创建一个动态窗口
img = cv2.imread("/home/gavin/NoteBook/pictures/lenet.png",0)# 读入图片
cv2.imshow("image", img)
cv2.imwrite("image_copy.png", img)

cv2.waitKey(0)
cv2.destroyAllWindows("image")
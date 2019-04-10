import cv2
import numpy as np
from PIL import Image
import os
# Path for face image database
path = '/home/pi/Desktop/FacialRecognitionProject/dataset'
recognizer = cv2.face.LBPHFaceRecognizer_create()                                                                                                               #初始化识别器
detector = cv2.CascadeClassifier("/home/pi/opencv-3.4.1/data/haarcascades/haarcascade_frontalface_default.xml");           #人脸检测器

def getImagesAndLabels(path):                                                             # 创建函数用于从数据集文件夹中获取训练图片，然后从图片的文件名中获取到这个素材相应的id
    imagePaths = [os.path.join(path,f) for f in os.listdir(path)]                  #获取训练图片

    faceSamples=[]                                                                             #存放人脸样本
    ids = []                                                                                            #存放id

    for imagePath in imagePaths:                                                          #遍历图片路径

        PIL_img = Image.open(imagePath).convert('L')                          # 转化为灰度图片
        img_numpy = np.array(PIL_img,'uint8')                                       #将图片转化成Numpy数组

        id = int(os.path.split(imagePath)[-1].split(".")[1])                    #获取id
        faces = detector.detectMultiScale(img_numpy)                        #获取人脸

        for (x,y,w,h) in faces:
            faceSamples.append(img_numpy[y:y+h,x:x+w])                    #图片放进上面的   faceSamples=[]   
            ids.append(id)                                                                            #id放进上面的      ids = []         

    return faceSamples,ids
print ("\n [INFO] Training faces. It will take a few seconds. Wait ...")
faces,ids = getImagesAndLabels(path)                                                  #调用上面的函数获取人脸和id
recognizer.train(faces, np.array(ids))                                                       #给识别器训练

recognizer.write('/home/pi/Desktop/FacialRecognitionProject/trainer/trainer.yml')     #保存训练后生成的yml文件

print("\n [INFO] {0} faces trained. Exiting Program".format(len(np.unique(ids))))

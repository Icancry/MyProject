import cv2
import numpy as np
from PIL import Image
import os
# Path for face image database
path = '/home/pi/Desktop/FacialRecognitionProject/dataset'
recognizer = cv2.face.LBPHFaceRecognizer_create()                                                                                                               #��ʼ��ʶ����
detector = cv2.CascadeClassifier("/home/pi/opencv-3.4.1/data/haarcascades/haarcascade_frontalface_default.xml");           #���������

def getImagesAndLabels(path):                                                             # �����������ڴ����ݼ��ļ����л�ȡѵ��ͼƬ��Ȼ���ͼƬ���ļ����л�ȡ������ز���Ӧ��id
    imagePaths = [os.path.join(path,f) for f in os.listdir(path)]                  #��ȡѵ��ͼƬ

    faceSamples=[]                                                                             #�����������
    ids = []                                                                                            #���id

    for imagePath in imagePaths:                                                          #����ͼƬ·��

        PIL_img = Image.open(imagePath).convert('L')                          # ת��Ϊ�Ҷ�ͼƬ
        img_numpy = np.array(PIL_img,'uint8')                                       #��ͼƬת����Numpy����

        id = int(os.path.split(imagePath)[-1].split(".")[1])                    #��ȡid
        faces = detector.detectMultiScale(img_numpy)                        #��ȡ����

        for (x,y,w,h) in faces:
            faceSamples.append(img_numpy[y:y+h,x:x+w])                    #ͼƬ�Ž������   faceSamples=[]   
            ids.append(id)                                                                            #id�Ž������      ids = []         

    return faceSamples,ids
print ("\n [INFO] Training faces. It will take a few seconds. Wait ...")
faces,ids = getImagesAndLabels(path)                                                  #��������ĺ�����ȡ������id
recognizer.train(faces, np.array(ids))                                                       #��ʶ����ѵ��

recognizer.write('/home/pi/Desktop/FacialRecognitionProject/trainer/trainer.yml')     #����ѵ�������ɵ�yml�ļ�

print("\n [INFO] {0} faces trained. Exiting Program".format(len(np.unique(ids))))

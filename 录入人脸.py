import cv2
import os
cam = cv2.VideoCapture(0)                            #��ȡ����ͷ
cam.set(3, 640)                                                #��������ͷ���ڿ��
cam.set(4, 480)                                                # ��������ͷ���ڸ߶�
face_detector = cv2.CascadeClassifier('/home/pi/opencv-3.4.1/data/haarcascades/haarcascade_frontalface_default.xml')#���ط�����
face_id = input('\n enter user id end press <return> ==> ')          #�����û�ID
print("\n [INFO] Initializing face capture. Look the camera and wait ...")
count = 0
while(True):                                                    #ѭ����������ͷ
    ret, img = cam.read()                                  #��ȡÿһ֡ͼ��

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)               #����Ƭ�Ҷȴ������Ч��
    faces = face_detector.detectMultiScale                                 #���÷��������������������
    (                               
        gray,                                                                                     #��ʾ����grayscaleͼ��
        scaleFactor=1.2,                                                                   #��ʾÿ��ͼ�������ı�����С
        minNeighbors=5,                                                                 # ��ʾÿ����ѡ���ο�߱����ڽ�����������Խ�󣬼�����Խ�١�
        minSize=(50,50)                                                                   #��ʾ����ʶ�����С���δ�С
        )
    for (x,y,w,h) in faces:                                                                 #�������ϱ��
        cv2.rectangle(img, (x,y), (x+w,y+h), (255,0,0), 2)               #����cv2����������
        count += 1          
        cv2.imwrite("/home/pi/Desktop/FacialRecognitionProject/dataset/User." + str(face_id) + '.' + str(count) + ".jpg", gray[y:y+h,x:x+w])#��������
        cv2.imshow('image', img)                                                       #��ʾ���þ��α�ǵ�ͼ��
    k = cv2.waitKey(100) & 0xff                                                  #���ڵȴ�                               
    if k == 27:                                                                              # �� 'ESC' �˳�����ͷ
        break
    elif count >= 200:                                                                  # ����200����Ƭ�Զ��˳�����
        break
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()                                                                          #�ͷ�����ͷ
cv2.destroyAllWindows()                                                      #�������д���
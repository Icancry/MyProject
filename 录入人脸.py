import cv2
import os
cam = cv2.VideoCapture(0)                            #获取摄像头
cam.set(3, 640)                                                #设置摄像头窗口宽度
cam.set(4, 480)                                                # 设置摄像头窗口高度
face_detector = cv2.CascadeClassifier('/home/pi/opencv-3.4.1/data/haarcascades/haarcascade_frontalface_default.xml')#加载分类器
face_id = input('\n enter user id end press <return> ==> ')          #输入用户ID
print("\n [INFO] Initializing face capture. Look the camera and wait ...")
count = 0
while(True):                                                    #循环调用摄像头
    ret, img = cam.read()                                  #获取每一帧图像

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)               #对照片灰度处理，提高效率
    faces = face_detector.detectMultiScale                                 #调用分类器函数向其输入参数
    (                               
        gray,                                                                                     #表示输入grayscale图像
        scaleFactor=1.2,                                                                   #表示每个图像缩减的比例大小
        minNeighbors=5,                                                                 # 表示每个备选矩形框具备的邻近数量。数字越大，假正类越少。
        minSize=(50,50)                                                                   #表示人脸识别的最小矩形大小
        )
    for (x,y,w,h) in faces:                                                                 #在人脸上标记
        cv2.rectangle(img, (x,y), (x+w,y+h), (255,0,0), 2)               #调用cv2函数画矩形
        count += 1          
        cv2.imwrite("/home/pi/Desktop/FacialRecognitionProject/dataset/User." + str(face_id) + '.' + str(count) + ".jpg", gray[y:y+h,x:x+w])#保存人脸
        cv2.imshow('image', img)                                                       #显示画好矩形标记的图像
    k = cv2.waitKey(100) & 0xff                                                  #窗口等待                               
    if k == 27:                                                                              # 按 'ESC' 退出摄像头
        break
    elif count >= 200:                                                                  # 或者200张照片自动退出窗口
        break
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()                                                                          #释放摄像头
cv2.destroyAllWindows()                                                      #销毁所有窗口
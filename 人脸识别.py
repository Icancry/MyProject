import cv2
import numpy as np
import os
import xlwt
import itchat
itchat.auto_login(hotReload=True)
import RPi.GPIO as GPIO
import time


recognizer = cv2.face.LBPHFaceRecognizer_create()                                                                         #初始化识别器
recognizer.read('/home/pi/Desktop/FacialRecognitionProject/trainer/trainer.yml')                         #读取训练完生成的yml文件
cascadePath = "/home/pi/opencv-3.4.1/data/haarcascades/haarcascade_frontalface_default.xml" 
faceCascade = cv2.CascadeClassifier(cascadePath);                                                                          #加载人脸检测器

font = cv2.FONT_HERSHEY_SIMPLEX

#iniciate id counter
id = 0

# names related to ids: example ==> Marcelo: id=1,  etc
names = ['None', '13-cpq', '36-lkd', '38-cxx'] 

# Initialize and start realtime video capture
cam = cv2.VideoCapture(0)
cam.set(3, 640) # set video widht
cam.set(4, 480) # set video height

# Define min window size to be recognized as a face
minW = 0.1*cam.get(3)
minH = 0.1*cam.get(4)

while True:

    ret, img =cam.read()
    #img = cv2.flip(img, -1) # Flip vertically

    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

    faces = faceCascade.detectMultiScale( 
        gray,
        scaleFactor = 1.2,
        minNeighbors = 5,
        minSize = (int(minW), int(minH)),
       )

    for(x,y,w,h) in faces:

        cv2.rectangle(img, (x,y), (x+w,y+h), (0,255,0), 2)

        id, confidence = recognizer.predict(gray[y:y+h,x:x+w])
        
        if (0 < confidence < 35):                                 #识别度大于65
            id = names[id]                                              #获取id
            T=time.strftime('%Y-%m-%d   %H:%M')           #获取当前时间
            confidence = "  {0}%".format(round(100 - confidence))
            trig=17
            def init():
                GPIO.setwarnings(False)
                GPIO.setmode(GPIO.BCM)
                GPIO.setup(trig,GPIO.OUT,initial=GPIO.HIGH)
                pass
            def beep(seconds):
                GPIO.output(trig,GPIO.LOW)
                time.sleep(seconds)
                GPIO.output(trig,GPIO.HIGH)
            def beepBatch(seconds,timespan,counts):
                for i in range(counts):
                    beep(seconds)
                    time.sleep(timespan)
            init()
            beepBatch(0.1,0.3,3)        
            GPIO.cleanup()
            with open('/home/pi/Desktop/1.txt', 'a') as f:     # 打开test.txt   如果文件不存在，创建该文件。                                 
                
                f.write(str("id=")+str(id)+"   "+str(T)+'\n')    #向文件1写入id和时间          
                outfile = open('/home/pi/Desktop/b.txt', 'w') #新的文件
                list_1=[]
                for line in open('/home/pi/Desktop/1.txt'):  #老文件
                    tmp = line.strip()                                        #去重复
                    if tmp not in list_1:
                        list_1.append(tmp)
                        outfile.write(line)
                outfile.close()         
            
        else:
            id = "unknown"                           
            confidence = "  {0}%".format(round(100 - confidence))
        
        cv2.putText(img, str(id), (x+5,y-5), font, 1, (255,255,255), 2)          #人脸框上显示id和名字
        cv2.putText(img, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)  
    
    cv2.imshow('camera',img)                                    #显示标记的图像
    k = cv2.waitKey(10) & 0xff                                 #等待退出
    if k == 27:
        break
    
def txt_xls(filename,xlsname):
    try:
        f = open(filename)
        xls = xlwt.Workbook()
        sheet = xls.add_sheet('sheet1',cell_overwrite_ok=True)
        x = 0
        
        while True:
            line = f.readline()
            if not line:
                break
            for i in range(len(line.split('\n'))):
                item=line.split('\n')[i]
                sheet.write(x,i,item) #x单元格经
            x += 1 #excel另起一行
        f.close()
        xls.save(xlsname) #保存xls文件
    except:
        raise
if __name__ == "__main__" :
    filename = "/home/pi/Desktop/b.txt"
    xlsname  = "/home/pi/Desktop/testb.xls"
    txt_xls(filename,xlsname)

users = itchat.search_friends(name='文件传输助手')
print(users)
itchat.send("@fil@%s" % '/home/pi/Desktop/testb.xls',toUserName = 'filehelper')

# Do a bit of cleanup
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()
cv2.destroyAllWindows()




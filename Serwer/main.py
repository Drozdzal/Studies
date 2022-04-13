import cv2
from flask import Flask, Response, render_template,request
from time import sleep
import requests
#IP ESP 192.168.0.171
class Camera:
    def __init__(self):
        self.is_stream_on = True
        self.camera = cv2.VideoCapture('http://192.168.0.234:8080/video')
    def check_stream(self):
        return self.is_stream_on

    def get_frame(self):
        while self.is_stream_on:
            ret,frame = self.camera.read()
            imgencode = cv2.imencode('.png', frame)[1]
            stringData = imgencode.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: text/plain\r\n\r\n' + stringData + b'\r\n')

    def release(self):
        self.is_stream_on = False
        print(self.is_stream_on)
        self.camera.release()

global obraz
obraz=Camera()
app = Flask(__name__)
rpi_url='http://192.168.0.82:5000'


@app.route('/home',methods = ['POST', 'GET'])
def home():
    if request.method=="POST":
        print("przyszedl_post")
        try:
            servo_1 = request.form['input_servo1_value']
        except:
            servo_1=0
        try:
            servo_2 = request.form['input_servo2_value']
        except:
            servo_2 = 0
        try:
            servo_3 = request.form['input_servo3_value']
        except:
            servo_3 = 0
        try:
            forward = request.form['forward']
        except:
            forward = 0
        try:
            turn = request.form['turn']
        except:
            turn = 0

        if float(servo_1) >0:
            print("servo1")
            requests.get("http://192.168.0.171/get?input_servo1_value=1")
        elif float(servo_2) >0:
            print("servo2")
            requests.get("http://192.168.0.171/get?input_servo2_value=1")
        elif float(servo_3) >0:
            print("servo3")
            requests.get("http://192.168.0.171/get?input_servo3_value=1")

        elif float(forward) > 0:
            requests.post(rpi_url + '/drive', params={'power': forward})
            print(forward)
        elif float(turn) != 0:
            requests.post(rpi_url + '/turn', params={'angle': turn})
            print(turn)
        #

    return render_template("Home.html",mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/video_buffor')
def video_buffor():
    if obraz.check_stream():
        return Response(obraz.get_frame(), mimetype='multipart/x-mixed-replace; boundary=frame')
    else:
        return Response('Stream_off')

@app.route('/camera_off')
def turn_off_camera():
    obraz.release()
    return Response('OK')

if __name__ == '__main__':
    app.run(host='localhost', port=5000, debug=False, threaded=True)



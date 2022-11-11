import PySimpleGUI as sg
import serial
import time

font = ("Helvetica", 16)
arduino = serial.Serial(port='/dev/cu.usbmodem142201', baudrate=115200, timeout=1)

sg.theme("DarkAmber")
sg.set_options(font=font)

# layout = [[sg.Text("Testing Serial Communication")],
#           [sg.Text("0", key="f0"), sg.Text("0", key="f1"), sg.Text("0", key="f2"), sg.Text("0", key="f3")],
#           [sg.Button("Cancel")]]

# Make Complex Layout
flex_sensor_column = [[sg.Text("Flex Sensors", font=("Helvetica", 24))],
                      [sg.HorizontalSeparator()],
                      [sg.Text("Sensor 0:"), sg.Text("0", key="f0")],
                      [sg.Text("Sensor 1:"), sg.Text("0", key="f1")],
                      [sg.Text("Sensor 2:"), sg.Text("0", key="f2")],
                      [sg.Text("Sensor 3:"), sg.Text("0", key="f3")]]

imu_column = [[sg.Text("IMU", font=("Helvetica", 24))],
              [sg.HorizontalSeparator()],
              [sg.Text("Temp:"), sg.Text("0", key="temp")],
              [sg.Text("AccX:"), sg.Text("0", key="accX"), 
               sg.Text("AccY:"), sg.Text("0", key="accY"), 
               sg.Text("AccZ:"), sg.Text("0", key="accZ")],
              [sg.Text("GyroX:"), sg.Text("0", key="gyroX"), 
               sg.Text("GyroY:"), sg.Text("0", key="gyroY"), 
               sg.Text("GyroZ:"), sg.Text("0", key="gyroZ")],
              [sg.Text("AccAngleX:"), sg.Text("0", key="accAngleX"), 
               sg.Text("AccAngleY:"), sg.Text("0", key="accAngleY")],
              [sg.Text("GyroAngleX:"), sg.Text("0", key="gyroAngleX"), 
               sg.Text("GyroAngleY:"), sg.Text("0", key="gyroAngleY"), 
               sg.Text("GyroAngleZ:"), sg.Text("0", key="gyroAngleZ")],
              [sg.Text("AngleX:"), sg.Text("0", key="angleX"), 
               sg.Text("AngleY:"), sg.Text("0", key="angleY"), 
               sg.Text("AngleZ:"), sg.Text("0", key="angleZ")]]

layout = [[sg.Column(flex_sensor_column), sg.VerticalSeparator(), sg.Column(imu_column)]]

window = sg.Window("HDGP Sensor Readings", layout)

def serial_read_write(input:int):
    arduino.write(bytes(input, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline().decode("utf-8").removesuffix()
    return data

def serial_read():
    return arduino.readline().decode("utf-8").strip()

def serial_readmany():
    #output = arduino.readline().decode("utf-8").strip()
    output = arduino.read_until("end").decode("utf-8").strip()
    return output.split(" ")
    #return [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

time.sleep(10)

while True:
    event, values = window.read(timeout=10)
    #current_time = int(round(time.time() * 100)) - start_time
    #window["time"].update('{:02d}:{:02d}.{:02d}'.format((current_time // 100) // 60,
    #                                                    (current_time // 100) % 60,
    #                                                    current_time % 100))
    #window["time"].update(f"{serial_read_write(values[0])}")
    #window["time"].update(f"{serial_read()}")
    if (arduino.in_waiting):
        reading = serial_readmany()
        #print(reading)
        window["f0"].update(reading[0])
        window["f1"].update(reading[1])
        window["f2"].update(reading[2])
        window["f3"].update(reading[3])
        window["temp"].update(reading[4])
        window["accX"].update(reading[5])
        window["accY"].update(reading[6])
        window["accZ"].update(reading[7])
        window["gyroX"].update(reading[8])
        window["gyroY"].update(reading[9])
        window["gyroZ"].update(reading[10])
        window["accAngleX"].update(reading[11])
        window["accAngleY"].update(reading[12])
        window["gyroAngleX"].update(reading[13])
        window["gyroAngleY"].update(reading[14])
        window["gyroAngleZ"].update(reading[15])
        window["angleX"].update(reading[16])
        window["angleY"].update(reading[17])
        window["angleZ"].update(reading[18])
    time.sleep(0.5)
    if event == sg.WIN_CLOSED or event == "Cancel":
        break
    #print("You entered ", values[0])
    
window.close()
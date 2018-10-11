from tkinter import *
import math
#import serial
from time import sleep

ser = serial.Serial()
ser.port = 'COM3'
ser.baudrate = 1200
ser.timeout = 0.1
ser.open()

#10 - 24_12_OFF
#11 - 24_12_ON
#20 - 12_5_OFF
#21 - 12_5_ON

ser.write(10)
ser.write(10)
ser.write(10)
ser.write(20)
ser.write(20)

def toggle_24_12():
    if(button_24_12["bg"] == "red"):
        button_24_12["bg"]="green"
        button_24_12["text"]="ON"
        button_24_12["activebackground"]="green"
        ser.write(11)
    else:
        button_24_12["bg"] = "red"
        button_24_12["text"]="OFF"
        button_24_12["activebackground"]="red"
        ser.write(10)

def toggle_12_5():
    if(button_12_5["bg"] == "red"):
        button_12_5["bg"]="green"
        button_12_5["text"]="ON"
        button_12_5["activebackground"]="green"
        ser.write(21)
    else:
        button_12_5["bg"] = "red"
        button_12_5["text"]="OFF"
        button_12_5["activebackground"]="red"
        ser.write(20)
    

#main
window = Tk()
window.title("Upravljački sustav")
window.configure(background="white")

photo1 = PhotoImage(file="fer_logo.gif")
Label(window, image=photo1, bg="white").grid(row=10, column=2, sticky=SE)

Label(window, text="TL2575", bg="white", fg="black", font="none 14 bold").grid(row=0, column=0, sticky=S)
Label(window, text="24V na 12V", bg="white", fg="black", font="none 9").grid(row=1, column=0, sticky=N)

Label(window, text="    ", bg="white", fg="black", font="none 12 bold").grid(row=0, column=1, sticky=S)

Label(window, text="LP2992", bg="white", fg="black", font="none 14 bold").grid(row=0, column=2, sticky=S)
Label(window, text="12V na 5V", bg="white", fg="black", font="none 9").grid(row=1, column=2, sticky=N)


Label(window, text="Svibanj 2018  Dino Šarić\n", bg="white", fg="black", font="none 8").grid(row=10, column=0, sticky=SW)
Label(window, text="\n\nUpravljanje pojedinim\nregulatorima napona", bg="white", fg="black", font="none 8 bold").grid(row=10, column=0, sticky=N)


button_24_12 = Button(window, width=3, text="OFF", font="none 12 bold", command=toggle_24_12, bg="red", fg="white", activebackground="red")
button_24_12.grid(row="2", column="0")

button_12_5 = Button(window, width=3, text="OFF", font="none 12 bold", command=toggle_12_5, bg="red", fg="white", activebackground="red")
button_12_5.grid(row="2", column="2")


window.mainloop()
ser.close()

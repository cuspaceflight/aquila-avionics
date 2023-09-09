# Daniel Fearn
# 07/09/2023
# 
# GUI for aquila ground station


import tkinter as tk
import serial # make sure to pip install pyserial, not serial!
import datetime

PORTNAME = 'COM5' # use arduino IDE or command line to find this
LOGLOCATION = 'log.csv' # note this is relative to where this script was called from

window = tk.Tk()
window.title("Aquila Ground Terminal")

counter = 1

#-------------------- ready for launch panel --------------------
frame_ready = tk.LabelFrame(master=window, relief=tk.GROOVE, borderwidth=5, padx=5, pady=5, text="Ready for ignition?")

lbl_ready = tk.Label(master=frame_ready, text="NOT READY", width=25, height=2, fg="red")
lbl_ready.pack()

frame_ready.pack()

#-------------------- main control panel --------------------
frame_controls = tk.LabelFrame(master=window, relief=tk.GROOVE, borderwidth=5, padx=5, pady=5, text="Commands")
control_btn_width = "25"
control_btn_height = "3"

# lock button
def send_lock():
    ser.write(b'L')
    print("lock")

btn_lock = tk.Button(
    master=frame_controls,
    text="LOCK",
    width=control_btn_width,
    height=control_btn_height,
    bg="gray",
    fg="white",
    command=send_lock
)
btn_lock.grid(row=0,column=0)

# unlock button
def send_unlock():
    ser.write(b'U')
    print("unlock")

btn_unlock = tk.Button(
    master=frame_controls,
    text="UNLOCK",
    width=control_btn_width,
    height=control_btn_height,
    bg="blue",
    fg="white",
    command=send_unlock
)
btn_unlock.grid(row=0,column=1)

# calibrate button
def send_cal():
    ser.write(b'C')
    print("calibrate")

btn_cal = tk.Button(
    master=frame_controls,
    text="Cal. Altimeter",
    width=control_btn_width,
    height=control_btn_height,
    bg="yellow",
    fg="black",
    command=send_cal
)
btn_cal.grid(row=0,column=2)


# arm pyro button
def send_arm():
    ser.write(b'A')
    print("arm pyro")

btn_arm = tk.Button(
    master=frame_controls,
    text="Arm Recovery",
    width=control_btn_width,
    height=control_btn_height,
    bg="red",
    fg="white",
    command=send_arm
)
btn_arm.grid(row=1,column=0)


# disarm pyro button
def send_disarm():
    ser.write(b'D')
    print("disarm")

btn_disarm = tk.Button(
    master=frame_controls,
    text="Disarm Recovery",
    width=control_btn_width,
    height=control_btn_height,
    bg="green",
    fg="white",
    command=send_disarm
)
btn_disarm.grid(row=1,column=1)

# disarm pyro button
def send_servo():
    ser.write(b'V')
    print("servo")

btn_servo = tk.Button(
    master=frame_controls,
    text="Move Servos",
    width=control_btn_width,
    height=control_btn_height,
    bg="purple",
    fg="white",
    command=send_servo
)
btn_servo.grid(row=1,column=2)

lbl_button_info = tk.Label(master=frame_controls, wraplength=500, text="Commands take a moment to send, and may need to be sent more than once. The flight computer will not execute the same command twice in a row.")
lbl_button_info.grid(row=2, column=0, columnspan=3)

#-------------------- state information panel --------------------
frame_info = tk.LabelFrame(master=window, relief=tk.GROOVE, borderwidth=5, padx=5, pady=5, text="Flight Data")

# important function: reads serial data from receiver, logs it, updates display
def update_info():
    global ser
    lbl_state.after(200, update_info)
    
    try:
        read = ser.readline().decode().strip()
    except Exception as e:
        print('lost connection to ground hardware')
        try:
            ser = serial.Serial(PORTNAME, timeout=0.01)
        except Exception as e:
            pass
        return

    if (read != ''):
        
        # log received data
        f = open(LOGLOCATION, 'a')
        f.write(str(datetime.datetime.now())+','+read+'\n')
        f.close()

        data = read.split(',')
        
        lbl_time['text'] = "Time (us): " + data[0]

        lbl_state["text"] = "Flight State: " + ["LOCKED", "PAD", "BURN", "COAST", "APOGEE", "DESCENT", "LAND"][int(data[1])]

        lbl_alt["text"] = "Inertial altitude (m): " + data[19]
        lbl_vel["text"] = "Inertial velocity (m/s): " + data[18]

        lbl_accel["text"] = "Accelerations (x,y,z) (g): " + ', '.join(data[2:5])

        lbl_gyro["text"] = "Gyroscope Rates (x,y,z) (deg/s): " + ', '.join(data[13:16])

        lbl_recovery["text"] = "Recovery armed: " + ["DISARMED", "ARMED"][int(data[8])]

        if int(data[8]) == 0:
            lbl_cont["text"] = "Pyro continuities: recovery must be armed"
        else:
            lbl_cont["text"] = "Pyro continuities: " + ', '.join(data[9:13])
    
        # update disabled buttons
        rec_armed = int(data[8])
        locked_state = (int(data[1]) == 0)
        if rec_armed:
            btn_arm["state"] = "disabled"
            btn_disarm["state"] = "normal"
            btn_servo["state"] = "normal"
        else:
            btn_arm["state"] = "normal"
            btn_disarm["state"] = "disabled"
            btn_servo["state"] = "disabled"
        
        if locked_state:
            btn_lock["state"] = "disabled"
            btn_unlock["state"] = "normal"
            btn_cal["state"] = "normal"
        else:
            btn_lock["state"] = "normal"
            btn_unlock["state"] = "disabled"
            btn_cal["state"] = "disabled"

        # update readiness indicator
        if int(data[1]) == 1 and rec_armed == False:
            lbl_ready["text"] = "READY"
            lbl_ready["fg"] = "GREEN"
        else:
            lbl_ready["text"] = "NOT READY"
            lbl_ready["fg"] = "RED"


        

# all the labels for flight data
lbl_time = tk.Label(master=frame_info, text="no data", anchor='w')
lbl_time.pack(fill=tk.X, expand=True, pady=5)

lbl_state = tk.Label(master=frame_info, text="no data", anchor='w')
lbl_state.pack(fill=tk.X, expand=True, pady=5)

lbl_alt = tk.Label(master=frame_info, text="no data", anchor='w')
lbl_alt.pack(fill=tk.X, expand=True, pady=5)

lbl_vel = tk.Label(master=frame_info, text="no data", anchor='w')
lbl_vel.pack(fill=tk.X, expand=True, pady=5)

lbl_accel = tk.Label(master=frame_info, text="no data", anchor='w')
lbl_accel.pack(fill=tk.X, expand=True, pady=5)

lbl_gyro = tk.Label(master=frame_info, text="no data", anchor='w')
lbl_gyro.pack(fill=tk.X, expand=True, pady=5)

lbl_recovery = tk.Label(master=frame_info, text="no data", anchor='w')
lbl_recovery.pack(fill=tk.X, expand=True, pady=5)

lbl_cont = tk.Label(master=frame_info, text="no data", anchor='w')
lbl_cont.pack(fill=tk.X, expand=True)



frame_controls.pack()
frame_info.pack(fill=tk.X, expand=True)




#-------------------- startup --------------------
try:
    ser = serial.Serial(PORTNAME, timeout=0.01)
except Exception as e:
    print("couldn't open port")
    exit()

update_info()
window.mainloop()

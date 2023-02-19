# Daniel Fearn
# 12/02/2023

# This code takes a csv file of time, altitude, velocity and acceleration values and generates c++ functions for them
import csv

def generate_for_selection(selection):
    with open('flight_data.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0

        prev_time = 0
        prev_val = 0

        dt = 0

        for row in csv_reader:

            time = float(row[0]) * 1000
            val = row[selection]

            if line_count == 1: dt = time

            if line_count == 0:
                pass
            else:
                prefix = ["else ", ""][(line_count == 1)]
                print(prefix + "if (time < " + str(time) + ") { return "+str(prev_val)+" + ("+str(val)+" - "+str(prev_val)+")*(time - " + str(prev_time) + ")/("+str(dt)+"); }" )
            
            prev_time = time
            prev_val = row[selection]

            line_count += 1

print("\n\n\n\nHeight curve: ")
generate_for_selection(1)
print("\n\n\n\nVelocity curve: ")
generate_for_selection(2)
print("\n\n\n\nAcceleration curve: ")
generate_for_selection(3)
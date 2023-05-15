import os
import csv
import re

data_dir = "C:/Users/leoni/Documents/University/Semester2/BSP2/Statistics/target_all2"
parsed_data_name = "parsed_data.csv"
labels = ["Engine", "Scenario", "Time", "Energy"]
numericSearch = "\d+\.\d+"

def getNumFromLine(line):
    line = line.replace(",", "")
    num = re.search(numericSearch, line)[0]

    if num is None:
        return 0
    return float(num)

def main():
    with open(parsed_data_name, "w") as d:
        writer = csv.writer(d)
        writer.writerow(labels)

        for target_dir in os.listdir(data_dir):
            engine, scenario = target_dir.split("_")
            for file in os.listdir(data_dir + "/" + target_dir):
                with open(data_dir + "/" + target_dir + "/" + file, "r") as f:
                    lines = f.readlines()
                    time = getNumFromLine(lines[8])
                    energy = getNumFromLine(lines[5]) + getNumFromLine(lines[6])

                    writer.writerow([engine, scenario, time, energy])

if __name__ == '__main__':
    main()
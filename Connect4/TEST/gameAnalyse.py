#mean time
def meanTime():
    times = []
    for i in range(3,7):
        filename = "test_" + str(i) + ".txt"
        times.append(extractTimeData(filename))
        filename = "test_" + str(i) + "_Ordered.txt"
        time.append(extractTimeData(filename))
    return times
                

def extractTimeData(filename):
    with open(filename,'r') as testFile:
            buffer = testFile.read().split('\n')
            buffer = [buffer[i] for i in range(0,len(buffer),3)]
            timeLine = buffer[0].split(';')
            print(timeLine)
            timeLine = [int(t) for t in timeLine if t.isdigit()]
            for i in range(1,len(buffer)):
                temp = buffer[i].split(';')
                timeLine = [timeLine[j] + temp[j] for j in range(len(timeLine))]
            timeLine = [t/len(buffer) for t in timeLine]
            return timeLine
    return None



print(meanTime())

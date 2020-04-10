import matplotlib.pyplot as plt
#mean time
def meanTime():
    times = []
    for i in range(3,7):
        filename = "test_" + str(i) + ".txt"
        times.append(extractTimeData(filename))
        filename = "test_" + str(i) + "_Ordered.txt"
        times.append(extractTimeData(filename))
    return times
                

def extractTimeData(filename):
    with open(filename,'r') as testFile:
            buffer = testFile.read().split('\n')
            buffer = [buffer[i] for i in range(0,len(buffer),3)]
            timeLine = buffer[0].split(';')
            timeLine = [int(t) for t in timeLine if t.isdigit()]
            for i in range(1,len(buffer)-1):
                temp = buffer[i].split(';')
                timeLine = [timeLine[j] + int(temp[j]) for j in range(len(timeLine)) if temp[j]!='']
            timeLine = [t/len(buffer)-1 for t in timeLine]
            return timeLine
    return None

def graphMean():
    times = meanTime()
    plt.figure()
    f = 1
    for i in range(0,len(times),2):
        plt.subplot(410+f)
        plt.tight_layout()
        plt.plot(times[i])
        plt.plot(times[i+1])
        plt.ylabel('Times (ms)')
        plt.xlabel('Move number')
        plt.title('Best move search, depth = ' + str(3+f))
        f+=1
    plt.show()

graphMean()


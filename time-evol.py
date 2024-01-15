import matplotlib.pyplot as plt
import numpy as np

def read_data(filename):
    x = []
    y = []
    fileObj = open(filename, 'rt')
    while True:
        line = fileObj.readline()
        if not line: break
        r = line.split(',')
        x.append(float(r[0]))
        y.append(float(r[1]))
    return (x, y)

def plotData(filename1, filename2=None, filename3=None):
    x1, y1 = read_data(filename1)
    #x2, y2 = read_data(filename2)
    #x3, y3 = read_data(filename3)

    fig = plt.figure(figsize=(5,4))
    ax = fig.add_subplot()

    #ax.set_title('PGG Time Evolution')
    ax.set_xlabel(r'$time$')
    ax.set_ylabel(r'$\rho_{C}$')
    ax.grid(True)

    ax.plot(x1[::100], y1[::100], 'g-.', label=r"$r=3.8$", linewidth=3)
    #ax.plot(x2[::500], y2[::500], 'r-.', label=r'$r=5$', linewidth=3)
    #ax.plot(x3[::100], y3[::100], 'b-.', label=r'$r=7$', linewidth=3)
    ax.legend()
    #fig2.savefig('phasetransition')
    plt.ylim([-0.01,1.01])
    #plt.xlim([0,10])
    #plt.xticks(np.arange(0,10,0.5))
    plt.show()

if __name__ == '__main__':
    
    plotData('time-evol-r3.800000.txt')
    

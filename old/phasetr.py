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

def plotData(filename1,filename2, filename3, filename4, filename5, filename6, filename7):
    x1, y1 = read_data(filename1)
    #x2, y2 = read_data(filename2)
    #x3, y3 = read_data(filename3)
    #x4, y4 = read_data(filename4)
    #x5, y5 = read_data(filename5)
    #x6, y6 = read_data(filename6)
    #x7, y7 = read_data(filename7)

    fig = plt.figure(figsize=(6,4))
    ax = fig.add_subplot()

    #ax.set_title('PGG Time Evolution')
    ax.set_xlabel(r'$r$')
    ax.set_ylabel(r'$\rho_{C}$')
    ax.grid(True)

    ax.plot(x1, y1, color='k', linestyle='-', marker='s', label=r"$\alpha=0$", linewidth=1,)

    #ax.plot(x2, y2, color='r', linestyle='-', marker='s', label=r"$\alpha=0.2$", linewidth=1,)

    #ax.plot(x3, y3, color='b', linestyle='-', marker='s', label=r"$\alpha=0.4$", linewidth=1,)

    #ax.plot(x4, y4, color='m', linestyle='-', marker='s', label=r"$\alpha=0.6$", linewidth=1,)

    #ax.plot(x5, y5, color='y', linestyle='-', marker='^', label=r"$\alpha=0.8$", linewidth=1,)

    #ax.plot(x6, y6, color='g', linestyle='-', marker='<', label=r"$\alpha=1$", linewidth=1,)

    #ax.plot(x7, y7, color='purple', linestyle='-', marker='>', label=r"$\alpha=2$", linewidth=1,)

    #ax.legend()
    #fig2.savefig('phasetransition')
    plt.ylim([-0.01,1.01])
    plt.xlim([2,5.5])
    #ax.set_xticks(np.linspace(1, 10, 10, endpoint=True))
    plt.legend()
    plt.show()

if __name__ == '__main__':
    
    #plotData('hetro-sq-a0.txt')
    plotData('hetro-sq-a0.txt','hetro-sq-a0.2.txt', 'hetro-sq-a0.4.txt', 'hetro-sq-a0.6.txt','hetro-sq-a0.8.txt','hetro-sq-a1.txt', 'hetro-sq-a2.txt')
    

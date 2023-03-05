#This code is used to draw two plots and their ratio

import matplotlib.pyplot as plt
import numpy as np




X = np.array([0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20])
Y = np.array([0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20])
Y1 = np.array([0,1.1,2.1,3.1,4.1,5.1,6.1,7.1,8.1,9.1,10.1,11.1,12.1,13.1,14.1,15.1,16.1,17.1,18.1,19.1,20.1])

Yratio= Y1/Y

fig, axs = plt.subplots(2, 1, sharex=True,figsize=(9, 7),gridspec_kw={'height_ratios':[2,1]})
# Remove horizontal space between axes
fig.subplots_adjust(hspace=0.03)

# Plot each graph, and manually set the y tick values
axs[0].plot(X,Y, 'ko',  label='Y',markersize=3)
axs[0].plot(X,Y1,'-' ,color='red', label='$Y_1$')


axs[0].grid(True)
axs[0].legend(loc=2, prop={'size': 11},ncol=2)
axs[0].set_ylabel('Y, $Y_{1}$',size=20)



axs[1].axhline(y=2, color='k', linestyle='-')
axs[1].plot(X,Yratio,'--',color='red')
axs[1].legend(loc=2, prop={'size': 0},ncol=2)
axs[1].set_ylim([0.5,1.5])

axs[1].grid(True)
axs[1].set_xlabel('X',size=20)
axs[1].set_ylabel('Y1/Y',size=15)



axs[0].set_title("put the title here")
plt.savefig('NameOfTheOutPut.pdf')  
plt.show()

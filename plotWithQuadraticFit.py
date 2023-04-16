import matplotlib.pyplot as plt
import numpy as np

X = np.array([-0.01, -0.02, -0.03, -0.04, -0.05, -0.06, -0.07, -0.08, -0.09, -0.1, 0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1])
Y = np.array([1.0372, 1.0113, 0.9869, 0.964, 0.9425, 0.9225, 0.9038, 0.8865, 0.8706, 0.856, 1.0647, 1.0938, 1.1245, 1.1568, 1.1909, 1.2266, 1.2642, 1.3035, 1.3448, 1.3879, 1.4329])

# Perform quadratic fit
coefficients = np.polyfit(X, Y, 2)
quadratic_fit = np.poly1d(coefficients)

# Generate points for the quadratic fit
X_fit = np.linspace(X.min(), X.max(), 100)
Y_fit = quadratic_fit(X_fit)

# Plot original data
plt.plot(X, Y, 'ko', label='Y', markersize=3)

# Plot quadratic fit
plt.plot(X_fit, Y_fit, 'r-', label='Quadratic Fit')

plt.grid(True)
plt.legend(loc=2, prop={'size': 11}, ncol=2)

plt.title("cross section vs a_tau with Quadratic Fit")
plt.xlabel('a_tau')
plt.ylabel('cross section (mb)')

plt.savefig('NameOfTheOutPut.pdf')
plt.show()

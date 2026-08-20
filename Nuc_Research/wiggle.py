

import matplotlib.pyplot as plt
import numpy as np




#45/135 para uncert
y_para_uncert = [102.223, 102.467, 102.343, 103.357, 103.739, 102.037, 100.302, 99.1762, 100.339, 102.541, 103.526, 101.84]

y_perp_uncert = [105.566, 106.585, 105.926, 104.509, 102.419, 102.103, 103.232, 105.029, 102.843, 101.413, 101.351, 101.22]



#0/90 perp uncert
#y_perp_uncert = [177.821, 181.896, 183.655, 181.88, 177.39, 174.289, 174.569, 175.513, 179.001, 180.465, 177.138, 176.255]

#0/90 para uncert
#y_para_uncert = [184.276, 183.625, 181.978, 177.858, 178.887, 180.375, 180.365, 177.843, 175.573, 176.071, 178.839, 182.296]



# 0/90 configs
#y_para = [23031.6, 22702.1, 22215.6, 21015.9, 21402.8, 21948.5, 21994.1, 21177.9, 20518.4, 20721.7, 21556.7, 22442.7]

#y_perp = [21401.8, 22657.8, 22999.8, 22603.6, 21358.9, 20518.1, 20632.2, 21006.3, 21944.5, 22335.2, 21217.7, 21029.6]


phi_angle = [-165, -135, -105, -75, -45, -15, 15, 45, 75, 105, 135, 165]


# 45/135 configs
y_para = [7087.06, 7008.11, 7026.56, 7238.16, 7329.48, 6961.08, 6657.07, 6545.32, 6784.19, 7171.29, 7292.81, 6962.29]

y_perp = [7546.06, 7741.16, 7621.45, 7378.76, 7052.42, 6977.93, 7218.42, 7501.16, 7152.6, 6970.74, 6913.6, 6863.33]

num_para = 0
for i in range(0, len(y_para)):
	num_para = num_para + float(y_para[i])

num_perp = 0
for i in range(0, len(y_perp)):
	num_perp = num_perp + float(y_perp[i])

print(num_para, num_perp)

asymmetry = []
y_uncer = []
for i in range(0, len(y_para)):
	asymmetry.append(((y_para[i]/float(num_para)) - (y_perp[i]/float(num_perp))) / ((y_para[i]/float(num_para)) + (y_perp[i]/float(num_perp))))
	y_uncer.append((((2*float(y_para[i])/((float(y_para[i])+float(y_perp[i]))**2))*float(y_perp_uncert[i]))**2 + ((2*float(y_perp[i])/((float(y_para[i])+float(y_perp[i]))**2))*float(y_para_uncert[i]))**2)**.5)



plt.errorbar(phi_angle, asymmetry,yerr=y_uncer, fmt="o", color="dodgerblue", label= r"45/135 Asymmetry : $\frac{N_{para}-N_{perp}}{N_{para}+N_{perp}}$")
plt.ylim(-0.1, 0.1)
plt.xlabel(r'$\phi$ [degrees]')
#plt.title(r'$\omega$ yields for 0 < |t| < 1')
plt.legend()
plt.show()

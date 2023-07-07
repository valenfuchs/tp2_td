import pandas as pd
import os
import matplotlib.pyplot as plt

#heuristicas = ["depMasCercano.csv", "menorRatio.csv", "venMasCercano.csv", "relocateDep.csv","relocateRatio.csv", "relocateVen.csv", "swapDep.csv", "swapRatio.csv", "swapVen.csv", "grasp100.csv", "grasp300.csv", "grasp500.csv"]
#busqueda_local = ["depMasCercano.csv", "menorRatio.csv", "venMasCercano.csv", "relocateDep.csv","relocateRatio.csv", "relocateVen.csv", "swapDep.csv", "swapRatio.csv", "swapVen.csv", "grasp100.csv", "grasp300.csv", "grasp500.csv"]
#metaheuristica = ["depMasCercano.csv", "menorRatio.csv", "venMasCercano.csv", "relocateDep.csv","relocateRatio.csv", "relocateVen.csv", "swapDep.csv", "swapRatio.csv", "swapVen.csv", "grasp100.csv", "grasp300.csv", "grasp500.csv"]


dep_mas_cercano = pd.read_csv("depMasCercano.csv")
dist1 = dep_mas_cercano['distancia_total'].tolist()
tiempo1 = dep_mas_cercano['tiempo'].tolist()
dep_mas_cercano = pd.read_csv("depMasCercano.csv")
dist2 = dep_mas_cercano['distancia_total'].tolist()
tiempo3 = dep_mas_cercano['tiempo'].tolist()
dep_mas_cercano = pd.read_csv("depMasCercano.csv")
dist1 = dep_mas_cercano['distancia_total'].tolist()
tiempo1 = dep_mas_cercano['tiempo'].tolist()


plt.plot(list(range(0,40)), dist1, color='green', label = 'Distance Greedy')
plt.plot(list(range(0,40)), dist2, color='purple', label = 'Distance Batching')
plt.plot(list(range(0,40)), dist3, color='purple', label = 'Distance Batching')
plt.xlabel('Instancia')
plt.ylabel('Distancia')
plt.legend()
plt.show()


        
        
        



import pandas as pd
import os
import matplotlib.pyplot as plt
'''
dep_mas_cercano = pd.read_csv("depMasCercano.csv")
dist1 = dep_mas_cercano['distancia_total'].tolist()
tiempo1 = dep_mas_cercano[' tiempo'].tolist()

menor_ratio = pd.read_csv("menorRatio.csv")
dist2 = menor_ratio['distancia_total'].tolist()
tiempo2 = menor_ratio[' tiempo'].tolist()

ven_mas_cercano = pd.read_csv("venMasCercano.csv")
dist3 = ven_mas_cercano['distancia_total'].tolist()
tiempo3 = ven_mas_cercano[' tiempo'].tolist()


plt.plot(list(range(0,27)), dist1, color='green', label = 'Deposito mas cercano')
plt.plot(list(range(0,27)), dist2, color='purple', label = 'Menor ratio')
plt.plot(list(range(0,27)), dist3, color='orange', label = 'Vendedor mas cercano')
plt.title("Distancias para Heuristicas Constructivas")
plt.xlabel('Instancia')
plt.ylabel('Distancia')
plt.legend()
plt.show()

plt.plot(list(range(0,27)), tiempo1, color='green', label = 'Deposito mas cercano')
plt.plot(list(range(0,27)), tiempo2, color='purple', label = 'Menor ratio')
plt.plot(list(range(0,27)), tiempo3, color='orange', label = 'Vendedor mas cercano')
plt.title("Tiempo para Heuristicas Constructivas")
plt.xlabel('Instancia')
plt.ylabel('Tiempo')
plt.legend()
plt.show()

#######################


dep_relocate = pd.read_csv("relocateDep.csv")
dist4 = dep_relocate['distancia_total'].tolist()
tiempo4 = dep_relocate[' tiempo'].tolist()

dep_swap = pd.read_csv("swapDep.csv")
dist5 = dep_swap['distancia_total'].tolist()
tiempo5 = dep_swap[' tiempo'].tolist()


plt.plot(list(range(0,27)), dist4, color='hotpink', label = 'Relocate')
plt.plot(list(range(0,27)), dist5, color='mediumblue', label = 'Swap')
plt.title("Distancias para Busqueda Local aplicando Deposito más cercano")
plt.xlabel('Instancia')
plt.ylabel('Distancia')
plt.legend()
plt.show()

plt.plot(list(range(0,27)), tiempo4, color='hotpink', label = 'Relocate')
plt.plot(list(range(0,27)), tiempo5, color='mediumblue', label = 'Swap')
plt.title("Tiempo para Busqueda Local aplicando Deposito más cercano")
plt.xlabel('Instancia')
plt.ylabel('Tiempo')
plt.legend()
plt.show()


###################################3
        
        
ratio_relocate = pd.read_csv("relocateRatio.csv")
dist6 = dep_relocate['distancia_total'].tolist()
tiempo6 = dep_relocate[' tiempo'].tolist()

ratio_swap = pd.read_csv("swapRatio.csv")
dist7 = ratio_swap['distancia_total'].tolist()
tiempo7 = ratio_swap[' tiempo'].tolist()


plt.plot(list(range(0,27)), dist6, color='hotpink', label = 'Relocate')
plt.plot(list(range(0,27)), dist7, color='mediumblue', label = 'Swap')
plt.title("Distancias para Busqueda Local aplicando Menor Ratio")
plt.xlabel('Instancia')
plt.ylabel('Distancia')
plt.legend()
plt.show()

plt.plot(list(range(0,27)), tiempo6, color='hotpink', label = 'Relocate')
plt.plot(list(range(0,27)), tiempo7, color='mediumblue', label = 'Swap')
plt.title("Tiempo para Busqueda Local aplicando Menor Ratio")
plt.xlabel('Instancia')
plt.ylabel('Tiempo')
plt.legend()
plt.show()


###################################3
        
        
ven_relocate = pd.read_csv("relocateVen.csv")
dist8 = ven_relocate['distancia_total'].tolist()
tiempo8 = ven_relocate[' tiempo'].tolist()

ven_swap = pd.read_csv("swapVen.csv")
dist9 = ven_swap['distancia_total'].tolist()
tiempo9 = ven_swap[' tiempo'].tolist()


plt.plot(list(range(0,27)), dist8, color='hotpink', label = 'Relocate')
plt.plot(list(range(0,27)), dist9, color='mediumblue', label = 'Swap')
plt.title("Distancias para Busqueda Local aplicando Vendedor más Cercano")
plt.xlabel('Instancia')
plt.ylabel('Distancia')
plt.legend()
plt.show()

plt.plot(list(range(0,27)), tiempo8, color='hotpink', label = 'Relocate')
plt.plot(list(range(0,27)), tiempo9, color='mediumblue', label = 'Swap')
plt.title("Tiempo para Busqueda Local aplicando Vendedor más Cercano")
plt.xlabel('Instancia')
plt.ylabel('Tiempo')
plt.legend()
plt.show()


###################################
        

        
grasp100 = pd.read_csv("grasp100.csv")
dist10 = grasp100['distancia_total'].tolist()
tiempo10 = grasp100[' tiempo'].tolist()

grasp300 = pd.read_csv("grasp300.csv")
dist11 = grasp300['distancia_total'].tolist()
tiempo11 = grasp300[' tiempo'].tolist()

grasp500 = pd.read_csv("grasp500.csv")
dist12 = grasp500['distancia_total'].tolist()
tiempo12 = grasp500[' tiempo'].tolist()



plt.plot(list(range(0,27)), dist10, color='coral', label = '100 iteraciones')
plt.plot(list(range(0,27)), dist11, color='yellow', label = '300 iteraciones')
plt.plot(list(range(0,27)), dist12, color='lightskyblue', label = '500 iteraciones')
plt.title("Distancias para GRASP")
plt.xlabel('Instancia')
plt.ylabel('Distancia')
plt.legend()
plt.show()

plt.plot(list(range(0,27)), tiempo10, color='coral', label = '100 iteraciones')
plt.plot(list(range(0,27)), tiempo11, color='yellow', label = '300 iteraciones')
plt.plot(list(range(0,27)), tiempo12, color='lightskyblue', label = '500 iteraciones')
plt.title("Tiempos para GRASP")
plt.xlabel('Instancia')
plt.ylabel('Tiempo')
plt.legend()
plt.show()

'''
#######################################################
reales = pd.read_csv("instancia_real.csv")
codigos = ["DmC", "MR", "VmC", "relD", "relMR", "relV", "SD", "SR", "SV", "g100", "g300", "g500"]
codigos1 = ["DmC", "MR", "VmC", "relD", "relMR", "relV", "SD", "SR", "SV"]
codigos2 = ["g100", "g300", "g500"]
dist = reales[' distancia_total'].tolist()
tiempo = reales[' tiempo'].tolist()
tiempo1 = tiempo[:9]
tiempo2 = tiempo[9:]

# Crear una lista de índices para las barras
#indices = reales['código'].tolist()
    
plt.bar(codigos, dist, color = 'teal')
plt.xlabel('Código utilizado')
plt.ylabel('Distancia Total')
plt.title('Distancias Totales para la Instancia Real')
plt.show()

plt.bar(codigos, tiempo, color = 'teal')
plt.xlabel('Código utilizado')
plt.yscale('log')
plt.ylabel('Tiempo')
plt.title('Tiempo para la Instancia Real')
plt.show()
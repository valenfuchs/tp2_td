import pandas as pd
import os


depositos = []
vendedores = []

for filename in os.listdir("instancias"):
    file_path = os.path.join("instancias", filename)
    if os.path.isfile(file_path):
        with open(file_path, "r") as file:
            line = file.readline().strip()
            values = line.split()
            if len(values) >= 2:
                depositos.append(int(values[0]))
                vendedores.append(int(values[1]))

archivos = ["depMasCercano.csv", "menorRatio.csv", "venMasCercano.csv", "relocateDep.csv","relocateRatio.csv", "relocateVen.csv", "swapDep.csv", "swapRatio.csv", "swapVen.csv", "grasp100.csv", "grasp300.csv", "grasp500.csv"]

# Iteramos sobre los nombres de archivo
for filename in archivos:
    # Verificamos si el archivo existe en la carpeta actual
    if os.path.exists(filename):
        df = pd.read_csv(filename)

        # Agrega las nuevas columnas al DataFrame al principio
        df.insert(0, "vendedores", vendedores)
        df.insert(0, "depositos", depositos)

        df.to_csv(filename, index=False)
    else:
        print(f"El archivo {filename} no existe en la carpeta actual.")




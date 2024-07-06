import random

def gerar_e_identificar_pares():
    for _ in range(10):
        numero_aleatorio = random.randint(1, 100)  
        print(f"Número Aleatório: {numero_aleatorio}")

        if numero_aleatorio % 2 == 0:
            print("Este número é par.\n")
        else:
            print("Este número é impar.\n")

gerar_e_identificar_pares()

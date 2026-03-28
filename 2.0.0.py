TORRES DUARTE, MICHELLE DANIELA
27/03/2026
solo se le hizo una mejora al ejecutar y dio como codigo final
# Programa para leer numeros y sacar suma, promedio, mayor y menor

# Funcion para leer numeros con validacion
def leer_numeros(n):
    numeros = []
    for i in range(n):
        while True:
            try:
                num = int(input(f"Ingresa el numero {i + 1}: "))
                numeros.append(num)
                break
            except ValueError:
                print("Entrada invalida. Intenta de nuevo.")
    return numeros

# Funcion suma
def suma(arr):
    s = 0
    for num in arr:
        s += num
    return s

# Funcion promedio
def promedio(arr):
    if len(arr) == 0:
        return 0
    return suma(arr) / len(arr)

# Funcion mayor
def mayor(arr):
    if len(arr) == 0:
        return 0
    maximo = arr[0]
    for num in arr:
        if num > maximo:
            maximo = num
    return maximo

# Funcion menor
def menor(arr):
    if len(arr) == 0:
        return 0
    minimo = arr[0]
    for num in arr:
        if num < minimo:
            minimo = num
    return minimo

# Mejora 1: contar positivos, negativos y ceros
def contar_tipos(arr):
    positivos = 0
    negativos = 0
    ceros = 0

    for num in arr:
        if num > 0:
            positivos += 1
        elif num < 0:
            negativos += 1
        else:
            ceros += 1

    return positivos, negativos, ceros

# Mejora 2: ordenar los numeros
def ordenar_numeros(arr):
    return sorted(arr)

# Mejora 3: verificar si hay numeros repetidos
def hay_repetidos(arr):
    if len(arr) != len(set(arr)):
        return "Si hay numeros repetidos"
    else:
        return "No hay numeros repetidos"

# Mejora 4: contar pares e impares
def contar_par_impar(arr):
    pares = 0
    impares = 0

    for num in arr:
        if num % 2 == 0:
            pares += 1
        else:
            impares += 1

    return pares, impares

# Programa principal
while True:
    try:
        n = int(input("Cantidad de numeros: "))
        if n > 0:
            break
        else:
            print("Error. Ingresa un numero mayor que 0.")
    except ValueError:
        print("Entrada invalida. Intenta de nuevo.")

numeros = leer_numeros(n)

positivos, negativos, ceros = contar_tipos(numeros)
pares, impares = contar_par_impar(numeros)

print("\n--- RESULTADOS ---")
print("Numeros ingresados:", numeros)
print("Numeros ordenados:", ordenar_numeros(numeros))
print("Suma:", suma(numeros))
print("Promedio: {:.2f}".format(promedio(numeros)))
print("Mayor:", mayor(numeros))
print("Menor:", menor(numeros))
print("Positivos:", positivos)
print("Negativos:", negativos)
print("Ceros:", ceros)
print("Pares:", pares)
print("Impares:", impares)
print(hay_repetidos(numeros))

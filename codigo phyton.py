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

print("\n--- RESULTADOS ---")
print("Suma:", suma(numeros))
print("Promedio: {:.2f}".format(promedio(numeros)))
print("Mayor:", mayor(numeros))
print("Menor:", menor(numeros))
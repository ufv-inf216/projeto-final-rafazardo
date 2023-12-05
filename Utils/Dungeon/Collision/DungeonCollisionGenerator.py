# Dungeon Collision Generator
# Trabalho Final da DisciplinaINF 216 - Projeto e Implementação de Jogos Digitais
# Objetivos: Gerar matrix de colisão para dungeons
# Criado por Rafael Zardo em 01/11/2023

# Cria uma matriz de colisão para uma sala retangular
# Input: 
# - h: altura da sala
# - w: largura da sala
# Output: 
# - Uma matriz bidimensional onde 0 representa espaço livre (não colide) e 1 representa uma parede (colide)
def CreateRectangularRoomCollisionMatrix(h, w):
    matrix = [[1] * w]  # Duas linhas de largura w formadas por 1
    matrix.append([1] * w)  # Duas linhas de largura w formadas por 1
    matrix.append([1] * w)  # Duas linhas de largura w formadas por 1

    for i in range(h - 6):
        row = [1] + [0] * (w - 2) + [1]  # Linhas do tipo 100...001
        matrix.append(row)

    matrix += [[1] * w]  # Duas linhas de largura w formadas por 1
    matrix += [[1] * w]  # Duas linhas de largura w formadas por 1
    matrix += [[1] * w]  # Duas linhas de largura w formadas por 1

    return matrix

# Cria uma matriz de colisão para uma sala circular
# Input: 
# - R: raio do circulo
# Output: 
# - Uma matriz bidimensional onde 0 representa espaço livre (não colide) e 1 representa uma borda (colide)
def CreateCircularRoomCollisionMatrix(R):
    size = 2 * R + 5
    center = size // 2
    matrix = []
    
    for i in range(1,size - 1):
        row = []
        for j in range(1,size - 1):
            distance = ((i - center) ** 2 + (j - center) ** 2) ** 0.5

            if distance <= R:
                row.append(0)  # Dentro da circunferência
            else:
                row.append(1)  # Fora da circunferência

        matrix.append(row)

    return matrix

# Cria uma matriz de colisão para uma sala retangular em U
# Input: 
# - h: altura da sala
# - w: largura da sala
# - direction: direção do formato em U (u - 'up', d - 'down', l - 'left', r - 'right')
# Output: 
# - Uma matriz bidimensional onde 0 representa espaço livre (não colide) e 1 representa uma parede (colide)
def CreateURoomCollisionMatrix(h, w, direction):
    matrix = CreateRectangularRoomCollisionMatrix(h, w)

    if direction == 'u':
        for i in range(1, w - 1):
            matrix[0][i] = 0
    elif direction == 'd':
        for i in range(1, w - 1):
            matrix[h-1][i] = 0
    elif direction == 'l':
        for i in range(1, h - 1):
            matrix[i][0] = 0
    elif direction == 'r':
        for i in range(1, h - 1):
            matrix[i][w-1] = 0
    else:
        print("Invalid direction. Please use 'u', 'd', 'l', or 'r'.")

    return matrix

# Escreve uma matriz de colisão em um arquivo
# Input: 
# - filename: Uma string que representa o nome do arquivo onde a matriz será gravada.
# - matrix: Uma matriz bidimensional (lista de listas) que representa a matriz de colisão que você deseja gravar no arquivo.
# Output: 
# - Nenhum (a função escreve a matriz no arquivo, não retorna um valor).
def WriteCollisionMatrixToFile(filename, matrix):
    with open(filename, 'w') as file:
        file.write(f"{len(matrix)} {len(matrix[0])}\n")
        
        for row in matrix:
            file.write(" ".join(map(str, row)) + "\n")

# Exemplos de uso:
dungeon_sq_w_h = CreateRectangularRoomCollisionMatrix(20, 20)
dungeon_cir_r = CreateCircularRoomCollisionMatrix(5)
dungeon_u_w_h = CreateURoomCollisionMatrix(15, 8, "u")

WriteCollisionMatrixToFile("./Results/dungeon_sq_w_h.collmat", dungeon_sq_w_h)
WriteCollisionMatrixToFile("./Results/dungeon_cir_r.collmat", dungeon_cir_r)
WriteCollisionMatrixToFile("./Results/dungeon_u_w_r.collmat", dungeon_u_w_h)

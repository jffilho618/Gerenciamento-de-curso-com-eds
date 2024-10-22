import matplotlib.pyplot as plt

# Dados de tempo de busca para ABB e AVL
abb_search_times = [8600, 8100, 8000, 9400, 9000, 10500, 9300, 8800, 8900, 9800, 6700, 10600, 7800, 7300, 8700, 8600, 8500, 8600, 7400, 7400, 7300, 7400, 8900, 10600, 7400, 8900, 10500, 7200, 7300, 9400]
avl_search_times = [400, 400, 300, 300, 300, 300, 300, 200, 300, 300, 300, 300, 300, 300, 300, 200, 300, 300, 300, 300, 200, 300, 300, 300, 300, 200, 200, 300, 200, 200]

# Gerar o gráfico de comparação dos tempos de busca

plt.figure(figsize=(10, 6))

# Gráfico de busca ABB
plt.plot(abb_search_times, label="ABB - Busca", color="blue", linestyle="--")

# Gráfico de busca AVL
plt.plot(avl_search_times, label="AVL - Busca", color="green", linestyle="-")

# Configurações do gráfico
plt.title('Comparação de Tempos de Busca - ABB vs AVL')
plt.xlabel('Execuções')
plt.ylabel('Tempo de Busca (nanosegundos)')
plt.legend()
plt.grid(True)
plt.tight_layout()

# Exibir o gráfico
plt.show()

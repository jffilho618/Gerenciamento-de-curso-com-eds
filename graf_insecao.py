# Re-import necessary libraries after environment reset
import matplotlib.pyplot as plt

# Dados de tempo de inserção para ABB e AVL
abb_random_insertion = [4300, 2900, 2300, 2300, 2400, 2800, 2700, 2600, 2100, 2400, 3100, 2800, 2500, 2100, 2000, 2100, 2300, 2300, 2600, 2900, 2200, 2500, 2400, 3000, 2600, 2400, 3200, 2300, 2300, 2100] 
abb_sorted_insertion = [906300, 781300, 761600, 795500, 814300, 767500, 776900, 788900, 737700, 892800, 851800, 1462700, 1213900, 927200, 1013300, 848300, 841600, 887300, 825200, 802800, 769900, 969500, 803600, 767400, 965800, 1008400, 833200, 925000, 828400, 1384600] 
abb_reverse_insertion = [2077500, 2365600, 2626900, 2145800, 2207300, 2091200, 3007200, 2698800, 3077600, 2218100, 2303700, 2124300, 2671400, 2041200, 2145900, 2197800, 2048900, 2092200, 2088100, 2114500, 2043500, 2125800, 2036400, 2414700, 2088200, 2078300, 2086900, 2111100, 2047900, 2133400]


avl_random_insertion = [11300, 6800, 5800, 5400, 5100, 5600, 5000, 5000, 5100, 5200, 5100, 4900, 5400, 4900, 5300, 5700, 7700, 7800, 8400, 7400, 6200, 8000, 7800, 7900, 6300, 6600, 4700, 5000, 5100, 4900] 
avl_sorted_insertion = [12800, 11900, 12000, 11400, 12000, 11500, 11900, 11800, 11800, 11600, 11500, 11500, 11600, 11400, 11600, 11700, 11400, 11000, 10900, 11100, 11300, 10900, 10900, 11300, 11300, 11400, 11200, 11700, 11600, 11000] 
avl_reverse_insertion = [14600, 13700, 13500, 13500, 13300, 12900, 13300, 13600, 13700, 13400, 13300, 13400, 13700, 13600, 13700, 13600, 13200, 13400, 13300, 13400, 13300, 13400, 13800, 13700, 13700, 13600, 13300, 13400, 13600, 13400]

# Gerar o gráfico de comparação

plt.figure(figsize=(10, 6))

# Gráfico ABB
plt.plot(abb_random_insertion, label="ABB - Ordem Aleatória", color="blue", linestyle="--")
plt.plot(abb_sorted_insertion, label="ABB - Ordem Crescente", color="green", linestyle="--")
plt.plot(abb_reverse_insertion, label="ABB - Ordem Decrescente", color="red", linestyle="--")

# Gráfico AVL
plt.plot(avl_random_insertion, label="AVL - Ordem Aleatória", color="blue", linestyle="-")
plt.plot(avl_sorted_insertion, label="AVL - Ordem Crescente", color="green", linestyle="-")
plt.plot(avl_reverse_insertion, label="AVL - Ordem Decrescente", color="red", linestyle="-")

# Configurações do gráfico
plt.title('Comparação de Tempos de Inserção - ABB vs AVL')
plt.xlabel('Execuções')
plt.ylabel('Tempo de Inserção (nanosegundos)')
plt.legend()
plt.grid(True)
plt.tight_layout()

# Exibir o gráfico
plt.show()

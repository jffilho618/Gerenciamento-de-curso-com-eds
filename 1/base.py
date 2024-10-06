import pandas as pd
import re
from unidecode import unidecode
import random

# Carregar o CSV
def carregar_base_dados(caminho_csv):
    try:
        df = pd.read_csv(caminho_csv, encoding='ISO-8859-1', delimiter=';')  # Altere o delimitador se necessário
        return df
    except FileNotFoundError:
        print("Arquivo CSV não encontrado. Verifique o caminho.")
        return None
    except UnicodeDecodeError as e:
        print(f"Erro de decodificação de caracteres: {e}")
        return None
    except pd.errors.ParserError as e:
        print(f"Erro de análise do CSV: {e}")
        return None

# Limpar o nome do curso, mantendo apenas a parte principal e removendo acentos e caracteres especiais
def limpar_nome_curso(nome_curso):
    # Remove partes após o primeiro hífen ou expressão de habilitação
    nome_curso = re.split(r' - | Com Habilitação Em | - Com Habilitação Em ', nome_curso)[0]
    
    # Remove acentos e caracteres especiais
    nome_curso = unidecode(nome_curso)
    
    # Remove espaços extras
    nome_curso = ' '.join(nome_curso.split())
    
    return nome_curso

# Projeta os nomes dos cursos acadêmicos, limpa e salva em arquivo txt
def salvar_nomes_cursos_repetidos(df, caminho_txt, num_linhas):
    if df is not None and 'NO_CURSO' in df.columns:
        cursos = df['NO_CURSO'].dropna().unique()
        indices = list(range(len(cursos)))

        with open(caminho_txt, 'w', encoding='utf-8') as f:
            while num_linhas > 0:
                random.shuffle(indices)
                for i in indices:
                    f.write(f"{cursos[i]}\n")
                    num_linhas -= 1
                    if num_linhas <= 0:
                        break

# Caminho para o arquivo CSV e TXT
caminho_csv = r'MICRODADOS_CADASTRO_CURSOS_2022.CSV'
caminho_txt = 'cursos.txt'

# Carregar a base de dados e salvar os nomes dos cursos
df = carregar_base_dados(caminho_csv)
salvar_nomes_cursos_repetidos(df, caminho_txt,1000000)

# Manual de Usuario - Motor de Inferencia SBR

## Descripción General
Este motor de inferencia implementa un sistema basado en reglas (SBR) con encadenamiento hacia atrás y factores de certeza. El sistema está desarrollado en C++ y permite procesar bases de conocimientos y hechos para inferir conclusiones.

## Requisitos
- Compilador C++ con soporte para C++17 o superior
- Git instalado (en caso de que se requiera clonar el repositorio)
- Code::Blocks 20.3

## Estructura del Repositorio

```
├── includes/           # Archivos de cabecera (.h)
├── sources/           # Archivos fuente (.cpp)  
└── main.cpp          # Punto de entrada del programa
```

## Clases Principales

### 1. Fact
Representa un hecho con:
- Identificador
- Factor de certeza

### 2. FactBase 
Gestiona la base de hechos:
- Almacena hechos
- Permite consulta y adición de hechos
- Maneja el hecho objetivo

### 3. Rule
Representa una regla con:
- Identificador 
- Antecedentes
- Consecuente
- Factor de certeza
- Tipo de regla (AND/OR)

### 4. KnowledgeBase
Gestiona la base de conocimiento:
- Almacena reglas
- Permite consulta de reglas

### 5. InferenceEngine 
Implementa el motor de inferencia:
- Algoritmo de encadenamiento hacia atrás
- Cálculo de factores de certeza
- Resolución de conflictos

## Formato de Archivos de Entrada

### Base de Conocimientos (.bc)
```
<número_de_reglas>
R1: Si <antecedente> Entonces <consecuente>, FC=<factor>
R2: Si <antecedente1> y <antecedente2> Entonces <consecuente>, FC=<factor>
R3: Si <antecedente1> o <antecedente2> Entonces <consecuente>, FC=<factor>
...
```

### Base de Hechos (.bh)
```
<número_de_hechos>
<hecho1>, FC=<factor>
<hecho2>, FC=<factor>
...
Objetivo
<objetivo>
```

## Uso del Programa

### Compilación
Importar el proyecto Code::Blocks 20.03 y llevar a cabo la compilacion. Por defecto  se ha configurado la compilación usando el estandar c++17 y usando linkado estatico, pues la version de GCC y Code::Blocks que ofrece el entorno Windows EVA presenta grandes fallas de linkado y de acceso a librerias estandar del sistema. Por lo tanto es necesario marcar las opciones ```-std=c++17``` y ```-static``` en caso de que no se encuentren marcadas


### Ejecución
```bash
.\<nombre_ejecutable> <base_conocimientos> <base_hechos1> [<base_hechos2> ...]
```

### Salida
El programa genera archivos .log con:
- Registro del proceso de inferencia
- Factores de certeza calculados
- Resultado final para el objetivo

## Mensajes de Error Comunes

1. "Formato de archivo de entrada inválido"
   - Revise el formato de los archivos .bc y .bh

2. "No se han proporcionado suficientes argumentos"
   - Asegúrese de proporcionar al menos una base de conocimientos y una base de hechos

## Ejemplos de Uso

```bash
# Procesar una base de hechos
".\SSII - InferenceEngine" ejemplo.bc ejemplo.bh

# Procesar múltiples bases de hechos
".\SSII - InferenceEngine" ejemplo.bc ejemplo1.bh ejemplo2.bh
```

## Formato de Salida

El sistema genera una salida estructurada en archivos .log con el siguiente formato:

### 1. Cabecera
```
··································
BASE DE CONOCIMIENTOS: "<nombre_BC>"
··································
BASE DE HECHOS: "<nombre_BH>"
··································
OBJETIVO: <objetivo>
··································
```

### 2. Proceso de Inferencia
Para cada regla activada durante el proceso, se muestra:

```
======================================================================
<tabs>R<num> (Regla Activada)
<tabs>    CASO 1 (si es necesario): <antecedentes>, FC=<factor>     # Evaluación de antecedentes
<tabs>    CASO 3: <consecuente>, FC=<factor>      					# Aplicación de la regla
<tabs>CASO 2 (si es necesario): <consecuente>, FC=<factor>          # Combinación de reglas (si aplica)
======================================================================
```

Donde:
- **CASO 1**: Muestra la evaluación de los antecedentes combinados
  - Para reglas AND: muestra antecedentes unidos por "y"
  - Para reglas OR: muestra antecedentes unidos por "o"
  - FC = factor de certeza resultante de la combinación

- **CASO 2**: Aparece cuando se combinan múltiples reglas para el mismo consecuente
  - Muestra el factor de certeza final tras combinar las reglas

- **CASO 3**: Muestra el resultado de aplicar una regla individual
  - FC = factor de certeza calculado para el consecuente

### 3. Resultado Final
```
RESULTADO OBTENIDO EN EL PROCESO DE INFERENCIA:

··································
<objetivo>, FC=<factor_final>
··································
```

La indentación (tabs) en el log indica la profundidad en el árbol de inferencia, permitiendo seguir visualmente el proceso de razonamiento del sistema.

Ademas, la profundidad asigna una jerarquia hacia abajo. Esto significa que evaluaciones tabuladas en el mismo nivel, las cuales tienen una evaluacion inmediatamente debajo y esta presenta una tabulacion inferior a la de estas dos, son evaluaciones requeridas para llevar a cabo la evaluación de esta ultima.

## Notas Importantes

- Los factores de certeza deben estar en el rango [-1,1]
- Las reglas admiten operadores "y"/"o" para antecedentes múltiples
- El sistema utiliza encadenamiento hacia atrás desde el objetivo
- Se generan archivos .log detallados del proceso de inferencia

## Soporte

Para reportar problemas o solicitar ayuda:
1. Abra un issue en el repositorio
2. Incluya los archivos de entrada y el mensaje de error
3. Describa los pasos para reproducir el problema

TUTORIA EIF201 PROGRAMACION I - LUNES 19 DE OCTUBRE DE 2026
Matrices de objetos, herencia y downcasting
Tutor: Andrey Jesus Solano Rojas

ESTRUCTURA
----------
01_Teoria/
    Guia_Teorica_Matrices_Herencia_Downcasting_EIF201.pdf
    codigo/sala_cine.cpp            Ejemplo completo de la guia (sala de cine)

02_Ejercicios/
    Ejercicios_Matrices_Herencia_Downcasting_EIF201.pdf
    ParteA_Trazado/                 Un programa por ejercicio, para comprobar
        A1_recorrido_columnas.cpp   la prediccion DESPUES de hacerla en papel
        A2_recorrido_zigzag.cpp
        A3_diagonales.cpp
        A4_region_sumada.cpp
        A5_dynamic_cast.cpp
        (A6 y A7 son de lectura de codigo: estan solo en el PDF)
    ParteB_Bodega/
        plantilla_bodega.cpp        Completar los ejercicios B1 a B6 en orden
    ParteC_Retos/
        sala_cine.cpp               Base para agregar los metodos de C1 a C4

03_Soluciones_tutor/                NO compartir con los estudiantes
    Soluciones_Matrices_Herencia_Downcasting_EIF201.pdf
    ParteB_Bodega/solucion_bodega.cpp
    ParteC_Retos/sala_cine_retos.cpp

COMO COMPILAR
-------------
Cada archivo .cpp es un programa independiente:
    g++ -std=c++11 archivo.cpp -o programa
En Visual Studio o CLion, cree un proyecto vacio y agregue el archivo.

NOTAS
-----
- plantilla_bodega.cpp compila desde el inicio, pero se cae al ejecutarse hasta
  que se resuelve B1 (constructor y destructor). Es intencional.
- Para compartir el material con los estudiantes, envie solo las carpetas
  01_Teoria y 02_Ejercicios.

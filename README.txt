TUTORIA EIF201 PROGRAMACION I - LUNES 2 DE NOVIEMBRE DE 2026
Repaso para el Examen 2 (domingo 8 de noviembre, 1:00 p. m.)
Tutor: Andrey Jesus Solano Rojas

ESTRUCTURA
----------
01_Teoria/
    Guia_Repaso_Examen2_EIF201.pdf     Resumen de todos los temas del examen
    Guias_de_semanas_anteriores/       Guias completas de cada tema
        1_Listas_Enlazadas.pdf
        2_Matrices_Herencia_Downcasting.pdf
        3_Herencia_Polimorfismo.pdf

02_Ejercicios/
    Ejercicios_Repaso_Examen2_EIF201.pdf
    ParteA_Ejercicios_cortos/          Para comprobar DESPUES de resolver en papel
        A1_polimorfismo.cpp
        A2_lista_trazado.cpp
        (A3 y A4 son de lectura de codigo: estan solo en el PDF)
    ParteB_Simulacro/
        plantilla_hospital.cpp         Simulacro tipo examen (50 minutos)

03_Soluciones_tutor/                   NO compartir con los estudiantes
    Soluciones_Repaso_Examen2_EIF201.pdf
    solucion_hospital.cpp

COMO COMPILAR
-------------
Cada archivo .cpp es un programa independiente:
    g++ -std=c++11 archivo.cpp -o programa
En Visual Studio o CLion, cree un proyecto vacio y agregue el archivo.

NOTAS
-----
- plantilla_hospital.cpp compila desde el inicio, pero se cae al ejecutarse
  hasta que se resuelve el ejercicio 2 (constructor del pabellon).
- Para compartir con los estudiantes, envie solo 01_Teoria y 02_Ejercicios.

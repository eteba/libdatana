#include "TMath.h"

/*
 * Función "datana".
 * 
 * Recibe un vector datos[N] y otro vector resultados[3].
 * Se hace un análisis de los resultados, devolviendo la media,
 * el intervalo de confianza para los sigmas que se soliciten y
 * puede que más cosas.
 * Por defecto, calcula el intervalo de confianza a 1 sigma,
 * descartando los datos que tengan una probabilidad de ocurrir de
 * menos de media vez (criterio de Chauvenet), aunque ambas cosas
 * se pueden sobreescribir al llamar a la función.
 * 		resultados[0]: media
 * 		resultados[1]: intervalo de confianza
 * 		resultados[2]: número de datos despreciados por Chauvenet.
 * 
 * NOTA: La función chauvenet() necesita hacer asumciones. En este
 * caso, aproximo la media muestral a la principal.
 * El criterio de Chauvenet considera que un dato es espúreo si su
 * probabilidad de ocurrir dentro de la muestra es de menos de media
 * vez.
 * 
 * Para el análisis, se ha tenido en cuenta que:
 * 		u=(dato-med_principal)/std_muestral sigue una T de Student.
 * 		u=(med_muestral-med_principal)/(std_muestral/sqrt(N)) también.
 */
void datana(double *datos, int N, double *resultados, int n_sigmas=1, bool chau=true);

/*
 * Funciones auxiliares.
 * 
 * 		media_muest() devuelve la media muestral de un conjunto de N datos.
 * 		varianza_muest() devuelve la varianza muestral de un conjunto de
 * 						 de N datos.
 * 		chauvenet() recibe un vector de datos, elimina los espúreos y
 * 					guarda los restantes en otro vector datos_aux.
 * 					NOTA: No pasarle como puntero el número de datos
 * 						  original, N, pues lo sobreescribirá. Usar una
 * 						  variable auxiliar en su lugar.
 */
double media_muest(double *datos, int N);
double varianza_muest(double *datos, int N, double med_muest);
bool chauvenet(double *datos, int *N_aux, double *datos_aux, double med_muest, double var_muest);

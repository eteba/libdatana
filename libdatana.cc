#include "libdatana.hh"

void datana(double *datos, int N, double *resultados, int n_sigmas, bool chau)
{
  double med_muest;
  double var_muest;
  int N_aux = N;
  
  // Criterio de Chauvenet
  if(chau)
  {
	double datos_aux[N];
	bool SeguirChau = true;
	do{
	  med_muest = media_muest(datos, N_aux);
	  var_muest = varianza_muest(datos, N_aux, med_muest);
	  
	  SeguirChau = chauvenet(datos, &N_aux, datos_aux, med_muest, var_muest);
	  
	  for(int i=0; i<N_aux; i++)
		datos[i] = datos_aux[i];
	}while(SeguirChau);
  }
  
  // Se puede pedir expresamente que no se aplique el criterio de Chauvenet
  else
  {
	med_muest = media_muest(datos, N_aux);
	var_muest = varianza_muest(datos, N_aux, med_muest);
  }
  
  //La varianza muestral de la distribucion de medias muestrales es s^2/N
  double var_med_muest = var_muest/N_aux;
  
  //Probabilidad que suponen las n_sigmas
  double P = TMath::Erf(n_sigmas/sqrt(2));
  
  //Quantil de una T de Student con N-1 grados de libertad equivalente a P
  double k = TMath::StudentQuantile((1-P)/2, N_aux-1, false);
  
  //Llenado de resultados
  resultados[0] = med_muest;
  resultados[1] = k*sqrt(var_med_muest);
  resultados[2] = N-N_aux;
  
  return;
}

double media_muest(double *datos, int N)
{
  double suma = 0.0;

  for(int i=0; i<N; i++)
	suma += datos[i];
  suma /= 1.0*N;

  return suma;
}

double varianza_muest(double *datos, int N, double med_muest)
{
  double suma = 0.0;
  
  for(int i=0; i<N; i++)
	suma += (datos[i]-med_muest)*(datos[i]-med_muest);
  suma /= 1.0*(N-1);

  return suma;
}

bool chauvenet(double *datos, int *N_aux, double *datos_aux, double med_muest, double var_muest)
{
  // P(med_princ - k_chau*s < x < med_princ + k_chau*s) = 1-1/(2N)
  double k_chau = TMath::StudentQuantile(1.0/(4*(*N_aux)), (*N_aux)-1, false);
  double std_muest = sqrt(var_muest);
  
  int cont_Sirven = 0;
  
  for(int i=0; i<*N_aux; i++)
	if((datos[i] >= med_muest-k_chau*std_muest) && (datos[i] <= med_muest+k_chau*std_muest))
	{
	  datos_aux[cont_Sirven] = datos[i];
	  cont_Sirven++;
	}
  
  int N_old = *N_aux;
  *N_aux = cont_Sirven;
    
  return (*N_aux == N_old) ? false : true;
}

#include <math.h>
#include <fcntl.h>
#include <time.h>
#include <iostream>
#include <string>
#include <C_General.hpp>
#include <C_Trace.hpp>
#include <C_File.hpp>
#include <C_Arguments.hpp>
#include <C_Matrix.hpp>
#include <C_Image.hpp>


double parecido(C_Matrix::IndexT j, C_Matrix::IndexT i,C_Matrix::IndexT compA, C_Matrix::IndexT compB, C_Image imag);

//primer metodo parecido
double parecido(int aux,C_Matrix::IndexT compA, C_Matrix::IndexT compB, C_Image imag){
	int numero=1;
	double aux1=1;
	if(imag.LastRow()<compA||imag.FirstRow()>compA ||imag.LastCol()<compB||imag.FirstCol()>compB){
		printf("fuera de rango no se computa");
	}
	
	else{
	numero= imag(compA,compB);
	numero++;

	aux1 = (double)(numero)/(aux+1);
	}
	return aux1;
}

int main(int argc, char **argv)
{

	// aqui se describe el menu con las diferentes opciones
 	string archivo;
	cout<< "Introduzca el nombre de la imagen a procesar\n";
	cin>>archivo;
	int blancoGris=1;
	int positivo;
	int criba=20;
	double rango1;
	double rango2;			
	C_Image imagen ;
	C_Image imagen2 ;
	//Accion para implementarla en un futuro, seria poner todos los puntos grises a negro o blanco dependiendo,
	//Para ello se ha puesto mas adelante la variable plus
	//cout<<"Para que la solucion sea en escala de grises pulse (0), para blanco y negro pulse (1)";
    //cin>>blancoGris;
	cout<<"Desea una solucion en negativo(1) o en positivo(0)\n";
	cin>>positivo;
	cout<<"El valor de criba afecta a la cantidad de pixeles analizados";
	cout<<"Que valor de criba desea nivel recomendado entre 10 y 50\n";
	cin>>criba;
	cout<<"El rango afecta a la sensibilidad de deteccion del programa, es decir, si detectara bordes mas pronunciados o menos pronunciados.";
	cout<<"Cuanto mayor rango y menor rango inferior mas dura sera la criba y mas pronunciado sera el borde detectado";
	cout<<"Que rango superior desea establecer entre 1 y 2\n";
	cin>>rango2;
	cout<<"Que rango inferior desea establecer entre 0 y 1\n";
	cin>>rango1;
	int tiempo;
	clock_t inicio,parada; 

	inicio=clock();

//Aquí el proceso a medir


	//imagen.ReadBMP("Ajedrez_Gris.bmp");
	//imagen2.ReadBMP("Ajedrez_Gris.bmp");
	//imagen.ReadBMP("Alumina.bmp");
	//imagen2.ReadBMP("Alumina.bmp");
	//imagen.ReadBMP("Hercules_Gris.bmp");
	//imagen2.ReadBMP("Hercules_Gris.bmp");
	//imagen.ReadBMP("Aguadulce_Gris.bmp");
	//imagen2.ReadBMP("Aguadulce_Gris.bmp");
	
	//lectura de la imagen
	imagen.ReadBMP(archivo.c_str());
	imagen2.ReadBMP(archivo.c_str());
	

	//C_Matrix matriz (imagen.FirstRow(),imagen.LastRow() , imagen.FirstCol(),imagen.LastCol(), 0);
	
	//indices j y j para poderte mover por la matriz
	C_Matrix::IndexT j,i;


	//C_Matrix multiplicador (imagen.FirstRow(),imagen.LastRow(),imagen.FirstCol(),imagen.LastCol(),0) ;
	printf("he llegado a calcular");
	for( j=imagen.FirstRow();j<=imagen.LastRow();j++){
		printf("Porcentaje: ");
		int porcentaje= (j-imagen.FirstRow())*100/(imagen.FirstRow()-imagen.LastRow());
		
		printf("%d\n", abs( porcentaje));	
		for( i=imagen.FirstCol();i<=imagen.LastCol();i++){
		// para poder aplicar matrices a la imagen pero no lo voy a usar
		//	multiplicador(j,i); para futuras matrices ahora no sirve

			int aux= imagen(j,i);
			//aqui se sale de rango cuando hace la consulta a la imagen.
			if(imagen.LastRow()>j&&imagen.FirstRow()<j &&imagen.LastCol()>i&&imagen.FirstCol()<i){
		
	
			int plus=0;
			if(abs((aux)-imagen(j+1,i))>=criba||abs((aux)-imagen(j,i+1))>=criba||abs((aux)-imagen(j-1,i))>=criba||abs((aux)-imagen(j,i-1))>=criba||abs((aux)-imagen(j+1,i+1))>=criba||abs((aux)-imagen(j+1,i-1))>=criba||abs((aux)-imagen(j-1,i+1))>=criba||abs((aux)-imagen(j-1,i-1))>=criba){
	
				double auxX1;
				double auxX2;
				double auxY1;
				double auxY2;
				//aqui se llama a la funcion parecido pero el tiempo de ejecucion pasa de 1 segundo a mas de media hora
				//double auxX1=parecido(aux,j+1,i,imagen);
				//double auxX2=parecido(aux,j-1,i,imagen);
				//double auxY1=parecido(aux,j,i-1,imagen);
				//double auxY2=parecido(aux,j,i+1,imagen);
				int numeroX1=1;
				int numeroX2=1;
				int numeroY1=1;
				int numeroY2=1;
				numeroX1= imagen(j+1,i);
				numeroX2= imagen(j-1,i);
				numeroY1= imagen(j,i-1);
				numeroY2= imagen(j,i+1);
				auxX1 = (double)(numeroX1+1)/(aux+1);
				auxX2 = (double)(numeroX2+1)/(aux+1);
				auxY1 = (double)(numeroY1+1)/(aux+1);
				auxY2 = (double)(numeroY2+1)/(aux+1);
				bool modificadoX1=false;
				bool modificadoX2=false;
				bool modificadoY1=false;
				bool modificadoY2=false;
		
				
				if(rango1<auxX1||auxX1>rango2){
					if(rango1<auxX1){
						if(((aux+plus)/auxX1)>254){// si nos pasamos de 255 se nos cambia la paleta de colores
							imagen2(j,i)=254;
							modificadoX1=true;
						} 
						else{
							imagen2(j,i)=(aux+plus)/auxX1;
							modificadoX1=true;
						}
					}
					else{
						if(((aux+plus)*auxX1)>254){
							modificadoX1=true;
							imagen2(j,i)=254;
						} 
						else{
							imagen2(j,i)=(aux+plus)*auxX1;							
							modificadoX1=true;
						}
					
					}
				
				}
				if(rango1<auxX2||auxX2>rango2){
					if(rango1<auxX2){
						if(((aux+plus)/auxX2)>254){// si nos pasamos de 255 se nos cambia la paleta de colores
							imagen2(j,i)=254;
							modificadoX2=true;
							
						} 
						else{
							modificadoX2=true;
							
							if(modificadoX1){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)/auxX2)/2;
							}
							else{
								imagen2(j,i)=(aux+plus)/auxX2;
							}
						}
					}
					else{
						if(((aux+plus)*auxX2)>254){// si nos pasamos de 255 se nos cambia la paleta de colores
							modificadoX2=true;
							imagen2(j,i)=254;
						} 
						else{	
							modificadoX2=true;
							if(modificadoX1){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)*auxX2)/2;
							}
							else{
								imagen2(j,i)=(aux+plus)*auxX2;
							}
						}
					}
				}
				if(rango1<auxY1||auxY1>rango2){
					if(rango1<auxY1){
						if(((aux+plus)/auxY1)>254){// si nos pasamos de 255 se nos cambia la paleta de colores
							modificadoY1=true;
							imagen2(j,i)=254;
						} 
						else{
							modificadoY1=true;
							if(modificadoX1){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)/auxY1)/2;
							}
							if(modificadoX2){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)/auxY1)/2;
							}		
							else{
							imagen2(j,i)=(aux+plus)/auxY1;
							}
						}
					}
					else{
						if(((aux+plus)*auxY1)>254){// si nos pasamos de 255 se nos cambia la paleta de colores
							modificadoY1=true;
							imagen2(j,i)=254;
						} 
						else{
							modificadoY1=true;
							if(modificadoX1){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)*auxY1)/2;
							}
							if(modificadoX2){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)*auxY1)/2;
							}
							else{
								imagen2(j,i)=(aux+plus)*auxY1;
							}
						}
					}

	
				}
				if(rango1<auxY2||auxY2>rango2){
					if(rango1<auxY2){
						if(((aux+plus)/auxY2)>254){// si nos pasamos de 255 se nos cambia la paleta de colores
							imagen2(j,i)=254;
							modificadoY2=true;
						} 
						else{
							modificadoY2=true;
							if(modificadoX1){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)/auxY2)/2;
							}
							if(modificadoX2){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)/auxY2)/2;
							}		
							if(modificadoY1){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)/auxY2)/2;
							}
							else{
								imagen2(j,i)=(aux+plus)/auxY2;
							}
						}
					}

					else{
						if(((aux+plus)*auxY2)>254){// si nos pasamos de 255 se nos cambia la paleta de colores
							modificadoY2=true;
							imagen2(j,i)=254;
						} 
						else{
							modificadoY2=true;
							if(modificadoX1){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)*auxY2)/2;
							}
							if(modificadoX2){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)*auxY2)/2;
							}		
							if(modificadoY1){
								imagen2(j,i)=(imagen2(j,i)+(aux+plus)*auxY2)/2;
							}
							else{
								imagen2(j,i)=(aux+plus)*auxY2;
							}
						}
					}
				}

				// el error esta aqui dado que unos valores puden ocultar a los otros para ello realizamos la media de todos ellos
				//hay que dividir entre las 4 coordenadas con distintos if para poder cribar mejor y hacer la funcion mas sencilla
				// seguimos teniendo margen en el rango de puntos clave de arriba poner tambien la funcion de marcado de bordes.
				
		
				else{
					if(positivo==1){
						imagen2(j,i)=0;
					}
					else{
						imagen2(j,i)=255;
					}
				}
			}
			else{
			  if(positivo==1){
					imagen2(j,i)=0;
					}
				else{
					imagen2(j,i)=255;
					}
				}
			}
		}
	}
	// importante pruebas de tiempo
	time_t t2 = time (NULL);
	
	printf("Duracion(ms): ");  

	parada=clock();
	tiempo=1000L*(parada-inicio)/CLK_TCK;

	printf("%d\n", tiempo); 

	//imagen2.WriteBMP("sol"+strlen(archivo.c_str()));
	imagen2.WriteBMP("Solucion.bmp");
	int numero=0;
	cin>>numero;
}


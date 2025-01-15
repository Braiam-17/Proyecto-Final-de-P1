#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Definición de colores en Windows
#define RED     12
#define GREEN   10
#define YELLOW  14
#define BLUE    9

// Función para establecer el color de texto en la consola de Windows
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}



typedef struct empleados{
	int cod;
	char dni[9];
	char cuil [15];
	char nombres [40];
	char apellidos [40];
}empleados;

typedef struct empresas{
	int cod;
	char cuit [15];
	char nombreE [40];
}empresas;

typedef struct datos {
	int dispositivo;
	int codigoEmpleado;
	char fecha [11];
	float costoH;
	float costoS;
	char nombEmpresa[100];
	int codigoEmpresa;
	float precioFinal;
}datos;

typedef struct nodo{
	int indice;
    struct datos dato;
	struct nodo *sig;
}nodo;


nodo *primero = NULL;
nodo *ultimo = NULL;
void ficheroEmpleados(){
	empleados empleadosCuyanito;
	FILE *fichero_empleados = fopen("empleados.dat","rb");
	if(fichero_empleados == NULL){
		printf("Error! No se pudo abrir el archivo");
	}
	else{
		system("cls");
		printf("\t>>>>>[DATOS EMPLEADOS]<<<<<");
		fread(&empleadosCuyanito,sizeof(empleados),1,fichero_empleados);
		while(!feof(fichero_empleados)){
			printf("\n[Codigo: %d] - [D.N.I: %s] - [Nombre y Apellido: %s %s]",empleadosCuyanito.cod,empleadosCuyanito.dni,empleadosCuyanito.nombres,empleadosCuyanito.apellidos);
			fread(&empleadosCuyanito,sizeof(empleados),1,fichero_empleados);
		}
		fclose(fichero_empleados);
	}
	printf("\n------------------------");
}
void ficheroEmpresas(){
	empresas empresasCuyanito;
	FILE *fichero_empresas = fopen("empresas.dat","rb");
	if(fichero_empresas == NULL){
		printf("!Error¡ No se pudo abrir el archivo");
	}
	else{
		printf("\t>>>>>[DATOS EMPRESAS]<<<<<");
		fread(&empresasCuyanito,sizeof(empresas),1,fichero_empresas);
		while(!feof(fichero_empresas)){
			printf("\n[Codigo: %d] - [Nombre: %s]",empresasCuyanito.cod,empresasCuyanito.nombreE);
			fread(&empresasCuyanito,sizeof(empresas),1,fichero_empresas);
		}
		fclose(fichero_empresas);
	}
}
int mostrarMenu();
void ingresarRep();
void buscarRepSegunTipo();
void buscarRepMayorPrecioFinal();
void mostrarRepEmplEspecifico();
void mostrarRepCorresAEmpresa();
void mostrarRepRealizadasEnFecha();
void almacenarReps();
void salir();
void ficheroEmpleados();
void ficheroEmpresas();
void mostrarReparaciones();
void borrarReparacion();


int main(){
	int opcion=1;
	while(opcion!=0){
	opcion = mostrarMenu();
	switch (opcion){
		case 1: system("cls"); ingresarRep(); break;
		case 2: system("cls"); buscarRepSegunTipo(); break;
		case 3: system("cls"); buscarRepMayorPrecioFinal(); break;
		case 4: system("cls"); mostrarRepEmplEspecifico(); break;
		case 5: system("cls"); mostrarRepCorresAEmpresa(); break;
		case 6: system("cls"); mostrarRepRealizadasEnFecha(); break;
		case 7: system("cls"); almacenarReps(); break;
		case 8: system("cls"); mostrarReparaciones(); break;
		case 9: system("cls"); borrarReparacion(); break;
		case 10: system("cls"); printf("¡Muchas gracias por utilizar Cuyanito Reparaciones, que tengas un buen dia!\n[by El Cuervo Reparaciones]\n"); exit(0); break;
		default: system("cls"); break;
		}
	}
}
int mostrarMenu(){
    int opcion;
    printf("\t\t>>>[Menu Cuyanito - By El Cuervo Reparaciones]<<<\n\n");
    setColor(BLUE);
    printf("1. Ingresar reparaciones.\n");
    printf("2. Buscar reparacion segun tipo de dispositivo\n");
    printf("3. Buscar la reparacion con el mayor precio.\n");
    printf("4. Mostrar las reparaciones realizadas por un empleado especifico.\n");
    printf("5. Mostrar las reparaciones correspondientes a una sola empresa.\n");
    printf("6. Mostrar las reparaciones realizadas en una fecha.\n");
    printf("7. Almacenar todas las reparaciones.\n");
    printf("8. Mostrar reparaciones.\n");
	printf("9. Borrar reparacion en memoria.\n");
	setColor(RED);
	printf("10. Salir del programa\n");
    printf("\nSeleccione una opcion: "); scanf("%d",&opcion);
    setColor(7); // Restablecer a color predeterminado
    return opcion;
}

void mostrarReparaciones(){
	nodo *actual = malloc(sizeof(nodo));
	actual = primero;
	int indice = 1, contadorMemoria = 0, contadorAlmacenada = 0;
	printf("\t>>>>>[REPARACIONES EN MEMORIA]<<<<<\n\n");
	while (actual!=NULL){
		actual->indice = indice;
		printf("\n[%d] - [Dispositivo reparado: %d] - [Codigo de empleado: %d] - [Codigo de la empresa: %d] - [Fecha: %s] - [Precio final: %.2f]\n",actual->indice,actual->dato.dispositivo,actual->dato.codigoEmpleado,actual->dato.codigoEmpresa,actual->dato.fecha,actual->dato.precioFinal);
		actual = actual->sig;
		indice++; contadorMemoria++;
	}
	printf("\n>[Total de reparaciones en memoria %d]<\n\n",contadorMemoria);
	FILE *ficheroRep = fopen("data.txt","r");
	if(ficheroRep==NULL){ printf("\n No se pudo abrir el archivo\n"); }
	else{
		datos datosAlmacenados;
		indice= 1;
		printf("\t>>>>>[REPARACIONES ALMACENADAS]<<<<<\n\n");
		fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
		while(!feof(ficheroRep)){
			printf("\n[%d] - [Dispositivo reparado: %d] - [Codigo de Empleado: %d] - [Codigo de Empresa: %d] - [Fecha: %s] - [Precio Final: %.2f]\n",indice,datosAlmacenados.dispositivo,datosAlmacenados.codigoEmpleado,datosAlmacenados.codigoEmpresa,datosAlmacenados.fecha,datosAlmacenados.precioFinal);
			fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
			indice++; contadorAlmacenada++;
		}
		fclose(ficheroRep);
		printf("\n>[Total de reparaciones almacenadas %d]<\n\n",contadorAlmacenada);
	}
	printf("\n>[Total de reparaciones son %d]<\n\n",(contadorMemoria+contadorAlmacenada));
	system("PAUSE"); system("cls"); fflush(stdin);
}
void ingresarRep(){
	nodo *nuevo = malloc(sizeof(nodo));
	int opcion;
	system("cls"); fflush(stdin);
	printf("\t\t\t>>>>>[INGRESAR REPARACIONES]<<<<<\n\n");
    printf("Tipo de dispositivo (1.Notebook 2.Celular 3.PC)\n");
	printf("Ingrese el dispositivo reparado: ");
	scanf("%d",&nuevo->dato.dispositivo);
    while(nuevo->dato.dispositivo < 1 || nuevo->dato.dispositivo > 3){
		system("cls");
		printf("\t\t\t>>>>>[INGRESAR REPARACIONES]<<<<<\n\n");
		printf("Tipo de dispositivo (1.Notebook 2.Celular 3.PC)\n");
		printf("Ingrese el dispositivo reparado: "); scanf("%d",&nuevo->dato.dispositivo);
    }
    ficheroEmpleados();
    printf("\nIngrese el codigo de Empleado: "); fflush(stdin); scanf("%d",&nuevo->dato.codigoEmpleado);
    while(nuevo->dato.codigoEmpleado < 1 || nuevo->dato.codigoEmpleado > 11){
		system("cls");
		ficheroEmpleados();
		printf("\nCodigo de empleado equivocado, intente de nuevo.\n");
		printf("Ingrese el codigo de empleado: "); scanf("%d",&nuevo->dato.codigoEmpleado);
    }
	system("cls");
	printf("\t\t\t>>>>>[INGRESAR REPARACIONES]<<<<<\n\n");
    printf("Fecha de la reparacion (dd/mm/aaaa): "); fflush(stdin); scanf("%s",nuevo->dato.fecha);
	printf("---------------------\n");
    printf("La reparacion fue de 1.Hardware 2.Software 3.Ambos\n"); fflush(stdin);
	printf("Ingrese opcion: "); scanf("%d",&opcion);
    switch(opcion){
        case 1: printf("Ingrese el costo del hardware: "); scanf("%f",&nuevo->dato.costoH); break;
        case 2: printf("Ingrese el costo del software: "); scanf("%f",&nuevo->dato.costoS); break;
        case 3: printf("Ingrese el costo del hardware: "); scanf("%f",&nuevo->dato.costoH); fflush(stdin);
                printf("Ingrese el costo del software: "); scanf("%f",&nuevo->dato.costoS); break;
	}
    while(opcion < 1 || opcion > 3){
        fflush(stdin);
        printf("La reparacion fue de 1.Hardware 2.Software 3.Ambos\n"); scanf("%d",&opcion);
        switch(opcion){
			case 1: printf("Ingrese el costo del hardware: "); scanf("%f", &nuevo->dato.costoH); break;
			case 2: printf("Ingrese el costo del software: "); scanf("%f", &nuevo->dato.costoS); break;
			case 3: printf("Ingrese el costo del hardware: "); scanf("%f", &nuevo->dato.costoH); fflush(stdin); printf("Ingrese el costo del software: "); scanf("%f", &nuevo->dato.costoS); break;
        }
    }
    system("cls");
    ficheroEmpresas();
    fflush(stdin);
	printf("\n--------------------------------------------\n");
    printf("Ingrese el codigo de la empresa: "); scanf("%d", &nuevo->dato.codigoEmpresa);
    while(nuevo->dato.codigoEmpresa < 1 || nuevo->dato.codigoEmpresa > 10){
		system("cls");
		ficheroEmpresas();
		printf("\nCodigo de empresa equivocado, intente de nuevo.\n");
		printf("Ingrese el codigo de la empresa: "); scanf("%d",&nuevo->dato.codigoEmpresa);
    }
    nuevo->dato.precioFinal = nuevo->dato.costoH + nuevo->dato.costoS;
	if(primero == NULL){
		primero = nuevo;
		primero->sig = NULL;
		ultimo = nuevo;
	}
	else{
		ultimo->sig = nuevo;
		nuevo->sig = NULL;
		ultimo = nuevo;
	}
	printf("\nReparacion almacenada en la memoria con exito.\n");
	system("pause"); system("cls");
}
void buscarRepSegunTipo(){
	int dispositivoBuscar,contador = 0,indice = 1;
	FILE *ficheroRep = fopen("data.txt","r");
	nodo *actual;
	actual = primero;
	printf("\t\t>>>>>[BUSCAR REPARACION]<<<<<\n\n");
	printf("¿Que dispositivo desea buscar? (1.Notebook 2.Celular 3.PC)\n");
	printf("Ingrese dispositivo: "); scanf("%d",&dispositivoBuscar);
	while(dispositivoBuscar < 1 || dispositivoBuscar > 3){
		system("cls");
		printf("Error, ingrese tipo de dispositivo correcto. (1.Notebook 2.Celular 3.PC)\n");
		printf("Ingrese el dispositivo reparado: "); scanf("%d",&dispositivoBuscar);
	}
	printf("\n\n"); fflush(stdin); system("cls");
	printf("\t\t>>>>>[REPARACIONES ACTUALES]<<<<<\n\n");
	while (actual!=NULL){ //Buscar reparaciones en la memoria
		if(actual->dato.dispositivo == dispositivoBuscar){
		actual->indice = indice;
		printf("\n[%d] - [Dispositivo reparado: %d] - [Codigo de empleado: %d] - [Codigo de la empresa: %d] - [Fecha: %s] - [Precio final: %.2f]\n",actual->indice,actual->dato.dispositivo,actual->dato.codigoEmpleado,actual->dato.codigoEmpresa,actual->dato.fecha,actual->dato.precioFinal);
		printf("\n\n");
		indice++;
		contador++;
		}
		actual = actual->sig;
	}
	printf("\t[Total de reparaciones de tipo %d en memoria: %d]\n\n",dispositivoBuscar,contador);
	if(ficheroRep == NULL){ printf("\n No se pudo abrir el archivo\n"); }
	else{
		contador = 0,indice = 1;
		datos datosAlmacenados;
		fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
		printf("\t\t>>>>>[REPARACIONES ALMACENADAS]<<<<<\n\n");
		while(!feof(ficheroRep)){ //buscar reparaciones ya almacenadas
			if(datosAlmacenados.dispositivo == dispositivoBuscar){
				printf("\n[%d] - [Dispositivo reparado: %d] - [Codigo de Empleado: %d] - [Fecha: %s] - [Precio Final: %.2f]\n",indice,datosAlmacenados.dispositivo,datosAlmacenados.codigoEmpleado,datosAlmacenados.fecha,datosAlmacenados.precioFinal);
				contador++;
				indice++;
			}
			fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
		}
		fclose(ficheroRep);
		printf("\n\t[Total de reparaciones de tipo %d almacenadas: %d]\n",dispositivoBuscar,contador);
	}


	printf("\n\n"); system("PAUSE"); system("cls");
}
void buscarRepMayorPrecioFinal(){
    float precioMayor = 0;
    float precioMayor1 = 0;
    datos auxiliar;
    datos auxiliar1;
    datos datosAlmacenados;
	FILE *ficheroRep = fopen("data.txt","r");
	nodo *actual;
	actual = primero;
	while (actual!=NULL){
		if(actual->dato.precioFinal > precioMayor){
            precioMayor = actual->dato.precioFinal;
            auxiliar = actual->dato;
		}
		actual = actual->sig;
	}
	if(ficheroRep == NULL){
		printf("\n No se pudo abrir el archivo\n");
	}
	else{
            fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
            while(!feof(ficheroRep)){
                    if(datosAlmacenados.precioFinal > precioMayor1){
                        precioMayor1 = datosAlmacenados.precioFinal;
                        auxiliar1 = datosAlmacenados;
			}
            fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
            }
            fclose(ficheroRep);
	}
	printf("\t\t\t>>>>>[REPARACIONES CON MAYOR PRECIO]<<<<<\n\n");
	if(precioMayor > precioMayor1 ){
        printf("\n- [Dispositivo: %d] - [Codigo de Empleado: %d] - [Codigo de Empresa: %d] - [Fecha: %s] - [Precio Final: %.2f]\n",auxiliar.dispositivo,auxiliar.codigoEmpleado,auxiliar.codigoEmpresa,auxiliar.fecha,auxiliar.precioFinal);
	}else if(precioMayor == precioMayor1){
		printf("\n- [Dispositivo: %d] - [Codigo de Empleado: %d] - [Codigo de Empresa: %d] - [Fecha: %s] - [Precio Final: %.2f]\n",auxiliar.dispositivo,auxiliar.codigoEmpleado,auxiliar.codigoEmpresa,auxiliar.fecha,auxiliar.precioFinal);
		printf("\n- [Dispositivo: %d] - [Codigo de Empleado: %d] - [Codigo de Empresa: %d] - [Fecha: %s] - [Precio Final: %.2f]\n",auxiliar1.dispositivo,auxiliar1.codigoEmpleado,auxiliar1.codigoEmpresa,auxiliar1.fecha,auxiliar1.precioFinal);
    }
	else{
		printf("\n- [Dispositivo: %d] - [Codigo de Empleado: %d] - [Codigo de Empresa: %d] - [Fecha: %s] - [Precio Final: %.2f]\n",auxiliar1.dispositivo,auxiliar1.codigoEmpleado,auxiliar1.codigoEmpresa,auxiliar1.fecha,auxiliar1.precioFinal);
	}
	printf("\n\n");
	system("PAUSE"); system("cls");
}
void mostrarRepEmplEspecifico(){
	int empleadoBuscar,contador = 0,indice = 1;
	FILE *ficheroRep = fopen("data.txt","r");
	nodo *actual;
	actual = primero;
	ficheroEmpleados();
	printf("\n¿Que empleado desea buscar correspondiente a su codigo?.\n");
	printf("\nSeleccione codigo de empleado: "); scanf("%d",&empleadoBuscar);
	fflush(stdin);
	while(empleadoBuscar < 1 || empleadoBuscar > 11){
		system("cls");
		printf("Error, ingrese tipo un codigo correcto. (1.Notebook 2.Celular 3.PC)\n");
		ficheroEmpleados();
		printf("\nSeleccione el codigo de empleado: "); scanf("%d",&empleadoBuscar);
	}
	printf("\n\n"); fflush(stdin); system("cls");
	if(actual != NULL){
		printf("\t\t>>>>>[EMPLEADO %d MEMORIA]<<<<<\n",empleadoBuscar);
		while(actual!=NULL){
			if(actual->dato.codigoEmpleado == empleadoBuscar){
				actual->indice = indice;
				printf("\n[%d] - [Dispositivo: %d] - [Codigo de Empleado: %d] - [Codigo de la Empresa: %d] - [Fecha: %s] - [Precio final: %.2f]\n\n",actual->indice,actual->dato.dispositivo,actual->dato.codigoEmpleado,actual->dato.codigoEmpresa,actual->dato.fecha,actual->dato.precioFinal);
				indice++; contador ++;
			}
		actual = actual->sig;
		}
		printf("\n\t[Total de reparaciones en memoria por Empleado %d, fueron %d]\n\n",empleadoBuscar,contador);
	}
	if(ficheroRep == NULL){ printf("\n No se pudo abrir el archivo\n"); }
	else{
		datos datosAlmacenados;
		fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
		printf("\t\t>>>>>[EMPLEADO %d ALMACENADO]<<<<<\n\n",empleadoBuscar);
		while(!feof(ficheroRep)){
			if(datosAlmacenados.codigoEmpleado == empleadoBuscar){
				printf("\n[%d] - [Dispositivo: %d] - [Codigo de Empleado: %d]- [Codigo de Empresa: %d] - [Fecha: %s] - [Precio Final: %.2f]\n",indice,datosAlmacenados.dispositivo,datosAlmacenados.codigoEmpleado,datosAlmacenados.codigoEmpresa,datosAlmacenados.fecha,datosAlmacenados.precioFinal);
				indice++; contador++;
			}
			fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
		}
		fclose(ficheroRep);
	}
	printf("\n\t[Total de reparaciones almacenadas por Empleado %d, fueron %d]\n",empleadoBuscar,contador);
	printf("\n\n"); system("PAUSE"); system("cls");
}
void mostrarRepCorresAEmpresa(){
    int empresaBuscar, indice = 1, contador = 0;
	FILE *ficheroRep = fopen("data.txt","r");
	nodo *actual;
	actual = primero;
	ficheroEmpresas();
	printf("\n\n¿Que empresa desea buscar correspondiente a su codigo?.\n");
	printf("\nSeleccione codigo de empresa: "); scanf("%d",&empresaBuscar);
	fflush(stdin);
	while(empresaBuscar < 1 || empresaBuscar > 10){
		system("cls");
		printf("Error, ingrese un codigo correcto.\n");
		ficheroEmpresas();
		printf("\nSeleccione el codigo de empresa: "); scanf("%d",&empresaBuscar);
	}
	printf("\n\n"); fflush(stdin); system("cls");
	printf("\t\t>>>>>[EMPRESA %d MEMORIA]<<<<<\n\n",empresaBuscar);
	while (actual!=NULL){
		if(actual->dato.codigoEmpresa == empresaBuscar){
			actual->indice = indice;
			printf("\n[%d] - [Dispositivo: %d] - [Codigo de empleado: %d] - [Codigo de la empresa: %d] - [Fecha: %s] - [Precio final: %.2f]\n",actual->indice,actual->dato.dispositivo,actual->dato.codigoEmpleado,actual->dato.codigoEmpresa,actual->dato.fecha,actual->dato.precioFinal);
			indice++; contador ++;
		}
		actual = actual->sig;
	}
	printf("\n\t[Total de reparaciones en memoria con empresa %d, fueron %d]\n\n",empresaBuscar,contador);
	if(ficheroRep == NULL){ printf("\n No se pudo abrir el archivo\n"); }
	else{
		contador = 0, indice = 1;
		datos datosAlmacenados;
		fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
		printf("\t\t>>>>>[EMPRESA %d ALMACENADA]<<<<<\n\n",empresaBuscar);
		while(!feof(ficheroRep)){
			if(datosAlmacenados.codigoEmpresa == empresaBuscar){
				printf("\n[%d] - [Dispositivo: %d] - [Codigo de Empleado: %d] - [Codigo de Empresa: %d] - [Fecha: %s] - [Precio Final: %.2f]\n",indice,datosAlmacenados.dispositivo,datosAlmacenados.codigoEmpleado,datosAlmacenados.codigoEmpresa,datosAlmacenados.fecha,datosAlmacenados.precioFinal);
				indice++; contador ++;
			}
			fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
		}
		printf("\n\t[Total de reparaciones almacenadas con empresa %d, fueron %d]\n",empresaBuscar,contador);
		fclose(ficheroRep);
	}
	printf("\n\n"); system("PAUSE"); system("cls");
}
void mostrarRepRealizadasEnFecha(){
    char fechaBuscar[11];
	int indice = 1, contador = 0;
	FILE *ficheroRep = fopen("data.txt","r");
	nodo *actual;
	actual = primero;
	printf("\t\t>>>>>[MOSTRAR REPARACIONES EN FECHA]<<<<<\n\n");
	printf("¿Que fecha desea buscar?");
	printf("\nDigite una fecha en formato dd/mm/aaaa : ");   fflush(stdin);   scanf("%s",fechaBuscar);
	printf("\n\n"); fflush(stdin);
	system("cls");
	printf("\t\t>>>>>[FECHA %s EN MEMORIA]<<<<<\n\n",fechaBuscar);
	while (actual!=NULL){
		if(strcmp(actual->dato.fecha,fechaBuscar)== 0){
			actual->indice = indice;
			printf("\n[%d] - [Dispositivo reparado: %d] - [Codigo de empleado: %d] - [Codigo de la empresa: %d] - [Fecha: %s]  - [Precio final: %.2f]\n",actual->indice,actual->dato.dispositivo,actual->dato.codigoEmpleado,actual->dato.codigoEmpresa,actual->dato.fecha,actual->dato.precioFinal);
			indice++; contador++;
		}
		actual = actual->sig;
	}
	printf("\n\t[Total de reparaciones en memoria con Fecha %s, fueron %d]\n\n",fechaBuscar,contador);
	if(ficheroRep == NULL){ printf("\n No se pudo abrir el archivo\n"); }
	else{
		contador = 0, indice = 1;
		datos datosAlmacenados;
		fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
		printf("\t\t>>>>>[FECHA %s ALMACENADA]<<<<<\n",fechaBuscar);
		while(!feof(ficheroRep)){
			if(strcmp(datosAlmacenados.fecha,fechaBuscar)== 0){
				printf("\n[%d] - [Dispositivo: %d] - [Codigo de Empleado: %d] - [Codigo de Empresa: %d] - [Fecha: %s]  - [Precio Final: %.2f]\n",indice,datosAlmacenados.dispositivo,datosAlmacenados.codigoEmpleado,datosAlmacenados.codigoEmpresa,datosAlmacenados.fecha,datosAlmacenados.precioFinal);
				indice++;
				contador++;
			}
			fread(&datosAlmacenados,sizeof(datos),1,ficheroRep);
		}
		printf("\n\t[Total de reparaciones almacenadas con Fecha %s, fueron %d]\n\n",fechaBuscar,contador);
		fclose(ficheroRep);
	}
	printf("\n\n"); system("PAUSE"); system("cls");
}
void almacenarReps(){
    fflush(stdin);
	nodo *actual;
	actual = primero;
	FILE *datosGuardados = fopen("data.txt","a");
	if(datosGuardados == NULL){
		printf("Archivo no creado, lo vamos a crear.\n"); system("pause"); system("cls"); return;
	}else{
	    while(actual!=NULL){
		fwrite(&actual->dato,sizeof(datos),1,datosGuardados);
		actual = actual->sig;
        }
	}
	fclose(datosGuardados);
	free(primero); free(ultimo);
	primero = NULL;
	ultimo = NULL;
	printf("Archivo Guardado con exito...\n");
	system("PAUSE"); system("cls");
}
void borrarReparacion(){
	nodo *actual;
	actual = primero;
	int datoEliminar;
	int contador = 1;
	if (actual == NULL){
		printf("No hay reparaciones en la memoria.\n\n");
		system("pause"); system("cls"); return;
	}
	printf("\t\t\t>>>>>[REPARACIONES ACTUALES]<<<<<\n\n");
	while(actual!=NULL){
		actual->indice = contador;
		printf("[%d] - [Dispositivo reparado: %d] - [Codigo de empleado: %d] - [Codigo de la empresa: %d] - [Fecha: %s] - [Precio final: %.2f]\n",actual->indice,actual->dato.dispositivo,actual->dato.codigoEmpleado,actual->dato.codigoEmpresa,actual->dato.fecha,actual->dato.precioFinal);
		printf("\n\n");
		contador++;
		actual = actual->sig;
	}
	printf("Ingrese la reparacion a eliminar: ");
	scanf("%d",&datoEliminar);

	actual = primero;

	if(actual->indice == datoEliminar){
		primero = primero->sig;
		free(actual);
	}else{
		while((actual->sig)->indice != datoEliminar){
		actual = actual->sig;
		}
		free(actual->sig);
		actual->sig = (actual->sig)->sig;
	}
	system("pause"); system("cls");
}


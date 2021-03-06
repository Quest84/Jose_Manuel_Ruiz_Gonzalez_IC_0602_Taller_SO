#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MENU 0
#define ALTA 1
#define BAJA 2
#define TODOS 3
#define ESPECIFICO 4
#define SOLO_ALTA 5
#define ABONAR 6
#define RETIRAR 7
#define BUSCAR_VACIO 8
#define MOSTRAR_LLENA 9
#define MOSTRAR_VACIA 10
#define MOSTRAR_PAISES 11
#define LONGITUDES 12
#define UPD_CLIENTE 13
#define SALIR 14

#define MENU_MOD 0
#define UPD_NOMBRE 1
#define UPD_SEXO 2
#define REGRESAR 3
 
void mostrarMenu();
void menuModificar();

int main(){
	int i = 0, n = 0, j = 0, m = 0, buscaID = 0, ID = 0;
	int flag0 = 0, flag1 = 0, flag2 = 0, resultado_pais = 0, resultado_cliente = 0;
	char nombreGenerico[20] = "Null";
	char sexoGenerico[2] = "G";
	float sueldoGenerico = 0.0;
	char nombreTemp[20];
	
	struct Pais {
		int id_pais;
		char nombre[20];
		int n_clientes;
	};

	struct Cliente{
		int id_cliente;
		char nombre[20];
		char sexo[2];
		float sueldo;
	};

	struct Sistema{
		struct Pais pais;
		struct Cliente cliente[100];
	};

	do{
		printf("Introduce el numero de paises: ");
		scanf("%i", &n);
		if (n < 1){
			printf("Error: No puedes tener menos de 1 pais!\n");
			getchar();
		}
		if (n > 194){
			printf("Error: No puedes tener mas de 194 paises!\n");
			getchar();
		}
	}while(n < 1 || n > 194);

	struct Sistema Sys[n];

	for (i = 0; i < n; i++){
		getchar();
		Sys[i].pais.id_pais = i;
		printf("Ingresa el nombre del pais [%i]: ", i);
		fgets(Sys[i].pais.nombre, sizeof(Sys[i].pais.nombre), stdin);
		
		char *ptr = strchr(Sys[i].pais.nombre,'\n');
		if(ptr){
			*ptr = '\0';
		}
		
		for (j = 0; j < 100; j++){
			*Sys[i].cliente[j].nombre = '\0';
		}

		do{		
			printf("\tIngresa el total de clientes del pais '%s': ", Sys[i].pais.nombre);
			m = 0;
			scanf("%i", &m);
			Sys[i].pais.n_clientes = m;
			if(m > 100){
				printf("Error: No puedes tener  mas de 100 clientes\n");
				getchar();
			}
			if (m <= 1){
				printf("Error: No puedes tener menos de 1 clientes!\n");
				getchar();
			}
		}while(m > 100 || m <= 1);
		
		getchar();
		for (j = 0; j < m; j++)	{
			Sys[i].cliente[j].id_cliente = j;			
			strcpy(Sys[i].cliente[j].nombre, nombreGenerico);
			strcpy(Sys[i].cliente[j].sexo, sexoGenerico);
			Sys[i].cliente[j].sueldo = sueldoGenerico;
		}
	}
	
	while(1){
		getchar();
		printf("\n");
		mostrarMenu();
		fflush(stdin);
		int opc = 18;
		scanf("%i", &opc);
		switch(opc){
			case MENU:
				system("clear");
			break;

			case ALTA:
				printf("--- Opcion Alta ---\n");	
				do{
					getchar();
					printf("\tIntroduce el nombre del pa??s: ");
					fgets(nombreTemp, sizeof(nombreTemp), stdin);
			                char *ptr = strchr(nombreTemp,'\n');
      				        if(ptr){
        	                		*ptr = '\0';
			                }	
	        	              			
					for(i = 0; i < n; i++){
						resultado_pais = strcmp(Sys[i].pais.nombre, nombreTemp);
						if(resultado_pais == 0){
							resultado_pais = i;
							flag0 = 1;
							//getchar();
							break;
						} 
						if (i >= (n-1) && resultado_pais != i) {
							printf("El nombre %s no se encuentra registrado\n", nombreTemp);
							printf("\t--> Intenta de nuevo(Ctrl+C para cerrar el programa)\n");	
							flag0 = 0;
						}
					}
				}while(flag0 == 0);		
				//printf("El pais que elegiste es %s\n", Sys[resultado_pais].pais.nombre);			
				
				/*for (i = 0; i < Sys[resultado_pais].pais.n_clientes; i++){
					printf("Cliente %i - Nombre: %s, Sexo: %s, Sueldo: %f\n", 
					i, Sys[resultado_pais].cliente[i].nombre, Sys[resultado_pais].cliente[i].sexo, Sys[resultado_pais].cliente[i].sueldo);
				}*/				
				
				do{
					for (i = 0; i < Sys[resultado_pais].pais.n_clientes; i++){
						resultado_cliente = strcmp(Sys[resultado_pais].cliente[i].nombre, "Null");
						if (resultado_cliente == 0){
							resultado_cliente = i;
							flag1 = 1;
							//getchar();
							break;
						}
						if (i >= (Sys[resultado_pais].pais.n_clientes - 1) && resultado_cliente != i){
							printf("No existe un indice vacio para el pa??s %s\n", Sys[resultado_pais].pais.nombre);
							printf("\t--> Intenta de nuevo(Ctrl+C para cerrar el programa)\n");
							flag1 = 1;
							flag0 = 0;
							break;
						} 				

					}	
				}while(flag1 == 0);
					
				do{
					if (flag0 == 0)
						break;
					printf("Introduce Nombre del cliente: ");
					fgets(Sys[resultado_pais].cliente[resultado_cliente].nombre, sizeof(Sys[resultado_pais].cliente[resultado_cliente].nombre), stdin);
					char *ptr = strchr(Sys[resultado_pais].cliente[resultado_cliente].nombre,'\n');
                                        if(ptr){
                                                *ptr = '\0';
                                        }

					printf("Introduce el Sexo del cliente: ");
                         		char sexoTemp[2];
					scanf("%c", sexoTemp);
					
					strcpy(Sys[resultado_pais].cliente[resultado_cliente].sexo, sexoTemp); 
					
					printf("Introduce el Sueldo del cliente: ");
					float sueldo;
					scanf("%f", &sueldo);
                                        Sys[resultado_pais].cliente[resultado_cliente].sueldo = sueldo;
					
					flag2 = 1;

				}while(flag2 == 0);
				flag0 = 0, flag1 = 0, flag2 = 0;
				getchar();
			break;

			case BAJA:
                                printf("--- Opcion Baja ---\n");
                                do{
                                        getchar();
                                        printf("\tIntroduce el nombre del pa??s: ");
                                        fgets(nombreTemp, sizeof(nombreTemp), stdin);
                                        char *ptr = strchr(nombreTemp,'\n');
                                        if(ptr){
                                                *ptr = '\0';
                                        }

                                        for(i = 0; i < n; i++){
                                                resultado_pais = strcmp(Sys[i].pais.nombre, nombreTemp);
                                                if(resultado_pais == 0){
                                                        resultado_pais = i;
                                                        flag0 = 1;
                                                        getchar();
                                                        break;
                                                }
                                                if (i >= (n-1) && resultado_pais != i) {
                                                        printf("El pais %s no se encuentra registrado\n", nombreTemp);
                                                        printf("\t--> Intenta de nuevo(Ctrl+C para cerrar el programa)\n");
                                                        flag0 = 0;
                                                }

                                        }

                                }while(flag0 == 0);
                         
                                do{
                                        for (i = 0; i < Sys[resultado_pais].pais.n_clientes; i++){
                                                resultado_cliente = strcmp(Sys[resultado_pais].cliente[i].nombre, "Null");
                                                if (resultado_cliente != 0){
                                                        resultado_cliente = i;
                                                        flag1 = 1;
                                                        getchar();
                                                        break;
                                                }
                                                if (i >= (Sys[resultado_pais].pais.n_clientes - 1) && resultado_cliente != i){
                                                        printf("--------------------------------------------------\n");
                                                        printf("\tToda la estructura esta vacia\n");             
                                                        printf("--------------------------------------------------\n");
                                                        printf("--> Intenta dar de alta primero(Ctrl+C para cerrar el programa)\n");             
							flag1 = 1;
                                                        flag0 = 0;
                                                        break;
                                                }

                                        }
                                }while(flag1 == 0);

                                do{
                                        if(flag0 == 0)
                                                break;
					
					printf("\tIntroduce el indice del cliente: ");
					int indiceTemp;
					scanf("%i", &indiceTemp);

					int resultadoIndice;
					resultadoIndice = strcmp(Sys[resultado_pais].cliente[indiceTemp].nombre, "Null");
					
					if(resultadoIndice != 0 && indiceTemp == Sys[resultado_pais].cliente[indiceTemp].id_cliente){
						printf("\tCliente %s dado de baja\n", Sys[resultado_pais].cliente[indiceTemp].nombre);
						strcpy(Sys[resultado_pais].cliente[indiceTemp].nombre, nombreGenerico);
						strcpy(Sys[resultado_pais].cliente[indiceTemp].sexo, sexoGenerico);
						Sys[resultado_pais].cliente[indiceTemp].sueldo = sueldoGenerico;
						flag2 = 1;
					} else {
						printf("\t-->No est?? en el rango o est?? vacio\n");
						flag2 = 0;
					}
					
                                }while(flag2 == 0);
                                flag0 = 0, flag1 = 0, flag2 = 0;
                                getchar();

			break;
			case TODOS:
			        printf("--- Opcion Mostrar Todo ---");
				for (i = 0; i < n; i++){
					printf("\n-----------------------------------------------------------------");
			                printf("\n\tDel pais [%i] %s:", Sys[i].pais.id_pais, Sys[i].pais.nombre);

			                //size_t m = sizeof(Sys[i].cliente)/sizeof(Sys[i].cliente[0]);
			                for(j = 0; j < 100; j++){
                        			if (*Sys[i].cliente[j].nombre != '\0'){
							printf("\nEl cliente [%i] es:\n", j);
			                                printf("\t--> Nombre: |%s| --> Sexo: |%s| --> Sueldo: |%f|\n", 
							Sys[i].cliente[j].nombre, Sys[i].cliente[j].sexo, Sys[i].cliente[j].sueldo);
                        			} else
			                                break;
				                }
			        }
		
			printf("\n-----------------------------------------------------------------\n");
			getchar();
			break;
			case ESPECIFICO:
                                printf("--- Opcion Mostrar Cliente Especifico ---\n");
                                do{
                                        getchar();
                                        printf("\tIntroduce el nombre del pa??s: ");
                                        fgets(nombreTemp, sizeof(nombreTemp), stdin);
                                        char *ptr = strchr(nombreTemp,'\n');
                                        if(ptr){
                                                *ptr = '\0';
                                        }

                                        for(i = 0; i < n; i++){
                                                resultado_pais = strcmp(Sys[i].pais.nombre, nombreTemp);
                                                if(resultado_pais == 0){
                                                        resultado_pais = i;
                                                        flag0 = 1;
                                                        break;
                                                }
                                                if (i >= (n-1) && resultado_pais != i) {
                                                        printf("\t\tEl pais %s no se encuentra registrado\n", nombreTemp);
                                                        printf("\t\t\t--> Intenta de nuevo(Ctrl+C para cerrar el programa)\n");
                                                        flag0 = 0;
                                                }

                                        }

                                }while(flag0 == 0);

                                do{
                                        for (i = 0; i < Sys[resultado_pais].pais.n_clientes; i++){
                                                resultado_cliente = strcmp(Sys[resultado_pais].cliente[i].nombre, "Null");
                                                if (resultado_cliente != 0){
                                                        resultado_cliente = i;
                                                        flag1 = 1;
                                                        break;
                                                }
                                                if (i >= (Sys[resultado_pais].pais.n_clientes - 1) && resultado_cliente != i){
                                                        printf("--------------------------------------------------\n");
                                                        printf("\tToda la estructura esta vacia\n");
                                                        printf("--------------------------------------------------\n");
                                                        printf("--> Intenta dar de alta primero(Ctrl+C para cerrar el programa)\n");
                                                        flag1 = 1;
                                                        flag0 = 0;
                                                        break;
                                                }

                                        }
                                }while(flag1 == 0);

                                do{
                                        if(flag0 == 0)
                                                break;

                                        printf("\tIntroduce el indice del cliente: ");
                                        int indiceTemp;
                                        scanf("%i", &indiceTemp);

                                        int resultadoIndice;
                                        resultadoIndice = strcmp(Sys[resultado_pais].cliente[indiceTemp].nombre, "Null");

                                        if(resultadoIndice != 0 && indiceTemp == Sys[resultado_pais].cliente[indiceTemp].id_cliente){
        					printf("\t--> Cliente [%i] --> Nombre: %s --> Sexo: [%s] --> Sueldo: [%f]", Sys[resultado_pais].cliente[indiceTemp].id_cliente,
						Sys[resultado_pais].cliente[indiceTemp].nombre, Sys[resultado_pais].cliente[indiceTemp].sexo, Sys[resultado_pais].cliente[indiceTemp].sueldo);                               
	                                        flag2 = 1;
                                        } else {
                                                printf("\t-->No est?? en el rango o est?? vacio\n");
                                                flag2 = 0;
                                        }

                                }while(flag2 == 0);
                                flag0 = 0, flag1 = 0, flag2 = 0;
                                getchar();

			break;
			case SOLO_ALTA:
                                printf("--- Opcion Mostrar solo Altas ---");
                                for (i = 0; i < n; i++){
					getchar();
                                        printf("\n-----------------------------------------------------------------");
                                        printf("\n\tDel pais [%i] %s:", Sys[i].pais.id_pais, Sys[i].pais.nombre);

                                        //size_t m = sizeof(Sys[i].cliente)/sizeof(Sys[i].cliente[0]);
                                        for(j = 0; j < 100; j++){
                                                resultado_cliente = strcmp(Sys[i].cliente[j].nombre, "Null");

                                                if (*Sys[i].cliente[j].nombre != '\0'){
                                                	resultado_cliente = strcmp(Sys[i].cliente[j].nombre, "Null");
							if(resultado_cliente != 0){
                                                        	printf("\nEl cliente [%i] es:\n", j);
	                                                        printf("\t--> Nombre: |%s| --> Sexo: |%s| --> Sueldo: |%f|\n",
        	                                                Sys[i].cliente[j].nombre, Sys[i].cliente[j].sexo, Sys[i].cliente[j].sueldo);
							}
                                                } else
                                                        break;
                                                }
                                }

                        printf("\n-----------------------------------------------------------------");
                        getchar();

			break;
			case ABONAR:
                                printf("--- Opcion Abonar ---\n");
                                do{
                                        getchar();
                                        printf("\tIntroduce el nombre del pa??s: ");
                                        fgets(nombreTemp, sizeof(nombreTemp), stdin);
                                        char *ptr = strchr(nombreTemp,'\n');
                                        if(ptr){
                                                *ptr = '\0';
                                        }

                                        for(i = 0; i < n; i++){
                                                resultado_pais = strcmp(Sys[i].pais.nombre, nombreTemp);
                                                if(resultado_pais == 0){
                                                        resultado_pais = i;
                                                        flag0 = 1;
                                                        break;
                                                }
                                                if (i >= (n-1) && resultado_pais != i) {
                                                        printf("El pais %s no se encuentra registrado\n", nombreTemp);
                                                        printf("\t--> Intenta de nuevo(Ctrl+C para cerrar el programa)\n");
                                                        flag0 = 0;
                                                }
                                        }

                                }while(flag0 == 0);              

                                do{
                                        for (i = 0; i < Sys[resultado_pais].pais.n_clientes; i++){
                                                resultado_cliente = strcmp(Sys[resultado_pais].cliente[i].nombre, "Null");
                                                if (resultado_cliente != 0){
                                                        resultado_cliente = i;
                                                        flag1 = 1;                                                   
                                                        break;
                                                }
                                                if (i >= (Sys[resultado_pais].pais.n_clientes - 1) && resultado_cliente != i){
                                                        printf("--------------------------------------------------\n");
                                                        printf("\tToda la estructura esta vacia\n");
                                                        printf("--------------------------------------------------\n");
                                                        printf("--> Intenta dar de alta primero(Ctrl+C para cerrar el programa)\n");
                                                        flag1 = 1;
                                                        flag0 = 0;
                                                        break;
                                                }

                                        }
                                }while(flag1 == 0);

                                do{
                                        if(flag0 == 0)
                                                break;

                                        printf("\tIntroduce el indice del cliente: ");
                                        int indiceTemp;
                                        scanf("%i", &indiceTemp);

                                        int resultadoIndice;
                                        resultadoIndice = strcmp(Sys[resultado_pais].cliente[indiceTemp].nombre, "Null");
					
					

                                        if(resultadoIndice != 0 && indiceTemp == Sys[resultado_pais].cliente[indiceTemp].id_cliente){
						float abono;
						printf("\tIntroduce cuanto ingresaras a la cuenta: ");
						scanf("%f", &abono);
						Sys[resultado_pais].cliente[indiceTemp].sueldo += abono;
                                                 flag2 = 1;
                                        } else {
                                                printf("\t-->No est?? en el rango o est?? vacio\n");
                                                flag2 = 0;
                                        }

                                }while(flag2 == 0);
                                flag0 = 0, flag1 = 0, flag2 = 0;
                                getchar();

			break;
			case RETIRAR:			
                                printf("--- Opcion Retirar ---\n");
                                do{
                                        getchar();
                                        printf("\tIntroduce el nombre del pa??s: ");
                                        fgets(nombreTemp, sizeof(nombreTemp), stdin);
                                        char *ptr = strchr(nombreTemp,'\n');
                                        if(ptr){
                                                *ptr = '\0';
                                        }

                                        for(i = 0; i < n; i++){
                                                resultado_pais = strcmp(Sys[i].pais.nombre, nombreTemp);
                                                if(resultado_pais == 0){
                                                        resultado_pais = i;
                                                        flag0 = 1;
                                                        break;
                                                }
                                                if (i >= (n-1) && resultado_pais != i) {
                                                        printf("El pais %s no se encuentra registrado\n", nombreTemp);
                                                        printf("\t--> Intenta de nuevo(Ctrl+C para cerrar el programa)\n");
                                                        flag0 = 0;
                                                }

                                        }

                                }while(flag0 == 0);
			
                                do{
                                        for (i = 0; i < Sys[resultado_pais].pais.n_clientes; i++){
                                                resultado_cliente = strcmp(Sys[resultado_pais].cliente[i].nombre, "Null");
                                                if (resultado_cliente != 0){
                                                        resultado_cliente = i;
                                                        flag1 = 1;                                                   
                                                        break;
                                                }
                                                if (i >= (Sys[resultado_pais].pais.n_clientes - 1) && resultado_cliente != i){
                                                        printf("--------------------------------------------------\n");
                                                        printf("\tToda la estructura esta vacia\n");
                                                        printf("--------------------------------------------------\n");
                                                        printf("--> Intenta dar de alta primero(Ctrl+C para cerrar el programa)\n");
                                                        flag1 = 1;
                                                        flag0 = 0;
                                                        break;
                                                }

                                        }
                                }while(flag1 == 0);

                                do{
                                        if(flag0 == 0)
                                                break;

                                        printf("\tIntroduce el indice del cliente: ");
                                        int indiceTemp;
                                        scanf("%i", &indiceTemp);

                                        int resultadoIndice;
                                        resultadoIndice = strcmp(Sys[resultado_pais].cliente[indiceTemp].nombre, "Null");

                                        if(resultadoIndice != 0 && indiceTemp == Sys[resultado_pais].cliente[indiceTemp].id_cliente){
                                                float retiro;
                                                printf("\tIntroduce cuanto retiraras de la cuenta: ");
                                                scanf("%f", &retiro);
						if (Sys[resultado_pais].cliente[indiceTemp].sueldo >= retiro){
							printf("Se ha deducido %f de la cuenta de %s", retiro, Sys[resultado_pais].cliente[indiceTemp].nombre);
	                                                Sys[resultado_pais].cliente[indiceTemp].sueldo -= retiro;
						} else {
							printf("\tImposible, tu saldo es insuficiente para retirar %f!", retiro);
						}
                                               flag2 = 1;
                                        } else {
                                                printf("\t--> No est?? en el rango o est?? vacio\n");
                                                flag2 = 0;
                                        }

                                }while(flag2 == 0);
                                flag0 = 0, flag1 = 0, flag2 = 0;
                                getchar();
			
			break;
			case BUSCAR_VACIO:
				getchar();
				ID = 0;	
                                printf("--- Opcion Buscar ID Vacio en toda la Estructura ---\n");
                                for (i = 0; i < n; i++){
                                        for (j = 0; j < 100; j++){
                                                if(*Sys[i].cliente[j].nombre != '\0'){ 
                                                        buscaID = strcmp(Sys[i].cliente[j].nombre, "Null");
                                                        if (buscaID == 0){
                                                                ID++;
                                                                printf("-----------------------------------------------\n");
                                                                printf("El pais [%i] %s tiene el cliente [%i] vacio\n", i, Sys[i].pais.nombre, Sys[i].cliente[j].id_cliente);
                                                                printf("-----------------------------------------------\n");
                                                                break;
                                                        }
                                                }
                                        }
                                }
                        if(ID == 0)
                                printf("\t--> No se encontro ningun indice vacio!\n");
			else
				printf("\t--> Hay %i estructuras vacias\n", ID);

                        int car = getchar();
                        while(car != '\n');
			break;

			case MOSTRAR_LLENA:
                                printf("\n--- Opcion buscar estructura llena ---\n");
                                getchar();
                                do{                                    
                                        getchar();
                                        printf("\tIntroduce el nombre del pa??s: ");
                                        fgets(nombreTemp, sizeof(nombreTemp), stdin);
                                        char *ptr = strchr(nombreTemp,'\n');
                                        if(ptr){
                                                *ptr = '\0';
                                        }
                                                                      
                                        for(i = 0; i < n; i++){
                                                resultado_pais = strcmp(Sys[i].pais.nombre, nombreTemp);
                                                if(resultado_pais == 0){
                                                        resultado_pais = i;
                                                        flag0 = 1;
                                                        //getchar();
                                                        break;
                                                }
                                                if (i >= (n-1) && resultado_pais != i) {
                                                        printf("El nombre %s no se encuentra registrado\n", nombreTemp);
                                                        printf("\t--> Intenta de nuevo(Ctrl+C para cerrar el programa)\n");
                                                        flag0 = 0;
                                                }

                                        }
                                        
                                }while(flag0 == 0);
                           
                                do{
                                        for (i = 0; i < Sys[resultado_pais].pais.n_clientes; i++){
                                                resultado_cliente = strcmp(Sys[resultado_pais].cliente[i].nombre, "Null");
                                                if (resultado_cliente == 0){
                                                        resultado_cliente = i;
                                                        flag1 = 1;
							flag0 = 1;
                                                        //getchar();
                                                        break;
                                                }
                                                if (i >= (Sys[resultado_pais].pais.n_clientes - 1) && resultado_cliente != i){
                                                        printf("--> La estructura esta llena para el pa??s %s\n", Sys[resultado_pais].pais.nombre);
                                                        printf("\t--> Intenta de nuevo(Ctrl+C para cerrar el programa)\n");
                                                        flag1 = 1;
                                                        flag0 = 0;
                                                        break;
                                                }

                                        }
                                }while(flag1 == 0);
                                if(flag0 != 0)
					printf("La estructura no esta llena para el pais %s\n", Sys[resultado_pais].pais.nombre);

			break;
			case MOSTRAR_VACIA:
                                printf("--- Opcion esta vacia toda la estructura ---\n");
                                do{
                                        getchar();
                                        printf("\tIntroduce el nombre del pa??s: ");
                                        fgets(nombreTemp, sizeof(nombreTemp), stdin);
                                        char *ptr = strchr(nombreTemp,'\n');
                                        if(ptr){
                                                *ptr = '\0';
                                        }

                                        for(i = 0; i < n; i++){
                                                resultado_pais = strcmp(Sys[i].pais.nombre, nombreTemp);
                                                if(resultado_pais == 0){
                                                        resultado_pais = i;
                                                        flag0 = 1;
                                                        break;
                                                }
                                                if (i >= (n-1) && resultado_pais != i) {
                                                        printf("El pais %s no se encuentra registrado\n", nombreTemp);
                                                        printf("\t--> Intenta de nuevo(Ctrl+C para cerrar el programa)\n");
                                                        flag0 = 0;
                                                }
                                        }

                                }while(flag0 == 0);
                                do{
                                        for (i = 0; i < Sys[resultado_pais].pais.n_clientes; i++){
                                                resultado_cliente = strcmp(Sys[resultado_pais].cliente[i].nombre, "Null");
                                                if (resultado_cliente != 0){
                                                        resultado_cliente = i;
                                                        flag1 = 1;
                                                        break;
                                                }
                                                if (i >= (Sys[resultado_pais].pais.n_clientes - 1) && resultado_cliente != i){
                                                        printf("--------------------------------------------------\n");
                                                        printf("\tToda la estructura esta vacia\n");
                                                        printf("--------------------------------------------------\n");
                                                        printf("--> Intenta dar de alta primero(Ctrl+C para cerrar el programa)\n");
                                                        flag1 = 1;
                                                        flag0 = 0;
                                                        break;
                                                }
                                        }
                                }while(flag1 == 0);
                                
                                if(flag0 == 0){
					printf("\nLa estructura no est?? vacia\n");
                                	break;
				}
				
			break;
			case MOSTRAR_PAISES:
				printf("--- Opci??n imprimir nombre de paises ---\n");
				printf("-------------------------------------------\n");
				printf("\tLos paises son: \n");
				for (i = 0; i < n; i++){
					printf("Pais [%i] %s\n", i, Sys[i].pais.nombre);
				}	
				printf("-------------------------------------------\n");
				getchar();
			break;

			case LONGITUDES:	
				printf("--- Opcion mostrar longitudes ---\n");
				printf("-----------------------------------\n");
				for (i = 0; i < n; i++){
					printf("--> Del pa??s %s, existen %i clientes\n", Sys[i].pais.nombre, Sys[i].pais.n_clientes);
				}
				printf("-----------------------------------\n");
				getchar();
			break;

			case UPD_CLIENTE:
                                printf("--- Opcion Actualizar Cliente Especifico ---\n");
                                do{
                                        getchar();
                                        printf("\tIntroduce el nombre del pa??s: ");
                                        fgets(nombreTemp, sizeof(nombreTemp), stdin);
                                        char *ptr = strchr(nombreTemp,'\n');
                                        if(ptr){
                                                *ptr = '\0';
                                        }

                                        for(i = 0; i < n; i++){
                                                resultado_pais = strcmp(Sys[i].pais.nombre, nombreTemp);
                                                if(resultado_pais == 0){ 
                                                        resultado_pais = i;
                                                        flag0 = 1;
                                                        break;
                                                }
                                                if (i >= (n-1) && resultado_pais != i) {
                                                        printf("El pais %s no se encuentra registrado\n", nombreTemp);
                                                        printf("\t--> Intenta de nuevo(Ctrl+C para cerrar el programa)\n");
                                                        flag0 = 0;
                                                }
                                        }

                                }while(flag0 == 0);

                                do{
                                        for (i = 0; i < Sys[resultado_pais].pais.n_clientes; i++){
                                                resultado_cliente = strcmp(Sys[resultado_pais].cliente[i].nombre, "Null");
                                                if (resultado_cliente != 0){
                                                        resultado_cliente = i;
                                                        flag1 = 1;
                                                        break;
                                                }
                                                if (i >= (Sys[resultado_pais].pais.n_clientes - 1) && resultado_cliente != i){
                                                        printf("--------------------------------------------------\n");
                                                        printf("\tToda la estructura esta vacia\n");
                                                        printf("--------------------------------------------------\n");
                                                        printf("--> Intenta dar de alta primero(Ctrl+C para cerrar el programa)\n");
                                                        flag1 = 1;
                                                        flag0 = 0;
                                                        break;
                                                }
                                        }
                                }while(flag1 == 0);

                                do{
                                        if(flag0 == 0)
                                                break;

                                        printf("\tIntroduce el indice del cliente: ");
                                        int indiceTemp;
                                        scanf("%i", &indiceTemp);

                                        int resultadoIndice;
                                        resultadoIndice = strcmp(Sys[resultado_pais].cliente[indiceTemp].nombre, "Null");

                                        if(resultadoIndice != 0 && indiceTemp == Sys[resultado_pais].cliente[indiceTemp].id_cliente){
                                                printf("\t--> Cliente [%i] --> Nombre: %s --> Sexo: [%s] --> Sueldo: [%f]", Sys[resultado_pais].cliente[indiceTemp].id_cliente,
                                                Sys[resultado_pais].cliente[indiceTemp].nombre, Sys[resultado_pais].cliente[indiceTemp].sexo, Sys[resultado_pais].cliente[indiceTemp].sueldo);    
						//while(getchar() != '\n');
						do{
							system("clear");
							fflush(stdin);
							menuModificar();
							int opc2 = 5;
							scanf("%i", &opc2);
							switch(opc2){
								case MENU_MOD:
									getchar();
									system("clear");
									
									flag0 = 0;
								break;

								case UPD_NOMBRE:
									getchar();
									printf("--- Opcion actualizar nombre ---\n");
									printf("Introduce nuevo nombre del cliente: ");
									fgets(Sys[resultado_pais].cliente[indiceTemp].nombre, sizeof(Sys[resultado_pais].cliente[indiceTemp].nombre), stdin);
				                                        char *ptr = strchr(Sys[resultado_pais].cliente[indiceTemp].nombre,'\n');
                        				                if(ptr){
				                                                *ptr = '\0';
                                				        }
									printf("\t--> Cliente [%i] --> Nombre: %s --> Sexo: [%s] --> Sueldo: [%f]", 
Sys[resultado_pais].cliente[indiceTemp].id_cliente,Sys[resultado_pais].cliente[indiceTemp].nombre, Sys[resultado_pais].cliente[indiceTemp].sexo, Sys[resultado_pais].cliente[indiceTemp].sueldo); 
								flag0 = 0;	
								while(getchar() != '\n');
								break;

								case UPD_SEXO:
									getchar();
									printf("--- Opci??n actualizar sexo ---\n");
									printf("Introduce el nuevo sexo: ");	
									char nuevoSexo[2];
									scanf("%c", nuevoSexo);	
									strcpy(Sys[resultado_pais].cliente[indiceTemp].sexo, nuevoSexo);

                                                                        printf("\t--> Cliente [%i] --> Nombre: %s --> Sexo: [%s] --> Sueldo: [%f]", 
Sys[resultado_pais].cliente[indiceTemp].id_cliente,Sys[resultado_pais].cliente[indiceTemp].nombre, Sys[resultado_pais].cliente[indiceTemp].sexo, Sys[resultado_pais].cliente[indiceTemp].sueldo);
								flag0 = 0;
								while(getchar() != '\n');
								break;

								case REGRESAR:
									flag0 = 1;
								break;

								default:
									flag0 = 0;
									printf("No se reconoci?? la entrada. Presiona Enter para continuar...");
									while(getchar() != '\n');
									break;
							}
							
							
						}while(flag0 == 0);
                                                flag2 = 1;
                                        } else {
                                                printf("\t--> No est?? en el rango o est?? vacio\n");
                                                flag2 = 0;
                                        }

                                }while(flag2 == 0);
                                flag0 = 0, flag1 = 0, flag2 = 0;
                                getchar();

			break;

			case SALIR:
				return 0;		
			break;

			default:
				printf("No se reconoci?? la entrada. Presiona Enter para continuar...");
				while(getchar() != '\n');
				system("clear");
			break;
		}
	}

	return 0;
}

void mostrarMenu(){
	printf("===== Menu =====\n");
	printf("0. Mostrar Menu*\n");
	printf("1. Dar de Alta Cliente*\n");
	printf("2. Dar de Baja Cliente*\n");
	printf("3. Mostrar todos los clientes*\n");
	printf("4. Mostrar cliente en espec??fico*\n");
	printf("5. Mostrar solo los clientes dados de alta\n");
	printf("6. Abonar saldo a cliente*\n");
	printf("7. Retirar saldo de Cliente*\n");
	printf("8. Buscar indice vaci?? en toda la estructura*\n");
	printf("9. Mostrar si esta llena la estructura*\n");
	printf("10. Mostrar si est?? toda vac??a la estructura*\n");
	printf("11. Mostrar nombre de pa??ses*\n");
	printf("12. Mostrar logitudes*\n");
	printf("13. Actualizar datos de cliente en espec??fico*\n");
	printf("14. Salir*\n");
	printf("------------------\n");
	printf("Elije una opci??n: ");
}

void menuModificar(){
        printf("\n===== Menu Modificar =====\n");
        printf("0. Mostrar Menu*\n");
        printf("1. Actualizar Nombre*\n");
        printf("2. Actualizar Sexo\n");
	printf("3. Regresar al menu principal\n");
        printf("------------------\n");
        printf("Elije una opci??n: ");
}


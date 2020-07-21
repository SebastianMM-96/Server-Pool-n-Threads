#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
 #include <time.h>

#define BUFFERSIZE 5


typedef struct datastruct
{
    int n1, n2; //Numeros de la operacion
    char op; // Caracter de la operacion a realizar.

}datastruct;

/*Tamaño del buffer de elementos de operaciones que se le 
enviaran al servidor. */
datastruct buffersize[BUFFERSIZE];

sem_t mutex;

char operacion;
int cont = 0;

void escribe(void *ptr);
void lee (void *ptr);

//pthread_mutex_t c1, c2;

int main(){

	int i, j, n;
	int n1, n2;
    int I[n];
	char oper;
    n = 10;
	pthread_t hCliente[n], hServidor; /* identificador del hilo */
	sem_init(&mutex,0,1);     /* se crea e inicializa el semáforo */
 	
		
 	/*Se crea el hilo Servidor que leera en el buffer y resolvera las operaciones*/
    i=n;
 	pthread_create(&hServidor, NULL, (void *) &lee, (void* )&i );

 	//printf("Ingrese el numero de hilos clientes que desea:");
 	//scanf("%d", n);
 	
 	//buffersize = (datastruct)* malloc (sizeof(datastruct)*n);

 	/*Creamos n hilos clientes*/
 	for (i = 0; i < n ; i++)
 	{
        I[i] = i;
 		pthread_create(hCliente + i, NULL, (void *) &escribe, (void* )&I[i] );
 	}

    /* El hilo padre espera a que terminen los hilos que creo */
    pthread_join(hServidor, NULL);
    for (j = 0; j < n ; j++)
    {
        /* code */
        pthread_join(hCliente[j], NULL);
    }


   	/* Se destruye el semaforo */
    sem_close(&mutex);

}

/*funcion que recibe la operacion y la escribe en el buffer. */
void escribe(void *ptr){
	
	int iId = *(int *)ptr;
    int n1, n2;
    unsigned int z;
    char op;
    
	//sem_wait(&mutex);
    /*Abre semaforo*/
	for (int i = 0; i < 10 ; i++)
    {
        /*HACER OPERACIONES RANDOM*/
        //; //
        //srand(time(NULL));
        printf ("Soy e hilo %d\n", iId);
        sleep (iId%3);
        n1 = rand() % 200; //Numeros entre 0 - 9
        n2 = rand() % 100;
        op = rand() % 4 + 1; //{+, -, *, /}

        if (op == 1)
        {
            op = '+';
        }else if (op == 2)
        {
            op = '-';
        }else if (op == 3)
        {
            op = '*';
        }else (op == 4);
        {
            op = '/';
        }

        while(1){
            z = rand () % (100 * (iId+1));
            //printf ("%u\n",z);
            usleep (z); //microsegundos
            sem_wait(&mutex);  
            if (cont < BUFFERSIZE )
            {   
                
                buffersize[cont].n1 = n1 ;
                buffersize[cont].n2 = n2 ;
                buffersize[cont].op = op ;
                cont++;

            }
            sem_post(&mutex);
        }
        
    }
	//sem_post(&mutex);

	
}


/*funcion que lee la operacion y la escribe en el buffer. */
void lee(void *ptr){
    int a, b;
    char op;
    
    //while(1){ 
        //sem_wait(&mutex);   
        while(1){
            op = 0;
            sem_wait(&mutex);
    	   if (cont != 0)
           {
 cont--;
               a = buffersize[cont].n1;
               b = buffersize[cont].n2;
               op = buffersize[cont].op;
               /*Realizar la operaciones*/
               
            }
            sem_post(&mutex);
                switch(op)
                {
                    case '+':
                        printf("%d + %d = %d\n",a, b, a + b);
                        break;

                    case '-':
                        printf("%d - %d = %d\n",a, b, a - b);
                        break;

                    case '*':
                        printf("%d * %d = %d\n",a, b, a * b);
                        break;

                    case '/':
                        printf("%d / %d = %f\n",a, b, (double)(a*1.0 / b));
                        break;

                    // operator doesn't match any case constant (+, -, *, /)
                    //default:
                      //  printf("Error! operator is not correct");
                }
        
           
           
        } //revisa en el buffer
        //sem_post(&mutex);
   //} //checa continuamente las peticiones
}
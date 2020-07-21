# Servidor con un pool de n hilos

Los procesos clientes depositan
sus solicitudes de servicio en un buffer (arreglo) y un hilo del servidor las toma de ahí y las
atiende. Para esto, el resultado del servicio sólo se despliega en pantalla. Se puede
utilizar como ejemplo de servicio una calculadora en donde cada solicitud de servicio
consta del operador y sus operandos.

Lo que buscamos es hacer lo siguiente:


#ifndef _ARCHIVOS
#define _ARCHIVOS

int inAbrirArchivo(char *szNombreArchivo, char *szModo);
void voCerrarArchivo();
int inLeerArchivo(char *szNombreArchivo);
int inLeerArchivoPorLinea(char *szNombreArchivo,char *szTextoALeer);
int inEscribirArchivo(char *szNombreArchivo,char *szTextoAEscribir);
int inEscribirArchivoPorLinea(char *szNombreArchivo,char *szTextoAEscribir);
int inLeerArchivoBusqueda(char *szNombreArchivo, char *szPalabraClave, int *contador);


#endif

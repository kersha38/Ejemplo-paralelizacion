#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <time.h>

//structura para nuevo archivo binario codigo y formula reducida
typedef struct{
    char nombre[13];
    int fReducida[17];
    int comTotal;
}datosReducidos;

//funcion calcula coeficiente
float calcCoe(int Na, int Nb, int Nc);

//funcion calcula formula
int *calcFormula(char *formula);

//funcion calcula similares
int calSimi(int *formA,int *formB);

//funcion calcula total
int calTotalComp(int *t);


int main () {
//abro el archivo
   FILE *fp,*faux;
   char c;//recorre archivo tabulao
   int b=0,*punte;
   datosReducidos datos;
   char formula[150];
   static char nom[]="nombform";

    faux=fopen("auxiliar.dat","wb");

   if(faux==NULL)
    printf("error");

   //fp = fopen("texto.txt","r");
   fp = fopen("real.txt","r");




   while(1) {
     c = fgetc(fp);
     if(c=='\t'){
            b=0;
        //guardo el nombre
        do{
            nom[b]=c;
            b++;
            c = fgetc(fp);
        }while(c!='\t');
       nom[b]='\0';


        //ignoro segundo param
         do{
            c = fgetc(fp);

        }while(c!='\t');

        //tomo la formula
        b=0;
        do{
            c = fgetc(fp);
            formula[b]=c;
            b++;

        }while(c!='\n');
        formula[b]='\0';

        punte=calcFormula(formula);

        b=0;
        while(b<17){
        datos.fReducida[b]=*punte;
        punte++;
        b++;
        }

         strcpy(datos.nombre,nom);
        datos.comTotal=calTotalComp(datos.fReducida);
        fwrite(&datos,sizeof(datosReducidos),1,faux);
     }

      if( feof(fp) ) {
         break ;
      }

   }

   fclose(fp);
   fclose(faux);

   //lectura archivo binario y calculo
   datosReducidos r[12422];

    FILE *fresult;
   faux=fopen("auxiliar.dat","rb");
   fresult=fopen("resultado.txt","w");

  /*//otra forma de leer
   while(fread(r,sizeof(datosReducidos),1,faux)!=NULL){

    printf("\nGuardado\nnombre:%s  primero:%d",r->nombre,r->fReducida[0]);
   }
    */
    int con=0,con2=0;
    float coefi;
    fread(r,sizeof(datosReducidos),12422,faux);
/*
    while(con<12422){
            printf("\nGuardado\nnombre:%s  con:%d",r[con].nombre,con);
            con++;
    }
*/
    //OPERACIONES


    clock_t start=clock();
    omp_set_num_threads(omp_get_max_threads());

#pragma omp parallel for ordered
    for(con=0;con<12422;con++){
            for(con2=0;con2<con;con2++){
                //CALCULO
                //coefi=calcCoe(calTotalComp(r[con].fReducida),calTotalComp(r[con2].fReducida),calSimi(r[con].fReducida,r[con2].fReducida));
                coefi=calcCoe(r[con2].comTotal,r[con].comTotal,calSimi(r[con].fReducida,r[con2].fReducida));
                //printf("\nel coeficiente es: %f",coefi);
                //GUARDO
                #pragma omp ordered
                fprintf(fresult, "%s%s\t%.2f\n",r[con2].nombre,r[con].nombre,coefi);
            }
    }
    fclose(fresult);
    fclose(faux);

    printf("tiempo ejecución: %f",(double)(clock()-start)/CLOCKS_PER_SEC);

   return(0);
}

float calcCoe(int Na, int Nb, int Nc){

	return (float)(Nc)/(float)(Na+Nb-Nc);
}

int calTotalComp( int *t){
	int total=0;
	while(*t!=-1){
        total+= *t;
        t++;
    }
	return total;
}

int calSimi(int *formA,int *formB){
    int Total=0;
    while(*formA!=-1){
        if(*formA<*formB)
            Total+=*formA;
        else
            Total+=*formB;
        formA++;
        formB++;
    }
    return Total;
}

int *calcFormula(char *formula){
	static int formResu[17];
	int a=0;
	for(;a<17;a++){
        formResu[a]=0;
	}
	while(*formula!='\0'){
		if(*formula==99)
			formResu[0]++;
		else if(*formula==67)
			formResu[1]++;
        else if(*formula==78)
			formResu[2]++;
		else if(*formula==79)
			formResu[3]++;
		else if(*formula==64)
			formResu[4]=1;
        else if(*formula==66)
			formResu[5]++;
        else if(*formula==70)
			formResu[6]++;
		else if(*formula==72)
			formResu[7]++;
        else if(*formula==73)
			formResu[8]++;
		else if(*formula==80)
			formResu[9]++;
        else if(*formula==83)
			formResu[10]++;
		else if(*formula==108)
			formResu[11]++;
        else if(*formula==110)
			formResu[12]++;
		else if(*formula==111)
			formResu[13]++;
        else if(*formula==114)
			formResu[14]++;
		else if(*formula==115)
			formResu[15]++;


        formula++;
	}

	formResu[16]=-1;


	return formResu;
}

//schedule(static,2)

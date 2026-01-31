#include<stdio.h>

#define MAX_PELAJAR 100
#define PANJANG_NAMA 50

#include<stdio.h>

#define MAX_PELAJAR 100
#define PANJANG_NAMA 50

typedef struct  {
   int id;
   char nama[PANJANG_NAMA] ;
   float nilai;
}Siswa;


void tambah_siswa(Siswa siswa[], int*hitung, int id, const char*nama, float nilai){
  if(*hitung >= MAX_PELAJAR){
    fprintf(stderr, "Error: Kapasistas maks dari pelajar sudah sampai \n");
  }
  siswa[*hitung].id = id;
  strncpy(siswa[*hitung].nama, nama, PANJANG_NAMA -1);

}


int main(){



  return 0 ;
}


int main(){



  return 0 ;
}
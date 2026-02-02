/**
 * @file array2.c
 * @brief Program manajemen data siswa menggunakan array
 * 
 * Program ini mendemonstrasikan penggunaan array struktur untuk menyimpan
 * dan mengelola data siswa. Program ini menyediakan fungsi-fungsi dasar
 * untuk menambah, mencari, menampilkan, dan menghitung statistik data siswa.
 */

#include <stdio.h>
#include <string.h>

/**
 * @def MAX_PELAJAR
 * @brief Maksimum jumlah siswa yang dapat disimpan dalam array
 */
#define MAX_PELAJAR 100

/**
 * @def PANJANG_NAMA
 * @brief Panjang maksimum untuk nama siswa (termasuk null terminator)
 */
#define PANJANG_NAMA 50

/**
 * @struct Siswa
 * @brief Struktur data yang merepresentasikan seorang siswa
 * 
 * Struktur ini digunakan untuk menyimpan informasi dasar seorang siswa
 * yang terdiri dari ID unik, nama, dan nilai.
 */
typedef struct {
  int id;                     /**< ID unik untuk identifikasi siswa */
  char nama[PANJANG_NAMA];    /**< Nama siswa dengan batas panjang PANJANG_NAMA */
  float nilai;                /**< Nilai siswa dalam format desimal */
} Siswa;

/**
 * @brief Menambahkan data siswa baru ke dalam array
 * 
 * Fungsi ini menambahkan data siswa baru ke posisi terakhir dalam array.
 * Fungsi akan memeriksa terlebih dahulu apakah array masih memiliki kapasitas.
 * 
 * @param siswa Array yang berisi data siswa
 * @param hitung Pointer ke variabel yang menyimpan jumlah siswa saat ini
 * @param id ID unik siswa yang akan ditambahkan
 * @param nama Nama siswa yang akan ditambahkan
 * @param nilai Nilai siswa yang akan ditambahkan
 * 
 * @note Nama siswa akan dipotong jika panjangnya melebihi PANJANG_NAMA-1 karakter
 * @note Jika array penuh, fungsi akan menampilkan pesan error dan mengembalikan kontrol
 */
void tambah_siswa(Siswa siswa[], int *hitung, int id, const char *nama,
                  float nilai) {
  // Cek apakah array sudah mencapai kapasitas maksimum
  if (*hitung >= MAX_PELAJAR) {
    fprintf(stderr, "error: kapasitas maks dari pelajar sudah sampai\n");
    return;
  }

  // Isi data siswa baru pada posisi saat ini
  siswa[*hitung].id = id;
  strncpy(siswa[*hitung].nama, nama, PANJANG_NAMA - 1);
  siswa[*hitung].nama[PANJANG_NAMA - 1] = '\0';  // Pastikan string diakhiri null
  siswa[*hitung].nilai = nilai;
  
  (*hitung)++;  // Tingkatkan jumlah siswa
  
  printf("siswa `%s` sudah ditambahkan\n", nama);
}

/**
 * @brief Mencari data siswa berdasarkan ID
 * 
 * Fungsi ini melakukan pencarian linear dalam array untuk menemukan
 * siswa dengan ID yang sesuai. Pencarian dimulai dari indeks 0 hingga
 * indeks terakhir yang berisi data.
 * 
 * @param siswa Array yang berisi data siswa (input konstan)
 * @param hitung Jumlah siswa yang tersimpan dalam array
 * @param id ID siswa yang ingin dicari
 * 
 * @return Indeks array tempat siswa ditemukan, atau -1 jika tidak ditemukan
 */
int cari_data_siswa(const Siswa siswa[], int hitung, int id) {
  // Lakukan pencarian linear
  for (int i = 0; i < hitung; i++) {
    if (siswa[i].id == id) {
      return i;  // Kembalikan indeks jika ditemukan
    }
  }
  return -1;  // Kembalikan -1 jika tidak ditemukan
}

/**
 * @brief Menampilkan semua data siswa ke layar
 * 
 * Fungsi ini menampilkan informasi semua siswa dalam format tabel sederhana.
 * Jika tidak ada data siswa, fungsi akan menampilkan pesan khusus.
 * 
 * @param siswa Array yang berisi data siswa (input konstan)
 * @param hitung Jumlah siswa yang tersimpan dalam array
 * 
 * @note Format output: "id: [id] || nama: [nama] || nilai: [nilai]"
 */
void tampilin_data_siswa(const Siswa siswa[], int hitung) {
  // Cek apakah ada data yang akan ditampilkan
  if (hitung == 0) {
    printf("tidak ada data siswa yang tersedia\n");
    return;
  }
  
  printf("daftar siswa tersedia:\n");
  
  // Iterasi melalui semua siswa dan tampilkan informasi mereka
  for (int i = 0; i < hitung; i++) {
    printf("id: %d || nama: %s || nilai: %.2f\n", 
           siswa[i].id, 
           siswa[i].nama,
           siswa[i].nilai);
  }
}

/**
 * @brief Menghitung nilai rata-rata dari semua siswa
 * 
 * Fungsi ini menghitung rata-rata nilai semua siswa yang tersimpan dalam array.
 * Jika tidak ada siswa, fungsi akan mengembalikan 0.0.
 * 
 * @param siswa Array yang berisi data siswa (input konstan)
 * @param hitung Jumlah siswa yang tersimpan dalam array
 * 
 * @return Rata-rata nilai semua siswa, atau 0.0 jika tidak ada siswa
 * 
 * @note Menggunakan konversi eksplisit hitung ke float untuk pembagian
 */
float hitung_rata_nilai(const Siswa siswa[], int hitung) {
  // Handle kasus array kosong
  if (hitung == 0) {
    return 0.0f;
  }

  float hasil = 0.0f;  // Akumulator untuk total nilai
  
  // Jumlahkan semua nilai
  for (int i = 0; i < hitung; i++) {
    hasil += siswa[i].nilai;
  }
  
  // Kembalikan rata-rata dengan konversi eksplisit
  return hasil / (float)hitung;
}

/**
 * @brief Fungsi utama program
 * 
 * Fungsi utama yang menjalankan program manajemen data siswa.
 * Program ini mendemonstrasikan penggunaan semua fungsi yang telah didefinisikan.
 * 
 * Alur program:
 * 1. Mendeklarasikan array siswa dan variabel penghitung
 * 2. Menambahkan beberapa data siswa contoh
 * 3. Menghitung dan menampilkan rata-rata nilai
 * 
 * @return 0 menandakan program berjalan dengan sukses
 * 
 * @note Bagian yang dikomentari dapat di-uncomment untuk fungsionalitas tambahan
 */
int main() {
  /**
   * Kode berikut adalah contoh penggunaan array dan pointer yang telah dikomentari
   * untuk referensi, namun tidak dieksekusi dalam program ini
   *
   * int array[5] = {10, 20, 30, 40, 50};  // -> {1, 2, 0, 0, 0}
   * int data[] = {1, 2, 3, 4};
   * int angka[10];
   * float nilai[5] = {0.0};
   * char nama[30] = "arfy";
   * int *pointer = array;
   * pointer = &array[0]
   * printf("array: %p\n", (void*) array);
   * printf("&array: %p\n", (void*)&array);
   * printf("sizeof dari si array: %zu\n", sizeof(array));
   * printf("sizeof dari pointer: %zu\n", sizeof(pointer));
   */

  // Array untuk menyimpan data siswa dengan kapasitas MAX_PELAJAR
  Siswa siswa[MAX_PELAJAR];
  
  // Variabel untuk melacak jumlah siswa yang telah ditambahkan
  int jumlah_siswa = 0;

  // Menambahkan data siswa contoh ke dalam array
  tambah_siswa(siswa, &jumlah_siswa, 101, "arfy", 70.2f);
  tambah_siswa(siswa, &jumlah_siswa, 102, "james", 80.52f);
  tambah_siswa(siswa, &jumlah_siswa, 103, "anne", 90.22f);

  // Fungsi untuk menampilkan data (dikomentari saat ini)
  // tampilin_data_siswa(siswa, jumlah_siswa);
  
  // Contoh penggunaan fungsi pencarian (dikomentari saat ini)
  // int indeks = cari_data_siswa(siswa, jumlah_siswa, 102);
  // if (indeks != -1) {
  //   printf("data ditemukan\n");
  //   printf("data: %s (nilai: %.2f)\n", siswa[indeks].nama, siswa[indeks].nilai);
  // } else {
  //   printf("data tidak ditemukan\n");
  // }

  // Menghitung dan menampilkan rata-rata nilai semua siswa
  float rata_rata = hitung_rata_nilai(siswa, jumlah_siswa);
  printf("rata-rata nilai adalah: %.2f\n", rata_rata);

  return 0;  // Program selesai dengan sukses
}
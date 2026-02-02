#include<stdio.h>
#include<string.h>  // Untuk fungsi strncpy
#include<ctype.h>   // Untuk fungsi tolower

#define MAX_PELAJAR 100    // Maksimum jumlah siswa yang dapat disimpan
#define PANJANG_NAMA 50    // Panjang maksimum nama siswa

/**
 * @struct Siswa
 * @brief Struktur data untuk merepresentasikan seorang siswa
 * 
 * Struktur ini menyimpan informasi dasar seorang siswa yang terdiri dari:
 * - ID unik
 * - Nama
 * - Nilai
 */
typedef struct  {
   int id;                     ///< ID unik siswa
   char nama[PANJANG_NAMA];    ///< Nama siswa (maksimal PANJANG_NAMA-1 karakter)
   float nilai;                ///< Nilai siswa (dalam format desimal)
} Siswa;

/**
 * @brief Membersihkan buffer input stdin
 * 
 * Fungsi ini membersihkan buffer input untuk mencegah masalah input yang tersisa.
 */
void bersihkan_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Validasi ID siswa
 * 
 * Fungsi ini memeriksa apakah ID sudah digunakan oleh siswa lain.
 * 
 * @param siswa Array yang berisi data siswa
 * @param hitung Jumlah siswa yang tersimpan dalam array
 * @param id ID yang akan divalidasi
 * 
 * @return 1 jika ID valid (tidak ada duplikat), 0 jika ID sudah digunakan
 */
int validasi_id(const Siswa siswa[], int hitung, int id) {
    for (int i = 0; i < hitung; i++) {
        if (siswa[i].id == id) {
            return 0;  // ID sudah digunakan
        }
    }
    return 1;  // ID valid
}

/**
 * @brief Validasi nama siswa
 * 
 * Fungsi ini memeriksa apakah nama valid (tidak kosong dan hanya berisi karakter yang diperbolehkan).
 * 
 * @param nama Nama yang akan divalidasi
 * 
 * @return 1 jika nama valid, 0 jika tidak valid
 */
int validasi_nama(const char* nama) {
    if (nama == NULL || strlen(nama) == 0) {
        return 0;  // Nama kosong
    }
    
    // Cek apakah nama hanya berisi huruf, spasi, atau tanda hubung
    for (int i = 0; nama[i] != '\0'; i++) {
        if (!isalpha(nama[i]) && nama[i] != ' ' && nama[i] != '-') {
            return 0;  // Karakter tidak valid
        }
    }
    
    return 1;  // Nama valid
}

/**
 * @brief Validasi nilai siswa
 * 
 * Fungsi ini memeriksa apakah nilai berada dalam rentang yang valid (0-100).
 * 
 * @param nilai Nilai yang akan divalidasi
 * 
 * @return 1 jika nilai valid, 0 jika tidak valid
 */
int validasi_nilai(float nilai) {
    return (nilai >= 0.0f && nilai <= 100.0f);
}

/**
 * @brief Menambahkan siswa baru ke dalam array siswa
 * 
 * Fungsi ini menambahkan data siswa baru ke dalam array. Jika kapasitas sudah penuh,
 * fungsi akan menampilkan pesan error dan tidak menambahkan data.
 * 
 * @param siswa Array yang berisi data siswa
 * @param hitung Pointer ke variabel yang menyimpan jumlah siswa saat ini
 * @param id ID unik siswa yang akan ditambahkan
 * @param nama Nama siswa yang akan ditambahkan
 * @param nilai Nilai siswa yang akan ditambahkan
 * 
 * @return 1 jika berhasil ditambahkan, 0 jika gagal
 * 
 * @note Nama akan dipotong jika melebihi PANJANG_NAMA-1 karakter
 */
int tambah_siswa(Siswa siswa[], int* hitung, int id, const char* nama, float nilai) {
    // Cek apakah array sudah penuh
    if(*hitung >= MAX_PELAJAR) {
        fprintf(stderr, "Error: Kapasitas maksimum dari pelajar sudah tercapai\n");
        return 0;
    }
    
    // Validasi input
    if (!validasi_id(siswa, *hitung, id)) {
        fprintf(stderr, "Error: ID %d sudah digunakan\n", id);
        return 0;
    }
    
    if (!validasi_nama(nama)) {
        fprintf(stderr, "Error: Nama tidak valid\n");
        return 0;
    }
    
    if (!validasi_nilai(nilai)) {
        fprintf(stderr, "Error: Nilai harus antara 0.0 dan 100.0\n");
        return 0;
    }
    
    // Isi data siswa baru
    siswa[*hitung].id = id;
    strncpy(siswa[*hitung].nama, nama, PANJANG_NAMA - 1);  // Salin nama dengan batasan panjang
    siswa[*hitung].nama[PANJANG_NAMA - 1] = '\0';          // Pastikan string diakhiri dengan null
    siswa[*hitung].nilai = nilai;
    
    (*hitung)++;  // Tingkatkan jumlah siswa
    
    printf("Siswa '%s' berhasil ditambahkan\n", nama);
    return 1;
}

/**
 * @brief Mencari data siswa berdasarkan ID
 * 
 * Fungsi ini melakukan pencarian linear untuk menemukan siswa dengan ID tertentu.
 * 
 * @param siswa Array yang berisi data siswa
 * @param hitung Jumlah siswa yang tersimpan dalam array
 * @param id ID siswa yang dicari
 * 
 * @return Indeks siswa dalam array jika ditemukan, -1 jika tidak ditemukan
 */
int cari_data_siswa(const Siswa siswa[], int hitung, int id) {
    // Lakukan pencarian linear
    for (int i = 0 ; i < hitung; i++) {
        if (siswa[i].id == id) {
            return i;  // Kembalikan indeks jika ditemukan
        }
    }
    return -1;  // Kembalikan -1 jika tidak ditemukan
}

/**
 * @brief Mencari data siswa berdasarkan nama (case-insensitive)
 * 
 * Fungsi ini melakukan pencarian siswa berdasarkan nama dengan pendekatan case-insensitive.
 * 
 * @param siswa Array yang berisi data siswa
 * @param hitung Jumlah siswa yang tersimpan dalam array
 * @param nama Nama siswa yang dicari
 * 
 * @return Indeks siswa dalam array jika ditemukan, -1 jika tidak ditemukan
 */
int cari_siswa_by_nama(const Siswa siswa[], int hitung, const char* nama) {
    if (nama == NULL || strlen(nama) == 0) {
        return -1;
    }
    
    for (int i = 0; i < hitung; i++) {
        // Bandingkan tanpa memperhatikan huruf besar/kecil
        if (strcasecmp(siswa[i].nama, nama) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Menampilkan semua data siswa ke layar
 * 
 * Fungsi ini menampilkan informasi semua siswa yang tersimpan dalam format tabel.
 * Jika tidak ada siswa, fungsi akan menampilkan pesan khusus.
 * 
 * @param siswa Array yang berisi data siswa
 * @param hitung Jumlah siswa yang tersimpan dalam array
 */
void tampilan_data_siswa(const Siswa siswa[], int hitung) {
    // Cek apakah ada data siswa
    if(hitung == 0) {
        printf("Tidak ada data siswa yang tersedia\n");
        return;
    } 
    
    // Tampilkan header
    printf("\n=== DAFTAR SISWA ===\n");
    printf("Jumlah siswa: %d\n\n", hitung);
    printf("No.  ID     Nama                     Nilai    Keterangan\n");
    printf("--------------------------------------------------------\n");
    
    // Tampilkan data setiap siswa
    for (int i = 0 ; i < hitung ; i++) {
        const char* keterangan;
        if (siswa[i].nilai >= 85.0f) {
            keterangan = "Sangat Baik";
        } else if (siswa[i].nilai >= 70.0f) {
            keterangan = "Baik";
        } else if (siswa[i].nilai >= 60.0f) {
            keterangan = "Cukup";
        } else {
            keterangan = "Perlu Perbaikan";
        }
        
        printf("%-4d %-6d %-25s %-8.2f %s\n", 
               i+1, siswa[i].id, siswa[i].nama, siswa[i].nilai, keterangan);
    }
    printf("--------------------------------------------------------\n");
}

/**
 * @brief Mengurutkan siswa berdasarkan nilai (descending)
 * 
 * Fungsi ini mengurutkan array siswa berdasarkan nilai dari tertinggi ke terendah.
 * Menggunakan algoritma bubble sort.
 * 
 * @param siswa Array yang berisi data siswa
 * @param hitung Jumlah siswa yang tersimpan dalam array
 */
void urutkan_siswa_by_nilai(Siswa siswa[], int hitung) {
    if (hitung <= 1) return;
    
    for (int i = 0; i < hitung - 1; i++) {
        for (int j = 0; j < hitung - i - 1; j++) {
            if (siswa[j].nilai < siswa[j + 1].nilai) {
                // Tukar posisi
                Siswa temp = siswa[j];
                siswa[j] = siswa[j + 1];
                siswa[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief Menghitung rata-rata nilai semua siswa
 * 
 * Fungsi ini menghitung nilai rata-rata dari semua siswa yang tersimpan.
 * 
 * @param siswa Array yang berisi data siswa
 * @param hitung Jumlah siswa yang tersimpan dalam array
 * 
 * @return Rata-rata nilai semua siswa. Mengembalikan 0.0 jika tidak ada siswa
 */
float hitung_rata_rata_nilai(const Siswa siswa[], int hitung) {
    // Cek apakah ada data siswa
    if (hitung == 0) {
        return 0.0f;
    }

    float hasil = 0.0f;  // Variabel untuk menyimpan total nilai

    // Jumlahkan semua nilai
    for (int i = 0; i < hitung; i++) {
        hasil += siswa[i].nilai;
    }

    return hasil / hitung;  // Kembalikan rata-rata
}

/**
 * @brief Menampilkan statistik nilai siswa
 * 
 * Fungsi ini menampilkan statistik lengkap dari nilai siswa:
 * - Nilai tertinggi
 * - Nilai terendah
 * - Rata-rata
 * - Jumlah siswa dalam setiap kategori
 * 
 * @param siswa Array yang berisi data siswa
 * @param hitung Jumlah siswa yang tersimpan dalam array
 */
void tampilkan_statistik(const Siswa siswa[], int hitung) {
    if (hitung == 0) {
        printf("Tidak ada data untuk ditampilkan statistik\n");
        return;
    }
    
    float max_nilai = siswa[0].nilai;
    float min_nilai = siswa[0].nilai;
    const char* max_nama = siswa[0].nama;
    const char* min_nama = siswa[0].nama;
    
    int kategori[4] = {0}; // [Sangat Baik, Baik, Cukup, Perlu Perbaikan]
    
    // Cari nilai tertinggi, terendah, dan hitung kategori
    for (int i = 0; i < hitung; i++) {
        // Update max
        if (siswa[i].nilai > max_nilai) {
            max_nilai = siswa[i].nilai;
            max_nama = siswa[i].nama;
        }
        
        // Update min
        if (siswa[i].nilai < min_nilai) {
            min_nilai = siswa[i].nilai;
            min_nama = siswa[i].nama;
        }
        
        // Hitung kategori
        if (siswa[i].nilai >= 85.0f) {
            kategori[0]++;
        } else if (siswa[i].nilai >= 70.0f) {
            kategori[1]++;
        } else if (siswa[i].nilai >= 60.0f) {
            kategori[2]++;
        } else {
            kategori[3]++;
        }
    }
    
    // Hitung rata-rata
    float rata_rata = hitung_rata_rata_nilai(siswa, hitung);
    
    // Tampilkan statistik
    printf("\n=== STATISTIK NILAI ===\n");
    printf("Jumlah Siswa           : %d\n", hitung);
    printf("Nilai Tertinggi        : %.2f (%s)\n", max_nilai, max_nama);
    printf("Nilai Terendah         : %.2f (%s)\n", min_nilai, min_nama);
    printf("Rata-rata              : %.2f\n", rata_rata);
    printf("\nDistribusi Nilai:\n");
    printf("  Sangat Baik (85-100) : %d siswa (%.1f%%)\n", 
           kategori[0], (float)kategori[0]/hitung*100);
    printf("  Baik (70-84)         : %d siswa (%.1f%%)\n", 
           kategori[1], (float)kategori[1]/hitung*100);
    printf("  Cukup (60-69)        : %d siswa (%.1f%%)\n", 
           kategori[2], (float)kategori[2]/hitung*100);
    printf("  Perlu Perbaikan (<60): %d siswa (%.1f%%)\n", 
           kategori[3], (float)kategori[3]/hitung*100);
    printf("========================\n");
}

/**
 * @brief Fungsi untuk menampilkan menu program
 * 
 * Menampilkan pilihan menu yang tersedia untuk pengguna.
 */
void tampilkan_menu() {
    printf("\n=== MENU UTAMA ===\n");
    printf("1. Tambah Siswa\n");
    printf("2. Tampilkan Semua Siswa\n");
    printf("3. Cari Siswa (berdasarkan ID)\n");
    printf("4. Cari Siswa (berdasarkan Nama)\n");
    printf("5. Urutkan Siswa (berdasarkan Nilai)\n");
    printf("6. Tampilkan Statistik\n");
    printf("7. Hitung Rata-rata Nilai\n");
    printf("8. Keluar\n");
    printf("Pilih menu (1-8): ");
}

/**
 * @brief Fungsi utama program
 * 
 * Program utama yang menyediakan interface interaktif untuk manajemen data siswa.
 * Program ini menyediakan menu untuk berbagai operasi manajemen siswa.
 * 
 * @return 0 jika program berjalan dengan sukses
 */
int main() {
    Siswa siswa[MAX_PELAJAR];  // Array untuk menyimpan data siswa
    int jumlah_siswa = 0;      // Variabel untuk melacak jumlah siswa
    int pilihan;
    
    // Data awal untuk contoh
    printf("=== PROGRAM MANAJEMEN DATA SISWA ===\n");
    printf("Memuat data contoh...\n");
    
    // Tambahkan beberapa siswa contoh
    tambah_siswa(siswa, &jumlah_siswa, 101, "Glen", 70.2);
    tambah_siswa(siswa, &jumlah_siswa, 102, "John", 90.9);
    tambah_siswa(siswa, &jumlah_siswa, 103, "Alice", 85.5);
    tambah_siswa(siswa, &jumlah_siswa, 104, "Bob", 67.8);
    tambah_siswa(siswa, &jumlah_siswa, 105, "Charlie", 95.0);
    
    printf("Data contoh berhasil dimuat (%d siswa)\n", jumlah_siswa);
    
    // Loop menu utama
    do {
        tampilkan_menu();
        
        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid! Silakan coba lagi.\n");
            bersihkan_buffer();
            continue;
        }
        bersihkan_buffer();
        
        switch(pilihan) {
            case 1: { // Tambah Siswa
                int id;
                char nama[PANJANG_NAMA];
                float nilai;
                
                printf("\n--- TAMBAH SISWA ---\n");
                
                // Input ID
                printf("Masukkan ID siswa: ");
                while (scanf("%d", &id) != 1) {
                    printf("ID harus berupa angka! Coba lagi: ");
                    bersihkan_buffer();
                }
                bersihkan_buffer();
                
                // Input Nama
                printf("Masukkan nama siswa: ");
                fgets(nama, PANJANG_NAMA, stdin);
                nama[strcspn(nama, "\n")] = '\0'; // Hapus newline
                
                // Input Nilai
                printf("Masukkan nilai siswa (0-100): ");
                while (scanf("%f", &nilai) != 1 || !validasi_nilai(nilai)) {
                    printf("Nilai tidak valid! Harus antara 0-100. Coba lagi: ");
                    bersihkan_buffer();
                }
                bersihkan_buffer();
                
                // Tambahkan siswa
                if (tambah_siswa(siswa, &jumlah_siswa, id, nama, nilai)) {
                    printf("Siswa berhasil ditambahkan!\n");
                } else {
                    printf("Gagal menambahkan siswa.\n");
                }
                break;
            }
            
            case 2: // Tampilkan Semua Siswa
                tampilan_data_siswa(siswa, jumlah_siswa);
                break;
                
            case 3: { // Cari berdasarkan ID
                int id_cari;
                printf("\n--- CARI SISWA (ID) ---\n");
                printf("Masukkan ID yang dicari: ");
                scanf("%d", &id_cari);
                bersihkan_buffer();
                
                int index = cari_data_siswa(siswa, jumlah_siswa, id_cari);
                if (index != -1) {
                    printf("\nSiswa ditemukan:\n");
                    printf("ID    : %d\n", siswa[index].id);
                    printf("Nama  : %s\n", siswa[index].nama);
                    printf("Nilai : %.2f\n", siswa[index].nilai);
                } else {
                    printf("Siswa dengan ID %d tidak ditemukan.\n", id_cari);
                }
                break;
            }
            
            case 4: { // Cari berdasarkan Nama
                char nama_cari[PANJANG_NAMA];
                printf("\n--- CARI SISWA (NAMA) ---\n");
                printf("Masukkan nama yang dicari: ");
                fgets(nama_cari, PANJANG_NAMA, stdin);
                nama_cari[strcspn(nama_cari, "\n")] = '\0';
                
                int index = cari_siswa_by_nama(siswa, jumlah_siswa, nama_cari);
                if (index != -1) {
                    printf("\nSiswa ditemukan:\n");
                    printf("ID    : %d\n", siswa[index].id);
                    printf("Nama  : %s\n", siswa[index].nama);
                    printf("Nilai : %.2f\n", siswa[index].nilai);
                } else {
                    printf("Siswa dengan nama '%s' tidak ditemukan.\n", nama_cari);
                }
                break;
            }
            
            case 5: // Urutkan berdasarkan Nilai
                printf("\n--- MENGURUTKAN SISWA ---\n");
                urutkan_siswa_by_nilai(siswa, jumlah_siswa);
                printf("Siswa berhasil diurutkan berdasarkan nilai (tertinggi ke terendah).\n");
                tampilan_data_siswa(siswa, jumlah_siswa);
                break;
                
            case 6: // Tampilkan Statistik
                tampilkan_statistik(siswa, jumlah_siswa);
                break;
                
            case 7: { // Hitung Rata-rata
                float rata_rata = hitung_rata_rata_nilai(siswa, jumlah_siswa);
                printf("\n--- RATA-RATA NILAI ---\n");
                printf("Rata-rata nilai semua siswa: %.2f\n", rata_rata);
                break;
            }
                
            case 8: // Keluar
                printf("\nTerima kasih telah menggunakan program!\n");
                printf("Jumlah siswa dalam sistem: %d\n", jumlah_siswa);
                break;
                
            default:
                printf("Pilihan tidak valid! Silakan pilih 1-8.\n");
        }
        
    } while (pilihan != 8);
    
    printf("\n=== PROGRAM SELESAI ===\n");
    return 0;
}
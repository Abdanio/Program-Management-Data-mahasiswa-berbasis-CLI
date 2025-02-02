#include <stdio.h>
#include <string.h>

#define MAX_MAHASISWA 100
#define FILENAME "data_mahasiswa.txt" // Nama file untuk menyimpan data

typedef struct {
    int id; // ID mahasiswa
    char nama[50]; // Nama mahasiswa
    char jurusan[50]; // Jurusan mahasiswa
    int tahun_masuk; // Tahun masuk mahasiswa
} Mahasiswa;

Mahasiswa data[MAX_MAHASISWA]; // Array untuk menyimpan data mahasiswa
int jumlah_mahasiswa = 0; // Jumlah mahasiswa yang terdaftar

void tambahMahasiswa() {
    if (jumlah_mahasiswa >= MAX_MAHASISWA) {
        printf("Data penuh!\n"); // Menampilkan pesan jika data sudah penuh
        return;
    }

    Mahasiswa m;
    m.id = jumlah_mahasiswa; // Secara otomatis menetapkan ID berdasarkan jumlah mahasiswa saat ini
    getchar(); // Menghapus karakter newline dari buffer input
    printf("Masukkan Nama: ");
    fgets(m.nama, sizeof(m.nama), stdin); // Mengambil input nama mahasiswa
    m.nama[strcspn(m.nama, "\n")] = 0; // Menghapus karakter newline dari nama
    printf("Masukkan Jurusan: "); 
    fgets(m.jurusan, sizeof(m.jurusan), stdin); // Mengambil input jurusan mahasiswa
    m.jurusan[strcspn(m.jurusan, "\n")] = 0; // Menghapus karakter newline dari jurusan
    printf("Masukkan Tahun Masuk: "); 
    scanf("%d", &m.tahun_masuk); // Mengambil input tahun masuk mahasiswa

    data[jumlah_mahasiswa++] = m; // Menambahkan mahasiswa ke array
    printf("Data berhasil ditambahkan!\n"); // Menampilkan pesan berhasil
}

void tampilkanMahasiswa() {
    // Mengurutkan data berdasarkan ID menggunakan Bubble Sort
    for (int i = 0; i < jumlah_mahasiswa - 1; i++) {
        for (int j = 0; j < jumlah_mahasiswa - i - 1; j++) {
            if (data[j].id > data[j + 1].id) {
                Mahasiswa temp = data[j]; // Menyimpan data sementara
                data[j] = data[j + 1]; // Menukar data
                data[j + 1] = temp; // Menyimpan data sementara ke posisi yang benar
            }
        }
    }

    // Menampilkan semua data mahasiswa
    for (int i = 0; i < jumlah_mahasiswa; i++) {
        printf("ID: %d, Nama: %s, Jurusan: %s, Tahun Masuk: %d\n",
               data[i].id, data[i].nama, data[i].jurusan, data[i].tahun_masuk);
    }
}

void cariMahasiswa() {
    int pilihan;
    printf("Cari berdasarkan:\n1. ID\n2. Nama\nPilih: ");
    scanf("%d", &pilihan);
    
    if (pilihan == 1) {
        int id;
        printf("Masukkan ID mahasiswa yang dicari: ");
        scanf("%d", &id);
        for (int i = 0; i < jumlah_mahasiswa; i++) {
            if (data[i].id == id) {
                printf("ID: %d, Nama: %s, Jurusan: %s, Tahun Masuk: %d\n",
                       data[i].id, data[i].nama, data[i].jurusan, data[i].tahun_masuk);
                return; // Menghentikan pencarian jika ditemukan
            }
        }
        printf("Mahasiswa dengan ID %d tidak ditemukan.\n", id); // Pesan jika tidak ditemukan
    } else if (pilihan == 2) {
        char nama[50];
        printf("Masukkan Nama mahasiswa yang dicari: ");
        getchar(); // Menghapus karakter newline dari buffer input
        fgets(nama, sizeof(nama), stdin); // Mengambil input nama mahasiswa
        nama[strcspn(nama, "\n")] = 0; // Menghapus karakter newline dari nama
        for (int i = 0; i < jumlah_mahasiswa; i++) {
            if (strcmp(data[i].nama, nama) == 0) {
                printf("ID: %d, Nama: %s, Jurusan: %s, Tahun Masuk: %d\n",
                       data[i].id, data[i].nama, data[i].jurusan, data[i].tahun_masuk);
                return; // Menghentikan pencarian jika ditemukan
            }
        }
        printf("Mahasiswa dengan nama %s tidak ditemukan.\n", nama); // Pesan jika tidak ditemukan
    } else {
        printf("Pilihan tidak valid.\n"); // Pesan jika pilihan tidak valid
    }
}

void updateMahasiswa() {
    int id;
    printf("Masukkan ID mahasiswa yang ingin diupdate: ");
    scanf("%d", &id);
    for (int i = 0; i < jumlah_mahasiswa; i++) {
        if (data[i].id == id) {
            printf("Masukkan Nama Baru: ");
            getchar(); // Menghapus karakter newline dari buffer input
            fgets(data[i].nama, sizeof(data[i].nama), stdin); // Mengambil input nama baru
            data[i].nama[strcspn(data[i].nama, "\n")] = 0; // Menghapus karakter newline dari nama
            printf("Masukkan Jurusan Baru: ");
            fgets(data[i].jurusan, sizeof(data[i].jurusan), stdin); // Mengambil input jurusan baru
            data[i].jurusan[strcspn(data[i].jurusan, "\n")] = 0; // Menghapus karakter newline dari jurusan
            printf("Masukkan Tahun Masuk Baru: ");
            scanf("%d", &data[i].tahun_masuk); // Mengambil input tahun masuk baru
            printf("Data mahasiswa berhasil diupdate!\n"); // Pesan berhasil
            return; // Menghentikan fungsi setelah update
        }
    }
    printf("Mahasiswa dengan ID %d tidak ditemukan.\n", id); // Pesan jika tidak ditemukan
}

void hapusMahasiswa() {
    int id;
    printf("Masukkan ID mahasiswa yang ingin dihapus: ");
    scanf("%d", &id);
    for (int i = 0; i < jumlah_mahasiswa; i++) {
        if (data[i].id == id) {
            for (int j = i; j < jumlah_mahasiswa - 1; j++) {
                data[j] = data[j + 1]; // Shift data left
            }
            jumlah_mahasiswa--; // Decrease count
            // Reassign IDs
            for (int k = 0; k < jumlah_mahasiswa; k++) {
                data[k].id = k; // Update IDs to be sequential
            }
            printf("Mahasiswa dengan ID %d berhasil dihapus.\n", id); // Pesan berhasil
            return; // Menghentikan fungsi setelah penghapusan
        }
    }
    printf("Mahasiswa dengan ID %d tidak ditemukan.\n", id); // Pesan jika tidak ditemukan
}

void simpanData() {
    FILE *file = fopen(FILENAME, "w"); // Membuka file untuk menulis
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data.\n");
        return;
    }
    for (int i = 0; i < jumlah_mahasiswa; i++) {
        fprintf(file, "%d,%s,%s,%d\n", data[i].id, data[i].nama, data[i].jurusan, data[i].tahun_masuk); // Menyimpan data ke file
    }
    fclose(file); // Menutup file
    printf("Data berhasil disimpan ke %s.\n", FILENAME); // Pesan berhasil
}

void muatData() {
    FILE *file = fopen(FILENAME, "r"); // Membuka file untuk membaca
    if (file == NULL) {
        printf("Gagal membuka file untuk memuat data.\n");
        return;
    }
    while (fscanf(file, "%d,%49[^,],%49[^,],%d\n", &data[jumlah_mahasiswa].id, data[jumlah_mahasiswa].nama, data[jumlah_mahasiswa].jurusan, &data[jumlah_mahasiswa].tahun_masuk) == 4) {
        jumlah_mahasiswa++; // Menambah jumlah mahasiswa
    }
    fclose(file); // Menutup file
    printf("Data berhasil dimuat dari %s.\n", FILENAME); // Pesan berhasil
}

int main() {
    muatData(); // Memuat data saat program dimulai
    int pilihan;
    do {
        printf("\n=== Sistem Manajemen Data Mahasiswa ===\n");
        printf("1. Tambah Data\n");
        printf("2. Tampilkan Semua Data\n");
        printf("3. Cari Mahasiswa\n");
        printf("4. Update Mahasiswa\n");
        printf("5. Hapus Mahasiswa\n");
        printf("6. Simpan Data\n");
        printf("7. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahMahasiswa();
                break;

            case 2:
                tampilkanMahasiswa();
                break;

            case 3:
                cariMahasiswa();
                break;

            case 4:
                updateMahasiswa();
                break;

            case 5:
                hapusMahasiswa();
                break;

            case 6:
                simpanData(); // Menyimpan data ke file
                break;

            case 7:
                printf("Keluar...\n"); // Pesan keluar
                break;

            default:
                printf("Pilihan tidak valid!\n"); // Pesan jika pilihan tidak valid
        }
    } while (pilihan != 7);

    return 0;
}

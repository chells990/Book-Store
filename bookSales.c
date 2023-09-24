#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// DEFINE
#define WINDOWS // Jika menggunakan OS windows, uncomment ini

// struct
typedef struct
{
    char judul[100];
    int hargaAsli;
    int hargaDiskon;
    char penerbit[100];
    char penulis[100];
    int stok;
    char kode[7];
    int terjual;
    long long int hargaTerjual;
} database;

typedef struct
{
    int hargaAsli_total;
    int hargaDiskon_total;
    int total;
    int genre;
    int index;
    int diskonCheck;
    int hargaSatuan;
} databaseKeranjang;

typedef struct
{
    char nama[100];
    int totalBuku;
    long long int totalHarga;
    char tanggal[25];
    int metodePembayaran;
    int jumlahJenis;

} dbPembeli;

// variabel global
int jumlahBuku[7];
int fileInvalid[6] = {0};
char headerGenre[5][10] = {"Novel", "Komik", "Religi", "Edukasi", "Majalah"};
char stringNamaFile[7][13] = {"NOVEL.txt", "KOMIK.txt", "RELIGI.txt", "EDUKASI.txt", "MAJALAH.txt", "Pembeli.txt", "Keranjang.txt"};
int bukuKe;
int pembeliKe = 0;
char bulan[12][20];
char pembayaranString[12][20];
long long int totalPendapatan = 0;
database dataBuku[6][25];
databaseKeranjang keranjang[100][30];
dbPembeli dataPembeli[100];

// Prototype
void menuUtama();
void printListDB(int jenisBuku, int index);
void clearScreen();
void pauseScreen();
void backToMainMenu();
void isiDatabaseDariFile();
void printListBukuBerdasarkanGenre(int clear, int jenisBuku);
int hitungHargaBuku(int harga, int total);
int listBuku(int clear);
void menuPembelian();
void isiKeranjangSekarang(int bayar);
void menuUtama();
int linearSearch(int *genre, int *bukuKe, char judul[]);
void search();
void tambahBuku();
int kodeGenerator(int genre, int index);
void tanggalGenerator();
void bulanGenerator();
void pembayarangenerator();
void quicksort(int terjual[], int left, int right);
void prosesBayar();
void simpanKeFileDB();
void salesHistory(int urutan);
void simpanKeFileSalesHistory(int urutan, int tanya, int z, int urut);

int main()
{
    printf("Tunggu sebentar, program sedang loading!\n\n");
    pembayarangenerator();
    bulanGenerator();
    isiDatabaseDariFile();
    menuUtama();
    return 0;
}

void clearScreen()
{
#ifdef WINDOWS
    system("CLS"); // Windows
#else
    system("clear"); // Linux OR mac use ini
#endif
}

void pauseScreen()
{
    printf("Tekan enter untuk melanjutkan");
    getchar();
}

void backToMainMenu()
{
    pauseScreen();
    menuUtama();
}

void isiDatabaseDariFile()
{
    int jenisBuku = 1;
    int index = 0;
    FILE *stokNovel = fopen("NOVEL.txt", "r");
    FILE *stokKomik = fopen("COMICS.txt", "r");
    FILE *stokReligi = fopen("RELIGI.txt", "r");
    FILE *stokEdukasi = fopen("EDUKASI.txt", "r");
    FILE *stokMajalah = fopen("MAJALAH.txt", "r");

    if (stokNovel == NULL)
    {
        fileInvalid[0] = 1;
    }
    else
    {
        while (fscanf(stokNovel, "\n%[^|]|%d|%d|%[^|]|%[^|]|%d|%[^\n]", &dataBuku[jenisBuku][index].judul, &dataBuku[jenisBuku][index].hargaAsli, &dataBuku[jenisBuku][index].hargaDiskon, &dataBuku[jenisBuku][index].penerbit, &dataBuku[jenisBuku][index].penulis, &dataBuku[jenisBuku][index].stok, &dataBuku[jenisBuku][index].kode) != EOF)
        {
            index++;
        }
    }

    jumlahBuku[jenisBuku] = index;
    index = 0;
    jenisBuku++;

    if (stokKomik == NULL)
    {
        fileInvalid[1] = 1;
    }
    else
    {
        while (fscanf(stokKomik, "\n%[^|]|%d|%d|%[^|]|%[^|]|%d|%[^\n]", &dataBuku[jenisBuku][index].judul, &dataBuku[jenisBuku][index].hargaAsli, &dataBuku[jenisBuku][index].hargaDiskon, &dataBuku[jenisBuku][index].penerbit, &dataBuku[jenisBuku][index].penulis, &dataBuku[jenisBuku][index].stok, &dataBuku[jenisBuku][index].kode) != EOF)
        {
            index++;
        }
    }

    jumlahBuku[jenisBuku] = index;
    index = 0;
    jenisBuku++;

    if (stokReligi == NULL)
    {
        fileInvalid[2] = 1;
    }
    else
    {
        while (fscanf(stokReligi, "\n%[^|]|%d|%d|%[^|]|%[^|]|%d|%[^\n]", &dataBuku[jenisBuku][index].judul, &dataBuku[jenisBuku][index].hargaAsli, &dataBuku[jenisBuku][index].hargaDiskon, &dataBuku[jenisBuku][index].penerbit, &dataBuku[jenisBuku][index].penulis, &dataBuku[jenisBuku][index].stok, &dataBuku[jenisBuku][index].kode) != EOF)
        {
            index++;
        }
    }

    jumlahBuku[jenisBuku] = index;
    index = 0;
    jenisBuku++;

    if (stokEdukasi == NULL)
    {
        fileInvalid[3] = 1;
    }
    else
    {
        while (fscanf(stokEdukasi, "\n%[^|]|%d|%d|%[^|]|%[^|]|%d|%[^\n]", &dataBuku[jenisBuku][index].judul, &dataBuku[jenisBuku][index].hargaAsli, &dataBuku[jenisBuku][index].hargaDiskon, &dataBuku[jenisBuku][index].penerbit, &dataBuku[jenisBuku][index].penulis, &dataBuku[jenisBuku][index].stok, &dataBuku[jenisBuku][index].kode) != EOF)
        {
            index++;
        }
    }

    jumlahBuku[jenisBuku] = index;
    index = 0;
    jenisBuku++;

    if (stokMajalah == NULL)
    {
        fileInvalid[4] = 1;
    }
    else
    {
        while (fscanf(stokMajalah, "\n%[^|]|%d|%d|%[^|]|%[^|]|%d|%[^\n]", &dataBuku[jenisBuku][index].judul, &dataBuku[jenisBuku][index].hargaAsli, &dataBuku[jenisBuku][index].hargaDiskon, &dataBuku[jenisBuku][index].penerbit, &dataBuku[jenisBuku][index].penulis, &dataBuku[jenisBuku][index].stok, &dataBuku[jenisBuku][index].kode) != EOF)
        {
            index++;
        }
    }

    jumlahBuku[jenisBuku] = index;

    fclose(stokNovel);
    fclose(stokKomik);
    fclose(stokReligi);
    fclose(stokEdukasi);
    fclose(stokMajalah);

    /* Data pembelian*/
    FILE *filePembelian = fopen("Pembeli.txt", "r");
    FILE *fileKeranjang = fopen("Keranjang.txt", "r");

    index = 0;

    if (filePembelian == NULL)
    {
        fileInvalid[5] = 1;
    }
    else
    {
        while (fscanf(filePembelian, "\n%[^|]|%d|%d|%d|%d|%[^\n]", &dataPembeli[index].nama, &dataPembeli[index].totalBuku, &dataPembeli[index].totalHarga, &dataPembeli[index].metodePembayaran, &dataPembeli[index].jumlahJenis, &dataPembeli[index].tanggal) != EOF)
        {
            totalPendapatan += dataPembeli[index].totalHarga;
            index++;
        }
    }

    pembeliKe = index;
    index = 0;
    int orangKe = 0;

    if (fileKeranjang == NULL)
    {
        fileInvalid[6] = 1;
    }
    else
    {
        while (fscanf(fileKeranjang, "\n%d|%d|%d|%d|%d|%d|%d\n", &keranjang[orangKe][index].diskonCheck, &keranjang[orangKe][index].hargaSatuan, &keranjang[orangKe][index].hargaAsli_total, &keranjang[orangKe][index].hargaDiskon_total, &keranjang[orangKe][index].total, &keranjang[orangKe][index].genre, &keranjang[orangKe][index].index) != EOF)
        {
            dataBuku[keranjang[orangKe][index].genre][keranjang[orangKe][index].index].terjual += keranjang[orangKe][index].total;
            if (keranjang[orangKe][index].diskonCheck == 0)
            {
                dataBuku[keranjang[orangKe][index].genre][keranjang[orangKe][index].index].hargaTerjual += keranjang[orangKe][index].hargaDiskon_total;
            }
            else
            {
                dataBuku[keranjang[orangKe][index].genre][keranjang[orangKe][index].index].hargaTerjual += keranjang[orangKe][index].hargaAsli_total;
            }
            index++;
            if (index == dataPembeli[orangKe].jumlahJenis)
            {
                orangKe++;
                index = 0;
            }
        }
    }

    fclose(filePembelian);
    fclose(fileKeranjang);
}

void printListDB(int jenisBuku, int index)
{
    printf("Buku ke       : %d\n", index + 1);
    printf("Judul         : %s\n", dataBuku[jenisBuku][index].judul);
    printf("Harga         : %d\n", dataBuku[jenisBuku][index].hargaAsli);
    printf("Harga Diskon  : ");
    if (dataBuku[jenisBuku][index].hargaDiskon > 0) // jika ada diskon
    {

        float fDiskon = (((float)dataBuku[jenisBuku][index].hargaAsli - (float)dataBuku[jenisBuku][index].hargaDiskon) / (float)dataBuku[jenisBuku][index].hargaAsli) * 100;
        printf("%d\n", dataBuku[jenisBuku][index].hargaDiskon);
        printf("Anda Hemat    : %.2f%c\n", fDiskon, '%');
    }
    else
    {
        printf("-\n");
    }
    printf("Penerbit      : %s\n", dataBuku[jenisBuku][index].penerbit);
    printf("Penulis       : %s\n", dataBuku[jenisBuku][index].penulis);
    printf("Stok Tersedia : %d\n", dataBuku[jenisBuku][index].stok);
    printf("Kode Buku     : %s\n\n", dataBuku[jenisBuku][index].kode);
}

void printListBukuBerdasarkanGenre(int clear, int jenisBuku)
{
    int index = 0;
    if (clear == 1)
    {
        clearScreen();
    }

    printf("List Buku Genre %s\n", headerGenre[jenisBuku - 1]);
    printf("Ada %d judul buku\n\n", jumlahBuku[jenisBuku]);

    do
    {
        printListDB(jenisBuku, index);
        index++;
    } while (index < jumlahBuku[jenisBuku]);

    if (clear == 1)
    {
        backToMainMenu();
    }
    else if (clear == 3) // ubah stok buku
    {
    pilihBuku2:
        printf("Input 999 untuk memilih genre lain\n\n");
        printf("Pilih buku yang diinginkan   : ");
        scanf("%d", &index);
        getchar();
        if (index == 999)
        {
            clearScreen();
            listBuku(clear);
        }
        else if (index > jumlahBuku[jenisBuku] || index <= 0)
        {
            printf("Maaf, input tidak dikenali!\n\n");
            goto pilihBuku2;
        }
        else
        {
            printf("Kode buku yang dipilih       : %s\n", dataBuku[jenisBuku][index - 1].kode);
            printf("Input stok baru buku         : ");
            scanf("%d", &dataBuku[jenisBuku][index - 1].stok);
            getchar();
            printf("\nStok sukses diperbarui!\n");
            pauseScreen();
            menuUtama();
        }
    }
    else if (clear == 4) // ubah harga buku
    {
        char confirm;
    pilihBuku3:
        printf("Input 999 untuk memilih genre lain\n\n");
        printf("Pilih buku yang diinginkan   : ");
        scanf("%d", &index);
        getchar();
        if (index == 999)
        {
            clearScreen();
            listBuku(clear);
        }
        else if (index > jumlahBuku[jenisBuku] || index <= 0)
        {
            printf("Maaf, input tidak dikenali!\n\n");
            goto pilihBuku3;
        }
        else
        {
            printf("Kode buku yang dipilih       : %s\n", dataBuku[jenisBuku][index - 1].kode);
            printf("Input harga normal baru      : Rp.");
            scanf("%d", &dataBuku[jenisBuku][index - 1].hargaAsli);
            getchar();
        tanyaDiskon2:
            printf("Apakah ada diskon? (Y/N)     : ");
            scanf("%c", &confirm);
            getchar();
            if (tolower(confirm) == 'y')
            {
            inputDiskon2:
                printf("Input harga diskon baru      : Rp.");
                scanf("%d", &dataBuku[jenisBuku][index - 1].hargaDiskon);
                getchar();
                if (dataBuku[jenisBuku][index - 1].hargaDiskon > dataBuku[jenisBuku][index - 1].hargaAsli)
                {
                    printf("Harga diskon harus lebih rendah dari harga asli!\n");
                    goto inputDiskon2;
                }
                else if (dataBuku[jenisBuku][index - 1].hargaDiskon < 1)
                {
                    printf("Value tidak sesuai!\n");
                    goto inputDiskon2;
                }
            }
            else if (tolower(confirm) == 'n')
            {
                dataBuku[jenisBuku][index - 1].hargaDiskon = 0;
            }
            else
            {
                printf("Maaf, input tidak dikenali\n");
                pauseScreen();
                goto tanyaDiskon2;
            }
        }
        printf("\nHarga sukses diperbarui!\n");
        pauseScreen();
        menuUtama();
    }
    else // menu pembelian
    {
    pilihBuku:
        printf("Input 999 untuk memilih genre lain\n\n");
        printf("Pilih buku yang diinginkan   : ");
        scanf("%d", &index);
        getchar();
        if (index == 999)
        {
            clearScreen();
            listBuku(clear);
        }
        else if (index > jumlahBuku[jenisBuku] || index <= 0)
        {
            printf("Maaf, input tidak dikenali!\n\n");
            goto pilihBuku;
        }
        else if (dataBuku[jenisBuku][index - 1].stok < 1)
        {
            printf("Maaf, stok buku habis! Silakan cek lain waktu!\n\n");
            goto pilihBuku;
        }
        else
        {
            printf("Kode buku yang dipilih       : %s\n", dataBuku[jenisBuku][index - 1].kode);
        tanyaJumlah:;
            int total = 0;
            printf("Total buku yang ingin dibeli : ");
            scanf("%d", &total);
            getchar();
            if (total <= 0)
            {
                printf("Total pembelian harus lebih dari 0!\n");
                goto tanyaJumlah;
            }
            else if (total > dataBuku[jenisBuku][index - 1].stok)
            {
                printf("Stok buku tidak cukup!\n");
                goto tanyaJumlah;
            }
            else
            {
                keranjang[pembeliKe][bukuKe].genre = jenisBuku;
                keranjang[pembeliKe][bukuKe].index = index - 1;
                keranjang[pembeliKe][bukuKe].hargaAsli_total = hitungHargaBuku(dataBuku[jenisBuku][index - 1].hargaAsli, total);
                if (dataBuku[jenisBuku][index - 1].hargaDiskon == 0) // tanpa diskon
                {
                    keranjang[pembeliKe][bukuKe].diskonCheck = 1;
                    keranjang[pembeliKe][bukuKe].hargaDiskon_total = hitungHargaBuku(dataBuku[jenisBuku][index - 1].hargaAsli, total);
                    keranjang[pembeliKe][bukuKe].hargaSatuan = dataBuku[jenisBuku][index - 1].hargaAsli;
                }
                else
                {
                    keranjang[pembeliKe][bukuKe].diskonCheck = 0;
                    keranjang[pembeliKe][bukuKe].hargaDiskon_total = hitungHargaBuku(dataBuku[jenisBuku][index - 1].hargaDiskon, total);
                    keranjang[pembeliKe][bukuKe].hargaSatuan = dataBuku[jenisBuku][index - 1].hargaDiskon;
                }
                keranjang[pembeliKe][bukuKe++].total = total;
            }
        }
    }
}

int hitungHargaBuku(int harga, int total)
{
    harga *= total;
    return harga;
}

int listBuku(int clear)
{
    int jenisBuku;
    printf("Genre yang tersedia:\n");
    printf("\t1. Novel\n");
    printf("\t2. Komik\n");
    printf("\t3. Religi\n");
    printf("\t4. Edukasi\n");
    printf("\t5. Majalah\n");
    printf("Pilih genre: ");
    scanf("%d", &jenisBuku);
    getchar();
    if (jenisBuku > 5 || jenisBuku < 1)
    {
        printf("Maaf, input tidak dikenali\n");
        pauseScreen();
        listBuku(clear);
    }

    if (clear == 2)
    {
        return jenisBuku;
    }
    else
    {
        printListBukuBerdasarkanGenre(clear, jenisBuku);
    }
}

void menuPembelian()
{
    bukuKe = 0;
    int input;

    printf("Masukkan nama pelanggan: ");
    scanf("%[^\n]s", &dataPembeli[pembeliKe].nama);
    getchar();

pilihBuku:
    listBuku(0);
aksi:
    printf("\n1. Tambah buku lagi\n");
    printf("2. Lihat keranjang belanjaan\n");
    printf("3. Checkout\n");

    printf("Pilih menu yang diinginkan: ");
    scanf("%d", &input);

    if (input == 1)
    {
        clearScreen();
        goto pilihBuku;
    }
    else if (input == 2)
    {
        clearScreen();
        isiKeranjangSekarang(0);
        goto aksi;
    }
    else if (input == 3)
    {
        clearScreen();
        isiKeranjangSekarang(1);
        tanggalGenerator();
        pembeliKe++;
        pauseScreen();
        menuUtama();
    }
    else if (input != 3)
    {
        printf("Maaf, input tidak dikenali\n");
        pauseScreen();
        goto aksi;
    }
}

void isiKeranjangSekarang(int bayar)
{
    long long int totalAsli = 0;
    long long int totalDiskon = 0;
    int totalBuku = 0;
    int i;
    double diskon;
    printf("Isi keranjang belanjaan saat ini atas nama %s: \n\n", dataPembeli[pembeliKe].nama);
    for (i = 0; i < bukuKe; i++)
    {
        printf("Buku ke                    : %d\n", i + 1);
        printf("Kode Buku                  : %s\n", dataBuku[keranjang[pembeliKe][i].genre][keranjang[pembeliKe][i].index].kode);
        printf("Judul Buku                 : %s\n", dataBuku[keranjang[pembeliKe][i].genre][keranjang[pembeliKe][i].index].judul);
        printf("Total Buku yang dibeli     : %d\n", keranjang[pembeliKe][i].total);
        dataBuku[keranjang[pembeliKe][i].genre][keranjang[pembeliKe][i].index].stok -= keranjang[pembeliKe][i].total;
        dataBuku[keranjang[pembeliKe][i].genre][keranjang[pembeliKe][i].index].terjual += keranjang[pembeliKe][i].total;

        if (dataBuku[keranjang[pembeliKe][i].genre][keranjang[pembeliKe][i].index].hargaDiskon == 0) // tanpa diskon
        {
            printf("Harga Satuan               : Rp.%d\n", dataBuku[keranjang[pembeliKe][i].genre][keranjang[pembeliKe][i].index].hargaAsli);
            printf("Total Harga                : Rp.%d\n\n", keranjang[pembeliKe][i].hargaAsli_total);
        }
        else
        {
            printf("Harga Satuan (Diskon)      : Rp.%d\n", dataBuku[keranjang[pembeliKe][i].genre][keranjang[pembeliKe][i].index].hargaDiskon);
            printf("Total Harga                : Rp.%d\n\n", keranjang[pembeliKe][i].hargaDiskon_total);
        }

        totalAsli += keranjang[pembeliKe][i].hargaAsli_total;
        totalDiskon += keranjang[pembeliKe][i].hargaDiskon_total;
        totalBuku += keranjang[pembeliKe][i].total;

        if (bayar == 1)
        {
            if (keranjang[pembeliKe][i].diskonCheck == 0)
            {
                dataBuku[keranjang[pembeliKe][i].genre][keranjang[pembeliKe][i].index].hargaTerjual += keranjang[pembeliKe][i].hargaDiskon_total;
            }
            else
            {
                dataBuku[keranjang[pembeliKe][i].genre][keranjang[pembeliKe][i].index].hargaTerjual += keranjang[pembeliKe][i].hargaAsli_total;
            }
        }
    }
    dataPembeli[pembeliKe].totalBuku = totalBuku;

    diskon = ((double)totalAsli - (double)totalDiskon) / (double)totalAsli * 100;

    if (totalAsli == totalDiskon)
    {
        printf("Total harga                : Rp.%d\n", totalAsli);
        dataPembeli[pembeliKe].totalHarga = totalAsli;
        if (bayar == 1)
        {
            totalPendapatan += totalAsli;
        }
    }
    else
    {
        printf("Total harga sebelum diskon : Rp.%d\n", totalAsli);
        printf("Total harga setelah diskon : Rp.%d\n", totalDiskon);
        printf("Anda hemat                 : Rp.%.2lf%c\n\n", diskon, '%');
        dataPembeli[pembeliKe].totalHarga = totalDiskon;
        if (bayar == 1)
        {
            totalPendapatan += totalDiskon;
        }
    }

    if (bayar == 1)
    {
        prosesBayar();
    }
}
int linearSearch(int *genre, int *index, char judul[])
{
    int i, j;
    for (i = 1; i < 6; i++)
    {
        for (j = 0; j < jumlahBuku[i]; j++)
        {
            if (strcmp(judul, dataBuku[i][j].judul) == 0)
            {
                *genre = i;
                *index = j;
                return 0;
            }
        }
    }
    return -1;
}

void search()
{
cariBuku:;
    int genre;
    int index;
    char input[100];
    char confirm;
    printf("Masukan Judul Buku : ");
    scanf("%[^\n]s", input);
    getchar();
    int result = linearSearch(&genre, &index, input);
    if (result == -1)
    {
        printf("Buku tidak ditemukan!\n");
    search0:
        printf("Search lagi? (Y/N): ");
        scanf("%c", &confirm);
        getchar();
        if (tolower(confirm) == 'y')
        {
            goto cariBuku;
        }
        else if (tolower(confirm) == 'n')
        {
            menuUtama();
        }
        else
        {
            printf("Maaf, input tidak dikenali\n");
            pauseScreen();
            goto search0;
        }
    }
    else
    {
        printf("Buku Ditemukan\n\n");
        printListDB(genre, index);
    search:
        printf("Search lagi? (Y/N): ");
        scanf("%c", &confirm);
        getchar();
        if (tolower(confirm) == 'y')
        {
            goto cariBuku;
        }
        else if (tolower(confirm) == 'n')
        {
            menuUtama();
        }
        else
        {
            printf("Maaf, input tidak dikenali\n");
            pauseScreen();
            goto search;
        }
    }
}

void tambahBuku()
{
    char confirm;
    int genre = listBuku(2);
    int index = jumlahBuku[genre];

    printf("\nInput judul              : ");
    scanf("%[^\n]s", &dataBuku[genre][index].judul);
    getchar();
    printf("Input harga normal       : Rp.");
    scanf("%d", &dataBuku[genre][index].hargaAsli);
    getchar();
tanyaDiskon:
    printf("Apakah ada diskon? (Y/N) : ");
    scanf("%c", &confirm);
    getchar();
    if (tolower(confirm) == 'y')
    {
    inputDiskon:
        printf("Input harga diskon       : Rp.");
        scanf("%d", &dataBuku[genre][index].hargaDiskon);
        getchar();
        if (dataBuku[genre][index].hargaDiskon > dataBuku[genre][index].hargaAsli)
        {
            printf("Harga diskon harus lebih rendah dari harga asli!\n");
            goto inputDiskon;
        }
        else if (dataBuku[genre][index].hargaDiskon < 1)
        {
            printf("Value tidak sesuai!\n");
            goto inputDiskon;
        }
    }
    else if (tolower(confirm) == 'n')
    {
        dataBuku[genre][index].hargaDiskon = 0;
    }
    else
    {
        printf("Maaf, input tidak dikenali\n");
        pauseScreen();
        goto tanyaDiskon;
    }
    printf("Input penerbit           : ");
    scanf("%[^\n]s", &dataBuku[genre][index].penerbit);
    getchar();
    printf("Input penulis            : ");
    scanf("%[^\n]s", &dataBuku[genre][index].penulis);
    getchar();
    printf("Input Stok               : ");
    scanf("%d", &dataBuku[genre][index].stok);
    getchar();
    kodeGenerator(genre, index);
    fileInvalid[genre - 1] = 0; // Sebagai tanda bahwa sudah ada data nya yang valid

    printf("\nBuku sukses ditambahkan!\n");
    jumlahBuku[genre] += 1;
    pauseScreen();
    menuUtama();
}

int kodeGenerator(int genre, int index)
{
    char indexCH[105];
    index += 1;
    snprintf(indexCH, 4, "%d", index);
    index -= 1;
    // kode abjad
    if (genre == 1)
    {
        dataBuku[genre][index].kode[0] = 'A';
    }
    else if (genre == 2)
    {
        dataBuku[genre][index].kode[0] = 'B';
    }
    else if (genre == 3)
    {
        dataBuku[genre][index].kode[0] = 'C';
    }
    else if (genre == 4)
    {
        dataBuku[genre][index].kode[0] = 'D';
    }
    else if (genre == 5)
    {
        dataBuku[genre][index].kode[0] = 'E';
    }

    if (index < 10)
    {
        dataBuku[genre][index].kode[1] = '0';
        dataBuku[genre][index].kode[2] = '0';
        strcat(dataBuku[genre][index].kode, indexCH);
    }
    else if (index < 100)
    {
        dataBuku[genre][index].kode[1] = '0';
        strcat(dataBuku[genre][index].kode, indexCH);
    }
    else
    {
        strcat(dataBuku[genre][index].kode, indexCH);
    }
}

void tanggalGenerator()
{
    char tahun[5], hari[3], jam[3], menit[3], detik[3], pembeliCH[4], bulanCH[3];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(hari, 3, "%02d", tm.tm_mday);
    snprintf(tahun, 5, "%02d", tm.tm_year + 1900);
    snprintf(jam, 3, "%02d", tm.tm_hour);
    snprintf(menit, 3, "%02d", tm.tm_min);
    snprintf(detik, 3, "%02d", tm.tm_sec);
    strcpy(dataPembeli[pembeliKe].tanggal, hari);
    strcat(dataPembeli[pembeliKe].tanggal, " ");
    strcat(dataPembeli[pembeliKe].tanggal, bulan[tm.tm_mon]);
    strcat(dataPembeli[pembeliKe].tanggal, " ");
    strcat(dataPembeli[pembeliKe].tanggal, tahun);
    strcat(dataPembeli[pembeliKe].tanggal, " - ");
    strcat(dataPembeli[pembeliKe].tanggal, jam);
    strcat(dataPembeli[pembeliKe].tanggal, ":");
    strcat(dataPembeli[pembeliKe].tanggal, menit);
    strcat(dataPembeli[pembeliKe].tanggal, ":");
    strcat(dataPembeli[pembeliKe].tanggal, detik);
}

void bulanGenerator()
{
    strcpy(bulan[0], "Januari");
    strcpy(bulan[1], "Februari");
    strcpy(bulan[2], "Maret");
    strcpy(bulan[3], "April");
    strcpy(bulan[4], "Mei");
    strcpy(bulan[5], "Juni");
    strcpy(bulan[6], "Juli");
    strcpy(bulan[7], "Agustus");
    strcpy(bulan[8], "September");
    strcpy(bulan[9], "Oktober");
    strcpy(bulan[10], "November");
    strcpy(bulan[11], "Desember");
}

void pembayarangenerator()
{
    strcpy(pembayaranString[0], "Cash");
    strcpy(pembayaranString[1], "Debit - VISA");
    strcpy(pembayaranString[2], "Debit - Mastercard");
    strcpy(pembayaranString[3], "Debit - GPN");
    strcpy(pembayaranString[4], "Kredit - VISA");
    strcpy(pembayaranString[5], "Kredit - Mastercard");
    strcpy(pembayaranString[6], "E-Wallet - OVO");
    strcpy(pembayaranString[7], "E-Wallet - GoPay");
    strcpy(pembayaranString[8], "E-Wallet - DANA");
    strcpy(pembayaranString[9], "E-Wallet - LinkAja");
    strcpy(pembayaranString[10], "E-Wallet - ShopeePay");
}

void prosesBayar()
{
    long long int input;
    printf("\nMetode Pembayaran        :\n");
    for (int i = 0; i < 11; i++)
    {
        printf("%d. %s\n", i + 1, pembayaranString[i]);
    }
inputMetode:
    printf("Pilih metode pembayaran  : ");
    scanf("%d", &dataPembeli[pembeliKe].metodePembayaran);
    getchar();
    if (dataPembeli[pembeliKe].metodePembayaran == 1)
    {
    inputUang:
        printf("Masukkan nominal uang    : ");
        scanf("%lld", &input);
        getchar();
        if (input == dataPembeli[pembeliKe].totalHarga)
        {
            printf("Tidak ada kembalian!\nPembelian Sukses!\n");
        }
        else if (input < dataPembeli[pembeliKe].totalHarga)
        {
            printf("Nominal Uang Kurang!\n");
            goto inputUang;
        }
        else
        {
            printf("Kembalian: %lld\nPembelian Sukses!\n", input - dataPembeli[pembeliKe].totalHarga);
        }
    }
    else if (dataPembeli[pembeliKe].metodePembayaran > 1 && dataPembeli[pembeliKe].metodePembayaran < 7)
    {
        printf("Masukkan nomor kartu     : ");
        scanf("%lld", &input);
        getchar();
        printf("Pembelian Sukses!\n");
    }
    else if (dataPembeli[pembeliKe].metodePembayaran > 6 && dataPembeli[pembeliKe].metodePembayaran < 12)
    {
        printf("Masukkan nomor handphone : ");
        scanf("%lld", &input);
        getchar();
        printf("Pembelian Sukses!\n");
    }
    else
    {
        printf("Input salah!\n");
        goto inputMetode;
    }
    dataPembeli[pembeliKe].jumlahJenis = bukuKe;

    fileInvalid[5] = 0;
    fileInvalid[6] = 0;
}

void simpanKeFileDB()
{
    int jenisBuku = 1;
    int index = 0;
    FILE *writeNovel = fopen("NOVEL.txt", "w");
    FILE *writeKomik = fopen("COMICS.txt", "w");
    FILE *writeReligi = fopen("RELIGI.txt", "w");
    FILE *writeEdukasi = fopen("EDUKASI.txt", "w");
    FILE *writeMajalah = fopen("MAJALAH.txt", "w");

    if (fileInvalid[0] == 0)
    {
        for (int index = 0; index < jumlahBuku[1]; index++)
        {
            fprintf(writeNovel, "%s|%d|%d|%s|%s|%d|%s\n", dataBuku[jenisBuku][index].judul, dataBuku[jenisBuku][index].hargaAsli, dataBuku[jenisBuku][index].hargaDiskon, dataBuku[jenisBuku][index].penerbit, dataBuku[jenisBuku][index].penulis, dataBuku[jenisBuku][index].stok, dataBuku[jenisBuku][index].kode);
        }
        fclose(writeNovel);
    }

    jenisBuku++;
    if (fileInvalid[1] == 0)
    {
        for (int index = 0; index < jumlahBuku[2]; index++)
        {
            fprintf(writeKomik, "%s|%d|%d|%s|%s|%d|%s\n", dataBuku[jenisBuku][index].judul, dataBuku[jenisBuku][index].hargaAsli, dataBuku[jenisBuku][index].hargaDiskon, dataBuku[jenisBuku][index].penerbit, dataBuku[jenisBuku][index].penulis, dataBuku[jenisBuku][index].stok, dataBuku[jenisBuku][index].kode);
        }
        fclose(writeKomik);
    }

    jenisBuku++;

    if (fileInvalid[2] == 0)
    {
        for (int index = 0; index < jumlahBuku[3]; index++)
        {
            fprintf(writeReligi, "%s|%d|%d|%s|%s|%d|%s\n", dataBuku[jenisBuku][index].judul, dataBuku[jenisBuku][index].hargaAsli, dataBuku[jenisBuku][index].hargaDiskon, dataBuku[jenisBuku][index].penerbit, dataBuku[jenisBuku][index].penulis, dataBuku[jenisBuku][index].stok, dataBuku[jenisBuku][index].kode);
        }
        fclose(writeReligi);
    }

    jenisBuku++;

    if (fileInvalid[3] == 0)
    {
        for (int index = 0; index < jumlahBuku[4]; index++)
        {
            fprintf(writeEdukasi, "%s|%d|%d|%s|%s|%d|%s\n", dataBuku[jenisBuku][index].judul, dataBuku[jenisBuku][index].hargaAsli, dataBuku[jenisBuku][index].hargaDiskon, dataBuku[jenisBuku][index].penerbit, dataBuku[jenisBuku][index].penulis, dataBuku[jenisBuku][index].stok, dataBuku[jenisBuku][index].kode);
        }
        fclose(writeEdukasi);
    }

    jenisBuku++;

    if (fileInvalid[4] == 0)
    {
        for (int index = 0; index < jumlahBuku[5]; index++)
        {
            fprintf(writeMajalah, "%s|%d|%d|%s|%s|%d|%s\n", dataBuku[jenisBuku][index].judul, dataBuku[jenisBuku][index].hargaAsli, dataBuku[jenisBuku][index].hargaDiskon, dataBuku[jenisBuku][index].penerbit, dataBuku[jenisBuku][index].penulis, dataBuku[jenisBuku][index].stok, dataBuku[jenisBuku][index].kode);
        }
        fclose(writeMajalah);
    }

    /* Data pembelian*/
    FILE *writePembelian = fopen("Pembeli.txt", "w");
    FILE *writeKeranjang = fopen("Keranjang.txt", "w");

    if (fileInvalid[5] == 0)
    {
        for (int index = 0; index < pembeliKe; index++)
        {
            fprintf(writePembelian, "%s|%d|%d|%d|%d|%s\n", dataPembeli[index].nama, dataPembeli[index].totalBuku, dataPembeli[index].totalHarga, dataPembeli[index].metodePembayaran, dataPembeli[index].jumlahJenis, dataPembeli[index].tanggal);
        }
        fclose(writePembelian);
    }

    int orangKe = 0;

    if (fileInvalid[6] == 0)
    {
        for (int orangKe = 0; orangKe < pembeliKe; orangKe++)
        {
            for (int index = 0; index < dataPembeli[orangKe].jumlahJenis; index++)
            {
                fprintf(writeKeranjang, "%d|%d|%d|%d|%d|%d|%d\n", keranjang[orangKe][index].diskonCheck, keranjang[orangKe][index].hargaSatuan, keranjang[orangKe][index].hargaAsli_total, keranjang[orangKe][index].hargaDiskon_total, keranjang[orangKe][index].total, keranjang[orangKe][index].genre, keranjang[orangKe][index].index);
            }
        }
        fclose(writeKeranjang);
    }
}

void salesHistory(int urutan)
{
    int z = pembeliKe;
    int ii;
    int urut = 0;
    char tanya;
    char input;
    clearScreen();
    if (fileInvalid[5] == 1 || fileInvalid[6] == 1)
    {
        printf("Data tidak ditemukan!\n");
        backToMainMenu();
    }
    else
    {
        if (urutan == 0)
        {
            printf("1. Terbaru Ke Terlama\n");
            printf("2. Terlama ke Terbaru\n");
            while (urut != 1 && urut != 2)
            {
                printf("Pilih urutan tanggal yang diinginkan: ");
                scanf("%d", &urut);
                getchar();
                if (urut != 1 && urut != 2)
                {
                    printf("Maaf, input tidak dikenali\n");
                }
            }
            clearScreen();
            printf("Laporan Penjualan Berdasarkan Tanggal Transaksi\n");
            printf("Total Pendapatan       : Rp.%lld\n\n", totalPendapatan);
            if (urut == 1)
            {
                int ii;
                for (int i = pembeliKe - 1, ii = 1; i >= 0, ii <= pembeliKe; i--, ii++)
                {
                    printf("Pembeli Ke             : %d\n", ii);
                    printf("Tanggal Transaksi      : %s\n", dataPembeli[i].tanggal);
                    printf("Nama Pelanggan         : %s\n", dataPembeli[i].nama);
                    printf("Metode Pembayaran      : %s\n", pembayaranString[dataPembeli[i].metodePembayaran - 1]);
                    printf("Total Pembayaran       : Rp.%lld\n", dataPembeli[i].totalHarga);
                    printf("Daftar Pembelian       :\n\n");

                    int oo;
                    for (int j = dataPembeli[i].jumlahJenis - 1, oo = 1; j >= 0, oo <= dataPembeli[i].jumlahJenis; j--, oo++)
                    {
                        printf("\tBuku ke                : %d\n", oo);
                        printf("\tJudul - Kode Buku      : %s - %s\n", dataBuku[keranjang[i][j].genre][keranjang[i][j].index].judul, dataBuku[keranjang[i][j].genre][keranjang[i][j].index].kode);

                        printf("\tTotal Buku yang dibeli : %d\n", keranjang[i][j].total);
                        if (keranjang[i][j].diskonCheck == 1)
                        {
                            printf("\tHarga Satuan           : Rp.%d\n", keranjang[i][j].hargaSatuan);
                            printf("\tTotal Harga            : Rp.%d\n\n", keranjang[i][j].hargaAsli_total);
                        }
                        else
                        {
                            printf("\tHarga Satuan (Diskon)  : Rp.%d\n", keranjang[i][j].hargaSatuan);
                            printf("\tTotal Harga            : Rp.%d\n\n", keranjang[i][j].hargaDiskon_total);
                        }
                    }
                }
            }
            else if (urut == 2)
            {
                for (int i = 0; i < pembeliKe; i++)
                {
                    printf("Pembeli Ke             : %d\n", i + 1);
                    printf("Tanggal Transaksi      : %s\n", dataPembeli[i].tanggal);
                    printf("Nama Pelanggan         : %s\n", dataPembeli[i].nama);
                    printf("Metode Pembayaran      : %s\n", pembayaranString[dataPembeli[i].metodePembayaran - 1]);
                    printf("Total Pembayaran       : Rp.%lld\n", dataPembeli[i].totalHarga);
                    printf("Daftar Pembelian       :\n\n");

                    for (int j = 0; j < dataPembeli[i].jumlahJenis; j++)
                    {
                        printf("\tBuku ke                : %d\n", j + 1);
                        printf("\tJudul - Kode Buku      : %s - %s\n", dataBuku[keranjang[i][j].genre][keranjang[i][j].index].judul, dataBuku[keranjang[i][j].genre][keranjang[i][j].index].kode);

                        printf("\tTotal Buku yang dibeli : %d\n", keranjang[i][j].total);
                        if (keranjang[i][j].diskonCheck == 1)
                        {
                            printf("\tHarga Satuan           : Rp.%d\n", keranjang[i][j].hargaSatuan);
                            printf("\tTotal Harga            : Rp.%d\n\n", keranjang[i][j].hargaAsli_total);
                        }
                        else
                        {
                            printf("\tHarga Satuan (Diskon)  : Rp.%d\n", keranjang[i][j].hargaSatuan);
                            printf("\tTotal Harga            : Rp.%d\n\n", keranjang[i][j].hargaDiskon_total);
                        }
                    }
                }
            }
        }

        else if (urutan == 1)
        {
        tanyaPembeli:
            pembeliKe = z;
            printf("Tampilkan data pembeli? (Y/N): ");
            scanf("%c", &tanya);
            getchar();
            if (tolower(tanya) != 'y' && tolower(tanya) != 'n')
            {
                printf("Maaf, input tidak dikenali\n");
                pauseScreen();
                goto tanyaPembeli;
            }

            printf("Laporan Penjualan Berdasarkan Buku Terpopuler\n");
            printf("Total Pendapatan       : Rp.%lld\n", totalPendapatan);
            // Menghitung jumlah judul buku
            int jumlahJudul = 0;
            for (int x = 1; x <= 5; x++)
            {
                jumlahJudul += jumlahBuku[x];
            }

            // sorting
            int terjual[jumlahJudul + 1];
            int x = 0;
            int checker[6][25];
            for (int i = 1; i < 6; i++)
            {
                for (int j = 0; j < jumlahBuku[i]; j++)
                {
                    terjual[x++] = dataBuku[i][j].terjual;
                    checker[i][j] = 0;
                }
            }
            quicksort(terjual, 0, jumlahJudul - 1);
            x = 0;

            for (int p = 0; p < jumlahJudul; p++)
            {
                for (int i = 1; i < 6; i++)
                {
                    for (int j = 0; j < jumlahBuku[i]; j++)
                    {

                        if (checker[i][j] == 0)
                        {
                            if (dataBuku[i][j].terjual == terjual[x])
                            {
                                printf("\nBuku Ke          : %d\n", x + 1);
                                printf("Genre            : %s\n", headerGenre[i - 1]);
                                printf("Judul - Kode     : %s - %s\n", dataBuku[i][j].judul, dataBuku[i][j].kode);
                                printf("Terjual          : %d\n", dataBuku[i][j].terjual);
                                printf("Total Harga      : Rp.%lld\n", dataBuku[i][j].hargaTerjual);
                                if (tolower(tanya) == 'y' && dataBuku[i][j].terjual != 0)
                                {
                                    printf("Data Pelanggan   : \n\n");
                                    printf("(No. Nama - Tanggal - Jumlah Buku - Total Harga)\n");
                                    int pp = 0;
                                    for (int k = pembeliKe - 1; k >= 0; k--)
                                    {
                                        for (int l = 0; l < dataPembeli[k].jumlahJenis; l++)
                                        {
                                            if (keranjang[k][l].genre == i && keranjang[k][l].index == j)
                                            {
                                                printf("%d. %s - %s - %d - Rp.", pp + 1, dataPembeli[k].nama, dataPembeli[k].tanggal, keranjang[k][l].total);
                                                if (keranjang[i][j].diskonCheck == 1)
                                                {
                                                    printf("%lld\n", keranjang[k][l].hargaAsli_total);
                                                }
                                                else
                                                {
                                                    printf("%lld\n", keranjang[k][l].hargaDiskon_total);
                                                }
                                                pp++;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    printf("\n");
                                }

                                checker[i][j] = 1;
                                x++;
                            }
                        }
                    }
                }
            }
        }

    konfirmasiCetak:
        printf("\nApakah ingin dicetak dalam file? (Y/N): ");
        scanf("%c", &input);
        getchar();
        if (tolower(input) == 'y')
        {
            simpanKeFileSalesHistory(urutan, tanya, z, urut);
            printf("Berhasil dicetak\n");
        }
        else if (tolower(input) != 'n')
        {
            goto konfirmasiCetak;
        }
        backToMainMenu();
    }
}

void simpanKeFileSalesHistory(int urutan, int tanya, int z, int urut)
{
    FILE *writeSales = fopen("sales.txt", "w+");
    if (urutan == 0)
    {
        fprintf(writeSales, "Laporan Penjualan Berdasarkan Tanggal Transaksi\n");
        fprintf(writeSales, "Total Pendapatan       : Rp.%lld\n\n", totalPendapatan);
        if (urut == 1)
        {
            int ii;
            for (int i = pembeliKe - 1, ii = 1; i >= 0, ii <= pembeliKe; i--, ii++)
            {

                fprintf(writeSales, "Pembeli Ke             : %d\n", ii);
                fprintf(writeSales, "Tanggal Transaksi      : %s\n", dataPembeli[i].tanggal);
                fprintf(writeSales, "Nama Pelanggan         : %s\n", dataPembeli[i].nama);
                fprintf(writeSales, "Metode Pembayaran      : %s\n", pembayaranString[dataPembeli[i].metodePembayaran - 1]);
                fprintf(writeSales, "Total Pembayaran       : Rp.%lld\n", dataPembeli[i].totalHarga);
                fprintf(writeSales, "Daftar Pembelian       :\n\n");

                int oo;
                for (int j = dataPembeli[i].jumlahJenis - 1, oo = 1; j >= 0, oo <= dataPembeli[i].jumlahJenis; j--, oo++)
                {
                    fprintf(writeSales, "\tBuku ke                : %d\n", oo);
                    fprintf(writeSales, "\tJudul - Kode Buku      : %s - %s\n", dataBuku[keranjang[i][j].genre][keranjang[i][j].index].judul, dataBuku[keranjang[i][j].genre][keranjang[i][j].index].kode);

                    fprintf(writeSales, "\tTotal Buku yang dibeli : %d\n", keranjang[i][j].total);
                    if (dataBuku[keranjang[i][j].genre][keranjang[i][j].index].hargaDiskon == 0)
                    {
                        fprintf(writeSales, "\tHarga Satuan           : Rp.%d\n", dataBuku[keranjang[i][j].genre][keranjang[i][j].index].hargaAsli);
                        fprintf(writeSales, "\tTotal Harga            : Rp.%d\n\n", keranjang[i][j].hargaAsli_total);
                    }
                    else
                    {
                        fprintf(writeSales, "\tHarga Satuan (Diskon)  : Rp.%d\n", dataBuku[keranjang[i][j].genre][keranjang[i][j].index].hargaDiskon);
                        fprintf(writeSales, "\tTotal Harga            : Rp.%d\n\n", keranjang[i][j].hargaDiskon_total);
                    }
                }
            }
        }
        else if (urut == 2)
        {
            for (int i = 0; i < pembeliKe; i++)
            {

                fprintf(writeSales, "Pembeli Ke             : %d\n", i + 1);
                fprintf(writeSales, "Tanggal Transaksi      : %s\n", dataPembeli[i].tanggal);
                fprintf(writeSales, "Nama Pelanggan         : %s\n", dataPembeli[i].nama);
                fprintf(writeSales, "Metode Pembayaran      : %s\n", pembayaranString[dataPembeli[i].metodePembayaran - 1]);
                fprintf(writeSales, "Total Pembayaran       : Rp.%lld\n", dataPembeli[i].totalHarga);
                fprintf(writeSales, "Daftar Pembelian       :\n\n");

                for (int j = 0; j < dataPembeli[i].jumlahJenis; j++)
                {
                    fprintf(writeSales, "\tBuku ke                : %d\n", j + 1);
                    fprintf(writeSales, "\tJudul - Kode Buku      : %s - %s\n", dataBuku[keranjang[i][j].genre][keranjang[i][j].index].judul, dataBuku[keranjang[i][j].genre][keranjang[i][j].index].kode);

                    fprintf(writeSales, "\tTotal Buku yang dibeli : %d\n", keranjang[i][j].total);
                    if (keranjang[i][j].diskonCheck == 1)
                    {
                        fprintf(writeSales, "\tHarga Satuan           : Rp.%d\n", keranjang[i][j].hargaSatuan);
                        fprintf(writeSales, "\tTotal Harga            : Rp.%d\n\n", keranjang[i][j].hargaAsli_total);
                    }
                    else
                    {
                        fprintf(writeSales, "\tHarga Satuan (Diskon)  : Rp.%d\n", keranjang[i][j].hargaSatuan);
                        fprintf(writeSales, "\tTotal Harga            : Rp.%d\n\n", keranjang[i][j].hargaDiskon_total);
                    }
                }
            }
        }
    }

    else if (urutan == 1)
    {
        pembeliKe = z;
        fprintf(writeSales, "Tampilkan data pembeli? (Y/N): %c\n", tanya);
        fprintf(writeSales, "Laporan Penjualan Berdasarkan Buku Terpopuler\n");
        fprintf(writeSales, "Total Pendapatan       : Rp.%lld\n", totalPendapatan);
        // Menghitung jumlah judul buku
        int jumlahJudul = 0;
        for (int x = 1; x <= 5; x++)
        {
            jumlahJudul += jumlahBuku[x];
        }

        // sorting
        int terjual[jumlahJudul + 1];
        int x = 0;
        int checker[6][25];
        for (int i = 1; i < 6; i++)
        {
            for (int j = 0; j < jumlahBuku[i]; j++)
            {
                terjual[x++] = dataBuku[i][j].terjual;
                checker[i][j] = 0;
            }
        }
        quicksort(terjual, 0, jumlahJudul - 1);
        x = 0;
        x = 0;

        for (int p = 0; p < jumlahJudul; p++)
        {
            for (int i = 1; i < 6; i++)
            {
                for (int j = 0; j < jumlahBuku[i]; j++)
                {

                    if (checker[i][j] == 0)
                    {
                        if (dataBuku[i][j].terjual == terjual[x])
                        {
                            fprintf(writeSales, "\nBuku Ke          : %d\n", x + 1);
                            fprintf(writeSales, "Genre            : %s\n", headerGenre[i - 1]);
                            fprintf(writeSales, "Judul - Kode     : %s - %s\n", dataBuku[i][j].judul, dataBuku[i][j].kode);
                            fprintf(writeSales, "Terjual          : %d\n", dataBuku[i][j].terjual);
                            fprintf(writeSales, "Total Harga      : Rp.%lld\n", dataBuku[i][j].hargaTerjual);
                            if (tolower(tanya) == 'y' && dataBuku[i][j].terjual != 0)
                            {
                                fprintf(writeSales, "Data Pelanggan   : \n\n");
                                fprintf(writeSales, "(No. Nama - Tanggal - Jumlah Buku - Total Harga)\n");
                                int pp = 0;
                                for (int k = pembeliKe - 1; k >= 0; k--)
                                {
                                    for (int l = 0; l < dataPembeli[k].jumlahJenis; l++)
                                    {
                                        if (keranjang[k][l].genre == i && keranjang[k][l].index == j)
                                        {
                                            fprintf(writeSales, "%d. %s - %s - %d - Rp.", pp + 1, dataPembeli[k].nama, dataPembeli[k].tanggal, keranjang[k][l].total);
                                            if (keranjang[i][j].diskonCheck == 1)
                                            {
                                                fprintf(writeSales, "%lld\n", keranjang[k][l].hargaAsli_total);
                                            }
                                            else
                                            {
                                                fprintf(writeSales, "%lld\n", keranjang[k][l].hargaDiskon_total);
                                            }
                                            pp++;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                fprintf(writeSales, "\n");
                            }

                            checker[i][j] = 1;
                            x++;
                        }
                    }
                }
            }
        }
    }
    fclose(writeSales);
}

void quicksort(int terjual[], int left, int right)
{
    int i = left;
    int j = right;
    int temp = terjual[i];

    if (left < right)
    {
        while (i < j)
        {
            while (terjual[j] <= temp && i < j)
            {
                j--;
            }
            terjual[i] = terjual[j];

            while (terjual[i] >= temp && i < j)
            {
                i++;
            }
            terjual[j] = terjual[i];
        }
        terjual[i] = temp;

        quicksort(terjual, left, i - 1);
        quicksort(terjual, j + 1, right);
    }
}

void peringatanFileInvalid()
{
    int headerSudahDiPrint = 0;

    for (int i = 0; i <= 5; i++)
    {
        if (fileInvalid[i] == 1)
        {
            if (headerSudahDiPrint == 0)
            {
                headerSudahDiPrint = 1;
                printf("File bermasalah :\n");
            }
            printf("\t- %s\n", stringNamaFile[i]);
        }
    }
    if (headerSudahDiPrint == 1)
        printf("Silahkan hubungi admin\n\n");
}

void menuUtama()
{
    int input;
    clearScreen();
    peringatanFileInvalid(); // Check file invalid (kosong / error)
    printf("Smart Toko Buku App\n");
    printf("------\n");
    printf("1. List Buku dari Database\n");
    printf("2. Beli Buku\n");
    printf("3. Cari Buku\n");
    printf("4. Ubah Stok Buku\n");
    printf("5. Ubah Harga Buku\n");
    printf("6. Tambah Buku\n");
    printf("7. Tampilkan History berdasarkan Tanggal\n");
    printf("8. Tampilkan History berdasarkan terlaris\n");

    printf("99. Exit\n");
    printf("------\n\n");

    printf("Mau ke mana?: ");
    scanf("%d", &input);
    getchar();
    if (input == 1)
    {
        clearScreen();
        listBuku(1);
    }
    else if (input == 2)
    {

        clearScreen();
        menuPembelian();
    }
    else if (input == 3)
    {
        clearScreen();
        search();
    }
    else if (input == 4)
    {
        clearScreen();
        listBuku(3);
    }
    else if (input == 5)
    {
        clearScreen();
        listBuku(4);
    }
    else if (input == 6)
    {
        clearScreen();
        tambahBuku();
    }
    else if (input == 7)
    {
        salesHistory(0);
    }
    else if (input == 8)
    {
        salesHistory(1);
    }

    else if (input == 99)
    {
        printf("Menyimpan data ke database\n");
        printf("Tunggu sebentar\n");
        simpanKeFileDB();
        exit(0);
    }
    else
    {
        printf("Maaf, input tidak dikenali\n");
        backToMainMenu();
    }
}

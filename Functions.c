#include "Functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


//fungsi untuk membuat database
void create_database(){
	FILE *file;
	int size, i ,j = 0, check = 0;
	mahasiswa *mhs;
	float temp_komponen, temp_total = 0;
	system("cls");
	printf("Berapa banyak mahasiswa?:");
	scanf("%d", &size);//meminta size mahasiswa
	while(size < 0){//error handling
		printf("Input invalid!\n");
		printf("Berapa banyak mahasiswa?:");
		scanf("%d", &size);
	}
	mhs = (mahasiswa*)malloc(size*sizeof(mahasiswa));//alokasi memori
	if(mhs == NULL){
		printf("Memori tidak dialokasikan!\n");
		exit(0);
	}
	file = fopen("DATABASE.txt", "w");//membuka atau membuat file dengan nama DATABASE.txt
	for(i = 0; i < size; i++){
		temp_total = 0;
		system("cls");
		printf("Masukkan nomor absen: ");//input absen
		scanf("%d", &mhs[i].no_absen);
		fflush(stdin);
		while(mhs[i].no_absen <= 0){
			printf("Input invalid!\n");
			printf("Masukkan nomor absen: ");
			scanf("%d", &mhs[i].no_absen);
			fflush(stdin);
		}
		printf("Masukkan nama: ");
		scanf("%[^\n]s", mhs[i].nama);//input nama
		printf("Masukkan npm: ");
		scanf("%u", &mhs[i].npm);//input npm
		while(mhs[i].npm < 0){
			printf("Input invalid!\n");
			printf("Masukkan npm: ");
			scanf("%u", &mhs[i].npm);
		}
		//meminta input nilai kuis dan menampung di variabel temp_komponen dan temp_total
		for(j = 0; j < 4; j++){
			printf("Masukkan nilai kuis ke - %d: ", j+1);
			scanf("%f", &temp_komponen);
			while(temp_komponen < 0 || temp_komponen > 100){
				printf("Input invalid!\n");
				printf("Masukkan nilai kuis ke - %d: ", j+1);
				scanf("%f", &temp_komponen);
			}
			temp_total += temp_komponen; 
		}
		mhs[i].nilai.kuis = temp_total / 4.0;//assign nilai kuis
		printf("Masukkan nilai UTS: ");
		scanf("%f", &mhs[i].nilai.uts);//input nilai uts
		while(mhs[i].nilai.uts < 0 || mhs[i].nilai.uts > 100){
			printf("Input invalid!\n");
			printf("Masukkan nilai UTS: ");
			scanf("%f", &mhs[i].nilai.uts);
		}
		printf("Masukkan nilai UAS: ");
		scanf("%f", &mhs[i].nilai.uas);//input nilai uas
		while(mhs[i].nilai.uas < 0 || mhs[i].nilai.uas > 100){
			printf("Input invalid!\n");
			printf("Masukkan nilai UAS: ");
			scanf("%f", &mhs[i].nilai.uas);
		}
		temp_total = 0;
		//meminta input nilai praktikum
		for(j = 0; j < 10; j++){
			printf("Masukkan nilai praktikum modul - %d: ", j+1);
			scanf("%f", &temp_komponen);
			while(temp_komponen < 0 || temp_komponen > 100){
				printf("Input invalid!\n");
				printf("Masukkan nilai kuis ke - %d: ", j+1);
				scanf("%f", &temp_komponen);
			}
			temp_total += temp_komponen;
		}
		mhs[i].nilai.praktikum = temp_total / 10.0;//assign nilai praktikum
		temp_total = 0;
		//input nilai tugas
		for(j = 0; j < 10; j++){
			printf("Masukkan nilai tugas ke - %d: ", j+1);
			scanf("%f", &temp_komponen);
			while(temp_komponen < 0 || temp_komponen > 100){
				printf("Input invalid!\n");
				printf("Masukkan nilai kuis ke - %d: ", j+1);
				scanf("%f", &temp_komponen);
			}
			temp_total += temp_komponen;
		}
		mhs[i].nilai.tugas = temp_total / 10.0;//assign nilai tugas
		printf("Masukkan nilai proyek akhir: ");
		scanf("%f", &mhs[i].nilai.proyek);//input nilai akhir
		while(mhs[i].nilai.proyek < 0 || mhs[i].nilai.proyek > 100){
			printf("Input invalid!\n");
			printf("Masukkan nilai proyek akhir: ");
			scanf("%f", &mhs[i].nilai.proyek);
		}
		mhs[i].nilai.total = mhs[i].nilai.kuis * 0.1 + mhs[i].nilai.uts * 0.2;
		mhs[i].nilai.total += mhs[i].nilai.uas * 0.25 + mhs[i].nilai.praktikum * 0.15;
		mhs[i].nilai.total += mhs[i].nilai.tugas * 0.1 + mhs[i].nilai.proyek * 0.2;//input nilai total sesuai persentase BRP
		mhs[i].nilai.nilai_huruf = add_char_grade(mhs[i].nilai.total);//meminta return nilai huruf dari nilai total
		fwrite(&mhs[i], sizeof(mahasiswa), 1, file);
	}
	system("cls");
	fclose(file);//save file
}

//fungsi untuk menampilkan database
void display_database(){
	FILE *file;
	mahasiswa mhs;
	file = fopen("DATABASE.txt", "r");
	printf("%s%12s%16s%35s%16s%17s%12s%15s%16s%19s%15s", "No.Absen", "NPM", "Nama", "Kuis", "tugas", "praktikum", "UTS", "UAS", "Proyek", "Nilai Akhir", "Nilai Huruf");
	while(fread(&mhs, sizeof(mahasiswa), 1, file)){//print selama data ada
		printf("\n%3d%19u%10s%-30s", mhs.no_absen, mhs.npm, "", mhs.nama);
		printf("%10.2f%15.2f%15.2f%15.2f%15.2f%15.2f%16.2f%14s", mhs.nilai.kuis, mhs.nilai.tugas, mhs.nilai.praktikum, mhs.nilai.uts, mhs.nilai.uas, mhs.nilai.proyek, mhs.nilai.total, mhs.nilai.nilai_huruf);
	}
	printf("\n");
	fclose(file);
}

//fungsi untuk menambahkan data, mirip dengan create_database, hanya beda di cara membuka filenya, yaitu dengan mode 'a' atau append
void append_database(){
	FILE *file;
	int size, i ,j;
	char temp[30];
	mahasiswa *mhs;
	float temp_komponen, temp_total = 0;
	system("cls");
	printf("Berapa banyak mahasiswa?:");
	scanf("%d", &size);
	while(size < 0){
		printf("Input invalid!");
		printf("Berapa banyak mahasiswa?:");
		scanf("%d", &size);
	}
	mhs = (mahasiswa*)malloc(size*sizeof(mahasiswa));
	if(mhs == NULL){
		printf("Memori tidak dialokasikan!\n");
		exit(0);
	}
	file = fopen("DATABASE.txt", "a");//DISINI
	for(i = 0; i < size; i++){
		temp_total = 0;
		system("cls");
		printf("Masukkan nomor absen: ");
		scanf("%d", &mhs[i].no_absen);
		fflush(stdin);
		while(mhs[i].no_absen <= 0){
			printf("Input invalid!\n");
			printf("Masukkan nomor absen: ");
			scanf("%d", &mhs[i].no_absen);
			fflush(stdin);
		}
		printf("Masukkan nama: ");
		scanf("%[^\n]s", mhs[i].nama);
		printf("Masukkan npm: ");
		scanf("%u", &mhs[i].npm);
		while(mhs[i].npm < 0){
			printf("Input invalid!\n");
			printf("Masukkan npm: ");
			scanf("%u", &mhs[i].npm);
		}
		for(j = 0; j < 4; j++){
			printf("Masukkan nilai kuis ke - %d: ", j+1);
			scanf("%f", &temp_komponen);
			while(temp_komponen < 0 || temp_komponen > 100){
				printf("Input invalid!\n");
				printf("Masukkan nilai kuis ke - %d: ", j+1);
				scanf("%f", &temp_komponen);
			}
			temp_total += temp_komponen; 
		}
		mhs[i].nilai.kuis = temp_total / 4.0;
		printf("Masukkan nilai UTS: ");
		scanf("%f", &mhs[i].nilai.uts);
		while(mhs[i].nilai.uts < 0 || mhs[i].nilai.uts > 100){
			printf("Input invalid!\n");
			printf("Masukkan nilai UTS: ");
			scanf("%f", &mhs[i].nilai.uts);
		}
		printf("Masukkan nilai UAS: ");
		scanf("%f", &mhs[i].nilai.uas);
		while(mhs[i].nilai.uas < 0 || mhs[i].nilai.uas > 100){
			printf("Input invalid!\n");
			printf("Masukkan nilai UAS: ");
			scanf("%f", &mhs[i].nilai.uas);
		}
		temp_total = 0;
		for(j = 0; j < 10; j++){
			printf("Masukkan nilai praktikum modul - %d: ", j+1);
			scanf("%f", &temp_komponen);
			while(temp_komponen < 0 || temp_komponen > 100){
				printf("Input invalid!\n");
				printf("Masukkan nilai kuis ke - %d: ", j+1);
				scanf("%f", &temp_komponen);
			}
			temp_total += temp_komponen;
		}
		mhs[i].nilai.praktikum = temp_total / 10.0;
		temp_total = 0;
		for(j = 0; j < 10; j++){
			printf("Masukkan nilai tugas ke - %d: ", j+1);
			scanf("%f", &temp_komponen);
			while(temp_komponen < 0 || temp_komponen > 100){
				printf("Input invalid!\n");
				printf("Masukkan nilai kuis ke - %d: ", j+1);
				scanf("%f", &temp_komponen);
			}
			temp_total += temp_komponen;
		}
		mhs[i].nilai.tugas = temp_total / 10.0;
		printf("Masukkan nilai proyek akhir: ");
		scanf("%f", &mhs[i].nilai.proyek);
		while(mhs[i].nilai.proyek < 0 || mhs[i].nilai.proyek > 100){
			printf("Input invalid!\n");
			printf("Masukkan nilai proyek akhir: ");
			scanf("%f", &mhs[i].nilai.proyek);
		}
		mhs[i].nilai.total = mhs[i].nilai.kuis * 0.1 + mhs[i].nilai.uts * 0.2;
		mhs[i].nilai.total += mhs[i].nilai.uas * 0.25 + mhs[i].nilai.praktikum * 0.15;
		mhs[i].nilai.total += mhs[i].nilai.tugas * 0.1 + mhs[i].nilai.proyek * 0.2;
		mhs[i].nilai.nilai_huruf = add_char_grade(mhs[i].nilai.total);
		fwrite(&mhs[i], sizeof(mahasiswa), 1, file);
	}
	system("cls");
	fclose(file);
}

//fungsi untuk menampilkan banyak data mahasiswa
void frequency_data(){
	int size;
	FILE *file;
	file = fopen("DATABASE.txt", "r");//open file dengan mode read
	fseek(file, 0, SEEK_END);//point sampai akhir
	size = ftell(file)/sizeof(mahasiswa);//mencari berapa banyak mahasiswa
	printf("Ada %d data mahasiswa di dalam database\n", size);
	fclose(file);
}

//fungsi untuk menghapus data mahasiswa
void delete_data(){
	mahasiswa mhs;
	int found = 0;
	FILE *file, *file1;//ada file baru untuk menampung data sementara
	int size, no_absen, check;
	file = fopen ("DATABASE.txt", "r");
	file1 = fopen ("TEMP.txt", "w");
	printf("Masukkan nomor absen yang ingin dihapus: ");
	scanf("%d", &no_absen);
	while(no_absen <= 0){
		printf("Input invalid!\n");
		printf("Masukkan nomor absen yang ingin dihapus: ");
		scanf("%d", &no_absen);
	}
	while (fread(&mhs, sizeof(mahasiswa), 1, file)){//membaca data pada file
		if(mhs.no_absen == no_absen){
			found=1;
		}else{
			fwrite(&mhs, sizeof(mahasiswa), 1, file1);
			/*menampung data sementara mahasiswa pada file1 dimana
			nomor absen mahasiswa tidak sama dengan nomor absen yang ingin dihapus
			*/
		}
	}
	fclose(file);
	fclose(file1);
	file1 = fopen("TEMP.txt", "r");
	file = fopen("DATABASE.txt", "w");
	if(found == 1){
		while(fread(&mhs, sizeof(mahasiswa), 1, file1)){//menaruh kembali data yang ada di file1 ke file
			fwrite(&mhs, sizeof(mahasiswa),1, file);
		}
	}
	fclose(file);
	fclose(file1);
}

//fungsi untuk sorting dengan nilai
void sort_database_Bygrade(int num){
	mahasiswa *mhs, temp;
	int size, i, j;
	FILE *file;
	file = fopen("DATABASE.txt", "r");//membuka data file
	fseek(file, 0, SEEK_END);//point ke akhir
	size = ftell(file)/sizeof(mahasiswa);//mencari size
	mhs = (mahasiswa*)malloc(size*sizeof(mahasiswa));
	rewind(file);//point file ke awal lagi
	for(i = 0; i < size; i++){
		fread(&mhs[i], sizeof(mahasiswa), 1, file);//membaca data file dan memasukkannya ke mhs[i]
	}
	fclose(file);
	//descending
	if(num == 1){
		for (i=0; i<size; i++){
			for (j = i+1; j<size; j++){
				if(mhs[i].nilai.total < mhs[j].nilai.total){
					temp = mhs[i];
					mhs[i] = mhs[j];
					mhs[j] = temp;
				}
			}
		}
	//ascending
	}else{
		for (i=0; i<size; i++){
			for (j = i+1; j<size; j++){
				if(mhs[i].nilai.total > mhs[j].nilai.total){
					temp = mhs[i];
					mhs[i] = mhs[j];
					mhs[j] = temp;
				}
			}
		}
	}
	file = fopen("DATABASE.txt", "w");
	for(i = 0; i < size; i++){
		fwrite(&mhs[i], sizeof(mahasiswa), 1, file);
	}
	fclose(file);
}

//mirip dengan fungsi sort_database_Bygrade tapi ini nomor absen
void sort_database_Byabsen(int num){
	mahasiswa *mhs, temp;
	int size, i, j, check;
	FILE *file;
	file = fopen("DATABASE.txt", "r");
	fseek(file, 0, SEEK_END);
	size = ftell(file)/sizeof(mahasiswa);
	mhs = (mahasiswa*)malloc(size*sizeof(mahasiswa));
	rewind(file);
	for(i = 0; i < size; i++){
		fread(&mhs[i], sizeof(mahasiswa), 1, file);
	}
	fclose(file);
	if(num == 1){
		for (i=0; i<size; i++){
			for (j = i+1; j<size; j++){
				if(mhs[i].no_absen < mhs[j].no_absen){
					temp = mhs[i];
					mhs[i] = mhs[j];
					mhs[j] = temp;
				}
			}
		}
	}else{
		for (i=0; i<size; i++){
			for (j = i+1; j<size; j++){
				if(mhs[i].no_absen > mhs[j].no_absen){
					temp = mhs[i];
					mhs[i] = mhs[j];
					mhs[j] = temp;
				}
			}
		}
	}
	file = fopen("DATABASE.txt", "w");
	for(i = 0; i < size; i++){
		fwrite(&mhs[i], sizeof(mahasiswa), 1, file);
	}
	fclose(file);	
}

//fungsi untuk me-return nilai huruf dari nilai total
char *add_char_grade(int num){
	if(num >= 85){
		return "A";
	}else if(num >= 80 && num < 85){
		return "A-";
	}else if(num >= 75 && num < 80){
		return "B+";
	}else if(num >= 70 && num < 75){
		return "B";
	}else if(num >= 65 && num < 70){
		return "B-";
	}else if(num >= 60 && num < 65){
		return "C+";
	}else if(num >= 55 && num < 60){
		return "C";
	}else if(num >= 40 && num < 55){
		return "D";
	}else{
		return "E";
	}
}

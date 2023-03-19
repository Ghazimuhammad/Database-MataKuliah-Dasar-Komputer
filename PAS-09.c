#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Functions.h"

/*
	program database nilai mata kuliah dasar komputer
	programmer: Muhammad Taqiyuddin Al Ghazi (2106707044)
	Tanggal: 07-12-2022
	Versi: 1.0
*/


int main(){
	int mode, cont = 1, pilihan;
	do{
		//pemilihan mode-mode database
		printf("1.Membuat database\n2.Menampilkan database\n");
		printf("3.Menambah database\n4.Menampilkan berapa banyak data\n5.Delete data\n");
		printf("6.Mengurutkan data dari nilai\n7.Mengurutkan data dari absen\n0.Keluar\n");
		printf("mode: ");
		scanf("%d", &mode);
		switch(mode){
			case 1:
				create_database();
				break;
			case 2:
				system("cls");
				display_database();
				break;
			case 3:
				system("cls");
				append_database();
				break;
			case 4:
				system("cls");
				frequency_data();
				break;
			case 5:
				system("cls");
				delete_data();
				printf("Delete data berhasil!\nSilahkan lihat di display database\n");
				break;
			case 6:
				system("cls");
				do{
					printf("1. descending\n2. ascending\nPilihan: ");
					scanf("%d", &pilihan);	
				}while(pilihan != 1 && pilihan != 2);
				sort_database_Bygrade(pilihan);
				break;
			case 7:
				system("cls");
				do{
					printf("1. descending\n2. ascending\nPilihan: ");
					scanf("%d", &pilihan);	
				}while(pilihan != 1 && pilihan != 2);
				sort_database_Byabsen(pilihan);
				break;
		}
		if(mode != 0){
			printf("Lanjut? (0. untuk berhenti): ");
			scanf("%d", &cont);
			system("cls");
		}
	}while(mode != 0 && cont != 0);
	return 0;
}

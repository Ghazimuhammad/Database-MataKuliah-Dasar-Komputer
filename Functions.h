#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

typedef struct{
	int no_absen;
	unsigned int npm;
	char nama[30];
	struct{
		float kuis, uts, uas;
		float proyek, praktikum, tugas;
		float total;
		char *nilai_huruf;
	}nilai;
}mahasiswa;

void create_database();
void display_database();
void append_database();
void frequency_data();
void sort_database_Bygrade(int num);
char *add_char_grade(int num);
void sort_database_Byabsen(int num);
void delete_data();

#endif

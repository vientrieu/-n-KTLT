#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <wchar.h>
struct sinhvien {
	wchar_t *MSSV;
	wchar_t *hoten;
	wchar_t *khoa;
	int	namhoc;
	wchar_t *ngaysinh;
	wchar_t *email;
	wchar_t *hinhanh;
	wchar_t *mota;
	wchar_t *sothich;
};typedef struct sinhvien SV;
int DemSV(FILE *In)
{
	rewind(In);
	int dem = 0;
	wchar_t s;
	while (!feof(In))
	{
		s = fgetwc(In);
		if (s == L'\n')
		{
			dem++;
		}
	}
	return dem;
}
wchar_t *docdulieu(FILE*filein)
{
	wchar_t * thongtin=NULL;
	int i = 0;
	wchar_t data = fgetwc(filein);
	if (data == L'\"')
	{
		while (1)
		{
			thongtin = (wchar_t*)realloc(thongtin, (i + 1)*sizeof(wchar_t));
			data = fgetwc(filein);
			if (data == L'\"')
			{
				*(thongtin + i) = '\0';
				break;
			}
			*(thongtin + i) = data;
			i++;
		}
		fseek(filein, 1L, 1);
	}
	else
	{
		fseek(filein, -1L, 1);
		while (1)
		{
			thongtin = (wchar_t*)realloc(thongtin, (i + 1)*sizeof(wchar_t));
			data = fgetwc(filein);
			if (data == L',')
			{
				*(thongtin + i) = '\0';
				break;
			}
			*(thongtin + i) = data;
			i++;
		}
	}
	return thongtin;
}
int main()
{
	FILE*filein = fopen("ttt.csv", "r");
	int a=DemSV(filein);
	printf("So luong sinh vien la: %d", a);
	wchar_t *t;
	t= docdulieu(filein);
	wchar_t *t2;
	t2= docdulieu(filein);
	wchar_t *t3;
	t3 = docdulieu(filein);
	wprintf(L"%ls", t);
	fclose(filein);
	getch();
}
@@@@
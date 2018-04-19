#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <wchar.h>
#include <fcntl.h>
struct sinhvien {// tạo struct sinh viên
	wchar_t *MSSV;
	wchar_t *hoten;
	wchar_t *khoa;
	int	namhoc;
	wchar_t *ngaysinh;
	wchar_t *email;
	wchar_t *hinh;
	wchar_t *mota;
	wchar_t *sothich;
};typedef struct sinhvien sv;
int DemSV(FILE *filein)// đếm số sinh viên
{
	rewind(filein);
	int dem = 0;
	wchar_t s;
	while (!feof(filein))
	{
		s = fgetwc(filein);
		if (s == L'\n')
		{
			dem++;
		}
	}
	return dem;
}
wchar_t *docdulieu(FILE*filein)// đọc kiểu unicode
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
int docdulieuint(FILE* filein)
{
	int n = 0;
	if (fgetwc(filein) == '\"')
	{
		fwscanf(filein, L"%ld", &n);
		fseek(filein, 2L, 1);
	}
	else
	{
		fseek(filein, -1L, 1);
		fwscanf(filein, L"%ld", &n);
		fseek(filein, 1L, 1);
	}
	return n;
}
sv thongtin1sinhvien(FILE*filein)
{
	sv a;
	a.MSSV = docdulieu(filein);
	a.hoten = docdulieu(filein);
	a.khoa = docdulieu(filein);
	a.namhoc = docdulieuint(filein);
	a.ngaysinh = docdulieu(filein);
	a.email = docdulieu(filein);
	a.hinh = docdulieu(filein);
	a.mota = docdulieu(filein);
	a.sothich = docdulieu(filein);
	return a;
}
sv* thongtintoansinhvien(FILE*filein,int soSV)
{
	sv*S = (sv*)malloc((soSV)*sizeof(sv));
	for (int i = 0; i < soSV; i++)
	{
		*(S + i) = thongtin1sinhvien(filein);
	}
	return S;
}
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	FILE*filein = _wfopen(L"thongtin.csv", L"r, ccs=UTF-8");
	//wchar_t *t= docdulieu(filein);
	//wchar_t *t2= docdulieu(filein);
	//wchar_t *t3 = docdulieu(filein);
	//int nam = docdulieuint(filein);
	//wchar_t *t4 = docdulieu(filein);
	//wchar_t *t5 = docdulieu(filein);
	//wchar_t *t6= docdulieu(filein);
	//wchar_t *t7 = docdulieu(filein);
	//wchar_t *t8 = docdulieu(filein);
	int dem = DemSV(filein);
	fseek(filein, 3L, 0);
	sv *s = thongtintoansinhvien(filein,dem);
	for (int i = 0; i < dem; i++)
	{
		wprintf(L"%ls,%ls,%ls,%ld,%ls,%ls,%ls,%ls,%ls", (*(s + i)).MSSV, (*(s + i)).hoten, (*(s + i)).khoa, (*(s + i)).namhoc, (*(s + i)).ngaysinh, (*(s + i)).email, (*(s + i)).hinh, (*(s + i)).mota, (*(s + i)).sothich);
	}
	fclose(filein);
	//FILE*fileout = _wfopen(L"tt.txt", L"w,ccs=UTF-8");
	//fwprintf(fileout, L"%ls,%ls,%ls,%ld", t, t2, t3, nam);
	//fclose(fileout);
	w
	getch();
	return 0;
}
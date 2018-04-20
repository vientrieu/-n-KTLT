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
	wchar_t * thongtin = NULL;
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
		/*	if (data == L'\n')
			{
				*(thongtin + i+1) = '\0';
				break;
			}*/
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
int docdulieuint(FILE* filein)//đọc kiểu int
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
int timchuoi(wchar_t* cha, wchar_t* con, int start)
{
	int a = wcslen(cha);
	int b = wcslen(con);
	for (int i = start; i < a; i++)
	{
		int dem = 0;
		for (int j = 0; j < b; j++)
		{
			if (*(con + j) != *(cha + i + j)) break;
			else dem++;
		}
		if (dem == b) return i;
	}
	return -1;
}
void chenthongtin(wchar_t*chuoi, wchar_t*thay, int n, int vitri)
{
	int a = wcslen(chuoi);
	int b = wcslen(thay);
	if (n == 0) return;
	else if (n < 0)
	{
		for (int i = vitri; i < a; i++)
		{
			*(chuoi + i) = *(chuoi - n + i);
		}
	}
	else
	{
		for (int i = a - 1; i >= vitri; i--)
		{
			*(chuoi + i + n) = *(chuoi + i);
		}
	}
	for (int i = 0; i < b; i++)
	{
		*(chuoi + vitri + i) = *(thay + i);
	}
	*(chuoi + a + n) = '\0';
}
void thaydoitt(wchar_t*chuoi, wchar_t*dau, wchar_t*cuoi)
{
	int i = 0;
	int a = wcslen(dau);
	int b = wcslen(cuoi);
	while (*(chuoi ))
	{
		int vitri = timchuoi(chuoi, dau, 0);
		if (vitri == -1) return;
		chenthongtin(chuoi, cuoi, b - a, vitri);
	}
}
void taohtml(FILE*filein,FILE*fileout,sv a)
{
	wchar_t *MSSV=L"1212123";
	wchar_t *hoten = L"Nguyễn Văn A";
	wchar_t*hotenvdcap = L"NGUYỄN VĂN A";
	wchar_t *khoa = L"Công nghệ thông tin";
	wchar_t *khoavdcap = L"CÔNG NGHỆ THÔNG TIN";
	int	namhoc=2013;
	wchar_t *ngaysinh = L"20/01/1994";
	wchar_t *email = L"nva@gmail.com";
	wchar_t *hinh = L"HinhCaNhan.jpg";
	wchar_t *sothich1 = L"Âm nhạc: POP, Balad";
	wchar_t *sothich2 = L"Ẩm thực: bún riêu, bún thịt nướng";
	wchar_t *mota = L"Tôi là một người rất thân thiện.";
	wchar_t *temp = (wchar_t*)malloc(256 * sizeof(wchar_t));
	wchar_t* hotencap = (wchar_t*)malloc(wcslen(a.hoten) * sizeof(wchar_t));
	wcscpy(hotencap,a.hoten);
	wcsupr(hotencap);
	wchar_t* khoacap = (wchar_t*)malloc(wcslen(a.khoa) * sizeof(wchar_t));
	wcscpy(khoacap, a.khoa);
	wcsupr(khoacap);
	wchar_t*no = L"";
	while (!feof(filein))
	{
		fgetws(temp,256, filein);
	//	thaydoitt(temp, MSSV, a.MSSV);
		thaydoitt(temp, hoten, a.hoten);
		thaydoitt(temp, hotenvdcap,hotencap );
		thaydoitt(temp, khoa, a.khoa);
		thaydoitt(temp, khoavdcap, khoacap);
		//thaydoitt(temp, ngaysinh, a.ngaysinh);
		thaydoitt(temp, email, a.email);
		thaydoitt(temp, hinh, a.hinh);
		thaydoitt(temp, sothich1, a.sothich);
		thaydoitt(temp, sothich2, no);
		thaydoitt(temp, mota, a.mota);
		fwprintf( fileout,L"%ls",temp);
	}
}
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	FILE*filein = _wfopen(L"thongtin.csv", L"r, ccs=UTF-8");
	int dem = DemSV(filein);
	fseek(filein, 4L, 0);
	sv *s = thongtintoansinhvien(filein,dem);
	fclose(filein);
	for (int i = 0; i < dem; i++)
	{
		wprintf(L"%ls,%ls,%ls,%ld,%ls,%ls,%ls,%ls,%ls\n", (*(s + i)).MSSV, (*(s + i)).hoten, (*(s + i)).khoa, (*(s + i)).namhoc, (*(s + i)).ngaysinh, (*(s + i)).email, (*(s + i)).hinh, (*(s + i)).mota, (*(s + i)).sothich);
	}
	FILE*filehtml = _wfopen(L"1212123.htm", L"r, ccs=UTF-8");
	FILE*fileout = _wfopen(L"ttaee.htm", L"w,ccs=UTF-8");
	taohtml(filehtml, fileout,s[1]);
	fclose(filehtml);
	fclose(fileout);
	getch();
	return 0;
}
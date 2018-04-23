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
void freesv(sv &a)
{
	free(a.MSSV);
	free(a.hoten);
	free(a.khoa);
	free(a.ngaysinh);
	free(a.email);
	free(a.hinh);
	free(a.);
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
	if (n < 0)
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
wchar_t *taofilename(sv a)
{
	int n = wcslen(a.MSSV);
	wchar_t* filename = (wchar_t*)malloc((n + 5)*sizeof(wchar_t));
	wcscpy(filename, a.MSSV);
	wchar_t* htm = L".htm";
	wcscat(filename, htm);
	return filename;
}
void taohtml(FILE*filein,sv a)
{

	wchar_t* filename = taofilename(a);
	FILE*fileout = _wfopen(filename, L"w,ccs=UTF-8");
	wchar_t MSSV[] = L"1212123";
	wchar_t hoten[] = L"Nguyễn Văn A";
	wchar_t hotenvdcap[] = L"NGUYỄN VĂN A";
	wchar_t khoa[] = L"Công nghệ thông tin";
	wchar_t khoavdcap[] = L"CÔNG NGHỆ THÔNG TIN";
	int	namhoc=2013;
	wchar_t ngaysinh[] = L"20/01/1994";
	wchar_t email[] = L"nva@gmail.com";
	wchar_t hinh[] = L"HinhCaNhan.jpg";
	wchar_t sothich[] = L"Âm nhạc: POP, Balad";
	wchar_t mota []= L"Tôi là một người rất thân thiện.";
	wchar_t *temp = (wchar_t*)malloc(256 * sizeof(wchar_t));
	wchar_t *hotencap = (wchar_t*)malloc(wcslen(a.hoten) * sizeof(wchar_t));
	wcscpy(hotencap,a.hoten);
	wcsupr(hotencap);
	wchar_t* khoacap = (wchar_t*)malloc(wcslen(a.khoa) * sizeof(wchar_t));
	wcscpy(khoacap, a.khoa);
	wcsupr(khoacap);
	while (!feof(filein))
	{
		fgetws(temp,256, filein);
		thaydoitt(temp, MSSV, a.MSSV);
		thaydoitt(temp, hoten, a.hoten);
		thaydoitt(temp, hotenvdcap,hotencap );
		thaydoitt(temp, khoa, a.khoa);
		thaydoitt(temp, khoavdcap, a.khoa);
		thaydoitt(temp, email, a.email);
		thaydoitt(temp, hinh, a.hinh);
		thaydoitt(temp, sothich, a.sothich);
		thaydoitt(temp, mota, a.mota);
		thaydoitt(temp, ngaysinh, a.ngaysinh);
		fwprintf( fileout,L"%ls",temp);
	}
	free(temp);
	free(khoacap);
	free(hotencap);
	free(filename);
	fclose(fileout);
}
void hoanthienfile(FILE*filein)
{

}
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	FILE*filein = _wfopen(L"thongtin.csv", L"r, ccs=UTF-8");
	int dem = DemSV(filein);
	fseek(filein, 3L, 0);
	sv *s = thongtintoansinhvien(filein,dem);
	fclose(filein);
	FILE*filehtml = _wfopen(L"filedemo.htm", L"r, ccs=UTF-8");
	//for (int i = 1; i < dem; i++)
	//{
		wchar_t* filename = taofilename(s[0]);
		taohtml(filehtml, s[0]);
	fclose(filehtml);
	free(s);
	getch();
	return 0;
}
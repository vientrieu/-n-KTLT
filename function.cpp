#include"Header.h"
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
void xoarac(wchar_t* chuoi)//xóa rác \n hoặc \t hoặc \" mà hàm đọc sai xót
{
	int n = wcslen(chuoi);
	int i = 0;
	while (i<n)
	{
		if (*(chuoi + i) == '\n' || *(chuoi + i) == '\t' || *(chuoi + i) == '\"')
		{
			for (int j = 0; j < n - i; j++)
			{
				*(chuoi + i + j) = *(chuoi + i + j + 1);
			}
			i = 0;
		}
		else i++;
	}
}
sv thongtin1sinhvien(FILE*filein)// đọc thông tin 1 sinh viên
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
	xoarac(a.MSSV);
	xoarac(a.hoten);
	xoarac(a.khoa);
	xoarac(a.ngaysinh);
	xoarac(a.email);
	xoarac(a.hinh);
	xoarac(a.mota);
	xoarac(a.sothich);
	return a;
}
sv* thongtintoansinhvien(FILE*filein, int soSV)//đọc thông tin toàn sinh viên
{

	sv*s = (sv*)malloc((soSV)*sizeof(sv));
	for (int i = 0; i < soSV; i++)
	{
		*(s + i) = thongtin1sinhvien(filein);
	}
	return s;
}
void freesv(sv &a)//giải phóng vùng nhớ xin cấp phát cho 1 sinh viên
{
	free(a.MSSV);
	free(a.hoten);
	free(a.khoa);
	free(a.ngaysinh);
	free(a.email);
	free(a.hinh);
	free(a.sothich);
	free(a.mota);
}
int timchuoi(wchar_t* cha, wchar_t* con, int start)//tìm chuỗi trong chuỗi, trả về vị trí đầu tiên
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
void chenthongtin(wchar_t*chuoi, wchar_t*thay, int n, int vitri)// thay đổi chuỗi
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
void thaydoitt(wchar_t*chuoi, wchar_t*dau, wchar_t*cuoi)// tìm chuỗi và thay thông tin
{
	int i = 0;
	int a = wcslen(dau);
	int b = wcslen(cuoi);
	while (*(chuoi))
	{
		int vitri = timchuoi(chuoi, dau, 0);//tìm vị trí
		if (vitri == -1) return;
		chenthongtin(chuoi, cuoi, b - a, vitri);//sửa thông tin
	}
}
wchar_t *taofilename(sv a)//tạo file name cho profile page theo MSSV
{
	int n = wcslen(a.MSSV);
	wchar_t* filename = (wchar_t*)malloc((n + 5)*sizeof(wchar_t));
	wcscpy(filename, a.MSSV);
	wchar_t* htm = L".htm";
	wcscat(filename, htm);//ghép đuôi .htm vào MSSV
	return filename;
}
void taohtml(FILE*filein, sv a)//tạo file HTML proflie page
{
	//tìm các thông tin trong file mẫu rồi thay thành thông tin sv 
	wchar_t* filename = taofilename(a);
	FILE*fileout = _wfopen(filename, L"w,ccs=UTF-8");
	wchar_t MSSV[] = L"1212123";
	wchar_t hoten[] = L"Nguyễn Văn A";
	wchar_t hotenvdcap[] = L"NGUYỄN VĂN A";
	wchar_t khoa[] = L"Công nghệ thông tin";
	wchar_t khoavdcap[] = L"CÔNG NGHỆ THÔNG TIN";
	int	namhoc = 2013;
	wchar_t ngaysinh[] = L"20/01/1994";
	wchar_t email[] = L"nva@gmail.com";
	wchar_t hinh[] = L"HinhCaNhan.jpg";
	wchar_t sothich[] = L"Âm nhạc: POP, Balad";
	wchar_t mota[] = L"Tôi là một người rất thân thiện.";
	wchar_t nam[] = L"@2013";
	wchar_t namthaythe[] = L"@2018";
	wchar_t MSSVmau[] = L"MSSV -";
	wchar_t MSSVtacgia[] = L"1712837 -";
	wchar_t tenmau[] = L"Tên sinh viên thực hiện";
	wchar_t tentacgia[] = L"Mang Viên Triệu";
	wchar_t *temp = (wchar_t*)malloc(256 * sizeof(wchar_t));
	wchar_t *hotencap = (wchar_t*)malloc(wcslen(a.hoten) * sizeof(wchar_t));
	wcscpy(hotencap, a.hoten);
	wcsupr(hotencap);//các bước viết hoa tên
	wchar_t* khoacap = (wchar_t*)malloc(wcslen(a.khoa) * sizeof(wchar_t));
	wcscpy(khoacap, a.khoa);
	wcsupr(khoacap);//các bước viết hoa khoa
	while (!feof(filein))
	{
		//sao chép từng dòng, thay đổi thông tin
		fgetws(temp, 256, filein);
		thaydoitt(temp, MSSV, a.MSSV);
		thaydoitt(temp, hoten, a.hoten);
		thaydoitt(temp, hotenvdcap, hotencap);
		thaydoitt(temp, khoa, a.khoa);
		thaydoitt(temp, khoavdcap, a.khoa);
		thaydoitt(temp, ngaysinh, a.ngaysinh);
		thaydoitt(temp, email, a.email);
		thaydoitt(temp, hinh, a.hinh);
		thaydoitt(temp, sothich, a.sothich);
		thaydoitt(temp, mota, a.mota);
		thaydoitt(temp, nam, namthaythe);
		thaydoitt(temp, MSSVmau, MSSVtacgia);
		thaydoitt(temp, tenmau, tentacgia);
		fwprintf(fileout, L"%ls", temp);//in ra file out
	}
	//giải phóng vùng nhớ và đóng file
	free(temp);
	free(filename);
	fclose(fileout);
}
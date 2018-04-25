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
}; typedef struct sinhvien sv;
int DemSV(FILE *filein);// đếm số sinh viên
wchar_t *docdulieu(FILE*filein);// đọc kiểu unicode
int docdulieuint(FILE* filein);//đọc kiểu int
void xoarac(wchar_t* chuoi);//xóa rác \n hoặc \t hoặc \" mà hàm đọc sai xót
sv thongtin1sinhvien(FILE*filein);//đọc thông tin 1 sinh viên
sv* thongtintoansinhvien(FILE*filein, int soSV);// đọc thông tin toàn sinh viên
void freesv(sv &a);//giải phóng vùng nhớ xin cấp phát cho 1 sinh viên
int timchuoi(wchar_t* cha, wchar_t* con, int start);//tìm chuỗi trong chuỗi, trả về vị trí đầu tiên
void chenthongtin(wchar_t*chuoi, wchar_t*thay, int n, int vitri);// thay đổi chuỗi
void thaydoitt(wchar_t*chuoi, wchar_t*dau, wchar_t*cuoi);// tìm chuỗi và thay thông tin
wchar_t *taofilename(sv a);//tạo file name cho profile page theo MSSV
void taohtml(FILE*filein, sv a);//tạo file HTML proflie page


#include"Header.h"
int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input
	FILE*filein = _wfopen(L"thongtin.csv", L"r, ccs=UTF-8");
	int dem = DemSV(filein);
	fseek(filein, 3L, 0);
	sv *s = thongtintoansinhvien(filein, dem);//tạo mảng sv
	fclose(filein);
	FILE*filehtml = _wfopen(L"filedemo.htm", L"r, ccs=UTF-8");//mở file mẫu
	for (int i = 0; i < dem; i++)
	{
		rewind(filehtml);
		taohtml(filehtml, s[i]);//tạo html
		freesv(s[i]);// giải phóng vùng nhớ 1 sv
	}
	fclose(filehtml);//đóng file mẫu
	free(s);//giải phóng mảng sv
	getch();
	return 0;
}
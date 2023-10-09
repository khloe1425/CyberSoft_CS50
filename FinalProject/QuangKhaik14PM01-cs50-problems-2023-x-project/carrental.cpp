#include<iostream>
using namespace std;
#include<string>

//cho hai loai xe xe dap xe may: xe dap 10000 nghìn 1 gio tiêp theo sau là 8000 : xe may 2 loai 100 voi 250 phan khoi xe 100 gio dau 150000 tiep theo sau là 100000 xe 250 gio dau 200000 tiep theo sau la 100000 xe 150 gio dau 175000 tiep theo sau la 100000
// khai báo lop cha : class XE
// CAR RENTAL
class XE
{
protected:
    string HoTenNguoiThue;
	float SoGioThue;

public:
     void NhapThongTin()
     {
     	while(getchar() !='\n');// xoa bo nho dem truoc khi nhap chuoi
     	cout<<"\nNhap ho ten nguoi thue: ";
     	getline(cin, HoTenNguoiThue);
     	cout<<"\nNhap so gio thue: ";
     	cin>> SoGioThue;
	 }
	 void XuatThongTin()
	 {
	 	cout << "\nHo ten nguoi thue: " << HoTenNguoiThue ;
	 	cout << "\nSo gio thue: " << SoGioThue;
	 }

};
// khai bao lop con: class XEDAP ke thua lai class XE
class XEDAP: public XE
{
private:
public:
	float TinhTienThueXe()
	{
		return  10000 + ((SoGioThue-1)*8000);
	}

};
// khai bao lop con: class XEMAY ke thua lai class XE
class XEMAY: public XE
{
private:
     int LoaiXe;
     string BienSo;
public:
	void NhapThongTin()
     {
     XE::NhapThongTin();
     cout << "\nNhap loai xe can thue(100-150-250 phan khoi): ";
     cin >>  LoaiXe;
     while(getchar() !='\n');// xoa bo nho dem truoc khi nhap chuoi
     cout << "\nNhap bien so: ";
     getline(cin, BienSo );
	 }
	 void XuatThongTin()
	 {
	 	XE::XuatThongTin();
	 	cout << "\nLoai xe: " << LoaiXe ;
	 	cout << "\nBien so: " << BienSo;
	 }
	float TinhTienThueXe()
	{
		float s=0;
		if(LoaiXe==100 )
		{
			s=150000;
		}
		else if (LoaiXe==150)
		{
			s=175000;
		}
		else
		{
			s=200000;
		}

		return  s + ((SoGioThue-1)*100000 );
	}

	// GETTER - LOAI XE
	int getter_LoaiXe()
	{
		return LoaiXe;
	 }
		void setter_LoaiXe(int LOAIXE)
	{
		LoaiXe=LOAIXE;
	 }
};
// phuong thuc xuat tat ca thong tin thue xe
void Xuat_Tat_Ca_Thong_Tin_Thue_Xe(XEDAP ds_xedap[], int n, XEMAY ds_xemay[], int m)
{
	int dem = 1;
	cout << "\n\n\t\t DANH SACH THUE XE DAP\n";
	// xuat danh sach xe dap
	for (int i=0; i<n;i++)
	{
		cout << "\n\t THONG TIN THUE XE DAP THU" << dem++ << endl;
		ds_xedap[i].XuatThongTin();
		cout <<"\nTien thue: " << (size_t)ds_xedap[i].TinhTienThueXe();
	}
	cout << "\n\n\t\t DANH SACH THUE XE MAY\n";
	// xuat danh sach xe may
	for (int i=0; i<m;i++)
	{
		cout << "\n\t THONG TIN THUE MAY DAP THU" << dem++ << endl;
		ds_xemay[i].XuatThongTin();
		cout <<"\nTien thue: " << (size_t)ds_xemay[i].TinhTienThueXe();
	}
}
// phuong thuc tinh tong tien thue xe dap va xe may
float Tinh_Tong_Tien_Thue_Xe(XEDAP ds_xedap[], int n, XEMAY ds_xemay[], int m)
{
     float tong = 0;
	// duyet danh sach xe dap
	for (int i=0; i<n;i++)
	{

		tong += ds_xedap[i].TinhTienThueXe();
	}

	// duyet danh sach xe may
	for (int i=0; i<m;i++)
	{
	tong += ds_xemay[i].TinhTienThueXe();
	}
	return tong;
}
// ham quan li cac loai xe
void Menu(XEDAP ds_xedap[], int n, XEMAY ds_xemay[], int m)
{
	int luachon;
	while (true)
	{
		system("cls");
		cout << "\n\n\t\t ====== QUAN LY XE ======";
		cout << "\n\n\t\t Tran Quang Khai";
		cout << "\n\n\t\t Ngay làm 8/8/2021";
		cout << "\n\t1. Nhap danh sach thue xe dap va xe may";
		cout << "\n\t2. Xuat tat ca thong tin thue xe";
		cout << "\n\t3. Tinh tong so tien cho thue xe dap va xe may";
		cout << "\n\t4. Xuat tat ca cac thong tin lien quan den viec cho thue xe dap";
		cout << "\n\t5. Liet ke  so tien cho thue xe may loai 250 phan khoi";
		cout << "\n\t6. Liet ke  so tien cho thue xe may loai 100 phan khoi";
		cout << "\n\t7. Liet ke  so tien cho thue xe may loai 150 phan khoi";
		cout << "\n\t0. Ket thuc ";
		cout << "\n\n\t\t ====== END ======";

		cout << "\nNhap lua chon ";
		cin >> luachon;

		if(luachon==1)
		{
			int chon;
			while (true)
			{
				system("cls");
				cout << "\n1. Thue XE DAP";
				cout << "\n2. Thue XE MAY";
				cout << "\n0. Ket thuc";

				cout << "\nNhap loai xe ban muon thue: ";
				cin >> chon;

				if (chon==1)
				{
					XEDAP X;
					cout << "\n\n\t\t NHAP THONG TIN THUE XE DAP\n";
					X.NhapThongTin();
					ds_xedap[n] = X;
					n++;
				}
			else if (chon==2)
				{
					XEMAY X;
					cout << "\n\n\t\t NHAP THONG TIN THUE XE MAY\n";
					X.NhapThongTin();
					ds_xemay[m] = X;
					m ++;
				}
				else
				{

					break;
				}
			}
		}
		else if (luachon==2)
		{
			 Xuat_Tat_Ca_Thong_Tin_Thue_Xe(ds_xedap, n, ds_xemay,  m);
			 system("pause");
		}
		else if (luachon==3)
		{
			cout  << "\n\n\t\tTong tien thue xe la: " << (size_t)Tinh_Tong_Tien_Thue_Xe(ds_xedap, n, ds_xemay,  m);
			system("pause");
		}
		else if (luachon == 4)
		{
				cout << "\n\n\t\t DANH SACH THUE XE DAP\n";
	// xuat danh sach xe dap
	for (int i=0; i<n;i++)
	{
		cout << "\n\t THONG TIN THUE XE DAP THU" << i + 1 << endl;
		ds_xedap[i].XuatThongTin();
		cout <<"\nTien thue: " << (size_t)ds_xedap[i].TinhTienThueXe();

	}
	system("pause");
		}
		else if (luachon == 5)
		{
			int dem = 0;
			cout << "\n\n\t\t DANH SACH THUE XE MAY LOAI 250 PHAN KHOI\n";
			//duyet danh sach xe may
	for (int i=0; i<m;i++)
	{
		if (ds_xemay[i].getter_LoaiXe()==250)
		{
			cout << "\n\t THONG TIN THUE MAY DAP THU" << ++dem << endl;
		ds_xemay[i].XuatThongTin();
		cout <<"\nTien thue: " << (size_t)ds_xemay[i].TinhTienThueXe();
		}

	}
	system("pause");
}
else if (luachon == 6)
		{
			int dem = 0;
			cout << "\n\n\t\t DANH SACH THUE XE MAY LOAI 100 PHAN KHOI\n";
			//duyet danh sach xe may
	for (int i=0; i<m;i++)
	{
		if (ds_xemay[i].getter_LoaiXe()==100)
		{
			cout << "\n\t THONG TIN THUE MAY DAP THU" << ++dem << endl;
		ds_xemay[i].XuatThongTin();
		cout <<"\nTien thue: " << (size_t)ds_xemay[i].TinhTienThueXe();
		}

	}
	system("pause");
}
else if (luachon == 7)
		{
			int dem = 0;
			cout << "\n\n\t\t DANH SACH THUE XE MAY LOAI 100 PHAN KHOI\n";
			//duyet danh sach xe may
	for (int i=0; i<m;i++)
	{
		if (ds_xemay[i].getter_LoaiXe()==150)
		{
			cout << "\n\t THONG TIN THUE MAY DAP THU" << ++dem << endl;
		ds_xemay[i].XuatThongTin();
		cout <<"\nTien thue: " << (size_t)ds_xemay[i].TinhTienThueXe();
		}

	}
	system("pause");
}

		else
		{
			break;
		}
	}
}
int main()
{
	XEDAP ds_xedap[100];
	int n=0;
	XEMAY ds_xemay[100];
	int m=0;
	Menu(ds_xedap, n, ds_xemay,  m);
	system("pause");
	return 0;
}
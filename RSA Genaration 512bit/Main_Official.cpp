#include<bits/stdc++.h>
#include"Ham.h"
using namespace std;
typedef long long ll;

int main(){
	int t = 1;
	
	while(t != 0){
		cout<<"1.Sinh Bo Khoa Ngau Nhien."<<endl;
		cout<<"2.Ma Hoa Doan Van Ban."<<endl;
		cout<<"3.Giai Ma Doan Van Ban."<<endl;
		cin >> t;
		switch(t){
			case 1:
				sinhKhoa();
				break;
			case 2:
				MaHoa();
				break;
			case 3:
				GiaiMa();
				break;
			default:
				t = 0;
		}
	}
	return 0;
}


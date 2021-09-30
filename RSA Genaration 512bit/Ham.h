#include<bits/stdc++.h>
#include"Bigint.h"
#include"base64.h"
using namespace std;
typedef long long ll;

//Ham TestNhanh: chia cho 1000 so nguyen to dau tien
bool T(bigint n,bigint *a){
		for(ll i = 0; i < 1000; i+=1){
			if(n % a[i] == 0){
				return false;}
		}
		return true;
}
//Ham Random co gioi han Khoang (a;b)
bigint random(bigint minN, bigint maxN){
    return minN + (bigint)rand() % (maxN + 1 - minN);
}
bigint demso(bigint n){
	bigint dem = 0;
	while(n>0){
		n/=1e4;
		dem+=4;
		
	}
	return dem;
}
//Ham a^b
bigint newpow(bigint x, bigint y){
	bigint res;
	if(y == 0) return 1;
	if(y%2 == 0)
		return newpow(x*x,y/2);
	else
		return x*newpow(x*x,y/2);
}
//Ham a^b % c, co the dung tuong tu ham newpow, tuy nhien sau khi chay, nhan ra ham power nhanh hon
bigint power(bigint x, bigint y, bigint p) 
{ 
    bigint res = 1;
    x = x % p;
    while (y > 0) 
    { 
        if (y % 2 == 1) 
            res = (res*x) % p; 
        y =y/2; 
        x = (x*x) % p; 
    } 
    return res; 
} 
//Ham Test Buoc 2 cua MILLER RABiN : kiem tra so nguyen to voi xac suat cao
bool miillerTest(bigint r,bigint d, bigint n) 
{ 
	// Random a = (2;n-2)
    bigint minN = 2;
	bigint maxN = n-2;
	bigint a = demso(maxN + 1 - minN)/5;
	bigint y = 0;
    for(bigint i = 0; i <= a;i+=1){
			y=y*1e5 + random(1,RAND_MAX);
	}
	a = minN + y % (maxN + 1 - minN);
    //a^d % n 
    bigint x = power(a, d, n); 
  
    if (x == 1  || x == n-1) 
       return true; 
  	for(bigint i = 1; i < r; i+=1){
  		x = power(x,2,n);
  		if(x == n - 1)
  			return true;
	  }
	//O Buoc nay true: co kha nang la sont, false: hop so
    return false; 
} 
// Testfermat: 2^(n-1) = 1 => co kha nang la snt
bool TestFermat(bigint n){
	bigint a = power(2,n-1,n);
	if(a == 1)
		return true;
	else
		return false;
}
//Test tong quat MILLER RABIN : Lap nhieu lan buoc 2
bool isPrime(bigint n, bigint k) 
{ 
    //Loai bo cac truong hop co ban hop so
    if (n <= 1 || n == 4)  return false; 
    if (n <= 3) return true; 
    if (n%2 == 0) return false;
  
    // r voi  n = 2^d * r 
    bigint d = n - 1; 
    bigint r = 0;
    while (d % 2 == 0){
        d /= 2;
		r+=1; 
    }
  
    // Lap voi k lan cho truoc tang xac suat snt (10;20) la kha cao
    for (bigint i = 0; i < k; i+=1) 
         if (!miillerTest(r,d, n)) 
              return false; 
  
    return true; 
} 
//Ham UCLN
bigint gcd(ll a, ll b) { 
    if (b == 0) return a;
    return gcd(b, a%b);
}
//Ham extend ho tro tinh modulo 
bigint gcd_extend(bigint a, bigint b, bigint *x, bigint *y) {
  	if (b == 0) {
   		*x = 1;
    	*y = 0;
    	return a;
	}
  	bigint x1, y1;
 	bigint gcd = gcd_extend(b, a%b,  &x1, &y1);
  	*x = y1;
  	*y = x1 - (a / b) * y1;
 	return gcd;
}
//XU lY x am
bigint modulo_inverse_euclidean(bigint n, bigint m) {
  bigint x, y;
  if (gcd_extend(n, m, &x, &y) != 1) return -1; // Khong ton tai x
  return (x % m  + m) % m; // Vi x co the am 
}
//Random e voi gcd(phi,e) = 1
bigint randomE(bigint n,bigint phi){
	bigint  y;
	bigint minN = newpow(2,n-1)+1;
	bigint maxN = newpow(2,n)-1;
	bigint a = demso(maxN + 1 - minN)/4;
	while(gcd(y,phi) != 1 || y >= phi){
		y = 0;
		for(bigint i = 0; i <= a;i+=1){
			y=y*1e4 + random(1,RAND_MAX);
		}
		y = minN + y % (maxN + 1 - minN);
	}
	return y;
}
//random 1 so nguyen to voi do dai n bit
bigint randombit(bigint n,bigint *data){
	bigint  y = 0;
	bigint minN = newpow(2,n-1)+1;
	bigint maxN = newpow(2,n)-1;
	bigint a = demso(maxN + 1 - minN)/4;
	while(y == 0){
//		y = 0;
		for(bigint i = 0; i <= a;i+=1){
			y=y*1e4 + random(1,RAND_MAX);
		}
		y = minN + y % (maxN + 1 - minN);
		if(T(y,data)){
			if(TestFermat(y))
				if(isPrime(y,10))
					return y;
				else
					y = (bigint)0;
			else
				y = (bigint)0;
			}
		else if(!T(y,data))
			y = (bigint)0;
	}
}
string MaHoaKey(bigint x){
	ofstream fileout1("Tam.txt");
		fileout1 << x;
	fileout1.close();
	
	string str1;
	ifstream filein2;
	filein2.open("Tam.txt");
		filein2 >>str1;
	filein2.close();
	char* st = new char[str1.size() + 1];
	strcpy(st, str1.c_str());
//	cout<<st<<endl;
	std::string t=base64_encode(st, str1.size());
	return t;

}
bigint GiaiMaKey(string x){
	string giaiMa = base64_decode(x);
//	cout<<giaiMa<<endl;
	return (bigint)giaiMa;
}
void sinhKhoa(){
	cout<<"Vui long cho trong giay lat...."<<endl;
	srand(time(NULL));
	bigint *data = new bigint[1000 + 1];
	ifstream file;
	file.open("giatriNT.txt");
	for(ll i = 0; i < 1000; i+= 1){
		file>>data[i];
  	//cout<<data[i]<<endl;
	}
	file.close();
	bigint q=randombit(256,data),p=q;
	while(q == p){
		p = randombit(256,data);
	}
	bigint n = q*p,e,d;
	bigint phi =(p-1)*(q-1);//gcd((p-1),(q-1));
//	cout<<"phi = "<<phi<<endl;
	e = randomE(256,phi);
//	cout<<"e = "<<e<<endl;
	d = modulo_inverse_euclidean(e,phi);
//	cout<<"d = "<<d<<endl
	string st_n,st_d,st_e;
	st_n = MaHoaKey(n);
	st_d = MaHoaKey(d);
	st_e = MaHoaKey(e);
	cout<<"Khoa Cong Khai chung, n: "<<endl<<st_n<<endl<<endl;	
	cout<<"Khoa Cong Khai, e: "<<endl<<st_e<<endl<<endl;
	cout<<"Khoa Bi Mat, d: "<<endl<<st_d<<endl<<endl;
	ofstream fileout("BoMa.txt");
		fileout << st_n<<endl;
		fileout << st_e<<endl;
		fileout << st_d<<endl;
	fileout.close();
	cout<<"!!!!File luu: BoMa.txt!!!"<<endl<<endl;
	
	
}

void MaHoa(){
	bigint n;
	bigint e;
	string st_n,st_d,st_e;
	int temp = 1;
	cout<<"---Hay Chac rang ban da nhap doan van vao file: DoanVan.txt"<<endl;
	cout<<endl;
	cout<<"1. Dung ma tu BoMa.txt"<<endl;
	cout<<"2. Tu nhap ma."<<endl;
	cin>>temp;
	ifstream filein1;
	switch(temp){
		case 1:
			filein1.open("BoMa.txt");
				filein1 >> st_n;
				filein1 >> st_e;
			filein1.close();
			break;
		case 2:
			cout<<"Moi ban nhap Key chung n: "<<endl;
			getline(cin,st_n);
			cin.clear(); cin.ignore(100,'\n');
			cout<<"Moi ban nhap Key Cong Khai e:"<<endl;
			getline(cin,st_e);
			break;
	}
	n = GiaiMaKey(st_n);
	e = GiaiMaKey(st_e);
	
	string str;
	ifstream filein;
	filein.open("DoanVan.txt");
		getline(filein,str);
	filein.close();
//	cout<<str;

	
	char* c = new char[str.size() + 1];
	bigint a=0;
	strcpy(c, str.c_str());
//	cout<<str<<endl;
//	cout<<a;
	for(int i = 0; i < str.size(); i++){
		a*=1000;
		a+=bigint(c[i]);
//		cout<<a<<endl;
		
	}
	cout<<endl;
//	cout<<str.size();
	cout<<endl;
//	cout<<a<<endl;
	a=power(a,e,n);
//	cout<<a<<endl;
	ofstream fileout1("DAngSoMAHOA.txt");
		fileout1 << a;
	fileout1.close();
	
	string str1;
	ifstream filein2;
	filein2.open("DAngSoMAHOA.txt");
		filein2 >>str1;
	filein2.close();
	char* st = new char[str1.size() + 1];
	strcpy(st, str1.c_str());
//	cout<<st<<endl;
	std::string t=base64_encode(st, str1.size());
	
	ofstream fileout("MaHoa.txt");
		fileout << t;
	fileout.close();
	cout<<"Doan Van da duoc ma hoa: "<<endl;
	cout<<t<<endl<<endl;
	cout<<"!!!Doan Van da ma hoa trong file: MaHoa.txt!!!"<<endl<<endl;
}
void GiaiMa(){
	ifstream filein;
	string st;
	filein.open("MaHoa.txt");
		getline(filein,st);
	filein.close();
	string giaiMa;
	giaiMa = base64_decode(st);
//	cout<<giaiMa<<endl;
	
	bigint tt;
	tt=(bigint)giaiMa;
//	cout<<tt;
	
	string st_n,st_d,st_e;
	bigint d;
	bigint n;
	cout<<"Moi ban nhap DOAN MA vao file: MaHoa.txt"<<endl<<endl;
	int temp = 1;
	cout<<"1. Dung ma tu BoMa.txt"<<endl;
	cout<<"2. Tu nhap ma."<<endl;
	cin>>temp;
	ifstream filein1;
	switch(temp){
		case 1:

			filein1.open("BoMa.txt");
				filein1 >> st_n;
				filein1 >> st_d;
				filein1 >> st_d;
			filein1.close();
			break;
		case 2:
			cout<<"Moi ban nhap Key chung n: "<<endl;
			getline(cin,st_n);
			cin.clear(); cin.ignore(100,'\n');
			cout<<"Moi ban nhap Key Bi Mat d:"<<endl;
			getline(cin,st_d);
			break;
		default:
			cout<<"Nhap sai.";
	}
		
			
	n = GiaiMaKey(st_n);
	d = GiaiMaKey(st_d);
	
	tt = power(tt,d,n);
//	cout<<d<<endl;
//	cout<<tt<<endl;
	string Ma;
	for(int i = 0; tt != 0 ; i++){
		Ma = char(tt%1000) + Ma;
//		giaiMa[i]=char(giaiMaSo.a[0])
		tt/=1000;
	}
//	cout<<"Giai ma:"<<endl;
//	cout<<Ma;
	ofstream fileout1("GiaiMa.txt");
		fileout1 << Ma;
	fileout1.close();
	cout<<"File da duoc Giai Ma: "<<endl;
	cout<<Ma<<endl<<endl;
	cout<<"!!!Moi ban mo file GiaiMa.txt!!!"<<endl<<endl;
	
}



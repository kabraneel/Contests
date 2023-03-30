// na ho paega humse
// nai_aati_coding
// i love PD
// Motivation when feeling low : http://bitly.com/98K8eH
#include <bits/stdc++.h>
#include <chrono>
using namespace std;


#ifdef KABRANEEL
#include<sys/resource.h>
#include <sys/time.h>
#endif

#define int long long
#ifdef KABRANEEL
#define LOCAL
#include "/home/kabraneel/coding/debug.h"
#else
#define debug(x...)
#define debugln(x...)
#endif


#define PB push_back
#define all(x) (x).begin(),(x).end()
#define MP make_pair
#define sz(x) (int)(x.size())

template<typename T,typename T1>T amax(T &a,T1 b){if(b>a)a=b;return a;}
template<typename T,typename T1>T amin(T &a,T1 b){if(b<a)a=b;return a;}

#define FOR(i,a,b) for(int i=a; i<b; i++)

const int MOD = 1e9 + 7;
const int INF = 1e18;

void solve(){
	int n; cin>>n;
	vector<int> arr(n);

	for(int i = 0; i<n; i++){
		cin>>arr[i];
	}

	vector<pair<int,int>> counts;
	int i = 0;
	while(i < n){
		int count = 0;
		int key = arr[i];
		while(i < n and arr[i] == key){
			count++;
			i++;
		}
		counts.PB({count, key});
	}

	if(sz(counts) == 1){
		cout << "1\n";
		for(int i = 0; i<n; i++){
			cout << "1 ";
		}
		cout << '\n';
		return;
	}
	// debug(counts);

	auto end = counts.back();
	if(end.second == counts[0].second){
		counts[0].first += end.first; 
		counts.pop_back();
	}

	if(sz(counts) % 2 == 0){

		cout << "2\n";
		int color = 1;

		int i = 0;
		while(i < n){
			int key = arr[i];
			while(i < n and arr[i] == key){
				cout << color + 1 << ' ';
				i++;
			}
			color = 1 - color;
		}
		cout << '\n';
		return;

	}

	int men = 0;
	int ind = -1;
	for(int i = 0; i < sz(counts); i++){
		if(counts[i].first > men){
			men = max(men, counts[i].first);
			ind = i;
		}
	}

	if(men == 1){
		cout << "3\n";
		for(int i = 0; i<n-1; i++){
			cout << (i % 2) + 1 << ' ';
		}
		cout << 3 << '\n';
		return;
	}

	int tsum = 0;
	for(int i = 0; i<ind; i++){
		tsum += counts[i].first;
	}

	debug(counts);
	debug(tsum, ind);

	arr[tsum] = 1e9;

	debug(arr);

	cout << "2\n";
	int color = 1;

	i = 0;
	while(i < n){
		int key = arr[i];
		while(i < n and arr[i] == key){
			cout << color + 1 << ' ';
			i++;
		}
		color = 1 - color;
	}
	cout << '\n';
	return;





}

signed main(){

	#ifdef KABRANEEL
	freopen("/home/kabraneel/coding/Contests/inputfa.txt", "r", stdin);
	freopen("/home/kabraneel/coding/Contests/outputfa.txt", "w", stdout);
	freopen("/home/kabraneel/coding/Contests/error.txt","w",stderr);
	#endif

	#ifdef KABRANEEL
        /* setting up soft limit on resources */
        rlimit rlim , rlim_time ;
        if(getrlimit( RLIMIT_FSIZE , &rlim) || getrlimit(RLIMIT_CPU , &rlim_time) )
           return 1 ;
        // maximum file size (in bytes) that your program will be able to create ;
        rlim.rlim_cur = 1000*1000;
        // maximum allowed runtime for your program ;
        rlim_time.rlim_cur = 1;
        if(setrlimit( RLIMIT_FSIZE , &rlim ) || setrlimit(RLIMIT_CPU , &rlim_time))
           return 2 ;
    #endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	auto start = chrono::high_resolution_clock::now();

	int t=1;
	int zcount = 1;
	cin>>t;

	while(t--){
		//cout<<"Case #"<<zcount++<<": ";
	  solve();
	}

	auto end = chrono::high_resolution_clock::now();
	double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	cerr <<fixed<<time_taken<<setprecision(9)<< " sec"<<endl;
	return 0;
}
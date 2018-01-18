// maximum bipartite matching
#include "stdio.h"
#include "string.h"
#define N 71
int c[N][N] = {}, f[N][N] = {}, src = -1, snk = -1, h[N] = {}, excess_flow[N] = {};
// queue
int q[N], qsz = N;
int min(int a,int b) {
	return a < b ? a : b;
}
void preflow(int s) {
	h[s] = N;
	int i;
	for(i = 0; i < N; i++) {
		f[s][i] = c[s][i];
		excess_flow[i] += c[s][i];
		f[i][s] = -f[s][i];
	}
}

int overflowVertex() {
	int i = 0;
	for(; i < N; i++) {
		if(i != src && i != snk && excess_flow[i] > 0)
			return i;
	}
	return -1;
}


int push(int u) {
	int v;
	for(v = 0; v < N; v++) {
		if(c[u][v] == f[u][v]) continue;
		if(h[u] > h[v]) {
			int newflow = min(c[u][v] - f[u][v], excess_flow[u]);
			excess_flow[u] -= newflow;
			excess_flow[v] += newflow;
			f[u][v] += newflow;
			f[v][u] -= newflow;
			return 1;
		}
	}
	return 0;
}
void relabel(int u) {
	int mh = 2e9, v;
	for(v = 0; v < N; v++) {
		if(f[u][v] == c[u][v]) continue;
		if(h[v] < mh) {
			mh = h[v];
			h[u] = mh + 1;
		}
	}
}
int flow() {
	preflow(src);
	while(1) {
		int u = overflowVertex();
		if(u == -1) break;
		if(!push(u))
			relabel(u);
	}
	return excess_flow[snk];
}
int getCapacity(char* x, char* y) {
	int common = 0, cnt[26][2] = {};
	int i, len;
	for(i = 0, len = strlen(x); i < len; i++)
		cnt[x[i] < 'a' ? x[i] - 'A': x[i] - 'a'][0]++;
	for(i = 0, len = strlen(y); i < len; i++)
		cnt[y[i] < 'a' ? y[i] - 'A': y[i] - 'a'][1]++;
	for(i = 0; i < 26; i++)
		common += min(cnt[i][0], cnt[i][1]);
	return strlen(y) - strlen(x) == 1 && common ? 2 * common: 0;
}
int main() {
	int i;
	// input
	char* names[N] = {"Mumbai", "Delhi",  "Bangalore", "Hyderabad",  "Ahmedabad",  "Chennai",  "Kolkata",  "Surat", "Pune",  "Jaipur",  "Lucknow",  "Kanpur",  "Nagpur",  "Visakhapatnam", "Indore",  "Thane",  "Bhopal",  "Patna", "Vadodara",  "Ghaziabad",  "Ludhiana",  "Coimbatore",  "Agra",  "Madurai",  "Nashik",  "Faridabad",  "Meerut", "Rajkot", "Varanasi",  "Srinagar",  "Aurangabad",  "Dhanbad",  "Amritsar", "NaviMumbai", "Allahabad", "Ranchi",  "Howrah",  "Jabalpur",  "Gwalior",  "Vijayawada",  "Jodhpur",  "Raipur",  "Kota",  "Guwahati", "Chandigarh", "Thiruvananthapuram", "Solapur", "Tiruchirappalli",  "Bareilly", "Moradabad",  "Mysore", "Tiruppur",  "Gurgaon", "Aligarh",  "Jalandhar", "Bhubaneswar",  "Salem", "Warangal",  "Guntur", "Bhiwandi", "Saharanpur",  "Gorakhpur",  "Bikaner",  "Amravati",  "Noida",  "Jamshedpur", "Bhilai",  "Cuttack",  "Firozabad", "Kochi", "Goa"};
	// graph generation
	for(i = 0; i < N; i++) {
		int j;
		if(names[i] == "Goa") src = i;
		else if(names[i] == "Thiruvananthapuram") snk = i;
		for(j = 0; j < N; j++) {
			c[i][j] = i==j ? 0 : (getCapacity(names[i], names[j]));
		}
	}
	for(i = 0; i < N; i++) {
		int j, incoming = 0, outgoing = 0;
		for(j = 0; j < N; j++) {
			if(c[i][j] > 0) outgoing++;
			if(c[j][i] > 0) incoming++;
		}
		if(!incoming) c[src][i] = 20;
		if(!outgoing) c[i][snk] = 20;
	}
	printf("Maximum flow is: %d.\n", flow());
}

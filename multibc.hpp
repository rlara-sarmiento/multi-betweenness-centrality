#include<vector>
#include<queue>
#include<algorithm>
#include<discreture.hpp>
#include<string>



#define D_s D[s]
#define W_s W[s]



using namespace std;
using namespace dscr;



class ValuedSubset{
	private:
		vector< int > elems;
		double value=0;
	public:
		ValuedSubset(){
			elems = vector< int > (0);
			value = 0; 
		}
		
		ValuedSubset(const vector< int > &v, double d=0){
			for( int x : v )
				elems.push_back(x);
			value = d;
		}
		
		void operator=(const ValuedSubset &S){
			elems = S.elems;
			value = S.value;
		}
		
		
		void display( ) const{
			cout << "U = {  ";
			for( int x : elems )
				cout << x << "  ";
			cout << "},     BC(U) = " << value << endl;
		}
		
		
		inline double getValue() const{   return value;  }
		
		
		inline vector < int > getElements() const{
			return elems;
		}
		
};






class Graph{

	private:
		vector<  vector<int>  > G;
		vector< double > B;
		vector< vector< double > > BCs;
		vector< vector< int > > D;
		vector< vector< int > > W;
		vector< int > SortedVertices;
		vector< string > Names;
		bool NotSortedVertices=true;
		bool BCNotCalculated=true;
	
	public:
		
		
		Graph(int n=0){
			 G = vector< vector<int>  > (n);
			 B = vector<double> (n);
			 BCs = vector< vector<double> > (n, vector<double> (n) );
			 D = vector< vector< int > > (n, vector< int > (n, -1) );
			 W = vector< vector< int > > (n, vector< int > (n) );
			 Names = vector< string > (n);
			 for(int i=0; i<n ; i++) SortedVertices.push_back(i);
		}
		
		
		inline void setName(int v, string name){
		
			Names[v] = name;
		}
		
		
		
		inline string getName(int v){
		
			return Names[v];
		}
		
	
		
		
		inline int numberOfVertices() const{	return G.size();	}
		
		
		inline int numberOfEdges() const{
			
			int sum = 0;
			for( auto &v : G )
				sum += v.size();
			return sum/2;
		}
		
		
		
		
		void addEdge(int v, int u){
			if( u >= numberOfVertices() || v >= numberOfVertices() || u < 0 || v < 0 ||  u == v ){
				cout << "     ERROR: No son vértices del grafo " << u << " o " << v  << endl;
			} 
			else{
				G[v].push_back( u );  G[u].push_back( v ); 
			}
		}
		
		
		
		
		
		
		int numberOfNeighbors(int v) const{
			if( v >= numberOfVertices() || v < 0){
				cout << "     ERROR: No es un vértice valido." << endl;	
				return -1;
			}
			else{
				return G[v].size();
			}
		}
		
		
		
		
		
		
		void calculateBC(){
			int n = numberOfVertices();
			int lastnode, d, w;
			BCNotCalculated=false;
			queue < int > q;
			for(int s = 0; s < n ; ++s ){

				vector< double > X (n, 1);
				vector< int > P = {s};
				D_s[s] = 0;  W_s[s]=1;
				q.push(s);
				
				
				////////////////    Step W   //////////////
				while( !q.empty() ){
					lastnode = q.front();   q.pop();
					d = D_s[lastnode];
					for(int v : G[lastnode] ){
							
						if( D_s[v] == -1){
							D_s[v] = d+1;
							W_s[v] = W_s[lastnode];
							q.push(v);
							P.push_back(v);
						}
						else if (D_s[v] == D_s[lastnode]+1 ){
							W_s[v] += W_s[lastnode];
						}
						
					}
	
				}
				
				
				//////////  Step X     //////////////////
				for( int i = P.size()-1; i>=0 ; i--){
					w = P[i];
					for(int u : G[w] ){
						if( D_s[u] == D_s[w]+1 )
							X[w] += (X[u]*(double(W_s[w])/double(W_s[u])));
					}
				}
				for( int i=0 ; i<n ; ++i ){
					BCs[s][i] = X[i];
					B[i] += X[i];
				}
				
				
			}
			
			
		}
		
	
		
		
		
		
		inline double delta(int i){
			if( i%2 == 1)	return -1;
			else 	return 1;
		}
		
		
		
		
		
		void BC_s(const vector< int > &U, const int &s , double& sum, vector< int >& V, long long paths, int pos){
			switch( V.size() ){
				case 0:
					break;
				case 1:
					sum += BCs[s][ V[0] ];
					paths = W_s[ V[0] ];
					break;
				default:
					int j = V.size()-1;
					if( D[s][ V[j] ] < D[s][ V[j-1] ] + D[ V[j-1] ][ V[j] ] )
						return;
					paths *= W[ V[j-1] ][ V[j] ];
					sum += delta(j)* BCs[s][ V[j] ]* ( double(paths) / double(W_s[ V[j] ]) );
				
			
			}
			for( int i=pos ; i < U.size() ; i++){
				V.push_back( U[i] );
				BC_s( U, s, sum, V, paths, i+1);
				V.pop_back( );
			}	
		}
		
		
		
		
		
		inline double BC(int v){
			if( BCNotCalculated )
				calculateBC();
			return B[v];
		}
		
		
		
		
		double BC( vector< int > &U_0){
			vector< int > aux;
			vector< int > U = U_0;
			double sum = 0;
			for( int s = 0; s < numberOfVertices() ; ++s){
				sort( U.begin(), U.end(), [this,&s](int u, int v){  return D_s[u]<D_s[v]; });
				BC_s( U, s, sum, aux , 0 , 0);	
			}		
			return sum;
		}
		
		
		
		
		
		
		inline double sumBC( const vector< int >& U ){
			double sum = 0;
			for( int x : U )
				sum += B[  SortedVertices[x] ];
			return sum;
		}

		
		vector<int> getMaximumVertices(int m=1){
		
			if( BCNotCalculated )
				calculateBC();
			if( NotSortedVertices ){
				sort(SortedVertices.begin(), SortedVertices.end(), [this](int u, int v){  return B[u]>B[v]; });
				NotSortedVertices = false;
			}
			vector<int> aux;
			for(int i=0;i<m;i++)
				aux.push_back(SortedVertices[i]);
			return aux;
		}
		
		
		
		ValuedSubset maxBC(int k=1){
			int cont=0;
			
			if( BCNotCalculated )
				calculateBC();
			if( NotSortedVertices ){
				sort(SortedVertices.begin(), SortedVertices.end(), [this](int u, int v){  return B[u]>B[v]; });
				NotSortedVertices = false;
			}
			
			if( k == 1 ){
				ValuedSubset max( {SortedVertices[0]}, BC( SortedVertices[0] ) );
				return max;
			}
			else{
				ValuedSubset max;
				double aux;
				combinations Y( numberOfVertices(), k );
				auto X = Y.find_all( [this, &max, &k](const vector< int > &comb) -> bool {
					int sum = sumBC( comb );
					if( sum + BC( SortedVertices[ comb.back( ) + 1 ] ) * ( k - comb.size() ) <= max.getValue( ) )
						return false;
					return true;
				});
				for( const auto& T : X ){
					vector< int > U;
					for(int x: T)
						U.push_back( SortedVertices[x] ); 
					aux = BC( U );
					if( aux > max.getValue() ){
						ValuedSubset AUX(U,aux);
						max = AUX;
					}
					
				}
				return max;
			}
		}		
		
			
			


};

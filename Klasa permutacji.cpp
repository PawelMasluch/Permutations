#include<iostream>
#include<new>


using namespace std;


typedef long long LL;


#define REP(i,a,b) for(int i=a; i<=b; ++i)

#define FORD(i,b,a) for(int i=b; i>=a; --i)


class Permutation
{
	private:
		int n; // dlugosc permutacji
		int *t; // permutacja
		
	public:
		
		Permutation() // publiczny konstruktor
		{
			n = 0;
			t = NULL;
			//cout << "\n\nKonstruktor\n\n";
		}
		
		~Permutation() // publiczny destruktor
		{
			delete [] t;
			//cout << "\n\nDestruktor\n\n";
		}
		
		Permutation(const Permutation &p) // konstruktor kopiujacy
		{
			n = p.n;
			t = new int [n];
			
			REP(i,0,n-1)
			{
				t[i] = p.t[i];
			}
			
			//cout << "\n\nKonstruktor kopiujacy\n\n";
		}
		
		Permutation(int N) // permutacja identycznosciowa
		{
			n = N;
			t = new int [n];
			
			REP(i,0,n-1)
			{
				t[i] = i + 1;
			}
		}
				
		void input()
		{
			cout << "\nPodaj dlugosc permutacji: ";
			cin >> n;
			
			t = new int [n];
			
			cout << "Podaj elementy permutacji (od 1 do " << n << "): ";
			REP(i,0,n-1)
			{
				cin >> t[i];
			}
		}
		
		void output()
		{
			cout << "\nDlugosc permutacji: " << n;
			
			cout << "\nElementy permutacji: ";
			REP(i,0,n-1)
			{
				cout << t[i] << " ";
			}
			
			cout << endl;
		}
		
		int is_permutation() // czy zadany ciag liczb to permutacja;    0 - to nie jest permutacja;  1 - to jest permutacja
		{
			bool *pom = new bool [n];
			
			REP(i,0,n-1)
			{
				pom[i] = false;	
			} 
			
			REP(i,0,n-1)
			{
				if( t[i] < 1  ||  t[i] > n )
				{
					delete [] pom;
					return 0; // to nie jest permutacja
				}
				
				if( pom[ t[i] - 1 ] == true ) // jesli wczesniej pojawila sie liczba "t[i]" 
				{
					delete [] pom;
					return 0; // to nie jest permutacja
				}
				
				pom[ t[i] - 1 ] = true; // wlasnie pojawila sie liczba "t[i]"
			}
			
			delete [] pom;
			return 1; // to jest permutacja
		}
		
		int operator ==(Permutation &p) // czy 2 permutacje sa identyczne;    0 - permutacje nie sa identyczne;  1 - permutacje sa identyczne
		{
			if( n != p.n ) // jesli permutacje maja rozne dlugosci
			{
				return 0; // permutacje nie sa identyczne
			}
			
			REP(i,0,n-1)
			{
				if( t[i] != p.t[i] )
				{
					return 0;
				}
			}
			
			return 1;
		}
		
		void DFS(bool *pom, int *t, int i)
		{
			do
			{
				pom[ t[i] - 1 ] = true;
				
				i = t[i] - 1;
			}
			while( pom[ t[i] - 1 ] == false );
		}
		
		int cycles_number() // liczba cykli
		{
			int wyn = 0; // liczba cykli
			
			
			bool *pom = new bool [n];
			
			REP(i,0,n-1)
			{
				pom[i] = false;	
			}
			
			
			REP(i,0,n-1)
			{
				if( pom[ t[i] - 1 ] == false ) // jesli element "t[i]" nie wystapil
				{
					++wyn;
					
					DFS( pom, t, i );
				}
			}
			
			delete [] pom;
			return wyn;
		}
		
		
		/*LL Merge(int *t, int pocz, int sr, int kon)
		{
			LL wyn = 0;
			
			int *pom = new int [ kon - pocz + 1 ];
			
			int a = pocz, b = sr + 1, i = pocz;
			
			while( a <= sr  && b <= kon )
			{
				if( t[b] < t[a] )
				{
					pom[ i - pocz ] = t[b];
					wyn += ( sr - a + 1 );
					++b;
				}
				else
				{
					pom[ i - pocz ] = t[a];
					++a;
				}
				
				++i;
			}
			
			while( a <= sr )
			{
				pom[ i - pocz ] = t[a];
				++a;
				++i;
			}
			
			while( b <= kon )
			{
				pom[ i - pocz ] = t[b];
				++b;
				++i;
			}
			
			REP(k,pocz,kon)
			{
				t[k] = pom[ k - pocz ];
			}
			
			
			delete [] pom;
			return wyn;
		}
		
		LL Mergesort(int *t, int pocz, int kon)
		{
			if( pocz == kon )
			{
				return 0;
			}
			
			int sr = ( pocz + kon ) / 2;
			
			return Mergesort( t, pocz, sr ) + Mergesort( t, sr + 1, kon ) + Merge( t, pocz, sr, kon );
		}
		
		
		LL invertions_number1()
		{
			Permutation p = (*this);
			
			return Mergesort( p.t, 0, p.n - 1 );
		}*/
		
		LL invertions_number() // liczba inwersji
		{
			LL wyn = 0; // poczatkowo liczba inwersji wynosi 0
			
			
			Permutation p = (*this);
			
			
			
			int pocz, kon, sr, a, b, j;
			
			for(int dl=2; dl<2*p.n; dl*=2) // kazda dlugosc podciagu (byc moze mniej dla pewnych szczegolnych sytuacji) do posortowania
			{
				int *pom = new int [dl]; // tablica pomocnicza
				
				for(int i=0; i<=max(0,p.n-dl); i+=dl) // kazdy mozliwy poczatek podciagu do posortowania
				{
					pocz = i;
					kon = min(  p.n - 1,  i + dl - 1  );
					sr = pocz + ( dl / 2 ) - 1;
					
					a = pocz;
					b = sr + 1;
					
					j = pocz;
					
					while( a <= sr  && b <= kon )
					{
						if( p.t[b] < p.t[a] )
						{
							pom[j-pocz] = p.t[b];
							wyn += ( sr - a + 1 );
							++b;
						}
						else
						{
							pom[j-pocz] = p.t[a];
							++a;
						}
						
						++j;
					}
					
					while( a <= sr )
					{
						pom[j-pocz] = p.t[a];
						++a;
						++j;
					}
					
					while( b <= kon )
					{
						pom[j-pocz] = p.t[b];
						++b;
						++j;
					}
					
					REP(k,pocz,kon)
					{
						p.t[k] = pom[k-pocz];
					}
				}
				
				delete [] pom;
			}
			
			
			return wyn;
		}
		
		
		/*LL invertions_number2()
		{
			LL wyn = 0; // liczba inwersji
			
			
			int N = 1; // N = min 2^k: 2^k >= n oraz k - ca³kowite nieujemne
			
			while( N < n )
			{
				N *= 2;
			}
			
			
			int *pom = new int [N]; // ciag do znalezienia liczby inwersji
			
			REP(i,0,n-1)
			{
				pom[i] = t[i];
			}
			
			REP(i,n,N-1)
			{
				pom[i] = i + 1;
			}
			
			
			int *tmp = new int [N];
			
			
			
			int pocz, kon, sr, a, b, j;
			
			for(int dl=2; dl<=N; dl*=2) // kazda dlugosc podciagu do posortowania
			{
				for(int i=0; i<=N-dl; i+=dl) // kazdy mozliwy poczatek podciagu do posortowania
				{
					pocz = i;
					kon = i + dl - 1;
					sr = ( pocz + kon ) / 2;
					
					a = pocz;
					b = sr + 1;
					
					j = i;
					
					while( a <= sr  && b <= kon )
					{
						if( pom[b] < pom[a] )
						{
							tmp[j] = pom[b];
							wyn += ( sr - a + 1 );
							++b;
						}
						else
						{
							tmp[j] = pom[a];
							++a;
						}
						
						++j;
					}
					
					while( a <= sr )
					{
						tmp[j] = pom[a];
						++a;
						++j;
					}
					
					while( b <= kon )
					{
						tmp[j] = pom[b];
						++b;
						++j;
					}
					
					REP(k,pocz,kon)
					{
						pom[k] = tmp[k];
					}
				}
			}
			
			
			delete [] pom;
			delete [] tmp;
			return wyn;
		}*/
		
		
		int biggest_less(int *S, int x, int pocz, int kon)
		{
			int sr, wyn;
			
			while( pocz <= kon )
			{
				sr = ( pocz + kon ) / 2;
				
				if( S[sr] < x )
				{
					wyn = sr;
					pocz = sr + 1;
				}
				else
				{
					kon = sr - 1;
				}
			}
			
			return wyn;
		}
		
		int longest_increasing_subsequence()
		{
			const int INF = n + 109;
			
			
			int *S = new int [n+1];
			
			S[0] = -INF;
			
			REP(i,1,n)
			{
				S[i] = INF;
			}
			
			
			int wyn = 0;
			
			
			int ind;
			
			REP(i,0,n-1)
			{
				ind = biggest_less( S, t[i], 0, i );
				wyn = max( wyn, ind + 1 );
				S[ ind + 1 ] = t[i];
			}
			
			delete [] S;
			return wyn; 
		}
		
		friend int LCS(Permutation &a, Permutation &b); // najdluzszy wspolny podciag (niekoniecznie spojny) obu permutacji
		
		Permutation operator *= (Permutation &p) // zalozenia: obie permutacje tej samej dlugosci; wynik to (this * p) = this(p(i))
		{
			int *pom = new int [p.n];
				
			REP(i,0,p.n-1)
			{
				pom[i] = this->t[ p.t[i] - 1 ];
			}
			
			REP(i,0,p.n-1)
			{
				this->t[i] = pom[i];
			}
			
			delete [] pom;
			
			return *this;
		}
		
		Permutation operator * (Permutation &a) // zalozenia: obie permutacje tej samej dlugosci;  wynik to this[ a[i] ]
		{
			Permutation wyn;
			wyn.n = a.n;
			wyn.t = new int [wyn.n];
			
			REP(i,0,wyn.n-1)
			{
				wyn.t[i] = this->t[ a.t[i] - 1 ];
			}
			
			return wyn;
		}
		
		Permutation power(int k) // p^k;  k >= 0;  O(n*logk)
		{
			Permutation p = *this;
			
			Permutation wyn( p.n ); // permutacja identycznosciowa
			
			while( k > 0 )
			{
				if( k % 2 == 1 )
				{
					wyn *= p;
				}
				
				p *= p;
				
				k /= 2;
			}
			
			return wyn;
		}
		
		Permutation inv() // permutacja odwrotna
		{
			Permutation wyn;
			wyn.n = this->n;
			wyn.t = new int [wyn.n];
			
			REP(i,0,(this->n)-1)
			{
				wyn.t[ ( this->t[i] ) - 1 ] = i + 1;
			}
			
			return wyn;
		}
		
		Permutation operator /= (Permutation &a) // zalozenia: obie permutacje tej samej dlugosci;  wynik to this[ a[i] ]
		{
			Permutation b = a.inv();
			
			(*this) *= b;
			
			return (*this);
		}
		
		Permutation operator / (Permutation &a) // zalozenia: obie permutacje tej samej dlugosci;  wynik to this[ a[i] ]
		{
			Permutation b = a.inv();
			
			return (*this) * b;
		}
		
		int dfs(bool *pom, int *t, int i)
		{
			int wyn = 0;
			
			do
			{
				pom[ t[i] - 1 ] = true;
				
				i = t[i] - 1;
				
				++wyn;
			}
			while( pom[ t[i] - 1 ] == false );
			
			return wyn;
		}
		
		int shortest_cycle() // najkrotszy cykl
		{
			int wyn = n + 1; // najkrotszy cykl
			
			
			bool *pom = new bool [n];
			
			REP(i,0,n-1)
			{
				pom[i] = false;	
			}
			
			
			REP(i,0,n-1)
			{
				if( pom[ t[i] - 1 ] == false ) // jesli element "t[i]" nie wystapil
				{
					wyn = min(  wyn, dfs( pom, t, i )  );
				}
			}
			
			delete [] pom;
			return wyn;
		}		
		
		int longest_cycle() // najdluzszy cykl
		{
			int wyn = 0; // najdluzszy cykl
			
			
			bool *pom = new bool [n];
			
			REP(i,0,n-1)
			{
				pom[i] = false;	
			}
			
			
			REP(i,0,n-1)
			{
				if( pom[ t[i] - 1 ] == false ) // jesli element "t[i]" nie wystapil
				{
					wyn = max(  wyn, dfs( pom, t, i )  );
				}
			}
			
			delete [] pom;
			return wyn;
		}		
};


int LCS(Permutation &a, Permutation &b)
{
	a.output();
	b.output();
	
	int DP[a.n+1][b.n+1];
	
	REP(i,0,a.n)
	{
		REP(j,0,b.n)
		{
			DP[i][j] = 0;
		}
	}
	
	REP(i,1,a.n)
	{
		REP(j,1,b.n)
		{
			DP[i][j] = max( DP[i][j-1], DP[i-1][j] );
			
			//cout << a.t[i-1] << " " << b.t[j-1] << endl;
			
			if( a.t[ i - 1 ] == b.t[ j - 1 ] )
			{
				DP[i][j] = max( DP[i][j], 1 + DP[ i - 1 ][ j - 1 ] );
			}
			
			//cout << DP[i][j] << " ";
		}
		
		//cout << endl;
	}
	
	
	int wyn = DP[a.n][b.n];
	
	return wyn;
}


int main()
{
	/*
	Permutation a;
	a.input();
	
	
	Permutation b;
	b.input();
	
	cout << "c:\n";
	Permutation c = b*b;
	c.output();
	
	cout << "d:\n";
	Permutation d = a.power( 100000 );
	d.output();
	
	
	cout << endl << LCS( a, b ) << endl;
	*/
	
	/*Permutation e;
	e.input();
	e.inv().output();*/
	
	/*Permutation a, b;
	
	a.input();
	b.input();
	
	a /= b;
	
	a.output();*/
	
	/*Permutation a, b;
	a.input();
	b.input();
	
	Permutation c = a / b;
	c.output();*/
	
	Permutation a;
	a.input();
	
	cout << a.shortest_cycle() << " " << a.longest_cycle() << endl;
	
	
	
	return 0;
}
// permutacja 20-elementowa: 19 3 1 15 9 8 14 20 2 4 6 7 10 18 12 16 5 13 17 11

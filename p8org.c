//	p8.org		1996 apr 21	last modified 1998 jun 01
//
//	Shows organization of dan's p8.c.
//

#include "p8.h"

int main( int argc,char **argv )
{
	void parse( void ),scan( void );

	if ( (argc < 2) || (3 < argc) ) {
		puts( "** use is >p8 [-y] sourcefilename **" );
		exit( 1 );
	}
	if ( argc == 3 ) {
		if ( strcmp( *++argv,"-y" ) == 0 ) {
			sopt = 1;
		} else {
			printf( "** illegal option: [%s] **\n",*argv );
			exit( 1 );
		}
	}
	if ( (fps = fopen( fname = *++argv,"rt" )) == (FILE *)NULL ) {
		printf( "** can't open %s **\n",fname );
		exit( 1 );
	}
	if ( (fpe = fopen( "$$err$$","wt" )) == (FILE *)NULL ) {
		puts( "** can't open \"$$err$$\" for writing errors **" );
		exit( 1 );
	}
	scan();
	if ( nerr == 0 ) {
		parse();
	}
	return( 0 );
}

long double atold( char *a )
{
	long double tento( int );

	long double y;
	int n,p,s;
}

void baddigitstr( char *t )
{
	fprintf( fpe, e2, line,t );
	nerr++;
	lsymb = symbol[nsymb++] = 0; 
}

void closeout( void )
{
	void makename( char *,char *,char * );

	int i;
	char fasm[13];
}

int comp( int s,int *p )
{
}    

void delimiter( void )
{
	lsymb = symbol[nsymb++] = 350+(int)delim[(int)ch & 0x00ff];
	if( ch == ';')
	{
		lrw = 0;
	}
}

void emit0( int n )
{
}

void emit1( int i )
{
}

void emit2( int i,int j )
{
	void emit0( int );
}

void emit3( int i,int j,int k )
{
	void emit0( int );
}

void extradot( int d,char *t )
{
	fprintf( fpe,e0,line,d,t );
	nerr++;
	lsymb = symbol[nsymb++] = 0;
}

void floatstr( char *t )
{
	long double atold( char * );

	double x;
	int i;
}

void gencode( void )
{
	int nextr( void );
	void emit1( int ),emit2( int,int ),emit3( int,int,int );

	int l,r;
}

void getsymbol( void )
{
}
//
//	If string s is new, return -(hash+1)
//	else if found, return hash.
//	Thus (in calling function):
//		if return value y < 0, then hash = -(y+1)
//				       else hash = y.
//

int hash( char *s )
{
	int h,q;
	char *p;
}

void illegalch( void )
{
	fprintf( fpe,e1,line,ch );
	nerr++;
	lsymb = symbol[nsymb++] = 0;
}

void initparse( void )
{
	int r;
}


void initscan( void )// By Miguel - 2/16 @ 12:10 PM  added initscan function.
{
	int hash( char * );

	int h,i;
	
	ch = NEWL;
	line = nerr = nilit = nivar = nrlit = nvar = nsymb = 0;
	hash = (HASHREC *)malloc( HSIZE*sizeof( HASHREC));
	
	if( hashp == (HASHREC *)NULL )
	{
		puts( "** can't allocate hash table **" );
		exit( 1 );
	}
	
	ssp = (char *)malloc( SSIZE );
	
	if( ssp == (char *)NULL )
	{
		puts( "** can't allocate string space **");
		exit( 1 );
	}
	
	ssp1 = ssp+SSIZE;
	for(i = 0; i < HSIZE; i++)
	{
		hashp[i].ptss = (char *)NULL;
	}
	
	for( i = 0; i < sizeof( trw )/sizeof( char *); i++)
	{
		h = -(hash( trw[i] + 1));
		hashp[h].ptss = trw[i];
		hashp[h].icod = 300 + i;
	}
}

void intstr( char *t )// By Miguel - 02/16 @04:23 am - I know im up late again :P
{
	long atol( char * );

	long x;
	int i;
	// from flowchart: for some reason I dont see another mention of " nilit " on page 103
	x = atol( t );
	for(i = 0; i < nilit; i++)
	{
		if( x == ilit[i] )
		{
			return lsymb = symbol[nsymb++] = 250 + i;//flow chart says return not sure if its meant to be like this or something else..
		}
	}
	
	if( 50 <= nilit )
	{
		puts( "** too many int literals **" );
		exit(1);
	}
	
	ilit[nilit++] = x;
	lsymb = symbol[nsymb++] = 249 + nilit;
}

void letterstr( char *t )
{
	int hash( char * );

	int h,i;
	char *p;
}

void makename( char *p,char *q,char *r )
{
}

void match( void )
{
	void gencode( void );
}

int nextr( void )
{
	int r;
}
//
//	st is as follows:
//	      -st : last symbol in string (here 0 < st)
//		0 : empty string (last, following a terminal fter)
//		1 : illegal char
//		2 : delimiter
//		3 : letterstring (possibly containing digits)
//		4 : letter in digitstring
//		5 : integer
//		6 : real
//	  7,8,... : too many dots (st-5 dots)
//

int nexts( char *s,char *t )
{
	int ch2,e,st;
	static char *p;
}

void ouch( int c )
{
	putchar( c );
}

void outscan( void )
{
	void makename( char *,char *,char * ),ouch( int );

	int c,i,j,k;
	char fsym[13];
}

void parse( void )
{
	void closeout( void ),getsymbol( void ),initparse( void ),
		reduce( void ),reportbug( void ),shift( void );
}

void reduce( void )
{
	int comp( int,int * );
	void match( void );
}

void reportbug( void )
{
	void ouch( int );

	int i,j,k;
}

void scan( void )
{
	int nexts( char *,char * );
	void baddigitstr( char * ),delimiter( void ),extradot( int,char * ),
		floatstr( char * ),illegalch( void ),initscan( void ),
		intstr( char * ),letterstr( char * ),outscan( void );

	int st;
	char s[MAXL+1],t[MAXL+1];
}

void shift( void )
{
}

long double tento( int n )
{
	long double y,z;
}

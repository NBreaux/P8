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
	y=(long double)0;
	/* this statement is completely legal in c */
	n = p = s = 0;
	// Danny - I can't tell if this is a space or just supposed to be nothing '' 
	/* Miguel - looks like a space chararecter */
	while ((*a==' ')||(*a=='\t'))
	{
		a++;
	}
	
	if(*a=='-')
	{
		a++;
		s++;
	}
	
	while(isdigit(*a))
	{
		y=((long double)10*y+(long double)((a++)-'0'));
	}
	
	if(*a=='.')
	{
		a++;
		while(isdigit(*a))
		{
 			p++;
 			y=((long double)10*y+(long double)((a++)-'0'));
		}
	}
	if ((*a=='e')||(*a=='E'))
	{  
		/* Miguel - atoi is a function of see that converts ascii chars to integers */           
		// Danny - what the hell is atoi
		n=atoi(++a);
	}
	y=y*tento(n-p);
	
return(s ? -y : y);

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
	
	if(!isdigit(*(t+strlen(t)-1)))
	{
		fprintf(fpe,e2,line,t);
		nerr++;
		lsymb = symbol[nsymb++]= 0;
		return;
	}
	
	x=atold(t);
	for(i=0; i < nrlit; i++)
	{
		if(x==rlit[i];)
		{
			lsymb = symbol[nsymb++] = 200+i;
			return;
		}
	}
		/* the else wasn't necessary - Miguel  */
		/* If i isnt less then nrlit then it'll go to the if statement below
			 which will then lead us to the end of the function */
	//I dont know if I need the else here but it looks like I may - Danny
	if(50<=nrlit)
	{
		puts("** too many real literals **");
		exit(1);
	}
	else
	{
		rlit[nrlit++] = x;
		lsymb=symbol[nsymb++]=199+nrlit;
	}
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
	/* I cant remember but can we just leave a for loop without braces? */
	for( p = s, q = 0; *p; q = q+(int)*p, p++)
	
	h = ( q % HSIZE ) - 1;
	
	for(q=0;;){
		if(HSIZE <= ++h){
			h = 0;
		}
		else if( hashp[h].ptss == (char*)NULL){
			return( -(h+1));
		}
		else if( strcmp( s, hashp[h].ptss) == 0){
			return( h );
		}
		else if( HSIZE <= ++q ){
			puts( "** hash table overflow **");
			exit(1);
		}
	}
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

	x = atol( t );
	for(i = 0; i < nilit; i++)
	{
		if( x == ilit[i] )
		{
			lsymb = symbol[nsymb++] = 250 + i;
			return;
		}
	}
	else{
		if( 50 <= nilit )
		{
			puts( "** too many int literals **" );
			exit(1);
		}
	  else
		{
			ilit[nilit++] = x;
			lsymb = symbol[nsymb++] = 249 + nilit;
		}
	}
}

void letterstr( char *t )
{
	int hash( char * );

	int h,i;
	char *p;
	
	h = hash( t );
	
	if( 0 <= h){
		i = hashp[h].icod;
		if( i == 0 ){
			fprintf( fpe, e4, line, t );
			nerr++;
		}
	else
	{
		if((i < 200) && ((lrw == 300) || (lrw == 301))){
			fprintf( fpe, e3, line, t );
			nerr++;
		}
		else{
			if( 300 <= i)
				lrw = i;
			else
				lsymb = symbol[nsymb++] = i;
		}
	 }
	}
	else{
		if( ssp1 <= ssp+strlen( t ) ){
			puts( "** out of string space **" );
			unlink( "$$err$$");
			fclose( fps );
			exit(1);
		}
		else{
			h = -(h + 1);
			hashp[h].ptss = ssp;
			p = t;
			
			while( (*ssp++ = *p++) != EOS);
			
			if( lrw == 300 ){
				var[nrvar] = hashp[h].ptss;
				lsymb = symbol[nsymb++] = hashp[h].icod = 100 + (nivar++);
				return;
			}
			else{
				if( lrw == 301 ){
					var[50+nivar] = hashp[h].ptss;
					lsymb = symbol[nsymb++] = hashp[h].icod = 150 + (nivar++);
					return;
				}
				else{
					fprintf( fpe, e4, line, t);
					nerr++;
					lsymb = symbol[nsymb++] = hashp[h].icod = 0;
				}
			}
		}
	}
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
	e = st = 0;
	
	if (ch == NEWL){
		p=s;
	}
	while (l) // that's and L
	{
       /* forgot this */
		ch = *p;
		ch2 = (((int)ch)<< 8) + ((int)*(p+1));

		switch(ch2)
		{ 
			/* Forgot to add p++ to the cases Also it seems that NEWL is defined in p8.h */
			case 0x2f2f: ch = NEWL; break;		// "//" also we may need to define NEWL somewhere
			case 0x3c3d: ch = (char)128; p++; break; // "<="
			case 0x3d3d: ch = (char)129; p++; break; // "=="
			case 0x213d: ch = (char)130; p++; break; // "!="
			/* I dont see this on page one anywhere Danny - Miguel */
			/*case 0x3e3d: ch = (char)131; break; // ">=" for p8'*/
			default:		
				switch( (int)kind[(int)ch & 0x00ff])
				{
					case 0:	*t = EOS; 
								 	return (-st);

					case 1:	if (st == 0){
									st = 3;
									}
									
									if (((ch == 'e')||(ch == 'E')) && ((st == 5) || (st==6)) 
										&& (e==0))
									{
										st =6;
										e++;
									}
 									
									else
									{
										if (4 < st){
											st = 4;
										}
									}

				 case 2: 	if (st==0)
								 	{
										st=5;
									}
									p++; 
									*t++=ch;
 									break;

				 case 3: 	if (st==0)
 									{
										*t++=ch;
 										p++;
                    //364 may need to be modified for p8'
										if ((ch=='-')&&isdigit(*p) && ((lsymb==303)||(lsymb ==352)||(lsymb==354)||
											((358<lsymb)&&(lsymb<364))))
										{
											st = 5;
											break;
 										}
										else
 										{
											*t=EOS;
											return (2);
										}
									}
 									else
									{
										if(st==3)
										{
											*t=EOS;
											return(3);
										}
										else
 										{
											if((ch=='-')&&((*(t-1)=='e')||(*(t-1)=='E')))
											{
												p++;
												*t++=ch;
												break;
											}
											else
											{
 												if(ch=='.')
												{
													*t++=ch;
													p++;
													
													if(4 < st)
													{
														st++;
													}
													break;
												}
												else
												{
													*t=EOS;
													return (st);
												}
											}
										}
									}
				 case 4:
 								p++;
								if(st)
								{
									*t=EOS;
									return(st);
								}
								else
									break;
				 case 5:
								if (st == 0)
								{
									p++;
									return(l);
								}
								else
								{
 									*t=EOS;
									return(st);
								}
			  }
 		}
  }
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

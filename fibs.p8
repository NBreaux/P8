{
	int a,b,c,n;

	input n;
	a = -1;
	b = 1;
	repeat ( n+1 ) {
		c = a;
		a = b;
		b = b+c;
		output b;
	}
}

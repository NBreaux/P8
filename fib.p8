{
	int n,next,prev,temp;

	n = -1;
	prev = -1;
	next = 1;
	while ( n < 10 ) {
		n = n+1;
		temp = prev;
		prev = next;
		next = temp+next;
		output n,next;
	}
}

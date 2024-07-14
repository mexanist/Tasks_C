int div(int *ptr1, int *ptr2){
	if (*ptr2 == 0){
		return -1;
	} else {
		return (*ptr1) / (*ptr2);
	}
}

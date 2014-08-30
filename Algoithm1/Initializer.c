



int readParameters(int *T, int *d_max, int *I0, double *h, double *p, double *c, double *k, double *pr, double *dk, int argc, char *argv[])
{
	double pr1,pr2,pr3,dk1,dk2,dk3

	if (argc != 2)
	{
		char szBuff[80];
		sprintf(szBuff, "No file/too many files given!");
		ERROR(szBuff);
	}

	READ_INT(argv[1], *T);
	READ_INT(argv[1], *d_max);
	READ_INT(argv[1], *I0);
	READ_DOUBLE(argv[1], *h);
	READ_DOUBLE(argv[1], *p);
	READ_DOUBLE(argv[1], *c);
	READ_DOUBLE(argv[1], *k);
	READ_DOUBLE(argv[1], pr1);
	READ_DOUBLE(argv[1], pr2);
	READ_DOUBLE(argv[1], pr3);
	READ_DOUBLE(argv[1], dk1);
	READ_DOUBLE(argv[1], dk2);
	READ_DOUBLE(argv[1], dk3);

	dk[0] = dk1;
	dk[1] = dk2;
	dk[2] = dk3;
	pr[0] = pr1;
	pr[0] = pr2;
	pr[0] = pr3;

	return 0;
}

void init_E(double *E, int d_max, int T)
{
	int a, b;
	for (a = 0; a <= T+1; a++)
		for (b = 0; b <= 2*d_max; b++)
			E[a][b] = 0;
}
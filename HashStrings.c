int main()
{
	char* STR[10]; // массив строк
	char** s = 0; // указатель на массив строк
	int* skip = 0; // массив найденных строк
	char buf[80]; // массив куда заносится введенная с клавиатуры консоль
	int n = 0; // счетчик числа введённых строк
		// ПРОЦЕДУРА ВВОДА
	printf("\nPlease input String, to go to the next entry, press /Enter/. To stop - press /Enter/ 1 more time\n");
	for (s = STR;; n++, s++) { //считываем данные в buf
		*s = input(s, buf, n);
		if (*s == 0) {
			printf("\a");
			break;
		}
	}

	skip = (int*)malloc(n * sizeof(int));
	if (!skip) {
		printf("Allocation error.");
		exit(1);
	}

	printf("------------------------------------------\n");
	compareFun(STR, n, s, skip);
	for (int i = 0; i < n; i++) {
		s = STR + i;
		free(*s);
	}
	free(skip);
	printf("\n------program_completed_successfully------\n");
	return 0;
}

int compareFun(char** STR, int n, char** s, int* skip)
{
	int i, j;
	int amount = 0; // кол-во уже найденых строк
	unsigned hashCompare;
	int group = 1;

	for (i = 0; i < n; i++) {
		s = STR + i;
		if (skipChek(i, skip, amount)) continue;
		hashCompare = hash(s);
		printf("\nGroup %d:\n", group++);

		for (j = 0; j < n; j++) {
			s = STR + j;
			if (hashCompare == hash(s)) {
				if (skipChek(j, skip, amount) == 0) {
					skip[amount++] = j;
				}
				printf("%2d) ", j + 1);
				puts(*s);
			}
		}
	}
	return 0;
}

unsigned hash(char** s)
{
	int d = 0;
	unsigned hashval;
	for (hashval = 0; (*(*s+d)) != '\0'; d++)
		hashval = *(*s + d) + 31 * hashval;
	return hashval % HASHSIZE;
}


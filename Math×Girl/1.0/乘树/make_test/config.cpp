#include <cstdio>

int main() {
	freopen("config.yml", "w", stdout);
	for (int i = 1; i <= 20; ++i) {
		if (i <= 2) {
			printf("%d.in:\n  subtaskId: 0\n  score: 10\n\n", i);
		} else if (i <= 5) {
			printf("%d.in:\n  subtaskId: 1\n  score: 15\n\n", i);
		} else if (i <= 10) {
			printf("%d.in:\n  subtaskId: 2\n  score: 25\n\n", i);
		} else if (i <= 20) {
			printf("%d.in:\n  subtaskId: 3\n  score: 50\n\n", i);
		}
	}
	return 0;
}

#include <cstdio>

int main() {
	freopen("config.yml", "w", stdout);
	for (int i = 1; i <= 20; ++i) {
		if (i <= 2) {
			printf("%d.in:\n  subtaskId: 0\n  score: 10\n\n", i);
		} else if (i <= 4) {
      printf("%d.in:\n  subtaskId: 1\n  score: 10\n\n", i);
    } else if (i <= 8) {
			printf("%d.in:\n  subtaskId: 2\n  score: 20\n\n", i);
		} else if (i <= 12) {
			printf("%d.in:\n  subtaskId: 3\n  score: 20\n\n", i);
		} else if (i <= 16) {
      printf("%d.in:\n  subtaskId: 4\n  score: 20\n\n", i);
    } else if (i <= 20) {
      printf("%d.in:\n  subtaskId: 5\n  score: 20\n\n", i);
    }
	}
	return 0;
}

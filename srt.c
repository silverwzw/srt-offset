#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define SKIP 24

int h[3],m[3],s[3],ms[3];

void gl(char *bf) {
	if (gets(bf) == NULL) {
		exit(0);
	}
}

void offset() {
	assert(h[0] >= 0);

	ms[2] -= ms[0];
	s[2] -= s[0];
	m[2] -= m[0];
	h[2] -= h[0];
	ms[1] -= ms[0];
	s[1] -= s[0];
	m[1] -= m[0];
	h[1] -= h[0];

	if(ms[2] < 0) {
		ms[2] += 1000;
		s[2]--;
	}
	if(s[2] < 0) {
		s[2] += 60;
		m[2]--;
	}
	if(m[2] < 0) {
		m[2] += 60;
		h[2]--;
	}
	assert(h[2] >= 0);

	if(ms[1] < 0) {
		ms[1] += 1000;
		s[1]--;
	}
	if(s[1] < 0) {
		s[1] += 60;
		m[1]--;
	}
	if(m[1] < 0) {
		m[1] += 60;
		h[1]--;
	}
	assert(h[1] >= 0);
}

int main(void) {
	char buff[2048];
	int lineno;
	h[0] = -1;
	while (1) {
		gl(buff);
		while (buff[0] == '\r' || buff[0] == '\0') {
			gl(buff);
		}
		sscanf(buff,"%d",&lineno);
		if(lineno <= SKIP) {
			gl(buff);
			while(buff[0] != '\r' || buff[0] == '\0') {
				gl(buff);
			}
			continue;
		}
		printf("%d\n",lineno-SKIP);
		gl(buff);
		sscanf(buff, "%2d%*c%2d%*c%2d%*c%3d%*s%2d%*c%2d%*c%2d%*c%3d",&h[1],&m[1],&s[1],&ms[1],&h[2],&m[2],&s[2],&ms[2]);
		if (h[0] == -1) {
			h[0] = h[1];
			m[0] = m[1];
			s[0] = s[1];
			ms[0] = ms[1];
		}
		offset();
		printf("%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d\n",h[1],m[1],s[1],ms[1],h[2],m[2],s[2],ms[2]);
		gl(buff);
		while(buff[0] != '\r' || buff[0] == '\0') {
			puts(buff);
			gl(buff);
		}
		putchar('\n');
	}
}

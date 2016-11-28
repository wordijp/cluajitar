#include <stdio.h>
#include <string.h>

#include "cluajitar.h"

int main(int argc, char *argv[])
{
	{
		/* archive */
		const char *files[] = {
			"data/hello_one.txt",
			"data/hello_two.txt",
			"data/hello_three.txt"
		};

		FILE *fp = fopen("cluajitar.dat", "wb");
		if (!fp) {
			perror("cluajiter.dat");
			return -1;
		}

		printf("write: size%ld\n", cluajitar_write(files, 3, fp));

		fclose(fp);
	}

	{
		/* load from archiver */
		FILE *fp = fopen("cluajitar.dat", "rb");
		struct cluajitar_header_content *content = cluajitar_load(fp);
		if (!content) {
			fprintf(stderr, "cluajitar_load failed");
			fclose(fp);
			return -1;
		}

		char *buf = cluajitar_load_file("data/hello_two.txt", fp, content);

		printf("* from cluajitar_load_file - - -\n");
		printf(buf);

		cluajitar_free_file(buf);
		cluajitar_free(content);
		fclose(fp);
	}

	{
		/* load from archiver (manual) */
		FILE *fp = fopen("cluajitar.dat", "rb");
		struct cluajitar_header h;
		fread(&h, sizeof(h), 1, fp);

		long offset = ftell(fp);
		long skip_size = 0;

		uint32_t size = 0;

		for (uint32_t i = 0; i < h.file_count; ++i) {
			struct cluajitar_file_header fh;
			fread(&fh, sizeof(fh), 1, fp);

			if (strcmp(fh.name, "data/hello_three.txt") == 0) {
				fseek(fp, offset + sizeof(fh) * h.file_count + skip_size, SEEK_SET);
				size = fh.file_size;
				break;
			}

			skip_size += fh.file_size;
		}

		char buf[size];
		fread(buf, 1, size, fp);

		printf("* from manual load - - -\n");
		printf(buf);

		fclose(fp);
	}

	return 0;
}

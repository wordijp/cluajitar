# README for cluajitar v0.0.1
=============================

very simple archives for [cLuaJIT](https://github.com/wordijp/cLuaJIT)

# file format

this meta data is minimum, archives support only, extract is not supported

|Format|Fixed or Variable length|Number|
|---|---|---|
|cluajitar_header|Fixed|N:1|
|cluajitar_file_header|Fixed|N:file_count|
|file data|Variable|N:file_count|


## header format

top header (N:1)

```
struct cluajitar_header {
	char magic[4]; /* "ljar" */
	uint32_t file_count;
};
```


file header (N:file_count)

```
struct cluajitar_file_header {
	char name[100]; /* equal tar file format */
	uint32_t file_size;
};
```


## file data format

file data (N:file_count)

```
char buf[file_size];
```


# usage

see example


# license

MIT license

# Raylib Example

![Screenshot-2024-05-31_23:59:29](https://github.com/KDesp73/raylib-example/assets/63654361/800844ce-50d6-4e38-a3df-cb09500ec3e5)

## Build and Run

```sh
git clone https://github.com/KDesp73/raylib-example
cd raylib-example
cc -Wall -Iinclude -Iraylib/raylib-5.0_linux_amd64/include -o raylib_example raylib_example.c -L./raylib/raylib-5.0_linux_amd64/lib -lm -lpthread -ldl -l:libraylib.a
./raylib_example
```

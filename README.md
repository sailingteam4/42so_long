# 42 So_long

This is a project developed as part of the 42 cursus. It uses the MiniLibX, a simple graphics library used in the 42 cursus.

## Cloning the repository

To clone the repository, use the following command:
```sh
git clone --recurse-submodules https://github.com/sailingteam4/42so_long.git so_long
```

This project uses git submodules for the MiniLibX library. After cloning the repository, with the above command, you should have the MiniLibX library in the `mlx_linux` folder.

## Building and Running the Project

To build the project, use the provided Makefile:
```sh
make
```

To run the project, use the following command:
```sh
./so_long <map.ber>
```
Replace `<map.ber>` with the path to the map file you want to use.

## So_long Tester

I have created a tester for this project, you can run it with the following command:
```sh
sh test.sh
```

## About the 42 Cursus
The 42 cursus is a software engineering program that emphasizes peer-to-peer learning, where students learn from each other in a project-based environment. This project is part of the cursus and is designed to help students learn about graphics programming with the MiniLibX library.
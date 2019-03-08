# Hiden

## About Hiden
Hiden is a CLI (Command Line Interface) program written in the C++ Programming Language, which uses its very own and unique encryption algorithm (custom made one). It generates a random key depending on the entered password, which is then applied to the data that is going to be encrypted/decrypted using XOR encryption. Originally developed as an Computer Security course project.

## About The Program's Name Origin
Hiden (秘伝) from Japanese, meaning: secret, is the name of the encryption program; the name was chosen as the meaning of the program’s purpose. Since the main use of encryption is data confidentiality; hence the name: secret for the program.

## :warning: Warning!
Hiden is a encryption program for study or educational purposes only, to better understand encryption of files, **do not** use it to encrypt any sensitive or valuable files! Nor it is meant to replace standard encryption algorithms or software.

## Building Hiden
`Git clone` [this repository](https://github.com/vargaspeniel/hiden.git) to any viable directory (e.g. Downloads) on your computer, change to `hiden` directory and either directly compile the source file, using any C++ compiler like `gnu-gcc`, or run `make` to automate the compiling process, and then run the generated executable file: `./bin/hiden`.

## Translation Generation & Testing
To automatically generate a po file to translate the program to your desired language using `xgettext`: go to the `Makefile` and add your desired language code (e.g. es = Spanish, ko = Korean, ja = Japanese.) to the `LANGS` variable, run `make locale` to generate your language `xx.po` file for the program, then go to the `locale` directory and look for your language `xx.po` file, translate its contents, and run `make build locale`. To test your translation: just run `make test` and execute the program; that is, if your `LANG` environment variable is set to the same language as the `xx.po` file, if not, manually set it like this: e.g. `LANG=ja_JP-UTF-8 ./bin/hiden`.

## License
Copyright (C) 2014-2019  Peniel Vargas

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
[COPYING file](./COPYING) for more details.

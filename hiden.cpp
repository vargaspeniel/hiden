/*
 * Copyright (C) 2014-2019  Peniel Vargas <tsuneake.kaemitsu@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

/* Using Declarations */
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::fstream;
using std::ios;

/* Function Prototypes */
void menu();
void finish();
void fselection();				// Acronym for: "File Selection"
string encrypt(string password, string text);

/* Start of the Program */
int main()
{
	menu();
	fselection();
	finish();
	return 0;
}

/* Program Main Menu */
void menu()
{
	/* Program Information & Description */
	cout << "Hiden, Encryption Program\n"
		 << "Copyright (C) 2014-2019 Peniel Vargas\n\n"
		 << "This program comes with ABSOLUTELY NO WARRANTY.\n"
		 << "This is free software, and you are welcome to\n"
		 << "redistribute it under certain conditions\n\n"
		 << "Course: COMP 3410 - Computer Security\n"
		 << "Class Project: Encryption Program Project"
		 << endl
		 << endl
		 << "Hiden from Japanese, meaning: secret, is a simple encryption program\n"
		 << "written in the C++ Programming Language, which uses its very own and\n"
		 << "unique encryption algorithm. Hiden is a CLI (Command Line Interface)\n"
		 << "program which provides the user with a way to encrypt files."
		 << endl
		 << endl;
}

/*
	Depending on the user's answer,
	reruns or exits the program.
 */
void finish()
{
	string state;

	cout << endl
		 << "Do you wish to run the program again? (Yes/No) ";
	getline(cin, state, '\n');

	if (("Yes" == state) || ("yes" == state))
	{
		/*
			Depending on the OS, runs a statement
			that clears the CLI screen, accordingly;
			then restarts the program by calling main.
		 */
		#ifdef __linux__
			system("reset");
		#endif
		#ifdef __WIN32
			system("cls");
		#endif

		main();
	}
	else if (("No" == state) || ("no" == state))
		return;
	else
	{
		cout << endl
			 << "Invalid Option!\n"
			 << "Program Terminated.\n\n"
			 << "Press the [enter] key to exit...";
		cin.clear();			// Clears the input buffer
		cin.get();				// Waits for an input operation
		return;
	}
}

/*
	Shows the requirements & instructions needed
	for the appropriate selection of a file to be
	encrypted/decrypted.

	Opens the file for reading, extracting its contents
	to a string object, which is then pass as an argument
	to the encrypt function.
 */
void fselection()
{
	/*
		fstream file object, use for I/O
		(input/output) operations on files.
	 */
	fstream file;
	string filename, password, text;

	cout << "File Selection\n\n"
		 << "To Encrypt/Decrypt a File:\n"
		 << "1) The file must be present in the program current directory.\n"
		 << "2) The filename must contain its file extension, if it has one.\n"
		 << "3) A unique password is required."
		 << endl
		 << endl
		 << "Note: The password will be required when decrypting the file.\n"
		 << "If the password is enter incorrectly, when trying to decrypt the file,\n"
		 << "the file will be encrypted again; making its decryption nearly impossible."
		 << endl
		 << endl
		 << "Filename:";
	getline(cin, filename, '\n');	// Stores in filename a text line entered at the CLI
	cout << "Password:";
	getline(cin, password, '\n');	// Stores in password a text line entered at the CLI

	/*
		Associates 'filename' contents with the 'file' fstream object;
		opening the file for I/O operations. If the file is successfully
		opened, extracts and appends its contents, character by character,
		to 'text' until the end of the file is reach, then closes the file.

		Reopens the file, passing 'password' and 'text' as arguments
		to the encrypt function; which will return a string containing
		the encrypted file contents; writes it to the file, and closes it.
	 */
	file.open(filename, ios::in | ios::out | ios::binary);
	if (file.is_open())
	{
		while (!file.eof())
			text.push_back(file.get());
		file.close();

		file.open(filename, ios::in | ios::out | ios::binary);
		file << encrypt(password, text);
		file.close();
	}
	else
		cout << endl
			 << "Such a file does not exist!\n"
			 << "Perhaps, the file extension was missing\n"
			 << "or the file is not in the program's directory."
			 << endl;
}

/*
	Base on the entered password, generates a
	unique key applying it to the file contents
	using XOR encryption.

	The more complex the password is, the better
	the encryption of the file contents will be.
 */
string encrypt(string password, string text)
{
	string key {password};
	unsigned int chr {0U};

	/*
		Before the key is generated, the values of 'password',
		in order, will be multiplied by its total length of characters;
		then, in reverse order, the values of 'password' will be added to
		the previously obtained results of the multiplication operation;
		this will result in the generation of the encryption key.
	 */
	for (; chr < password.size(); chr++);
	for (unsigned int pos {0U}; pos < key.size(); pos++)
		key[pos] = password[--chr] + password[pos] * password.size();

	/*
		Using the previously generated key, applies
		XOR encryption/decryption to the file contents.
	 */
	for (unsigned int ch {0U}; ch < text.size(); ch++)
		text[ch] ^= key[ch % key.size()];

	/*
		Removes the null character prensent at the
		end of the file, before saving the file.
	 */
	text.pop_back();

	return text;
}

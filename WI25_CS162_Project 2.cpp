/*
* Author: Lily Zhen
* Descrption: A program that reads a wizard info file and a spellbook info file.
* 	Prompts for login info and allows user to access spellbook info file upon 
* 	successful login. Spellbook info file is then able to be displayed in 3 
* 	different ways; display all, search book by name, and search spell by effect.
*/

#include <iostream>
#include <fstream>
#include <string>

struct spell {
	std::string name;
	float success_rate;
	std::string effect;
};

struct spellbook {
	std::string title;
	std::string author;
	int num_pages;
	int edition;
	int num_spells;
	float avg_success_rate;
	spell *spells;
};

struct wizard {
	std::string name;
	int id; // Used for logging in
	std::string password; // Used for logging in
	std::string position_title; // Used to restrict poison and death spells
	float beard_length;
};

/*
 * Function: create_spells
 * Description: Allocates a dynamic array of spells of the requested size and
 * 		returns a pointer that points to it
 * Parameters:
 * 		size (int): Size of dynamic array of spells to create
 * Returns: Pointer that points to dynamically allocated array of spells
 */
spell* create_spells(int size) {
	spell* p_spells = new spell[size];

	return p_spells;	
}

/*
 * Function: read_spell_data
 * Description: Reads all of the information associated with a single spell
 * 		structure from the given spellbooks text file and returns a created
 * 		spell structure containing that information.
 * Parameters:
 * 		file (std::ifstream&): A reference to an std::ifstream that is open on
 * 		the input spellbooks text file and prepared to read information about
 * 		the next spell in a spellbook.
 * Returns: The created spell structure containing the information of the
 * 		next spell in the input file
 */
spell read_spell_data(std::ifstream& file) {
	spell s;

	file >> s.name;
	file >> s.success_rate;
	file >> s.effect;

	return s;
}

/*
 * Function: size_spellbooks
 * Description: Reads the number of spellbooks in a spellbook info text file.
 * Parameters:
 * 		file (std::ifstream&): Reference to std::ifstream that is open on the
 * 		input spellbooks text file.
 * Returns: The number of spellbooks in a spellbook file.
 */
int size_spellbooks(std::ifstream& file) {
	int num_spellbooks;
	file >> num_spellbooks;
	
	return num_spellbooks;
}

/*
 * Function: create_spellbooks
 * Description: Allocates a dynamic array of spellbooks of the requested size.
 * Parameters:
 * 		size (int): Size of dynamic array of spellbooks to create
 * Returns: Pointer that points to dynamically allocated array of spellbooks
 */
spellbook* create_spellbooks(int size) {
	spellbook* p_spellbooks = new spellbook[size];

	return p_spellbooks;
}

/*
 * Function: read_spellbook_data
 * Description: Reads all of the information associated with a single spellbook
 * 		structure from the given spellbooks text file and returns a created
 * 		spellbook structure containing that information. Note that the
 * 		avg_success_rate member variable of the returned spellbook structure is
 * 		not contained in the text file, but rather will need to be computed as
 * 		the average (mean) success rate of all spells in the spellbook (i.e.,
 * 		add up the success rates of all spells in the spellbook, then divide by
 * 		the number of spells in the spellbook).
 * Parameters:
 * 		file (std::ifstream&): A reference to an std::ifstream that is open on
 * 		the input spellbooks text file and prepared to read information about
 * 		the next spellbook.
 * Returns: The created spellbook structure containing the information of the
 * 		next spellbook in the file
 */
spellbook read_spellbook_data(std::ifstream& file) {
	spellbook sb;

	file >> sb.title;
	file >> sb.author;
	file >> sb.num_pages;
	file >> sb.edition;
	file >> sb.num_spells;

	// create dynamic array of spells
	sb.spells = create_spells(sb.num_spells);

	// populate dynamic array of spells with spell structures
	for (int i = 0; i < sb.num_spells; i++) {
		sb.spells[i] = read_spell_data(file);
	}

	// calculate average success rate of spellbook's spells
	sb.avg_success_rate = 0;
	for (int i = 0; i < sb.num_spells; i++) {
		sb.avg_success_rate += sb.spells[i].success_rate;
	}
	sb.avg_success_rate = sb.avg_success_rate / sb.num_spells;

	return sb;
}

/*
 * Function: populate_spellbooks
 * Description: Populates dynamic array of spellbook structures using spellbook info file.
 * Parameters:
 * 		spellbook_info (std::ifstream&): A reference to std::ifstream that is open
 * 		on a spellbook info file.
 * 		num_spellbooks (int): Size of dynamic array of spellbook structures.
 * Returns: A pointer to a dynamic array populated with spellbook structures using
 * 		info from the spellbook info file. 
 */
spellbook* populate_spellbooks(std::ifstream& spellbook_info, int num_spellbooks) {
	// store spellbook file info to memory
	// assigns pointer to a dynamic array of spellbooks
	spellbook* spellbooks_array = create_spellbooks(num_spellbooks);

	// populate spellbooks array with spellbook structures 
	for (int i = 0; i < num_spellbooks; i++) {
		spellbooks_array[i] = read_spellbook_data(spellbook_info);
	}

	// returns pointer to dynamic array
	return spellbooks_array;
}

/*
 * Function: delete_spells
 * Description: Deletes a given dynamic array of spells and updates its pointer
 * 		to be nullptr.
 * Parameters:
 * 		spells (spell*&): A reference to the pointer that points to the dynamic
 * 			array of spells to be deleted.
 * Post-conditions: 1. Dynamic array of spells should be deleted. 2. spells
 * 		pointer parameter should be set to nullptr. Since this parameter is
 * 		passed by reference, the corresponding argument will be set to nullptr
 * 		as well.
 */
void delete_spells(spell*& spells) {
	delete[] spells;
	spells = nullptr;
}

/*
 * Function: delete_spellbooks
 * Description: Deletes all of the dynamic memory associated with the given
 * 		array of spellbooks, including the arrays of spells inside each
 * 		spellbook. The size parameter indicates the size of the array of
 * 		spellbooks.
 * Parameters:
 * 		spellbooks (spellbook*&): A reference to the pointer that points to the
 * 			dynamic array of spellbooks to be deleted
 * 		size (int): Number of spellbooks
 * Post-conditions: 1. Dynamic arrays of spells within each spellbook should
 * 		be deleted (see hint). 2. Dynamic array of spellbooks should be deleted.
 * 		3. spellbooks pointer parameter should be set to nullptr. Since this
 * 		parameter is passed by reference, the corresponding argument will be set
 * 		to nullptr as well.
 */
void delete_spellbooks(spellbook*& spellbooks, int size) {

	for (int i = 0; i < size; i++) {
		delete_spells(spellbooks[i].spells);
	}
	
	delete[] spellbooks;
	spellbooks = nullptr;
}

/*
 * Function: size_wizards
 * Description: Reads the number of wizards in a wizard info text file.
 * Parameters:
 *  	file (std::ifstream&): A reference to std::ifstream that is open on the
 * 		input wizard text file.
 * Returns: The number of wizards in the wizards file.
 */
int size_wizards(std::ifstream& file) {
	int num_wizards;
	file >> num_wizards;

	return num_wizards;
}

/*
 * Function: create_wizards
 * Description: Creates a dynamic array of wizards of the requested size.
 * Parameters:
 * 		size (int): size of dynamic wizard array
 * Returns: A pointer that points to a dynamic array of wizards.
 */
wizard* create_wizards(int size) {
	wizard* p_wizard = new wizard[size];

	return p_wizard;
}

/*
 * Function: read_wizard_data
 * Description: Reads the wizard data for the ID and password input by user.
 * Parameters:
 * 		file (std::ifstream&): A reference to a std::ifstream that is open on
 * 		the input wizards info text file.
 * Returns: A wizard structure containing the information from the 
 * 		wizard info text file.
 */
wizard read_wizard_data(std::ifstream& file) {
	wizard wiz;

	file >> wiz.name;
	file >> wiz.id;
	file >> wiz.password;
	file >> wiz.position_title;
	file >> wiz.beard_length;

	return wiz;
}

/*
 * Function: populate_wizards 
 * Description: Populates a dynamic array of wizard structures using wizard info file.
 * Parameters:
 * 		wizard_info (std::ifstream&): A reference to std::ifstream that is open on
 * 		a wizard info file.
 * 		num_wizards (int): Size of dynamic array of wizard structures.
 * Returns: A pointer to a dynamic array of wizard structures.
 */
wizard* populate_wizards(std::ifstream& wizard_info, int num_wizards) {
	// store wizard file info to memory
	// create dynamic array of wizards, reading first line of ifstream file for size
	wizard* wizards_array = create_wizards(num_wizards);

	//populate wizards array with wizard structures
	for (int i = 0; i < num_wizards; i++) {
		wizards_array[i] = read_wizard_data(wizard_info);
	}
	return wizards_array;
}

/*
 * Function: delete_wizards
 * Description: Deletes all of the dynamic memory associated with the given
 * 		array of wizards.
 * Parameters:
 * 		spellbooks (spellbook*&): A reference to the pointer that points to the
 * 			dynamic array of wizards to be deleted
 * Post-conditions: Dynamic array of wizards should be deleted and wizards 
 * 		pointer parameter should be set to nullptr.
 */
void delete_wizards(wizard*& wizards) {
	delete[] wizards;
	wizards = nullptr;
}

/*
 * Function: wizard_file
 * Description: Prompts the user for the name of the file that holds information
 * 		about wizards.
 * Returns: The user's string input for wizard info file name.
 */
std::string wizard_file() {
	std::string file_name;

	std::cout << "Enter the wizard info file name: ";
	std::cin >> file_name;
	
	return file_name;
}

/*
 * Function: spellbook_file
 * Description: Prompts the user for the name of the file that holds spellbooks
 * 		and spells information.
 * Returns: The user's string input for spellbook info file name.
 */
std::string spellbook_file() {
	std::string file_name;

	std::cout << "Enter the spellbook info file name: ";
	std::cin >> file_name;

	return file_name;
}

/*
 * Function: file_prompt
 * Description: Attempts to open wizard info and spellbook info file inputs.
 * 		If a file open fails, program prints error message and terminates.
 * Parameters:
 * 		wizard_file (std::ifstream&): A reference to a std::ifstream for wizard info.
 * 		spellbook_file (std::ifstream&): A reference to a std::ifstream for spellbook info.
 * Returns: Boolean value 0, or 1 if both files open successfully.
 * Side effects:
 * 		Prints error messages to terminal if file open fails.
 * 		Modifies std::ifstreams to open wizard or spellbook file.
 */
bool file_prompt(std::ifstream& wizard_info, std::ifstream& spellbook_info) {
	bool opened_files = 0;

	wizard_info.open(wizard_file());
	if (wizard_info.fail()) {
		std::cout << "Error: wizard file not found." << std::endl;
		return opened_files;
	} 
	spellbook_info.open(spellbook_file());
	if (spellbook_info.fail()) {
		std::cout << "Error: spellbook file not found." << std::endl;
		return opened_files;
	} else {
		opened_files = 1;
		return opened_files;
	}
}

/*
 * Function: id_prompt
 * Description: Prompts user for login ID.
 * Returns:The user's integer ID input.
 */
int id_prompt() {
	int user_id;

	std::cout << "Enter your ID: ";
	std::cin >> user_id;

	return user_id;
}

/*
 * Function: password_prompt
 * Description: Prompts user for login password.
 * Returns: The user's string password input.
 */
std::string password_prompt() {
	std::string user_pass;

	std::cout << "Enter your password: ";
	std::cin >> user_pass;

	return user_pass;
}

/*
 * Function: log_in
 * Description: Prompts user for login info. Then reads array of wizard structures
 * 		for one that matches the ID and password input by user.
 * Parameters:
 * 		wizard_array (wizard*): A pointer to a dynamic array of wizard structures. 
 * 		num_wizards (int&): A reference to the number of wizards in dynamic array of wizards. 
 * Returns: Boolean value 0, or 1 upon successful login.
 * Side effects: Changes value of num_wizards to array index of matching wizard.
 */
bool log_in(wizard*& wiz_array, int& num_wizards) {
	bool login_success = 0;
	
	for (int i = 0; i < 4; i++) {
		// if 3 invalid attempts, terminate program and free memory
		if (i == 3) {
			std::cout << "Too many invalid attempts- exiting program." << std::endl;
			delete_wizards(wiz_array);
			
			return login_success;
		}		

		// otherwise, prompt and check wizard list
		int id = id_prompt();
		std::string password = password_prompt();
		
		for (int j = 0; j < num_wizards; j++) {
			// check array of wizards id and password for match to input
			if (wiz_array[j].id == id and wiz_array[j].password == password) {
				login_success = 1;
				num_wizards = j;
				return login_success;
			} 
		}

		if (login_success == 0) {
		std::cout << "Invalid ID or password." << std::endl;
		}
	}
return login_success;
}

/*
 * Function: print_wizard
 * Description: Prints the information of the wizard that has logged in.
 * Parameters: 
 * 		login_wizard (wizard*): A pointer to the wizard array containing
 *  	information	from the wizard info text file.		
 * Side effects: Prints logged in wizard's information to terminal.
 */
void print_wizard(wizard* login_wizard, int which_wiz) {
	std::cout << "Hello, " << login_wizard[which_wiz].name << "." << std::endl;
	std::cout << "ID: " << login_wizard[which_wiz].id << std::endl;
	std::cout << "Status: " << login_wizard[which_wiz].position_title << std::endl;
	std::cout << "Beard Length: " << login_wizard[which_wiz].beard_length << std::endl;
}

/*
 * Function: check_status
 * Description: Checks whether logged in user is a student.
 * Parameters:
 * 		wizards (wizard*): A pointer to the wizard structures array.
 * 		wiz_number (int): The index of the logged in wizard in the wizard array.
 * Returns: Boolean value 0, or 1 if user is a student.
 */
bool check_status(wizard* wizards, int wiz_number) {
	bool status = 0;

	if (wizards[wiz_number].position_title == "Student") {
		status = 1;
	}

	return status;
}

/*
 * Function: print_spells_info
 * Description: Prints information of a spell.
 * Parameters:
 * 		spellbooks (spellbook*): A pointer to dynamic array of spellbooks.
 * 		num_spellbook (int): Index of the spellbook to be printed.
 * 		status (bool): A boolean value indicating whether user is a student or not.
 * Side effects: Prints spell information to terminal.
 */
void print_spells_info(spellbook* spellbooks, int num_spellbook, bool status) {
	
	for (int i = 0; i < spellbooks[num_spellbook].num_spells; i++) {
		if (status == 1) {
			if (spellbooks[num_spellbook].spells[i].effect == "poison" or
			spellbooks[num_spellbook].spells[i].effect == "death") {
				// do nothing
			} else {
			std::cout << spellbooks[num_spellbook].spells[i].name << " " <<
			spellbooks[num_spellbook].spells[i].success_rate << " " <<
			spellbooks[num_spellbook].spells[i].effect << std::endl;
			}
		} else {
			std::cout << spellbooks[num_spellbook].spells[i].name << " " <<
			spellbooks[num_spellbook].spells[i].success_rate << " " <<
			spellbooks[num_spellbook].spells[i].effect << std::endl;
		}
	}
}

/*
 * Function: print_spellbook_info
 * Description: Prints information of a spellbook, including its spells' info.
 * Parameters:
 * 		spellbooks (spellbook*): A pointer to dynamic array of spellbooks.
 * 		num_spellbook (int): Index of the spellbook to be printed.
 * 		status (bool): A boolean value indicating whether user is a student or not.
 * 		total_spells (int): Number of spells available for user to see.
 * Side effects: Prints spellbook information to terminal.
 */
void print_spellbook_info(spellbook* spellbooks, int num_spellbook, bool status, int total_spells) {
		std::cout << "Title: " << spellbooks[num_spellbook].title << " | Author: " 
		<< spellbooks[num_spellbook].author << std::endl;
		std::cout << "# of pages: " << spellbooks[num_spellbook].num_pages << 
		" | Edition: " << spellbooks[num_spellbook].edition << std::endl;
		std::cout << "# of spells: " << total_spells << 
		" | Average Success Rate: " << spellbooks[num_spellbook].avg_success_rate  
		<< std::endl;

		print_spells_info(spellbooks, num_spellbook, status);
}

/*
 * Function: print_spellbooks
 * Description: Checks if user is a student and prints spellbook info accordingly.
 * Parameters:
 * 		spellbooks (spellbook*): A pointer to dynamic array of spellbooks.
 * 		num_spellbook (int): Index of the spellbook to be printed.
 * 		status (bool): A boolean value indicating whether user is a student or not.
 */
void print_spellbooks(spellbook* spellbooks, int num_spellbook, bool status) {
	int total_spells = spellbooks[num_spellbook].num_spells;

	if (status == 1) {
		for (int j = 0; j < spellbooks[num_spellbook].num_spells; j++) {
			if (spellbooks[num_spellbook].spells[j].effect == "poison" or 
			spellbooks[num_spellbook].spells[j].effect == "death") {
				total_spells += -1;
			}
		}
		if (total_spells < 1) {
			//do nothing - do not print spellbook
		} else {
			print_spellbook_info(spellbooks, num_spellbook, status, total_spells);
		}		
	} else {
	print_spellbook_info(spellbooks, num_spellbook, status, total_spells);
	} 
}

/*
 * Function: display_all
 * Description: Displays information of all spellbooks, including its spells info. 
 * 		Does not print poison and death spells if user is a student.
 * Parameters:
 * 		status (bool): A boolean value indicating whether user is a student or not.
 * 		spellbooks (spellbook*): A pointer to dynamic array of spellbooks.
 * 		num_books (int): Number of spellbooks in dynamic array of spellbook structures.
 * Side effects: Prints all spellbooks information to terminal.
 */
void display_all(bool status, spellbook* spellbooks, int num_books) {
	for (int i = 0; i < num_books; i++) {
		print_spellbooks(spellbooks, i, status);
	}
}

/*
 * Function: prompt_name
 * Description: Prompts user for spellbook name.
 * Returns: User input string.
 */
std::string prompt_name() {
	std::string user_input;

	std::cout << "Enter the title of a spellbook: ";
	std::cin >> user_input;

	return user_input;
}

/*
 * Function: search_name
 * Description: Prompts user for a spellbook title  and displays spellbook information
 *		if input is valid. Does not print poison and death spells if user is a student.
*		Returns to selection options if invalid title.
 * Parameters:
 * 		status (bool): A boolean value indicating whether user is a student or not.
 * 		spellbooks (spellbook*): A pointer to dynamic array of spellbook structures.
 * 		num_books (int): Number of spellbooks in dynamic array of spellbook structures.
 */
void search_name(bool status, spellbook* spellbooks, int num_books) {
	std::string title = prompt_name();
	bool match_found = 0;

	for (int i = 0; i < num_books; i++) {
		if (title == spellbooks[i].title) {
			print_spellbooks(spellbooks, i, status);
			match_found = 1;
		} 
	}

	if (match_found == 0) {
		std::cout << "No spellbook with that title found." << std::endl;
	}
}

/*
 * Function: append_effects
 * Description: Writes spell information to a user named file.
 * Parameters:
 * 		file_name (std::string): User input for file name.
 * 		spellbooks (spellbook*): A pointer to a dynamic array of spellbook structures.
 * 		num_books (int): Number of spellbooks in dynamic array of spellbook structures.
 * 		effect (std::string): User requested effect. 
 * Side effects: Creates or appends a file with the requested spell information.
 */
void append_effects(std::string file_name, spellbook* spellbooks, int num_books, std::string effect) {
	std::ofstream file;
	file.open(file_name, std::ofstream::app);

	for (int i = 0; i < num_books; i++) {
		for (int j = 0; j < spellbooks[i].num_spells; j++) {	
			if (spellbooks[i].spells[j].effect == effect) {
				file << spellbooks[i].spells[j].name << " " <<
				spellbooks[i].spells[j].success_rate << " " <<
				spellbooks[i].spells[j].effect << std::endl;	
			}
		}
	}
	std::cout << "Spells copied to file." << std::endl;
}

/*
 * Function: file_name
 * Description: Prompts user for a file name to write spell info into.	
 * Returns: String of user input for file name.
 */
std::string file_name() {
	std::string user_input;

	std::cout << "Please provide file name: ";
	std::cin >> user_input;

	return user_input;
}

/*
 * Function: print_effects
 * Description: Prints information of spells with user requested effect to terminal.
 * Parameters:
 * 		spellbooks (spellbook*): A pointer to dynamic array of spellbook structures.
 * 		num_books (int): Number of spellbooks in dynamic array of spellbook structures.
 * 		effect (std::string): User requested effect. 
 * Side effects: Prints spells with requested effect from every spellbook to terminal.
 */
void print_effects(spellbook* spellbooks, int num_books, std::string effect, bool status) {
	for (int i = 0; i < num_books; i++) {
		for (int j = 0; j < spellbooks[i].num_spells; j++) {
			if (spellbooks[i].spells[j].effect == effect) {
				std::cout << spellbooks[i].spells[j].name << " " <<
				spellbooks[i].spells[j].success_rate << " " <<
				spellbooks[i].spells[j].effect << std::endl;
			}
		}
	}
}

/*
 * Function: prompt_method
 * Description: Prompts user for preferred method of information display- 1 for
 * printing to terminal, 2 for appending to a file.
 * Returns: Number corresponding to method input by user.
 */
int prompt_method() {
	int user_input;

	do {
		std::cout << "How would you like the information displayed?" << std::endl;
		std::cout << "1 - Print info to terminal." << std::endl;
		std::cout << "2 - Print info to file." << std::endl;
		std::cout << "Your choice: ";
		std::cin >> user_input;

		if (user_input > 2 or user_input < 1) {
			std::cout << "That is not a valid input. Try again." << std::endl;
		}
	} while (user_input > 2 or user_input < 1);

	return user_input;
}

/*
 * Function: prompt_effect
 * Description: Prompts user to enter a spell effect until valid. If user is a student,
 * "poison" and "death" effects are not valid inputs. 
 * Parameters:
 * 		status (bool): A boolean value indicating whether user is a student or not.
 * Returns: String of user's effect input.
 */
std::string prompt_effect(bool status) {
	bool valid_ans = 0;
	std::string user_input;

	do {
		std::cout << "Enter a spell effect: ";
		std::cin >> user_input;

		if (status == 1) {
			if (user_input == "fire" or user_input == "bubble" or user_input == "memory_loss" ) {
				valid_ans = 1;
			} else {
				std::cout << "Invalid effect. Try again." << std::endl;
			}
		} else if (user_input == "fire" or user_input == "bubble" or 
		user_input == "memory_loss" or user_input == "poison" or user_input == "death") {
			valid_ans = 1;
		} else {
			std::cout << "Invalid effect. Try again." << std::endl;
		}
	} while (valid_ans == 0);

	return user_input;
}

/*
 * Function: search_effect
 * Description: Prompts user for a spell effect. Asks whether user would like to
 * 		print to screen or write to file and does so accordingly. 
 * Parameters:
 * 		status (bool): A boolean value indicating whether user is a student or not.
 * 		spellbooks (spellbook*): A pointer to dynamic array of spellbook structures.
 * 		num_books (int): Number of spellbooks in dynamic array of spellbook structures.
 */
void search_effect(bool status, spellbook* spellbooks, int num_books) {
	std::string effect = prompt_effect(status);

	int method = prompt_method();

	if (method == 1) {
		print_effects(spellbooks, num_books, effect, status);
	}

	if (method == 2) {
		std::string file = file_name();
		append_effects(file, spellbooks, num_books, effect);
	}
}

/*
 * Function: quit_program
 * Description: Terminates program. Deletes pointers and dynamic arrays to 
 * 		avoid memory leaks.
 * Parameters: 
 * 		exit (bool&): A reference to a bool used to quit the program.
 * 		wizards (wizard*&): A reference of the pointer to a dynamic array of wizard structures.
 * 		spellbooks (spellbook*&): A reference of the pointer to a dynamic array of spellbook structures.
 * 		num_books (int): Number of spellbooks in dynamic array of spellbook structures.
 * 		num_wiz (int): Number of wizards in dynamic array of wizard structures.
 * Returns: Modified bool variable.
 * Side effects: Modifies bool exit.
 */
bool quit_program(bool& exit, wizard*& wizards, spellbook*& spellbooks, int num_books) {
	std::cout << "Quitting program." << std::endl;
	
	// free spellbooks and spells dynamic arrays
	delete_spellbooks(spellbooks, num_books);

	// free wizards dynamic array
	delete_wizards(wizards);

	exit = 1;
	return exit;
}


/*
 * Function: select_option
 * Description: Prompts user to select an option by enternig an integer between 1-4.
 * Parameters:
 * 		status (bool): A boolean value indicating whether user is a student or not.
 * 		spellbooks (spellbook*): A pointer to a dynamic array of spellbook structures.
 * 		num_spellbooks (int): Number of spellbooks in dynamic array of spellbook structures.
 * 		wizards (wizard*): A pointer to the wizard structures array.
 */
void select_option(bool status, spellbook*& spellbooks, int num_spellbooks, wizard*& wizards) {

	int user_input; 
	bool exit = 0;

	do {
		do {
			std::cout << "Which option would you like to choose?" << std::endl;
			std::cout << "1 - Display all" << std::endl;
			std::cout << "2 - Search by spellbook name" << std::endl;
			std::cout << "3 - Search by spell effect" << std::endl;
			std::cout << "4 - Quit program" << std::endl;		
			std::cout << "Your choice: ";
			std::cin >> user_input;

			if (user_input > 4 or user_input < 1) {
			std::cout << "That is not a valid input. Try again." << std::endl;
			}
		} while (user_input > 4 and user_input < 1);
		
		// display all
		if (user_input == 1) {
			display_all(status, spellbooks, num_spellbooks);
		}

		// search book by name
		if (user_input == 2) {
			search_name(status, spellbooks, num_spellbooks);
		}

		// search spells by effect
		if (user_input == 3) {
			search_effect(status, spellbooks, num_spellbooks);
		}

		// quit do while loop
		if (user_input == 4) {
			quit_program(exit, wizards, spellbooks, num_spellbooks);
		}
	} while (exit == 0);
}

int main () {
	// initialize ifstreams
	std::ifstream wizard_info; 
	std::ifstream spellbook_info;

	// prompt for file names, open files if valid names
	if (file_prompt(wizard_info, spellbook_info) == 1) {
		// store wizard info in memory
		int num_wizards = size_wizards(wizard_info);
		wizard* wizards = populate_wizards(wizard_info, num_wizards);		

		// prompt for wizard login - 3 times max
		if (log_in(wizards, num_wizards) == 1) {
			// display wizard information upon successful login
			print_wizard(wizards, num_wizards);

			// store spellbook info in memory
			int num_spellbooks = size_spellbooks(spellbook_info);
			spellbook* spellbooks = populate_spellbooks(spellbook_info, num_spellbooks);

			// check if user is a student
			bool status = check_status(wizards, num_wizards);

			// present search options until prompted to quit
			select_option(status, spellbooks, num_spellbooks, wizards);
		}
	}
}

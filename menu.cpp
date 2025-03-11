#include "menu.h"

void provider_terminal(Table<Member> &members, Table<Provider> &providers) {
  Provider provider;
  string provider_id;
  string provider_name;
  char choice = '0';

  cout << ">>> Provider Terminal <<<\n\n";

  // Login
  while (true) {
    cout << "Enter your provider ID: ";
    cin >> provider_id;
    cin.ignore(100, '\n');
    cout << endl;

    cout << "Enter your name: ";
    getline(cin, provider_name);
    cout << endl;

    if (providers.find(provider, provider_id, provider_name) == false) {
      cout << "Invalid credentials. Please try again.\n";
    } else {
      cout << "Login successful.\n\n";
      break;
    }
  }

  // Main menu
  while (true) {
    cout << "Select an option:\n"
         << "1. Check-in a member\n"
         << "2. Display all Providers\n"
         << "3. Display all Members\n"
         << "4. Exit\n";
    cin >> choice;
    cin.ignore(100, '\n');
    cout << endl;
    switch (choice) {
    case '1':
      check_in(members, providers, provider);
      break;
    case '2':
      cout << ">>> Displaying all Providers <<<\n\n";
      providers.display();
      break;
    case '3':
      cout << ">>> Displaying all Members <<<\n\n";
      members.display();
      break;
    case '4':
      return;
    default:
      cout << "Invalid choice. Please try again.\n";
    };
  }
}

void manager_terminal(Table<Member> &members, Table<Provider> &providers) {
  string user;
  string pass;
  char choice = '0';

  cout << ">>> Manager Terminal <<<\n\n";

  /*
  cout << "Enter your Manager ID: ";
  cin >> manager_id;
  cin.ignore(100, '\n');
  cout << endl;
  */

  // Login
  cout << "Enter the username: ";
  getline(cin, user);

  cout << "Enter the password: ";
  getline(cin, pass);

  // validate credentials
  if (!validate_admin_creds(user, pass)) {
    cout << "Invalid Credentials.\n";
    return;
  } else
    cout << "Login successful.\n\n";

  while (true) {
    cout << "Select an option:\n"
         << "1. Run a report\n"
         << "2. Add a member\n"
         << "3. Remove a member\n"
         << "4. Add a provider\n"
         << "5. Remove a provider\n"
         << "6. Display all providers\n"
         << "7. Display all members\n"
         << "8. Display List of Services\n"
         << "9. Exit\n";
    cin >> choice;
    cin.ignore(100, '\n');
    cout << endl;
    switch (choice) {
    case '1':
      run_report();
      break;
    case '2':
      add_member(members);
      break;
    case '3':
      remove_member(members);
      break;
    case '4':
      add_provider(providers);
      break;
    case '5':
      remove_provider(providers);
      break;
    case '6':
      providers.display();
      break;
    case '7':
      members.display();
      break;
    case '8':
      display_services();
      break;
    case '9':
      return;
    default:
      cout << "Invalid choice. Please try again.\n";
    }
  }

  return;
}

void check_in(Table<Member> &members, Table<Provider> &providers,
              Provider provider) {
  Member member;
  string member_id;
  string member_name;
  Service service;
  string service_date;
  string service_code;
  string comments;
  char choice;

  // Collect and validate member credentials
  while (true) {
    cout << "Enter member ID: ";
    cin >> member_id;
    cin.ignore(100, '\n');
    cout << endl;

    cout << "Enter member Name: ";
    getline(cin, member_name);
    cout << endl;

    if (members.find(member, member_id, member_name)) {
      cout << "Memberhip Status: "
           << (member.get_status() ? "Validated" : "Suspended") << endl;
      if (!member.get_status())
        return;
      break;
    } else {
      cout << "Invalid credentials. Please try again.\n";
    }
  }

  // Collect and validate billing date
  regex regex_date(
      "^(0[1-9]|1[0-2])-(0[1-9]|[1-2][0-9]|3[0-1])-(19[7-9]\\d|20\\d{2})$");
  while (true) {
    cout << "Enter the date of service (MM-DD-YYYY): ";
    cin >> service_date;
    cin.ignore(100, '\n');
    cout << endl;

    if (regex_match(service_date, regex_date)) {
      break;
    } else {
      cout << "Invalid date. Please try again.\n";
    }
  }

  // display list of service codes
  display_services();

  // Collect and validate service code
  while (true) {
    cout << "Enter the service code: ";
    cin >> service_code;
    cin.ignore(100, '\n');
    cout << endl;

    service = find_service(service_code);
    if (!(service.code.empty())) { // if the code was found
      cout << service.code << ": " << service.description << endl
           << "Is this the correct service? (Y/N): ";
      cin >> choice;
      cin.ignore(100, '\n');
      if (choice == 'Y' || choice == 'y') {
        break;
      } else {
        cout << "Please try again.\n";
      }
    } else {
      cout << "Invalid service code. Please try again.\n";
    }
  }

  // Collect comments about service (optional)
  while (true) {
    cout << "Would you like to add any comments? (Y/N): ";
    cin >> choice;
    cin.ignore(100, '\n');
    cout << endl;

    if (choice == 'Y' || choice == 'y') {
      cout << "Enter comments (up to 100 characters): ";
      getline(cin, comments);
      cout << endl;
      break;
    } else if (choice == 'N' || choice == 'n') {
      break;
    } else {
      cout << "Invalid choice. Please try again.\n";
    }
  }

  // Open service record file to write
  ofstream service_file(RECORDS, ios::app);
  if (!service_file.is_open()) {
    cerr << "Error: Unable to open file." << endl;
    return;
  }

  // Open member record file to write
  string member_file_name = member_id + "_member_record.txt";
  ofstream member_file(member_file_name, ios::app);
  if (!member_file.is_open()) {
    cerr << "Error: Unable to open file." << endl;
    return;
  }
  // Initialize member record with member data if it doesn't exist
  member_file.seekp(0, ios::end);
  if (member_file.tellp() == 0) {
    member_file << "Name: " << member_name << endl;
    member_file << "Phone: " << member.get_number() << endl;
    member_file << "Address: " << member.get_address() << endl;
    member_file << "City: " << member.get_city() << endl;
    member_file << "State: " << member.get_state() << endl;
    member_file << "Zip: " << member.get_zip() << endl << endl;
  }

  // Open provider record file to write
  string provider_file_name = provider.get_id() + "_provider_record.txt";
  ofstream provider_file(provider_file_name, ios::app);
  if (!provider_file.is_open()) {
    cerr << "Error: Unable to open file." << endl;
    return;
  }

  // Initialize provider record with provider data if it doesn't exist
  provider_file.seekp(0, ios::end);
  if (provider_file.tellp() == 0) {
    provider_file << "Name: " << provider.get_name() << endl;
    provider_file << "Phone: " << provider.get_number() << endl;
    provider_file << "Address: " << provider.get_address() << endl;
    // provider_file << "City: " << provider.get_city() << endl;
    provider_file << "State: " << provider.get_state() << endl;
    provider_file << "Zip: " << provider.get_zip() << endl;
  }

  // Get and format current date and time
  time_t current_time = time(nullptr);
  tm *local_time = localtime(&current_time);
  char formatted_time[20];
  strftime(formatted_time, sizeof(formatted_time), "%m-%d-%Y %H:%M:%S",
           local_time);

  // Write service details to service report
  service_file << "Current Date and Time: " << formatted_time << endl;
  service_file << "Date Service Provided: " << service_date << endl;
  service_file << "Provider Phone: " << provider.get_number() << endl;
  service_file << "Member Phone: " << member.get_number() << endl;
  service_file << "Service Code: " << service.code << endl;
  if (!comments.empty()) {
    service_file << "Comments: " << comments << endl;
  }
  service_file << endl << endl;

  // Write member details to member record
  member_file << "Date Service Provided: " << service_date << endl;
  member_file << "Provider Name: " << provider.get_name() << endl;
  member_file << "Service: " << service.description << endl << endl;

  // Write provider details to provider record
  provider_file << "Date Service Provided: " << service_date << endl;
  provider_file << "Date Service Billed: " << formatted_time << endl;
  provider_file << "Member Name: " << member_name << endl;
  provider_file << "Member Phone: " << member.get_number() << endl;
  provider_file << "Service Code: " << service.code << endl;
  provider_file << "Fee: " << service.fee << endl << endl;

  return;
}

vector<string> split(const string &s, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream token_stream(s);
  while (getline(token_stream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

Service find_service(const string &target) {
  ifstream file(DIRECTORY);
  string line;
  Service found;

  while (getline(file, line)) {
    vector<string> parts = split(line, '|');
    if (parts.size() == 3) {
      if (parts[0] == target) {
        found.code = parts[0];
        found.description = parts[1];
        found.fee = stod(parts[2]);
        file.close();
        return found;
      }
    }
  }

  file.close();
  return Service();
}

void run_report() {
  char report_code;
  string id;
  string filename;

  while (true) {
    cout << "Which report would you like to run? Enter a report code:\n"
         << "\t1: Member report\n\t2: Provider report\n\t3: Summary report\n";
    cin >> report_code;
    cin.ignore(100, '\n');
    cout << endl;
    if (report_code != '1' && report_code != '2' && report_code != '3') {
      cout << "Invalid report code. Please try again.\n\n";
    } else {
      break;
    }
  }

  switch (report_code) {
  case '1':
    cout << ">> Running Member Report <<\n\n";
    display_file(RECORDS);
    break;
  case '2':
    cout << "Enter the provider ID: ";
    cin >> id;
    cin.ignore(100, '\n');
    filename = id + "_provider_record.txt";
    cout << "\n\n>> Running Provider Report <<\n\n";
    display_file(filename);
    break;
  case '3':
    cout << "Enter the member ID: ";
    cin >> id;
    cin.ignore(100, '\n');
    filename = id + "_member_record.txt";
    cout << ">> Running Summary Report <<\n\n";
    display_file(filename);
    break;
  }
  return;
}

bool add_provider(Table<Provider> &providers) {
  // provider class data
  string name;
  string number;
  string address;
  string state;
  string city;
  string zip;
  string id;
  string service_code;
  float fee = 0.0;

  cout << "Enter info about the provider to add:\n";
  cout << "\nName: ";
  getline(cin, name);
  cout << "\nPhone: ";
  cin >> number;
  cin.ignore(100, '\n');
  cout << "\nAddress: ";
  getline(cin, address);
  cout << "\nState: ";
  cin >> state;
  cin.ignore(100, '\n');
  cout << "\nZipcode: ";
  cin >> zip;
  cin.ignore(100, '\n');
  cout << "\nID: ";
  cin >> id;
  cin.ignore(100, '\n');
  cout << "\nService Code: ";
  cin >> service_code;
  cin.ignore(100, '\n');
  cout << "\nFee: ";
  cin >> fee;
  cin.ignore(100, '\n');
  cout << endl;

  Provider to_add(name, number, address, state, city, zip, id, fee,
                  service_code);
  if (providers.add(to_add)) {
    cout << "Provider added successfully.\n";
    return true;
  } else {
    cout << "Error: Provider could not be added.\n";
    return false;
  }
}

bool remove_provider(Table<Provider> &providers) {
  string id;
  string name;

  cout << "Enter the ID of the provider to remove: ";
  cin >> id;
  cin.ignore(100, '\n');
  cout << endl;

  cout << "Enter the name of the provider to remove: ";
  getline(cin, name);
  cout << endl;

  if (providers.remove(id, name)) {
    cout << "Provider removed successfully.\n";
    return true;
  }

  else {
    cout << "Provider not found.\n";
    return false;
  }
}

bool add_member(Table<Member> &members) {
  string name;
  string number;
  string address;
  string state;
  string city;
  string zip;
  string id;
  bool status;
  string comments;

  cout << "Enter info about the Member to add:\n";
  cout << "\nName: ";
  getline(cin, name);

  cout << "\nPhone: ";
  cin >> number;
  cin.ignore(100, '\n');

  cout << "\nAddress: ";
  cin >> address;
  cin.ignore(100, '\n');

  cout << "\nState: ";
  cin >> state;
  cin.ignore(100, '\n');

  cout << "\nZipcode: ";
  cin >> zip;
  cin.ignore(100, '\n');

  cout << "\nID: ";
  cin >> id;
  cin.ignore(100, '\n');

  cout << "\nStatus (1 for valid, 0 for suspended): ";
  cin >> status;
  cin.ignore(100, '\n');

  cout << "\nComments: ";
  getline(cin, comments);

  Member to_add(name, number, address, state, city, zip, id, status, comments);

  if (members.add(to_add)) {
    cout << "Member added successfully.\n";
    return true;
  } else {
    cout << "Error: Member could not be added.\n";
    return false;
  }
}

bool remove_member(Table<Member> &members) {
  string id;
  string name;

  cout << "Enter the ID of the member to remove: ";
  cin >> id;
  cin.ignore(100, '\n');
  cout << endl;

  cout << "Enter the name of the member to remove: ";
  getline(cin, name);
  cout << endl;

  if (members.remove(id, name)) {
    cout << "Member removed successfully.\n";
    return true;
  }

  else {
    cout << "Member not found. Please try again.\n";
    return false;
  }
}

void display_services() {
  ifstream file_in;
  Service services;

  file_in.open(DIRECTORY);
  cout << ">> Service Codes <<\n\n";

  if (file_in) {
    getline(file_in, services.code, '|');
    while (!file_in.eof()) {
      getline(file_in, services.description, '|');
      file_in >> services.fee;
      file_in.ignore(100, '\n');

      // show the service codes and their description
      cout << "Service Code: " << services.code << endl;
      cout << "Description: " << services.description << endl;
      cout << "Fee: $" << fixed << setprecision(2) << services.fee << endl
           << endl;

      getline(file_in, services.code, '|');
    }
  }
  file_in.close();
}

void display_file(string filename) {
  string line;
  ifstream file(filename);
  if (!file.is_open()) {
    cout << "Error: Unable to open file.\n";
    return;
  }

  while (getline(file, line)) {
    cout << line << endl;
  }

  file.close();
}

bool validate_admin_creds(const string &user, const string &pass) {
  string admin_usr;
  string admin_pass;
  ifstream file_in;

  file_in.open("admin_cred.txt");
  if (file_in) {
    getline(file_in, admin_usr, ':');
    getline(file_in, admin_pass, '\n');
  }

  file_in.close();

  if (user == admin_usr && pass == admin_pass)
    return true;
  else
    return false;
}

#include "menu.h"
// #include "table.h" <- included in menu.h

int main() {
  Table<Member> MembersList;
  Table<Provider> ProvidersList;
  char choice[10];

  // Load the list of members and providers
  MembersList.load_member(MEMBER_FILE);
  ProvidersList.load_provider(PROVIDER_FILE);

  // Display appropriate terminal
  while (true) {
    cout << "Are you a Provider or a Manager?: ";
    cin >> choice;
    cin.ignore(100, '\n');
    cout << endl;
    if (strcasecmp(choice, "provider") == 0 || strcasecmp(choice, "p") == 0) {
      provider_terminal(MembersList, ProvidersList);
      break;
    } else if (strcasecmp(choice, "manager") == 0 ||
               strcasecmp(choice, "m") == 0) {
      manager_terminal(MembersList, ProvidersList);
      break;
    } else {
      cout << "Invalid choice. Please try again.\n";
    }
  }

  // save just before exiting.
  MembersList.save(MEMBER_FILE);
  ProvidersList.save(PROVIDER_FILE);

  return 0;
}
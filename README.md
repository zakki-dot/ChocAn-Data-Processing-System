# ChocAn-Data-Processing-System

The ChocAn Data Processing System is a command line application designed to manage employee and provider payroll records efficiently. It implements a structured approach to storing and retrieving member and provider data while offering secure authentication, automated payroll calculations, and report generation.

At the core of the system is an object-oriented design that defines three primary classes: Person, Member, and Provider. The Person class serves as a base for both Member and Provider, handling basic information such as name, address, phone number, and ID. Members represent employees who receive services, while Providers are service personnel who facilitate these services. Each provider is associated with a service code and a corresponding fee, stored in the provider_directory.txt file.

The system operates through a menu-driven interface that allows users to interact with two main terminals: Provider Terminal and Manager Terminal. In the Provider Terminal, providers can log in, check-in members for services, and view a list of members and providers. Providers authenticate using their ID and name, after which they can enter service details, including the date of service, service code, and optional comments. The system ensures data integrity by validating inputs such as service codes and member IDs.

In the Manager Terminal, managers authenticate with admin credentials stored in admin_cred.txt. Once logged in, they can generate reports, add or remove members and providers, and display records. The reports include member reports, provider reports, and summary reports, which detail payroll information and service history. The check-in process records transactions between providers and members, ensuring that service details are correctly stored in both provider and member records.

The backend structure relies on a hash table-based data storage system, implemented in table.h and table.tpp. This allows for efficient lookup, retrieval, and storage of members and providers based on their unique IDs. The system reads and writes data to list_of_members.txt and list_of_providers.txt, ensuring persistence between program executions.

To use the system, the user first compiles the program using a Makefile or a standard g++ compilation command. Running the program presents a prompt asking whether the user is a provider or manager, guiding them to the appropriate terminal. The data is automatically saved before exiting, ensuring that all modifications are retained.

This project provides a structured, efficient, and secure way to manage payroll and service records for an organization, making it an essential tool for tracking financial transactions and personnel activities.

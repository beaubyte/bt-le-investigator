# bt-le-investigator

`bt-le-investigator` is a simple project that grabs nearby Bluetooth Low Energy devices and their MAC Addresses, and uploads them to a given database specified at the start of the program.

I built this program for Ubuntu, so I cannot promise compatibility with other platforms.
### Warning
This program is for demonstration purposes only, and DOES NOT store the password securely when in RAM. Other programs could potentially pull this data and obtain the database password, so do not use this program for important tasks.

### Dependencies
This project requires a few key dependencies to compile, best retrieved from apt-get on Ubuntu
- `cmake`
- `ninja-build`
- `qt6-base-dev`
- `qt6-tools-dev`
- `qt6-connectivity-dev`
-  `libqt6sql6-psql` 

### Compilation Instructions
- Ensure the dependencies are installed
- Clone the repository into a local directory with `git clone`
- `cd` into the project folder
- Make a build directory with `mkdir build`
- Generate buildfiles with `cmake -S ./ -G Ninja -B build`
- `cd` into build folder
- Run `ninja` to compile the project

### Usage
When the program starts up, it will ask for a **Location**. This is what will be put into the database for where the Bluetooth device was found, so it is completely abstract. Any string can be put here, so it can refer to a device, room, or building.

Afterwards, the program will ask for attributes of your database. These will be saved for the next time the program launches, with the exception of the password which must be entered at deployment each time.

The program assumes a database exists with this schema:

[[docs/database_structure.png]]

The schema must be called bluetooth, as part of the investigator table. A file with the schema called `investigator-schema.sql` has been included to help with the construction of the database. Replace `[user]` with the user in your PostgreSQL database with permissions to insert and delete from the database.
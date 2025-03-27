# Berg Build System

**A quick note:**
- As of v1.0.59122: This is only a very tiny hobby project. Do not use this for high levels of software. Small projects only. If you want to use it for big projects, go ahead.



## Overview

Berg is a very tiny build system focused on simplicity and transparency, inspired by Ninja. It is designed to provide quick feedback during the build process with clear, verbose logging to help developers understand what's happening behind the scenes.

## Features

- **Speed**: Berg focuses on minimizing the overhead of the build process.
- **Transparency**: Verbose logging shows exactly why a build is triggered and what commands are executed.
- **Incremental Builds**: Only rebuilds files that have changed, reducing unnecessary work.
- **Parallel Builds**: Takes advantage of multi-core systems to speed up the build process.
- **Error Handling**: Provides detailed error messages to help diagnose issues quickly.

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/owgydz/berg.git
   cd berg
2. Compile the Berg executable:
   ```
   g++ -o berg main.cpp fs.cpp parser.cpp -std=c++17
3. Ensure that the berg executable is in your PATH or use it directly by running `./berg.`

## Usage
Berg operates on a project configuration file (autogen at build.berg), where you define the build targets, source files, and the commands to run. You can create a template file by using `berg init`

## Commands
1. `build`
Builds the target specified in the build.berg file. Rebuilds only if necessary (e.g., if source files have changed). Run via:
`berg build`

2. `clean`
Removes the target file specified in the build.berg file. Run via:
`berg clean`

3. `status`
Checks if the target is up to date. Prints whether the target needs rebuilding or not. Run via:
`berg status`

4. `init`
Initialize a new Berg project. You can optionally specify a custom target file with the command flag `-t.`

`./berg init [-t <target-file>]`

## Configuration
The build.berg file is a simple text file that defines the targets, source files, and build commands.

Here's an example `build.berg` file.

```
target: my_program
source: main.cpp utils.cpp
command: g++ -o my_program main.cpp utils.cpp
```
Where:

target: The output file to be generated.

source: The source files required for the build.

command: The command used to build the target.


## Advanced Features

***Parallel Builds**

Berg can be configured to take advantage of multiple CPU cores to build targets in parallel. This can speed up the build process for large projects with multiple targets.

**Incremental Builds**

Berg tracks file modification times and only rebuilds targets when the source files have changed. This reduces unnecessary rebuilds and speeds up the development cycle.

**Contribution**

Berg is open-source and contributions are welcome! If you have suggestions or bug reports, please open an issue or submit a pull request.

**License**

Berg is licensed under the Apache License, v2.0. See the LICENSE file for more details.

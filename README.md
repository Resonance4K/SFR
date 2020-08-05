
# SFR

A command line source file reader written in C.

## Table of Contents

- [Screenshots](#screenshots)
- [Supported Platforms](#supported-platforms)
- [Installation](#installation)
- [Usage](#usage)
- [Supported File Types and Extensions](#supported-file-types-and-extensions)
- [Definition of Statistics](#definition-of-statistics)
- [Change Log](#change-log)

## Screenshots

<p align="center">
	Program Output
	<br />
	<img src="/screenshots/output.png?raw=true" alt="Output" />
</p>

## Supported Platforms

The program is currently being supported on the following platforms:

- Windows
- Linux

## Installation

_**Note:** The Make and GNU Compiler Collection (GCC) tools are required to use the provided makefile for program compilation._

<br />

Download the latest version of the program source from the repository's [release](https://github.com/Resonance4K/SFR/releases) page and extract the contents of the ZIP file to your local file system.

If we define the installation directory of the program as

```
[WINDOWS]
C:/SFR

[LINUX]
~/SFR
```

and we compile the program by running the provided makefile in a command prompt or terminal (after navigating to the above directory) with

```
make build
```

then an executable binary file should have been created with a directory path of

```
[WINDOWS]
C:/SFR/bin/SFR

[LINUX]
~/SFR/bin/SFR
```

If the program needs to be recompiled then replace the above `make build` command with `make rebuild` instead.

## Usage

_**Note:** This section only applies once the program has been compiled and an executable has been created as per the instructions under the [installation](#installation) section._

<br />

If we define the installation directory of the program as

```
[WINDOWS]
C:/SFR

[LINUX]
~/SFR
```

and if we define the directory path that should be read by the program as

```
[WINDOWS]
C:/TestDir

[LINUX]
~/TestDir
```

then the program can be invoked by running one of the following commands in a command prompt or terminal where the first part points to the executable binary file followed by any input parameters

```
[WINDOWS]
1.  C:/SFR/bin/SFR C:/TestDir
2.  C:/SFR/bin/SFR C:/TestDir d:5

[LINUX]
1.  ~/SFR/bin/SFR ~/TestDir
2.  ~/SFR/bin/SFR ~/TestDir d:5
```

As shown above, the program accepts a minimum and maximum of 1 and 2 input parameters respecfully. The first command represents all mandatory input parameters where as the second command represents all mandatory and optional input parameters.

The mandatory input parameters must be specified in order and are as follows:

| Position | Flags | Default Value | Name           |
|:--------:|:-----:|:-------------:|:---------------|
| 1        |       |               | Directory Path |

The optional input parameters can be specified in any order with the exception that they must be specified after the mandatory input parameters and are as follows:

| Flags | Default Value | Name                      |
|:-----:|:-------------:|:--------------------------|
| d     | 12            | Directory Traversal Depth |

If an input parameter uses flags then their associated value is separated by a colon in the format

```
FLAGS:VALUE
```

## Supported File Types and Extensions

The program supports the following file types and their extensions:

| File Type    | File Extension |
|:-------------|:---------------|
| Java         | .java          |
| C            | .c             |
| C++          | .cpp           |
| C/C++ Header | .h and .hpp    |
| C#           | .cs            |

## Definition of Statistics

**Physical Lines**\
_Lines of code that are responsible for executing and assisting the execution of a program._

**Blank Lines**\
_Lines of code that contain only control characters such as LF and CR (no visible characters)._

**Comment Lines**\
_Lines of code that provide human readable annotations of a program's source code._

**Total Lines**\
_The total number of lines of code resulting from the sum of physical lines, blank lines and comment lines._

**File Count**\
_The number of files read for each file type supported by the program._

## Change Log

Refer to the repository's [release](https://github.com/Resonance4K/SFR/releases) page for more information.

<br />

<!-- Miscellaneous section with an empty heading acting as a horizontal rule -->
##

<p align="center">
	<a href="#sfr">Back to Top</a>
</p>

# Minishell Project Overview

## Introduction
The Minishell project is an engaging challenge at 42, aimed at deepening students' understanding of Unix shell interactions by building a simplified shell program, referred to as Minishell. This project covers fundamental concepts such as process creation, execution, signal handling, and environment management, mirroring the functionality of shells like bash.

## Objectives
- **Shell Prompt:** Implement a functional shell prompt that accurately reads and processes user input.
- **Command Execution:** Enable the execution of executable commands within the shell environment, along with built-in commands like `cd`, `echo`, `pwd`, `export`, `unset`, and `env`.
- **Signal Handling:** Properly manage signals (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) to mimic the behavior of bash.
- **Environment Variables:** Support for setting, updating, and unsetting environment variables.

## Bonus Achievements
To extend the project's complexity and functionality, the following bonus features were implemented:
- **Binary Tree for Command Parsing:** Adopted a binary tree structure to efficiently parse and execute commands. This approach facilitated the handling of complex command structures and redirections through recursive descent parsing, enhancing the shell's capability to process input accurately and flexibly.

## Technologies Used
- C Programming Language
- GNU Readline Library

## Challenges Faced
- **Parsing Complexity:** Developing a parser using binary trees and recursive descent introduced complexity, particularly in accurately recognizing and executing various command structures and redirections.
- **Signal Handling:** Mimicking bash's signal handling required a deep understanding of Unix signals and process control.
- **Memory Management:** Ensuring efficient and leak-free memory management throughout the development of the shell, especially within the parsing mechanism.

## Outcomes
The Minishell project successfully replicated key functionalities of a Unix shell, providing a solid foundation in system programming and Unix system interactions. The implementation of a binary tree for command parsing as a bonus significantly enhanced the shell's parsing capabilities, offering a robust solution to command execution challenges.

## Conclusion
Through the Minishell project, I gained profound insights into the workings of Unix shells, process management, and advanced parsing techniques. This project was not only a testament to my growing programming skills but also an opportunity to tackle complex system programming challenges head-on, pushing the boundaries of what I could achieve with C programming.

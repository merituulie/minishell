# Introduction to Minishell

🐚 This project implements a simple yet powerful shell environment, providing users with a versatile interface to interact with their operating system.

## Features 🚀

- **Interactive Prompt**: Minishell greets you with a friendly prompt, ready to execute your commands and fulfill your computing needs.

- **Command History**: With built-in command history support, navigating through your previous commands is a breeze, allowing for quick access to your command lineage.

- **Command Execution**: Harness the power of Minishell's command execution engine, effortlessly locating and running executables based on the PATH variable.

- **Input and Output Redirection**: Redirect input and output streams with ease using Minishell's redirection operators (`<`, `>`, `<<`, `>>`), enabling efficient data manipulation.

- **Pipeline Support**: Seamlessly connect multiple commands using pipelines (`|`), facilitating the flow of data between processes and enabling complex command chaining.

- **Environment Variable Expansion**: Expand environment variables (`$`) on-the-fly, allowing for dynamic value substitution and flexible command execution.

- **Built-in Commands**: Minishell offers a suite of essential built-in commands, including `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`, providing essential control over the shell environment.

- **Signal Handling**: Experience robust signal handling capabilities, ensuring graceful handling of signals such as `ctrl-C`, `ctrl-D`, and `ctrl-\`.

## Get Started 🛠️

Follow these steps to set up your Minishell using the provided Makefile.

## 1. Clone the Repository 📁

git clone <repository_url>
cd <repository_name>

# Setting Up Minishell with Makefile

Follow these steps to set up your Minishell project using the provided Makefile.

## 2. Compile the Project

To compile the Minishell project, run the following command:

```make all```

## 3. Cleaning Up

If needed, you can remove the built files using:

```make clean```
```make fclean```

## 4. Rebuilding the Project

To perform a clean rebuild, removing all object files and recompiling the project, use:

```make re```

## 5. Running the Minishell

Once compiled, you can run the Minishell executable by typing:

```./minishell```

Enjoy exploring the capabilities of your Minishell environment!

Happy shell scripting! 🌟

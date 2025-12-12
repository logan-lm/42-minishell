This project has been created as part of the 42 curriculum by pberne, lomartin

# Description

The goal of this project is to reproduce a basic shell behavior :
- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
- Use at most one global variable to indicate a received signal.
- Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
- Handle ’ (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for $ (dollar sign).
- Implement the following redirections:
  - < redirects input.
  - > redirects output.
  - > << reads the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
  - >> redirects output in append mode.
- Implement pipes (| character).
- Handle environment variables.
- Handle $?.
- Handle ctrl-C, ctrl-D and ctrl-\.
- Implement the following built-in commands:
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options

# Insctructions

Compile using make command
```bash
make minishell
```

# Ressources

- None
